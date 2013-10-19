<?
require('domXml.inc');
function getAllMessages()
{
	$xml = new ParseXML("maessages.xml");
	$xml->GetNodesAttribsValuesByName($xml->RootNode, "message", "id");
	$NAV = $xml->nodesAttribValue;
	$AllInfoAboutUsers = array();
	foreach ($NAV as $elem)
	{
		$xml->SearchNode($xml->RootNode, "message", "id", $elem);
		if ($xml->SearchedNodeLink != null && strlen($elem) != 0)
		{
			$xml->AttribFromSNL("", $vis);
			$AllInfoAboutUsers[] = $vis;
			unset($vis);
		}
	}
	$xml->Destroy();
	return $AllInfoAboutUsers;
}
	$allMessage = getAllMessages();
	$str = "";
	if (strlen($_GET['limit']) > 0)
	{
		for ($i = count($allMessage) - 1; $i > -1; --$i)
		{
			if ($allMessage[$i]["public"] == "true")
			{
				$str.="<h4>".$allMessage[$i]["FIO"]." - ".$allMessage[$i]["data"]."</h4>".$allMessage[$i]["mess"]."<br><hr>";
			}
		}
	}
	else
	{
		for ($i = count($allMessage) - 1; $i > -1; --$i)
		{
			if ($allMessage[$i]["public"] == "true")
			{
				$str.="<h4>".$allMessage[$i]["FIO"]." - ".$allMessage[$i]["data"]."</h4><p align='justify'>".$allMessage[$i]["mess"]."</p><hr>";
			}
		}
	}
	//print_r ($allMessage);
	print $str;
?>