//поле с именами измененных полей 
//var changedFieldId = 'changeField';
$(document).ready(
		function (){
			var browser=get_browser();
			var browser_version=get_browser_version()
			if (browser.toLowerCase() == "msie"){
				alert("Браузер "+browser+" "+browser_version+" игрой не поддерживается. Извините.");
				history.back();
			}
		}
);

function get_browser(){
    var N=navigator.appName, ua=navigator.userAgent, tem;
    var M=ua.match(/(opera|chrome|safari|firefox|msie)\/?\s*(\.?\d+(\.\d+)*)/i);
    if(M && (tem= ua.match(/version\/([\.\d]+)/i))!= null) M[2]= tem[1];
    M=M? [M[1], M[2]]: [N, navigator.appVersion, '-?'];
    return M[0];
    }
function get_browser_version(){
    var N=navigator.appName, ua=navigator.userAgent, tem;
    var M=ua.match(/(opera|chrome|safari|firefox|msie)\/?\s*(\.?\d+(\.\d+)*)/i);
    if(M && (tem= ua.match(/version\/([\.\d]+)/i))!= null) M[2]= tem[1];
    M=M? [M[1], M[2]]: [N, navigator.appVersion, '-?'];
    return M[1];
    }

function addChagedElement (obj){
	var field = $('[name='+changedFieldId+']');
	var value = field.attr('value'); 
	if (typeof(obj) == "string")
	{
		var obj = {'name':obj};
	}
	if (obj instanceof String){
		var obj = {'name':obj.toString()};
	}
	if (value.indexOf(obj.name) < 0)
	{
		field.attr('value', value+obj.name+"|");
		
	}
}

//устанавливает вычисляемые поля в readOnly
function setReadOnly(conf){
	for(var i in conf)
	{
		$('[name='+i+']').attr('readonly', conf[i]['readOnly']);
	}
}

//объект с конфигом для вычисляемых полей
//var config = {'sum':{'fieldsId':['pole1', 'pole2'], 'actions':['pole1+pole2']} };
function doAction(obj){
	for(var i in config)
	{
		if ($.inArray(obj.name, config[i].fieldsId) > -1){
			var line = config[i].actions;
			for(var j in config[i].fieldsId){
				var val = $('[name='+config[i].fieldsId[j]+']').val().length == 0 ? '0' : $('[name='+config[i].fieldsId[j]+']').val();
				line=line.replaceAll(config[i].fieldsId[j], val);
			}
			$('[name='+i+']').attr('value', eval(line));
			addChagedElement(new String(i));
		}
	}
}

String.prototype.replaceAll = function(key, value){
	var formated = this;
	while (formated.indexOf(key)!=-1){
		formated = formated.replace(key, value);
	}
	return formated;
}

//функция находит и устанавливает значение value для поля с name
function setValue(name, value)
{
	var obj = $("[name="+name+"]"); 
	if (obj.attr('type') == "text"){
		obj.attr('value', value);
	}
}

//изменение высоты кнопки старт/стоп при наведении
function imgOver(img, inc)
{
	img.height = inc;
}

//запуск/остановка автоматического обновления страницы игрока
function RunStop(img)
{
	if (img.id == 1)
	{
		img.id = 0;
	}
	else
	{
		img.id = 1;
	}
	img.src = "img/"+img.id+".gif";
	document.timerObj.state.value = img.id;
	document.timerObj.submit();
}

//затенение фишки при наведении мыши
function mOverAction (img)
{
	img.src = "img/img_7.gif";
	return 0;
}

//возврат цвета фишки к исходному
function mOutAction (img)
{
	if (img.name != "img_"+document.gamerReg.capColor.value)
	{
		img.src="img/"+img.name+".gif";
		return 0;
	}
}

//фишка выбрана при клике
function mOnClick(img)
{
	if (document.gamerReg.capColor.value != "")
	{
		eval("document.img_"+document.gamerReg.capColor.value+".src='img/img_"+document.gamerReg.capColor.value+".gif';");
	}
	document.gamerReg.capColor.value=img.id;
	img.src = "img/img_7.gif";
	document.gamerReg.but.disabled="";
	return 0;
}


function trimStr(v, onNotFillMes)
{
	v = v.replace( /^\s+/g, '');
	if (v == "")
	{
		return onNotFillMes;
	}
	else
	{
		return "";
	}
}

//проверка полей формы на заполненность
function validFormData()
{
	var preMes = "Переход к игре не возможен.\n Пожалуйста заполните следующие поля: \n";
	var mes = "";
	mes = trimStr(document.gamerReg.FIO.value, "Фамилия Имя Отчество \n")+trimStr(document.gamerReg.skype.value, "Имя пользователя Skype \n");
	mes += trimStr(document.gamerReg.email.value, "E-mail \n")+trimStr(document.gamerReg.capColor.value, "Выберите цвет фишки \n");
	if (mes != "")
	{
		if (!document.gamerReg.but.disabled)
		{
			alert(preMes+mes);
			document.gamerReg.but.disabled="disabled";
			document.gamerReg.dataValid.value="";
		}
		
	}
	else
	{
		document.gamerReg.dataValid.value="validate";
	}
}

//создание объекта для ajax запроса
function getXmlHttp(){
var xmlhttp;
	try {
		xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
	} catch (e) {
	try {
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    } catch (E) {
		xmlhttp = false;
    }
	}
	if (!xmlhttp && typeof XMLHttpRequest!='undefined') {
		xmlhttp = new XMLHttpRequest();
  }
  return xmlhttp;
}

//выполнение get-запроса queryString с выводом результата в outputArea
function vote(queryString, outputArea) 
{
	var req = getXmlHttp(); 
	var statusElem = document.getElementById(outputArea);
	var sizeWait;
	if (statusElem.clientHeight >= statusElem.clientWidth)
	{
		sizeWait = "width="+statusElem.clientWidth;
	}
	else
	{
		sizeWait = "height="+statusElem.clientHeight;
	}
	req.onreadystatechange = function() 
	{  
		if (req.readyState == 4) 
		{ 
			statusElem.innerHTML = req.statusText // показать статус (Not Found, ОК..)
			if(req.status == 200) 
			{ 
				statusElem.innerHTML=req.responseText;
			}
		}
	}
	req.open('GET', queryString, true);  
	req.send(null);  // отослать запрос
	statusElem.innerHTML = "<img class='card' src='img/loading.gif' "+sizeWait+" >";
}

//мануальное отключение автообновления страницы
function userRefreshStop()
{
	try
	{
		clearTimeout(TO);
	} 
	catch (e)
	{
	
	}
	document.run.src = "img/1.gif";
	document.run.id = 1;
	document.timerObj.state.value = "1";
}

//выбрать карточку для отображения пользователю
function sendCardType(obj)
{
	//obj.disabled = "disabled";
	if (obj.value != "null")
	{
		vote("operation.php?randcard=Off&userId="+obj.name+"&cardType="+obj.value, "card_"+obj.name);
	}
	//alert(obj.id+" "+obj.value);
}

//смена состояния чекбокса показывания чей ход
function onChecking(objInp, objImg)
{		
	objInp.checked = !objInp.checked;
	if (objInp.checked)
	{
		objImg.src = "img/chchecked.gif";
	}
	else
	{
		objImg.src = "img/chclear.gif";
	}
	update(objInp);
	vote("operation.php?isActive="+objInp.checked+"&userId="+objInp.id.substring(objInp.id.indexOf('_')+1,objInp.id.length)+"&action="+objInp.id.substring(0,objInp.id.indexOf('_')), "empty_"+objInp.id.substring(0,objInp.id.indexOf('_')));
}

//устанавливаем все чекбоксы в false кроме выбранного
function update(inp)
{	
	list = document.getElementsByName(inp.name);
	for (var i=0;i<list.length;i++)
	{
		if (inp.id != list[i].id)
		{
			document.getElementById('i'+list[i].id).src = "img/chclear.gif";
		}
	}
}

function setGetPay(id, pref, action, attrib)
{
	var i = 0;
	var la = 0;
	formInput = document.getElementById(pref+"i_"+id);
	formHInput = document.getElementById(pref+"ih_"+id);
	try{
		formInput.value == "" ? formInput.value = "0" : i++;
		formHInput.value == "" ? formHInput.value = "0" : i++;
 		formInput.value = parseFloat(formInput.value);
		formHInput.value = parseFloat(formHInput.value);
	} catch (e)
	{
		alert ("Одно из значений операции ("+formInput.value+" или "+formHInput.value+")\r не является допустимым числом");
		return false;
	}
	divOut = document.getElementById(pref+"_"+id);
	setVal = eval(formHInput.value+action+formInput.value);
	if (action == "+"){
		action = " увеличен на ";
	} else {
		action = " уменьшен на ";
	}
	if (attrib == 'glob_sour'){
		la = "Последнее действие : Ресурс"+action+formInput.value;
	}else
	{
		la = "Последнее действие : Доход"+action+formInput.value;
	}
	vote('operation.php?doPay=do&value='+setVal+'&atribute='+attrib+'&userId='+id+'&lastAction='+la, divOut.id);
	formHInput.value = setVal;
}

var dblClick_showPrompt = function(object){
	object.value = prompt("Введите значение поля", object.value);
}

function editFormSubmit(form){
	var getValidValue = function(value){ 
	try{
		return parseFloat(value);
	}
	catch(e){
		return false;
	}
	}
	/*var getSumOfInput = function (inputArray){
		var str = 0;
		var str1 = "";
		for (var elem in inputArray){
			if (getValidValue(form[inputArray[elem]].value)){
				str+=getValidValue(form[inputArray[elem]].value);
			}
		}
		return str;
	}
	var pasIncomeRedBlue = ["moneyFromParent", "bisnesAPasIncome_1", "bisnesAPasIncome_2", "bisnesBPasIncome_1", "bisnesBPasIncome_1", "bisnesCPasIncome_1", "bisnesCPasIncome_2"];
	pasIncomeRedBlue.push("statApasIncome_1", "statApasIncome_2", "statBpasIncome_1", "statBpasIncome_2", "statCpasIncome_1", "statCpasIncome_2", "income_400");
	var pasIncomeRedBlueGreen = pasIncomeRedBlue.concat();
	pasIncomeRedBlueGreen.push("zp");
	var commonRes = ["bornSource", "bisnesAR_1", "bisnesAR_2", "bisnesBR_1", "bisnesBR_2", "bisnesCR_1", "bisnesCR_2", "profSource"];
	commonRes.push("study_apended", "childrens_appended");
	form["pasIncomeBlueCircle"].value = getSumOfInput(pasIncomeRedBlue);
	addChagedElement("pasIncomeBlueCircle");
	form["pasIncomeGreenCircle"].value = getSumOfInput(pasIncomeRedBlueGreen);
	addChagedElement("pasIncomeGreenCircle");
	form["commonR"].value = getSumOfInput(commonRes);
	addChagedElement("commonR");
	form["pasIncomeBlueCircle"].disabled = "";
	form["pasIncomeGreenCircle"].disabled = "";
	form["commonR"].disabled = "";
	return true;*/
}

function setDate(obj)
{
	obj.value = obj.value == "" ? new Date().toLocaleString() : obj.value;
	addChagedElement (obj.name);
}

function onLoad(divName)
{
	var radios = document.getElementsByTagName('input');
	for (var i=0;i<radios.length;i++)
	{
		if (radios[i].type == 'radio')
		{
			if (radios[i].checked)
			{
				jQuery('div').scrollTo('#'+radios[i].id);
				return;
			}
		}
	}
}

var randCardMapping = {};
function showField(count, name, cardName){
	$('#mask').fadeIn(500);
	$('#mask').fadeTo("slow",0.8);
	$('#closeDialog').fadeIn(1);
	var winH = $(window).height();
	var winW = $(window).width();
	id = "#dialog";
	$(id).css('top',  winH/2-$(id).height()/2);
	$(id).css('left', winW/2-$(id).width()/2);
	$("#closeDialog").css('top',winH/2-$(id).height()/2 - 20);
	$("#closeDialog").css('left',winW/2-$(id).width()/2 + 450);
	$(id).fadeIn(1000);
	var w = (100 - cardName.length) / (cardName.length / 1.8);
	if ($(id).children("div").length == 1){
		for (var i = 1;i<=count;++i){
			var e = $("#dSource").clone();
			e.children()[0].name = i;
			e.children()[0].text = cardName;
			$(e.children()[0]).css("font-size", (w > 30?30:w)+"px");
			var rnd = -1;
			while (randCardMapping[rnd] != null || rnd == -1){
				rnd = getRandomInt(1, count);
			}
			randCardMapping[rnd] = i;
			e.click(function () {
				var index = getKeyByValue($(this).children()[0].name, randCardMapping);
				if (index){
					vote('operation.php?randcard=On&pref='+name+"&index="+index, 'vote_status');
					$('#dialog').fadeOut(500);
					$('#mask').fadeOut(500);
					$(this).fadeOut(1);
					$("a[name='"+name+"'").fadeOut(1000);
					$("a[name='"+name+"'").attr('name', 'null');
				}
			});
			e.appendTo("#dialog");
			e.fadeIn(2000);
		}
	}
}

function getKeyByValue(value, a){
	var keys = Object.keys(a);
	for (var key in keys){
		if (a[keys[key]] == value){
			return key;
		}
	}
	return null;
}

function getRandomInt(min, max)
{
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

function removeUser(url, fio){
	if (confirm('Вы действительно хотите удалить '+ fio + ' из игры ?')){
		$.get(url, function(data){
			if (data.status == "Ok"){
				alert("Игрок " + fio + " удален.");
				location.reload();
			} else {
				alert(data.message);
			}
		})
	}
}

try {

$(document).ready(function() {

$('ul.tabs li').css('cursor', 'pointer');

$('ul.tabs.tabs1 li').click(function(){
	var thisClass = this.className.slice(0,2);
	$('div.t1').hide();
	$('div.t2').hide();
	$('div.t3').hide();
	$('div.t4').hide();
	$('div.' + thisClass).show();
	$('ul.tabs.tabs1 li').removeClass('tab-current');
	$(this).addClass('tab-current');
	});

});
} catch(e){ }