var loading = {
	dialogTemplate:"<div id='loading-container' style='position:absolute;top:0;width:100%;height:100%;z-index:1500'>" +
			"<div id='shadow' style='position:absolute;top:0;width:100%;height:100%;z-index:1501;background:rgb(170,170,170);opacity:0.4'></div>" +
			"<div id='content' style='z-index:1502;position:absolute'>" +
			"<table style='background:gray;border-radius:5px'><tr><td align='center' valign='center'><img src='img/loading.gif' title='Загрузка'></td>" +
			"<td align='center' valign='center' width='250px'><b><font color='white'>{text}</font></b></td></tr></table>" +
			"</div></div>",
	show: function (text){
		//var $ = jQuery.noConflict();
		if ($('#loading-container')[0]){
			$('#loading-container').remove();
		}
		$('body').append(this.dialogTemplate.replace('{text}', text));
		this.centring('content');
	},
	hide: function (){
		//var $ = jQuery.noConflict();
		$('#loading-container').remove();
	},
	centring: function (id){
		var wHeight = window.innerHeight;
		var wWidth = window.innerWidth;
		document.getElementById(id).style['top'] = wHeight / 2 - document.getElementById(id).clientHeight / 2;
		document.getElementById(id).style['left'] = wWidth / 2 - document.getElementById(id).clientWidth / 2;
	}
};

var select = {
		style:"",
		create:function(id, config, data){
			//var $ = jQuery.noConflict();
			if (!$('#'+id+'-select')[0]){
				$('#'+id).append("<select id='"+id+"-select' style='"+select.style+"'></select>");
			}
			$('#'+id+'-select').find('option').end().append("<option value='default' disabled>Список резервных копий</option>").val('default');
			for(var index in data){
				$('#'+id+'-select').append("<option value='"+data[index][config.value]+"'>"+data[index][config.text]+"</option>");
			}
			if (config.selected){
				$('#'+id+'-select').val(config.selected);
			}
			if ($('select[id='+id+'-select] option').size() == 0){
				$('#'+id+'-select').append("<option value='null'>Список пуст</option>");
			}
			return $('#'+id+'-select');
		}
};

var formatting = {
		formatWithConfig:function(templ, config, data){
			var clone = ''+templ
			for(var conf in config){
				while(clone.indexOf(conf)>-1){
					clone = clone.replace(conf, data[config[conf]]);
				}
			}
			return clone;
		},
		formatFromTmpl:function (templ, data){
			var clone = ''+templ;
			for(var elem in data){
				while(clone.indexOf('{'+elem+'}')>-1){
					clone = clone.replace('{'+elem+'}', data[elem]);
				}
			}
			return clone;
		}
};

var elementList = {
		create:function (id, templ, config, data){
			//var $ = jQuery.noConflict();
			if ($('#'+id)[0]){
				$('#'+id).html('');
			}
			for (var index in data){
				if (config){
					$('#'+id).append(formatting.formatWithConfig(templ, config, data[index]));
				} else {
					$('#'+id).append(formatting.formatFromTmpl(templ, data[index]));
				}
			}
			if (!data || data.length == 0){
				$('#'+id).append("Нет элементов для отображения");
			}
			return $('#'+id);
		}
};

var imgSelector = {
		create : function (id, data){
			//var $ = jQuery.noConflict();
			$('[id='+id+']').each(function (ind, obj){
				if (obj.tagName.toUpperCase()!="div".toUpperCase())
					imgSelector.replace(obj, data);
				}					
			);
		},
		replace:function(obj, data){
			//var $ = jQuery.noConflict();
			var currentSrc = $(obj).attr('src');
			var currentTitle = $(obj).attr('title');
			var currentId = $(obj).attr('id');
			var parent = $(obj).parent();
			$(obj).remove();
			$(parent).append("<select id='"+currentId+"'></select>");
			var select = $(parent).children();
			$(select).append("<option value='"+currentTitle+"' data-imagesrc='"+currentSrc+"'></option>");
			for(var index in data){
				if (currentSrc.indexOf(data[index].img) == -1){
					$(select).append("<option value='"+data[index].value+"' data-imagesrc='"+data[index].src+"' style='background-color:green'></option>");
				}
			}
			var tempId = (Math.random()+"").replace("0.","");
			$(select).attr('id', tempId);
			$(select).ddslick({'width':'80px'});
			var data = $('#'+tempId).data('ddslick');
			$(data.selectedItem).css('background-color', 'rgb(255, 174, 174)');
			$('#'+tempId).attr('id', currentId);
		},
		setSimple: function (id){
			
		},
		makeCapsColorObject:function(list){
			var obj = [];
			for (var index in list){
				if (index.indexOf('.gif') == -1){
					obj.push({'value':index, 'src':'img/'+list[index], 'img':list[index]});
				}
			}
			return obj;
		}
};