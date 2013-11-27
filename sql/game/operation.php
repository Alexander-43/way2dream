<?php
header("Content-Type: text/html; charset=utf-8");
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	include (incFolder.'external.inc');
	function printForRemote($object)
	{
		makeHeader();
		print $object;
		exit;
	}
	//обработчик новой игры
	if ($_GET['source']=="newGame")
	{
		StartNewGame();
		print "<script> window.history.back();</script>";
	}
	//для Ajax запроса карточки для вывода
	if ($_GET['randcard']=="On" && $_GET['pref'] != "null")
	{
		RandCard($_GET['pref']);
	}
	if ($_GET['randcard']=="Off")
	{
		setCardForUserSelect($_GET['userId'], $_GET['cardType']);
		print "Карточка в процессе выбора";
	}
	//устанавливаем активного пользователя
	if ($_GET['isActive'] == "true" || $_GET['isActive'] == "false")
	{
		if ($_GET['action']=="hod")
		{
			setActiveUser($_GET['isActive'], $_GET['userId']);
		}
		else
		{
			setCubeUser($_GET['isActive'], $_GET['userId']);
		}
	}
	//действия с доходом и ресурсами
	if ($_GET['doPay'] == "do")
	{
		setPayValue($_GET['userId'], $_GET['atribute'], $_GET['value'], $_GET['lastAction']);
	}
	//генерирование нового кода доступа
	if ($_GET['generate'] == "true")
	{
		genHash($_GET['str']);
	}
	//сброс карточки
	if ($_GET['hideCard'] == "yes")
	{
		resetCard($_GET['idUser']);
	}
	//рандомить кубик
	if ($_GET['randCube'] == "yes")
	{
		randCube($_GET['userId']);
	}
	// возвращает ведущих для select
	if ($_GET['operId'] == "getPresentersSelect")
	{
		printForRemote(getPresenters(xmlForPresenters, "true", "select", "ln"));
	}
	if ($_GET['operId'] == "getAllPresenters")
	{
		printForRemote(getPresenters(xmlForPresenters, null, "", null));
	}
	//проверка подключения
	if ($_GET['operId'] == 'testConnection')
	{
		printForRemote(getHashGameFolder($_GET['url']));
	}
	//возвращает игроков
	if ($_GET['operId'] == 'getGamers')
	{
		printForRemote(getGamers(xmlForUserData, @json_decode(str_replace('\\', '',$_GET['data']), true)));
	}
	//Обновляет состояние объекта
	if ($_GET['operId'] == 'updateObject')
	{
		printForRemote(updateObject($_GET['data']));
	}
	//возвращает фишки
	if ($_GET['operId'] == 'getCaps')
	{
		printForRemote(getCapColor(xmlForFlash, $_GET['onlyFree']));
	}
	if ($_GET['operId'] == 'remoteAuth')
	{
	  printForRemote(remoteAuth($_GET['userId'], $_GET['password']));
	}
	if ($_GET['operId'] == 'remoteEnter')
	{
	  $_SESSION['presenterCode'] = $_GET['password'];
	  $_SESSION['presenterUnic'] = $_GET['userId'];
	  $_SESSION = array_merge($_SESSION, saveAndLoadPresenterInfo());
	  print "<script>document.location.replace('presenter.php');</script>";
	}
	if ($_GET['operId'] == 'sendMail')
	{
		printForRemote(sendMail($_GET['data']));
	}
	
?>