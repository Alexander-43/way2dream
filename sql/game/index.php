<?php
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	
	print '<script>var GLOBAL_LOCALE_COOKIE_NAME = "'.CookieLocalResolver::COOKIE_LOCALE_NAME.'"; </script>';
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<title><?php print $messages->msg("login_page.title"); ?></title>
	<meta http-equiv="content-type" content="text/html; charset=UTF-8" />
	<link href="css/style.css" type="text/css" rel="stylesheet" />
	<link rel="shortcut icon" href="favicon.ico">
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/ddslick.min.js"></script>
	<script type="text/javascript" src="js/jquery.cookie.min.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
</head>

<body>
<? printBrs(5); ?>
<center>
<table>
<tr>
	<td width="360px">
<div id="wrapper">

	<ul class="tabs tabs1">
		<li class="t1 tab-current"><a><?php print $messages->msg("login_page.tabGamerLabel"); ?></a></li>
		<li class="t2"><a><?php print $messages->msg("login_page.tabPresenterLabel"); ?></a></li>
	</ul>

	<div class="t1" align="center">
		<br>
		<form name="gamerReg" method="post" action="saveData.php">
		<table>
		<tr>
			<td align="left"><?php print $messages->msg("login_page.fio"); ?></td>
			<td><input name="FIO" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td align="left"><?php print $messages->msg("login_page.skype"); ?></td>
			<td><input name="skype" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td align="left"><?php print $messages->msg("login_page.mail"); ?></td>
			<td><input name="email" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td colspan="2" align="left"><u><?php print $messages->msg("login_page.color"); ?><u></td>
		</tr>
		<tr>
			<td align="center" colspan="2">
			<br>
			<?
				printImg();
			?>
			</td>
		</tr>
		<tr>
			<td align="center" colspan="2">
			<br>
			<input name="but" type="submit" value=" <?php print $messages->msg("buttons.save"); ?> " onMouseOver="validFormData();" onFocus="validFormData();"></td>
		</tr>
			<tr>
			<td colspan="2"><font color="red">*</font> <font size="-2" color="green"><u><?php print $messages->msg("login_page.comment"); ?></u></font></td>
		</tr>
		</table>
		<br>
		<input name="capColor" type="hidden" value="">
		<input name="dataValid" type="hidden" value="">
		</form>
	</div>

	<div class="t2">
		<form name="presEnter" method="post" action="saveData.php">
			<br>
			<?php print $messages->msg("login_page.accessCode"); ?>
			<input name="admCode" type="password" value="">
			<input name="but" type="submit" value=" <?php print $messages->msg("buttons.enter"); ?> ">
		</form>
			<br>
	</div>

</div>
</td>
</tr>
</table>
</center>
<div id="language"></div>
</body>
</html>