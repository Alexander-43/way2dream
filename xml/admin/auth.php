<?php
	require(dirname(__FILE__)."/vars.inc");
	require(dirname(__FILE__)."/inc/domXml.inc");
	require(dirname(__FILE__)."/inc/func.inc");
	require(dirname(__FILE__)."/inc/TIniParse.inc");
	
	if ($_POST['authType']=='presenter')
	{
	  $message = sendRequest($_POST['gameType'].'/operation.php?operId=remoteAuth&userId='.$_POST['loginName'].'&password='.md5($_POST['presPass']), true, "Ошибка авторизации");
	  $message = json_decode($message, true);
	  if ($message == null) { $message['status'] = "Ошибка сервера.";}
      $_POST['loginName'] = $message['id'];
      if ($message['status'] == 'OK')
	  {
	    print "<script>document.location.replace('".$_POST['gameType']."/operation.php?operId=remoteEnter&userId=".$_POST['loginName']."&password=".md5($_POST['presPass'])."');</script>";
	  }
	  else
	  {
	    print "<script>alert('".$message['status']."'); window.history.back();</script>";
	  }
	  
	}else if ($_POST['authType']=='admin')
	{
	  $_SESSION['adminPass'] = md5($_POST['adminPass']);
	  if (checkAuth($_SESSION))
	  {
	    print "<script>document.location.replace('manage.php');</script>";
	  }
	}
	else
	{
	  header('HTTP/1.0 404 not found');
	  require(page404);
	}
?>