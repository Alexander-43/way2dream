<?php 
	include ('vars.inc');
	include ('domXml.inc');
	include ('func.php');
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
	
?>
<style>
a{text-decoration:none}
a:link{color:gray; font-style:normal}
a:hover {font-size:14px; font-style:italic; background-color:silver; color:white}
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

</style>
<html>
<head>
	<title>Страница игрока </title>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<? printBrs(5); ?>
<table width="100%" height="100%" border="0">
<tr height='50%'>
	<td valign="middle">
	<? ShowRunStopObject($_POST['timer'], $_POST['state']); 
	   InfoAboutUser($_SESSION);
	?>
	</td>
	<td align="top" width="70%" rowspan="2" style="background: url(img/loading.gif) center no-repeat;">
		<object type="application/x-shockwave-flash" data="gamer.swf" width="100%" height="100%">
		<param name="movie" value="gamer.swf" />
		<param name="wmode" value="opaque" />
		<param name="salign" value="r">
		<param name="allowScriptAccess" value="sameDomain" />
		<param name="flashvars" value="pathToXmlBase=<? print xmlGenerator."?".time() ?>" />
		<EMBED src="gamer.swf" FLASHVARS="pathToXmlBase=<? print xmlGenerator."?".time() ?>" quality="high" wmode="transparent" WIDTH="100%" HEIGHT="100%" TYPE="application/x-shockwave-flash">
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