<? 
	require("func.inc"); 
?>
<html>
	<body>
		<script src="../../js/jquery.js"></script>
		<script src="func.js"></script>
		<? if (isset($_GET['folder'])){
			$destFolder = $_GET['folder'];
		} else {
			$destFolder = $_POST['folder'];
		} ?>
		<form method="post" action="#" enctype="multipart/form-data">
			<input id="selected_files" type="file" name="files[]" multiple="true" min="1" max="6" style="opacity:0;position:absolute;left:-100px;z-index:1">
			<input name="folder" type="text" value="<? print $destFolder; ?>" style="opacity:0;position:absolute;z-index:2">
			<table id="table" border="1" width="100%" height="100%" style="background-color:rgb(226, 255, 166);z-index:999;border:solid 5px silver;border-radius:10px" cellspacing="0">
				<tr>
					<td align="center">
						<div id="files" style="margin:0 30px 0 0">Нет выбранных файлов</div>
					</td>
				</tr>
				<tr id="dwnl" style="display:none">
					<td align="center" valign="bottom" style="height:20px">
						<input type="submit" value="Загрузить">
					</td>
				</tr>
			</table>
			<div id="actions" style="position:absolute;top:10px;right:15px;z-index:1000">
				<img id="exit" src="img/exit.png" title="Закрыть" style="cursor:pointer"><br>
				<img id="add" src="img/add.png" title="Выбрать файлы" style="cursor:pointer">
			</div>
		</form>
	</body>
</html>