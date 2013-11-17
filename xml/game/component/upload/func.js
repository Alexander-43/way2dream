//var $ = jQuery.noConflict();
$(document).ready(function(){
	$('#add').click(function(){
		$('#selected_files').click();
		$('#selected_files').change(function(){
			var fCount = $('#selected_files')[0].files.length;
			if (fCount > 0){
				$('#dwnl').fadeIn();
			} else {
				$('#dwnl').fadeOut();
			}
			parent.document.getElementById('frame').height = ((fCount+1) * 25 + 90) + 'px';
			var files = $('#selected_files')[0].files;
			var str=files.length!=0 ? "<ol align='left'>":"";
			for(var index = 0;index<files.length;++index){
				str+="<li title='"+((files[index].size/1024).toPrecision(4))+" Кб"+"'>"+files[index].name+"</li>";
			}
			if (files.length == 0){
				str+="Нет выбранных файлов";
			}else{
				str+="</ol>";
			}
			$('#files').html(str);
		});
	});
	$('#exit').click(function(){
		parent.hideUploadDialog("fade", "frame");
	});
	var wHeight = parent.innerHeight;
	var wWidth = parent.innerWidth;
	parent.document.getElementById('frame').style['top'] = wHeight / 2 - parent.document.getElementById('frame').clientHeight / 2;
	parent.document.getElementById('frame').style['left'] = wWidth / 2 - parent.document.getElementById('frame').clientWidth / 2;
});