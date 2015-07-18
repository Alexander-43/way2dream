<?php
	
	$dataSources = array(
							"mysql"=>"dbConnector",
							"xml"=>"ParseXML"
						);
						
    class ParseXML implements IDataSource
    {
        var $Nfile;							//путь к файлу xml
		var $EFile;							//файл для экспорта
		var $linkToXml;							//ссылка на открытый xml-файл
		var $RootNode;							//ссылка на корень xml
		var $SearchedNodeLink;						//поле содержащее ссылку на узел, результат SearchNode
		var $FLockName;							//имя файла блокировки
		var $FileIsLocked = false;					//флаг блокировки файла
		function ParseXML($file_name, $lockFile = false)
			{
				$this->Nfile = $file_name;
				$this->linkToXml = new DOMDocument();
				$this->FLockName = md5(date("dMMY His"));
				if (file_exists($this->Nfile))
				{
					if ($lockFile)
					{
						rename($file_name, $this->FLockName);
						$temp = $this->Nfile;
						$this->Nfile = $this->FLockName;
						$this->FLockName = $temp;
						$this->FileIsLocked = true;
					}
					try
					{
						$this->linkToXml->load($this->Nfile);
					}
					catch (Exception $e)
					{
						if ($lockFile) rename($this->Nfile, $this->FLockName);
						return;
					}
				}
				else
				{
					$i = 0;
					$sum=0; 
					while(!file_exists($file_name) && $i <= 5)
					{
						$sum +=$i++;
						sleep($sum);
						if ($i == 5) 
						{
							set_time_limit(30);   
							$i = 0;
							$sum = 0;
						}
					}
					set_time_limit(60);
					fclose($f);
					if ($lockFile)
					{
						rename($file_name, $this->FLockName);
						$temp = $this->Nfile;
						$this->Nfile = $this->FLockName;
						$this->FLockName = $temp;
					}
					try
					{
						$this->linkToXml->load($this->Nfile);
					}
					catch (Exception $e)
					{
						if ($lockFile) rename($this->Nfile, $this->FLockName);
						return;
					}
				}
				$this->RootNode = new DOMNode();
				$this->RootNode = $this->linkToXml->childNodes;
				$this->SearchedNodeLink = new DOMNode();
				$this->SearchedNodeLink = null;
			}
			
			
		/**************************************************************************************/
			//объод всего xml дерева и вывод всех его узлов и их атрибутов=значений
			function Next_element($root)
			{
			   $node = new DOMNode();
			   foreach ($root as $node)
			   {
					   print '<br>Найден Элемент - '.$node->nodeName;
					   if ($node->hasAttributes())
					   {  
							print '<br>Содержит атрибуты<br><ol>';
							foreach($node->attributes as $atr_name)
							{
								print '<li>'.$atr_name->name.'="'.$atr_name->value.'"</li>';     
							}
							print '</ol>';
					   }
					   print utf8_decode($node->nodeValue);
				}
				if ($node->hasChildNodes())
				{
					$this->Next_element($node->childNodes);
				}
			}
			
			
			/**************************************************************************************/
			//поиск узла по имени $tag, начиная с $root, содержащего атрибут с именем $name и значением $value
			//при успехе ссылка на найденный узел хранится в SearchedNodeLink объета XML
			function SearchNode($root, $tag, $name, $value)
			{
			   $node = new DOMNode();
			   foreach ($root as $node)
			   {
						//имя узла $node->nodeName;
						if ($node->nodeName == $tag)
						{
							if ($node->hasAttributes())
							{  
								foreach($node->attributes as $atr_name)
								{
									//просмотр атрибутов
									//имя - $atr_name->name 
									//значение - $atr_name->value
									if ($atr_name->name == $name && $atr_name->value==$value)
									{
										$this->SearchedNodeLink = $node;
										return true;
									}
								}
							}
							//значение текста узла $node->nodeValue
						}		
				}
				//если есть еще дочерние узлы то продолжаем поиск
				if ($node->hasChildNodes())
				{
					$this->SearchNode($node->childNodes, $tag, $name, $value);
				}
				if ($this->SearchedNodeLink == null) 
				{
					return false;
				}
			}
			
			
			/**************************************************************************************/
			//имя тега, имя атрибута для идентификации узла, значение атрибута для идетификации узла, 
			//имя искомого атрибута(при удаче содержит значение атрибута), ссылка на узел
			function getAttribValue($tag, $name, $value, &$SearchAtr, $root)
			{
			   $node = new DOMNode();
			   foreach ($root as $node)
			   {
						$flag = false;
						//имя узла $node->nodeName;
						if ($node->nodeName == $tag)
						{
							if ($node->hasAttributes())
							{
								$tempArr = Array();
								foreach($node->attributes as $atr_name)
								{
									//просмотр атрибутов
									//имя - $atr_name->name 
									//значение - $atr_name->value
									if ($atr_name->name == $name && $atr_name->value==$value)
									{
										$flag = true;
									}
									$tempArr[$atr_name->name]=$atr_name->value;
								}
							}
							//значение текста узла $node->nodeValue
						}
						if ($flag)
						{
							$SearchAtr = $tempArr[$SearchAtr];
							unset($tempArr);
							return true;
						}
				}
				//если есть еще дочерние узлы то продолжаем поиск
				if ($node->hasChildNodes())
				{
					$this->getAttribValue($tag, $name, $value, $SearchAtr, $node->childNodes);
				}
			}
			
					
			/**************************************************************************************/
			function SaveInFile ($FileName)
			{
				$this->linkToXml->Save($FileName);
				if ($this->FileIsLocked)
				{               
					$temp = $this->FLockName;
					$this->FLockName = $this->Nfile;
					$this->Nfile = $temp;
					rename($this->FLockName, $this->Nfile);
					$this->FileIsLocked = false;
				}            
			}
			
					
			/**************************************************************************************/
			function Destroy()
			{
				if ($this->FileIsLocked)
				{
					$temp = $this->FLockName;
					$this->FLockName = $this->Nfile;
					$this->Nfile = $temp;
					rename($this->FLockName, $this->Nfile);
					$this->FileIsLocked = false;
				}
				unset($this->Nfile);
				unset($this->linkToXml);
				unset($this->RootNode);
				unset($this->SearchedNodeLink);
				unset($this);
			}
			
					
			/**************************************************************************************/
			function Print_ALL_in_file()
			{
				$root = new DOMNode();
				$root = $this->linkToXml->childNodes;
				$this->Next_element($root);
			} 

			
			/**************************************************************************************/
			function AttribFromSNL($name = null, &$Atribs = array ())
			{
				$flag = false;
				if ($this->SearchedNodeLink != null)
				{
					foreach($this->SearchedNodeLink->attributes as $atr)
					{
						if ($atr->name == $name) $flag = true;
						$Atribs[$atr->name] = $atr->value;
					}
					if ($flag) 
					{
						return $Atribs[$name]; 
					}
					else 
					{
						return "{*absent*}";
					}
				}
			}
			
			/**************************************************************************************/
			var $nodesAttribValue = array();
			//получает все значения выбранного атрибута всех выбранных элементов
			function GetNodesAttribsValuesByName ($root, $nodeName, $attribName)
			{
				$node = new DOMNode();
			   foreach ($root as $node)
			   {
					if ($node->nodeName == $nodeName && $node->hasAttributes())
					{  
						foreach($node->attributes as $atr_name)
						{
							if ($atr_name->name == $attribName)
							{
								$this->nodesAttribValue[] = $atr_name->value;
							}
						}   
					}
				}
				if ($node->hasChildNodes())
				{
					$this->GetNodesAttribsValuesByName($node->childNodes, $nodeName, $attribName);
				}
			}
		/*
		*  Изменяет xml-элемент
		*  $elementName - имя элемента в xml-файле
		*  $attribList - массив атрибутов и их значений (name=>value)
		*  $linkToElement - ссылка на изменяемый элемент, если не указана, то будет создан новый узел
		*/
		function ModifyElement($elementName, $attribList, $linkToElement = "new")
		{
		  if ($linkToElement == "new")
		  {
			$node = $this->linkToXml->createElement($elementName);
			$this->SearchedNodeLink = $this->linkToXml->documentElement->appendChild($node);
		  }
		  else if ($attribList['action'] == "del")
		  {
			$linkToElement->parentNode->removeChild($linkToElement);
			$this->SaveInFile($this->Nfile);
			return true;
		  }
		  else
		  {
			$this->SearchedNodeLink = $linkToElement;
		  }
		  foreach($attribList as $name => $value)
		  {
			$this->SearchedNodeLink->setAttribute($name, $value);
		  }
		  $this->SaveInFile($this->Nfile);
		}
		
		function setAttribute($linkToXml, $data = array()){
			foreach($data as $name=>$value){
				$linkToXml->setAttribute($name, $value);
			}
		}
        
        public function getXmlFromCurrentObject(){
            print file_get_contents($this->FileIsLocked ? $this->FLockName : $this->Nfile);       
        }
    }
    
    class dbConnector implements IDataSource
    {
      private $host;
      private $user;
      private $password;
      private $dbName;
      private $mySqlIdentifer;
      private $isConnected = false;
      private $recId;
      private $tableName = null;
	  private $tableFields = Array();
	  private $lastSql = Array();
	  public $SearchedNodeLink = null;
      public function __construct($fileName, $lock = false){
		if (file_exists(mysqlFolder.'connect')){
		  include(mysqlFolder.'connect');
		  $this->host = host;
		  $this->user = user;
		  $this->password = password;
		  $this->dbName = dbName;
		  $this->mySqlIdentifer = mysql_connect($this->host, $this->user, $this->password);
		  if ($this->mySqlIdentifer > 0){
			$this->isConnected = mysql_select_db($this->dbName, $this->mySqlIdentifer);
		  }
		}
		if (!$this->isConnected){
		  return null;
		}else {
            mysql_query ("set_client='utf8'");
            mysql_query ("set character_set_results='utf8'");
            mysql_query ("set collation_connection='utf8_general_ci'");
            mysql_query ("SET NAMES utf8");
			if ($this->tableExists($fileName, $message)){
				return $this;
			} else {
				print $message;
				return null;
			}
		}
      }
		/**
        * Проверка существования таблицы
        * создание и заполнение default-значениями
        * если таблицы не существует
        * 
        * @param mixed $tableName
        *                   - имя таблицы
        * @param mixed $message
        *                   - сообщение об ошибке
        */
		public function tableExists($tableName, &$message = ""){
			$sql = "SHOW tables";
			$result = $this->makeArrayValues($this->execQuery($sql));
			$tName = md5(dirname(__FILE__))."_".str_replace('.', '_', basename($tableName));
			$this->pathHashFile(md5(dirname(__FILE__)));
			foreach($result as $name=>$value){
				if ( $tName == $value['Tables_in_'.$this->dbName] || strtolower($tName)== strtolower($value['Tables_in_'.$this->dbName])){
					$this->tableName($tName);
					return true;
				}
			}
			global $baseTables;
			if (strlen($baseTables[$tableName]['sql']) > 0){
				if($this->execQuery(str_replace('[*tableName*]', $tName, $baseTables[$tableName]['sql']))){
					$this->tableName($tName);
					if (strlen($baseTables[$tableName]['inserts']) > 0){ 
						if ($this->execQuery(str_replace('[*tableName*]', $tName, $baseTables[$tableName]['inserts']))){
							return true;
						} else{
							$message = "<i>Ошибка вставки данных в таблицу - ".$tableName."</i><br><b>Данные:</b><br>".$baseTables[$tableName]['inserts']."<br>".mysql_error();
							//$this->execQuery("DROP TABLE ".$tName);
							return false;
						}
					}
					return true; 
				} else {
					$message = "<i>Ошибка создания таблицы - ".$tableName.".<i><br><b>".mysql_error()."</b>";
					return false;
				}
			}
		}
		
		/**
		 * Создание файла с именем префикса таблиц в БД
		 * @param String $name
		 */
		private function pathHashFile($name){
			if (!file_exists($name)){
				$f = fopen($name, "w") or die("Can`t create file");
				fclose($f);
			}
		}
		
		//implemented
		public function SaveInFile ($FileName){
			//nothing
		}
		
		//implemented
		public function Destroy(){
			mysql_close($this->mySqlIdentifer);
		}
		
      /*
      * Ротация из query в объект массива
      */
      public function makeArrayValues($query){
		if (!$query) return Array("res"=>"null");
		//print $query;
		while($field=mysql_fetch_field($query)){
		  $names_fields[]=$field->name;
		}
		$values = Array();
		while ($row = mysql_fetch_array($query, MYSQL_NUM)) {
		  $line = Array();
		  for($i = 0; $i < count($names_fields); $i++)
		  {
			$line[$names_fields[$i]]=$row[$i];
		  }
		  $values[] = $line;
		}
		return $values;
      }
      /**
      * Возвращает список полей таблицы
      * 
      * @param mixed $tableName
      *                 - имя таблицы
      */
	  public function getTableFields($tableName){
		$sql = "describe ".$tableName;
		$result = $this->makeArrayValues($this->execQuery($sql));
		//print_r($result);
		for($i = 0;count($result) > $i;++$i){			
			$this->tableFields[] = $result[$i]['Field'];
		}
		return $this->tableFields;
	  }
	  /**
      * Устанавливает/возвращает имя таблицы с которой происходит работа
      * 
      * @param mixed $name
      *                 - set table name
      */
	  public function tableName($name = null){
		if ($name != null){
			$this->tableName = $name;
			$this->getTableFields($name);
		}else{
			return $this->tableName;
		}
	  }
	  //implemented
      public function SearchNode($root = 'implemented', $tag, $name, $value){
      	$condition = strlen($value) == 0 ? "(".$name."='".$value."' OR ".$name." is null)" : $name."='".$value."'";
		$sql = "SELECT * FROM ".$this->tableName." WHERE tag='".$tag."' AND ".$condition;
		$result = $this->makeArrayValues($this->execQuery($sql));
		if (count($result) > 0){
			$this->recId = $result[0]['id'];
		} else {
			$this->SearchedNodeLink = null;
			return null;
		}
		$this->SearchedNodeLink = true;
		return true;
      }
      /**
      * Выплняет запрос
      * 
      * @param mixed $sql
      *                 - sql-запрос
      * @return resource
      *                 - массив значений
      */
      public function execQuery($sql){
		//print "<br>LastQuery:".$sql."<br>";
		$this->addSql($sql);
		if (logging){
			$this->log($sql);
		}
		return mysql_query($sql, $this->mySqlIdentifer);
      }
	  
	  //имя тега, имя атрибута для идентификации узла, значение атрибута для идетификации узла, 
	  //имя искомого атрибута(при удаче содержит значение атрибута), ссылка на узел
	  //implemented
	  public function getAttribValue($tag, $name, $value, &$SearchAtr, $root){
		$sql = "SELECT ".$SearchAtr." FROM ".$this->tableName." WHERE tag='".$tag."' AND ".$name."='".$value."'".($this->recId!=null ?" AND id='".$this->recId."'":"");
		$result = $this->makeArrayValues($this->execQuery($sql));
		if (count($result) > 0){
			$SearchAtr = $result[0][$SearchAtr];
			return true;
		}else{
			return false;
		}
	  }
	  
	  //implemented
	  public function AttribFromSNL($name = null, &$Atribs = array ())
		{
			$sql = "SELECT * from ".$this->tableName." where id='".$this->recId."'";
			$result = $this->makeArrayValues($this->execQuery($sql));
			$flag = false;
			if (count($result) > 0)
			{
				foreach($result[0] as $atrName=>$atrValue)
				{
					if ($atrName == $name) $flag = true;
					$Atribs[$atrName] = $atrValue;
				}
				if ($flag) 
				{
					return $Atribs[$name]; 
				}
				else 
				{
					return "{*absent*}";
				}
			} else {
				return "{*absent*}";
			}
		}
		
		var $nodesAttribValue = array();
		//получает все значения выбранного атрибута всех выбранных элементов
		public function GetNodesAttribsValuesByName ($root = 'implemented' ,$nodeName, $attribName)
		{
			$sql = "SELECT ".$attribName." FROM ".$this->tableName." where tag='".$nodeName."'";
			$result = $this->makeArrayValues($this->execQuery($sql));
			if (count($result) > 0){
                foreach ($result as $n=>$v)
                {   
                   foreach ($result[$n] as $name=>$value)
			       {
					    $this->nodesAttribValue[] = $value;
				    }
                }
				return $this->nodesAttribValue;
			}
		}
		/**
		* Проверяет наличие полей в таблице из $tested
		*/
		public function checkTableFields($tested){
			$fieldToAdd="";
			foreach ($tested as $name=>$value){
				$flag = false;
				foreach ($this->tableFields as $field){
					if (strlen($name) == 0 || $name == null){
						$flag == true;
						break;
					}
					if ($name == $field){
						$flag = true;
					}
				}
				if (!$flag){
					$fieldToAdd = strlen($fieldToAdd) == 0 ? $name." varchar(250)" : $fieldToAdd.", ".$name." varchar(250)";
				}
			}
			if (strlen($fieldToAdd) != 0){
				$sql = "ALTER TABLE ".$this->tableName." ADD(".$fieldToAdd.")";
				return $this->execQuery($sql);
			}
		}
        //implemented
		public function ModifyElement($elementName, $attribList, $linkToElement = "new")
		{
		  $tempId = null;
		  if ($linkToElement === "new")
		  {
			$tempId = md5(mt_rand());
			$sql = "INSERT INTO ".$this->tableName."(`tag`, `tempId`) VALUES('".$elementName."', '".$tempId."')";
			$result = $this->execQuery($sql);
		  }
		  else if ($attribList['action'] == "del")
		  {
			$sql = "DELETE FROM ".$this->tableName." WHERE id='".$this->recId."'";
			$result = $this->execQuery($sql);
			return true;
		  }
		  $this->checkTableFields($attribList);
		  $data = null;
		  foreach($attribList as $name => $value)
		  {
			$data = strlen($data) != 0 ? $data.", ".$name."='".$value."'" : $name."='".$value."'";
		  }
		  $sql = "UPDATE ".$this->tableName." SET ".$data;
		  if ($data != null){
			if($tempId != null){
				$sql = $sql." WHERE tempId='".$tempId."'";
			} else {
				$sql = $sql." WHERE id='".$this->recId."'";
			}
			$result = $this->execQuery($sql);
		  }
		}
		//implemented
		public function setAttribute($linkToXml, $data = array()){
			$this->ModifyElement(null, $data, null);
		}
        
        /**
        * Генерация xml из таблицы MySql
        * 
        */
        public function getXmlFromCurrentObject(){
            $sql = "SELECT * FROM ".$this->tableName();
            $data = $this->makeArrayValues($this->execQuery($sql));
            $xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root>";
            foreach($data as $row){
                $xml.="<".$row['tag']." ";
                foreach ($row as $name=>$value){
                    $xml.=$name."=\"".$value."\" ";        
                }
                $xml.="/>";
            }
            $xml.="</root>";
            return $xml;
        }
		/**
        * Логирует(в памяти) выполняемые sql-запросы
        * 
        * @param mixed $sql - запрос
        */
		public function addSql($sql){
			$key = mt_rand();
			$this->lastSql[$key]['date'] = date("d.m.Y H:i:s");
			$this->lastSql[$key]['sql'] = $sql;
		}
		/**
        * Выводит список запросов выполненных 
        * с момента создания объекта до его уничтожения
        * 
        */
		public function printLastSql(){
			$str = "<table border='1'><tr><td align='center'>Время/Дата</td><td align='center'>SQL</td></tr>";
			foreach ($this->lastSql as $data){
				$str.="<tr><td>".$data['date']."</td><td>".$data['sql']."</td></tr>";
			}
			$str .= "</table>";
			print $str;
		}
		
		private function log($text){
			if (!logTable){
				return;
			}
			$sql = "SHOW tables";
			$result = $this->makeArrayValues(mysql_query($sql, $this->mySqlIdentifer));
			$tName = logTable;
			$flag = false;
			foreach($result as $name=>$value){
				if ( $tName == $value['Tables_in_'.$this->dbName] || strtolower($tName) == strtolower($value['Tables_in_'.$this->dbName])){
					$flag = true;
				}
			};
			global $baseTables;
			if (!$flag){
				mysql_query($baseTables[logTable]['sql'], $this->mySqlIdentifer) or die (mysql_error($this->mySqlIdentifer));
			}
			$sql="select count(*) as count from `".logTable."`";
			$res = $this->makeArrayValues(mysql_query($sql, $this->mySqlIdentifer));
			if ($res[0]['count'] >= maxRows){
				mysql_query("TRUNCATE ".logTable, $this->mySqlIdentifer);
			}
			$sql="INSERT INTO `".logTable."` VALUES(null, null, '".mysql_real_escape_string($text)."')";
			mysql_query($sql, $this->mySqlIdentifer) or die (mysql_error($this->mySqlIdentifer));			
		}
    }
    /**
    * Утильный класс для создания объекта нужного в данного контексте класса
    */
	class Parse{
		public function Parse($objectName, $fileName, &$retObj, $lock = false){
            $objectName = AbstractDS::getDataSource($objectName);
            if (!empty($objectName)&&class_exists($objectName)){
                $retObj = new $objectName($fileName, $lock); 
			} else {
				return null;
			}
		}
	}
    /**
    * Интерфейс с набором обязательных для реализации методов 
    */
	interface IDataSource {
		public function SearchNode($root, $tag, $name, $value);
		public function getAttribValue($tag, $name, $value, &$SearchAtr, $root);
		public function SaveInFile ($FileName);
		public function Destroy();
		public function AttribFromSNL($name = null, &$Atribs = array ());
		public function GetNodesAttribsValuesByName ($root, $nodeName, $attribName);
		public function ModifyElement($elementName, $attribList, $linkToElement = "new");
		public function setAttribute($linkToXml, $data = array());
        public function getXmlFromCurrentObject();
	}
	/**
    * Абстрактный класс необходим для 
    * определения класса объекта в текущем контексте
    */
	abstract class AbstractDS implements IDataSource{
		/**
        * Поиск типа источника данных по его названию
        * 
        * @param mixed $dataSourceType
        *                   - тип источника данных
        * @return mixed
        *                   - класс типа источника данных
        */
        public static function getDataSource($dataSourceType){
            global $dataSources;
			if (!empty($dataSources[$dataSourceType]))
			{
				return $dataSources[$dataSourceType];
			} else {
				return null;
			}
		}
	}
	

?>