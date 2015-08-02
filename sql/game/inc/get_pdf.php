<?php

include_once 'tcpdf/config/tcpdf_config.php';
include_once 'tcpdf/tcpdf.php';
include_once 'objectExtractor/includes.inc';
include_once 'PdfGenerator.inc';

$pdf = new PDF(@file_get_contents("http://sqltest.ru/editUserData.php?id=eac929db221ad7ab4801f04c18cfecb7"), null, array('input'));
$pdf->getPdf();

?>