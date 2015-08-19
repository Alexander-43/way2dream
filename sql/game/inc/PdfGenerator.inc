<?php 

class PDF {

	private $varsValues;
	private $html;
	private $htmlObjects;
	private $skipped;
	private $pdfFile;
	
	public function __construct($html, $varsValues = null, $selectors = array(), $skipped = array()){
		$this->setHtml($html);
		$this->setVarsValues($varsValues);
		$this->setHtmlObjects($selectors);
		$this->setSkipped($skipped);
	}
	
	public function setHtmlObjects($selectors){
		foreach ($selectors as $selector){
			$this->htmlObjects[$selector] = new HtmlObject($selector, $this->getHtml());
		}
	}
	
	public function getPdf(){
		$this->setPdfFile(new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, "custom", true, 'UTF-8', false));
		$this->pdfFile->SetCreator(PDF_CREATOR);
		$this->pdfFile->SetAuthor('Nicola Asuni');
		$this->pdfFile->SetTitle('TCPDF Example 014');
		$this->pdfFile->SetSubject('TCPDF Tutorial');
		$this->pdfFile->SetKeywords('TCPDF, PDF, example, test, guide');
		$this->pdfFile->setFontSubsetting(false);
		$this->pdfFile->SetFont('freeserif', '', 10, '', false);
		$this->pdfFile->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);
		$this->pdfFile->setPrintHeader(false);
		$this->pdfFile->setPrintFooter(false);
		$this->pdfFile->AddPage();
		$this->pdfFile->setFormDefaultProp(array('lineWidth'=>1, 'borderStyle'=>'solid', 'fillColor'=>array(255, 255, 200), 'strokeColor'=>array(255, 128, 128)));
		$this->pdfFile->Image("../img/card.jpg", 5, 8, /*280*/0, /*447*/0, '', '', '', false, 300, '', false, false, 0);
		foreach ($this->getHtmlObjects() as $selector=>$objects){
			foreach ($objects->getObjects("") as $object){
				$objType = $object->tag;
				if (!$this->isNameSkipped($object->attr['name'])){
					$this->$objType($object);
				}
			}
		}
		$this->pdfFile->Output('example_.pdf', 'I');
	}
	
	public function input($element){
		if ($element->attr['type'] != 'text' && method_exists($this, $element->attr['type'])){ 
			$method = $element->attr['type'];
			return $this->$method($element);
		} else if ($element->attr['type'] == 'hidden') {
			return;
		}
		$style = StylePropFormatter::get($element->attr['style']);
		$temp = array('dimentsions'=>array());
		$w = StylePropFormatter::extractValue("width", $element->attr['width'], $temp);
		$h = StylePropFormatter::extractValue("height", $element->attr['height'], $temp);
		$w = !$w ? $style['width']:$w;
		$h = !$h ? $style['height']:$h;
		$name = $element->attr['name'];
		$this->pdfFile->SetX($this->pdfFile->pixelsToUnits($style['left']), true);
		$this->pdfFile->SetY($this->pdfFile->pixelsToUnits($style['top']), false, true);
		$this->pdfFile->TextField($name, $this->pdfFile->pixelsToUnits($w ? $w : 100), $this->pdfFile->pixelsToUnits($h ? $h : 20), array('value'=>$element->attr['name'], 'multiline'=>false));
	}
	
	public function checkbox($element){
		$style = StylePropFormatter::get($element->attr['style']);
		$this->pdfFile->SetX($this->pdfFile->pixelsToUnits($style['left']), true);
		$this->pdfFile->SetY($this->pdfFile->pixelsToUnits($style['top']), false, true);
		$this->pdfFile->CheckBox($element->attr['name'], 10);
	}
	
	public function div($element){
		$style = StylePropFormatter::get($element->attr['style']);
		$this->pdfFile->SetX($this->pdfFile->pixelsToUnits($style['left']), true);
		$this->pdfFile->SetY($this->pdfFile->pixelsToUnits($style['top']), false, true);
		$str = $element->outertext();
		$this->pdfFile->writeHTML($str, true, false, true, false, '');
	}
	
	public function style($element){
		$this->pdfFile->writeHTML($element->outertext(), true, false, true, false, '');
	}
	
	private function isNameSkipped($name){
		foreach ($this->getSkipped() as $value){
			if (preg_match($value, $name) === 1){
				return true;
			}
		}
		return false;
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
	
	public function setPdfFile($file){
		$this->pdfFile = $file;		
	}
	
	public function getPdfFile(){
		return $this->pdfFile;
	}
	
	public function setSkipped($value){
		$this->skipped = $value;
	}
	
	public function getSkipped(){
		return $this->skipped;
	}
}

?>