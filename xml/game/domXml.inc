<?php
    class ParseXML
    {
        var $Nfile;							//путь к файлу xml
	var $EFile;							//файл для экспорта
	var $linkToXml;						//ссылка на открытый xml-файл
	var $RootNode;						//ссылка на корень xml
	var $SearchedNodeLink;				//поле содержащее ссылку на узел, результат SearchNode
	var $FLockName;						//имя файла блокировки
	var $FileIsLocked = false;			//флаг блокировки файла
	function ParseXML($file_name, $lockFile = false)
        {
            $this->Nfile = $file_name;
			$this->linkToXml = new DOMDocument();
			$this->FLockName = $file_name."_".md5(date("dMMY His"));
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
				while(!file_exists($file_name) || $i <= 3)
				{
					$sum +=$i++;
					set_time_limit(30);
					sleep($sum);
                    if ($i == 3) 
                    {
                        set_time_limit(30);   
                        //$i = 0;
						//$sum = 0;
						//$this->repairFiles($file_name);
                    }
				}
				set_time_limit(60);
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
	
	function repairFiles($fileName){
		if (!$fileName) return;
		$mask = "*".$fileName;
		foreach (glob($mask) as $file){
			if (strlen($file) > strlen($fileName)){
				rename($file, $fileName);
			}
		}
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
    }
?>