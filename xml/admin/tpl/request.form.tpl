<script type="text/javascript" src="script/common.js"></script>
<div class='mainConteiner' id="containertext">
	<h1>Обратная связь</h1>
	<table width="100%">
		<tr>
			<td valign="top" align="right" width="95%">
				<div id="result" style="overflow:auto;">
				</div>
			</td>
			<td valign="top" align="right" width="200">
				<div align="right">
					<form id="inc/request/save.php" name="writeMessage" align="center">
						<i><input id="field_1" name="FIO" type="text" value="Как к вам обращаться ?" onClick="clearThis(this)" style="width:150px;"></i>
						<input id="field_3" name="public" checked type="checkbox" title="Публиковать" value="true" onClick="this.value = this.checked"><br>
						<textarea id="field_2" rows="13" name="mess" onClick="clearThis(this)">Ваше сообщение</textarea><br>
						<p onMouseDown="imgRotate(document.getElementById('butSend'), 'off')" 
						onMouseOver="imgRotate(document.getElementById('butSend'), 'over')" 
						onMouseOut="imgRotate(document.getElementById('butSend'), 'on')" 
						style="cursor:pointer" 
						onClick="saveMessage('inc/request/save.php', document.forms.writeMessage['field_1'], document.forms.writeMessage['field_2'], document.forms.writeMessage['field_3'], 'inc/request/showMessages.php');">
						<img id="butSend" src="img/on.gif" align="middle">
						<b>Отправить</b>
						</p>
					</form>
				</div>
			</td>
		</tr>
	</table>
</div>
<script type="text/javascript">
	$(document).ready(function() {
		vote("inc/request/showMessages.php", "result");
		setHeight('upSide', 'containertext');
	});
</script>