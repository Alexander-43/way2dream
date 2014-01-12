<?php
include ('vars.inc');
include ('domXml.inc');
include ('external.php');
include ('func.php');
if ($_SESSION['authKey']!=accessCode && strlen($_SESSION['presenterCode']) == 0)
{
	print "<script> alert('Для вас доступ к странице запрещен,\\n зарегистрируйтесь или войдите как ведущий.');";
	print "window.location.replace('index.php');</script>";
}
if ( ((int)$_GET['source']>= 1) && ((int)$_GET['source']<= 6))
{
	UpdateCapValues("cap_".$_GET['source'], $_GET['PosX'], $_GET['PosY']);
	if (in_array(1, $Except))
	{
		print "Ошибка обновления координат фишки №".$_GET['source'];
	}
}
if (count($_POST) != 0 && empty($_FILES))
{
	$_SESSION = array_merge($_SESSION, saveAndLoadPresenterInfo($_POST));
	$_SESSION['presenterCode'] = $_SESSION['password'];
}
upload($_FILES);
?>
<html xmlns="http://www.w3.org/1999/xhtml" style="width:100%; height:100%; overflow:hidden;">
<head>
	<title>Страница ведущего </title>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<meta http-equiv="Expires" content="Mon, 26 Jul 1997 05:00:00 GMT" /> 
	<meta http-equiv="Pragma" content="no-cache" />
	<script type="text/javascript" src="js/jquery.min.js"></script>
	<script type="text/javascript" src="js/jquery.scrollTo-min.js"></script>
	<script type="text/javascript" src="js/jquery-ui.min.js"></script>
	<script type="text/javascript" src="js/ddslick.min.js"></script>
	<script type="text/javascript" src="js/utils.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
	<script type="text/javascript" src="js/managegame.js"></script>
	<?php includeGlobalComponentJS(); ?>
	<link rel="stylesheet" type="text/css" href="style.css">
<style>
/* <![CDATA[ */

* {margin: 0; padding: 0;}
body {margin: 10px; font: 13px/1.5 "Trebuchet MS", Tahoma, Arial;}
a {color: blue;}
p {padding: 7px 0;}
h1 {font-size: 20px; margin: 0 0 30px;}
#wrapper {width: 100%; height: 100%}

/* tabs */
ul.tabs {
	height: 25px;
	line-height: 25px;
	margin: 0 0 3px;
	list-style: none;
}
* html ul.tabs {margin-bottom: 0;}
ul.tabs li {
	float: left;
	margin-right: 1px;
}
ul.tabs li a {
	display: block;
	padding: 0 13px 1px;
	margin-bottom: -1px;
	color: #444;
	text-decoration: none;
	cursor: pointer;
	background: #F9F9F9;
	border: 1px solid #EFEFEF;
	border-bottom: 1px solid #F9F9F9;
	position: relative;
}
* html ul.tabs li a {float: left}
*+html ul.tabs li a {float: left}
ul.tabs li a:hover {
	color: #F70;
	padding: 0 13px;
	background: #FFFFDF;
	border: 1px solid #FFCA95;
}
ul.tabs li.tab-current a {
	color: #444;
	background: #EFEFEF;
	padding: 0px 13px 2px;
	border: 1px solid #DDD;
	border-bottom: 1px solid #EFEFEF;
}
div.t2,
div.t3,
div.t4,
div.t5 {
	display: none;
}
div.t1,
div.t2,
div.t3,
div.t4,
div.t5 {
	border: 1px solid #DDD;
	background: #EFEFEF;
	padding: 0 10px;
}
img {
	cursor:pointer;
}
img.action_icon{
	cursor:pointer;
	width:32px;
	height:32px;
}
img.action_icon_small{
	cursor:pointer;
	width:16px;
	height:16px;
}
/* end tabs */

/* ]]> */
</style>
</head>
<body onLoad="onLoad();">
<? printBrs(5); ?>
<center>
<div id="wrapper">

	<ul class="tabs tabs1">
		<li class="t1 tab-current"><a>Управление игрой</a></li>
		<li class="t2"><a>Даные игроков</a></li>
		<!--li class="t3"><a>Архив игроков</a></li-->
		<? if (strlen($_SESSION['presenterCode']) != 0 ) showPresenterInfo($_SESSION['presenterUnic'], $_SESSION['presenterCode']); ?>
		<li class="t5"><a>Восстановление</a></li>
	</ul>

	<div class="t1" style="padding:0">
		<? if ($_GET['tab'] == 't1' || strlen($_GET['tab']) == 0) {include('inc/presenter/gamecontrol.inc');} ?>
	</div>
	<div class="t2" style="overflow-y: auto; height:96%">
		<? if ($_GET['tab'] == 't2'){showActiveGamers(1);} ?> 
	</div>
	<div class="t3" align="left">
		<? //ShowFileInDir(folderBaseArchive); ?> 
	</div>
	<div class="t4">
		<? if (strlen($_SESSION['presenterCode']) != 0 && $_GET['tab'] == 't4') {include ('inc/presenter/presenterinfo.inc');} ?>
	</div>
	<div class="t5" style="height:96%">
		<? if ($_GET['tab'] == 't5'){include ('inc/presenter/managegame.inc');}?>
	</div>
</div>
</center>
<? 
if (strlen($_GET['tab']) > 0){
	print "<script>
	$(document).ready(function() {
		$('div.t1').hide();
		$('div.".$_GET['tab']."').show();
		$('ul.tabs.tabs1 li').removeClass('tab-current');
		$('ul.tabs.tabs1 li.".$_GET['tab']."').addClass('tab-current');
	});
	</script>";
}
 ?>
</body>
</html>