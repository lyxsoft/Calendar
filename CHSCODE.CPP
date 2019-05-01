//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChsCode.h"

const AnsiString	strTermCode = "小寒大寒立春雨水惊蛰春分清明谷雨立夏小满芒种夏至小暑大暑立秋处暑白露秋分寒露霜降立冬小雪大雪冬至";
const AnsiString	strSkyCode = "甲乙丙丁戊己庚辛壬癸";
const AnsiString	strEarthCode = "子丑寅卯辰巳午末申酉戌亥";
const AnsiString	strBirthCode = "鼠牛虎兔龙蛇马羊猴鸡狗猪";
const AnsiString	strMonthCode = "正二三四五六七八九十1112";
const AnsiString	strDayCode = "十一二三四五六七八九初十廿三初二三";
const AnsiString	strNumber = "负零一二三四五六七八九十百千万";
const AnsiString	strWeekDay = "日一二三四五六";
const AnsiString	strWeekDayStart = "星期";
//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString	ChineseCode (long nValue, CodeIndex eCode)
{
	AnsiString	strResult;

	if (nValue < 0 && eCode != NumCode)
		return AnsiString ("");

	switch (eCode)
	{
	case	NumCode:
		if (nValue < 0)
		{
			strResult = strNumber.SubString (1, 2);
			nValue = -nValue;
		}
		else if (nValue == 0)
			return	strNumber.SubString (3, 2);
		if (nValue > 99999)
			return strResult;
		else
		{
			long		nBitCount = 0;
			AnsiString	strNum = "";

			while (nValue >0)
			{
				if ((nValue % 10) != 0)
				{
					if (nBitCount == 1 && (nValue % 10) == 1)
						strNum = strNumber.SubString (23, 2) + strNum;
					else
					{
						if (nBitCount > 0)
							strNum = strNumber.SubString (23 + (nBitCount -1) * 2, 2) + strNum;
						strNum = strNumber.SubString (3 + (nValue % 10) * 2, 2) + strNum;
					}
				}
				else if (nBitCount > 0 && (strNum.IsEmpty () || strNum.SubString(1, 2) != strNumber.SubString(3, 2)))
				{
					strNum = strNumber.SubString(3, 2) + strNum;
				}
				nValue /= 10;
				nBitCount ++;
			}
			return strNum;
		}
	case	SkyCode:
		nValue = nValue % 10;
		if (nValue >= 0 && nValue < 10)
			return strSkyCode.SubString (nValue * 2 + 1, 2);
		break;
	case	EarthCode:
		nValue = nValue % 12;
		if (nValue >= 0 && nValue < 12)
			return strEarthCode.SubString (nValue * 2 + 1, 2);
		break;
	case	WeekDay:
		nValue = (nValue - 1) % 7;
		if (nValue >= 0 && nValue < 7)
			return strWeekDayStart + strWeekDay.SubString (nValue * 2 + 1, 2);
		break;
	case	MoonMonth:
		nValue = (nValue - 1) % 12;
		if (nValue >= 0 && nValue < 12)
		{
			if (nValue == 0)
				return strMonthCode.SubString (1, 2);
			else
				return ChineseCode (nValue + 1, NumCode);
		}
		break;
	case	MoonMonthShort:
		nValue = (nValue - 1) % 12;
		if (nValue >= 0 && nValue < 12)
			return strMonthCode.SubString (nValue * 2 + 1, 2);
		break;
	case	MoonDay:
		nValue = (nValue - 1) % 30 + 1;
		if (nValue > 0 && nValue <= 30)
		{
			if (nValue <= 10)
				return strDayCode.SubString (21, 2) + ChineseCode (nValue, NumCode);
			else
				return ChineseCode (nValue, NumCode);
		}
		break;
	case	MoonDayShort:
		nValue = (nValue - 1) % 30 + 1;
		if (nValue > 0 && nValue <= 30)
		{
			if ((nValue % 10) == 0)
				return strDayCode.SubString ((nValue / 10) * 2 + 27, 2) + strDayCode.SubString (1, 2);
			else
				return strDayCode.SubString ((nValue / 10) * 2 + 21, 2) + strDayCode.SubString ((nValue % 10) * 2 + 1, 2);
		}
		break;
	case	BirthCode:
		nValue = (nValue - 1) % 12;
		if (nValue >= 0 && nValue < 12)
			return strBirthCode.SubString (nValue * 2 + 1, 2);
		break;
	case	TermCode:
		nValue = (nValue - 1) % 24;
		if (nValue >= 0 && nValue < 24)
			return strTermCode.SubString (nValue * 4 + 1, 4);
		break;
	}
	return AnsiString ("");
}
//---------------------------------------------------------------------------

