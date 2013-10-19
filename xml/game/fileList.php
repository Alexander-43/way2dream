<?php
	function repairFiles($fileName=""){
		if ($_GET['filter']){
			$fileName = $_GET['filter'];
		}
		$mask = "*".$fileName;
		foreach (glob($mask) as $file){
			print "<a href='http://".$_SERVER["SERVER_NAME"].dirname($_SERVER['REQUEST_URI'])."/".basename($file)."'>".basename($file)." (".filesize($file).")<br>";
		}
	}
	repairFiles();
?>