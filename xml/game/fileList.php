<?php
	function deleteFile($file){
		if(isset($file) && file_exists($file)){
			if (!is_dir($file)){
				unlink($file);
			}else{
				rmdir($file);
			}
			print $file." - удален";
		}
	}	

	function repairFiles($fileName=""){
		if ($_GET['filter'] && $_GET['filter'] != "/"){
			$fileName = $_GET['filter']."/";
		}
		$mask = $fileName."*";
		print "<table width='50%' align='center'>";
		print "<tr style='background-color:silver'><td></td><td>Имя</td><td>Размер</td></tr>";
		$index = strrpos($_GET['filter'], "/") | 0;
		if ($index != false || $index == 0){
			$back = substr($_GET['filter'], 0, $index);
			print "<tr><td></td><td><a href='?filter=".$back."'> ... </a></td><td></td></tr>";
		}
		foreach (glob($mask) as $file){
			if (is_dir($file)){
				print "<tr><td> <a href='?file=".$file."&filter=".$fileName."'>(X)</a> </td><td><a href='?filter=".$fileName.basename($file)."'>".basename($file)."</a></td><td>&ltDIR></td></tr>";
			} else {
				print "<tr><td> <a href='?file=".$file."&filter=".$fileName."'>(X)</a> </td><td><a href='http://".$_SERVER["SERVER_NAME"].dirname($_SERVER['PHP_SELF'])."/".$file."'>".basename($file)."</td><td>".round(filesize($file)/1024, 2)." Kb</td></tr>";
			}
		}
		print "</table>";
	}
	deleteFile($_GET['file']);
	repairFiles();
?>