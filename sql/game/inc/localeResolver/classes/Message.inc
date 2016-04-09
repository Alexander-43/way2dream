<?php

class Message {
	
	private $ini;
	
	function __construct($ini){
		$this->ini = $ini;
	}
	
	function msg($id, $args = array()){
		$format = $this->ini->getValueByKey($id);
		return vsprintf($format, $args);
	}
	
}

?>