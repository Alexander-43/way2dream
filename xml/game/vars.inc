<?php
	header("Content-Type: text/html; charset=utf-8");
	session_start();
	//error_reporting(1);
	define("xmlFolder","xml");
	define("swfFolder","swf");
	define("xmlForFlash", xmlFolder."/capSettings.xml");
	define("xmlForUserData", xmlFolder."/gameBase.xml");
	define("xmlForPresenters", xmlFolder."/presenters.xml");
	define("tempFolder", "temp");
	define("maxBaseSize", 20);
	define("emptyBaseXmlFile", "xml/gameBase");
	define("folderBaseArchive", "gameBaseArchive");
	define("accessCode","21232f297a57a5a743894a0e4a801fc3");
	define("columnOfArchFile", 3);
	define("operPage", "operation.php");
	define("page404", "http://www.google.com");
	define("way2dream","http://way2dream.ru/");
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
									"capColor"=>"Цвет фишки",
									"date"=>"Дата регистрации",
									"dream"=>"Мечта",
									"code"=>"Код",
									"prop1"=>"Цель 1", "prop2"=>"Цель 2", "prop3"=>"Цель 3", 
									"prop4"=>"Цель 4", "prop5"=>"Цель 5", "prop6"=>"Цель 6",
									"res1"=>"Ресурс 1", "res2"=>"Ресурс 2", "res3"=>"Ресурс 3",
									"res4"=>"Ресурс 4", "res5"=>"Ресурс 5", "res6"=>"Ресурс 6",
									"res7"=>"Ресурс 7", "res8"=>"Ресурс 8", "res9"=>"Ресурс 9", "res10"=>"Ресурс 10",
									"exprUp"=>"Фраза поддержки",
									"childrensCount"=>"Дети",
									"childrens"=>"Ресурс детей",
									"credit"=>"Кредит",
									"prom"=>"Акции",
									"creditTBegin"=>"Накопительное страхование t нач.",
									"creditTEnd"=>"Накопительное страхование t оконч.",
									"riskStrah"=>"Рисковое страхование t.нач",
									"bisnesAbaks_1"=>"1.Бизнес А (вклад)",
									"bisnesAbaks_2"=>"2.Бизнес А (вклад)",
									"bisnesAbaks_3"=>"3.Бизнес А (вклад)",
									"bisnesBbaks_1"=>"1.Бизнес B (вклад)",
									"bisnesBbaks_2"=>"2.Бизнес B (вклад)",
									"bisnesBbaks_3"=>"2.Бизнес B (вклад)",
									"bisnesCbaks_1"=>"1.Бизнес C (вклад)",
									"bisnesCbaks_2"=>"2.Бизнес C (вклад)",
									"bisnesCbaks_3"=>"2.Бизнес C (вклад)",
									"bisnesAProc_1"=>"1.Бизнес А (%)",
									"bisnesAProc_2"=>"2.Бизнес А (%)",
									"bisnesAProc_3"=>"3.Бизнес А (%)",
									"bisnesBProc_1"=>"1.Бизнес B (%)",
									"bisnesBProc_2"=>"2.Бизнес B (%)",
									"bisnesBProc_3"=>"3.Бизнес B (%)",
									"bisnesCProc_1"=>"1.Бизнес C (%)",
									"bisnesCProc_2"=>"2.Бизнес C (%)",
									"bisnesCProc_3"=>"3.Бизнес C (%)",
									"bisnesAActIncome_1"=>"1.Бизнес А (активный доход)",
									"bisnesAActIncome_2"=>"2.Бизнес А (активный доход)",
									"bisnesAActIncome_3"=>"3.Бизнес А (активный доход)",
									"bisnesBActIncome_1"=>"1.Бизнес В (активный доход)",
									"bisnesBActIncome_2"=>"2.Бизнес В (активный доход)",
									"bisnesBActIncome_3"=>"3.Бизнес В (активный доход)",
									"bisnesCActIncome_1"=>"1.Бизнес С (активный доход)",
									"bisnesCActIncome_2"=>"2.Бизнес С (активный доход)",
									"bisnesCActIncome_3"=>"3.Бизнес С (активный доход)",
									"bisnesAR_1"=>"1.Бизнес A (Ресурс)",
									"bisnesAR_2"=>"2.Бизнес A (Ресурс)",
									"bisnesAR_3"=>"3.Бизнес A (Ресурс)",
									"bisnesBR_1"=>"1.Бизнес B (Ресурс)",
									"bisnesBR_2"=>"2.Бизнес B (Ресурс)",
									"bisnesBR_3"=>"3.Бизнес B (Ресурс)",
									"bisnesCR_1"=>"1.Бизнес C (Ресурс)",
									"bisnesCR_2"=>"2.Бизнес C (Ресурс)",
									"bisnesCR_3"=>"3.Бизнес C (Ресурс)",
									"statAbaks_1"=>"1.Недвижимость A (Вклад)",
									"statAbaks_2"=>"2.Недвижимость A (Вклад)",
									"statAbaks_3"=>"3.Недвижимость A (Вклад)",
									"statBbaks_1"=>"1.Недвижимость B (Вклад)",
									"statBbaks_2"=>"2.Недвижимость B (Вклад)",
									"statBbaks_3"=>"3.Недвижимость B (Вклад)",
									"statCbaks_1"=>"1.Недвижимость C (Вклад)",
									"statCbaks_2"=>"2.Недвижимость C (Вклад)",
									"statCbaks_3"=>"3.Недвижимость C (Вклад)",
									"statAproc_1"=>"1.Недвижимость A (%)",
									"statAproc_2"=>"2.Недвижимость A (%)",
									"statAproc_3"=>"3.Недвижимость A (%)",
									"statBproc_1"=>"1.Недвижимость B (%)",
									"statBproc_2"=>"2.Недвижимость B (%)",
									"statBproc_3"=>"3.Недвижимость B (%)",
									"statCproc_1"=>"1.Недвижимость C (%)",
									"statCproc_2"=>"2.Недвижимость C (%)",
									"statCproc_3"=>"3.Недвижимость C (%)",
									"franProc"=>"Франшиза (%)",
									"franshiza"=>"Франшиза",
									"franshPasIncome"=>"Пассивный доход",
									"statApasIncome_1"=>"1.Недвижимость A (пасивный доход)",
									"statApasIncome_2"=>"2.Недвижимость A (пасивный доход)",
									"statApasIncome_3"=>"3.Недвижимость A (пасивный доход)",
									"statBpasIncome_1"=>"1.Недвижимость B (пасивный доход)",
									"statBpasIncome_2"=>"2.Недвижимость B (пасивный доход)",
									"statBpasIncome_3"=>"3.Недвижимость B (пасивный доход)",
									"statCpasIncome_1"=>"1.Недвижимость C (пасивный доход)",
									"statCpasIncome_2"=>"2.Недвижимость C (пасивный доход)",
									"statCpasIncome_3"=>"3.Недвижимость C (пасивный доход)",
									"capital"=>"Капитал",
									"capProc"=>"Капитал (%)",
									"capitalPasIncome"=>"Капитал (Пассивный доход)",
									"studyDescription"=>"Образование",
									"activeIncomeGreenCircle"=>"Активный доход(зеленый круг)",
									"passIncomeAllCircle"=>"Пассивный доход (все круги)",
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