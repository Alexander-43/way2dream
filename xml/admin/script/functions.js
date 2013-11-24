var message = {
          "downStatusId":"status",								//идентификатор строки состояния
          "loadData":"Загрузка данных",							//текст строки состояния при загрузке данных
	  "statusSowTime": 5000,								//время показа статусных сообщений
          "testConnection":"Проверка соединения c {0} ...",					//тектс строки состояния при проверках коннекта к выбранной игре
          "errorConnection":"<font color='red'>Ошибка соединения c {0}</font>",		//текст строки состояния при ошибке подключения к выбранной игре
          "successConnection":"<font color='green'>Подключение к {0} удалось</font>",		//текст строки остояния при удачном подключении к выбранной игре
          "paginatorId":"paginator",								//идентификатор div`a в который будет встраиваться пагинатор
	  "countElementOnPage":10,								//количество элементов на странице при пагинации
          "saveSucc":"Сохранено."
  
	  };
var gameListLineFormat = "<tr class='tableLine' name='{0}' onDblClick='dblClickOnTableLine(this)'>\
                <td id='selection' width='20'>\
                  <input name='isSelect' type='checkbox' id='{1}' value='true' style='display:none'>\
                  <img src='img/recycle.gif' height='20' title='Удалить' onClick='clickDelete(this)'>\
               </td>\
			   <td id='update'>\
					<img id='updall_{1}' src='img/update.gif' height='20' title='Обновить игру' onClick='clickUpdate(this, null);'>\
			   </td>\
                <td id='index' onClick='clickOnTableLine(this)'>\
                  {2}\
                </td>\
                <td id='active'>\
                  {3}\
                </td>\
                <td id='url' onClick='clickOnTableLine(this)'>\
                  {4}\
                </td>\
                <td id='title' onClick='clickOnTableLine(this)'>\
                  {5}\
                </td>\
                <td id='userCount' onClick='clickOnTableLine(this)'>\
                  {6}\
                </td>\
               </tr>\
                ";
var presenterListLineFormat = "<tr class='tableLine' name='{0}' onDblClick='dblClickOnTableLine(this)'>\
                  <td id='selection' width='20'>\
                    <input name='isSelect' type='checkbox' id='{1}' value='true' style='display:none'>\
                    <img src='img/recycle.gif' height='20' title='Удалить' onClick='clickDelete(this)'>\
                  </td>\
                  <td id='index' onClick='clickOnTableLine(this)'>\
                    {2}\
                  </td>\
                  <td id='active'>\
                    {3}\
                  </td>\
                  <td id='fio' onClick='clickOnTableLine(this)'>\
                    {4}\
                  </td>\
                  <td id='email' onClick='clickOnTableLine(this)'>\
                    {5}\
                  </td>\
                  <td id='skype' onClick='clickOnTableLine(this)'>\
                    {6}\
                  </td>\
                  <td id='dateBegin' onClick='clickOnTableLine(this)'>\
                    {7}\
                  </td>\
                  <td id='dateEnd' onClick='clickOnTableLine(this)'>\
                    {8}\
                  </td>\
                </tr>\
                  ";
var gamersListLineFormat = "<tr class='tableLine' name='{0}' onDblClick='dblClickOnTableLine(this)'>\
                  <td id='selection' width='20'>\
                    <input name='isSelect' type='checkbox' id='{1}' value='true' style='display:none'>\
                    <img src='img/recycle.gif' height='20' title='Удалить' onClick='clickDelete(this)'>\
                  </td>\
                  <td id='index' onClick='clickOnTableLine(this)'>\
                    {2}\
                  </td>\
                  <td id='active'>\
                    {3}\
                  </td>\
                  <td id='fio' onClick='clickOnTableLine(this)'>\
                    {4}\
                  </td>\
                  <td id='email' onClick='clickOnTableLine(this)'>\
                    {5}\
                  </td>\
                  <td id='skype' onClick='clickOnTableLine(this)'>\
                    {6}\
                  </td>\
                  <td id='capColor' onClick='clickOnTableLine(this)'>\
                    {7}\
                  </td>\
                </tr>\
                  ";

function updateAllGames(){
		if ($.each($("input[name='isSelect'][checked]"), 
	function(){
		var line = $("tr.tableLine[name='"+this.id+"']")[0];
		var vals = getCelTextContentById(line, {});
		var calBackFunc = new Object();
		var obj = $("#updall_"+this.id)[0];
		calBackFunc['error'] = function(){
											$(line).css('background-color', '#F00');
											$(obj).attr("src","img/checkstates/notaccept.gif");
											$(obj).attr("onClick","");
											showStatusText(message['downStatusId'], "<font color='red'>Ошибка обновления иры "+vals['title']+"("+vals['url']+")</font>", message['statusSowTime'], false);
										}
		calBackFunc['success'] = function(){
												$('#'+getElementAttribValue(line,'name')).attr('checked', false);
												$(line).css('background-color', 'white');
												$(line).css('color', 'black');
												$(obj).attr("src","img/checkstates/accept.gif");
												$(obj).attr("onClick","");
												showStatusText(message['downStatusId'], "<font color='green'>Игра "+vals['title']+" ("+vals['url']+") успешно обновлена.</font>", message['statusSowTime'], false);
											}
		calBackFunc['complete'] = function(){
												$(line).animate({'opacity': '1'}, 'slow');
											}	
		$(line).animate({'opacity': '0.5'}, 'slow');
		clickUpdate(obj, calBackFunc)
	}).length == 0)
	{
		showStatusText(message['downStatusId'], "<font color='red'>Нет выбранных элементов</font>", message['statusSowTime'], false);
	}
}
				  
function clickUpdate(obj, calBackFunc){
	showStatusText(message['downStatusId'], "Обновление файлов игры. Подождите ...", message['statusSowTime'], true);
	$(obj).attr("src", "img/loading.gif");
	lineName = getElementAttribValue(obj.parentNode.parentNode, "name");
	activeCHBox = $("input:checkbox[value='"+lineName+"']");
	action = JSON.parse(getElementAttribValue(activeCHBox[0], 'action'));
	reqObj = new Object();
	reqObj['fileName'] = action['fileName'];
	reqObj['object'] = action['object'];
	reqObj['unic'] = action['searchByAttr'];
	reqObj['value'] = action['withValue'];
	if (!calBackFunc){
		calBackFunc = new Object();
		calBackFunc['error'] = function(){
											$(obj).attr("onClick","");
											$(obj).attr("src","img/checkstates/notaccept.gif");
											showStatusText(message['downStatusId'], "<font color='red'>Ошибка обновления иры</font>", message['statusSowTime'], false);
										}
		calBackFunc['success'] = function(){
												$(obj).attr("onClick","");
												$(obj).attr("src","img/checkstates/accept.gif");
												showStatusText(message['downStatusId'], "<font color='green'>Игра успешно обновлена.</font>", message['statusSowTime'], false);
											}
	}
	makeQuery("operations.php", null, null, "operId=updateGame&data="+JSON.stringify(reqObj), 'get', 'json', true, calBackFunc);
}
	  
function clickDelete(obj)
{
  showStatusText(message['downStatusId'], "Попытка удаления ...", message['statusSowTime'], true);
  lineName = getElementAttribValue(obj.parentNode.parentNode, "name");
  activeCHBox = $("input:checkbox[value='"+lineName+"']");
  action = JSON.parse(getElementAttribValue(activeCHBox[0], 'action'));
  reqObj = new Object();
  reqObj['fileName'] = action['fileName'];
  reqObj['local'] = action['local'];
  reqObj['object'] = action['object'];
  reqObj['unic'] = action['searchByAttr'];
  reqObj['value'] = action['withValue'];
  if (reqObj['local'])
  {
    if (makeQuery("operations.php", "Удалено.", "Не удалось удалить.", "operId=delElement&data="+JSON.stringify(reqObj)+"&local="+reqObj['local'], 'get', 'json', false, new Object()))
    {
      updateControls('operations.php?operId=makeGamesTable');
    }
  } else
  {
      reqObj['action'] = 'del';
      reqObj['unicValue'] = reqObj['value'];
      url = $('#filterBy').attr('value');
      if (makeQuery(url+"/operation.php?operId=updateObject", "Удалено.", "Не удалось удалить.", "data="+JSON.stringify(reqObj), 'get', 'json', false, new Object()))
      {
	  checkSelectValues();
      }
  }
}
	  
/*
 * Возвращает значение атрибута
 * obj - объект
 * nodeName - имя необходимого атрибута
 */
function getElementAttribValue(obj, nodeName)
{
  for (var i=0; i < obj.attributes.length; ++i)
  {
    if (obj.attributes[i].nodeName == nodeName)
    {
        return obj.attributes[i].nodeValue;
    }
  }
}

/* Обходит содержимое строки таблицы и извлекает значения
 * obj - строка таблицы
 */
function getCelTextContentById(obj, result)
{
    for(var i=0; i<obj.cells.length; ++i)
    {
	result[obj.cells[i].id] = $.trim(obj.cells[i].textContent);

    }
    result['active'] = $("input:checkbox[value='"+getElementAttribValue(obj, 'name')+"']").prop("checked");
    result['objectId'] = getElementAttribValue(obj, 'name');
    if ($('#filterBy').length > 0)
    {
	result['assignTo'] = $('#filterBy').val();
    }
    return result;
}
/*
 * Устанавливает значения элементов формы, данные берутся из data
 * form - форма для заполнения
 * data - объект из которого берутся данные для элементов
 */
function setFormsValues(form, data)
{
  for (var i=0; i < form.length; ++i)
  {
    if (form.elements[i].name in data)
    {
      if (form.elements[i].type == 'checkbox')
      {
	form.elements[i].checked = data[form.elements[i].name];
      }
      else if (form.elements[i].nodeName == 'SELECT')
      {
	  $("#"+form.elements[i].id+" option[value='"+data[form.elements[i].name]+"']").attr("selected", true);
      }
      else
      {
	form.elements[i].value = data[form.elements[i].name];
      }
    }
  }
}
/*
 * Обработчик события двойного нажатия на строке таблицы
 * obj - строка таблицы
 */
function dblClickOnTableLine(obj)
{
  var data = getCelTextContentById(obj, {});
  setFormsValues(document.forms[0], data);
  $('ul.tabs.tabs1 li.t2').click();
}

/*
 * Обработчик клика на строке таблицы с её выделением
 * obj - строка таблицы
 */
function clickOnTableLine(obj)
{
  obj= obj.parentNode;
  id = getElementAttribValue(obj, 'name')
  state = !document.getElementById(id).checked;
  $('#'+id).attr('checked', state);
  if (state)
  {
      obj.style.backgroundColor = '#FFCCCC';
      obj.style.color = '#33CC00';
  }
  else
  {
      obj.style.backgroundColor = 'white';
      obj.style.color = 'black';
  }
}
               
//отображение формы в зависимости от выбранного пользователем тиипа аутентификуации (ведущий/админ)
function selectAuthType(authType, visElName){
    var elements = document.getElementsByTagName(visElName);
    for(var i = 0;i < elements.length;++i)
    {
       
        if (elements[i].id != "" && elements[i].id != "downer")
        {
            if (elements[i].id == authType.value)
            {
                elements[i].style.display = "";
            }
            else
            {
                elements[i].style.display = "none";
            }
        }
    }
    if (authType.value == "presenter")
    {
      updateControls("operations.php?operId=getGamesSelect&selId=gt");
    }
}

function lockObject(objectId, action)
{
    $("#"+objectId).attr('disabled', action);
}
/*
* Обновляем значения selecta
*/
function updateSelect(val)
{
  lockObject(val["id"], true);
  $('#'+val["id"]+' option:not(:first)').remove();
  for(var i = 0; i < val['value'].length; ++i)
  {
    $("#"+val["id"]).append("<option "+val['value'][i]['disabled']+" "+val['value'][i]['selected']+" value='"+val['value'][i]['value']+"'>"+val['value'][i]['text']+"</option>");
  }
  lockObject(val["id"], false);
}
/*
* Строим таблицу с играми
* val - массив значений
*/
function updateTable(val)
{
  $('#'+val["id"]+' tr:not(:first)').remove();
  showStatusText(message['downStatusId'], message['loadData'], '', true);
  index = 1;
  for(var i = val['value'].length - 1; i >= 0 ; --i)
  {
    if (val["id"] == 'gamesList')
    {
        showStatusText(message['downStatusId'], message['loadData'], '', true);
      line = gameListLineFormat.format(val['value'][i]['id'], val['value'][i]['id'], index, val['value'][i]['active'], val['value'][i]['url'], val['value'][i]['title'], val['value'][i]['userCount']);
    }
    else if (val["id"] == 'presenterList')
    {
    line = presenterListLineFormat.format(val['value'][i]['id'], val['value'][i]['id'], index, val['value'][i]['active'], val['value'][i]['fio'], val['value'][i]['email'], val['value'][i]['skype'], val['value'][i]['dateBegin'], val['value'][i]['dateEnd']);
    }
    else if (val["id"] == 'gamersList')
    {
    line = gamersListLineFormat.format(val['value'][i]['id'], val['value'][i]['id'], index, val['value'][i]['active'], val['value'][i]['FIO'], val['value'][i]['email'], val['value'][i]['skype'], val['value'][i]['capColor']);
    }
    $('#'+val["id"]+' tr:last').after(line);
    ++index;
  }
  showStatusText(message['downStatusId'], '', 'none', false);
  showPaginations(val["id"]);
}

// Заполняем таблицу ведущих в соответствии с выбранной игрой
function fillTableOnChangeSelect(obj, url, tableId)
{
   $('#'+tableId+' tr:not(:first)').remove();
   if (checkForAvalible(obj.value, true))
   {
    updateControls(url+obj.value);
   }
   else
   {
      checkGameUrlInSelect(obj);
   }
    
}

/*
* Обновить элементы формы
* url - url-адрес откуда надо получить данные
*/
function updateControls(url)
{
	$(document).ready(function(){
		showStatusText(message['downStatusId'], "Загрузка данных ...", '', true);
		$.getJSON(url, function(data){
			if (data){
				$.each(data, function(key, val){
					if (val['type'] == 'select')
					{
						updateSelect(val);
					}
					else if (val['type'] == 'table')
					{
						updateTable(val);
					}
				});
			} else {
				alert("Ошибка запроса списка игр.");
			}
		})
		.complete(function(response, status) {
			showStatusText(message['downStatusId'], "Готово.", 5500, false);
		})
		.success(function(){
			showStatusText(message['downStatusId'], "Загрузка данных завершена.", '', false);
		})
	});
}

function checkGameUrlInSelect(obj)
{
  $('#'+obj.id+' option').each(
    function(){
    if (!checkForAvalible($(this).attr('value'), true))
    {
        $(this).attr('disabled', true);
    }
    }
  );
}


function changeState(obj)
{
  showStatusText(message['downStatusId'], "Попытка сменить активность", 2000, true);
  data = getElementAttribValue(obj, 'action');
  state = obj.checked;
  dat = JSON.parse(data);
  dat.currentState = state;
  if (!makeQuery('operations.php?operId=setState', "Новое состояние активности установлено", "Не удалось установить состояние активности", "data="+JSON.stringify(dat), 'post', 'json', false, new Object()))
  {
      obj.checked=!state;   
  }
}

/*
* Меняет набор доступных пользователей в соответствии с выбранной игрой
*/
function selectGameType(gameType)
{
    $('#ln option').not(':first').remove();
    if (checkForAvalible(gameType.value, true))
    {
      updateControls(gameType.value+"/operation.php?operId=getPresentersSelect")
    }
    else
    {
      if (confirm("Сайт {0} \nпо адресу {1}, не доступен. \nПровести проверку всех сайтов ?".format(gameType.options[gameType.selectedIndex].text, gameType.value)))
      {
       
        $('#'+gameType.id+' option').each(
          function(){
          if (!checkForAvalible($(this).attr('value'), true))
          {
              $(this).attr('disabled', true);
          }
          }
        );
      }
    }
}
/*
 * Выбор логина
 */
function selectLogin()
{
    return true;
}

/*
* Проверка формы на заполненность полей
* formObj - объект формы
*/
function validateForm(formObj){
    var str = "Введите:\n";
    for (var i = 0; i < formObj.length; i++)
    {
        if (formObj.elements[i].type == "text")
        {
            if (formObj.elements[i].alt != "skip")
            {
                if (formObj.elements[i].title == formObj.elements[i].value || formObj.elements[i].value.length == 0)
                {
                    str+=formObj.elements[i].alt+"\n";
                }
            }
        }
    }
    if (str != "Введите:\n")
    {
        alert(str);
        return false;
    }
    else
    {
        return true;
    }
}
/*
 * Выводит статусное сообщение
 * idArea - идентификатор области вывода
 * text - сообщение для вывода
 * mSec - время для отображения
 * isProcess - добавлять/не добавлять крутилку
 */
function showStatusText(idArea, text, mSec, isProcess)
{
    var obj = document.getElementById(idArea);
    if(obj == null) return false; 
    obj.innerHTML = "";
    $('#'+idArea).css('display', '');
    if (isProcess)
    {
          obj.innerHTML = "<img height='20px' src='img/loading.gif' title='Загружается'>";
    }
    obj.innerHTML += "<b><i>"+text+"</i></b>";
    if (mSec != '')
    {
      setTimeout('$("#'+idArea+'").css("display", "none")', mSec);
    }
}

function runActionsOnloadPage()
{
  //showStatusText('status', 'test text', '');
  //alert($.getUrlVars());
}

/*
 * Выполняет ajax запрос с заданными параметрами и возвращает true если запрос удался
 * urlSend - строка url куда надо сделать запрос
 * successMsg - сообщение в статусе при удаче
 * errorMsg - сообщение в статусе при неудаче
 * dataSend - отправляемые данные
 * qType - post/get
 * dType - тип возвращаемого контента
 * isAsync - true/false
 * calBackFunc - массив calBack функций
 */
function makeQuery(urlSend, successMsg, errorMsg, dataSend, qType, dType, isAsync, calBackFunc)
{
	var resp = $.ajax(
      {
    type: qType,
    url: urlSend,
    data: dataSend,
    dataType: dType,
    async: isAsync,
	success: ('success' in calBackFunc) ? calBackFunc['success']:function(){},
    error: ('error' in calBackFunc) ? calBackFunc['error']:function(){},
	complete: ('complete' in calBackFunc) ? calBackFunc['complete']:function(){}
	});
    if (!isAsync)
	{
		if (resp.status == 200)
		{
		  if (successMsg){
			showStatusText(message['downStatusId'], successMsg, message['statusSowTime'], false);
		  }
		  return true;
		}
		else
		{
		  if (errorMsg){
			showStatusText(message['downStatusId'], errorMsg, message['statusSowTime'], false);
			}
		  return false;
		}
	}
}

/*
* Проверка игры на доступность
* testUrl - url-для проверки
* showInStatus - показать процесс в строке статуса
*/
function checkForAvalible(testUrl, showInStatus)
{
    testUrl = testUrl.convertToUrlDir();
    var remoteScript = "/operation.php?operId=testConnection&url={0}".format(testUrl);
    if (showInStatus)
    {
      showStatusText(message['downStatusId'], message['testConnection'].format(testUrl), message['statusSowTime'], true);
    }
    else
    {
    window.status = message['testConnection'].format(testUrl);
    }
    var resp = $.ajax(
      {
    type: 'get',
    dataType: 'json',
    url: testUrl+remoteScript,
    async: false,
    error:function(xhr, status, error){
        if (showInStatus)
        {
          showStatusText(message['downStatusId'], message['errorConnection'].format(testUrl), message['statusSowTime'], false);
        }
        else
        {
          window.status = message['errorConnection'].format(testUrl);
        }
          },
    success:function(msg){
        if (showInStatus)
        {
          showStatusText(message['downStatusId'], message['successConnection'].format(testUrl), message['statusSowTime'], false);
        }
        else
        {
          window.status = message['successConnection'].format(testUrl);
        }
          }
      });
    if (resp.status == 200)
    {
    return true;
    }
    else
    {
    return false;
    }
}

/*
 * Генерирует набор li для пагинации таблицы
 * count - общее число строк таблицы
 * tabId - идентификатор таблицы
 */
function showPaginations(tabId)
{
  var pagesObject = "<ul class='pagination'>";
  var elOnPage = message['countElementOnPage'];
  var count = $('tr.tableLine').length;
  var countPage = Math.ceil(count/elOnPage);
  if (countPage == 1) return;
  for (var i=1; i<=countPage;++i)
  {
    pagesObject+="<li><a onClick='applyPaging({0}, \"{1}\")'>{2}</a></li>".format(i, tabId, ((i-1)*elOnPage+1)+'-'+((i-1)*elOnPage+elOnPage));
  }
  pagesObject+="<li><a onClick='applyPaging({0}, \"{1}\")'>все ({2})</a></li></ul>".format(-1, tabId, count);
  if (count == 0) return;
  $('#paging').html(pagesObject);
  applyPaging(1, tabId);
}

/*
 * Применяет выбранную пагинацию при щелчке по диапазону
 * num - номер страницы
 * tabId - идентификатор таблицы
 */
function applyPaging(num, tabId)
{
  var elOnPage = message['countElementOnPage'];
  var begin = (num-1)*elOnPage;
  
  var end = begin + elOnPage;
  var countAll = $('#'+tabId+' tr').length;
  if (countAll < end)
  {
     end = end + (countAll - end);
  }
  if (num == -1)
  {
      begin = 0;
      end = countAll;
  }
  $.each($('tr.tableLine'),function(index, value){
                            if(index >= begin && index < end)
                            {
                             $(this).show('slow'); 
                            }
                            else
                            {
			      $(this).hide('slow');
                            }
     
  });
  $.each($('ul.pagination li a'),function(index, value){
				if (index == num-1)
				{
				    $(this).css('background', '#66CC00');
				}
				else
				{
				    $(this).css('background', '#666');
				}
  });
}
/*
 * Расставляет высоту верхней и нижней части страцы (объектов) чтобы нормально отображался скролл
 * up - id верхней части
 * down - id нижней части
 */
function setHeight(up, down)
{
    var winHei = window.screen.availHeight;
    var uper = $('#'+up).attr('height');
    var need = winHei -uper;
    $('#'+down).css('height', winHei - 200);
}

/*
 * Функция проверки установленных значений select`ов и вызов событий onChange 
 */
function checkSelectValues()
{
    $.each($('select'), function(){
      value = getElementAttribValue(this, "value");
      if (value != 'null' && value != '')
      {
	objId = this.id;
	setTimeout(function(){$("#"+objId+" option[value='"+value+"']").attr("selected", "selected").change()}, 2000);
      }
    });
}
/*
* Action при выборе чекбокса "Попробовать скопировать игру"
* targeturl - передается из компонента со страницы добавления игры
* obj - сам объект для изменеия состояния
*/
function trycopy(targeturl, obj)
{
	showStatusText(message['downStatusId'], "Подождите. Идет копирование ...", '', true);
  $.getJSON('operations.php?operId=trycopy&targetUrl='+targeturl, 
  function (data){
	if (data == null) return;
	if (!data['status'] != null)
	{
		showStatusText(message['downStatusId'], "<font color='"+data['color']+"'>"+data['status']+"</font>", message['statusSowTime'], false);
		obj.checked = false;
		return;
	}
	if (!data['test'])
	{
		obj.checked = data['test'];
	}
  });
}

function MailToSelect(obj)
{
	if ($.each($("input[name='isSelect'][checked]"), 
	function(){
		var line = $("tr.tableLine[name='"+this.id+"']")[0];
		var vals = getCelTextContentById(line, {});
		var calBackFunc = new Object();
		calBackFunc['error'] = function(){
											$(line).css('background-color', '#F00');
											showStatusText(message['downStatusId'], "<font color='red'>Сообщение для "+vals['fio']+" отправить не удалось.</font>", message['statusSowTime'], false);
										}
		calBackFunc['success'] = function(){
												$('#'+getElementAttribValue(line,'name')).attr('checked', false);
												$(line).css('background-color', 'white');
												$(line).css('color', 'black');
												showStatusText(message['downStatusId'], "<font color='green'>Сообщение для "+vals['fio']+" отправлено.</font>", message['statusSowTime'], false);
											}
		calBackFunc['complete'] = function(){
												$(line).animate({'opacity': '1'}, 'slow');
											}	
		$(line).animate({'opacity': '0.5'}, 'slow');
		vals['gameName'] = $("#filterBy option[value='"+$("#filterBy").attr("value")+"']").text();
		SendMailTo(vals, calBackFunc)
	}).length == 0)
	{
		showStatusText(message['downStatusId'], "<font color='red'>Нет выбранных элементов</font>", message['statusSowTime'], false);
	}
}

function SendMailTo(mail, calBackFunc)
{
	var flag = false;
	try
	{
		if (mail[0].constructor == Array)
		{
			flag = true;
		}
	} catch (e)
	{
		flag = false;
	}
	if (flag)
	{
		for(var i=0; i < mail.length; ++i)
		{
			var sucMessage = "<font color='green'>Сообщение для "+mail[i]['fio']+" отправлено.</font>";
			var erroMessage = "<font color='red'>Сообщение для "+mail[i]['fio']+" отправить не удалось.</font>";
			makeQuery(mail['assignTo']+'operation.php?operId=sendMail', sucMessage, erroMessage, "data="+JSON.stringify(mail[i]), "get", "html", true, calBackFunc);
		}
	}
	else
	{
		var sucMessage = "<font color='green'>Сообщение для "+mail['fio']+" отправлено.</font>";
		var erroMessage = "<font color='red'>Сообщение для "+mail['fio']+" отправить не удалось.</font>";
		if (makeQuery(mail['assignTo']+'operation.php?operId=sendMail', sucMessage, erroMessage, "data="+JSON.stringify(mail), "get", "html", true, calBackFunc))
		{
			return true;
		}
	}
}

