<li style="border-radius:5px" item="{\'path\':\'{filePath}\'}" onmouseover="this.style[\'background-color\']=\'rgb(231, 231, 231)\'" onmouseout="this.style[\'background-color\']=\'white\'">\
	<table style="width:100%;cursor:pointer;font-size:12px;font-weight:600;color:steelblue;" border="0" onselect="return false">\
		<tr>\
			<td rowspan="4" style="width:90px;text-align:center">\
				<img id="capImg-{control}" src="{imgSrc}" style="" title="{capColor}">\
			</td>\
			<td>\
				ФИО:\
			</td>\
			<td title="ФИО">\
				{FIO}\
			</td>\
			<td rowspan="4" valign="center" align="center">\
				<img id="presenter_hideIcon-{control}" src="img/hide.png" onmouseover="this.style.opacity=\'1\'" onmouseout="this.style.opacity=\'0.3\'" style="opacity:0.3" title="Скрыть"><br>\
				<img id="presenter_removeIcon-{control}" src="img/trash.png" onmouseover="this.style.opacity=\'1\'" onmouseout="this.style.opacity=\'0.3\'" style="opacity:0.3" title="Удалить">\
			</td>\
		</tr>\
		<tr>\
			<td>\
				Дата регистрации:\
			</td>\
			<td title="Дата регистрации">\
				{date}\
			</td>\
		</tr>\
		<tr>\
			<td>\
				Skype:\
			</td>\
			<td title="Skype">\
				{skype}\
			</td>\
		</tr>\
		<tr>\
			<td>\
				E-mail:\
			</td>\
			<td title="Электронная почта">\
				{email}\
			</td>\
		</tr>\
	</table>\
</li>