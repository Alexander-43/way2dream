<?php

include_once 'tcpdf/config/tcpdf_config.php';
include_once 'tcpdf/tcpdf.php';
include_once 'objectExtractor/includes.inc';
include_once 'PdfGenerator.inc';
include_once 'getContentClass.inc';

$skip = array('/winnerPlan\d*/', 
		'/dreamSymbol/', 
		'/h_solve_\d*/', 
		'/h_state_\d*/', 
		'/h_happend_\d*/',
		'/h_time_\d*/',
		'/sourceIncome\S*/');
$contentGetter = new contentReturnerProcessor();
$path = substr(dirname($_SERVER['SCRIPT_NAME']), 0, -3);
$userInfo = $contentGetter->get_content('http://'.$_SERVER['HTTP_HOST'].$path."operation.php?operId=getUserInfo&id=".$_GET['id']);
$pdf = new PDF($contentGetter->get_content('http://'.$_SERVER['HTTP_HOST'].$path."editUserData.php?id=".$_GET['id']), 
				json_decode($userInfo, true), 
				array('style', 'input','div[id=table1]','div[id=text1]','div[id=text2]','div[id=text3]','div[id=text4]','div[id=table2]'), 
				$skip);

$pdf->getPdf();

?>