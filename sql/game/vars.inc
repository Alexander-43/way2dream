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
									"FIO"=>"Атрибуты",
									"email"=>"Email",
									"skype"=>"Skype",
									"date"=>"Дата регистрации",
									"dream"=>"Мечта",
									"Code"=>"Код",
									"moneyFromParent"=>"Доход от родителей",
									"bornSource"=>"Ресурс рождения",
									"pasIncomeBlueCircle"=>"Пассивный доход\n(красный и синий круги)",
									"pasIncomeGreenCircle"=>"Пассивный доход\n+зарплата(зеленый круг)",
									"commonR"=>"Общий R",
									"credit"=>"Кредит",
									"creditTBegin"=>"Время начала кредита",
									"creditTEnd"=>"Время окончания кредита",
									"strahOtFM"=>"Срахование от Ф.М.",
									"strahOtMR"=>"Страхование от минусов рынка",
									"bisnesAbaks_1"=>"1.Бизнес А ($)",
									"bisnesAbaks_2"=>"2.Бизнес А ($)",
									"bisnesBbaks_1"=>"1.Бизнес B ($)",
									"bisnesBbaks_2"=>"2.Бизнес B ($)",
									"bisnesCbaks_1"=>"1.Бизнес C ($)",
									"bisnesCbaks_2"=>"2.Бизнес C ($)",
									"bisnesAProc_1"=>"1.Бизнес А (%)",
									"bisnesAProc_2"=>"2.Бизнес А (%)",
									"bisnesBProc_1"=>"1.Бизнес B (%)",
									"bisnesBProc_2"=>"2.Бизнес B (%)",
									"bisnesCProc_1"=>"1.Бизнес C (%)",
									"bisnesCProc_2"=>"2.Бизнес C (%)",
									"bisnesAPasIncome_1"=>"1.Бизнес А (пассивный доход)",
									"bisnesAPasIncome_2"=>"2.Бизнес А (пассивный доход)",
									"bisnesBPasIncome_1"=>"1.Бизнес B (пассивный доход)",
									"bisnesBPasIncome_2"=>"2.Бизнес B (пассивный доход)",
									"bisnesCPasIncome_1"=>"1.Бизнес C (пассивный доход)",
									"bisnesCPasIncome_2"=>"2.Бизнес C (пассивный доход)",
									"bisnesAR_1"=>"1.Бизнес A (R)",
									"bisnesAR_2"=>"2.Бизнес A (R)",
									"bisnesBR_1"=>"1.Бизнес B (R)",
									"bisnesBR_2"=>"2.Бизнес B (R)",
									"bisnesCR_1"=>"1.Бизнес C (R)",
									"bisnesCR_2"=>"2.Бизнес C (R)",
									"statAbaks_1"=>"1.Недвижимость A ($)",
									"statAbaks_2"=>"2.Недвижимость A ($)",
									"statBbaks_1"=>"1.Недвижимость B ($)",
									"statBbaks_2"=>"2.Недвижимость B ($)",
									"statCbaks_1"=>"1.Недвижимость C ($)",
									"statCbaks_2"=>"2.Недвижимость C ($)",
									"statAproc_1"=>"1.Недвижимость A (%)",
									"statAproc_2"=>"2.Недвижимость A (%)",
									"statBproc_1"=>"1.Недвижимость B (%)",
									"statBproc_2"=>"2.Недвижимость B (%)",
									"statCproc_1"=>"1.Недвижимость C (%)",
									"statCproc_2"=>"2.Недвижимость C (%)",
									"statApasIncome_1"=>"1.Недвижимость A (пасивный доход)",
									"statApasIncome_2"=>"2.Недвижимость A (пасивный доход)",
									"statBpasIncome_1"=>"1.Недвижимость B (пасивный доход)",
									"statBpasIncome_2"=>"2.Недвижимость B (пасивный доход)",
									"statCpasIncome_1"=>"1.Недвижимость C (пасивный доход)",
									"statCpasIncome_2"=>"2.Недвижимость C (пасивный доход)",
									"promA"=>"Акции А",
									"promB"=>"Акции В",
									"promC"=>"Акции C",
									"prof"=>"Профессия",
									"zp"=>"з/п",
									"profSource"=>"Ресурс профессии",
									"study"=>"Образование",
									"childrens"=>"Дети",
									"exprUp"=>"Фраза поддержки",
									"prop1"=>"Цель 1", "prop2"=>"Цель 2", "prop3"=>"Цель 3", 
									"prop4"=>"Цель 4", "prop5"=>"Цель 5", "prop6"=>"Цель 6",
									"res1"=>"Ресурс 1", "res2"=>"Ресурс 2", "res3"=>"Ресурс 3",
									"res4"=>"Ресурс 4", "res5"=>"Ресурс 5", "res6"=>"Ресурс 6",
									"res7"=>"Ресурс 7", "res8"=>"Ресурс 8", "res9"=>"Ресурс 9", "res10"=>"Ресурс 10",
									"talants"=>"Таланты к деятельности"
									);
	
	$cardsSettings = Array (
							array ("multi"=>"", "size"=>"size='1'"),
							array ("name" => "Выберите карточку", "imgFile" => "null", "isSelected" => ""),
							array ("name" => "Возможность", "imgFile" => "possible.jpg", "isSelected" => ""),
							array ("name" => "Новости рынка", "imgFile" => "marketNews.jpg", "isSelected" => ""),
							array ("name" => "Работа", "imgFile" => "work.jpg", "isSelected" => ""),
							array ("name" => "Семья", "imgFile" => "famaly.jpg", "isSelected" => ""),
							array ("name" => "Учеба", "imgFile" => "study.jpg", "isSelected" => ""),
							array ("name" => "Форс-мажор", "imgFile" => "forceM.jpg", "isSelected" => "")
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