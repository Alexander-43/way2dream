<?php 
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	if (strlen($_SESSION['id']) == 0 || strlen($_SESSION['authKey']) != 0) 
	{
		if (strlen($_GET['id']) != 0)
		{
			$_SESSION['id'] = $_GET['id'];
		}else
		{
			if (strlen($_SESSION['id']) == 0){
				print "<script> alert('Для вас доступ к странице запрещен,\\n зарегистрируйтесь или войдите как ведущий.');";
				print "window.location.replace('index.php');</script>";
			}
		}
	}
	//используется в связке с ShowRunStopObject
	if ($_POST['state'] == "0")
	{
		print "<script>TO=setTimeout('document.timerObj.submit()',".($_POST['timer']*1000)."); </script>";
	}
	
	if ( ((int)$_POST['source']>= 1) && ((int)$_POST['source']<= 6))
	{
		UpdateCapValues("cap_".$_POST['source'], $_POST['PosX'], $_POST['PosY']);
		if (in_array(1, $Except))
		{
			print "Ошибка обновления координат фишки №".$_POST['source'];
		}
	}
	
?>
<style>
a{text-decoration:none}
a:link{color:gray; font-style:normal}
//a:hover {font-size:14px; font-style:italic; background-color:silver; color:white}
a:visited{color:gray}
td.card
{
	padding:5px;
	text-align:center;
}
*.selCard
{
	text-align:center; 
	padding:10px;
	border-color:silver;
	border-style:solid;
	border-radius: 10px 10px 10px 10px;
}
img.card
{
	width: 150px;
	cursor:pointer;
}
#mask {
		position:absolute;
		left:0;
		top:0;
		z-index:9000;
		background-color:#000;
		display:none;
		font-family: Georgia;
		width:100%;
		height:100%;
	}
	#boxes .window {
		position:absolute;
		left:0;
		top:0;
		width:460px;
		min-height:150px;
		max-height:310px;
		display:none;
		z-index:9999;
		padding:20px;
		text-align: center;
		font-size: 25px;
		border-radius: 20px 0px 0px 20px;
		  border: solid;
		  border-color: goldenrod;
		  background-color: white;
		  overflow-y:auto;
		  
	}
	boxes #dialog {
		width:375px;
		height:203px;
		padding:10px;
		background-color:#ffffff;
		text-align: center;
	}
	#dSource {
		display : none;
		width:100px;
		height:50px;
		text-align:center;
		vertical-align: middle;
		z-index:1;
		cursor:pointer;
		margin:5px;
	}
	.clear {
		float:clear;
		background-color:gray;
	}
	.fixed{
		display:block;
		float:left;
		background:-webkit-gradient(linear, 0% 0%, 0% 100%, from(#616161), to(#292929));;
		border-radius:15px 15px 15px 15px;
	}
	#dSource:hover {
		background: -webkit-gradient(linear, 0% 0%, 0% 100%, from(#16E720), to(#2F5232));;
	}
	#aSource{
		line-height:50px;
		color:white;
		font-size:30px;
		z-index:0;
	}
	#aSource a:hover {
		line-height:50px;
		color:white;
		font-size:30px;
		z-index:0;
	}

</style>
<html>
<head>
	<title>Страница игрока </title>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
	<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
<div id="boxes">
<span id="closeDialog" style="font-size:10px;font-weight:900;color:white;position:absolute;z-index:99999;cursor:pointer;display:none" onclick="$('#dialog').fadeOut(500);$('#mask').fadeOut(500);$(this).fadeOut(1)">Скрыть [ Х ]</span>
	<div id="dialog" class="window">
		Выберите одну из карточек<br><br>
		<div id="dSource" class="fixed">
			<a id="aSource">1</a>
		</div>
	</div>
	<div id="mask"></div>
</div>
<? printBrs(5); ?>
<table width="100%" height="100%" border="0">
<tr height='50%'>
	<td valign="middle">
	<? ShowRunStopObject($_POST['timer'], $_POST['state']); 
	   InfoAboutUser($_SESSION);
	?>
	</td>
	<td align="top" width="70%" rowspan="2" style="background: url(img/loading.gif) center no-repeat;">
		<object type="application/x-shockwave-flash" data="<? print swfFolder;?>gamer.swf" width="100%" height="100%">
		<param name="movie" value="<? print swfFolder;?>gamer.swf" />
		<param name="wmode" value="opaque" />
		<param name="salign" value="r">
		<param name="allowScriptAccess" value="sameDomain" />
		<param name="flashvars" value="pathToXmlBase=<? print xmlGenerator."?".time() ?>" />
		<EMBED src="<? print swfFolder;?>gamer.swf" FLASHVARS="pathToXmlBase=<? print xmlGenerator."?".time() ?>" quality="high" wmode="transparent" WIDTH="100%" HEIGHT="100%" TYPE="application/x-shockwave-flash">
		</EMBED>
		</object>
	</td>
</tr>
<tr>
	<td align="center" valign="top">
		<? ShowCardForUserSelect($_SESSION); ?>
	</td>
</tr>
</table>
</body>
</html>