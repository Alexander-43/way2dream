<?php
	include ('vars.inc');
	include ('domXml.inc');
	include ('func.php');
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<title>Добро пожаловать </title>
	<meta http-equiv="content-type" content="text/html; charset=UTF-8" />
	<link href="style.css" type="text/css" rel="stylesheet" />
	<link rel="shortcut icon" href="favicon.ico">
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/tab.js"></script>
</head>

<body>
<? printBrs(5); ?>
<center>
<div id="wrapper">

	<ul class="tabs tabs1">
		<li class="t1 tab-current"><a>Игрок</a></li>
		<li class="t2"><a>Ведущий</a></li>
	</ul>

	<div class="t1" align="center">
		<br>
		<form name="gamerReg" method="post" action="saveData.php">
		<table>
		<tr>
			<td align="left">Фамилия Имя Отчество</td>
			<td><input name="FIO" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td align="left">Имя пользователя Skype</td>
			<td><input name="skype" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td align="left">E-mail</td>
			<td><input name="email" type="text" value="" onMouseOver="gamerReg.but.disabled='';"></td>
		</tr>
		<tr>
			<td colspan="2" align="left"><u>Выберите цвет фишки:<u></td>
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
			<input name="but" type="submit" value=" Сохранить " onMouseOver="validFormData();" onFocus="validFormData();"></td>
		</tr>
			<tr>
			<td colspan="2"><font color="red">*</font> <font size="-2" color="green"><u>Для игры рекомендуется использовать браузер Opera ...</u></font></td>
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
			Код доступа
			<input name="admCode" type="password" value="">
			<input name="but" type="submit" value=" Вход ">
		</form>
			<br>
	</div>

</div>
</center>
</body>
</html>