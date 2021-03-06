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
		RandCard($_GET['pref'], $_GET['index']);
	}
	if ($_GET['randcard']=="Off")
	{
		setCardForUserSelect($_GET['userId'], $_GET['cardType']);
		print $messages->msg("gamer_page.cardInProgress");
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
		resetCard($_GET['idUser'], $_GET['side']);
	}
	//рандомить кубик
	if ($_GET['randCube'] == "yes")
	{
		if ($_GET['randNum']){
			$explod = explode("_", $_GET['randNum']);
			if ($explod[0] && $explod[1]){
				randCube($_GET['userId'], $_GET['randNum']);
			}
		} else {
			randCube($_GET['userId']);
		}
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
	  $_SESSION['id'] = "";
	  print "<script>document.location.replace('presenter.php');</script>";
	}
	if ($_GET['operId'] == 'sendMail')
	{
		printForRemote(sendMail($_GET['data']));
	}
	if ($_GET['operId'] == 'removeUser'){
		printForRemote(removeUser($_GET['id']));
	}
	
	if ($_POST['operId'] == 'getAttribs'){
		printForRemote(getAttribs($_POST['attribs'], $_POST['id']));
	}
	if ($_GET['operId'] == 'getUserInfo'){
		printForRemote(json_encode(getUserInfo($_GET['id'])));
	}
	
?>