<?
	header("Content-Type: text/html; charset=utf-8");
	require(dirname(__FILE__)."/vars.inc");
	require(dirname(__FILE__)."/inc/domXml.inc");
	require(dirname(__FILE__)."/inc/pclzip.lib.inc");
	require(dirname(__FILE__)."/inc/func.inc");
	require(dirname(__FILE__)."/inc/TIniParse.inc");
	checkAuth($_SESSION);
?>
<html style="overflow:hidden;">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<link rel="stylesheet" type="text/css" href="css/css.css">
	<link rel="stylesheet" type="text/css" href="css/tcal.css">
	<link rel="stylesheet" type="text/css" href="css/paging.css">
	<link rel="stylesheet" type="text/css" href="css/tabs.css">
</head>
	<body style="margin: 20px 0px 0px 0px; height:100%;" onLoad="">
		<script type="text/javascript" src="script/functions.js"></script>
		<script type="text/javascript" src="script/jq.js"></script>
		<script type="text/javascript" src="script/tcal.js"></script>
		<table height="97%" width="100%" border="0">
			<tr>
				<td width="15 %" valign="top">
					<div class="leftMenu" onClick="document.location='?page=1'">Игры</div>
					<div class="leftMenu" onClick="document.location='?page=2'">Ведущие</div>
					<div class="leftMenu" onClick="document.location='?page=3'">Игроки</div>
					<div class="leftMenu" onClick="document.location='?page=4'">Настройки</div>
					<div class="leftMenu" onClick="document.location='?page=5'">Обратная связь</div>
				</td>
				<td width="85 %" valign="top">
					<?
						switch ($_GET['page'])
						{
							case 1 : GAMES($_POST); break;
							case 2 : PRESENTERS($_POST); break;
							case 3 : GAMERS($_POST);break;
							case 4 : SETTINGS($_POST); break;
							case 5 : REQUEST($_POST);break;
							case "": print "<title>Управление игровым процессом</title><h1 align='center'>Страница управления играми и ведущими</h1>";
						}
					?>
				</td>
			</tr>
			<tr id="downer" height="20">
				<td colspan='2' align="center">
					<div id="status">
					  
					</div>
					<script>
					try {
					    $(document).ready(function() {
					    $('ul.tabs li').css('cursor', 'pointer');
					    $('ul.tabs.tabs1 li').click(function(){
						    var thisClass = this.className.slice(0,2);
						    $('div.t1').hide('slow');
						    $('div.t2').hide('slow');
						    $('div.t3').hide('slow');
						    $('div.t4').hide('slow');
						    $('div.' + thisClass).show('slow');
						    $('ul.tabs.tabs1 li').removeClass('tab-current');
						    $(this).addClass('tab-current');
						    });
					    });
					    } catch(e){ }
					</script>
				</td>
			</tr>
		</table>
	</body
</html>
<?php

?>