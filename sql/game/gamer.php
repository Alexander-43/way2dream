<?php 
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	print("<script>var GLOBAL_MSG=".json_encode($ini->getAll()).";</script>");
	if (strlen($_GET['id']) != 0 || strlen($_SESSION['authKey']) != 0) 
	{
		if (strlen($_GET['id']) != 0)
		{
			$_SESSION['id'] = $_GET['id'];
		}else
		{
			if (strlen($_SESSION['id']) == 0){
				print "<script> alert('".$messages->msg("errors.accessDenied")."');";
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
			print $messages->msg("errors.updateXYCap", array($_POST['source']));
		}
	}
	
	print '<script>var GLOBAL_LOCALE_COOKIE_NAME = "'.CookieLocalResolver::COOKIE_LOCALE_NAME.'"; </script>';
	
?>
<html>
<head>
	<title><?php print $messages->msg("gamer_page.title"); ?> </title>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/ddslick.min.js"></script>
	<script type="text/javascript" src="js/jquery.cookie.min.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
	<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
<div id="boxes">
<span id="closeDialog_card" onclick="$('#dialog_card').fadeOut(500);$('#mask').fadeOut(500);$(this).fadeOut(1)"><?php print $messages->msg("gamer_page.hide"); ?> [ Х ]</span>
<span id="closeDialog_cube" onclick="$('#dialog_cube').fadeOut(500);$('#mask').fadeOut(500);$(this).fadeOut(1)"><?php print $messages->msg("gamer_page.hide"); ?> [ Х ]</span>
	<div id="dialog_cube" class="window">
		<span id="dialog_header_cube"><?php print $messages->msg("gamer_page.chooseOneOfCard"); ?></span><br><br>
		<table id="tSource" border="0" style="min-width: 390px; border-spacing: 0px; display:none;">
			<tr>
				<td width="50%" valign="top">
					<table width="100%" style="border-right-style: solid;">
						<caption><b><?php print $messages->msg("gamer_page.chooseCube", array("1")); ?></b></caption>
						<tr><td id="tSource_td_left" align="center"></td></tr>
					</table>
				</td>
				<td width="50%" valign="top">
					<table width="100%">
						<caption><b><?php print $messages->msg("gamer_page.chooseCube", array("2")); ?></b></caption>
						<tr><td id="tSource_td_right" align="center"></td></tr>
					</table>
				</td>
			</tr>
		</table>
	</div>
	<div id="dialog_card" class="window">
	<span id="dialog_header_card"><?php print $messages->msg("gamer_page.chooseOneOfCard"); ?></span><br><br>
		<div id="dSource" class="fixed">
			<a id="aSource">1</a>
		</div>
	</div>
	
	<div id="mask"></div>
</div>
<? printBrs(5); ?>
<table width="100%" height="100%" border="0">
<tr height="300px">
	<td valign="top">
	<? ShowRunStopObject($_POST['timer'], $_POST['state']); 
	   InfoAboutUser($_SESSION);
	?>
	</td>
	<td align="top" width="68%" rowspan="2" style="background: url(img/loading.gif) center no-repeat;">
		<object type="application/x-shockwave-flash" data="<? print swfFolder;?>gamer.swf" width="100%" height="100%">
		<param name="movie" value="<? print swfFolder;?>gamer.swf" />
		<param name="wmode" value="opaque" />
		<param name="salign" value="r">
		<param name="allowScriptAccess" value="sameDomain" />
		<param name="flashvars" value="pathToXmlBase=<? print xmlGenerator."%3F".time() ?>&submitUrl=gamer.php" />
		<EMBED src="<? print swfFolder;?>gamer.swf" FLASHVARS="submitUrl=gamer.php&pathToXmlBase=<? print xmlGenerator."%3F".time() ?>" quality="high" wmode="transparent" WIDTH="100%" HEIGHT="100%" TYPE="application/x-shockwave-flash">
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
<div id="language"></div>
</body>
</html>