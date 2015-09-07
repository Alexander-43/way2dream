<script language="javascript" type="text/javascript">
	$(document).ready(
		function() {
			$(':text').change(
				function(){
					addChagedElement(this);
					doAction(this);
				}
			);
			$('textarea').change(
				function(){
					addChagedElement(this);
					doAction(this);
				}
			);
			setReadOnly(config);
		}
	)
</script>
<style>
input.min {
	font-size:55%;
}
</style>
<div id="image2" style="position:absolute; overflow:hidden; left:17px; top:25px; width:770px; height:1147px; z-index:0">
	<img src="img/card.jpg" alt="" border=0 width=770 height=1147>
</div>
<input name="dream" type="text" style="position:absolute;width:620px;left:149px;top:37px;z-index:1">
<input name="FIO" type="text" style="position:absolute;width:620px;left:149px;top:13px;z-index:2">
<input name="prop1" type="text" style="position:absolute;width:317px;left:470px;top:169px;z-index:3">
<input name="prop2" type="text" style="position:absolute;width:317px;left:470px;top:209px;z-index:4">
<input name="prop3" type="text" style="position:absolute;width:317px;left:470px;top:250px;z-index:5">
<input name="prop4" type="text" style="position:absolute;width:317px;left:471px;top:375px;z-index:6">
<input name="prop5" type="text" style="position:absolute;width:317px;left:471px;top:417px;z-index:7">
<input name="prop6" type="text" style="position:absolute;width:317px;left:471px;top:458px;z-index:8">
<input name="res1" type="text" style="position:absolute;width:162px;left:121px;top:167px;z-index:9">
<input name="res2" type="text" style="position:absolute;width:162px;left:121px;top:202px;z-index:10">
<input name="res3" type="text" style="position:absolute;width:162px;left:121px;top:236px;z-index:11">
<input name="res4" type="text" style="position:absolute;width:162px;left:121px;top:271px;z-index:12">
<input name="res5" type="text" style="position:absolute;width:162px;left:121px;top:305px;z-index:13">
<input name="res6" type="text" style="position:absolute;width:162px;left:121px;top:340px;z-index:14">
<input name="res7" type="text" style="position:absolute;width:162px;left:121px;top:375px;z-index:15">
<input name="res8" type="text" style="position:absolute;width:162px;left:121px;top:409px;z-index:16">
<input name="res9" type="text" style="position:absolute;width:162px;left:121px;top:444px;z-index:17">
<input name="res10" type="text" style="position:absolute;width:153px;left:131px;top:477px;z-index:18">
<input type="checkbox" name="cbManager" <? TryCheck ($_POST['cbManager'], "Менеджер"); ?> value="Менеджер" style="position:absolute;left:179px;top:595px;z-index:19" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbUrist" <? TryCheck ($_POST['cbUrist'], "Юрист"); ?> value="Юрист" style="position:absolute;left:179px;top:624px;z-index:20" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbEconomic" <? TryCheck ($_POST['cbEconomic'], "Экономист"); ?> value="Экономист" style="position:absolute;left:179px;top:653px;z-index:21" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbIngeneer" <? TryCheck ($_POST['cbIngeneer'], "Инженер"); ?> value="Инженер" style="position:absolute;left:179px;top:682px;z-index:22" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbDoctor" <? TryCheck ($_POST['cbDoctor'], "Врач"); ?> value="Врач" style="position:absolute;left:345px;top:595px;z-index:23" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbTourist" <? TryCheck ($_POST['cbTourist'], "Турист"); ?> value="Турист" style="position:absolute;left:345px;top:624px;z-index:24" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbTeacher" <? TryCheck ($_POST['cbTeacher'], "Педагог"); ?> value="Педагог" style="position:absolute;left:345px;top:652px;z-index:25" onChange="addChagedElement(new String(this.name))">
<input type="checkbox" name="cbDoner" <? TryCheck ($_POST['cbDoner'], "Творец"); ?> value="Творец" style="position:absolute;left:345px;top:681px;z-index:26" onChange="addChagedElement(new String(this.name))">
<input name="credit" type="text" style="position:absolute;width:130px;left:448px;top:722px;z-index:27">
<input name="creditTBegin" type="text" style="position:absolute;width:89px;left:544px;top:614px;z-index:28">
<input name="creditTEnd" type="text" style="position:absolute;width:46px;left:734px;top:614px;z-index:29">
<input name="moneyFromParent" type="text" style="position:absolute;width:32px;left:296px;top:746px;z-index:30">
<input name="bornSource" type="text" style="position:absolute;width:32px;left:548px;top:746px;z-index:31">
<input class="min" name="bisnesAbaks_1" type="text" style="position:absolute;width:81px;left:81px;top:838px;z-index:32">
<input class="min" name="bisnesBbaks_1" type="text" style="position:absolute;width:81px;left:81px;top:900px;z-index:51">
<input class="min" name="bisnesCbaks_1" type="text" style="position:absolute;width:81px;left:81px;top:960px;z-index:33">

<input class="min" name="bisnesAbaks_2" type="text" style="position:absolute;width:81px;left:81px;top:857px;z-index:81">
<input class="min" name="bisnesBbaks_2" type="text" style="position:absolute;width:81px;left:81px;top:919px;z-index:82">
<input class="min" name="bisnesCbaks_2" type="text" style="position:absolute;width:81px;left:81px;top:979px;z-index:83">

<input class="min" name="bisnesAbaks_3" type="text" style="position:absolute;width:81px;left:81px;top:876px;z-index:32">
<input class="min" name="bisnesBbaks_3" type="text" style="position:absolute;width:81px;left:81px;top:938px;z-index:51">
<input class="min" name="bisnesCbaks_3" type="text" style="position:absolute;width:81px;left:81px;top:998px;z-index:33">
<!-- ***************** -->
<input class="min" name="bisnesAProc_1" type="text" style="position:absolute;width:51px;left:173px;top:838px;z-index:34">
<input class="min" name="bisnesBProc_1" type="text" style="position:absolute;width:51px;left:173px;top:900px;z-index:52">
<input class="min" name="bisnesCProc_1" type="text" style="position:absolute;width:51px;left:173px;top:960px;z-index:35">

<input class="min" name="bisnesAProc_2" type="text" style="position:absolute;width:51px;left:173px;top:857px;z-index:84">
<input class="min" name="bisnesBProc_2" type="text" style="position:absolute;width:51px;left:173px;top:919px;z-index:85">
<input class="min" name="bisnesCProc_2" type="text" style="position:absolute;width:51px;left:173px;top:979px;z-index:86">

<input class="min" name="bisnesAProc_3" type="text" style="position:absolute;width:51px;left:173px;top:876px;z-index:84">
<input class="min" name="bisnesBProc_3" type="text" style="position:absolute;width:51px;left:173px;top:938px;z-index:85">
<input class="min" name="bisnesCProc_3" type="text" style="position:absolute;width:51px;left:173px;top:998px;z-index:86">
<!-- ***************** -->
<input class="min" name="bisnesAR_1" type="text" style="position:absolute;width:53px;left:298px;top:838px;z-index:38">
<input class="min" name="bisnesBR_1" type="text" style="position:absolute;width:53px;left:298px;top:900px;z-index:54">
<input class="min" name="bisnesCR_1" type="text" style="position:absolute;width:53px;left:298px;top:960px;z-index:39">

<input class="min" name="bisnesAR_2" type="text" style="position:absolute;width:53px;left:298px;top:857px;z-index:90">
<input class="min" name="bisnesBR_2" type="text" style="position:absolute;width:53px;left:298px;top:919px;z-index:91">
<input class="min" name="bisnesCR_2" type="text" style="position:absolute;width:53px;left:298px;top:979px;z-index:92">

<input class="min" name="bisnesAR_3" type="text" style="position:absolute;width:53px;left:298px;top:876px;z-index:38">
<input class="min" name="bisnesBR_3" type="text" style="position:absolute;width:53px;left:298px;top:938px;z-index:54">
<input class="min" name="bisnesCR_3" type="text" style="position:absolute;width:53px;left:298px;top:998px;z-index:39">
<!-- ***************** -->
<input class="min" name="bisnesAActIncome_1" type="text" style="position:absolute;width:61px;left:228px;top:838px;z-index:36">
<input class="min" name="bisnesBActIncome_1" type="text" style="position:absolute;width:61px;left:228px;top:900px;z-index:53">
<input class="min" name="bisnesCActIncome_1" type="text" style="position:absolute;width:61px;left:228px;top:960px;z-index:37">

<input class="min" name="bisnesAActIncome_2" type="text" style="position:absolute;width:61px;left:228px;top:857px;z-index:87">
<input class="min" name="bisnesBActIncome_2" type="text" style="position:absolute;width:61px;left:228px;top:919px;z-index:88">
<input class="min" name="bisnesCActIncome_2" type="text" style="position:absolute;width:61px;left:228px;top:979px;z-index:89">

<input class="min" name="bisnesAActIncome_3" type="text" style="position:absolute;width:61px;left:228px;top:876px;z-index:87">
<input class="min" name="bisnesBActIncome_3" type="text" style="position:absolute;width:61px;left:228px;top:938px;z-index:88">
<input class="min" name="bisnesCActIncome_3" type="text" style="position:absolute;width:61px;left:228px;top:998px;z-index:89">
<!-- ***************** -->
<input name="exprUp" type="text" style="position:absolute;width:454px;left:280px;top:511px;z-index:80">
<input name="franshiza" type="text" style="position:absolute;width:224px;left:389px;top:1045px;z-index:93">
<input name="franProc" type="text" style="position:absolute;width:55px;left:625px;top:1045px;z-index:43" value="10" readonly>
<input name="capital" type="text" style="position:absolute;width:224px;left:389px;top:1120px;z-index:94">
<input name="capProc" type="text" style="position:absolute;width:55px;left:625px;top:1120px;z-index:44" value="10">
<input name="franshPasIncome" type="text" style="position:absolute;width:80px;left:689px;top:1045px;z-index:95">
<input name="capitalPasIncome" type="text" style="position:absolute;width:82px;left:688px;top:1120px;z-index:96">
<input name="riskStrah" type="text" style="position:absolute;width:181px;left:601px;top:684px;z-index:97">
<input name="code" type="text" style="position:absolute;width:200px;left:82px;top:91px;z-index:98">
<input name="studyDescription" type="text" style="position:absolute;width:237px;left:128px;top:1050px;z-index:99;">
<input name="study" type="text" style="position:absolute;width:170px;left:195px;top:1078px;z-index:99;">
<input name="prom" type="text" style="position:absolute;width:321px;left:459px;top:582px;z-index:100">
<input name="commonR" type="text" style="position:absolute;width:70px;left:766px;top:746px;z-index:101">

<input class="min" name="statAbaks_1" type="text" style="position:absolute;width:104px;left:509px;top:838px;z-index:40">
<input class="min" name="statBbaks_1" type="text" style="position:absolute;width:104px;left:509px;top:900px;z-index:41">
<input class="min" name="statCbaks_1" type="text" style="position:absolute;width:104px;left:509px;top:960px;z-index:42">

<input class="min" name="statAbaks_2" type="text" style="position:absolute;width:104px;left:509px;top:857px;z-index:102">
<input class="min" name="statBbaks_2" type="text" style="position:absolute;width:104px;left:509px;top:919px;z-index:103">
<input class="min" name="statCbaks_2" type="text" style="position:absolute;width:104px;left:509px;top:979px;z-index:104">

<input class="min" name="statAbaks_3" type="text" style="position:absolute;width:104px;left:509px;top:876px;z-index:102">
<input class="min" name="statBbaks_3" type="text" style="position:absolute;width:104px;left:509px;top:938px;z-index:103">
<input class="min" name="statCbaks_3" type="text" style="position:absolute;width:104px;left:509px;top:998px;z-index:104">


<input class="min" name="statAproc_1" type="text" style="position:absolute;width:55px;left:625px;top:838px;z-index:43">
<input class="min" name="statBproc_1" type="text" style="position:absolute;width:55px;left:625px;top:900px;z-index:44">
<input class="min" name="statCproc_1" type="text" style="position:absolute;width:55px;left:625px;top:960px;z-index:45">

<input class="min" name="statAproc_2" type="text" style="position:absolute;width:55px;left:625px;top:857px;z-index:43">
<input class="min" name="statBproc_2" type="text" style="position:absolute;width:55px;left:625px;top:919px;z-index:44">
<input class="min" name="statCproc_2" type="text" style="position:absolute;width:55px;left:625px;top:979px;z-index:45">

<input class="min" name="statAproc_3" type="text" style="position:absolute;width:55px;left:625px;top:876px;z-index:43">
<input class="min" name="statBproc_3" type="text" style="position:absolute;width:55px;left:625px;top:938px;z-index:44">
<input class="min" name="statCproc_3" type="text" style="position:absolute;width:55px;left:625px;top:998px;z-index:45">


<input class="min" name="statApasIncome_1" type="text" style="position:absolute;width:69px;left:695px;top:838px;z-index:43">
<input class="min" name="statBpasIncome_1" type="text" style="position:absolute;width:69px;left:695px;top:900px;z-index:44">
<input class="min" name="statCpasIncome_1" type="text" style="position:absolute;width:69px;left:695px;top:960px;z-index:45">

<input class="min" name="statApasIncome_2" type="text" style="position:absolute;width:69px;left:695px;top:857px;z-index:43">
<input class="min" name="statBpasIncome_2" type="text" style="position:absolute;width:69px;left:695px;top:919px;z-index:44">
<input class="min" name="statCpasIncome_2" type="text" style="position:absolute;width:69px;left:695px;top:979px;z-index:45">

<input class="min" name="statApasIncome_3" type="text" style="position:absolute;width:69px;left:695px;top:876px;z-index:43">
<input class="min" name="statBpasIncome_3" type="text" style="position:absolute;width:69px;left:695px;top:938px;z-index:44">
<input class="min" name="statCpasIncome_3" type="text" style="position:absolute;width:69px;left:695px;top:998px;z-index:45">


<input name="prof" type="text" style="position:absolute;width:77px;left:105px;top:1022px;z-index:46">
<input name="zp" type="text" style="position:absolute;width:40px;left:228px;top:1023px;z-index:47">
<input name="profSource" type="text" style="position:absolute;width:36px;left:328px;top:1023px;z-index:48">
<input name="childrensCount" type="text" style="position:absolute;width:140px;left:436px;top:543px;z-index:49">
<input name="childrens" type="text" style="position:absolute;width:90px;left:690px;top:543px;z-index:49">
<input name="activeIncomeGreenCircle" type="text" style="position:absolute;width:200px;left:34px;top:1172px;z-index:105">
<input name="passIncomeAllCircle" type="text" style="position:absolute;width:226px;left:388px;top:1172px;z-index:106">