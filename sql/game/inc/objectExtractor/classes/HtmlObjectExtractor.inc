<?php 

class HtmlObjectExtractor {
	
	const INPUT_PROP_REGEXP = "|\<input name=\"(.*?)\".*style=\"(.*?)\"|gmi";
	
	
	
	private $text;
	private $objects;
	
	public function __construct($text = null){
		if ($text){
			$this->setText($text);
			
		}
	}
	
	public function setText($text){
		$this->text;
	}
	
	public function getText(){
		return $this->text;
	}
}

?>