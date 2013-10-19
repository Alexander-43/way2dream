<?
	require('domXml.inc');
	if (strlen($_GET["FIO"]) > 0 && strlen($_GET["mess"]) > 0)
	{
		$xml = new ParseXML('maessages.xml');
		$xml->SearchNode($xml->RootNode, "message", "mess", $_GET["mess"]);
		if ($xml->SearchedNodeLink == null)
		{
			$node = $xml->linkToXml->createElement("message");
			$xml->SearchedNodeLink = $xml->linkToXml->documentElement->appendChild($node);
			$xml->SearchedNodeLink->setAttribute("id", md5(date("dmYhhmmss")));
			$xml->SearchedNodeLink->setAttribute("data", date("d.m.Y h:m:s"));
			foreach ($_GET as $name=>$value)
			{	
				$name =  str_replace (">","&gt;", str_replace ("<", "&lt;", $name));
				$value =  str_replace (">","&gt;", str_replace ("<", "&lt;", $value));
				$xml->SearchedNodeLink->setAttribute($name, $value);
			}			
			$xml->SaveInFile($xml->Nfile);
		}
	}
?>