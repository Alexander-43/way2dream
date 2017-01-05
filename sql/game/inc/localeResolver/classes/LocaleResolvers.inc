<?php

include_once 'ILocaleResolver.inc';

class CookieLocalResolver implements ILocaleResolver{
	const COOKIE_LOCALE_NAME = "current_locale";
	function getLocale(){
		if (isset($_COOKIE[CookieLocalResolver::COOKIE_LOCALE_NAME]) 
				&& $_COOKIE[CookieLocalResolver::COOKIE_LOCALE_NAME] != ""){
			return $_COOKIE[CookieLocalResolver::COOKIE_LOCALE_NAME];
		} else {
			return null;
		}
	}
	
	function setLocale($value){
		setcookie(CookieLocalResolver::COOKIE_LOCALE_NAME, $value,  mktime().time()+60*60*24*365, "/");
	}
}

class BrowserLocalResolver implements ILocaleResolver {
	
	const FULL_LOCALE_NAME = false;
	
	function getLocale(){
		$locale = $_SERVER['HTTP_ACCEPT_LANGUAGE'];
		if ($locale != null && $locale != ""){
			if (BrowserLocalResolver::FULL_LOCALE_NAME){
				return $locale;
			} else {
				return $this->parseDefaultLanguage($locale);
			}
		} else {
			ILocaleResolver::DEFAULT_LOCALE;
		}
	}
	
	function parseDefaultLanguage($http_accept) {
		$deflang = ILocaleResolver::DEFAULT_LOCALE;
		if(isset($http_accept) && strlen($http_accept) > 1)  {
			# Split possible languages into array
			$x = explode(",",$http_accept);
			foreach ($x as $val) {
				#check for q-value and create associative array. No q-value means 1 by rule
				if(preg_match("/(.*);q=([0-1]{0,1}.\d{0,4})/i",$val,$matches))
					$lang[$matches[1]] = (float)$matches[2];
					else
						$lang[$val] = 1.0;
			}
	
			#return default language (highest q-value)
			$qval = 0.0;
			foreach ($lang as $key => $value) {
				if ($value > $qval) {
					$qval = (float)$value;
					$deflang = $key;
				}
			}
		}
		if (strrpos($deflang, "-") !== false){
			$exp = explode("-", $deflang);
			return $exp[0];
		}
		return strtolower($deflang);
	}
	
}

?>