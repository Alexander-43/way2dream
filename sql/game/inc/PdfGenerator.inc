<?php 

class PDF {
	private $varsValues;
	private $html;
	private $htmlObjects;
	
	public function __construct($html, $varsValues = null, $selectors = array()){
		$this->setHtml($html);
		$this->setVarsValues($varsValues);
		$this->setHtmlObjects($selectors);
	}
	
	public function setHtmlObjects($selectors){
		foreach ($selectors as $selector){
			$this->htmlObjects[] = new HtmlObject($selector, $this->getHtml());
		}
	}
	
	public function getHtmlObjects(){
		return $this->htmlObjects;
	}
	
	public function setHtml($html){
		$this->html = $html;
	}
	
	public function getHtml(){
		return $this->html;
	}
	
	public function setVarsValues($value){
		$this->varsValues = $value;
	}
	
	public function getVarsValues(){
		return $this->varsValues;
	}
	
}

?>