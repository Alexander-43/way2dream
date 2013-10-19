<?php
include ('vars.inc');
include ('domXml.inc');
include ('func.php');
unset($_SESSION['id']);
unset($_SESSION['authKey']);
if ($_POST['dataValid']=="validate")
{
	$arrData = Array ("FIO" => $_POST['FIO'], "skype" => $_POST['skype'], "email"=>$_POST['email'], "cap"=>"cap_".$_POST['capColor']);
	$id=md5(date("dmYhhmmss")." ".$_POST['skype']." ".$_POST['email']);
	$arrData["id"] = $id;
	$_SESSION = array_merge($_SESSION, $arrData);
	SaveRegData($arrData);
	print "<script>window.location.replace('gamer.php')</script>";
}
else if (md5($_POST['admCode'])==accessCode)
{
	$_SESSION['authKey']=accessCode;
	print "<script>window.location.replace('presenter.php')</script>";
}else
{
	printBrs(5);
	print "<table width='50%' align='center'><tr><td align='center'><font color='red'><h2>Доступ к этой странице незарегистрированным пользователям запрещен</h2></font></td></tr>";
	print "<tr height='100'><td></td></tr>";
	print "<tr><td height='100' align='center' style='border-color:silver;border-style:solid;border-radius: 10px 10px 10px 10px;'><a href='index.php'><h2>Зарегистрироваться</h2></a></td></table>";
}
?>