<?
	function makeHeader($AccessControl = "*" , $ContentType = "text/json")
	{
	  header('Access-Control-Allow-Origin: '.$AccessControl);
	  header('Content-type: '.$ContentType);
	}
	
	function getHashGameFolder($url)
	{
	  $fromGet = md5(str_replace("/","", $url));
	  $fromHere = md5(str_replace("/","","http://".$_SERVER['SERVER_NAME'].str_replace("\\","",dirname($_SERVER['PHP_SELF']))));
	  if ($fromGet == $fromHere)
	  {
	    return json_encode(array(0 => "Ok"));
	  }
	  else
	  {
	    return json_encode(array(0 => "error"));
	  }
	}
	//Функция получения значений всех данных из файла
	function getAllInfoFromFile($fileName, $element, $unicField, $attribExpr = null, $attribValue)
	{
		new Parse(dataSourceType, $fileName, $xml);
		$xml->GetNodesAttribsValuesByName($xml->RootNode, $element, $unicField);
		$NAV = $xml->nodesAttribValue;
		$xml->Destroy();
		$AllInfo = array();
		new Parse(dataSourceType, $fileName, $xml);
		foreach ($NAV as $elem)
		{
			$xml->SearchNode($xml->RootNode, $element, $unicField, $elem);
			if ($xml->SearchedNodeLink != null && strlen($elem) != 0)
			{
				$xml->AttribFromSNL("", $vis);
				if ($attribExpr != null && $vis[$attribExpr] == $attribValue)
				{
					$AllInfo[] = $vis;
				}
				else if ($attribExpr == null)
				{
					$AllInfo[] = $vis;
				}
				unset($vis);
			}
		}
		$xml->Destroy();
		return $AllInfo;
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
	* создает строку json для построения отображаемых обектов на странице (для ведущих)
	* $fileName - имя xml-файла
	* $onlyActive - только активные/все ведущие
	* $genObjectType - тип создаваемого объекта
	* $genObjectId - id элемента на странице
	*/
	function getPresenters($fileName, $onlyActive, $genObjectType, $genObjectId = null)
	{
		if ($genObjectId != null)
		{
		    $NAV = getAllInfoFromFile($fileName, "presenter", "id", "active", $onlyActive);
		    $forReturn = makeReqObject($genObjectType, $genObjectId, "auto");
		    $index = count($forReturn) - 1;
		    if ($genObjectType == "select")
		    {
			    foreach ($NAV as $elem)
			    {
				    $forReturn[$index]["value"][] = array("disabled" => "", "selected" => "", "text"=>$elem['fio'], "value"=>$elem['id']);
			    }
		    }
		}
		else
		{
		    $forReturn = getAllInfoFromFile($fileName, "presenter", "id", null, $onlyActive);
		}
		return json_encode($forReturn);
	}
	
	/*
	* возвращает активных игроков
	* $fileName - xml-файл
	* $onlyActive - только активные/все игроки
	* $attribs - список возвращаемых атрибутов
	*/
	function getGamers($fileName, $attribs = array())
	{
	  $allInfo = getAllInfoAboutUsers();
	  if (count($attribs) > 0)
	  {
	    $result = array();
	    foreach($allInfo as $user)
	    {
	      $index = count($result) - 1;
	      foreach($attribs as $attribName)
	      {
		$result[$index][$attribName] = $user[$attribName];
	      }
	    }
	    return json_encode($result);
	  }
	  else
	  {
	    return json_encode($allInfo);
	  }
	}
	
	/*
	* Обновляет состояние объекта
	* $postData - данные для обновления (json)
	*/
	function updateObject($postData)
	{
	  $data = makeGoodUrlParm($postData);
	  if ($data['object'] == 'presenter')
	  {
	    $data['fileName'] = xmlForPresenters;
	    global $presenterAttribs;
	    $attribValues = makeAttribArray($data, $presenterAttribs);
	  }
	  else if ($data['object'] == 'user')
	  {
	    $data['fileName'] = xmlForUserData;
	    global $userAttribsMinimal;
	    $attribValues = makeAttribArray($data, $userAttribsMinimal);
	    if (strlen($attribValues['active']) != 0)
	    {
	      setDependCap($data['unicValue'], $attribValues['active'] == '1'? 'true':'false', strlen($data['action'])==0 ? 'update': $data['action']);
	    }
	  }
	  else
	  {
	    return "NO";
	  }
	  new Parse(dataSourceType, $data['fileName'], $xml, true);
	  if ($data['unic']=='new')
	  {
	    $attribValues['id'] = $data['id'];
	    $xml->SearchedNodeLink = 'new';
	  }
	  else
	  {
	    $xml->SearchNode($xml->RootNode, $data['object'], $data['unic'], $data['unicValue']);	    
	  }
	  $attribValues['action'] = $data['action'];
	  if ($xml->SearchedNodeLink != null || $xml->SearchedNodeLink == 'new')
	  {
	    $xml->ModifyElement($data['object'], $attribValues, $xml->SearchedNodeLink);
	    $xml->Destroy();
	    return "OK";
	  }
	  else
	  {
	    return "No";
	  }
	}
	
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
	
	function setDependCap($userId, $state, $action = 'update')
	{
	  if ($action == 'update')
	  {
	    new Parse(dataSourceType, xmlForFlash, $xml, true);
	    $xml->SearchNode($xml->RootNode, 'cap', 'idUser', $userId);
	    if ($xml->SearchedNodeLink != null)
	    {
	      $xml->ModifyElement("cap", array("visible"=>$state), $xml->SearchedNodeLink);
	    }
	    $xml->Destroy();
	  }
	  else if ($action == 'add')
	  {
	    new Parse(dataSourceType, xmlForFlash, $xml, true);
	    $xml->SearchNode($xml->RootNode, 'cap', 'idUser', $userId);
	    if ($xml->SearchedNodeLink != null)
	    {
	      $xml->ModifyElement("cap", array("visible"=>$state), $xml->SearchedNodeLink);
	    }
	    $xml->Destroy();
	  }
	}
	
	function makeAttribArray($data, $attribsArray)
	{
	  $retArray = Array();
	  foreach($attribsArray as $key=>$value)
	  {
	    if (strlen($value) == 0)
	    {
	      if (strlen($data[$key]) != 0)
	      {
		$retArray[$key] = $data[$key];
	      }
	    }
	  }
	  return $retArray;
	}
	
	function getCapColor($fileName, $onlyFree = 'true')
	{
	  new Parse(dataSourceType, xmlForFlash, $xml);
	  $xml->GetNodesAttribsValuesByName($xml->RootNode, "cap", "name");
	  $NAV = $xml->nodesAttribValue;
	  $infoAboutCards = Array();
	  foreach ($NAV as $elem)
	  {
		$xml->SearchNode($xml->RootNode, "cap", "name", $elem);
		if ($xml->SearchedNodeLink != null && strlen($elem) != 0)
		{
			$xml->AttribFromSNL("", $vis);
			$infoAboutCards[] = $vis['visible'] != $onlyFree ? $vis : "";
			unset($vis);
		}
	  }
	  $xml->Destroy();
	  return json_encode($infoAboutCards);
	}
	
	/*
	* Авторизация чере url
	* $userId - внутренний идентификатор из файла ведущих
	* $password - md5 пароля
	*/
	function remoteAuth($userId, $password)
	{
	  return json_encode(checkPresenterActive(Array("userId"=>$userId, "password"=>$password)));
	}
	
	/*
	* Отправка сообщения
	* $postData - принянтые данные 
	*/
	function sendMail($postData)
	{
		global $presenterAttribs;
		global $mailParams;
		global $messagePresTemplate;
		global $messagePresAttrib;
		$data = makeGoodUrlParm($postData);
		new Parse(dataSourceType, xmlForPresenters, $xml);
		$xml->SearchNode($xml->RootNode, $presenterAttribs['node'], $presenterAttribs['unic'], $data['objectId']);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->AttribFromSNL("", $vis);
			$url = $data['assignTo'].'operation.php?operId=remoteEnter&password='.$vis['password'].'&userId='.$vis[$presenterAttribs['unic']];
			$mess = getMessageFromTemplate($messagePresTemplate, $messagePresAttrib, Array("Письмо не требует ответа", $vis['fio'], $url, $data['gameName']));
			if (!mail($vis['email'], $mailParams['subject'], $mess, "Content-type: text/html; charset=utf-8 \r\nFrom: ".$mailParams['from']))
			{
				header('HTTP/1.1 500 Internal Server Error');
				return "NO";
			}
            else
            {
                return "OK";
            }
		}
		else
		{
			header('HTTP/1.1 500 Internal Server Error');
			return "NO";
		}
	}
	
	function getMessageFromTemplate($tpl, $attrib, $value)
	{
		return str_replace($attrib, $value, $tpl);
	}
?>