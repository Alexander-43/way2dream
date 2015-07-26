<?php

class HtmlObject {
	
	private $selector;
	private $objects;
	
	public function __construct($selector = null, $html = null){
		if ($selector){
			$this->selector = $selector;
		}
		if ($html){
			$this->getObjects($html);
		}
	}
	
	public function getObjects($value, $type = 'text'){
		if (count($this->objects) > 0){
			return $this->objects;
		}
		$html = '';
		if ($type == 'text'){
			$html = str_get_html($value);
		} else if ($type == 'url') {
			$html = file_get_html($value);
		}
		return $this->objects = $html->find($this->getSelector());
	}
	
	public function getStyle($index){
		return StylePropFormatter::get($this->objects[$index]->style);
	}
	
	public function setSelector ($selector){
		$this->selector = $selector;
	}

	public function getSelector(){
		return $this->selector;
	}
}

class StylePropFormatter {
	public static function get($value){
		$props = split(';', $value);
		$result = array();
		foreach ($props as $v){
			$sp = split(':', $v);
			$result[$sp[0]] = $sp[1];
		}
		return $result;
	}
}

?>