<?php

interface IConfig {
	public function getAll();
	
	public function getValueByKey($key);
	
	public function setSource($object);
}

?>