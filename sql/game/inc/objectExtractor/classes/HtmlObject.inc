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
		if (is_int($index)){
			return StylePropFormatter::get($this->objects[$index]->style);
		} else {
			return StylePropFormatter::get($index);
		}
	}
	
	public function setSelector ($selector){
		$this->selector = $selector;
	}

	public function getSelector(){
		return $this->selector;
	}
}

class StylePropFormatter {
	
	const DIMENSIONS = 'px|%';
	
	public static function get($value){
		$props = explode(';', $value);
		$result = array('dimensions'=>array());
		foreach ($props as $v){
			$sp = explode(':', $v);
			$result[$sp[0]] = StylePropFormatter::extractValue($sp[0], $sp[1], $result);
		}
		return $result;
	}
	
	public static function extractValue($key, $value, &$retrying){
		foreach (explode("|", StylePropFormatter::DIMENSIONS) as $dim){
			if (strpos($value, $dim) !== false){
				$retrying['dimensions'][$key] = $dim;
				$spacesRemoved = str_replace(" ", "", $value);
				$dimRemoved = str_replace($dim, "", $spacesRemoved);
				return $dimRemoved;
			}
		}
		return $value;
	}
}

?>