<form name='presenterForm' action='#' method='post'>
	<table id='upSide' width='50%' align='center' border='0' height='450'>
		<tr align='left'>
			<td>
				<label>
					<b>ФИО ведущего:</b> 
					<input name='fio' type='text' value='<? print $_SESSION['fio'];?>' title='ФИО ведущего' alt='ФИО ведущего' style='width:100%'>
				</label>
			</td>
		</tr>
		<tr align='left'>
			<td>
				<label>
					<b>Пароль:</b> 
					<input id='randPass' name='password' type='password' value='{@}|{@}' title='Пароль' alt='skip' style='width:100%'>
				</label>
			</td>
		</tr>		
		<tr align='left'>
			<td>
				<label>
					<b>Skype:</b> 
					<input name='skype' type='text' value='<? print $_SESSION['skype'];?>' title='Skype' alt='Skype' style='width:100%'>
				</label>
			</td>
		</tr>		
		<tr align='left'>
			<td>
				<label>
					<b>E-mail:</b> 
					<input name='email' type='text' value='<? print $_SESSION['email'];?>' title='E-mail' alt='E-mail' style='width:100%'>
				</label>
			</td>
		</tr>		
		<tr align='center'>
			<td>
				<table>
					<tr>
						<td>
						<label>
							<b>Дата начала действия: <? print $_SESSION['dateBegin'];?></b>
						</label>
						</td>
						<td>
						<label>
							<b>Дата окончания действия: <? print $_SESSION['dateEnd'];?></b>
						</label>
						</td>						
					</tr>
				</table>
				<? 
					$dat = calcDatePeriod(null, $_SESSION['dateEnd']); 
					print "<br>Время активности вашего акаунта заканчивается через <br>".$dat['day']." дней ".$dat['hours']." часов ".$dat['minutes']." минут ".$dat['seconds']." секунд";
				?>
			</td>
		</tr>
		<tr align='center'>
			<td>
				<input id='presenterFormButton' type='submit' value='Сохранить'>
			</td>
		</tr>
	</table>		
</form>