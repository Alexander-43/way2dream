<script>
  function addValidation(sourceId, targetId)
  {
     $('#'+targetId).keyup(function(){
      if ($('#'+sourceId).attr('value') != $('#'+targetId).attr('value'))
      {
	$('#'+targetId).css('color','red');
	$('#'+targetId).css('border','1px solid red');
      }
      else
      {
	$('#'+targetId).css('color','green');
	$('#'+targetId).css('border','1px solid green');
      }
     });
     $('#'+targetId).keyup();
  }
</script>
<title>Настройки</title>
<? $ini = getIniValues(iniFile); ?>
<form name='settingsForm' action='#' method='post' onSubmit="return validateForm(this);">
<div class='mainConteiner' id='setting' height='0'>
<table width='50%' align='center' border='0'>
		<tr>
		  <td align='left'>
		    Пароль администратора
		  </td>
		</tr>
		<tr align='left'>
		 <td>
			<table width='100%'>
			  <tr>
			    <td>
				    <label>
					    <b>Текущий пароль:</b>
					    <input id='currentPass' name='currentPass' type='password' value='' title='Текущий пароль администратора' alt='skip' style='width:100%;'>
				    </label>
			    </td>
			    <td>
				    <label>
					    <b>Новый пароль:</b> 
					    <input id='newPass' name='newPass' type='password' value='' title='Новый пароль администратора' alt='skip' style='width:100%' onChange="addValidation('newPass','newPassAgain');">
				    </label>
			    </td>
			    <td>
				    <label>
					    <b>Повторите пароль:</b> 
					    <input id='newPassAgain' name='newPassAgain' type='password' value='' title='Повторить новый пароль администратора' alt='skip' style='width:100%'>
				    </label>
			    </td>			  
			  </tr>
			</table>
		  </td>
		</tr>
		<tr>
		  <td>
			  <label>
				  <b>Url-адрес папки администрирования:</b>
				  <input id='adminUrl' name='adminUrl' type='text' value="<? print dirname('http://'.$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'])?>" title='Адрес папки администрирования' alt='skip' style='width:100%;'>
			  </label>
		  </td>
		</tr>
		<tr>
		  <td>
			  <label>
				  <b>E-mail адрес администратора:</b>
				  <input id='adminEmail' name='adminEmail' type='text' value="<? print $ini->read('setting', 'adminEmail', ''); ?>" title='Адрес папки администрирования' alt='skip' style='width:100%;'>
			  </label>
		  </td>
		</tr>		
		<tr align='center'>
			<td>
				<input id='settingsFormButton' type='submit' value='Сохранить'>
			</td>
		</tr>
	</table>
</div>
</form>
<script>
  setHeight('setting', 'setting');
</script>