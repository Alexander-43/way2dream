<?
	function GAMES($postData){
		if (count($postData) != 0)
		{
			addNewGame($postData['url'], $postData['title'], $postData['active'], $postData['objectId']);
		}
		require (rootSite."/tpl/games.forms.addNewGame.tpl");
	}
	
	function PRESENTERS($postData)
	{
		if (count($postData) != 0)
		{
		      global $filesAttribs;
		      $temp = makeDataArray($postData, $filesAttribs[presenter]);
		      $temp['object'] = $temp['node'];
		      if (strlen($postData['objectId']) == 0)
		      {
			$temp['unic'] = 'new';
			$temp['id'] = mktime();
		      }
		      else
		      {
			$temp['unicValue'] = $postData['objectId'];
		      }
		      $temp['active'] = isset($temp['active']) ? 'true' : 'false';
		      if ($temp['password'] != 'Пароль')
		      {
			$temp['password'] =  md5($temp['password']);
		      }
		      else
		      {
			unset($temp['password']);
		      }
		      if (checkGame($postData['assignTo']))
		      {
			$req = sendRequest($postData['assignTo']."/operation.php?operId=updateObject&data=".urlencode(json_encode($temp)), false, "Не удалось сохранить ведущего");
			if ($req = "OK")
			{
			  print "<script>showStatusText(message['downStatusId'], message['saveSucc'], 2000, true);</script>";
			}
			else
			{
			  print "<script>showStatusText(message['downStatusId'], ".$req.", 2000, true);</script>";
			}
		      }
		      else
		      {
			print "<script>alert('Выбранная вами игра не доступна. Схранение не возможно!');</script>";
		      }
		}
		require (rootSite."/tpl/presenters.forms.addNewPresenter.tpl");
	}
	
	function GAMERS($postData)
	{
		require (rootSite."/tpl/gamers.forms.addNewGamer.tpl");
	}
	
	function SETTINGS($postData)
	{
		if (count($postData) != 0)
		{
		  $ini = new TIniFileEx(iniFile);
		  if (strlen($postData['newPass']) != 0)
		  {
		    if (md5($postData['currentPass']) == $ini->read('password', 'current', null) && $postData['newPass'] == $postData['newPassAgain'])
		    {
		      $ini->write('password', 'current', md5($postData['newPass']));
			  $_SESSION['adminPass'] = md5($postData['newPass']);
		    }
		    else
		    {
		      print "<script>alert('Не удалось сохранить новый пароль');</script>";
		    }
		  }
		  $ini->write('setting', 'adminUrl', $postData['adminUrl']);
		  $ini->write('setting', 'adminEmail', $postData['adminEmail']);
		  $ini->updateFile();
		}
		require (rootSite."/tpl/settings.forms.setting.tpl");
	}
	
	function REQUEST($postData){
		require (rootSite."/tpl/request.form.tpl");
	}
 	
	function checkAuth($data)
	{
	  $ini = new TIniFileEx(iniFile);
	  if ($data['adminPass'] != $ini->read('password', 'current', null))
	  {
	    print "<script>alert('Страница закрыта для общего доступа. \\nВы ввели неверный пароль или попали на эту странцу \\nне через форму авторизации'); document.location.replace('index.php');</script>";
	  }
	  else
	  {
	    return true;
	  }
	}
	/*
	* Проверка существования записи в xml-файле
	* $fileName - Имя файла
	* $elementName - Имя nod`a
	* $attribName - Имя атрибута
	* $value - Значение для поиска
	*/
	function existInXml($fileName, $elementName, $attribName, $value){
		$xml = new ParseXML($fileName, false);
		$xml->SearchNode($xml->RootNode, $elementName, $attribName, $value);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->Destroy();
			return true;
		}
		else
		{
			$xml->Destroy();
			return false;
		}
	}
	
	/*
	* Проверка доступности удаленной игры
	* $url - URL игры
	*/
	function checkGame($url)
	{
		return get_content($url."/operation.php?operId=testConnection&url=".$url);
	}
	
	function sendRequest($url, $returnResult = false, $errorMessage = "")
	{
	  $req = get_content($url);
	  if ($returnResult && $req)
	  {
	    return $req;
	  }
	  else
	  {
	    if ($req == "OK")
	    {
	      return $req;
	    }
	    else
	    {
	      try{
			header('HTTP/1.1 500 Internal Server Error');
				return $errorMessage;
			} catch(Exception $e){
				$errorMessage = $errorMessage."(".$e.")";
			}
			return $errorMessage;
	    }
	  }
	}
	
	/*
	* Добавляет новую игру
	* $url - адрес страницы
	* $title - отображаемый заголовок
	* $active - признак активности сайта
	*/
	function addNewGame($url, $title, $active, $objectId){
		if (strlen($objectId) == 0)
		{
			$url = makeUrlDir($url);
		}
		$id = strlen($objectId) == 0 ? md5($url) : $objectId;
		$xml = new ParseXML(gamesXml, true);
		$xml->SearchNode($xml->RootNode, "game", "id", $id);
		$link = $xml->SearchedNodeLink != null ? $xml->SearchedNodeLink : "new";
		$attribValues = array("id" => md5($url), "url" => $url, "title" => $title, "active" => $active);
		$xml->ModifyElement("game", $attribValues, $link);
		$xml->Destroy();
	}
	
	/*
	* Получить все/только доступные игры
	* $fileName - имя xml-файла
	* $onlyActive - true/false
	*/
	function getGames($fileName, $onlyActive = true)
	{
	  $xml = new ParseXML($fileName);
	  $xml->GetNodesAttribsValuesByName($xml->RootNode, "game", "id");
	  $NAV = $xml->nodesAttribValue;
	  $info = array();
	  foreach ($NAV as $elem)
	  {
		  $xml->SearchNode($xml->RootNode, "game", "id", $elem);
		  if ($xml->SearchedNodeLink != null && strlen($elem) != 0)
		  {
			  $xml->AttribFromSNL("", $vis);
			  if ($onlyActive)
			  {
				  if ($vis['active']== "true")
				  {
					  $info[] = $vis;
				  }
			  }
			  else
			  {
				  $info[] = $vis;
			  }
			  unset($vis);
		  }
	  }
	  $xml->Destroy();
	  return $info;
	}
	
	/*
	* Создает массив значений Select для передачи как json
	* $NAV - набор значений
	*/
	function makeSelectObject($NAV, $keys = Array("text"=>"title", "value"=>"url"))
	{
	  $forSelectReturn = makeReqObject("select", "none");
	  $index = count($forSelectReturn)-1;
	  foreach ($NAV as $elem)
	  {
	    if (strlen($elem[$keys['text']]) != 0)
	    {
	      $forSelectReturn[$index]["value"][] = array("disabled" => "", "selected" => "", "text"=>$elem[$keys['text']], "value"=>$elem[$keys['value']]);
	    }
	  }
	  return $forSelectReturn;
	}
	
	/*
	* Возвращает значения для селекта игр
	*/
	function getGamesSelect($fileName, $id)
	{
	  header('Content-type: text/json');
	  $select = makeSelectObject(getGames($fileName));
	  $select[0]['id'] = $id;
	  return json_encode($select);
	}
	
	/* создает массив для передачи значений в json или добавляет к имеющемуся новую запись об объекте
	*  $objectType - тип объекта для которого задаются свойства
	*  $objectId - Id объекта для поиска его на странице
	*  $itemIndex - номер/текстовая метка в массиве объектов для создаваемого объекта
	*  $addTo - массив к которому необходимо добавить содаваемый объект
	*/
	function makeReqObject($objectType, $objectId, $itemIndex = "auto", $addTo = array())
	{
	  if ($itemIndex == "auto")
	  {
	    $newObjectIndex = count($addTo);
	  }
	  else
	  {
	    $newObjectIndex = $itemIndex;
	  }
	  $object = array("type" => $objectType, "id" => $objectId, "value" => array());
	  $addTo[$newObjectIndex] = $object;
	  return $addTo;
	}
	
	/*
	* Cоздает объект с данными для таблицы игр
	* $fileName - имя xml-файла источника данных
	*/
	function makeGamesTable($fileName)
	{
	  $games = getGames($fileName, false);
	  $forTableReturn = makeReqObject("table","gamesList");
	  $index = count($forTableReturn)-1;
	  for($i = 0; $i < count($games); ++$i)
	  {
	    $action = array('local'=> true, 'fileName'=>$fileName, 'object'=>"game", 'attribName'=>"active", 'valueIfTrue'=>"true", 'valueIfFalse'=>"false", 'currentState'=>'', 'searchByAttr'=>'id', 'withValue'=>$games[$i]['id']);
	    $active = "<input type='checkbox' value='".$games[$i]['id']."' ".($games[$i]['active']=='true' ?'checked':'')." action='".json_encode($action)."' onClick='changeState(this)'>";
	    $userCount = getUserCoutFromGame($games[$i]['url']);
	    $forTableReturn[$index]['value'][] = array(
							"id"=> $games[$i]['id'], 
							"active" => $active, 
							"url" => $games[$i]['url'], 
							"title"=>$games[$i]['title'], 
							"userCount"=>$userCount);
	  }
	  header('Content-type: text/json');
	  return json_encode($forTableReturn);
	}
	
	/*
	* Создает набор данных для таблицы ведущих
	* $gameUrl - Url игры
	*/
	function makePresentersTable($gameUrl)
	{
	  $data = getAllPresenters($gameUrl);
	  $forReturn = makeReqObject("table", "presenterList");
	  $forReturn[0]['value'] = json_decode($data, true);
	  $forReturn[0]['count'] = count($forReturn[0]['value']);
	  for($i = 0;$i < count($forReturn[0]['value']); ++$i)
	  {
	      $action = array("local"=> false, "urlGame"=>$gameUrl, "object"=>"presenter", "attribName"=>"active", "valueIfTrue"=>"true", "valueIfFalse"=>"false", 'currentState'=>'', 'searchByAttr'=>'id', 'withValue'=>$forReturn[0]['value'][$i]['id']);
	      $forReturn[0]['value'][$i]['active'] = "<input type='checkbox' value='".$forReturn[0]['value'][$i]['id']."' ".($forReturn[0]['value'][$i]['active']=='true' ?'checked':'')." action='".json_encode($action)."' onClick='changeState(this)'>"; 
	  }
	  header('Content-type: text/json');
	  return json_encode($forReturn);
	}
	
	/*
	*
	*/
	function makeGamersTable($gameUrl)
	{
	  $attribs =array("id","FIO","active","email","skype","capColor");
	  $userInfo = json_decode(sendRequest($gameUrl.'/operation.php?operId=getGamers&data='.json_encode($attribs), true), true);
	  $forReturn = makeReqObject("table", "gamersList");
	  $index = count($forReturn) - 1;
	  $i=0;
	  foreach($userInfo as $user)
	  {
	    foreach ($attribs as $attr)
	    {
	      $forReturn[$index]['value'][$i][$attr] = $user[$attr];
	    }
	    $action = array('local'=>false, 'urlGame'=>$gameUrl, 'fileName'=>userData, 'object'=>'user', 'attribName'=>'active', 'valueIfTrue'=>'1', 'valueIfFalse'=>'0', 'currentState'=>'', 'searchByAttr'=>'id', 'withValue'=>$user['id']);
	    $forReturn[$index]['value'][$i]['active'] = "<input type='checkbox' value='".$user['id']."' ".($user['active']=='1' ?'checked':'')." action='".json_encode($action)."' onClick='changeState(this)'>";
	    ++$i;
	  }
	  return json_encode($forReturn);
	}
	
	/*
	* Возвращает набор для Select`a цветов фишек (свободных)
	* $gameUrl - Url игры
	* $freeOnly - признак занятости
	*/
	function getCapColorSelect($gameUrl, $id, $freeOnly = true)
	{
	  $cap = json_decode(sendRequest($gameUrl."/operation.php?operId=getCaps&onlyFree=".$freeOnly, true, ""), true);
	  $select = makeSelectObject($cap, array("text"=>"color", "value"=>"name"));
	  $select[0]["id"] = $id;
	  return json_encode($select);
	}
	
	/*
	* Возвращает всех ведущих как json-строку
	* $gameUrl - URL игры
	*/
	function getAllPresenters($gameUrl)
	{
	  if (checkGame($gameUrl))
	  {
	    return get_content($gameUrl."/operation.php?operId=getAllPresenters");
	  }
	}
	
	/*
	* Возвращает инф-ию о игроках
	* $gameUrl - url-игры
	* $returnAll - признак возврата только количества/всех данных
	*/
	function getUserCoutFromGame($gameUrl, $returnAll = false)
	{
	  if (get_content($gameUrl."/operation.php?operId=testConnection&url=".$gameUrl))
	  {
	    $data = get_content($gameUrl."/operation.php?operId=getGamers");
	    $data = @json_decode($data);
	    if ($data != null)
	    {
	      if ($returnAll)
	      {
		return $data;
	      }
	      else
	      {
		return count($data);
	      }
	    }
	    else
	    {
	      return "Недоступно";
	    }
	  }
	  else
	  {
	    return "Недоступно";
	  }
	}
	
	/*
	* изменение атрибута для локального объекта
	* $data - значения для изменяемого объекта
	*/
	function localObject($data)
	{
	  if (file_exists($data['fileName']))
	  {
	    $xml = new ParseXML($data['fileName'], true);
	    $attribValues = array($data['attribName']=>$data['currentState']?$data['valueIfTrue']:$data['valueIfFalse']);
	    $xml->SearchNode($xml->RootNode, $data['object'], $data['searchByAttr'], $data['withValue']);
	    if ($xml->SearchedNodeLink != null)
	    {
	      $xml->ModifyElement($data['object'], $attribValues, $xml->SearchedNodeLink);
	      $xml->Destroy();
	      return "OK";
	    }
	    else
	    {
	      header('HTTP/1.0 404 not found');
	      return "Не удалось обновить состояние объекта";
	    }
	  }
	  else
	  {
	    header('HTTP/1.0 404 not found');
	    return "Не удалось обновить состояние объекта";
	  }
	}
	
	/*
	* Обновление состояния удаленного объекта
	* $data - значения для изменеия объекта
	*/
	function remoteObject($data)
	{
	  global $filesAttribs;
	  if (checkGame($data['urlGame']))
	  {
	    $url = $data['urlGame'];
	    $data = makeDataArray(
				    $data, 
				    $filesAttribs[$data['object']], 
				    Array(
					    $data['attribName']=>$data['currentState']?$data['valueIfTrue']:$data['valueIfFalse'], 
					    "object"=>$data['object'], 
					    "unicValue"=>$data['withValue']
					  )
				  );
	    return sendRequest($url."/operation.php?operId=updateObject&data=".urlencode(json_encode($data)), false, "Не удалось обновить состояние объекта");
	  }
	}
	
	/*
	* Обновляет значения объекта, берет значения из $postData
	* $postData - массив значений для изменеия (json)
	*/
	function updateValueOfObject($postData)
	{
	  $data = @json_decode(str_replace('\\', '', $postData), true)?json_decode(str_replace('\\', '', $postData), true):$postData;
	  if ($data['local'])
	  {
	    return localObject($data);
	  }
	  else
	  {
	    return remoteObject($data);
	  }
	}
	
	function makeDataArray ($data, $attribList, $result = Array())
	{
	  foreach($attribList as $key=>$value)
	  {
	    if (strlen($data[$key])!=0)
	    {
	      $result[$key] = $data[$key];
	    }
	    $result['node'] = $attribList['node'];
	    $result['unic'] = $attribList['unic'];
	  }
	  return $result;
	}
	
	function getIniValues($fileName)
	{
	  return new TIniFileEx($fileName);
	}
	
	function deleteElem($postData)
	{
	  if ($postData['local'] == true)
	  {
	    $data = makeGoodUrlParm($postData['data']);
	    $xml = new ParseXML($data['fileName'], true);
	    $xml->SearchNode($xml->RootNode, $data['object'], $data['unic'], $data['value']);
	    if ($xml->SearchedNodeLink != null)
	    {
		$xml->ModifyElement($data['object'], array("action"=>"del"), $xml->SearchedNodeLink);
		$xml->Destroy();
		return "OK";
	    }
	    else
	    {
		header('HTTP/1.1 500 Internal Server Error');
		return "NO";
	    }
	   }
	}
	
	/*
	* Делает из кривой json строки нормальный массив
	* $data - кривая строка json
	*/
	function makeGoodUrlParm($data)
	{
	  if (is_array($data))
	  {
	    return $data;
	  }
	  $data = str_replace('\\', '', $data);
	  if (strpos($data, "u0") >= 0)
	  {
	    $data = str_replace("u0", "\\u0", $data);
	  }
	  $data = @json_decode($data, true)?json_decode($data, true):$data;
	  return $data;
	}
	
	/*
	* Приводит url к виду содержещему только папку
	* $url - полный url или не полный
	*/
	function makeUrlDir($url)
	{
		$converted = $url;
	    $segments = explode("/", $url);
	    $i = 0;
	    if (strpos($segments[0],":") < 0)
	    {
		$converted = 'http://';
	    }
	    else
	    {
		$converted = $segments[0]."//";
		$i = 2;
	    }
		$converted =$converted.$segments[$i]."/";
		$i++;
	    for ($i; $i < count($segments); $i++)
	    {
	      $temp = explode("?", $segments[$i]); 
	      if (count($temp) > 1)
	      {
		  return $converted;
	      }
	      $temp = explode(".", $segments[$i]);
	      if (count($temp) > 1)
	      {
		  return $converted;
	      }
	      $converted = $converted.$segments[$i]."/";
	    }
	   return $converted;
	
	}
	
	/*
	* Попытка скопировать игру
	*
	*/
	function trycopy($postData, $test = true)
	{
		if (!checkGame($postData['targetUrl']))
		{
			$filePath = makeFilePath($postData);
			if (file_exists($filePath))
            {
                return json_encode(Array("test"=>false, "status"=>"Директория уже существует. Введите другой адрес игры", "color"=>"red"));
            }
            if (@mkdir($filePath, 0777, true))
			{
				if (!$test)
				{
					return $filePath;
				}
				else
				{
					//rmdir($filePath);
                    if (!unpackGameTo($filePath))
                    {
                        return json_encode(Array("test"=>false, "status"=>"Ошибка при распаковке архива", "color"=>"red"));
                    }
                    else
                    {
                        return json_encode(Array("status"=>"Игра скопирована.", "color"=>"green"));
                    }
                         
				}
			}
			else
			{
				if ($test)
				{
					return json_encode(Array("test"=>false));
				}
				else
				{
					return null;
				}
			}
		}
		else
		{
			return json_encode(Array("status"=>"Данный адрес уже используется игрой", "color"=>"red"));
		}
		
	}
	
	/*
		Обновление игры из архива
	*/
	function updateGame($postData){
		$data = makeGoodUrlParm($postData['data']);
	    $xml = new ParseXML($data['fileName']);
		$xml->SearchNode($xml->RootNode, $data['object'], $data['unic'], $data['value']);
		if ($xml->SearchedNodeLink != null)
	    {
			$xml->AttribFromSNL("", $vis);
			$filePath = makeFilePath(Array("targetUrl"=>$vis['url']));
			if (file_exists($filePath."/index.php")){
				makeBackUp($filePath);
				require_once("pclzip.lib.inc");
				$zip = new PclZip(baseGameFolder);
				$list = $zip->extract(PCLZIP_OPT_PATH, $filePath, PCLZIP_OPT_REPLACE_NEWER);
				if ($list != 0){
					foreach (glob($filePath."/bak/*") as $file){
						copy($file, $filePath."/xml/".basename($file));
						unlink($file);
					}
					rmdir($filePath."/bak");
					return json_encode(Array("status"=>"Ok"));
				} else {
					rmdir($filePath."/bak");
					header('HTTP/1.1 500 Internal Server Error');
					return json_encode(Array("status"=>"Copy error", "text"=>"Can`t copy to ".$vis['url']." (".$filePath.")"));
				}
			} else {
				header('HTTP/1.1 500 Internal Server Error');
				return json_encode(Array("status"=>"Copy error", "text"=>"Domain wrong for ".$vis['url']." (".$filePath.")"));
			}
		} else {
			header('HTTP/1.1 500 Internal Server Error');
			return json_encode(Array("status"=>"Update error", "Search_for"=>"object - ".$data['object']."; unic - ".$data['unic']."; value - ".$data['value']));
		}
	}
	
	function makeBackUp($path){
		$copyFilesMask = $path."/xml/*";
		$tempFilesMask = $path."/temp/*";
		foreach (glob($copyFilesMask) as $file){
			if (!file_exists($path."/bak")){
				mkdir($path."/bak");
			}
			copy($file, $path."/bak/".basename($file));
		}
		removeFiles(glob($path."/*"), array("bak"));
	}
	
	function removeFiles($files, $undeleted = array()){
		foreach ($files as $file){
			if (is_dir($file)){
				if (!in_array(dirname($file), $undeleted)){
					rmdir($file);
				}
			} else {
				if (!in_array(basename($file), $undeleted)){
					unlink($file);
				}
			}
		}
	}
	
	/*
	* Делает из URL-адреса файловый путь на сервере
	*/
	function makeFilePath($postData)
	{
	  $ini = new TIniFileEx(iniFile);
	  $adminUrl = $ini->read('setting', 'adminUrl', null);
	  if ($adminUrl == null)
	  {
	    return 'URL-адрес страницы администрирования не установлен. Проверьте его в настройках.';
	  }
	  $slash = getSlash();
	  $targetUrl = makeUrlDir($postData['targetUrl']);
	  $absPath = explode($slash, rootSite);
	  $forCopyPath = "";
	  for($i = 0; $i < count($absPath) - 1; $i++)
	  {
	    $forCopyPath = $forCopyPath.$slash.$absPath[$i];
	  }
	  $arrAdminUrl = explode("/",$adminUrl);
	  $arrTargetUrl = explode("/",$targetUrl);
	  for($i = 0; $i < count($arrTargetUrl); $i++)
	  {
		if ($arrTargetUrl[$i] != $arrAdminUrl[$i])
		{
			$forCopyPath = $forCopyPath.$slash.$arrTargetUrl[$i];
		}
	  }
	  if (strpos($forCopyPath, ":") == 2)
	  {
		$forCopyPath = str_replace(substr($forCopyPath, 0, 3), substr($forCopyPath, 1, 2), $forCopyPath);
	  }
	  return $forCopyPath;
	}
	
	/*
	* Из-за разности путей в ОС определяет разделитель  путях
	*/
	function getSlash()
	{
		if (strpos(rootSite, "/") >= 0)
		{
			return "/";
		}
		else
		{
			return "\\";
		}
	}
    /*
    *  Распаковка архива игры в новую папку
    */
    function unpackGameTo($path)
    {
		require_once("pclzip.lib.inc");
        $zip = new PclZip(baseGameFolder);
        $list = $zip->extract(PCLZIP_OPT_PATH, $path);
        if ($list != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    function get_content($url, $type){
    	require_once ('getContentClass.php');
    	global $get_content_configs;
    	$obj = new contentReturnerProcessor($get_content_configs, $type);
    	return $obj->get_content($url);
    }
    
	/*
	Копирование папок a la xcopy 
	(с перезаписью более старых файлов) 
	*/

	function copy_folder($d1, $d2, $upd = true, $force = true) {
	    if ( is_dir( $d1 ) ) {
		$d2 = mkdir_safe( $d2, $force );
		if (!$d2) {fs_log("!!fail $d2"); return;}
		$d = dir( $d1 );
		while ( false !== ( $entry = $d->read() ) ) {
		    if ( $entry != '.' && $entry != '..' ) 
			copy_folder( "$d1/$entry", "$d2/$entry", $upd, $force );
		}
		$d->close();
	    }
	    else {
		$ok = copy_safe( $d1, $d2, $upd );
		$ok = ($ok) ? "ok-- " : " -- ";
		fs_log(rootSite."/".logFName,"{$ok}$d1"); 
	    }
	} //function copy_folder

	function mkdir_safe( $dir, $force ) {
	    if (file_exists($dir)) {
		if (is_dir($dir)) return $dir;
		else if (!$force) return false;
		unlink($dir);
	    }
	    return (mkdir($dir, 0777, true)) ? $dir : false;
	} //function mkdir_safe

	function copy_safe ($f1, $f2, $upd) {
	    $time1 = filemtime($f1);
	    if (file_exists($f2)) {
		$time2 = filemtime($f2);
		if ($time2 >= $time1 && $upd) return false;
	    }
	    $ok = copy($f1, $f2);
	    if ($ok) touch($f2, $time1);
	    return $ok;
	} //function copy_safe 

	function fs_log($fileName, $str) {
	    $log = fopen($fileName, "a");
	    $time = date("Y-m-d H:i:s");
	    fwrite($log, "$str ($time)\n");
	    fclose($log);
	}

?>