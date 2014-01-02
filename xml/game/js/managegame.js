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
	}
};