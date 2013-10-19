<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes" encoding="UTF-8"/>
	<xsl:template match="/">
		<xsl:apply-templates />
	</xsl:template>
	<xsl:template match="root">
		<h1 align="center">Пользователи</h1>
		<table border="1" align="center">
			<tr bgcolor="#CCFFCC">
				<td align="center">
					ФИО
				</td>
				<td align="center">
					Skype
				</td>
				<td align="center">
					E-mail
				</td>	
				<td align="center">
					Цвет фишки
				</td>
				<td align="center">
					Дата регистрации
				</td>
				<td align="center">
					Мечта
				</td>
				<td align="center">
					Код
				</td>									
				<td align="center">
					Доход от родителей
				</td>									
				<td align="center">
					Ресурс рождения
				</td>
				<td align="center">
					Пассивный доход\n(красный и синий круги)
				</td>
				<td align="center">
					Пассивный доход\n+зарплата(зеленый круг)
				</td>
				<td align="center">
					Общий R
				</td>
				<td align="center">
					Кредит
				</td>
				<td align="center">
					Время начала кредита
				</td>
				<td align="center">
					Время окончания кредита
				</td>
				<td align="center">
					Срахование от Ф.М.
				</td>
				<td align="center">
					Страхование от минусов рынка
				</td>
				<td align="center">
					Бизнес А ($)
				</td>
				<td align="center">
					Бизнес B ($)
				</td>
				<td align="center">
					Бизнес C ($)
				</td>
				<td align="center">
					Бизнес А (%)
				</td>
				<td align="center">
					Бизнес B (%)
				</td>
				<td align="center">
					Бизнес C (%)
				</td>
				<td align="center">
					Бизнес А (пассивный доход)
				</td>
				<td align="center">
					Бизнес B (пассивный доход)
				</td>				
				<td align="center">
					Бизнес C (пассивный доход)
				</td>
				<td align="center">
					Бизнес A (R)
				</td>
				<td align="center">
					Бизнес B (R)
				</td>
				<td align="center">
					Бизнес C (R)
				</td>
				<td align="center">
					Недвижимость A ($)
				</td>
				<td align="center">
					Недвижимость B ($)
				</td>
				<td align="center">
					Недвижимость C ($)
				</td>
				<td align="center">
					Недвижимость A (%)
				</td>
				<td align="center">
					Недвижимость B (%)
				</td>
				<td align="center">
					Недвижимость C (%)
				</td>
				<td align="center">
					Недвижимость A (пасивный доход)
				</td>
				<td align="center">
					Недвижимость B (пасивный доход)
				</td>
				<td align="center">
					Недвижимость C (пасивный доход)
				</td>
				<td align="center">
					Акции А
				</td>
				<td align="center">
					Акции В
				</td>
				<td align="center">
					Акции C
				</td>
				<td align="center">
					Профессия
				</td>
				<td align="center">
					з/п
				</td>
				<td align="center">
					Ресурс профессии
				</td>
				<td align="center">
					Образование
				</td>
				<td align="center">
					Дети
				</td>
				<td align="center">
					Фраза поддержки
				</td>
				<td align="center">
					Цель 1
				</td>
				<td align="center">
					Цель 2
				</td>
				<td align="center">
					Цель 3
				</td>
				<td align="center">
					Цель 4
				</td>
				<td align="center">
					Цель 5
				</td>
				<td align="center">
					Цель 6
				</td>
				<td align="center">
					Ресурс 1
				</td>
				<td align="center">
					Ресурс 2
				</td>
				<td align="center">
					Ресурс 3
				</td>
				<td align="center">
					Ресурс 4
				</td>
				<td align="center">
					Ресурс 5
				</td>
				<td align="center">
					Ресурс 6
				</td>
				<td align="center">
					Ресурс 7
				</td>
				<td align="center">
					Ресурс 8
				</td>
				<td align="center">
					Ресурс 9
				</td>
				<td align="center">
					Ресурс 10
				</td>
				<td align="center">
					Таланты к деятельности
				</td>				
			</tr>
		<xsl:apply-templates select="user" />
		</table>
	</xsl:template>
	<xsl:template match="//user">
	<tr>
	<xsl:if test="position() mod 2 = 0">
		<xsl:attribute name="bgcolor">#CCCCCC</xsl:attribute>
	</xsl:if>
			<td>
				<xsl:value-of select="@FIO"/>
			</td>
			<td>
				<xsl:value-of select="@skype"/>
			</td>
			<td>
				<xsl:value-of select="@email"/>
			</td>
			<td>
				<xsl:value-of select="@capColor"/>
			</td>
			<td>
				<xsl:value-of select="@date"/>
			</td>
			<td>
				<xsl:value-of select="@dream"/>
			</td>
			<td>
				<xsl:value-of select="@Code"/>
			</td>
			<td>
				<xsl:value-of select="@moneyFromParent"/>
			</td>
			<td>
				<xsl:value-of select="@bornSource"/>
			</td>
			<td>
				<xsl:value-of select="@pasIncomeBlueCircle"/>
			</td>
			<td>
				<xsl:value-of select="@pasIncomeGreenCircle"/>
			</td>
			<td>
				<xsl:value-of select="@commonR"/>
			</td>
			<td>
				<xsl:value-of select="@credit"/>
			</td>
			<td>
				<xsl:value-of select="@creditTBegin"/>
			</td>
			<td>
				<xsl:value-of select="@creditTEnd"/>
			</td>
			<td>
				<xsl:value-of select="@strahOtFM"/>
			</td>
			<td>
				<xsl:value-of select="@strahOtMR"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesAbaks"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesBbaks"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesCbaks"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesAProc"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesBProc"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesCProc"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesAPasIncome"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesBPasIncome"/>
			</td>
			<td>
				<xsl:value-of select="@bisnesCPasIncome"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesAR"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesBR"/>
			</td>	
			<td>
				<xsl:value-of select="@bisnesCR"/>
			</td>	
			<td>
				<xsl:value-of select="@statAbaks"/>
			</td>
			<td>
				<xsl:value-of select="@statBbaks"/>
			</td>
			<td>
				<xsl:value-of select="@statCbaks"/>
			</td>
			<td>
				<xsl:value-of select="@statAproc"/>
			</td>
			<td>
				<xsl:value-of select="@statBproc"/>
			</td>
			<td>
				<xsl:value-of select="@statCproc"/>
			</td>
			<td>
				<xsl:value-of select="@statApasIncome"/>
			</td>
			<td>
				<xsl:value-of select="@statBpasIncome"/>
			</td>
			<td>
				<xsl:value-of select="@statCpasIncome"/>
			</td>
			<td>
				<xsl:value-of select="@promA"/>
			</td>
			<td>
				<xsl:value-of select="@promB"/>
			</td>
			<td>
				<xsl:value-of select="@promC"/>
			</td>
			<td>
				<xsl:value-of select="@prof"/>
			</td>
			<td>
				<xsl:value-of select="@zp"/>
			</td>	
			<td>
				<xsl:value-of select="@profSource"/>
			</td>	
			<td>
				<xsl:value-of select="@study"/>
			</td>
			<td>
				<xsl:value-of select="@childrens"/>
			</td>
			<td>
				<xsl:value-of select="@exprUp"/>
			</td>
			<td>
				<xsl:value-of select="@prop1"/>
			</td>
			<td>
				<xsl:value-of select="@prop2"/>
			</td>
			<td>
				<xsl:value-of select="@prop3"/>
			</td>
			<td>
				<xsl:value-of select="@prop4"/>
			</td>
			<td>
				<xsl:value-of select="@prop5"/>
			</td>
			<td>
				<xsl:value-of select="@prop6"/>
			</td>
			<td>
				<xsl:value-of select="@res1"/>
			</td>
			<td>
				<xsl:value-of select="@res2"/>
			</td>
			<td>
				<xsl:value-of select="@res3"/>
			</td>
			<td>
				<xsl:value-of select="@res4"/>
			</td>
			<td>
				<xsl:value-of select="@res5"/>
			</td>
			<td>
				<xsl:value-of select="@res6"/>
			</td>
			<td>
				<xsl:value-of select="@res7"/>
			</td>
			<td>
				<xsl:value-of select="@res8"/>
			</td>
			<td>
				<xsl:value-of select="@res9"/>
			</td>
			<td>
				<xsl:value-of select="@res10"/>
			</td>
			<td>
				<xsl:value-of select="@cbManager"/>
				&#160;
				<xsl:value-of select="@cbUrist"/>
				&#160;
				<xsl:value-of select="@cbUrist"/>
				&#160;
				<xsl:value-of select="@cbEconomic"/>
				&#160;
				<xsl:value-of select="@cbIngeneer"/>
				&#160;
				<xsl:value-of select="@cbDoctor"/>
				&#160;
				<xsl:value-of select="@cbTourist"/>
				&#160;
				<xsl:value-of select="@cbTeacher"/>
				&#160;
				<xsl:value-of select="@cbDoner"/>
			</td>										
		</tr>
	</xsl:template>
</xsl:stylesheet>