function hideUploadDialog(fade, frame){
	//var $ = jQuery.noConflict();
	$('#'+fade).fadeOut();
	$('#'+frame).fadeOut();
	$('#'+fade).remove();
	$('#'+frame).remove();
}