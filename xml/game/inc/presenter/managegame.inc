<script>
	function openUploadDialog(){
		var $ = jQuery.noConflict();
		var folder = "<? print urlencode(root.slash.tempFolder); ?>";
		$.get('component/upload/index.php',
			{
				folder:folder
			},
			function(data){
				$('body').append(data);
			},
			'html'
		);
	}

	function makeBackUp(){
		var $ = jQuery.noConflict();
		loading.show('Создание резервной копии ...');
		var url = "<? print operPage; ?>";
		$.get(url,
			{operId:'back_up'}, 
			function (data){
				loading.hide();
				if(data['status']=='Ok'){
					alert('Дата создания резервной копии - '+data['date']+'\nСодержит файлы:\n'+data['filelist']);
				} else {
					alert(data);
				}
			}
		);
	}
</script>
<table style="width:100%;">
	<tr>
		<td align="right">
			<img src="<? print "img".slash."managegame".slash."upload-dialog.png"; ?>" onclick="openUploadDialog()" title="Загрузить файлы-данных игроков">
			<img src="<? print "img".slash."managegame".slash."back-up.png"; ?>" onclick="makeBackUp()" title="Резервная копия файлов-данных игроков">
		</td>
	</tr>
</table>