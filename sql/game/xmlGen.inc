<?php
	header("Content-Type: application/xml; charset=utf-8");
	error_reporting(E_ALL);
    require("vars.inc");
    require("domXml.inc");
    require(incFolder."func.inc");
    new Parse(dataSourceType, xmlForFlash, $object);
    print $object->getXmlFromCurrentObject();
?>