<?
header("Content-Type: text/html; charset=utf-8");
	include ('vars.inc');
	include ('domXml.inc');
	include (incFolder.'func.inc');
	print("<script>var GLOBAL_MSG=".json_encode($ini->getAll(),true).";</script>");
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
<!DOCTYPE HTML PUBLIC "-//W3C//Dtd HTML 4.01 transitional//EN">
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
<style>
	.saveButton {
		font-size: 18px;
		width: 120px;
		height: 40px;
		color: white;
		border-radius: 20px 20px 20px 20px;
		background-image: url(img/button.png);
		background-position: 0% 20%;
		cursor: pointer;
	}
	.targetsTable td {
		height : 32px;
		color: #003300;
	}
	.w202 {
		width:202pxpx;
	}
</style>
</head>
<body>
<form name="editForm" method="POST" action="#" onSubmit="editFormSubmit(this)">
<!-- <input name="sourceIncomeA" type="text" value="<? print $_POST['sourceIncomeA']?>" style="position:absolute;width:270px;left:492px;top:1270px;z-index:71" onChange="addChagedElement(this.name)">
<input name="sourceIncomeB" type="text" value="<? print $_POST['sourceIncomeB']?>" style="position:absolute;width:271px;left:492px;top:1299px;z-index:72" onChange="addChagedElement(this.name)">
<input name="sourceIncomeC" type="text" value="<? print $_POST['sourceIncomeC']?>" style="position:absolute;width:272px;left:492px;top:1328px;z-index:73" onChange="addChagedElement(this.name)"> -->
<? require(incFolder.'card.inc'); ?>
<input name="editedField" type="hidden" value="">
<input name="id" type="hidden" value="<?print $_POST['id']?>">

<div id="text1" style="position:absolute; overflow:hidden; left:27px; top:1229px; width:860px; height:132px; z-index:70">
<div class="wpmd">
<div><B><U><?php print $messages->msg("present_and_future_income.present_and_future_income");?></U></B></div>
<br>
<table border='0' width="770px" style="font-size: 13px;">
	<tr>
		<td width="470px">
			<?php print $messages->msg("present_and_future_income.sourceIncomeA");?>
		</td>
		<td>
			<input size="40" name="sourceIncomeA" type="text" value="<? print $_POST['sourceIncomeA']?>" style="width:270px;z-index:71" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td>
			<?php print $messages->msg("present_and_future_income.sourceIncomeB");?>
		</td>
		<td>
			<input size="40" name="sourceIncomeB" type="text" value="<? print $_POST['sourceIncomeB']?>" style="width:270px;z-index:72" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td>
			<?php print $messages->msg("present_and_future_income.sourceIncomeC");?>
		</td>
		<td>
			<input size="40" name="sourceIncomeC" type="text" value="<? print $_POST['sourceIncomeC']?>" style="width:270px;z-index:73" onChange="addChagedElement(this.name)">
		</td>
	</tr>
</table>
</div></div>

<div id="table1" style="position:absolute; overflow:none; left:46px; top:1359px; width:719px; height:192px; z-index:74">
	<div class="wpmd">
		<div>
			<table class="targetsTable" bgcolor="#FFFFFF" border="1" bordercolorlight="#C0C0C0" bordercolordark="#808080" cellspacing="0">
				<tr valign="top">
					<td width="130px" valign="middle" align="center" height="35px">
						<div><?php print $messages->msg("targetsTable.target");?></div>
					</td>
					<td width="202px" valign="middle" align="center">
						<div><?php print $messages->msg("targetsTable.result_time_cost");?></div>
					</td>
					<td width="202px" valign="middle" align="center">
						<div><?php print $messages->msg("targetsTable.motion");?></div>
					</td>
					<td width="202px" valign="middle" align="center">
						<div><?php print $messages->msg("targetsTable.steps");?></div>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a1" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a1']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b1" style="border:0;width:202px;" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b1']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c1" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c1']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d1" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d1']?></textarea>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a2" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a2']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b2" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b2']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c2" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c2']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d2" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d2']?></textarea>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a3" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a3']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b3" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b3']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c3" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c3']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d3" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d3']?></textarea>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a4" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a4']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b4" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b4']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c4" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c4']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d4" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d4']?></textarea>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a5" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a5']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b5" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b5']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c5" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c5']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d5" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d5']?></textarea>
					</td>
				</tr>
				<tr valign="top">
					<td width="130px" style="height:35px">
						<textarea name="a6" style="border:0" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['a6']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="b6" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['b6']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="c6" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['c6']?></textarea>
					</td>
					<td width="202px">
						<textarea cols="39" name="d6" style="border:0;width:202px" onKeyUp="addChagedElement(new String(this.name))"><? print $_POST['d6']?></textarea>
					</td>
				</tr>
			</table>
		</div>
	</div>
</div>

<div id="text2" style="position:absolute; overflow:hidden; left:46px; top:1650px; width:715px; height:294px; z-index:75"><div class="wpmd">
<div align="center"><font class="ws16"><B><U><?php print $messages->msg("other.winnerplan");?></U></B></font></div>
<br>
<table>
	<tr>
		<td width="30px" height="25px">
			1.
		</td>
		<td>
			<input size="140" name="winnerPlan1" type="text" value="<? print $_POST['winnerPlan1']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			2.
		</td>
		<td>
			<input size="140" name="winnerPlan2" type="text" value="<? print $_POST['winnerPlan2']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			3.
		</td>
		<td>
			<input size="140" name="winnerPlan3" type="text" value="<? print $_POST['winnerPlan3']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			4.
		</td>
		<td>
			<input size="140" name="winnerPlan4" type="text" value="<? print $_POST['winnerPlan4']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			5.
		</td>
		<td>
			<input size="140" name="winnerPlan5" type="text" value="<? print $_POST['winnerPlan5']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			6.
		</td>
		<td>
			<input size="140" name="winnerPlan6" type="text" value="<? print $_POST['winnerPlan6']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			7.
		</td>
		<td>
			<input size="140" name="winnerPlan7" type="text" value="<? print $_POST['winnerPlan7']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
	<tr>
		<td height="25px">
			8.
		</td>
		<td>
			<input size="140" name="winnerPlan8" type="text" value="<? print $_POST['winnerPlan8']?>" style="width:679px;z-index:76" onChange="addChagedElement(this.name)">
		</td>
	</tr>
</table>
</div></div>
<style type="text/css">
.wpmd {font-size: 13px;font-family: 'Arial';font-style: normal;font-weight: normal;}
</style>
<div id="text3" style="position:absolute; overflow:hidden; left:45px; top:1900px; width:828px; height:28px; z-index:84">
	<div class="wpmd">
		<div><font class="ws12"><?php print $messages->msg("other.dreamSymbol");?></font>
		<input size="135" name="dreamSymbol" type="text" value="<? print $_POST['dreamSymbol']?>" style="width:616px;z-index:85" onChange="addChagedElement(this.name)"></div>
	</div>
</div>

<div id="text4" style="position:absolute; overflow:hidden; left:46px; top:1930px; width:85px; height:27px; z-index:86">
	<div class="wpmd">
		<div><font class="ws12"><?php print $messages->msg("other.gameStatus");?></font></div>
	</div>
</div>

<div id="table2" style="position:absolute; left:43px; top:1960px; width:722px; height:41px; z-index:87">
	<div id="history" class="wpmd">
		<? print getUserHistory($_POST); ?>
	</div>
	<br><br>
</div>
<input type="hidden" id="currentScroll" name="currentScroll" value="0">
<div style="position:fixed;left:900px;top:20px;"> 
	<button name="but" type="submit" title="<?php print $messages->msg("buttons.save");?>">	
		<img src="img/save.png" style="cursor:pointer">
	</button>
</div>
<div style="position:fixed;left:960px;top:20px;">
	<a href="inc/get_pdf.php?id=<?php print $_GET['id'];?>">
		<button name="pdf" type="button" title="<?php print $messages->msg("buttons.downloadAsPdf");?>"> 
			<img src="img/pdf.png" style="cursor:pointer" title="<?php print $messages->msg("buttons.downloadAsPdf");?>">
		</button>
	</a>
</div>
</form>
</body>
</html>
<? fillCardValuesFomPost($_POST); ?>
