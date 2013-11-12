<script type="text/javascript">
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

var $ = jQuery.noConflict();
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

$(document).ready(function() {
	var onSelectChange = function(){
		var $ = jQuery.noConflict();
		loading.show("Загрузка. Пожалуйста подождите");
		$.get('<? print operPage; ?>', 
				{'operId':'get_object_list',
				'path':this.value},
				function (data){
					elementList.create('arh-filelist', '<? include(root.slash.inc.slash.presenter.slash."managegame.listelement.inc"); ?>', null, data.list);
				}
		);
		loading.hide();
	};
	$.get('<? print operPage; ?>',
			{'operId':'get_object_list',
			'path':'<? print urlencode(root.slash.tempFolder); ?>',
			'type':'dir',
			'conf':{'0':{'name':'Загружены вручную','path':'<? print urlencode(root.slash.tempFolder); ?>'}}},
				function(data){
					var sel = select.create("arch", {"value":"path", "text":"name"}, data.list);
					if (sel){
						sel.change(onSelectChange);
					}
				}
			,'json'
	);

	$.get('<? print operPage; ?>',
			{'operId':'get_object_list',
			'path':'<? print urlencode(root.slash.xmlFolder); ?>'
			},
			function (data){
				elementList.create('active-filelist', '<? include(root.slash.inc.slash.presenter.slash."managegame.listelement.inc"); ?>', null, data.list);
			}
	);
});
</script>
<table style="width:100%;height:100%">
	<tr>
		<td style="width:50%">
		</td>
		<td align="right" style="width:50%;height:40px">
			<img src="<? print "img".slash."managegame".slash."upload-dialog.png"; ?>" onclick="openUploadDialog()" title="Загрузить файлы-данных игроков">	
			<img src="<? print "img".slash."managegame".slash."back-up.png"; ?>" onclick="makeBackUp()" title="Резервная копия файлов-данных игроков">
		</td>
	</tr>
	<tr>
		<td valign="bottom">
			Список текущих игроков:
			<div style="height:95%;width:95%;overflow:auto;border:solid silver 1px;border-radius:5px;background-color:white">
				<ul id="active-filelist">
				
				</ul>
			</div>
		</td>
		<td valign="bottom">
			Резервные копии:
			<div id="arch" style="display:inline"></div>
			<div style="height:95%;width:100%;overflow:auto;border:solid silver 1px;border-radius:5px;background-color:white">
				<ul id="arh-filelist">
					
				</ul>
			</div>
		</td>
	</tr>
</table>