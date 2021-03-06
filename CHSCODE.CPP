//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChsCode.h"

const AnsiString	strTermCode = "С����������ˮ���ݴ���������������С��â������С��������ﴦ���¶��ֺ�¶˪������Сѩ��ѩ����";
const AnsiString	strSkyCode = "���ұ����켺�����ɹ�";
const AnsiString	strEarthCode = "�ӳ���î������ĩ�����纥";
const AnsiString	strBirthCode = "��ţ������������Ｆ����";
const AnsiString	strMonthCode = "�������������߰˾�ʮ1112";
const AnsiString	strDayCode = "ʮһ�����������߰˾ų�ʮإ��������";
const AnsiString	strNumber = "����һ�����������߰˾�ʮ��ǧ��";
const AnsiString	strWeekDay = "��һ����������";
const AnsiString	strWeekDayStart = "����";
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

