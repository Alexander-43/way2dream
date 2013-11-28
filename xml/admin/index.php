<?
	header("Content-Type: text/html; charset=utf-8");
?>
<html id="noScroll">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<link rel="stylesheet" type="text/css" href="css/css.css">
	<link rel="shortcut icon" href="favicon.ico">
</head>
<title>Авторизация</title>
<body id="noScroll">
<script type="text/javascript" src="script/functions.js"></script>
<script type="text/javascript" src="script/jq.js"></script>
<form name="logon" method="post" action="auth.php">
<table width="100%" height="100%">
	<tr>
		<td align="center" valign="middle">
			<table border="0" align="center" style="border-radius: 10px 10px">
				<th id="upper" colspan="2">Форма входа</th>
				<tr>
					<td>
						<b>Выберите тип входа:</b>
					</td>
					<td>
						<select class="forWidth" id="at" name="authType" value="null" onChange="selectAuthType(this, 'tr')">
							<option disabled="true" selected="true">Тип входа</option>
							<option value="presenter">Как ведущий</option>
							<option value="admin">Как админ</option>
						</select>
					</td>
				</tr>
				<tr id="admin" style="display:none;" name="layer">
					<td>
						<b>Пароль:</b>
					</td>
					<td>
						<input class="forWidth" name="adminPass" type="password">
					</td>
				</tr>
				<tr id="presenter" style="display:none;" name="layer">
					<td>
						<b>Игра:</b>
					</td>
					<td>
						<div id="selectGames">
							<select class="forWidth" id="gt" name="gameType" value="null" onChange="selectGameType(this, 'tr')">
								<option disabled selected>Игра</option>
								<option value="game 1">ЗАГРУЗКА !!!!!</option>
							</select>
						</div>
					</td>
				</tr>
				<!--tr id="presenter" style="display:none;" name="layer">
					<td>
						<b>Имя пользователя:</b>
					</td>
					<td>
						<div id="selectUserName">
							<select class="forWidth" id="ln" name="loginName" value="null" onChange="selectLogin(this, 'tr')">
								<option disabled selected>Имя пользователя</option>
							</select>
						</div>
					</td>
				</tr-->	
				<tr id="presenter" style="display:none;" name="layer">
					<td>
						<b>Пароль:</b>
					</td>
					<td>
						<input class="forWidth" name="presPass" type="password">
					</td>
				</tr>
				<tr>
					<td id="downer" align="center" valign="middle" height="5" colspan="2">
						<p onClick="document.forms[0].submit();" style="cursor:pointer" title="Кликните для входа">ВОЙТИ</p>
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr id="downer" height="30px">
		<td colspan='2' align="center">
			<div id="status">
			</div>
		</td>
	</tr>	
</table>
<input type='submit' value='' style='display:none'>
</form>
</body>
</html>