<?php
	function getArrayValues($query){
		if (!$query) return Array("res"=>"null");
		while($field=mysql_fetch_field($query)){
			$names_fields[]=$field->name;
		}
		$values = Array();
		while ($row = mysql_fetch_array($query, MYSQL_NUM)) {
			$line = Array();
			for($i = 0; $i < count($names_fields); $i++)
			{
			$line[$names_fields[$i]]=$row[$i];
			}
			$values[] = $line;
		}
		return $values;
	}
	
	include_once '../mysql/connect';
	
	
	if ($_POST['query']!=null){
		$clink = mysql_connect(host, user, password);
		if ($clink){
			$dblink = mysql_select_db(dbName);
		}
		$result = mysql_query($_POST['query']);
		if ($result === false){
			print  mysql_error();
		}
		$res = getArrayValues($result);
		if (count($res) > 0){
			print "<table width='100%' border='1'><tr>";
			foreach($res[0] as $key=>$value){
				print "<td>$key</td>";
			}
			print "</tr>";
			for($i=0;$i<count($res);$i++){
				print "<tr>";
				foreach ($res[$i] as $key=>$v){
					print "<td>$v</td>";
				}
				print "</tr>";
			}
			print "</table>";
		}
	}
?>
<form name="f1" method="post" action="#">
	<input name="query" type="text" value="<?php print $_POST['query'];?>">
	<input type="submit">
</form>