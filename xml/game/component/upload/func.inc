<?
	header("Content-Type: text/html; charset=utf-8");
	upload($_FILES, $_POST);
	
	function upload($files, $postData){
		if (!empty($files)){
			$str = "";
			$tempFolder = $postData['folder'];
			foreach ($files["files"]["error"] as $key => $error) {
				if ($error == UPLOAD_ERR_OK) {
					$tmp_name = $files["files"]["tmp_name"][$key];
					$name = $files["files"]["name"][$key];
					if (!file_exists($tempFolder)){
						mkdir($tempFolder, 0777);
					}
					move_uploaded_file($tmp_name, $tempFolder."/$name");
				} else {
					$str +="Ошибка загрузки - ".$files["files"]["name"][$key]."\n";
				}
			}
			if (strlen($str) > 0){
				print "<script>alert('".$str."')</script>";
			} else {
				print "<script>alert('Файлы загружены.')</script>";
			}
		}
	}

?>