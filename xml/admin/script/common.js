function FadeImg(action)
{
	if (action == 'over')
	{
		document.getElementById('statImg').style.opacity=0.3;
	}
	if (action == 'out')
	{
		document.getElementById('statImg').style.opacity=1;
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
	if (outputArea != null)
	{
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
	}
	req.onreadystatechange = function() 
	{  
		if (req.readyState == 4) 
		{ 
			if (outputArea != null)
			{
				statusElem.innerHTML = req.statusText; // показать статус (Not Found, ОК..)
			}
			if(req.status == 200) 
			{ 
				if (outputArea != null)
				{
					statusElem.innerHTML=req.responseText;
				}
			}
		}
	}
	req.open('GET', queryString, true);  
	req.send(null);  // отослать запрос
	if (outputArea != null)
	{
		statusElem.innerHTML = "<img class='card' src='img/loading.gif' "+sizeWait+" >";
	}
}

function clearThis(obj)
{
	if (obj.alt != "edit")
	{
		obj.value="";
		obj.alt = "edit";
	}
}

function imgRotate(obj, action)
{
	obj.src = "img/"+action+".gif";
}

function saveMessage()
{
	var url = arguments[0]+"?";
	for (var i=1;i<arguments.length-1;i++)
	{
		url+="&"+arguments[i].name+"="+arguments[i].value
	}
	vote(url, null);
	vote(arguments[arguments.length-1], "result")
}