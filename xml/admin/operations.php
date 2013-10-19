<?php
	require(dirname(__FILE__)."/vars.inc");
	require(rootSite."/inc/domXml.inc");
	require(rootSite."/inc/func.inc");
	require(rootSite."/inc/TIniParse.inc");
	function printWithHeader($str)
	{
		header('Content-type: text/json');
		print $str;
		exit;
	}
	if ($_GET['operId']=="getGamesSelect")
	{
	  print getGamesSelect(gamesXml, $_GET['selId']);
	  exit;
	}
	else if ($_GET['operId']=="makeGamesTable")
	{
	  print makeGamesTable(gamesXml);
	  exit;
	}
	else if ($_GET['operId']=='mail')
	{
	  @mail('kerhac@rambler.ru', 'Заголовок письма', 'Текст письма', 'From: admin@eval.net46.net');
	}
	else if ($_GET['operId']=='makePresentersTable')
	{
	  print makePresentersTable($_GET['gameUrl']);
	  exit;
	}
	else if ($_GET['operId'] == 'setState')
	{
	  printWithHeader(updateValueOfObject($_POST['data']));
	}
	else if($_GET['operId'] == 'getCapColorSelect')
	{
	  printWithHeader(getCapColorSelect($_GET['url'], $_GET['id'], $_GET['free']));
	}
	else if($_GET['operId'] == 'makeGamersTable')
	{
	  printWithHeader(makeGamersTable($_GET['url']));
	}
	else if($_GET['operId'] == 'delElement')
	{
	  printWithHeader(deleteElem($_GET));
	}
	else if ($_GET['operId'] == 'trycopy')
	{
	  printWithHeader(trycopy($_GET));
	}
	else if ($_GET['operId'] == 'updateGame'){
	  printWithHeader(updateGame($_GET));
	}
	else
	{
		header('HTTP/1.1 500 Internal Server Error');
		print "Server error. Wrong parametrs !!!!";
		exit;
	}
?>

