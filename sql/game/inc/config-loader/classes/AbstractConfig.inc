<?php
include_once 'IConfig.inc';

abstract class AbstractConfig implements IConfig {
	
	public $source;
	
	public function __construct($object){
		if ($object != null){
			$this->setSource($object);
		}
		$this->exception = new Exception();
	}
	
	public function setSource($object){
		$this->source = $object;
	}
}

?>