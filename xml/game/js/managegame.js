var eventsFunction = {
	containerTag:'li',
	containerAttrib:'item',
	bindTo : function(id, name, action, data){
		//var $ = jQuery.noConflict();
		$('[id='+id+']').each(function(ind, obj){
			if (typeof data == 'undefined'){
				data = false;
			}
			$(obj).unbind(action).bind(action, data, eventsFunction[name]);
		});
	},
	deleteGamer : function(event){
		if (confirm('Вы действительно хотите удалить информацию об игроке навсегда ?')){
			loading.show('Выполняется удаление. Подождите ...');
			var me = this;
			var path = eval('('+$(eventsFunction.getUpperParent(this)).attr('item')+')').path;
			$.get('operation.php',
				{'operId':'deleteGamer',
				'path':path},
				function(data){
					if (data['status'] == 'Ok'){
						eventsFunction.hideGamer({'data':me});
						loading.hide();
					}
				}
			);
		}
	},
	hideGamer : function(event){
		//var $ = jQuery.noConflict();
		var cont = eventsFunction.getUpperParent(event.data || this);
		if (cont){
			$(cont).fadeOut("slow", function(){$(cont).remove();});
		}
	},
	getUpperParent: function(obj){
		//var $ = jQuery.noConflict();
		while(obj.tagName.toUpperCase() != eventsFunction.containerTag.toUpperCase() && !obj[eventsFunction.containerAttrib] && obj.tagName.toUpperCase()!='body'.toUpperCase()){
			obj = $(obj).parent()[0];
		}
		if (obj.tagName == 'body'){
			return false;
		}else{
			return obj;
		}
	},
	saveCurrentConfig: function (){
		loading.show('Сохранение новой конфигурации игры');
		var status = null;
		var activeListElements = $('#active-filelist').children();
		var postData = new Object();
		var idList = [];
		for(var index=0;index<activeListElements.length;++index){
			var liElement = $(activeListElements[index]);
			var capObj = liElement.find('#capImg-active').length == 0 ? liElement.find('#capImg-arh'):liElement.find('#capImg-active');
			var imgSelData = capObj.data('ddslick').selectedData;
			var color = imgSelData.value;
			var data = eval('('+liElement.attr('item')+')');
			if (postData[color] == null){
				if ($.inArray(data.id, idList) == -1)
				{
					postData[color] = data;
					idList.push(data.id);
				} else {
					status = "Невозможно создать игру, так как \n"+data.fio+" добавлен дважды или используется некорретный файл-данных игрока"; 
					break;
				}
			} else {
				status = "Невозможно создать игру, так как\nу "+data.fio+" и "+postData[color].fio+"\nзадан одиннаковый цвет фишки - "+color;
				break;
			}
		}
		if (status != null){
			loading.hide();
			alert(status);
			return;
		}else{
			$.post('operation.php',
					{operId:'saveConfig',
					data:postData},
					function(data){
						alert(data['status']);
					}
			).complete(function(){loading.hide();});
		}
	},
	removeFromGame: function (userFile, name){
		if (confirm("Вы действительно хотите удалить "+name+" из игры ?")){
			var me = this;
			loading.show("Удаление игрока ...");
			$.get('operation.php',
					{'operId':'deleteGamer',
					'path':userFile},
					function(data){
						if (data['status'] == 'Ok'){
							$('tr[id='+id+']').fadeOut('slow', function (){$(me).remove()});
						} else {
							alert(data['status']);
						}
						loading.hide();
					}
				);
		} else {
			return false;
		}
	},
	removeArhGamerFiles: function (){
		loading.show("Удаление резервных копий ...");
		var selectedOptions = $("#arch-select")[0].selectedOptions;
		var obj = new Object();
		obj['opt'] = [];
		for (var index=0; index<selectedOptions.length;++index){
			obj['opt'].push({'label':selectedOptions[index].label, 'path':selectedOptions[index].value});
			obj['caption'] = obj['caption'] ? obj['caption']+selectedOptions[index].label:selectedOptions[index].label;
		}
		if (confirm("Удалить все резервные копии из \""+obj.caption+"\"")){
			$.get('operation.php',
					{'operId':'removeArhGamerFiles',
					 'data':obj},
					 function(data){
						 alert(data['status']);
					 }
			).complete(function(){loading.hide()});
		}
	}
};