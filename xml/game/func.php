<?php
$Except = array();
$ErorrList = Array ("0" => "Выбранная вами фишка с цветом {*color*} уже занята другим игроком",
					"1" => "Неудалось обновить значения координат фишки с именем {*capName*}",
					"2" => "Файл {*absentFile*} не существует. Выберите другой файл.",
					"3" => "Ошибка копирования файла {*copyedFile*}",
					"4" => "Не удалось заменить {*FilesReplace*}",
					"97"=> "Файл данных игры успешно обновлен пустой копией",
					"98"=> "Файл данных игры удачно скопирован в архив",
					"99"=> "Данные игры обновлены, используемые фишки освобождены"
					);
								
function AddToErrorList($NumErr, $StrReplace, $MetaTag = null)
{
	$Except[] = $NumErr;
	if ($MetaTag != null)
	{
		$ErorrList[$NumErr] = str_replace($MetaTag, "\"".$StrReplace."\"", $ErorrList[$NumErr]);
	}
}

function getAllInfoAboutUser ($userId)
{
	$name = getUserFileName($userId);
	$xml = new ParseXML($name);
	$xml->SearchNode($xml->RootNode, "user", "id", $userId);
	if ($xml->SearchedNodeLink != null)
	{
		$attribs = array();
		$xml->AttribFromSNL("", $attribs);
	}
	$xml->Destroy();
	return $attribs;
}

//сохраняет регистрационные даные пользователя					
function SaveRegData($data)
{
	global $ErorrList;
	global $Except;
	$Attribs = array();
	$xml = new ParseXML(xmlForFlash, true);
	$xml->SearchNode($xml->RootNode, "cap", "name", $data["cap"]);
	if ($xml->SearchedNodeLink != null)
	{
		$AtrVal = $xml->AttribFromSNL("visible");
		if ($AtrVal != "{*absent*}" && $AtrVal != "true") 
		{
			$xml->SearchedNodeLink->setAttribute("visible", "true");
			$xml->SearchedNodeLink->setAttribute("idUser", $_SESSION['id']);
			$xml->AttribFromSNL("", $Attribs);
			$xml->SaveInFile($xml->Nfile);
			$xml->Destroy();
			$name = getUserFileName($_SESSION['id'], true);
			$xml = new ParseXML($name, true);
			$node = $xml->linkToXml->createElement("user");
			$xml->SearchedNodeLink = $xml->linkToXml->documentElement->appendChild($node);
			$xml->SearchedNodeLink->setAttribute("id", $data["id"]);
			$xml->SearchedNodeLink->setAttribute("FIO", $data["FIO"]);
			$xml->SearchedNodeLink->setAttribute("email", $data["email"]);
			$xml->SearchedNodeLink->setAttribute("skype", $data["skype"]);
			$xml->SearchedNodeLink->setAttribute("capColor", $Attribs["color"]);
			$xml->SearchedNodeLink->setAttribute("active", "1");
			$xml->SearchedNodeLink->setAttribute("date", date("d.m.Y H:i:s"));	
			$xml->SaveInFile($xml->Nfile);
			$xml->Destroy();
		}
		else
		{
			AddToErrorList(0, $xml->AttribFromSNL("color"), "{*color*}");
			$xml->Destroy();
		}
	}
}

//вывод собранных возникших ошибок
function PrintErorrs($Erorrs)
{
	global $ErorrList;
	$er = "";
	for ($i = 0; $i < count($Erorrs);++$i)
	{
		$er.=$i.". ".$ErorrList[$Erorrs[$i]]."\n";
	}
	return $er;
}

function ArchiveGameBase()
{

}

//Функция обновления координат фишек по имени, если ссылка на xml файл не передается, то
//xml объект создаётся и уничтожается в функции
function UpdateCapValues($CapName, $Xpos, $Ypos, $xml = null)
{
	$flag = false;
	if ($xml == null)
	{
		$xml = new ParseXML(xmlForFlash, true);
		$flag = true;
	}
	$xml->SearchNode($xml->RootNode, "cap", "name", $CapName);
	if ($xml->SearchedNodeLink != null)
	{
		$xml->SearchedNodeLink->setAttribute("posX", $Xpos);
		$xml->SearchedNodeLink->setAttribute("posY", $Ypos);
		$xml->SaveInFile($xml->Nfile);
	}
	else
	{
		AddToErrorList(1, $CapName, "{*capName*}");
	}
	if ($flag) $xml->Destroy();
}

//функция выводит select для выбора времени обновления и кнопку старт/стоп
function ShowRunStopObject($time, $state = 0)
{
	if ($time == "") $time=5;
	print "<span height='10' style='overflow:visible; margin:0 0 5px 0; position:relative;'><form name='timerObj' action='gamer.php' method='post'>Обновлять раз в <select name='timer'>";
			for ($i=5;$i<=20;$i+=2)
			{
				if ($i==$time) 
				{
					print "<option value=".$i." selected>".$i." сек."."</option>";
				}else
				{
					print "<option value=".$i.">".$i." сек."."</option>";
				}
			}
	print "</select> &nbsp";
	if ($state=="") $state = 1;
	if ($state == 1)
	{
		$alt="Запуск атоматического обновления страницы";
	}else
	{
		$alt="Остановить автоматическое обновление страницы";
	}
	print "<img name='run' id='".$state."' src='img/".$state.".gif' height='30' align='middle' onMouseDown='imgOver(this, 28);' onMouseUpt='imgOver(this, 30);' onClick='RunStop(this);' alt='".$alt."' style='cursor:pointer'>";
	print "<span id='hod' style='margin:0 0 0 10'></span>";
	print "<input id='state' name='state' type='hidden' value='".$state."'>";
	print "</form></span>";
}

//функция вывода блока информации о пользователе на странице наблюдения за игрой
function InfoAboutUser($arrayOfInfo)
{
	global $capColorReferences;
	$allInfo = getAllInfoAboutUser ($arrayOfInfo['id']);
	if (!$allInfo || ($allInfo && !array_key_exists("glob_inc", $allInfo))) $allInfo['glob_inc']=0;
	if (!$allInfo || ($allInfo && !array_key_exists("glob_sour", $allInfo))) $allInfo['glob_sour']=0;
	$colorText = $allInfo['capColor'];
	print "<table class='selCard' align='center' border='1' width='100%'>";
	print "<tr><td align='left' style='border-style:none'><b><i>".$allInfo['FIO']."</i></b></td>";
	print "<td align='right' width='100' style='border-style:none'><a href='editUserData.php?id=".$allInfo['id']."' target='top'><img src='img/info.jpg' align='middle' title='Редактировать информацию игры' width='50px'></a>";
	print "<img src='img/".$capColorReferences[$allInfo['capColor']]."' align='middle' title='".$colorText."'></td></tr>";
	if (!isset($allInfo['commonR']) || strLen($allInfo['commonR'])==0) $allInfo['commonR'] = 0;
	if (!isset($allInfo['pasIncomeBlueCircle']) || strLen($allInfo['pasIncomeBlueCircle'])==0) $allInfo['pasIncomeBlueCircle'] = 0;
	if (!isset($allInfo['pasIncomeGreenCircle']) || strLen($allInfo['pasIncomeGreenCircle'])==0) $allInfo['pasIncomeGreenCircle'] = 0;
		print "<tr><td colspan='2'>";
			print "<table width='100%' border='1' style='border:solid; border-color:black; border-collapse: collapse;'>";
				print "<tr align='center' style='border:solid;'><td style='border:solid; padding:5px;'><font size='-1'>Активный доход<br>(зеленый круг)</font></td><td style='padding:5px;'><font size='-1'>Пассивный доход<br>(все круги)</font></td></tr>";
				print "<tr align='center' style='border:solid;'><td style='border:solid; padding:10px;'>".$allInfo['activeIncomeGreenCircle']."</td><td style='padding:10px;'>".$allInfo['passIncomeAllCircle']."</td></tr>";
				print "<tr style='border:solid;'><td align='center' colspan='2'><font size='+2'>общий Ресурс: ".$allInfo['commonR']."</font></td></tr>";
			print "</table>";
		print "</td></tr>";
	print "<tr><td colspan='2' style='border-style:none'>".printPaySystem($allInfo, false)."</td></tr>";
	print "</table>";
}

//генерация кода доступа
function genHash($str)
{
	print (" Полученный код доступа - ".md5($str));
}

//выводит файлы архива игроков
function ShowFileInDir($DIR)
{
	$mask = $DIR."/*.xml";
	$s = array();
	foreach (glob($mask) as $fn)
	{
		$s[] = "<td align='center' style='border:solid; padding: 10 0 10 0;'><a href='".$fn."'>".basename($fn)." ( ".round(filesize($fn)/1024, 2)." Kb)</a></td>";
	}
	print "<table width='100%' style='border-collapse: collapse;'>";
	print "<tr><td colspan='".columnOfArchFile."' style='padding: 20 0 20 30'><input id='genHash' name='genHash' type='text' value=''> <input type='button' value='Сгенерировать код доступа' onClick=\"vote('operation.php?generate=true&str='+document.getElementById('genHash').value, 'hash')\"><div id='hash' style='display:inline'></div></td></tr>";
	print "<tr><td align='center' colspan='".columnOfArchFile."' style='padding: 20 0 20 0; border:solid'>Файлы архива</td></tr>";
	for ($i=0; $i <= count($s)-1;$i=$i+columnOfArchFile)
	{
		$t="";
		for ($j=0;$j<=columnOfArchFile-1;$j++)
		{
			$t = $t.$s[$i+$j];
		}
		print "<tr>".$t."</tr>";
	}
	print "</table>";
}

//делает доступными все фишки
function StartNewGame()
{
	$xml = new ParseXML(xmlForFlash, true);
	$xml->SearchNode($xml->RootNode, "card", "id", "card");
	$xml->SearchedNodeLink->setAttribute("userId", "");
	$xml->SearchedNodeLink->setAttribute("cardforView", "");
	$xml->SearchedNodeLink->setAttribute("cardSelected", "");
	$xml->SearchedNodeLink->setAttribute("isActive", "");
	$xml->SearchedNodeLink->setAttribute("id", "card");
	$xml->SearchNode($xml->RootNode, "cube", "id", "cube");
	$xml->SearchedNodeLink->setAttribute("userId", "");
	$xml->SearchedNodeLink->setAttribute("isActive", "");
	$xml->SearchedNodeLink->setAttribute("result", "");
	$xml->SearchedNodeLink->setAttribute("id", "cube");
	$xml->SearchNode($xml->RootNode, "cap", "visible", "true");
	$xml->AttribFromSNL("visible", $vis);
	while ($vis["visible"]=="true" && $xml->SearchedNodeLink != null)
	{
		print_r ($vis);
		$xml->SearchedNodeLink->setAttribute("visible", "false");
		$xml->SearchedNodeLink->setAttribute("posX", "-1");
		$xml->SearchedNodeLink->setAttribute("posY", "-1");
		$xml->SearchedNodeLink->setAttribute("idUser", "");
		$xml->SearchedNodeLink = null;
		$xml->SearchNode($xml->RootNode, "card", "userId", $vis["idUser"]);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->SearchedNodeLink->setAttribute("userId", "");
			$xml->SearchedNodeLink->setAttribute("cardforView", "");
			$xml->SearchedNodeLink->setAttribute("cardSelected", "");
			$xml->SearchedNodeLink->setAttribute("isActive", "");
			$xml->SearchedNodeLink = null;
		}
		unlink(getUserFileName($vis["idUser"]));
		$xml->SearchNode($xml->RootNode, "cap", "visible", "true");
		unset($vis);
		$xml->AttribFromSNL("visible", $vis);
	}
	$xml->SaveInFile($xml->Nfile);
	AddToErrorList(99, "");
	$xml->Destroy();
	//ArchXmlBase(xmlForUserData, maxBaseSize, folderBaseArchive);
}

//создает файл $fname с содержимым $body
function CreateFile($fname, $body = "")
{
	$f = fopen($file, "w");
	fputs($f, $body);
	fclose($f);
}

//проверяет размер бызы и перемещает в архив при достижении критического размера
function ArchXmlBase($file, $maxSize, $ArhFolder)
{
	if (file_exists($file) && round(filesize($file)/1024, 2)>$maxSize)
	{
		if (!file_exists(substr($file, 0, -4)))
		{
			CreateFile(substr($file, 0, -4), "<?xml version='1.0' encoding='UTF-8'?><?xml-stylesheet type='text/xsl' href='test.xsl'?><root></root>");
		}
		if (copy($file, $ArhFolder."/".date("d.m.Y").".xml"))
		{
			AddToErrorList(98, "");
			if (copy(substr($file, 0, -4), $file))
			{
				AddToErrorList(97, "");
			}else
			{
				AddToErrorList(4, "файл ".$file." на файл ".substr($file, 0, -4), "{*FilesReplace*}");
			}
		}else
		{
			AddToErrorList(3, $file, "{*copyedFile*}");
		}
	}else
	{
		AddToErrorList(2, $file, "{*absentFile*}");
	}
	PrintErorrs($Except);
}

//Функция получения значений всех данных пользователей
function getAllInfoAboutUsers()
{
	$xml = new ParseXML(xmlForFlash);
	$xml->GetNodesAttribsValuesByName($xml->RootNode, "cap", "idUser");
	$NAV = $xml->nodesAttribValue;
	$xml->Destroy();
	$AllInfoAboutUsers = array();
	
	foreach ($NAV as $elem)
	{
		$name = getUserFileName($elem);
		$xml = new ParseXML($name);
		$xml->SearchNode($xml->RootNode, "user", "id", $elem);
		if ($xml->SearchedNodeLink != null && strlen($elem) != 0)
		{
			$xml->AttribFromSNL("", $vis);
			$AllInfoAboutUsers[] = $vis;
			unset($vis);
		}
		unset($xml);
	}
	return $AllInfoAboutUsers;
}

function ShowSelectCard($userId, $cardType = null)
{
	global $cardsSettings;
	//disabled='disabled'
	$select = "<select align='right' id='card' ".$cardsSettings[0]['size']." ".$cardsSettings[0]['multi']." name='".$userId."' onChange='sendCardType(this)'>";
	for ($i=1;$i<=count($cardsSettings)-1; $i++)
	{
		$isSel = "";
		if ($cardsSettings[$i]['imgFile'] == $cardType)
		{
			$isSel = "selected";
		}
		$select .= "<option value='".$cardsSettings[$i]['imgFile']."' ".$isSel.">".$cardsSettings[$i]['name']."</option>";
	}
	$select .= "</select>";
	return $select;
}

//выводит поля для оплаты/получения в зависимости от игрок/ведущий
function printPaySystem($userInfo, $admin = false)
{
	$actionPay = " onMouseDown=\"this.src='img/payDown.gif'\" onMouseUp=\"this.src='img/pay.gif'\" ";
	$actionIncass = "onMouseDown=\"this.src='img/incassDown.gif'\" onMouseUp=\"this.src='img/incass.gif'\"";
	$str = "<table width='100%' border='0'>";
	$str = $str."<tr>";
		$str = $str."<td align='left'>Наличные деньги:</td><td align='left'><div id='d_".$userInfo['id']."' height='20' title='Тестовое'>".$userInfo['glob_inc']."</div></td>";
		$str = $str."<td align='right'><input id='dih_".$userInfo['id']."' type='hidden' value='".$userInfo['glob_inc']."'><input id='di_".$userInfo['id']."' type='text' value='' size='6'></td>";
		$str = $str."<td align='center'><img style='cursor:pointer' id='".$userInfo['id']."' height='30' src='img/incass.gif' title='Уменьшить значение' style='float:middle;' onClick=\"setGetPay(this.id, 'd', '-', 'glob_inc');\"".$actionIncass.">";
			if ($admin)
			{
				$str = $str."<img style='cursor:pointer' id='".$userInfo['id']."' height='30' src='img/pay.gif' title='Увеличить значение' style='float:middle;' onClick=\"setGetPay(this.id, 'd', '+', 'glob_inc');\"".$actionPay.">";
			}
		$str = $str."</td>";
	$str = $str."</tr>";
	$str = $str."<tr>";
		$str = $str."<td align='left'>Наличные ресурсы:</td><td align='left'><div id='r_".$userInfo['id']."'>".$userInfo['glob_sour']."</div></td>";
		$str = $str."<td align='right'><input id='rih_".$userInfo['id']."' type='hidden' value='".$userInfo['glob_sour']."'><input id='ri_".$userInfo['id']."' type='text' value='' size='6'></td>";
		$str = $str."<td align='center'><img style='cursor:pointer' id='".$userInfo['id']."' height='30' src='img/incass.gif' title='Уменьшить значение' style='float:middle;' onClick=\"setGetPay(this.id, 'r', '-', 'glob_sour');\"".$actionIncass.">";
			if ($admin)
			{
				$str = $str."<img style='cursor:pointer' id='".$userInfo['id']."' height='30' src='img/pay.gif' title='Увеличить значение' style='float:middle;' onClick=\"setGetPay(this.id, 'r', '+', 'glob_sour');\"".$actionPay.">";
			}
		$str = $str."</td>";
	$str = $str."</tr>";
	if (isset($userInfo['lastAction'])){
		$str = $str."<tr><td colspan='4' align='center' style='padding: 10 0 10 0;'><font size='-1'><u>".$userInfo['lastAction']."</u></font></td></tr>";
	}	
	$str = $str."</table>";
	return $str;
}


//выводит чекбокс чей ход
function printCheckBox($userId, $pic, $checked)
{
	$str = "<tr><td valign='center' colspan='2' width='70%'>";
	$str = $str."<input id='hod_".$userId."' name='gr_hod' type='radio' value='test_".rand()."' $checked style='position:absolute; visibility:hidden;'>";
	$str = $str."Очередь ходить:</td><td align='right'><img width='25' style='cursor:pointer;' id='ihod_".$userId."' name='hod_".$userId."' src='".$pic."' onClick=\"onChecking(document.getElementById(this.name), this)\">";
	$str = $str."<div id='empty_hod' style='position:absolute; visibility:hidden;'></div></td></tr>";
	print $str;
}

//выводит чекбокс "Кубик"
function printCheckBoxCube($userId, $pic, $checked, $result = "", $res = "")
{
	$result = str_replace('<br>', '', $result);
	$text = "";
	if (strpos($res, "_") > 0)
	{
	  //$text = "<font size='-1'><i>Кубик 1</i> - <b>".getCubeValue($res, 0)."</b><br><i>Кубик 2</i> - <b>".getCubeValue($res, 1)."</b></font>";
	  $text = "<font size='-1'><i>На кубиках выпало</i><br><b>".getCubeValue($res, 0)."</b> и <b>".getCubeValue($res, 1)."</b></font>";
	}
    $str = "<tr><td valign='center' colspan='2' width='70%'>";
	$str = $str."<input id='cube_".$userId."' name='gr_cube' type='radio' value='test_".rand()."' $checked style='position:absolute; visibility:hidden;'>";
	$str = $str."Бросить кубик:</td><td align='right'><table border='0' style='margin:0 -3 0 0' width='100%'><tr><td align='center'>".$text."</td>
    
    <td align='right'><img width='25' style='cursor:pointer;' id='icube_".$userId."' name='cube_".$userId."' src='".$pic."' onClick=\"onChecking(document.getElementById(this.name), this)\" title='$result'>";
	$str = $str."<div id='empty_cube' style='position:absolute; visibility:hidden;'></div></td></tr></table></td></tr>";
	print $str;
}



//Функция вывода активных в данный момент игроков
function showActiveGamers($ViewType = 0)
{
	global $capColorReferences;
	global $EnToRusUserAttributes;
	$UsersInfo = getAllInfoAboutUsers();
	$iauc = getInfoAboutShowedCard();
	$iac = getInfoAboutCube();
	if ($ViewType == 0)
	{
		print "<div id='activeGamers' style='height:100%;overflow-y:auto;overflow-x:hidden'><table border='0' width='100%'>";
		foreach ($UsersInfo as $element)
		{
			$stat =""; $cardType = "";
			if ($iauc['userId']==$element['id'])
			{
				$stat = $iauc['statusA'];
				$cardType = $iauc['cardforView'];
			}
			$forCapUrl = $element['active'] == '1'? "'editUserData.php?id=".$element['id']."'" : "''";
			$forFioUrl = $element['active'] == '1'? "'gamer.php?id=".$element['id']."'" : "''";
			$state = $element['active'] != '1'? "(Не активен)" : "";
			$userFile = getUserFileName($element['id']);
			print "<tr  id='$id'><td><table><tr style='background-color:silver;'><td colspan='3'><a href=".$forCapUrl." target='_blank'>"; 
			print "<img align='right' src='img/".$capColorReferences[$element['capColor']]."' title='Кликните для редактирования' border='0'></a><p><img class='remove_from_game' src='img/managegame/cross_red.png' height='20px' title='Удалить из игры' onclick='eventsFunction.removeFromGame(\"".urlencode($userFile)."\", \"".$element['FIO']."\")'><b><i><a href=".$forFioUrl." target='_blank'>".$element['FIO'].$state."</a></i></b></p></td></tr>";
			print "<tr><td >Показать карт.:</td><td align='right' colspan='2'>".ShowSelectCard($element['id'], $cardType)."</td></tr>";
            if ($iauc['isActive']==$element['id'])
			{
                printCheckBox($element['id'], "img/chchecked.gif", "checked");
			}else
			{
				printCheckBox($element['id'], "img/chclear.gif", "");
			}
			if ($iac['isActive']==$element['id'])
			{
				printCheckBoxCube($element['id'], "img/chchecked.gif", "checked", $iac['status'], $iac['result']);
			}
			else
			{
				printCheckBoxCube($element['id'], "img/chclear.gif", "", $iac['result']);
			}
			if (!isset($element['commonR']) || strLen($element['commonR'])==0) $element['commonR'] = 0;
			if (!isset($element['activeIncomeGreenCircle']) || strLen($element['activeIncomeGreenCircle'])==0) $element['activeIncomeGreenCircle'] = 0;
			if (!isset($element['passIncomeAllCircle']) || strLen($element['passIncomeAllCircle'])==0) $element['passIncomeAllCircle'] = 0;
				print "<tr><td colspan='3'>";
					print "<table width='100%' border='1' style='border:solid; border-color:black; border-collapse: collapse;'>";
						print "<tr align='center' style='border:solid;'><td style='border:solid; padding:5px;'><font size='-1'>Активный доход<br>(зеленый круг)</font></td><td style='padding:5px;'><font size='-1'>Пассивный доход<br>(все круги)</font></td></tr>";
						print "<tr align='center' style='border:solid;'><td style='border:solid; padding:10px;'>".$element['activeIncomeGreenCircle']."</td><td style='padding:10px;'>".$element['passIncomeAllCircle']."</td></tr>";
						print "<tr style='border:solid;'><td align='center' colspan='2'><font size='+2'>общий Ресурс: ".$element['commonR']."</font></td></tr>";
					print "</table>";
				print "</td></tr>";
			print "<tr><td colspan='3'>".printPaySystem($element, true)."</td>";
			print "<tr><th colspan='3' style='border-color:silver; border-style:solid; border-radius: 10px 10px 10px 10px;'><div id='card_".$element['id']."'>".$stat."</div></th></tr></table></td></tr>";
		}
		print "</table></div>";
		//print_r (getInfoAboutShowedCard());
	}
	else if ($ViewType == 1)
	{
		print "<table width='100%' style='border-collapse: collapse' border='0'>";
		foreach ($EnToRusUserAttributes as $atrName=>$atrValue)
		{
			if ($atrName == "FIO")
			{
				$parm = "style='background-color:silver; font-style:italic'";
			}else
			{
				$parm="";
			}
			print "<tr $parm><td style='border:solid; border-color:white'>".$atrValue."</td>";
			for ($i=0; $i<=count($UsersInfo)-1;$i++)
			{
				if ($atrName == "talants")
				{
					$text = $UsersInfo[$i]["cbManager"]." ".$UsersInfo[$i]["cbUrist"]." ".$UsersInfo[$i]["cbEconomic"]." ".$UsersInfo[$i]["cbIngeneer"]." ".$UsersInfo[$i]["cbDoctor"]." ".$UsersInfo[$i]["cbTourist"]." ".$UsersInfo[$i]["cbTeacher"]." ".$UsersInfo[$i]["cbDoner"];
					print "<td style='border:solid; border-color:white'>".$text."</td>";
				}else
				{
					print "<td style='border:solid; border-color:white'>".$UsersInfo[$i][$atrName]."</td>";
				}
			}
			print "</tr>";
		}
		print "</table>";
	}
}

//проверка выбранности checkbox`a и вывод chcked
function TryCheck ($name, $value)
{
	if ($name == $value)
	{
		return print "checked";
	}
}

//записывает измененные атрибуты указанные в $changedFilds
function WriteAttrib (&$arrAttrib, $changedFilds)
{
	if (count($changedFilds)!=0)
	{
        $name = getUserFileName($arrAttrib['id']);
		$xml = new ParseXML($name, true);
		$xml->SearchNode($xml->RootNode, "user", "id", $arrAttrib['id']);
		if ($xml->SearchedNodeLink != null)
		{
			foreach ($changedFilds as $name)
			{
				if (strlen($name)!= 0)
				{
					$arrAttrib[$name] = str_replace(array("\r\n", "\r", "\n"), " ", $arrAttrib[$name]);
					$xml->SearchedNodeLink->setAttribute($name, $arrAttrib[$name]);
				}
			}
			$xml->SaveInFile($xml->Nfile);
		}
		$xml->Destroy();
	}
}
//заполняем поля формы и переданного массива
function fillCardValuesFomPost($post)
{
	print "<script> $(document).ready(function(){";
	foreach($post as $key=>$value)
	{
		if (strlen($value) != 0)
			print "setValue('".$key."', '".$value."');";
	}
	print "})</script>";
}

//генерация карточки по передаваемому в функцию префиксу изображения
function RandCard($pref)
{
	$mask = "img/card/".$pref."*.jpg";
	$fileList = array();
	foreach (glob($mask) as $fn)
	{	
		$fileList[] = $fn;
	}
	$randNum = mt_rand(0, count($fileList) - 1);
	print "<img class='card' src='".$fileList[$randNum]."?".date("hms")."'>";
	$xml = new ParseXML(xmlForFlash, true);
	$xml->SearchNode($xml->RootNode, "card", "userId", $_SESSION['id']);
	if ($xml->SearchedNodeLink != null)
	{
		$xml->SearchedNodeLink->setAttribute("cardSelected", $fileList[$randNum]);
		$xml->SaveInFile($xml->Nfile);
	}
	$xml->Destroy();
}

//вывод заданного количества <br>
function PrintBrs ($count)
{
	for ($i=1; $i<=$count; $i++)
	{
		//print "<br>";
	}
}

//фиксация пользователя и типа карточки, которые надо ему показать
function setCardForUserSelect($userId, $cardType)
{
	$xml = new ParseXML(xmlForFlash);
	$xml->SearchNode($xml->RootNode, "card", "cardforView", "");
	if ($xml->SearchedNodeLink != null)
	{
		$xml->SearchedNodeLink->setAttribute("cardforView", $cardType);
		$xml->SearchedNodeLink->setAttribute("userId", $userId);
		$xml->SearchedNodeLink->setAttribute("cardSelected", "");
		$xml->SaveInFile($xml->Nfile);
	}else
	{
		$xml->SearchNode($xml->RootNode, "card", "userId", $userId);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->SearchedNodeLink->setAttribute("cardforView", $cardType);
			$xml->SearchedNodeLink->setAttribute("cardSelected", "");
			$xml->SaveInFile($xml->Nfile);
		}
		else
		{
			$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "cardforView");
			$xml->SearchNode($xml->RootNode, "card", "cardforView", $xml->nodesAttribValue[0]);
			$xml->SearchedNodeLink->setAttribute("cardforView", "");
			$xml->SaveInFile($xml->Nfile);
			setCardForUserSelect($userId, $cardType);
		}
	}
	$xml->Destroy();
}

//возвращает массив информации о показе кубика
function getInfoAboutCube()
{
	$result = array();
	$xml = new ParseXML(xmlForFlash);
	$xml->GetNodesAttribsValuesByName ($xml->RootNode, "cube", "isActive");
	if (count($xml->nodesAttribValue) != 0)
	{
		$result['userId'] = $xml->nodesAttribValue[0];
		$xml->GetNodesAttribsValuesByName ($xml->RootNode, "cube", "isActive");
		$result['isActive'] = $xml->nodesAttribValue[1];
		$xml->GetNodesAttribsValuesByName ($xml->RootNode, "cube", "result");
		$result['result'] = $xml->nodesAttribValue[2];
		$xml->Destroy();
		$name = getUserFileName($result['isActive']);
		$xml = new ParseXML($name);
		$xml->SearchNode($xml->RootNode, "user", "id", $result['isActive']);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->AttribFromSNL("", $temp);
			$xml->Destroy();
			$result['FIO'] = $temp['FIO'];
			$result['capColor'] = $temp['capColor'];
			unset($temp);
		}
		else
		{
			$xml->Destroy();
		}
		if (strlen(getCubeValue($result['result'],0)) == 0 || strlen(getCubeValue($result['result'],1)) == 0)
		{
			if(strlen($result['isActive']) == 0)
			{
				$result['status'] = "";
			}
			else
			{
				$result['status'] = "Кубики не были брошены";
			}
		}
		else
		{
			$result['status'] = "Кубики брошены игроком ".$result['FIO'].".<br> Значение кубика №1 = ".getCubeValue($result['result'], 0)."<br> Значение кубика №2 = ".getCubeValue($result['result'], 1);
		}
		if (strlen($result['isActive']) == 0)
		{
			$result['isActive'] = null;
		}
	}
	else
	{
		$xml->Destroy();
	}
	return $result;
}

//возвращает массив инвормации о пользователе и типе карточи, которую ему показывают
function getInfoAboutShowedCard()
{
	$result = array();
	$xml = new ParseXML(xmlForFlash);
	$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "userId");
	if (count($xml->nodesAttribValue) != 0)
	{
		$result['userId'] = $xml->nodesAttribValue[0];
		$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "cardforView");
		$result['cardforView'] = $xml->nodesAttribValue[1];
		$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "cardSelected");
		$result['cardSelected'] = $xml->nodesAttribValue[2];
		$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "isActive");
		$result['isActive'] = $xml->nodesAttribValue[3];
		$xml->Destroy();
		$name = getUserFileName($result['userId']);
		$xml = new ParseXML($name);
		$xml->SearchNode($xml->RootNode, "user", "id", $result['userId']);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->AttribFromSNL("", $temp);
			$xml->Destroy();
			$result['FIO'] = $temp['FIO'];
			$result['capColor'] = $temp['capColor'];
			unset($temp);
		}
		unset($xml);
		$name = getUserFileName($result['isActive']);
		$xml = new ParseXML($name);
		$xml->SearchNode($xml->RootNode, "user", "id", $result['isActive']);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->AttribFromSNL("", $temp);
			$xml->Destroy();
			$result['actFIO'] = $temp['FIO'];
			$result['actcapColor'] = $temp['capColor'];
		}
		$xml->Destroy();
	}else
	{
		$xml->Destroy();
	}
	if (strlen($result['cardSelected']) == 0)
	{
		$result['status'] = "Карточка в процессе выбора.";
		$result['click']="Нажмите на карточку";
		$result['statusA'] = "Карточка в процессе выбора.";
	}else
	{
		$title = "Карточка была выбрана игроком: ".$result['FIO'].", который играет фишкой с цветом: \"".$result['capColor']."\".";
		$result['status'] = "<img class='card' style='cursor:pointer' src='".$result['cardSelected']."' title='".$title."'>";
		$result['statusA'] = "<img class='card' style='cursor:pointer' src='".$result['cardSelected']."' title='".$title."' onClick=\"vote('operation.php?hideCard=yes&idUser=".$result['userId']."', 'card_".$result['userId']."')\">";
	}
	if ($result['cardSelected'] == $result['cardforView'])
	{
		$result['status'] = "";
		$result['statusA'] = "";
	}
	return $result;
}

//по имени карточки возвращает её русское название
function GetRusNameCard($src)
{
	global $cardsSettings;
	$i = 0;
	while ($cardsSettings[$i]['imgFile'] !== $src)
	{
		$i++;
	}
	return $cardsSettings[$i]['name'];
}

// таблица доходов всех пользователей
function commonUserMoney()
{
	$info = getAllInfoAboutUsers();
	$result = "<table border='1' width='100%' style='border-color:silver; border-style:solid; border-radius: 10px 10px 10px 10px;'>";
	$result .="<tr align='center' style='background-color:silver;'><td>ФИО</td><td>АД</td><td>ПД</td><td>R</td></tr>";
	foreach ($info as $user){
		$result .="<tr><td style='background-color:silver;'>".$user['FIO']."</td>";
		$result .="<td>".$user['activeIncomeGreenCircle']."</td>";
		$result .="<td>".$user['passIncomeAllCircle']."</td>";
		$result .="<td>".$user['commonR']."</td></tr>";
	}
	return $result .="</table>";
}

//показывает карточку пользователю которому необходимо сделать выбор 
//или показывет выбранную другим пользователем карточку
function ShowCardForUserSelect($userInfo)
{
	$temp = getInfoAboutShowedCard();
	if ($temp['isActive']==$userInfo['id'])
	{
		print "<script>document.getElementById('hod').innerHTML=\"<img align='middle' width='60' src='img/you_hod.gif?".time()."' width='100%' title='Ваш ход'>\";</script>";
	} else if ($temp['isActive'] != null && $temp['isActive'] !== "")
	{
		print "<font color='green'><u><b>Очередь ходить:</b></u></font> ".$temp['actFIO']."</br><font color='green'><u><b>Цвет фишки:</b></u></font> ".$temp['actcapColor']."<hr>";
	}	
	print "<div id='wrapper'>
		<ul class='tabs tabs1'>
			<li class='t1 tab-current'><a>Карточка</a></li>
			<li class='t2'><a>Доход и ресурсы игроков</a></li>
		</ul>
		<div class='t1' style='background-color:white;'>";
	//если текущий пользователь должен выбирать карточку
	if ($temp['userId'] == $userInfo['id'])
	{
		//если карточку он еще не выбрал
		if (strlen($temp['cardSelected']) > 0)
		{
			$action = "";
		}else
		{
			$action = "onClick=\"userRefreshStop(); vote('operation.php?randcard=On&pref='+this.name, 'vote_status'); this.name='null'\"";
		}	
		print "<table border='0' width='100%'>";
		if ($action == "") $temp['click'] = $temp['status'];
        print "<tr>	<td class='selCard' colspan='3'><div id='vote_status' height='30'>".$temp['click']."</div></td></tr>";
		print "<tr><td class='card'>";
		print "<a name='".substr($temp['cardforView'], 0, -4)."_' ".$action.">";
		if ($action !== "")
		{
			print "<img class='card' src='img/card/".$temp['cardforView']."' title='".GetRusNameCard($temp['cardforView'])."' alt='Выберите карточку <".GetRusNameCard($temp['cardforView']).">'>";
		}	
		print "</a></td></table>";
		print "</div>";
	}else
	{
		print "<table border='0' width='100%'>";
		//print "<th align='center' colspan='3'>Карточка</th>";
		print "<tr>	<td class='selCard' colspan='3'><div id='vote_status' height='30'>".$temp['status']."</div></td></tr>";
		print "</table>";
		print "</div>";
	}
		print "<div class='t2' style='padding:10 10 10 10; background-color:white;'>";
		print commonUserMoney();
		print "</div></div>".showCubeForSelect($userInfo['id']);
//	print_r ($temp);
}

//контролл для показа выбора кубика
function showCubeForSelect($userId)
{
	$cubeInfo = getInfoAboutCube();
	$str = "";
	if ($cubeInfo['isActive'] == $userId)
	{
		if (strlen($cubeInfo['result']) == 0)
		{
			$str .= "<p align='left'>Бросьте кубики <button onClick=\"vote('operation.php?randCube=yes&userId=".$userId."','cube');this.style.display='none';\">Бросить</button></p><div id='cube'><img src='img/cube/none.gif'></div>";
		}
		else
		{
			$str .= "<p align='center'><i>Значение кубика 1</i> - <font size='+1'>[".getCubeValue($cubeInfo['result'], 0)."]</font> <i>Значение кубика 2 </i>- <font size='+1'>[".getCubeValue($cubeInfo['result'], 1)."]</font></p><div id='cube'><img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/".getCubeValue($cubeInfo['result'], 0).".gif' align='left'><img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/".getCubeValue($cubeInfo['result'], 1).".gif' align='right'></div>";
		}
	}
	else
	{
		if (strlen($cubeInfo['isActive']) != 0)
		{
			$str .="<p align='left'>".$cubeInfo['status']."</p>";
		}
	}
	return $str;
}

//рандомим кубик
function randCube($userId)
{
	$str = "";
	$randNum = mt_rand(1,6)."_".mt_rand(1,6);
	$xml = new ParseXML(xmlForFlash, true);
	$xml->SearchNode($xml->RootNode, "cube", "isActive", $userId);
	$xml->SearchedNodeLink->setAttribute("result", $randNum);
	$xml->SaveInFile($xml->Nfile);
	$xml->Destroy();
	$randNum = explode("_", $randNum);
	$str .="<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/".$randNum[0].".gif' align='left'>"."<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/".$randNum[1].".gif' align='right'>";
	print $str;
}

//установить активного пользователя
function setActiveUser($action, $userId)
{
	$xml = new ParseXML(xmlForFlash, true);
	$xml->GetNodesAttribsValuesByName ($xml->RootNode, "card", "userId");
	if ($action == "true")
	{
		$xml->SearchNode($xml->RootNode, "card", "userId", $xml->nodesAttribValue[0]);
		$xml->SearchedNodeLink->setAttribute("isActive", $userId);
	}else if ($userId !== "")
	{
		$xml->SearchNode($xml->RootNode, "card", "userId", $xml->nodesAttribValue[0]);
		$xml->SearchedNodeLink->setAttribute("isActive", "");
	}
	$xml->SaveInFile($xml->Nfile);
	$xml->Destroy();
}

//установить пользователя которому показываем кубик
function setCubeUser($action, $userId)
{
	$xml = new ParseXML(xmlForFlash, true);
	$xml->GetNodesAttribsValuesByName ($xml->RootNode, "cube", "userId");
	if ($action == "true")
	{
		$xml->SearchNode($xml->RootNode, "cube", "userId", $xml->nodesAttribValue[0]);
		$xml->SearchedNodeLink->setAttribute("isActive", $userId);
		$xml->SearchedNodeLink->setAttribute("result", "");
	}else if ($userId !== "")
	{
		$xml->SearchNode($xml->RootNode, "cube", "userId", $xml->nodesAttribValue[0]);
		$xml->SearchedNodeLink->setAttribute("isActive", "");
		$xml->SearchedNodeLink->setAttribute("result", "");
	}
	$xml->SaveInFile($xml->Nfile);
	$xml->Destroy();
}

//плата/получение
function setPayValue($userId, $attribute, $value, $lastAction)
{
	$name = getUserFileName($userId);
	$xml = new ParseXML($name, true);
	$xml->SearchNode($xml->RootNode, "user", "id", $userId);
	if ($xml->SearchedNodeLink != null)
	{
		$xml->SearchedNodeLink->setAttribute($attribute, $value);
		$xml->SearchedNodeLink->setAttribute("lastAction", $lastAction);
		$xml->SaveInFile($xml->Nfile);
	}
	$xml->Destroy();
	print $value;
}

//сброс выбранной карты
function resetCard($idUser)
{
	$xml = new ParseXML(xmlForFlash, true);
	$xml->SearchNode($xml->RootNode, "card", "userId", $idUser);
	if ($xml->SearchedNodeLink != null)
	{
		$xml->SearchedNodeLink->setAttribute("cardforView", "");
		$xml->SearchedNodeLink->setAttribute("cardSelected", "");
		$xml->SearchedNodeLink->setAttribute("userId", "");
		$xml->SaveInFile($xml->Nfile);
	}
	$xml->Destroy();
	print "Карточка скрыта";
}

//вывод истории игры
function getUserHistory($userInfo)
{
	$arraySize = count($userInfo);
	$i = 0;
	while ($i < $arraySize && strlen($userInfo['h_time_'.$i]) != 0)
	{
		
		++$i;
	}
	$str = "<input type='hidden' value='".$i."'><TABLE bgcolor='#FFFFFF' border='1' bordercolorlight='#C0C0C0' bordercolordark='#808080' cellspacing='0'>";
	$str .="<TR valign='top'>";
	$str .="<TD width='148' bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Время</div></div></TD>";
	$str .="<TD width=162 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Что произошло</div></div></TD>";
	$str .="<TD width=219 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Состояние</div></div></TD>";
	$str .="<TD width=160 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Выводы</div></div></TD></TR>";
	$common = $i;
	$i = 0;
	while ($i <= $common)
	{
		if ($i == $common)
		{
			$values = array ("","","","");
		}else
		{
			$values = array ($userInfo['h_time_'.$i], $userInfo['h_happend_'.$i], $userInfo['h_state_'.$i], $userInfo['h_solve_'.$i]);
		}
		$str .="<TR>";
		$str .="<TD width='148' bgcolor='#C0C0C0'>";
		$str .="<input name='h_time_".($i)."' type='text' value='".$values[0]."' onChange='addChagedElement(this.name)' OnFocus='setDate(this)'></TD>";
		$str .="<TD width='162' bgcolor='#C0C0C0'>";
		$str .="<input name='h_happend_".($i)."' type='text' value='".$values[1]."' onChange='addChagedElement(this.name)'></TD>";		
		$str .="<TD width='219' bgcolor='#C0C0C0'>";
		$str .="<input style='width:219' name='h_state_".($i)."' type='text' value='".$values[2]."' onChange='addChagedElement(this.name)'></TD>";		
		$str .="<TD width='160' bgcolor='#C0C0C0'>";
		$str .="<input name='h_solve_".($i)."' type='text' value='".$values[3]."' onChange='addChagedElement(this.name)'></TD>";		
		$str .="</TR>";
		++$i;
	}
	$str .="</TABLE>";
	return $str;
}

function checkPresenterActive($data)
{
  global $presenterAttribs;
  $xml = new ParseXML(xmlForPresenters);
  $xml->SearchNode($xml->RootNode, $presenterAttribs['node'], "password", $data['password']);
  if ($xml->SearchedNodeLink != null)
  {
    $xml->AttribFromSNL("", $vis);
    if ($vis['active'] == 'true')
    {
      $now = strtotime(date("d-m-Y"));
      $dateBegin = strtotime($vis['dateBegin']);
      $dateEnd = strtotime($vis['dateEnd']);
      if ($now >=$dateBegin && $now<=$dateEnd)
      {
	if ($data['password'] == $vis['password'])
	{
	    $vis['status'] = 'OK';
	}
	else
	{
	    $vis['status'] = 'Не верный пароль';
	}
      }
      else
      {
	    $vis['status'] = 'Уточните период действия аккаунта для '.$vis['fio'];
      }
    }
    else
    {
      $vis['status'] = 'Аккаунт '.$vis['fio'].' не активен. Обратитесь к администратору';
    }
  }else {
      $vis['status'] = "Пользователь с таким паролем не существует в выбранной игре.";
  }
  $xml->Destroy();
  return $vis;
}

function showPresenterInfo($userId, $password)
{
  $info = checkPresenterActive(array("userId"=>$userId, "password"=>$password));
  if ($info['status'] != 'OK')
  {
    print "<script>alert('".$info['status']."');".$info['status']; //document.location.replace('".page404."');</script>
  }else
  {
	$dat = calcDatePeriod(null, $_SESSION['dateEnd']);
    print "<li class='t4'><u>Активный ведущий: ".$info['fio'].". Осталось - ".$dat['day']."д/".$dat['hours']."ч/".$dat['minutes']."м/".$dat['seconds']."с/";
  }
}

function saveAndLoadPresenterInfo($postData = Array())
{
	$vis = checkPresenterActive(array("userId"=>$_SESSION['presenterUnic'], "password"=>$_SESSION['presenterCode']));
	if ($vis['status'] != 'OK')
	{
		print "<script>alert('".$vis['status']."');document.location.replace('".page404."');</script>";
	}
	if (count($postData) != 0)
	{
		if ($postData['password'] == "{@}|{@}" || strlen($postData['password']) == 0)
		{
			unset ($postData['password']);
		}
		else
		{
			$postData['password'] = md5($postData['password']);
		}
        global $presenterAttribs;
		$atttrValues = makeAttribArray($postData, $presenterAttribs);
		$xml = new ParseXML(xmlForPresenters, true);
		$xml->SearchNode($xml->RootNode, 'presenter', 'id', $_SESSION['presenterUnic']);
		if ($xml->SearchedNodeLink != null)
		{
			$xml->ModifyElement("presenter", $atttrValues, $xml->SearchedNodeLink);
		}
        $xml->Destroy();
        $xml = new ParseXML(xmlForPresenters);
	    $xml->SearchNode($xml->RootNode, 'presenter', 'id', $_SESSION['presenterUnic']);
	    $xml->AttribFromSNL("", $vis);
	    $xml->Destroy();
    }
	$_SESSION['presenterCode'] = $vis['password'];
	$_SESSION['presenterUnic'] = $vis['id'];
	return $vis;
}

function calcDatePeriod($begin, $end)
{
	if ($begin == null)
	{
		$start_date = mktime();
	}
	else
	{
		$start_date = strtotime($begin); 
	}
	$end_date = strtotime($end); 

	$sec = $end_date - $start_date; 
	$days = floor($sec / 86400); 
	$hours = floor(($sec - $days * 86400) / 3600); 
	$minutes = floor(($sec - $days * 86400 - $hours * 3600) / 60); 
	$seconds = $sec - $days * 86400 - $hours * 3600 - $minutes * 60; 
	$counter =  Array("day"=>$days, "hours"=>$hours, "minutes"=>$minutes, "seconds"=>$seconds);
	return $counter;
}

function getCubeValue($result, $index){
	$res = explode("_", $result);
	return strlen($res[$index]) != 0 ? $res[$index] : "";
}

function getUserFileName($userId, $isNew = false){
	if ($isNew){
		copy(emptyBaseXmlFile, xmlFolder."/".$userId.".xml");
	}
	return xmlFolder."/".$userId.".xml";
}

/*
 * Загружает на сервер файлы из $files
 */
function upload($files){
if (!empty($files)){
	$str = "";
	foreach ($files["files"]["error"] as $key => $error) {
		if ($error == UPLOAD_ERR_OK) {
			$tmp_name = $files["files"]["tmp_name"][$key];
			$name = $files["files"]["name"][$key];
			if (!file_exists(tempFolder)){
				mkdir(tempFolder, 0777);
			}
			move_uploaded_file($tmp_name, tempFolder."/$name");
		} else {
			$str +="Ошибка загрузки - ".$files["files"]["name"][$key]."\n";
		}
	}
	if (strlen($str) > 0){
		print "<script>alert('".$str."')</script>";
	} else {
		print "<script>alert('Файлы загружены.')</script>";
	}
}
}

/*
 * Inject component js
 */
function includeGlobalComponentJS($name="global.js"){
	$compFolder = root.slash."component".slash."*";
	foreach(glob($compFolder) as $item){
		if (is_dir($item)){
			if (file_exists($item.slash.$name)){
				print "<script type='text/javascript'>";
				include($item.slash.$name);
				print "</script>";
			}
		}
	}
}

/*
 * Создаёт копию текущих файлов данных игроков
 * во временной папке с текущей датой и времнем
 */
function makeBackupUserFile(){
	global $userAttribsMinimal;
	$result = array();
	foreach(glob(xmlFolder."/*.xml") as $file){
		if (!is_dir($file)){
			$xml = new ParseXML($file);
			$xml->GetNodesAttribsValuesByName($xml->RootNode, $userAttribsMinimal['node'], $userAttribsMinimal['unic']);
			if (count($xml->nodesAttribValue) > 0){
				if (!isset($dest)){
					$dest = date('d-m-Y H.i.s');
					$result['date'] = $dest;
					if (!file_exists(tempFolder."/".$dest)){
						mkdir(tempFolder."/".$dest, 0777);
						$dest = tempFolder."/".$dest;
					}
				}
				copy($file, $dest."/".basename($file));
				$result['filelist'] .= basename($file)."\n";
			}
			$xml->Destroy();
			print_r ($attribs);
		}
	}
	$result['status'] = 'Ok'; 
	return json_encode($result);
}

/*
 * Возвращает список файлов/папок + информация из файла
 */
function getObjectInFolder($path, $type='dir', $conf){
	$result = array();
	if ($path == null) {
		return $result;
	}
	global $userAttribsMinimal;
	global $capColorReferences;
	foreach (glob(urldecode($path).slash."*") as $file){
		if ($type == "dir"){
			if (is_dir($file)){
				$result['list'][] = array("name"=>basename($file), "path"=>urlencode($file)); 
			}
		}else{
			if (!is_dir($file)){
				$xml = new ParseXML($file);
				if (!$xml->LoadResult) {
					continue;
				}
				$xml->GetNodesAttribsValuesByName($xml->RootNode, $userAttribsMinimal['node'], $userAttribsMinimal['unic']);
				if (count($xml->nodesAttribValue) > 0){
					foreach ($xml->nodesAttribValue as $value){
						$xml->SearchNode($xml->RootNode, $userAttribsMinimal['node'], $userAttribsMinimal['unic'], $value);
						if ($xml->SearchedNodeLink != null){
							$ind = count($result['list']);
							$xml->AttribFromSNL("", $result['list'][$ind]);
							if ($result['list'][$ind]['capColor']){
								$result['list'][$ind]['imgSrc'] = 'img'.slash.$capColorReferences[$result['list'][$ind]['capColor']];
							}
							$result['list'][$ind]['fileName'] = basename($file);
							$result['list'][$ind]['filePath'] = urlencode($file);
							foreach ($conf['addToObject'] as $key=>$value){
								$result['list'][$ind][$key]=$value;
							}
						}
					}
				}
				$xml->Destroy();
			}
		}
	}
	if (count($conf) > 0){
		for ($index=0;$index<count($conf);++$index){
			if ($conf[$index] != null){
				$result['list'][] = $conf[$index];
			}
		}
	}
	if ($type != "dir"){
		$result['caps'] = $capColorReferences;
	}
	return json_encode($result);
}

/*
 * Удаляет файл/папку по полному пути
 */
function deleteFile($file){
	if(isset($file) && file_exists($file)){
		if (!is_dir($file)){
			return unlink($file);
		}else{
			return rmdir($file);
		}
	}
}

function inFolder($path, $folder){
	if (strpos($path, $folder)==0){
		return true;
	} else {
		return false;
	}
}
/*
 * Ajax: удаляет игрока из игры
 */
function deleteGamer($path){
	$path = urldecode($path);
	if (!file_exists($path)){
		if (!file_exists(root.slash.$path)){
			return json_encode(array('status'=>urlencode($path).' - не существует'));
		} else {
			$path = root.slash.$path;
		}
	} else {
		$path = realpath($path);
	}
	if (!inFolder($path, root.slash.xmlFolder)){
		deleteFile($path);
		return json_encode(array('status'=>'Ok'));
	} else {
		return json_encode(deleteGamerFromAnywhere());
	}
	return json_encode(array('status'=>'Error in deleteGamer function'));
}

/*
 * Удаление игрока из игры по файлу данных
 */
function deleteGamerFromAnywhere($file){
	$xml = new ParseXML($file);
	if (!$xml->LoadResult){
		return array('status'=>'Error loading file '.$file.' in deleteGamerFromAnywhere function');
	}else {
		global $userAttribsMinimal;
		$xml->GetNodesAttribsValuesByName($xml->RootNode, $userAttribsMinimal['node'], $userAttribsMinimal['unic']);
		if (count($xml->nodesAttribValue) > 0){
			$capXml = new ParseXML(xmlForFlash);
			$needSave = false;
			foreach ($xml->nodesAttribValue as $value){
				$capXml->SearchNode($capXml->RootNode, 'cap', 'idUser', $value);
				if ($capXml->SearchedNodeLink != null){
					$capXml->ModifyElement(null, array('posX'=>'-1','posY'=>'-1','visible'=>'false','idUser'=>''), $capXml->SearchedNodeLink);
				}
				$capXml->SearchNode($capXml->RootNode, 'card', 'isActive', $value);
				if ($capXml->SearchedNodeLink != null){
					$capXml->ModifyElement(null, array('userId'=>'', 'cardforView'=>'', 'cardSelected'=>'', 'isActive'=>'', 'result'=>''), $capXml->SearchedNodeLink);
				}
				$capXml->SearchNode($capXml->RootNode, 'cube', 'isActive', $value);
				if ($capXml->SearchedNodeLink != null){
					$capXml->ModifyElement(null, array('userId'=>'', 'isActive'=>'', 'result'=>''), $capXml->SearchedNodeLink);
				}
			}
			$capXml->Destroy();
		}
	}
	$xml->Destroy();
	if (deleteFile($file)){
		return array('status'=>'Ok');
	} else {
		return array('status'=>'Can`t remove file '.$file);
	}
}

function saveConfig($postData){
	$capFN = getCapXmlBak();
	$capXml = new ParseXML($capFN,true);
	foreach ($postData as $color=>$data)
	{
		$userFile = urldecode($data['path']);
		$xml=new ParseXml($userFile,true);
		$xml->GetNodesAttribsValuesByName($xml->RootNode, 'user', 'id');
		$userIdsForCheck = array();
		foreach($xml->nodesAttribValue as $value){
			$xml->SearchNode($xml->RootNode, 'user', 'id', $value);
			$attrs = array();
			if ($xml->SearchedNodeLink != null){
				$xml->AttribFromSNL('', $attrs);
				if ($attrs['capColor']!=$color){
					$xml->SearchedNodeLink->setAttribute('capColor', $color);
				}
				if (!inFolder($userFile, root.slash.xmlFolder)){
					$xml->SaveInFile(root.slash.xmlFolder.slash.$attrs['id'].'.xml');
				} else {
					$xml->SaveInFile($xml->Nfile);
				}
				$capAttrs = array();
				$capXml->SearchNode($capXml->RootNode, 'cap', 'color', $color);
				if ($capXml->SearchedNodeLink != null){
					$capXml->AttribFromSNL('', $capAttrs);
					if ($capAttrs['idUser']!=$attrs['id']){
						$capXml->SearchedNodeLink->setAttribute('idUser', $attrs['id']);
						$capXml->SearchedNodeLink->setAttribute('visible', 'true');
						$userIdsForCheck[] = $capAttrs['idUser'];
					}
				}
			}
		}
		$xml->Destroy();
	}
	foreach ($userIdsForCheck as $id){
		$exist = false;
		foreach ($postData as $color=>$data){
			if ($data['id']==$id && !empty($id)){
				$exist = true;
				break;
			}
		}
		if (!$exist && !empty($id) && file_exists(root.slash.xmlFolder.slash.$id.'.xml')){
			deleteFile(root.slash.xmlFolder.slash.$id.'.xml');
		}
	}
	$capXml->SaveInFile($capXml->Nfile);
	$capXml->Destroy();
	rename($capFN, xmlForFlash);
	return json_encode(array('status'=>'Новая конфигурация игры сохранена.'));
}

function getCapXmlBak(){
	$tempName = md5(date("dmYhhmmss"));
	if (copy(xmlForFlash, $tempName)){
		$xml = new ParseXml($tempName);
		$xml->SearchNode($xml->RootNode, "cap", "visible", "true");
		$xml->AttribFromSNL("visible", $vis);
		while ($vis["visible"]=="true" && $xml->SearchedNodeLink != null)
		{
			$xml->SearchedNodeLink->setAttribute("visible", "false");
			$xml->SearchedNodeLink->setAttribute("posX", "-1");
			$xml->SearchedNodeLink->setAttribute("posY", "-1");
			$xml->SearchedNodeLink->setAttribute("idUser", "");
			$xml->SearchedNodeLink = null;
			$xml->SearchNode($xml->RootNode, "card", "userId", $vis["idUser"]);
			if ($xml->SearchedNodeLink != null)
			{
				$xml->SearchedNodeLink->setAttribute("userId", "");
				$xml->SearchedNodeLink->setAttribute("cardforView", "");
				$xml->SearchedNodeLink->setAttribute("cardSelected", "");
				$xml->SearchedNodeLink->setAttribute("isActive", "");
				$xml->SearchedNodeLink = null;
			}
			$xml->SearchNode($xml->RootNode, "cap", "visible", "true");
			unset($vis);
			$xml->AttribFromSNL("visible", $vis);
		}
		$xml->SaveInFile($xml->Nfile);
		$xml->Destroy();
		return $tempName;
	} else {
		return xmlForFlash;
	}
}
?>
