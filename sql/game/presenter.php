<?php
include ('vars.inc');
include ('domXml.inc');
include (incFolder.'external.inc');
include (incFolder.'func.inc');
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
if (count($_POST) != 0)
{
	$_SESSION = array_merge($_SESSION, saveAndLoadPresenterInfo($_POST));
    $_SESSION['presenterCode'] = $_SESSION['password'];
}
?>
<html xmlns="http://www.w3.org/1999/xhtml" style="width:100%; height:100%; overflow:hidden;">
<head>
	<title>Страница ведущего </title>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<meta http-equiv="Expires" content="Mon, 26 Jul 1997 05:00:00 GMT" /> 
	<meta http-equiv="Pragma" content="no-cache" />
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
	<link rel="stylesheet" type="text/css" href="css/style.css">
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
div.t4 {
	display: none;
}
div.t1,
div.t2,
div.t3,
div.t4 {
	border: 1px solid #DDD;
	background: #EFEFEF;
	padding: 0 10px;
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
		<li class="t2"><a onClick="jQuery('div.t2').css('height', window.screen.availHeight - 150)">Даные игроков</a></li>
		<!--li class="t3"><a>Архив игроков</a></li-->
		<? if (strlen($_SESSION['presenterCode']) != 0 ) showPresenterInfo($_SESSION['presenterUnic'], $_SESSION['presenterCode']); ?>
	</ul>

	<div class="t1">
	<table width="100 %" height="600"  border="0">
	<tr>
		<td valign="top">
		<? showActiveGamers(0); ?>
		</td>
		<td align="top" width="70%">
		<object type="application/x-shockwave-flash" data="<? print swfFolder;?>presenter.swf" width="100%" height="100%">
		<param name="movie" value="<? print swfFolder;?>presenter.swf" />
		<param name="wmode" value="transparent" />
		<param name="salign" value="t">
		<param name="allowScriptAccess" value="sameDomain" />
		<param name="flashvars" value="pathToXmlBase=<? print xmlGenerator."?".time() ?>&operPage=<? print operPage?>" />
		<EMBED src="<? print swfFolder;?>presenter.swf" FLASHVARS="pathToXmlBase=<? print xmlGenerator."?".time() ?>&operPage=<? print operPage?>" quality="high" wmode="transparent" WIDTH="100%" HEIGHT="100%" TYPE="application/x-shockwave-flash">
		</EMBED>
		</object>
		</td>
	</tr>
	</table>
	</div>
	<div class="t2" style="overflow-y: auto; height:500">
		<? showActiveGamers(1); ?> 
	</div>
	<div class="t3" align="left">
		<? ShowFileInDir(folderBaseArchive); ?> 
	</div>
	<div class="t4">
	<form name='presenterForm' action='#' method='post'>
		<table id='upSide' width='50%' align='center' border='0' height='450'>
			<tr align='left'>
				<td>
					<label>
						<b>ФИО ведущего:</b> 
						<input name='fio' type='text' value='<? print $_SESSION['fio'];?>' title='ФИО ведущего' alt='ФИО ведущего' style='width:100%'>
					</label>
				</td>
			</tr>
			<tr align='left'>
				<td>
					<label>
						<b>Пароль:</b> 
						<input id='randPass' name='password' type='password' value='{@}|{@}' title='Пароль' alt='skip' style='width:100%'>
					</label>
				</td>
			</tr>		
			<tr align='left'>
				<td>
					<label>
						<b>Skype:</b> 
						<input name='skype' type='text' value='<? print $_SESSION['skype'];?>' title='Skype' alt='Skype' style='width:100%'>
					</label>
				</td>
			</tr>		
			<tr align='left'>
				<td>
					<label>
						<b>E-mail:</b> 
						<input name='email' type='text' value='<? print $_SESSION['email'];?>' title='E-mail' alt='E-mail' style='width:100%'>
					</label>
				</td>
			</tr>		
			<tr align='center'>
				<td>
					<table>
						<tr>
							<td>
							<label>
								<b>Дата начала действия: <? print $_SESSION['dateBegin'];?></b>
							</label>
							</td>
							<td>
							<label>
								<b>Дата окончания действия: <? print $_SESSION['dateEnd'];?></b>
							</label>
							</td>						
						</tr>
					</table>
					<? 
						$dat = calcDatePeriod(null, $_SESSION['dateEnd']); 
						print "<br>Время активности вашего акаунта заканчивается через <br>".$dat['day']." дней ".$dat['hours']." часов ".$dat['minutes']." минут ".$dat['seconds']." секунд";
					?>
				</td>
			</tr>
			<tr align='center'>
				<td>
					<input id='presenterFormButton' type='submit' value='Сохранить'>
				</td>
			</tr>
		</table>		
	</form>
	</div>

</div>
</center>
</body>
</html>