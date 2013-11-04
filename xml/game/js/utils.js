var loading = {
	dialogTemplate:"<div id='loading-container' style='position:absolute;top:0;width:100%;height:100%;z-index:1500'>" +
			"<div id='shadow' style='position:absolute;top:0;width:100%;height:100%;z-index:1501;background:rgb(170,170,170);opacity:0.4'></div>" +
			"<div id='content' style='z-index:1502;position:absolute'>" +
			"<table style='background:gray;border-radius:5px'><tr><td align='center' valign='center'><img src='img/loading.gif' title='Загрузка'></td>" +
			"<td align='center' valign='center' width='250px'><b><font color='white'>{text}</font></b></td></tr></table>" +
			"</div></div>",
	show: function (text){
		var $ = jQuery.noConflict();
		$('body').append(this.dialogTemplate.replace('{text}', text));
		this.centring('content');
	},
	hide: function (){
		var $ = jQuery.noConflict();
		$('#loading-container').remove();
	},
	centring: function (id){
		var wHeight = window.innerHeight;
		var wWidth = window.innerWidth;
		document.getElementById(id).style['top'] = wHeight / 2 - document.getElementById(id).clientHeight / 2;
		document.getElementById(id).style['left'] = wWidth / 2 - document.getElementById(id).clientWidth / 2;
	}
};