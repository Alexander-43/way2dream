<?
header("Content-Type: text/html; charset=utf-8");
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	$a = preg_split("/[|]{1,3}/",$_POST['editedField']);
	WriteAttrib ($_POST, $a);
	if (strlen($_POST['id']) == 0)
	{
		if (strlen($_GET['id'])!=0)
		{
			new Parse(dataSourceType, xmlForUserData, $xml, false);
			$xml->SearchNode($xml->RootNode, "user", "id", $_GET['id']);
			if ($xml->SearchedNodeLink != null)
			{
				$xml->AttribFromSNL("", $vis);
				$_POST = $vis;
				$_POST['currentScroll'] = $_SESSION['currentScroll'];
			}
			$xml->Destroy();
		}
	} else {
		$_SESSION['currentScroll'] = $_POST['currentScroll'];
		header("Location: ".$_SERVER['REQUEST_URI']);
	}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript">
	var changedFieldId = 'editedField';
	var config = {
					'sum':
						{
							'fieldsId':['pole1', 'pole2'], 
							'actions':'pole1+pole2',
							'readOnly': true
						},
					'commonR':
						{
							'fieldsId':['bisnesAR_1', 'bisnesBR_1', 'bisnesCR_1', 'bisnesAR_2', 'bisnesBR_2', 'bisnesCR_2', 'bisnesAR_3', 'bisnesBR_3', 'bisnesCR_3', 'profSource', 'childrens', 'study', 'bornSource'], 
							'actions':'bisnesAR_1+bisnesBR_1+bisnesCR_1+bisnesAR_2+bisnesBR_2+bisnesCR_2+bisnesAR_3+bisnesBR_3+bisnesCR_3+profSource+childrens+study+bornSource',
							'readOnly': true
						},
					'passIncomeAllCircle':
						{
							'fieldsId':['statApasIncome_1', 'statBpasIncome_1', 'statCpasIncome_1', 'statApasIncome_2', 'statBpasIncome_2', 'statCpasIncome_2', 'statApasIncome_3', 'statBpasIncome_3', 'statCpasIncome_3', 'franshPasIncome', 'capitalPasIncome'], 
							'actions':'statApasIncome_1+statBpasIncome_1+statCpasIncome_1+statApasIncome_2+statBpasIncome_2+statCpasIncome_2+statApasIncome_3+statBpasIncome_3+statCpasIncome_3+franshPasIncome+capitalPasIncome',
							'readOnly': true
						},
					'activeIncomeGreenCircle':
						{
							'fieldsId':['bisnesAActIncome_1', 'bisnesBActIncome_1', 'bisnesCActIncome_1', 'bisnesAActIncome_2', 'bisnesBActIncome_2', 'bisnesCActIncome_2', 'bisnesAActIncome_3', 'bisnesBActIncome_3', 'bisnesCActIncome_3', 'zp'], 
							'actions':'bisnesAActIncome_1+bisnesBActIncome_1+bisnesCActIncome_1+bisnesAActIncome_2+bisnesBActIncome_2+bisnesCActIncome_2+bisnesAActIncome_3+bisnesBActIncome_3+bisnesCActIncome_3+zp',
							'readOnly': true
						},
					'franshPasIncome' : {
						'fieldsId':['franshiza', 'franProc'], 
						'actions':'franshiza*franProc/100',
						'readOnly': true
					},
					'capitalPasIncome' : {
						'fieldsId':['capProc', 'capital'], 
						'actions':'capital*capProc/100',
						'readOnly': true
					}						
				};
	window.onscroll = function(){
		$('#currentScroll').attr('value', window.pageYOffset || document.documentElement.scrollTop);
	};
</script>
<script type="text/javascript" src="js/tab.js"></script>
</head>
<body>
<form name="editForm" method="POST" action="#" onSubmit="editFormSubmit(this)">
<input name="sourceIncomeA" type="text" value="<? print $_POST['sourceIncomeA']?>" style="position:absolute;width:270px;left:492px;top:1270px;z-index:71" onChange="addChagedElement(this.name)">
<input name="sourceIncomeB" type="text" value="<? print $_POST['sourceIncomeB']?>" style="position:absolute;width:271px;left:492px;top:1299px;z-index:72" onChange="addChagedElement(this.name)">
<input name="sourceIncomeC" type="text" value="<? print $_POST['sourceIncomeC']?>" style="position:absolute;width:272px;left:492px;top:1328px;z-index:73" onChange="addChagedElement(this.name)">
<? require(incFolder.'card.inc'); ?>
<input name="winnerPlan1" type="text" value="<? print $_POST['winnerPlan1']?>" style="position:absolute;width:679px;left:80px;top:1705px;z-index:76" onChange="addChagedElement(this.name)">
<input name="winnerPlan2" type="text" value="<? print $_POST['winnerPlan2']?>" style="position:absolute;width:679px;left:80px;top:1735px;z-index:77" onChange="addChagedElement(this.name)">
<input name="winnerPlan3" type="text" value="<? print $_POST['winnerPlan3']?>" style="position:absolute;width:679px;left:80px;top:1768px;z-index:78" onChange="addChagedElement(this.name)">
<input name="winnerPlan4" type="text" value="<? print $_POST['winnerPlan4']?>" style="position:absolute;width:679px;left:80px;top:1802px;z-index:79" onChange="addChagedElement(this.name)">
<input name="winnerPlan5" type="text" value="<? print $_POST['winnerPlan5']?>" style="position:absolute;width:679px;left:80px;top:1836px;z-index:80" onChange="addChagedElement(this.name)">
<input name="winnerPlan6" type="text" value="<? print $_POST['winnerPlan6']?>" style="position:absolute;width:679px;left:80px;top:1870px;z-index:81" onChange="addChagedElement(this.name)">
<input name="winnerPlan7" type="text" value="<? print $_POST['winnerPlan7']?>" style="position:absolute;width:679px;left:80px;top:1904px;z-index:82" onChange="addChagedElement(this.name)">
<input name="winnerPlan8" type="text" value="<? print $_POST['winnerPlan8']?>" style="position:absolute;width:679px;left:80px;top:1938px;z-index:83" onChange="addChagedElement(this.name)">
<input name="dreamSymbol" type="text" value="<? print $_POST['dreamSymbol']?>" style="position:absolute;width:596px;left:162px;top:1975px;z-index:85" onChange="addChagedElement(this.name)">
<input name="editedField" type="hidden" value="">
<input name="id" type="hidden" value="<?print $_POST['id']?>">

<div id="text1" style="position:absolute; overflow:hidden; left:27px; top:1229px; width:460px; height:132px; z-index:70">
<div class="wpmd">
<div><B><U>Источники доходов в настоящем и будущем:</U></B></div>
<BR>
<OL type=A>
<li value=1>(работа по специальности, свое дело)&nbsp; или идея бизнес проекта1</li>
</OL>
<OL type=A>
<li value=2>(предпринимательство, сетевой бизнес)&nbsp; или идея бизнес проекта2</li>
</OL>
<OL type=A>
<li value=3>(инвестирование, недвижимость)&nbsp; или идея бизнес проекта3</li>
</OL>
</div></div>

<div id="table1" style="position:absolute; overflow:none; left:46px; top:1359px; width:719px; height:192px; z-index:74">
	<div class="wpmd">
		<div>
			<TABLE bgcolor="#FFFFFF" border=1 bordercolorlight="#C0C0C0" bordercolordark="#808080" cellspacing=0>
				<TR valign=top>
					<TD width=114 height=17 valign=middle>
						<div class="wpmd">
							<div align=center>Цель</div>
						</div>
					</TD>
					<TD width=202 height=17 valign=middle>
						<div class="wpmd">
							<div align=center>Образ результата, Сроки, стоимость</div>
						</div>
					</TD>
					<TD width=195 height=17 valign=middle>
						<div class="wpmd">
							<div align=center>Эмоция достижения</div>
						</div>
					</TD>
					<TD width=184 height=17 valign=middle>
						<div class="wpmd">
							<div align=center>Первые шаги, этапы достижения</div>
						</div>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a1" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a1']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b1" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b1']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c1" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c1']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d1" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d1']?></textarea>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a2" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a2']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b2" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b2']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c2" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c2']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d2" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d2']?></textarea>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a3" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a3']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b3" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b3']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c3" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c3']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d3" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d3']?></textarea>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a4" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a4']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b4" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b4']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c4" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c4']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d4" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d4']?></textarea>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a5" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a5']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b5" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b5']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c5" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c5']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d5" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d5']?></textarea>
					</TD>
				</TR>
				<TR valign=top>
					<TD width=114>
						<textarea name="a6" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a6']?></textarea>
					</TD>
					<TD width=202>
						<textarea name="b6" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b6']?></textarea>
					</TD>
					<TD width=195>
						<textarea name="c6" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c6']?></textarea>
					</TD>
					<TD width=184>
						<textarea name="d6" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d6']?></textarea>
					</TD>
				</TR>
			</TABLE>
		</div>
	</div>
</div>

<div id="text2" style="position:absolute; overflow:hidden; left:46px; top:1690px; width:715px; height:294px; z-index:75"><div class="wpmd">
<div align=center><font class="ws16"><B><U>Мой план победы!</U></B></font></div>
<div align=justify><font class="ws16"><B>1.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>2.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>3.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>4.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>5.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>6.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>7.</B></font></div>
<div align=justify><font class="ws6"><B><BR></B></font></div>
<div align=justify><font class="ws16"><B>8.</B></font></div>
</div></div>
<style type="text/css">
.wpmd {font-size: 13px;font-family: 'Arial';font-style: normal;font-weight: normal;}
</style>
<div id="text3" style="position:absolute; overflow:hidden; left:45px; top:1975px; width:128px; height:28px; z-index:84">
	<div class="wpmd">
		<div><font class="ws12">Символ мечты:</font></div>
	</div>
</div>

<div id="text4" style="position:absolute; overflow:hidden; left:46px; top:2010px; width:85px; height:27px; z-index:86">
	<div class="wpmd">
		<div><font class="ws12">Ход игры:</font></div>
	</div>
</div>

<div id="table2" style="position:absolute; left:43px; top:2030px; width:722px; height:41px; z-index:87">
	<div id="history" class="wpmd">
		<? print getUserHistory($_POST); ?>
	</div>
	<br>
	<div style="position:fixed;left:800px;bottom:20px;opacity:0.1" onMouseOver="this.style.opacity=1" onMouseOut="this.style.opacity=0.1;zoom:1"> 
		<center><input name="but" type="submit" value="Сохранить"><!-- br><a href="<? //print $name;?>">Скачать</a> --></center>
	</div>
	<br><br>
</div>
<input type="hidden" id="currentScroll" name="currentScroll" value="0">
</form>
</body>
</html>
<? fillCardValuesFomPost($_POST); ?>
