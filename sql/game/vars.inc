<?php
	header("Content-Type: text/html; charset=utf-8");
	session_start();
	define("root", dirname(__FILE__));
	if(strrpos(root, "/") > 0){
		define("slash", "/");
	}else {
		define("slash", "\\");
	}
	//error_reporting(1);
	define("xmlFolder","xml/");
	define("mysqlFolder", "mysql/");
	define("incFolder", "inc/");
	
	include_once incFolder.'localeResolver/index.inc';
	$blr = new BrowserLocalResolver();
	$clr = new CookieLocalResolver();
	if ($clr->getLocale() == null){
		print '<script>var GLOBAL_DEFAULT_LOCALE_VALUE="'.$blr->getLocale().'";</script>';
		define("currentLocale", $blr->getLocale());
	} else {
		define("currentLocale", $clr->getLocale());
	}
	
	define("messageFileName", "messages/".currentLocale.".ini");
	include_once incFolder.'config-loader/index.inc';
	$ini = new IniConfig(messageFileName);
	print("<script>var GLOBAL_MSG=".json_encode($ini->getAll(),true).";</script>");
	include_once incFolder.'localeResolver/index.inc';
	$messages = new Message($ini);
	define("swfFolder","swf/".currentLocale."/");
	define("xmlForFlash", xmlFolder."cap_settings.xml");
	define("xmlForUserData", xmlFolder."game_base.xml");
	define("xmlForPresenters", xmlFolder."presenters.xml");
	define("xmlGenerator", "xmlGen.php");
	define("maxBaseSize", 20);
	define("emptyBaseXmlFile", "gameBase");
	define("folderBaseArchive", "gameBaseArchive");
	define("accessCode","21232f297a57a5a743894a0e4a801fc3");
	define("columnOfArchFile", 3);
	define("operPage", "operation.php");
	define("page404", "http://www.google.com");
	define("way2dream","http://way2dream.ru/");
	define("dataSourceType","mysql");
	define('encoding','utf8_general_ci');
	define('tableType', 'MyISAM');
	define('logging', false);
	define('logTable', 'log_table');
	define('maxRows', 25000);
	$baseTables[xmlForUserData]['description'] = xmlForUserData." - основная таблица для хранения данных пользователей";
	$baseTables[xmlForUserData]['sql'] = "CREATE TABLE `[*tableName*]` (
		`id` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`tag` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`email` TINYTEXT NULL DEFAULT '' COLLATE '".encoding."',
		`skype` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`FIO` TINYTEXT NULL DEFAULT '' COLLATE '".encoding."',
		`capColor` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`active` TINYTEXT NULL DEFAULT '' COLLATE '".encoding."',
		`date` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`tempId` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`description` TINYTEXT NULL DEFAULT '' COLLATE '".encoding."') 
		COLLATE='".encoding."' ENGINE=".tableType;
	$baseTables[xmlForFlash]['description'] = xmlForFlash." - таблица информации о фишках";
	$baseTables[xmlForFlash]['sql'] = "CREATE TABLE `[*tableName*]` (
		`id` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`tag` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`tempId` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`name` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`posX` VARCHAR(5) NULL DEFAULT '' COLLATE '".encoding."',
		`posY` VARCHAR(5) NULL DEFAULT '' COLLATE '".encoding."',
		`visible` VARCHAR(8) NULL DEFAULT '' COLLATE '".encoding."',
		`idUser` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`color` VARCHAR(15) NULL DEFAULT '' COLLATE '".encoding."',
		`userId` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`cardforView` VARCHAR(255) NULL DEFAULT '' COLLATE '".encoding."',
		`cardSelected` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`isActive` VARCHAR(50) NULL DEFAULT '' COLLATE '".encoding."',
		`result` VARCHAR(20) NULL DEFAULT '' COLLATE '".encoding."'
		) COLLATE='".encoding."' ENGINE=".tableType;
	
	$baseTables[xmlForFlash]['inserts'] = "INSERT INTO `[*tableName*]` VALUES 
		(rand(), 'cap', null, 'cap_1', '-1', '-1', 'false', null, 'синий', null, null, null, null, null),
		(rand(), 'cap', null, 'cap_2', '-1', '-1', 'false', null, 'желтый', null, null, null, null, null),
		(rand(), 'cap', null, 'cap_3', '-1', '-1', 'false', null, 'пурпурный', null, null, null, null, null),
		(rand(), 'cap', null, 'cap_4', '-1', '-1', 'false', null, 'зеленый', null, null, null, null, null),
		(rand(), 'cap', null, 'cap_5', '-1', '-1', 'false', null, 'голубой', null, null, null, null, null),
		(rand(), 'cap', null, 'cap_6', '-1', '-1', 'false', null, 'красный', null, null, null, null, null),
		('card', 'card', null, null, null, null, null, null, null, null, null, null, null, null),
		('cube', 'cube', null, null, null, null, null, null, null, null, null, null, null, null)";
	$baseTables[xmlForPresenters]['description'] = xmlForPresenters." - таблица хранения информации о ведущих игры";
	$baseTables[xmlForPresenters]['sql'] = "CREATE TABLE `[*tableName*]` (
		`id` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`tag` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`fio` VARCHAR(250) NULL DEFAULT NULL COLLATE '".encoding."',
		`email` VARCHAR(250) NULL DEFAULT NULL COLLATE '".encoding."',
		`dateBegin` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`dateEnd` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`active` VARCHAR(250) NULL DEFAULT NULL COLLATE '".encoding."',
		`password` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`skype` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`tempId` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."',
		`action` VARCHAR(50) NULL DEFAULT NULL COLLATE '".encoding."') 
		COLLATE='".encoding."' ENGINE=".tableType;
	$baseTables[logTable]['description'] = logTable." - таблица для логирования";
	$baseTables[logTable]['sql'] = "CREATE TABLE `".logTable."` (
	`counter` INT(10) NOT NULL AUTO_INCREMENT,
	`data` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
	`comment` TEXT NOT NULL, PRIMARY KEY (`counter`)
	) COLLATE='".encoding."' ENGINE=".tableType;
	$capColorReferences = array (
								"синий"=>"img_1.gif", 
								"желтый"=>"img_2.gif",
								"пурпурный"=>"img_3.gif",
								"зеленый"=>"img_4.gif",
								"голубой"=>"img_5.gif",
								"красный"=>"img_6.gif",
								"img_1.gif"=>"синий",
								"img_2.gif"=>"желтый",
								"img_3.gif"=>"пурпурный",
								"img_4.gif"=>"зеленый",
								"img_5.gif"=>"голубой",
								"img_6.gif"=>"красный"
								);
								
	$EnToRusUserAttributes = array (
									"FIO"=>$messages->msg("attributes_labels.FIO"),
									"email"=>$messages->msg("attributes_labels.email"),
									"skype"=>$messages->msg("attributes_labels.skype"),
									"date"=>$messages->msg("attributes_labels.date"),
									"dream"=>$messages->msg("attributes_labels.dream"),
									"Code"=>$messages->msg("attributes_labels.Code"),
									"moneyFromParent"=>$messages->msg("attributes_labels.moneyFromParent"),
									"bornSource"=>$messages->msg("attributes_labels.bornSource"),
									"pasIncomeBlueCircle"=>$messages->msg("attributes_labels.pasIncomeBlueCircle"),
									"pasIncomeGreenCircle"=>$messages->msg("attributes_labels.pasIncomeGreenCircle"),
									"commonR"=>$messages->msg("attributes_labels.commonR"),
									"credit"=>$messages->msg("attributes_labels.credit"),
									"creditTBegin"=>$messages->msg("attributes_labels.creditTBegin"),
									"creditTEnd"=>$messages->msg("attributes_labels.creditTEnd"),
									"strahOtFM"=>$messages->msg("attributes_labels.strahOtFM"),
									"strahOtMR"=>$messages->msg("attributes_labels.strahOtMR"),
									"bisnesAbaks_1"=>$messages->msg("attributes_labels.bisnesAbaks_1"),
									"bisnesAbaks_2"=>$messages->msg("attributes_labels.bisnesAbaks_2"),
									"bisnesBbaks_1"=>$messages->msg("attributes_labels.bisnesBbaks_1"),
									"bisnesBbaks_2"=>$messages->msg("attributes_labels.bisnesBbaks_2"),
									"bisnesCbaks_1"=>$messages->msg("attributes_labels.bisnesCbaks_1"),
									"bisnesCbaks_2"=>$messages->msg("attributes_labels.bisnesCbaks_2"),
									"bisnesAProc_1"=>$messages->msg("attributes_labels.bisnesAProc_1"),
									"bisnesAProc_2"=>$messages->msg("attributes_labels.bisnesAProc_2"),
									"bisnesBProc_1"=>$messages->msg("attributes_labels.bisnesBProc_1"),
									"bisnesBProc_2"=>$messages->msg("attributes_labels.bisnesBProc_2"),
									"bisnesCProc_1"=>$messages->msg("attributes_labels.bisnesCProc_1"),
									"bisnesCProc_2"=>$messages->msg("attributes_labels.bisnesCProc_2"),
									"bisnesAPasIncome_1"=>$messages->msg("attributes_labels.bisnesAPasIncome_1"),
									"bisnesAPasIncome_2"=>$messages->msg("attributes_labels.bisnesAPasIncome_2"),
									"bisnesBPasIncome_1"=>$messages->msg("attributes_labels.bisnesBPasIncome_1"),
									"bisnesBPasIncome_2"=>$messages->msg("attributes_labels.bisnesBPasIncome_2"),
									"bisnesCPasIncome_1"=>$messages->msg("attributes_labels.bisnesCPasIncome_1"),
									"bisnesCPasIncome_2"=>$messages->msg("attributes_labels.bisnesCPasIncome_2"),
									"bisnesAR_1"=>$messages->msg("attributes_labels.bisnesAR_1"),
									"bisnesAR_2"=>$messages->msg("attributes_labels.bisnesAR_2"),
									"bisnesBR_1"=>$messages->msg("attributes_labels.bisnesBR_1"),
									"bisnesBR_2"=>$messages->msg("attributes_labels.bisnesBR_2"),
									"bisnesCR_1"=>$messages->msg("attributes_labels.bisnesCR_1"),
									"bisnesCR_2"=>$messages->msg("attributes_labels.bisnesCR_2"),
									"statAbaks_1"=>$messages->msg("attributes_labels.statAbaks_1"),
									"statAbaks_2"=>$messages->msg("attributes_labels.statAbaks_2"),
									"statBbaks_1"=>$messages->msg("attributes_labels.statBbaks_1"),
									"statBbaks_2"=>$messages->msg("attributes_labels.statBbaks_2"),
									"statCbaks_1"=>$messages->msg("attributes_labels.statCbaks_1"),
									"statCbaks_2"=>$messages->msg("attributes_labels.statCbaks_2"),
									"statAproc_1"=>$messages->msg("attributes_labels.statAproc_1"),
									"statAproc_2"=>$messages->msg("attributes_labels.statAproc_2"),
									"statBproc_1"=>$messages->msg("attributes_labels.statBproc_1"),
									"statBproc_2"=>$messages->msg("attributes_labels.statBproc_2"),
									"statCproc_1"=>$messages->msg("attributes_labels.statCproc_1"),
									"statCproc_2"=>$messages->msg("attributes_labels.statCproc_2"),
									"statApasIncome_1"=>$messages->msg("attributes_labels.statApasIncome_1"),
									"statApasIncome_2"=>$messages->msg("attributes_labels.statApasIncome_2"),
									"statBpasIncome_1"=>$messages->msg("attributes_labels.statBpasIncome_1"),
									"statBpasIncome_2"=>$messages->msg("attributes_labels.statBpasIncome_2"),
									"statCpasIncome_1"=>$messages->msg("attributes_labels.statCpasIncome_1"),
									"statCpasIncome_2"=>$messages->msg("attributes_labels.statCpasIncome_2"),
									"promA"=>$messages->msg("attributes_labels.promA"),
									"promB"=>$messages->msg("attributes_labels.promB"),
									"promC"=>$messages->msg("attributes_labels.promC"),
									"prof"=>$messages->msg("attributes_labels.prof"),
									"zp"=>$messages->msg("attributes_labels.zp"),
									"profSource"=>$messages->msg("attributes_labels.profSource"),
									"study"=>$messages->msg("attributes_labels.study"),
									"childrens"=>$messages->msg("attributes_labels.childrens"),
									"exprUp"=>$messages->msg("attributes_labels.exprUp"),
									"prop1"=>$messages->msg("attributes_labels.prop1"), 
									"prop2"=>$messages->msg("attributes_labels.prop2"), 
									"prop3"=>$messages->msg("attributes_labels.prop3"), 
									"prop4"=>$messages->msg("attributes_labels.prop4"), "prop5"=>$messages->msg("attributes_labels.prop5"), "prop6"=>$messages->msg("attributes_labels.prop6"),
									"res1"=>$messages->msg("attributes_labels.res1"), "res2"=>$messages->msg("attributes_labels.res2"), "res3"=>$messages->msg("attributes_labels.res3"),
									"res4"=>$messages->msg("attributes_labels.res4"), "res5"=>$messages->msg("attributes_labels.res5"), "res6"=>$messages->msg("attributes_labels.res6"),
									"res7"=>$messages->msg("attributes_labels.res7"), "res8"=>$messages->msg("attributes_labels.res8"), "res9"=>$messages->msg("attributes_labels.res9"), "res10"=>$messages->msg("attributes_labels.res10"),
									"talants"=>$messages->msg("attributes_labels.talants")
									);
	
	$cardsSettings = Array (
							array ("multi"=>"", "size"=>"size='1'"),
							array ("name" => $messages->msg("gamer_page.chooseCard"), "imgFile" => "null", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.possibillity"), "imgFile" => "possible.jpg", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.bussinesNews"), "imgFile" => "marketNews.jpg", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.work"), "imgFile" => "work.jpg", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.family"), "imgFile" => "famaly.jpg", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.study"), "imgFile" => "study.jpg", "isSelected" => ""),
							array ("name" => $messages->msg("cardSettings.forceMajor"), "imgFile" => "forceM.jpg", "isSelected" => "")
							);
	$presenterAttribs = Array ("node"=>"presenter", "unic"=>"id", "fio"=>"", "email"=>"", "dateBegin"=>"", "dateEnd"=>"", "active"=>"", "password"=>"", "skype"=>"");
	$userAttribsMinimal = Array ("node"=>"user", "unic"=>"id", "FIO"=>"", "email"=>"", "skype"=>"", "active"=>"");
	$messagePresAttrib = Array("[*title*]", "[*fio*]", "[*url*]", "[*game_name*]");
	$messagePresTemplate = "<html>
							<head>
								<title>[*title*]</title>
							</head>
							<body>
								<h1>Уважаемый, [*fio*].</h1> 
								Уведомляем вас о том, 
								что вы добавлены в игру <a href='".way2dream."'>'Путь к мечте'</a> как ведущий.<br>
								Имя вашей игры на странице авторизации \"[*game_name*]\"<br>
								Для перехода к игре нажмите <a href='[*url*]'>сюда</a>
							</body>
						</html>
						";
	$mailParams = Array("subject"=>"no-reply", "from"=>"test@mail.ru");
?>