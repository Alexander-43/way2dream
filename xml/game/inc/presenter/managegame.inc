<style>
	.placeHolder{
		border:dashed yellow 1px;
		height:70px;
		line-height:70px;
	}
</style>
<script type="text/javascript">
function openUploadDialog(){
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

var cache = [];
function makeBackUp(){
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
		loading.show("Загрузка. Пожалуйста подождите");
		$.get('<? print operPage; ?>', 
				{'operId':'get_object_list',
				'path':this.value,
				'conf':{'addToObject':{'control':'arh'}}
				},
				function (data){
					elementList.create('arh-filelist', '<? include(root.slash.inc.slash.presenter.slash."managegame.listelement.inc"); ?>', null, data.list);
					eventsFunction.bindTo('presenter_hideIcon-arh', 'hideGamer', 'click');
					eventsFunction.bindTo('presenter_removeIcon-arh', 'deleteGamer', 'click');
				}
		);
		loading.hide();
		var tempFolder = "<? print urlencode(root.slash.tempFolder);?>";
		if (this.value != "default" && this.value != tempFolder){
			$("#restore_fb").fadeIn();
			$("#remove_arh").fadeIn();
		} else {
			$("#restore_fb").fadeOut();
			$("#remove_arh").fadeOut();
		}
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
			'path':'<? print urlencode(root.slash.xmlFolder); ?>',
			'conf':{'addToObject':{'control':'active'}}
			},
			function (data){
				elementList.create('active-filelist', '<? include(root.slash.inc.slash.presenter.slash."managegame.listelement.inc"); ?>', null, data.list);
				eventsFunction.bindTo('presenter_hideIcon-active', 'hideGamer', 'click');
				eventsFunction.bindTo('presenter_removeIcon-active', 'deleteGamer', 'click');
				if (!cache['caps']){
					cache['caps'] = imgSelector.makeCapsColorObject(data.caps);
				}
				imgSelector.create('capImg-active', cache['caps']);
			}
	);

    $( "#active-filelist, #arh-filelist" ).sortable({
        connectWith: "ul#active-filelist",
        placeholder:"placeHolder",
        receive:function(event, ui){
        		imgSelector.replace($(ui.item[0]).find('#capImg-arh')[0], cache['caps']);
            }
      }).disableSelection();
});
</script>
<table style="width:100%;height:100%">
	<tr>
		<td style="width:50%">
			<img class="action_icon" src="<? print "img".slash."managegame".slash."save_config.png";?>" onClick="eventsFunction.saveCurrentConfig()" title="Сохранить созданную конфигурацию игры">
		</td>
		<td align="right" style="width:50%;height:40px">
			<img class="action_icon" src="<? print "img".slash."managegame".slash."upload-dialog.png"; ?>" onclick="openUploadDialog()" title="Загрузить файлы-данных игроков">	
			<img class="action_icon" src="<? print "img".slash."managegame".slash."back-up.png"; ?>" onclick="makeBackUp()" title="Резервная копия файлов-данных игроков">
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
			<img id="restore_fb" src="<? print "img".slash."managegame".slash."restore_from_backup.png";?>" class="action_icon_small" title="Восстановить игру из выбранной резервной копии" style="display:none" onclick="">
			<img id="remove_arh" src="<? print "img".slash."trash.png";?>" class="action_icon_small" title="Удалить резервные копии" style="display:none" onclick="eventsFunction.removeArhGamerFiles()">
			<div style="height:95%;width:100%;overflow:auto;border:solid silver 1px;border-radius:5px;background-color:white">
				<ul id="arh-filelist" style="height:70px" title="Выберите резервную копию из списка">
					
				</ul>
			</div>
		</td>
	</tr>
</table>