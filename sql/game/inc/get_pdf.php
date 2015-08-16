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
		'/sourceIncome\S*/'
);
$pdf = new PDF(@file_get_contents("http://sqltest.ru/editUserData.php?id=eac929db221ad7ab4801f04c18cfecb7"), null, array('style', 'input', 'div[id=table1]', 'div[id=text1]', 'div[id=text2]', 'div[id=text3]', 'div[id=text4]', 'div[id=table2]'), $skip);
$pdf->getPdf();

?>