<table width="100%" height="600"  border="0">
	<tr>
		<td valign="top">
			<? showActiveGamers(0); ?>
		</td>
		<td align="top" width="70%">
			<object type="application/x-shockwave-flash" data="<? print swfFolder."/";?>presenter.swf" width="100%" height="100%">
				<param name="movie" value="<? print swfFolder."/";?>presenter.swf" />
				<param name="wmode" value="transparent" />
				<param name="salign" value="t">
				<param name="allowScriptAccess" value="sameDomain" />
				<param name="flashvars" value="pathToXmlBase=<? print xmlForFlash."?".time() ?>&operPage=<? print operPage?>" />
				<EMBED src="<? print swfFolder."/";?>presenter.swf" FLASHVARS="pathToXmlBase=<? print xmlForFlash."?".time() ?>&operPage=<? print operPage?>" quality="high" wmode="transparent" WIDTH="100%" HEIGHT="100%" TYPE="application/x-shockwave-flash">
				</EMBED>
			</object>
		</td>
	</tr>
</table>