<?php 

interface ILocaleResolver {
	
	const DEFAULT_LOCALE = "ru";
	
	function getLocale();	
}

?>