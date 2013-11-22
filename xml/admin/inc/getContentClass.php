<?
	interface contentGetter {
		public function get_contents($content);
		public function checkUrl($url);
	}

	abstract class abstractContentGetter implements contentGetter {
		public $parameters = array();
		public function __construct($params = array()){
			$this->parameters = $params;
		}
		
		public function get_contents($content){
			return $content;
		}
		public function checkUrl($url){
			$result = @file_get_contents($url);
			if ($result === false){
				return false;
			} else {
				return $this->get_contents($result);
			}
		}
		
		public function asJson($url){
			$result = $this->checkUrl($url);
			if ($result !== false){
				$result = json_decode($result);
				if ($result !== null){
					return $result;
				} else {
					return false;
				}
			} else {
				return $result;
			}
			
		}
	}
	
	class simpleContentReturner extends abstractContentGetter {
		
	}
	
	class proxyContentReturner extends abstractContentGetter {
		
		public function checkUrl($url){
			$requestUrl = $this->makeRequestUrl($url);
			$result = @file_get_contents($requestUrl);
			if ($result === false){
				return false;
			} else {
				$this->get_contents($result);
			}
		}
		
		public function makeRequestUrl($url){
			$urlIndex = array_search('{*url*}', $this->parameters['vars']);
			if ($urlIndex !== false){
				$this->parameters['vals'][$urlIndex] = $url;
			}
			return str_replace($this->parameters['vars'], $this->parameters['vals'], $this->parameters['tmpl']);
		}
	}
	
	class contentReturnerProcessor {
		public $config = array();
		public $type = false;
		public function __construct($conf = array(), $type = false){
			$this->config = $conf;
			$this->type = $type;
		}
		
		public function get_content($url){
			foreach($this->config as $ind=>$elem){
				if (class_exists($elem["name"])){
					$name = $elem["name"];
					$obj = new $name($elem['parameters']);
					if ($this->type && arra_search($this->type, get_class_methods($name)) !== false){
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