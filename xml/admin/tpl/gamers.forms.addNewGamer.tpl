<script>	function check(obj)	{		$('#assignToState').attr('src','img/loading.gif');		$('#assignToState').attr('title',$('#assignToState').attr('alt').format('*Подключение*'));		if (checkForAvalible(obj.value, true))		{			$('#atv').attr('checked', true)			$('#assignToState').attr('src','img/checkstates/accept.gif');			$('#assignToState').attr('title',$('#assignToState').attr('alt').format('*Подключение удалось*'));			updateControls('operations.php?operId=getCapColorSelect&id=capColor&free=true&url='+obj.value);		}		else		{			$('#atv').attr('checked', false);			$('#assignToState').attr('src','img/checkstates/notaccept.gif');			$('#assignToState').attr('title',$('#assignToState').attr('alt').format('*Подключение не удалось*'));			$('#capColor option:not(:first)').remove();			$('#capColor option:first').attr('selected', true);		}	}</script><title>Добавление / Редактирование игроков</title><ul class="tabs tabs1">	<li class="t1 tab-current"><a>Список игроков</a></li>	<li class="t2"><a>Редактировать</a></li></ul><div class="t2" align='center'><form name='gamersForm' action='#' method='post' onSubmit='return validateForm(this);'>	<input type='hidden' id='editingRecord' value='$POST_[\"editRecId\"]'>	<table id='upSide' width='50%' align='center' border='0' height='350'>		<tr align='left'>			<td>				<label>					<b>Добавить в игру:</b> 					<select 						class='forWidth' 						id='assignTo' 						name='assignTo' 						value='null' 						style='width:90%' 						onChange="check(this)">					  <option disabled selected value="">Выберите игру</option>					</select>					<script>					  updateControls('operations.php?operId=getGamesSelect&selId=assignTo');					</script>					<input id='atv' name='assignToValid' type='checkbox' value='true' style='display:none'>					<img id='assignToState' src='img/checkstates/indefinite.gif' width='9%' align='middle' style='display:inline;' alt='Статус проверки {0}' title=''>				</label>			</td>		</tr>			<tr align='left'>			<td>				<label>					<b>ФИО игрока:</b> 					<input name='fio' type='text' value='ФИО игрока' title='ФИО игрока' alt='ФИО игрока' style='width:100%'>				</label>			</td>		</tr>		<tr align='left'>			<td>				<label>					<b>Skype:</b> 					<input id='skype' name='skype' type='text' value='Skype' title='Skype' alt='Skype' style='width:100%'>				</label>			</td>		</tr>				<tr align='left'>			<td>				<label>					<b>E-mail:</b> 					<input name='email' type='text' value='E-mail' title='E-mail' alt='E-mail' style='width:100%'>				</label>			</td>		</tr>		<tr>			<td>				<label>					<b>Цвет фишки:</b>					<select						id="capColor"						name="capColor"						value="null"						style="width:100%"						>					<option disabled selected value="">Выберите цвет фишки</option>					</select>				</label>			</td>		</tr>		<tr align='center'>			<td>				<label>					<b>Игрок активен: </b>					<input name='active' type='checkbox' checked value='true' title='Игрок сможет войти в игру' alt='skip'>				</label>			</td>		</tr>		<tr align='center'>			<td>				<input id='gamerFormButton' type='submit' value='Сохранить'>			</td>		</tr>	</table></div><div class="t1"><p id='upSide' align='left' height='50' style='margin:0 0 0 0; position:relative; top: -30px; padding:0 0 0 0; margin-bottom: -20px; width:50%'>   <table>    <tr>      <td>	      <select 		      class='forWidth' 		      id='filterBy' 		      name='filterBy' 		      value="<? print $_POST['filterBy'] ?>" 		      onChange="fillTableOnChangeSelect(this,'operations.php?operId=makeGamersTable&url=', 'gamersList')">		<option disabled selected value="">Выберите игру</option>	      </select>      <!--td>	    <button>	      Показать все	    </button>      </td-->      </td>      <td>	<div id='paging'></div>      </td>      <!--td>	Доп. кнопочки      </td-->    </tr>   </table></p>  <div class='mainConteiner' id='GAMERS'>  <table width='100%' id='gamersList' class='lineHover'>    <tr id='upper'>      <td align='center' width='0'>	<input id='selectAll' type='checkbox' title="Выбрать все" style='display:none'>      </td>      <td align='center' width='30'>	№      </td>      <td align="center" width='100'>	Активен      </td>      <td align='center'>	ФИО      </td>      <td align='center'>	E-mail      </td>      <td align='center'>	Skype      </td>      <td align="center" width='180'>	Цвет фишки      </td>    </tr>  </table>  </div></form></div><script>  updateControls('operations.php?operId=getGamesSelect&selId=filterBy');  checkSelectValues();  setHeight('upSide', 'GAMERS');</script>