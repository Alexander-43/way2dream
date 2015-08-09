<?php
$Except = array ();
$ErorrList = Array (
		"0" => "Выбранная вами фишка с цветом {*color*} уже занята другим игроком",
		"1" => "Неудалось обновить значения координат фишки с именем {*capName*}",
		"2" => "Файл {*absentFile*} не существует. Выберите другой файл.",
		"3" => "Ошибка копирования файла {*copyedFile*}",
		"4" => "Не удалось заменить {*FilesReplace*}",
		"97" => "Файл данных игры успешно обновлен пустой копией",
		"98" => "Файл данных игры удачно скопирован в архив",
		"99" => "Данные игры обновлены, используемые фишки освобождены" 
);
function printImg() {
	new Parse ( dataSourceType, xmlForFlash, $xml );
	$kol = 0;
	for($i = 1; $i < 7; $i ++) {
		$stt = "";
		$str = "<img id='" . $i . "' name='img_" . $i . "' src='img/img_" . $i;
		$str = $str . ".gif' onMouseOver='mOverAction(this);' onMouseOut='mOutAction(this);' ";
		$str = $str . "onClick='mOnClick(this);'/>";
		$atr = "visible";
		$xml->getAttribValue ( "cap", "name", "cap_" . $i, $atr, $xml->RootNode );
		if ($atr != "true") {
			print "$str";
			$kol ++;
		}
	}
	$xml->Destroy ();
	if ($kol == 0) {
		if (isset ( $_SESSION ['id'] )) {
			print "<a href='gamer.php'>Вернуться в игру</a>";
		} else {
			print "<h3 align='center'>Извините, количество игроков в игре максимально</h3>";
		}
	}
}
function AddToErrorList($NumErr, $StrReplace, $MetaTag = null) {
	$Except [] = $NumErr;
	if ($MetaTag != null) {
		$ErorrList [$NumErr] = str_replace ( $MetaTag, "\"" . $StrReplace . "\"", $ErorrList [$NumErr] );
	}
}
function getAllInfoAboutUser($userId) {
	new Parse ( dataSourceType, xmlForUserData, $xml );
	$xml->SearchNode ( $xml->RootNode, "user", "id", $userId );
	if ($xml->SearchedNodeLink != null) {
		$attribs = array ();
		$xml->AttribFromSNL ( "", $attribs );
	}
	$xml->Destroy ();
	return $attribs;
}

// сохраняет регистрационные даные пользователя
function SaveRegData($data) {
	global $ErorrList;
	global $Except;
	$Attribs = array ();
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "cap", "name", $data ["cap"] );
	if ($xml->SearchedNodeLink != null) {
		$AtrVal = $xml->AttribFromSNL ( "visible" );
		if ($AtrVal != "{*absent*}" && $AtrVal != "true") {
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"visible" => "true",
					"idUser" => $_SESSION ['id'] 
			) );
			$xml->AttribFromSNL ( "", $Attribs );
			$xml->SaveInFile ( $xml->Nfile );
			$xml->Destroy ();
			new Parse ( dataSourceType, xmlForUserData, $xml, true );
			$attribList = Array (
					"id" => $data ["id"],
					"FIO" => $data ["FIO"],
					"email" => $data ["email"],
					"skype" => $data ["skype"],
					"capColor" => $Attribs ["color"],
					"active" => "1",
					"date" => date ( "d.m.Y H:i:s" ) 
			);
			$xml->ModifyElement ( "user", $attribList, "new" );
			$xml->SaveInFile ( $xml->Nfile );
			$xml->Destroy ();
		} else {
			AddToErrorList ( 0, $xml->AttribFromSNL ( "color" ), "{*color*}" );
			$xml->Destroy ();
		}
	}
}

// вывод собранных возникших ошибок
function PrintErorrs($Erorrs) {
	global $ErorrList;
	$er = "";
	for($i = 0; $i < count ( $Erorrs ); ++ $i) {
		$er .= $i . ". " . $ErorrList [$Erorrs [$i]] . "\n";
	}
	return $er;
}
function ArchiveGameBase() {
}

// Функция обновления координат фишек по имени, если ссылка на xml файл не передается, то
// xml объект создаётся и уничтожается в функции
function UpdateCapValues($CapName, $Xpos, $Ypos, $xml = null) {
	$flag = false;
	if ($xml == null) {
		new Parse ( dataSourceType, xmlForFlash, $xml, true );
		$flag = true;
	}
	$xml->SearchNode ( $xml->RootNode, "cap", "name", $CapName );
	if ($xml->SearchedNodeLink != null) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"posX" => $Xpos,
				"posY" => $Ypos 
		) );
		$xml->SaveInFile ( $xml->Nfile );
	} else {
		AddToErrorList ( 1, $CapName, "{*capName*}" );
	}
	if ($flag)
		$xml->Destroy ();
}

// функция выводит select для выбора времени обновления и кнопку старт/стоп
function ShowRunStopObject($time, $state = 0) {
	if ($time == "")
		$time = 15;
	print "<span height='10' style='overflow:visible; margin:0 0 5px 0; position:relative;'><form name='timerObj' action='gamer.php' method='post'>Обновлять раз в <select name='timer'>";
	for($i = 5; $i <= 20; $i += 2) {
		if ($i == $time) {
			print "<option value=" . $i . " selected>" . $i . " сек." . "</option>";
		} else {
			print "<option value=" . $i . ">" . $i . " сек." . "</option>";
		}
	}
	print "</select> &nbsp";
	if ($state == "")
		$state = 1;
	if ($state == 1) {
		$alt = "Запуск атоматического обновления страницы";
	} else {
		$alt = "Остановить автоматическое обновление страницы";
	}
	print "<img name='run' id='" . $state . "' src='img/" . $state . ".gif' height='30' align='middle' onMouseDown='imgOver(this, 28);' onMouseUpt='imgOver(this, 30);' onClick='RunStop(this);' alt='" . $alt . "' style='cursor:pointer'>";
	print "<span id='hod' style='margin:0 0 0 10'></span>";
	print "<input id='state' name='state' type='hidden' value='" . $state . "'>";
	print "</form></span>";
}

// функция вывода блока информации о пользователе на странице наблюдения за игрой
function InfoAboutUser($arrayOfInfo) {
	global $capColorReferences;
	$allInfo = getAllInfoAboutUser ( $arrayOfInfo ['id'] );
	if (! array_key_exists ( "glob_inc", $allInfo ))
		$allInfo ['glob_inc'] = 0;
	if (! array_key_exists ( "glob_sour", $allInfo ))
		$allInfo ['glob_sour'] = 0;
	$colorText = $allInfo ['capColor'];
	print "<table class='selCard' align='center' border='1' width='100%'><tr>";
	if ($_SESSION['authKey']!=accessCode && strlen($_SESSION['presenterCode']) == 0){
		print "<td align='left' style='border-style:none'><b><i>" . $allInfo ['FIO'] . "</i></b></td>";
		print "<td align='right' width='100' style='border-style:none'>";
		print "<img src='img/" . $capColorReferences [$allInfo ['capColor']] . "' align='middle' title='" . $colorText . "'>";
		print "<a href='editUserData.php?id=" . $allInfo ['id'] . "' target='top'><img src='img/info.jpg' align='middle' title='Редактировать информацию игры' width='50px'></a>";
		print "</td>";
	} else {
		userSelectorRender($arrayOfInfo['id']);
	}
	if (! isset ( $allInfo ['commonR'] ) || strLen ( $allInfo ['commonR'] ) == 0)
		$allInfo ['commonR'] = 0;
	if (! isset ( $allInfo ['pasIncomeBlueCircle'] ) || strLen ( $allInfo ['pasIncomeBlueCircle'] ) == 0)
		$allInfo ['pasIncomeBlueCircle'] = 0;
	if (! isset ( $allInfo ['pasIncomeGreenCircle'] ) || strLen ( $allInfo ['pasIncomeGreenCircle'] ) == 0)
		$allInfo ['pasIncomeGreenCircle'] = 0;
	print "</tr><tr><td colspan='2'>";
	print "<table width='100%' border='1' style='border:solid; border-color:black; border-collapse: collapse;'>";
	print "<tr align='center' style='border:solid;'><td style='border:solid; padding:5px;'><font size='-1'>Активный доход<br>(зеленый круг)</font></td><td style='padding:5px;'><font size='-1'>Пассивный доход<br>(все круги)</font></td></tr>";
	print "<tr align='center' style='border:solid;'><td style='border:solid; padding:10px;'>" . $allInfo ['activeIncomeGreenCircle'] . "</td><td style='padding:10px;'>" . $allInfo ['passIncomeAllCircle'] . "</td></tr>";
	print "<tr style='border:solid;'><td align='center' colspan='2'><font size='+2'>общий Ресурс: " . $allInfo ['commonR'] . "</font></td></tr>";
	print "</table>";
	print "</td></tr>";
	print "<tr><td colspan='2' style='border-style:none'>" . printPaySystem ( $allInfo, false ) . "</td></tr>";
	print "</table>";
}

function userSelectorRender($id){
	global $capColorReferences;
	$usersInfo = getUserInfo('all');
	print "<td align='left' style='border-style:none'><select id='userSelector' class='userSelector'>";
	$defaultIndex = null;
	for ($i = 0; $i<count($usersInfo);++$i){
		if ($usersInfo[$i]['id'] == $id){
			$defaultIndex = $i;
		}
		$description ="Цвет фишки:%s, Email:%s, Skype:%s";
		$description = sprintf($description, $usersInfo[$i]['capColor'], $usersInfo[$i]['email'], $usersInfo[$i]['skype']);
		print "<option value='".$usersInfo[$i]['id']."' data-imagesrc='img/".$capColorReferences [$usersInfo[$i]['capColor']]."' data-description='".$description."'>";
		print $usersInfo[$i]['FIO'];
		print "</option>";
	}
	print "</select></td>";
	print "<td align='right' width='50' style='border-style:none'><a href='editUserData.php?id=" . $id . "' target='top'><img src='img/info.jpg' align='middle' style='padding-left:10' title='Редактировать информацию игры' width='50px'></a></td>";
	print getScriptHtml("createUserSelector('#userSelector',".$defaultIndex.")","'#userSelector'");
	
}

// генерация кода доступа
function genHash($str) {
	print (" Полученный код доступа - " . md5 ( $str )) ;
}

// выводит файлы архива игроков
function ShowFileInDir($DIR) {
	$mask = $DIR . "/*.xml";
	$s = array ();
	foreach ( glob ( $mask ) as $fn ) {
		$s [] = "<td align='center' style='border:solid; padding: 10 0 10 0;'><a href='" . $fn . "'>" . basename ( $fn ) . " ( " . round ( filesize ( $fn ) / 1024, 2 ) . " Kb)</a></td>";
	}
	print "<table width='100%' style='border-collapse: collapse;'>";
	print "<tr><td colspan='" . columnOfArchFile . "' style='padding: 20 0 20 30'><input id='genHash' name='genHash' type='text' value=''> <input type='button' value='Сгенерировать код доступа' onClick=\"vote('operation.php?generate=true&str='+document.getElementById('genHash').value, 'hash')\"><div id='hash' style='display:inline'></div></td></tr>";
	print "<tr><td align='center' colspan='" . columnOfArchFile . "' style='padding: 20 0 20 0; border:solid'>Файлы архива</td></tr>";
	for($i = 0; $i <= count ( $s ) - 1; $i = $i + columnOfArchFile) {
		$t = "";
		for($j = 0; $j <= columnOfArchFile - 1; $j ++) {
			$t = $t . $s [$i + $j];
		}
		print "<tr>" . $t . "</tr>";
	}
	print "</table>";
}

// удаляет пользователя и очищает кубик, ход и карточку
function removeUser($id) {
	$message = "";
	$status = "Ok";
	if (! isset ( $id )) {
		return json_encode ( array (
				"status" => "Error",
				"message" => "Ueser id not set !" 
		) );
	}
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	if ($xml->SearchNode ( $xml->RootNode, "card", "isActive", $id ) || $xml->SearchNode ( $xml->RootNode, "card", "userId", $id )) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"userId" => "",
				"cardforView" => "",
				"cardSelected" => "",
				"isActive" => "",
				"id" => "card" 
		) );
	}
	if ($xml->SearchNode ( $xml->RootNode, "cube", "isActive", $id )) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"userId" => "",
				"isActive" => "",
				"result" => "",
				"id" => "cube" 
		) );
	}
	if ($xml->SearchNode ( $xml->RootNode, "cap", "idUser", $id )) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"visible" => "false",
				"posX" => "-1",
				"posY" => "-1",
				"idUser" => "" 
		) );
	} else {
		$status = "Error";
		$message = "User not found";
	}
	return json_encode ( array (
			"status" => $status,
			"message" => $message 
	) );
}

// делает доступными все фишки
function StartNewGame() {
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "card", "id", "card" );
	$xml->setAttribute ( $xml->SearchedNodeLink, Array (
			"userId" => "",
			"cardforView" => "",
			"cardSelected" => "",
			"isActive" => "",
			"id" => "card" 
	) );
	$xml->SearchNode ( $xml->RootNode, "cube", "id", "cube" );
	$xml->setAttribute ( $xml->SearchedNodeLink, Array (
			"userId" => "",
			"isActive" => "",
			"result" => "",
			"id" => "cube" 
	) );
	try {
		new Parse ( dataSourceType, xmlForUserData, $xmlBase, true );
	} catch ( Exception $e ) {
		CreateFile ( substr ( $file, 0, - 4 ), "<?xml version='1.0' encoding='UTF-8'?><?xml-stylesheet type='text/xsl' href='test.xsl'?><root></root>" );
		new Parse ( dataSourceType, xmlForUserData, $xmlBase, true );
	}
	$xml->SearchNode ( $xml->RootNode, "cap", "visible", "true" );
	$xml->AttribFromSNL ( "visible", $vis );
	while ( $vis ["visible"] == "true" && $xml->SearchedNodeLink != null ) {
		print_r ( $vis );
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"visible" => "false",
				"posX" => "-1",
				"posY" => "-1",
				"idUser" => "" 
		) );
		$xml->SearchedNodeLink = null;
		$xml->SearchNode ( $xml->RootNode, "card", "userId", $vis ["idUser"] );
		if ($xml->SearchedNodeLink != null) {
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"userId" => "",
					"cardforView" => "",
					"cardSelected" => "",
					"isActive" => "" 
			) );
			$xml->SearchedNodeLink = null;
		}
		$xmlBase->SearchNode ( $xmlBase->RootNode, "user", "id", $vis ["idUser"] );
		if ($xmlBase->SearchedNodeLink != null) {
			$xmlBase->setAttribute ( $xmlBase->SearchedNodeLink, Array (
					"active" => "0" 
			) );
			$xmlBase->SearchedNodeLink = null;
		}
		$xml->SearchNode ( $xml->RootNode, "cap", "visible", "true" );
		unset ( $vis );
		$xml->AttribFromSNL ( "visible", $vis );
	}
	$xmlBase->SaveInFile ( $xmlBase->Nfile );
	$xml->SaveInFile ( $xml->Nfile );
	AddToErrorList ( 99, "" );
	$xml->Destroy ();
	$xmlBase->Destroy ();
	// ArchXmlBase(xmlForUserData, maxBaseSize, folderBaseArchive);
}

// создает файл $fname с содержимым $body
function CreateFile($fname, $body = "") {
	$f = fopen ( $file, "w" );
	fputs ( $f, $body );
	fclose ( $f );
}

// проверяет размер бызы и перемещает в архив при достижении критического размера
function ArchXmlBase($file, $maxSize, $ArhFolder) {
	if (file_exists ( $file ) && round ( filesize ( $file ) / 1024, 2 ) > $maxSize) {
		if (! file_exists ( substr ( $file, 0, - 4 ) )) {
			CreateFile ( substr ( $file, 0, - 4 ), "<?xml version='1.0' encoding='UTF-8'?><?xml-stylesheet type='text/xsl' href='test.xsl'?><root></root>" );
		}
		if (copy ( $file, $ArhFolder . "/" . date ( "d.m.Y" ) . ".xml" )) {
			AddToErrorList ( 98, "" );
			if (copy ( substr ( $file, 0, - 4 ), $file )) {
				AddToErrorList ( 97, "" );
			} else {
				AddToErrorList ( 4, "файл " . $file . " на файл " . substr ( $file, 0, - 4 ), "{*FilesReplace*}" );
			}
		} else {
			AddToErrorList ( 3, $file, "{*copyedFile*}" );
		}
	} else {
		AddToErrorList ( 2, $file, "{*absentFile*}" );
	}
	PrintErorrs ( $Except );
}

// Функция получения значений всех данных пользователей
function getAllInfoAboutUsers() {
	new Parse ( dataSourceType, xmlForFlash, $xml );
	$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "cap", "idUser" );
	$NAV = $xml->nodesAttribValue;
	$xml->Destroy ();
	$AllInfoAboutUsers = array ();
	new Parse ( dataSourceType, xmlForUserData, $xml );
	foreach ( $NAV as $elem ) {
		$xml->SearchNode ( $xml->RootNode, "user", "id", $elem );
		if ($xml->SearchedNodeLink != null && strlen ( $elem ) != 0) {
			$xml->AttribFromSNL ( "", $vis );
			$AllInfoAboutUsers [] = $vis;
			unset ( $vis );
		}
	}
	$xml->Destroy ();
	return $AllInfoAboutUsers;
}
function ShowSelectCard($userId, $cardType = null) {
	global $cardsSettings;
	// disabled='disabled'
	$select = "<select align='right' id='card' " . $cardsSettings [0] ['size'] . " " . $cardsSettings [0] ['multi'] . " name='" . $userId . "' onChange='sendCardType(this)'>";
	for($i = 1; $i <= count ( $cardsSettings ) - 1; $i ++) {
		$isSel = "";
		if ($cardsSettings [$i] ['imgFile'] == $cardType) {
			$isSel = "selected";
		}
		$select .= "<option value='" . $cardsSettings [$i] ['imgFile'] . "' " . $isSel . ">" . $cardsSettings [$i] ['name'] . "</option>";
	}
	$select .= "</select>";
	return $select;
}

// выводит поля для оплаты/получения в зависимости от игрок/ведущий
function printPaySystem($userInfo, $admin = false) {
	// $actionPay = " onMouseDown=\"this.src='img/payDown.gif'\" onMouseUp=\"this.src='img/pay.gif'\" ";
	// $actionIncass = "onMouseDown=\"this.src='img/incassDown.gif'\" onMouseUp=\"this.src='img/incass.gif'\"";
	$str = "<table width='100%' border='0'>";
	$str = $str . "<tr>";
	$str = $str . "<td align='left'>Наличные деньги:</td><td align='left'><div id='d_" . $userInfo ['id'] . "' height='20' title='Тестовое'>" . $userInfo ['glob_inc'] . "</div></td>";
	$str = $str . "<td align='right'><input id='dih_" . $userInfo ['id'] . "' type='hidden' value='" . $userInfo ['glob_inc'] . "'><input id='di_" . $userInfo ['id'] . "' type='text' value='' size='6'></td>";
	$str = $str . "<td align='center'><img style='cursor:pointer' id='" . $userInfo ['id'] . "' height='30' src='img/incass.gif' title='Уменьшить значение' style='float:middle;' onClick=\"setGetPay(this, 'd', '-', 'glob_inc');\"" . $actionIncass . ">";
	if ($admin) {
		$str = $str . "<img style='cursor:pointer' id='" . $userInfo ['id'] . "' height='30' src='img/pay.gif' title='Увеличить значение' style='float:middle;' onClick=\"setGetPay(this, 'd', '+', 'glob_inc');\"" . $actionPay . ">";
	}
	$str = $str . "</td>";
	$str = $str . "</tr>";
	$str = $str . "<tr>";
	$str = $str . "<td align='left'>Наличные ресурсы:</td><td align='left'><div id='r_" . $userInfo ['id'] . "'>" . $userInfo ['glob_sour'] . "</div></td>";
	$str = $str . "<td align='right'><input id='rih_" . $userInfo ['id'] . "' type='hidden' value='" . $userInfo ['glob_sour'] . "'><input id='ri_" . $userInfo ['id'] . "' type='text' value='' size='6'></td>";
	$str = $str . "<td align='center'><img style='cursor:pointer' id='" . $userInfo ['id'] . "' height='30' src='img/incass.gif' title='Уменьшить значение' style='float:middle;' onClick=\"setGetPay(this, 'r', '-', 'glob_sour');\"" . $actionIncass . ">";
	if ($admin) {
		$str = $str . "<img style='cursor:pointer' id='" . $userInfo ['id'] . "' height='30' src='img/pay.gif' title='Увеличить значение' style='float:middle;' onClick=\"setGetPay(this, 'r', '+', 'glob_sour');\"" . $actionPay . ">";
	}
	$str = $str . "</td>";
	$str = $str . "</tr>";
	if (isset ( $userInfo ['lastAction'] )) {
		$str = $str . "<tr><td colspan='4' align='center' style='padding: 10 0 10 0;'><font size='-1'><u>" . $userInfo ['lastAction'] . "</u></font></td></tr>";
	}
	$str = $str . "</table>";
	return $str;
}

// выводит чекбокс чей ход
function printCheckBox($userId, $pic, $checked) {
	$str = "<tr><td valign='center' colspan='2' width='70%'>";
	$str = $str . "<input id='hod_" . $userId . "' name='gr_hod' type='radio' value='test_" . rand () . "' $checked style='position:absolute; visibility:hidden;'>";
	$str = $str . "Очередь ходить:</td><td align='right'><img width='25' style='cursor:pointer;' id='ihod_" . $userId . "' name='hod_" . $userId . "' src='" . $pic . "' onClick=\"onChecking(document.getElementById(this.name), this)\">";
	$str = $str . "<div id='empty_hod' style='position:absolute; visibility:hidden;'></div></td></tr>";
	print $str;
}

// выводит чекбокс "Кубик"
function printCheckBoxCube($userId, $pic, $checked, $result = "", $res = "") {
	$result = str_replace ( '<br>', '', $result );
	$text = "";
	if (strpos ( $res, "_" ) > 0) {
		// $text = "<font size='-1'><i>Кубик 1</i> - <b>".getCubeValue($res, 0)."</b><br><i>Кубик 2</i> - <b>".getCubeValue($res, 1)."</b></font>";
		$text = "<font size='-1'><i>На кубик" . (getCubeValue ( $res, 0 ) == "NaN" || getCubeValue ( $res, 1 ) == "NaN" ? "е" : "ах") . " выпало</i><br>" . (getCubeValue ( $res, 0 ) != 'NaN' ? "<b>" . getCubeValue ( $res, 0 ) . "</b>" : "") . (getCubeValue ( $res, 0 ) != "NaN" && getCubeValue ( $res, 1 ) != "NaN" ? " и " : "") . (getCubeValue ( $res, 1 ) != 'NaN' ? "<b>" . getCubeValue ( $res, 1 ) . "</b>" : "") . "</font>";
	}
	$str = "<tr><td valign='center' colspan='2' width='70%'>";
	$str = $str . "<input id='cube_" . $userId . "' name='gr_cube' type='radio' value='test_" . rand () . "' $checked style='position:absolute; visibility:hidden;'>";
	$str = $str . "Бросить кубик:</td><td align='right'><table border='0' style='margin:0 -3 0 0' width='100%'><tr><td align='center'>" . $text . "</td>
    
    <td align='right'><img width='25' style='cursor:pointer;' id='icube_" . $userId . "' name='cube_" . $userId . "' src='" . $pic . "' onClick=\"onChecking(document.getElementById(this.name), this)\" title='$result'>";
	$str = $str . "<div id='empty_cube' style='position:absolute; visibility:hidden;'></div></td></tr></table></td></tr>";
	print $str;
}

// Функция вывода активных в данный момент игроков
function showActiveGamers($ViewType = 0) {
	global $capColorReferences;
	global $EnToRusUserAttributes;
	$UsersInfo = getAllInfoAboutUsers ();
	$iauc = getInfoAboutShowedCard ();
	$iac = getInfoAboutCube ();
	if ($ViewType == 0) {
		print "<div style='height:100%; overflow:auto;'><table border='0' width='100%'>";
		foreach ( $UsersInfo as $element ) {
			$stat = "";
			$cardType = "";
			if ($iauc ['userId'] == $element ['id']) {
				$stat = $iauc ['statusA'];
				$cardType = $iauc ['cardforView'];
			}
			$forCapUrl = $element ['active'] == '1' ? "'editUserData.php?id=" . $element ['id'] . "'" : "''";
			$forFioUrl = $element ['active'] == '1' ? "'gamer.php?id=" . $element ['id'] . "'" : "''";
			$state = $element ['active'] != '1' ? "(Не активен)" : "";
			print "<tr style='background-color:silver;'><td colspan='3'><a href=" . $forCapUrl . " target='_blank'>";
			print "<img align='right' src='img/" . $capColorReferences [$element ['capColor']] . "' title='Кликните для редактирования' border='0'></a>";
			print "<img align='right' src='img/cross_red.png' onclick='removeUser(\"" . operPage . "?id=" . $element ['id'] . "&operId=removeUser" . "\", \"" . $element ['FIO'] . "\")' style='width:15px;position:relative;left:45px;cursor:pointer;' title='Удалить игрока'>";
			print "<p><b><i><a href=" . $forFioUrl . " target='_blank'>" . $element ['FIO'] . $state . "</a></i></b></p></td></tr>";
			print "<tr><td >Показать карт.:</td><td align='right' colspan='2'>" . ShowSelectCard ( $element ['id'], $cardType ) . "</td></tr>";
			if ($iauc ['isActive'] == $element ['id']) {
				printCheckBox ( $element ['id'], "img/chchecked.gif", "checked" );
			} else {
				printCheckBox ( $element ['id'], "img/chclear.gif", "" );
			}
			if ($iac ['isActive'] == $element ['id']) {
				printCheckBoxCube ( $element ['id'], "img/chchecked.gif", "checked", $iac ['status'], $iac ['result'] );
			} else {
				printCheckBoxCube ( $element ['id'], "img/chclear.gif", "", $iac ['result'] );
			}
			if (! isset ( $element ['commonR'] ) || strLen ( $element ['commonR'] ) == 0)
				$element ['commonR'] = 0;
			if (! isset ( $element ['activeIncomeGreenCircle'] ) || strLen ( $element ['activeIncomeGreenCircle'] ) == 0)
				$element ['activeIncomeGreenCircle'] = 0;
			if (! isset ( $element ['passIncomeAllCircle'] ) || strLen ( $element ['passIncomeAllCircle'] ) == 0)
				$element ['passIncomeAllCircle'] = 0;
			print "<tr><td colspan='3'>";
			print "<table width='100%' border='1' style='border:solid; border-color:black; border-collapse: collapse;'>";
			print "<tr align='center' style='border:solid;'><td style='border:solid; padding:5px;'><font size='-1'>Активный доход<br>(зеленый круг)</font></td><td style='padding:5px;'><font size='-1'>Пассивный доход<br>(все круги)</font></td></tr>";
			print "<tr align='center' style='border:solid;'><td style='border:solid; padding:10px;'>" . $element ['activeIncomeGreenCircle'] . "</td><td style='padding:10px;'>" . $element ['passIncomeAllCircle'] . "</td></tr>";
			print "<tr style='border:solid;'><td align='center' colspan='2'><font size='+2'>общий Ресурс: " . $element ['commonR'] . "</font></td></tr>";
			print "</table>";
			print "</td></tr>";
			print "<tr><td colspan='3'>" . printPaySystem ( $element, true ) . "</td>";
			print "<tr><th colspan='3' style='border-color:silver; border-style:solid; border-radius: 10px 10px 10px 10px;'><div id='card_" . $element ['id'] . "'>" . $stat . "</div></th></tr>";
		}
		print "</table></div>";
		// print_r (getInfoAboutShowedCard());
	} else if ($ViewType == 1) {
		print "<table width='100%' style='border-collapse: collapse' border='0'>";
		foreach ( $EnToRusUserAttributes as $atrName => $atrValue ) {
			if ($atrName == "FIO") {
				$parm = "style='background-color:silver; font-style:italic'";
			} else {
				$parm = "";
			}
			print "<tr $parm><td style='border:solid; border-color:white'>" . $atrValue . "</td>";
			for($i = 0; $i <= count ( $UsersInfo ) - 1; $i ++) {
				if ($atrName == "talants") {
					$text = $UsersInfo [$i] ["cbManager"] . " " . $UsersInfo [$i] ["cbUrist"] . " " . $UsersInfo [$i] ["cbEconomic"] . " " . $UsersInfo [$i] ["cbIngeneer"] . " " . $UsersInfo [$i] ["cbDoctor"] . " " . $UsersInfo [$i] ["cbTourist"] . " " . $UsersInfo [$i] ["cbTeacher"] . " " . $UsersInfo [$i] ["cbDoner"];
					print "<td style='border:solid; border-color:white'>" . $text . "</td>";
				} else {
					print "<td style='border:solid; border-color:white'>" . $UsersInfo [$i] [$atrName] . "</td>";
				}
			}
			print "</tr>";
		}
		print "</table>";
	}
}

// проверка выбранности checkbox`a и вывод chcked
function TryCheck($name, $value) {
	if ($name == $value) {
		return print "checked";
	}
}

// записывает измененные атрибуты указанные в $changedFilds
function WriteAttrib($arrAttrib, $changedFilds) {
	if (count ( $changedFilds ) != 0) {
		new Parse ( dataSourceType, xmlForUserData, $xml, true );
		$xml->SearchNode ( $xml->RootNode, "user", "id", $arrAttrib ['id'] );
		if ($xml->SearchedNodeLink != null) {
			$map = array ();
			foreach ( $changedFilds as $name ) {
				if (strlen ( $name ) != 0) {
					$arrAttrib [$name] = str_replace ( array (
							"\r\n",
							"\r",
							"\n" 
					), " ", $arrAttrib [$name] );
					$map [$name] = $arrAttrib [$name];
				}
			}
			$xml->setAttribute ( $xml->SearchedNodeLink, $map );
			$xml->SaveInFile ( $xml->Nfile );
		}
		$xml->Destroy ();
	}
}
// заполняем поля формы и переданного массива
function fillCardValuesFomPost($post) {
	print "<script> $(document).ready(function(){";
	foreach ( $post as $key => $value ) {
		if (strlen ( $value ) != 0)
			print "setValue('" . $key . "', '" . $value . "');";
	}
	print "})</script>";
}

// генерация карточки по передаваемому в функцию префиксу изображения
function RandCard($pref, $index = null) {
	$mask = "img/card/" . $pref . "*.jpg";
	$fileList = array ();
	foreach ( glob ( $mask ) as $fn ) {
		$fileList [] = $fn;
	}
	$randNum = $index ? $index - 1 : mt_rand ( 0, count ( $fileList ) - 1 );
	print "<img class='card' src='" . $fileList [$randNum] . "?" . date ( "hms" ) . "'>";
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "card", "userId", $_SESSION ['id'] );
	if ($xml->SearchedNodeLink != null) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"cardSelected" => $fileList [$randNum] 
		) );
		$xml->SaveInFile ( $xml->Nfile );
	}
	$xml->Destroy ();
}

// количество файлов с заданным префиксом
function fileCountByPrefix($prefix) {
	return count ( glob ( "img/card/" . $prefix . "*.jpg" ) );
}

// вывод заданного количества <br>
function PrintBrs($count) {
	for($i = 1; $i <= $count; $i ++) {
		// print "<br>";
	}
}

// фиксация пользователя и типа карточки, которые надо ему показать
function setCardForUserSelect($userId, $cardType) {
	new Parse ( dataSourceType, xmlForFlash, $xml );
	$xml->SearchNode ( $xml->RootNode, "card", "cardforView", "" );
	if ($xml->SearchedNodeLink != null) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"cardforView" => $cardType,
				"userId" => $userId,
				"cardSelected" => "" 
		) );
		$xml->SaveInFile ( $xml->Nfile );
	} else {
		$xml->SearchNode ( $xml->RootNode, "card", "userId", $userId );
		if ($xml->SearchedNodeLink != null) {
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"cardforView" => $cardType,
					"cardSelected" => "" 
			) );
			$xml->SaveInFile ( $xml->Nfile );
		} else {
			$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "cardforView" );
			$xml->SearchNode ( $xml->RootNode, "card", "cardforView", $xml->nodesAttribValue [0] );
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"cardforView" => "" 
			) );
			$xml->SaveInFile ( $xml->Nfile );
			setCardForUserSelect ( $userId, $cardType );
		}
	}
	$xml->Destroy ();
}

// возвращает массив информации о показе кубика
function getInfoAboutCube() {
	$result = array ();
	new Parse ( dataSourceType, xmlForFlash, $xml );
	$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "cube", "isActive" );
	if (count ( $xml->nodesAttribValue ) != 0) {
		$result ['userId'] = $xml->nodesAttribValue [0];
		$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "cube", "isActive" );
		$result ['isActive'] = $xml->nodesAttribValue [1];
		$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "cube", "result" );
		$result ['result'] = $xml->nodesAttribValue [2];
		$xml->Destroy ();
		new Parse ( dataSourceType, xmlForUserData, $xml );
		$xml->SearchNode ( $xml->RootNode, "user", "id", $result ['isActive'] );
		if ($xml->SearchedNodeLink != null) {
			$xml->AttribFromSNL ( "", $temp );
			$xml->Destroy ();
			$result ['FIO'] = $temp ['FIO'];
			$result ['capColor'] = $temp ['capColor'];
			unset ( $temp );
		} else {
			$xml->Destroy ();
		}
		if (strlen ( getCubeValue ( $result ['result'], 0 ) ) == 0 || strlen ( getCubeValue ( $result ['result'], 1 ) ) == 0) {
			if (strlen ( $result ['isActive'] ) == 0) {
				$result ['status'] = "";
			} else {
				$result ['status'] = "Кубики не были брошены";
			}
		} else {
			$cb1 = getCubeValue ( $result ['result'], 0 );
			$cb2 = getCubeValue ( $result ['result'], 1 );
			$result ['status'] = "Кубик" . ($cb1 == 'NaN' || $cb2 == 'NaN' ? "" : "и") . " брошен" . ($cb1 == 'NaN' || $cb2 == 'NaN' ? "" : "ы") . " игроком " . $result ['FIO'] . ($cb1 != 'NaN' ? ".<br> Значение кубика №1 = " . $cb1 : '') . ($cb2 != 'NaN' ? "<br> Значение кубика №2 = " . $cb2 : '');
		}
		if (strlen ( $result ['isActive'] ) == 0) {
			$result ['isActive'] = null;
		}
	} else {
		$xml->Destroy ();
	}
	return $result;
}

// возвращает массив инвормации о пользователе и типе карточи, которую ему показывают
function getInfoAboutShowedCard() {
	$result = array ();
	new Parse ( dataSourceType, xmlForFlash, $xml );
	$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "userId" );
	if (count ( $xml->nodesAttribValue ) != 0) {
		$result ['userId'] = $xml->nodesAttribValue [0];
		$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "cardforView" );
		$result ['cardforView'] = $xml->nodesAttribValue [1];
		$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "cardSelected" );
		$result ['cardSelected'] = $xml->nodesAttribValue [2];
		$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "isActive" );
		$result ['isActive'] = $xml->nodesAttribValue [3];
		$xml->Destroy ();
		new Parse ( dataSourceType, xmlForUserData, $xml );
		$xml->SearchNode ( $xml->RootNode, "user", "id", $result ['userId'] );
		if ($xml->SearchedNodeLink != null) {
			$xml->AttribFromSNL ( "", $temp );
			$result ['FIO'] = $temp ['FIO'];
			$result ['capColor'] = $temp ['capColor'];
			unset ( $temp );
		}
		$xml->Destroy ();
		new Parse ( dataSourceType, xmlForUserData, $xml );
		$xml->SearchNode ( $xml->RootNode, "user", "id", $result ['isActive'] );
		if ($xml->SearchedNodeLink != null) {
			$xml->AttribFromSNL ( "", $temp );
			$result ['actFIO'] = $temp ['FIO'];
			$result ['actcapColor'] = $temp ['capColor'];
		}
	}
	$xml->Destroy ();
	if (strlen ( $result ['cardSelected'] ) == 0) {
		$result ['status'] = "Карточка в процессе выбора.";
		$result ['click'] = "Выберите карточку";
		$result ['statusA'] = "Карточка в процессе выбора.";
	} else {
		$title = "Карточка была выбрана игроком: " . $result ['FIO'] . ", который играет фишкой с цветом: \"" . $result ['capColor'] . "\".";
		$result ['status'] = "<img class='card' style='cursor:pointer' src='" . $result ['cardSelected'] . "' title='" . $title . "' onClick=\"vote('operation.php?hideCard=yes&idUser=" . $result ['userId'] . "&side=gamer', 'vote_status')\">";
		$result ['statusA'] = "<img class='card' style='cursor:pointer' src='" . $result ['cardSelected'] . "' title='" . $title . "' onClick=\"vote('operation.php?hideCard=yes&idUser=" . $result ['userId'] . "&side=admin', 'card_" . $result ['userId'] . "')\">";
	}
	if ($result ['cardSelected'] == $result ['cardforView']) {
		$result ['status'] = "";
		$result ['statusA'] = "";
	}
	return $result;
}

// по имени карточки возвращает её русское название
function GetRusNameCard($src) {
	global $cardsSettings;
	$i = 0;
	while ( $cardsSettings [$i] ['imgFile'] !== $src ) {
		$i ++;
	}
	return $cardsSettings [$i] ['name'];
}

// таблица доходов всех пользователей
function commonUserMoney() {
	$info = getAllInfoAboutUsers ();
	$result = "<table border='1' width='100%' style='border-color:silver; border-style:solid; border-radius: 10px 10px 10px 10px;'>";
	$result .= "<tr align='center' style='background-color:silver;'><td>ФИО</td><td>АД</td><td>ПД</td><td>R</td></tr>";
	foreach ( $info as $user ) {
		$result .= "<tr><td style='background-color:silver;'>" . $user ['FIO'] . "</td>";
		$result .= "<td>" . $user ['activeIncomeGreenCircle'] . "</td>";
		$result .= "<td>" . $user ['passIncomeAllCircle'] . "</td>";
		$result .= "<td>" . $user ['commonR'] . "</td></tr>";
	}
	return $result .= "</table>";
}

// показывает карточку пользователю которому необходимо сделать выбор
// или показывет выбранную другим пользователем карточку
function ShowCardForUserSelect($userInfo) {
	$temp = getInfoAboutShowedCard ();
	$cap = "";
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "cap", "idUser", $_SESSION ['id'] );
	if ($xml->SearchedNodeLink != null) {
		$xml->AttribFromSNL ( "", $cap );
	}
	if ($temp ['isActive'] == $userInfo ['id']) {
		print "<script>document.getElementById('hod').innerHTML=\"<img align='middle' width='60' src='img/you_hod.gif?" . time () . "' width='100%' title='Ваш ход'>\";</script>";
	} else if ($temp ['isActive'] != null && $temp ['isActive'] !== "") {
		print "<font color='green'><u><b>Очередь ходить:</b></u></font> " . $temp ['actFIO'] . "</br><font color='green'><u><b>Цвет фишки:</b></u></font> " . $temp ['actcapColor'] . "<hr>";
	}
	print "<div id='wrapper'>
		<ul class='tabs tabs1'>
			<li class='t1 tab-current'><a>Карточка</a></li>
			<li class='t2'><a>Доход и ресурсы игроков</a></li>
		</ul>
		<div class='t1' style='background-color:white;'>";
	// если текущий пользователь должен выбирать карточку
	if ($temp ['userId'] == $userInfo ['id']) {
		// если карточку он еще не выбрал
		if (strlen ( $temp ['cardSelected'] ) > 0) {
			$action = "";
		} else {
			$count = fileCountByPrefix ( substr ( $temp ['cardforView'], 0, - 4 ) . "_" );
			$action = getScriptHtml ( "userRefreshStop(); showField(" . $count . ", '" . substr ( $temp ['cardforView'], 0, - 4 ) . "', '" . GetRusNameCard ( $temp ['cardforView'] ) . "')" );
		}
		
		print "<table border='0' width='100%'>";
		if ($action == "")
			$temp ['click'] = $temp ['status'];
		print "<tr>	<td id='selCard' class='selCard' colspan='3'><div id='vote_status' height='30'>" . ($cap ['result'] !== "hideCard" ? $temp ['click'] : "") . "</div></td></tr>";
		print "<tr><td class='card'>";
		// print "<a name='".substr($temp['cardforView'], 0, -4)."_' ".$action.">";
		if ($action !== "") {
			print $action;
		}
		print "</a></td></table>";
		
		print "</div>";
	} else {
		print "<table border='0' width='100%'>";
		// print "<th align='center' colspan='3'>Карточка</th>";
		print "<tr>	<td class='selCard' colspan='3'><div id='vote_status' height='30'>" . ($cap ['result'] !== "hideCard" ? $temp ['status'] : "") . "</div></td></tr>";
		print "</table>";
		print "</div>";
	}
	print "<div class='t2' style='padding:10 10 10 10; background-color:white;'>";
	print commonUserMoney ();
	print "</div></div>" . showCubeForSelect ( $userInfo ['id'] );
	// print_r ($temp);
}

// контролл для показа выбора кубика
function showCubeForSelect($userId) {
	$cubeInfo = getInfoAboutCube ();
	$str = "";
	if ($cubeInfo ['isActive'] == $userId) {
		if (strlen ( $cubeInfo ['result'] ) == 0) {
			$script = getScriptHtml ( "cubeChooser('" . $userId . "', this);" );
			$str .= "<p align='center'>Бросьте кубики</p>" . $script . "<div id='cube'></div>";
		} else {
			$str = getCubeValueDescription ( getCubeValue ( $cubeInfo ['result'], 0 ), getCubeValue ( $cubeInfo ['result'], 1 ) );
		}
	} else {
		if (strlen ( $cubeInfo ['isActive'] ) != 0) {
			$str .= "<p align='left'>" . $cubeInfo ['status'] . "</p>";
		}
	}
	return $str;
}

// рандомим кубик
function randCube($userId, $presetRandNum = null) {
	$str = "";
	$randNum = $presetRandNum == null ? mt_rand ( 1, 6 ) . "_" . mt_rand ( 1, 6 ) : $presetRandNum;
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "cube", "isActive", $userId );
	$xml->setAttribute ( $xml->SearchedNodeLink, Array (
			"result" => $randNum 
	) );
	$xml->SaveInFile ( $xml->Nfile );
	$xml->Destroy ();
	$randNum = explode ( "_", $randNum );
	print getCubeValueDescription ( $randNum [0], $randNum [1] );
}

/**
 * Возвращает изображения кубиков по выбранным значениям
 * 
 * @param Int $cb1
 *        	- значение кубика 1
 * @param Int $cb2
 *        	- значение кубика 2
 * @return string - html показывающий кубики и их описание
 */
function getCubeValueDescription($cb1, $cb2) {
	$format = "<p align='center'>%s %s</p><div id='cube'>%s%s</div>";
	$str = "";
	if ($cb1 != 'NaN' && $cb2 == 'NaN') {
		$str .= sprintf ( $format, "<i>Значение кубика 1</i> - <font size='+1'>[" . $cb1 . "]</font>", "", "<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/" . $cb1 . ".gif' align='left'>", "" );
	} else if ($cb2 != 'NaN' && $cb1 == 'NaN') {
		$str .= sprintf ( $format, "", "<i>Значение кубика 2</i> - <font size='+1'>[" . $cb2 . "]</font>", "", "<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/" . $cb2 . ".gif' align='right'>" );
	} else {
		$str .= sprintf ( $format, "<i>Значение кубика 1</i> - <font size='+1'>[" . $cb1 . "]</font>", "<i>Значение кубика 2</i> - <font size='+1'>[" . $cb2 . "]</font>", "<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/" . $cb1 . ".gif' align='left'>", "<img style='border-radius: 10px 10px 10px 10px; border-color:silver; border-style:solid' src='img/cube/" . $cb2 . ".gif' align='right'>" );
	}
	return $str;
}

// установить активного пользователя
function setActiveUser($action, $userId) {
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "card", "userId" );
	if ($action == "true") {
		$xml->SearchNode ( $xml->RootNode, "card", "userId", $xml->nodesAttribValue [0] );
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"isActive" => $userId 
		) );
	} else if ($userId !== "") {
		$xml->SearchNode ( $xml->RootNode, "card", "userId", $xml->nodesAttribValue [0] );
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"isActive" => "" 
		) );
	}
	$xml->SaveInFile ( $xml->Nfile );
	$xml->Destroy ();
}

// установить пользователя которому показываем кубик
function setCubeUser($action, $userId) {
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	$xml->GetNodesAttribsValuesByName ( $xml->RootNode, "cube", "userId" );
	if ($action == "true") {
		$xml->SearchNode ( $xml->RootNode, "cube", "userId", $xml->nodesAttribValue [0] );
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"isActive" => $userId,
				"result" => "" 
		) );
	} else if ($userId !== "") {
		$xml->SearchNode ( $xml->RootNode, "cube", "userId", $xml->nodesAttribValue [0] );
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				"isActive" => "",
				"result" => "" 
		) );
	}
	$xml->SaveInFile ( $xml->Nfile );
	$xml->Destroy ();
}

// плата/получение
function setPayValue($userId, $attribute, $value, $lastAction) {
	new Parse ( dataSourceType, xmlForUserData, $xml, true );
	$xml->SearchNode ( $xml->RootNode, "user", "id", $userId );
	if ($xml->SearchedNodeLink != null) {
		$xml->setAttribute ( $xml->SearchedNodeLink, Array (
				$attribute => $value,
				"lastAction" => $lastAction 
		) );
		$xml->SaveInFile ( $xml->Nfile );
	}
	$xml->Destroy ();
	print $value;
}

// сброс выбранной карты
function resetCard($idUser, $side = "gamer") {
	new Parse ( dataSourceType, xmlForFlash, $xml, true );
	if ($side == "admin") {
		$xml->SearchNode ( $xml->RootNode, "card", "userId", $idUser );
		if ($xml->SearchedNodeLink != null) {
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"cardforView" => "",
					"cardSelected" => "",
					"userId" => "" 
			) );
			$xml->SaveInFile ( $xml->Nfile );
		}
		$xml->execQuery ( "UPDATE `" . $xml->tableName () . "` SET `result`=NULL WHERE `tag`='cap'" );
		print "Карточка скрыта";
	} else {
		$xml->SearchNode ( $xml->RootNode, "cap", "idUser", $_SESSION ['id'] );
		if ($xml->SearchedNodeLink != null) {
			$xml->setAttribute ( $xml->SearchedNodeLink, Array (
					"result" => "hideCard" 
			) );
			$xml->SaveInFile ( $xml->Nfile );
		}
		print "Карточка скрыта";
	}
	$xml->Destroy ();
}

// вывод истории игры
function getUserHistory($userInfo) {
	$arraySize = count ( $userInfo );
	$i = 0;
	while ( $i < $arraySize && strlen ( $userInfo ['h_time_' . $i] ) != 0 ) {
		
		++ $i;
	}
	$str = "<input type='hidden' value='" . $i . "'><TABLE bgcolor='#FFFFFF' border='1' bordercolorlight='#C0C0C0' bordercolordark='#808080' cellspacing='0'>";
	$str .= "<TR valign='top'>";
	$str .= "<TD width='148' bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Время</div></div></TD>";
	$str .= "<TD width=162 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Что произошло</div></div></TD>";
	$str .= "<TD width=219 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Состояние</div></div></TD>";
	$str .= "<TD width=160 bgcolor='#C0C0C0'><div class='wpmd'><div align=center>Выводы</div></div></TD></TR>";
	$common = $i;
	$i = 0;
	while ( $i <= $common ) {
		if ($i == $common) {
			$values = array (
					"",
					"",
					"",
					"" 
			);
		} else {
			$values = array (
					$userInfo ['h_time_' . $i],
					$userInfo ['h_happend_' . $i],
					$userInfo ['h_state_' . $i],
					$userInfo ['h_solve_' . $i] 
			);
		}
		$str .= "<TR>";
		$str .= "<TD width='148' bgcolor='#C0C0C0'>";
		$str .= "<input name='h_time_" . ($i) . "' type='text' value='" . $values [0] . "' onChange='addChagedElement(this.name)' OnFocus='setDate(this)'></TD>";
		$str .= "<TD width='162' bgcolor='#C0C0C0'>";
		$str .= "<input name='h_happend_" . ($i) . "' type='text' value='" . $values [1] . "' onChange='addChagedElement(this.name)'></TD>";
		$str .= "<TD width='219' bgcolor='#C0C0C0'>";
		$str .= "<input style='width:219' name='h_state_" . ($i) . "' type='text' value='" . $values [2] . "' onChange='addChagedElement(this.name)'></TD>";
		$str .= "<TD width='160' bgcolor='#C0C0C0'>";
		$str .= "<input name='h_solve_" . ($i) . "' type='text' value='" . $values [3] . "' onChange='addChagedElement(this.name)'></TD>";
		$str .= "</TR>";
		++ $i;
	}
	$str .= "</TABLE>";
	return $str;
}
function checkPresenterActive($data) {
	global $presenterAttribs;
	new Parse ( dataSourceType, xmlForPresenters, $xml, true );
	// $xml = new ParseXML(xmlForPresenters);
	$xml->SearchNode ( $xml->RootNode, $presenterAttribs ['node'], "password", $data ['password'] );
	if ($xml->SearchedNodeLink != null) {
		$xml->AttribFromSNL ( "", $vis );
		if ($vis ['active'] == 'true') {
			$now = strtotime ( date ( "d-m-Y" ) );
			$dateBegin = strtotime ( $vis ['dateBegin'] );
			$dateEnd = strtotime ( $vis ['dateEnd'] );
			if ($now >= $dateBegin && $now <= $dateEnd) {
				if ($data ['password'] == $vis ['password']) {
					$vis ['status'] = 'OK';
				} else {
					$vis ['status'] = 'Не верный пароль';
				}
			} else {
				$vis ['status'] = 'Уточните период действия аккаунта для ' . $vis ['fio'];
			}
		} else {
			$vis ['status'] = 'Аккаунт ' . $vis ['fio'] . ' не активен. Обратитесь к администратору';
		}
	} else {
		$vis ['status'] = "Пользователь с таким паролем не существует в выбранной игре.";
	}
	$xml->Destroy ();
	return $vis;
}
function showPresenterInfo($userId, $password) {
	$info = checkPresenterActive ( array (
			"userId" => $userId,
			"password" => $password 
	) );
	if ($info ['status'] != 'OK') {
		$_SESSION['presenterCode'] = "";
		print "<script>alert('" . $info ['status'] . "');</script>"; // document.location.replace('".page404."');</script>
	} else {
		$dat = calcDatePeriod ( null, $_SESSION ['dateEnd'] );
		print "<li class='t4'><u>Активный ведущий: " . $info ['fio'] . ". Осталось - " . $dat ['day'] . "д/" . $dat ['hours'] . "ч/" . $dat ['minutes'] . "м/" . $dat ['seconds'] . "с/";
	}
}
function saveAndLoadPresenterInfo($postData = Array()) {
	$vis = checkPresenterActive ( array (
			"userId" => $_SESSION ['presenterUnic'],
			"password" => $_SESSION ['presenterCode'] 
	) );
	if ($vis ['status'] != 'OK') {
		print "<script>alert('" . $vis ['status'] . "');document.location.replace('" . page404 . "');</script>";
	}
	if (count ( $postData ) != 0) {
		if ($postData ['password'] == "{@}|{@}" || strlen ( $postData ['password'] ) == 0) {
			unset ( $postData ['password'] );
		} else {
			$postData ['password'] = md5 ( $postData ['password'] );
		}
		global $presenterAttribs;
		$atttrValues = makeAttribArray ( $postData, $presenterAttribs );
		new Parse ( dataSourceType, xmlForPresenters, $xml, true );
		$xml->SearchNode ( $xml->RootNode, 'presenter', 'id', $_SESSION ['presenterUnic'] );
		if ($xml->SearchedNodeLink != null) {
			$xml->ModifyElement ( "presenter", $atttrValues, $xml->SearchedNodeLink );
		}
		$xml->Destroy ();
		new Parse ( dataSourceType, xmlForPresenters, $xml );
		$xml->SearchNode ( $xml->RootNode, 'presenter', 'id', $_SESSION ['presenterUnic'] );
		$xml->AttribFromSNL ( "", $vis );
		$xml->Destroy ();
	}
	$_SESSION ['presenterCode'] = $vis ['password'];
	$_SESSION ['presenterUnic'] = $vis ['id'];
	return $vis;
}
function calcDatePeriod($begin, $end) {
	if ($begin == null) {
		$start_date = mktime ();
	} else {
		$start_date = strtotime ( $begin );
	}
	$end_date = strtotime ( $end );
	
	$sec = $end_date - $start_date;
	$days = floor ( $sec / 86400 );
	$hours = floor ( ($sec - $days * 86400) / 3600 );
	$minutes = floor ( ($sec - $days * 86400 - $hours * 3600) / 60 );
	$seconds = $sec - $days * 86400 - $hours * 3600 - $minutes * 60;
	$counter = Array (
			"day" => $days,
			"hours" => $hours,
			"minutes" => $minutes,
			"seconds" => $seconds 
	);
	return $counter;
}
function getCubeValue($result, $index) {
	$res = explode ( "_", $result );
	return strlen ( $res [$index] ) != 0 ? $res [$index] : "";
}
function getScriptHtml($js, $readyObject = "document") {
	$script = "<script>";
	$script .= "$(".$readyObject.").ready(function (){";
	$script .= $js;
	$script .= "});";
	$script .= "</script>";
	return $script;
}

function getAttribs($attributes, $id) {
	new Parse ( dataSourceType, xmlForUserData, $xml );
	$xml->SearchNode ( $xml->RootNode, "user", "id", $id);
	if ($xml->SearchedNodeLink != null) {
		$xml->AttribFromSNL ( "", $vis);
		if (count($vis)>0){
			$res = array();
			foreach($attributes as $attr){
				$res[$attr] = $vis[$attr];
			}
			return json_encode($res);
		} else {
			return json_encode(array());
		}
	}
}

function getUserInfo($id){
	$info = getAllInfoAboutUsers();
	if ($id != 'all'){
		for ($index = 0;$index<count($info);++$index){
			if ($info[$index]['id'] == $id){
				return $info[$index];
			}
		}
		return array();
	} else {
		return $info;
	}
}

?>
