<?
	header("Content-Type: text/html; charset=utf-8");
?>
<div id="fade" style="background:rgb(250,247,179);opacity:0.3;z-index:100;width:100%;height:100%;position:absolute;top:0;left:0"></div>
<iframe id="frame" src="component/upload/upload.php?folder=<? print $_GET['folder']; ?>" frameborder="0" scrolling="no" width="400px" style="position:absolute;z-index:200"></iframe>