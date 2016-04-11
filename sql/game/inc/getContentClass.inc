<?
	/**
	 * Интерфейс для геттеров контента по URL
	 * в случае если file_get_content не работает для localhost
	 * @author Alexander
	 *
	 */
	interface contentGetter {
		/**
		 * Пост обработка пришедшего ответа
		 * поумолчанию просто возвращает то что пришло
		 * @param unknown $content
		 */
		public function get_contents($content);
		
		/**
		 * Проверяет что ответ пришел и возвращет его
		 * @param String $url
		 * 						- адрес на который будет отправлен запрос
		 */
		public function checkUrl($url);
	}

	/**
	 * Реализация базового геттера
	 * через file_get_contents
	 * @author Alexander
	 *
	 */
	abstract class abstractContentGetter implements contentGetter {
		public $parameters = array();
		/**
		 * Конструктор с установкой параметров геттера
		 * @param array() $params
		 * 						- массив параметров
		 */
		public function __construct($params = array()){
			$this->parameters = $params;
		}
		
		public function get_contents($content){
			return $content;
		}
		public function checkUrl($url){
			$opts = array(
					'http'=>array(
							'method'=>"GET",
							'header'=>"Cookie: ".$this->getCookieStringHeader()
					)
			);
			
			$context = stream_context_create($opts);
			$result = @file_get_contents($url, false, $context);
			if ($result === false){
				return false;
			} else {
				return $this->get_contents($result);
			}
		}
		
		public function getCookieStringHeader(){
			$result = "";
			foreach (array_keys($_COOKIE) as $key=>$value){
				$result.= $result == "" ? $value."=".$_COOKIE[$value] : ";".$value."=".$_COOKIE[$value];
			}
			return $result;
		}
		
		/**
		 * 
		 * @param String $url
		 * @return 
		 * 			false - если не удалось преобразовать в json или ничего не пришло с $url
		 * 			Array() - если пришел валидный json и удачно преобразовался в массив/объект
		 */
		public function asJson($url){
			$result = $this->checkUrl($url);
			if ($result !== false){
				if (json_decode($result) !== null){
					return $result;
				} else {
					return false;
				}
			} else {
				return $result;
			}
			
		}
	}
	
	/**
	 * Реализация геттера через file_get_contents
	 * @author Alexander
	 *
	 */
	class simpleContentReturner extends abstractContentGetter {
		
	}
	
	/**
	 * Реализация геттера через проксирующий сайт
	 * Работает в случае, если запрешены file_get_contents с localhost
	 * @author Alexander
	 *
	 */
	class proxyContentReturner extends abstractContentGetter {
		
		public function checkUrl($url){
			$requestUrl = $this->makeRequestUrl($url);
			$result = @file_get_contents($requestUrl);
			if ($result === false){
				return false;
			} else {
				return $this->get_contents($result);
			}
		}
		/**
		 * Формирование строки запроса
		 * @param String $url
		 * 					- адрес запроса
		 * @return String
		 * 					- адрес с учетом прокси
		 */
		public function makeRequestUrl($url){
			$urlIndex = array_search('{*url*}', $this->parameters['vars']);
			if ($urlIndex !== false){
				$this->parameters['vals'][$urlIndex] = $url;
			}
			return str_replace($this->parameters['vars'], $this->parameters['vals'], $this->parameters['tmpl']);
		}
	}
	/**
	 * Геттер контента через curl
	 * @author Alexander
	 *
	 */
	class curlContentReturner extends simpleContentReturner{
		
		public function checkUrl($url){
			if (!$this->isCurl()) return false;
			$ch = curl_init();
			if (strtolower($this->parameters['method']) == 'post'){
				curl_setopt($ch, CURLOPT_POST, true);
				if (count($this->parameters['args'])>0){
					$args = "";
					foreach ($this->parameters['args'] as $name=>$value){
						$args.=$args == "" ? $name."=".$value : $args."&".$name."=".$value;
					}
					curl_setopt($ch, CURLOPT_POSTFIELDS, $args);
				}
			}
			curl_setopt($ch, CURLOPT_HEADER, 0);
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
			curl_setopt($ch, CURLOPT_URL, $url);
			 
			$data = curl_exec($ch);
			curl_close($ch);
			 
			return $this->get_contents($data);
		}
		
		public function isCurl(){
			return function_exists('curl_version');
		}
		
	}
	
	/**
	 * В соответствии с переданным конфигом
	 * запускает геттеры и при первой удаче возвращает ответ от сервера
	 * @author Alexander
	 *
	 */
	class contentReturnerProcessor {
		/**
		 * Пример конфига:
		 json_decode('{
			"0":{"name":"simpleContentReturner", "parameters":[]},
			"1":{"name":"proxyContentReturner", "parameters":{
																"vars":["{*url*}"], 
																"vals":["url"], 
																"tmpl":"http://anonymouse.org/cgi-bin/anon-www.cgi/{*url*}"}
															}
		}',true);
		 * 
		 */
		public $config = array();
		/**
		 * Позволяет задать метод который необходимо вызвать у геттера
		 * для получения ответа
		 */
		public $type = false;
		public function __construct($conf = array(), $type = false){
			if ($conf != null){
				$this->config = $conf;
			} else {
				$this->config = json_decode('{
											"0":{"name":"simpleContentReturner", "parameters":[]},
											"1":{"name":"curlContentReturner", "parameters":[]},
											"2":{"name":"proxyContentReturner", "parameters":{
																								"vars":["{*url*}"], 
																								"vals":["url"], 
																								"tmpl":"http://anonymouse.org/cgi-bin/anon-www.cgi/{*url*}"}
																							}
										}',true);
			}
			$this->type = $type;
		}
		
		/**
		 * 
		 * @param String $url
		 * 					- адрес запроса
		 * @return unknown
		 * 					- 
		 */
		public function get_content($url){
			foreach($this->config as $ind=>$elem){
				if (class_exists($elem["name"])){
					$name = $elem["name"];
					$obj = new $name($elem['parameters']);
					if ($this->type && array_search($this->type, get_class_methods($name)) !== false){
						$method = $this->type;
						$result = $obj->$method($url);
					} else {
						$result = $obj->checkUrl($url);
					}
					if ($result !== false){
						return $result;
					}
				}
			}
		}
	}
	
?>