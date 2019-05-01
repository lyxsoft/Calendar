//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FestItem.h"
#include "ChsCode.h"
#include "Externs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString		strNewLine("\n");

//---------------------------------------------------------------------------
bool    CFestItem::RegSaveItem (TRegistry *RegKey)
{
	try
	{
		RegKey->WriteString ("Name", strName);
		RegKey->WriteString ("ShortName", strShortName);
		RegKey->WriteString ("Remarks", strRemarks);
		RegKey->WriteInteger ("YearFrom", nYearFrom);
		RegKey->WriteInteger ("YearTo", nYearTo);
		RegKey->WriteInteger ("FestMode", nFestMode);
		RegKey->WriteInteger ("Month", nMonth);
		RegKey->WriteInteger ("Day", nDay);
		RegKey->WriteInteger ("DayDiff", nDayDiff);
		RegKey->WriteInteger ("WeekNo", nWeekNo);
		RegKey->WriteInteger ("WeekDay", nWeekDay);
		RegKey->WriteInteger ("Term", nTerm);
		RegKey->WriteBool ("IgnorLeepMonth", bIgnorLeepMonth);
		RegKey->WriteBool ("ShowYearCount", bShowYearCount);
		RegKey->WriteBool ("IsHoliday", bIsHoliday);
		RegKey->WriteInteger ("HolidayDays", nFestDays);
		RegKey->WriteBool ("HolidayAtWeekend", bFestAtWeekend);
		return true;
	}
	catch (Exception &exception)
	{
		return false;
	}
}
//---------------------------------------------------------------------------
bool    CFestItem::RegReadItem (TRegistry *RegKey)
{
	if (RegKey->ValueExists ("Name") &&
		RegKey->ValueExists ("ShortName") &&
		RegKey->ValueExists ("Remarks") &&
		RegKey->ValueExists ("YearFrom") &&
		RegKey->ValueExists ("YearTo") &&
		RegKey->ValueExists ("FestMode"))
	{
		strName = RegKey->ReadString ("Name");
		strShortName = RegKey->ReadString ("ShortName");
		strRemarks = RegKey->ReadString ("Remarks");
		nYearFrom = RegKey->ReadInteger ("YearFrom");
		nYearTo = RegKey->ReadInteger ("YearTo");
		nFestMode = RegKey->ReadInteger ("FestMode");

		if (RegKey->ValueExists ("Month"))
			nMonth = RegKey->ReadInteger ("Month");
		else
			nMonth = 0;
		if (RegKey->ValueExists ("Day"))
			nDay = RegKey->ReadInteger ("Day");
		else
			nDay = 0;
		if (RegKey->ValueExists ("DayDiff"))
			nDayDiff = RegKey->ReadInteger ("DayDiff");
		else
			nDayDiff = 0;
		if (RegKey->ValueExists ("WeekNo"))
			nWeekNo = RegKey->ReadInteger ("WeekNo");
		else
			nWeekNo = 0;
		if (RegKey->ValueExists ("WeekDay"))
			nWeekDay = RegKey->ReadInteger ("WeekDay");
		else
			nWeekDay = 0;
		if (RegKey->ValueExists ("Term"))
			nTerm = RegKey->ReadInteger ("Term");
		else
			nTerm = 0;
		if (RegKey->ValueExists ("IgnorLeepMonth"))
			bIgnorLeepMonth = RegKey->ReadBool ("IgnorLeepMonth");
		else
			bIgnorLeepMonth = false;
		if (RegKey->ValueExists ("ShowYearCount"))
			bShowYearCount = RegKey->ReadBool ("ShowYearCount");
		else
			bShowYearCount = false;
		if (RegKey->ValueExists ("IsHoliday"))
			bIsHoliday = RegKey->ReadBool ("IsHoliday");
		else
			bIsHoliday = true;
		if (RegKey->ValueExists ("HolidayDays"))
			nFestDays = RegKey->ReadInteger ("HolidayDays");
		else
			nFestDays = 1;
		if (RegKey->ValueExists ("HolidayAtWeekend"))
			bFestAtWeekend = RegKey->ReadBool ("HolidayAtWeekend");
		else
			bFestAtWeekend = true;
		return true;
	}
	else
		return false;
}
//---------------------------------------------------------------------------
bool    CFestItem::ShowItem (TListItem *cpListItem)
{
	cpListItem->Caption = strName;
	switch (nFestMode)
	{
	case	1:
		if (nDayDiff == 0)
			cpListItem->ImageIndex = 0;
		else
			cpListItem->ImageIndex = 3;
		break;
	case	2:
		cpListItem->ImageIndex = 2;
		break;
	case	-1:
		cpListItem->ImageIndex = 1;
		break;
	}
	return true;
}
//---------------------------------------------------------------------------
AnsiString	CFestItem::DateText ()
{
	AnsiString	strResult = "";

	if (nYearFrom <= 0)
		strResult = AnsiString("每年");
	else
	{
		if (nYearTo <= 0)
			strResult = AnsiString("从") + AnsiString(nYearFrom) + "年开始每年";
		else if (nYearTo != nYearFrom)
			strResult = AnsiString("从") + AnsiString(nYearFrom) + "年至" + AnsiString(nYearTo) + "年";
		else
			strResult = AnsiString(nYearFrom) + "年";
	}
	switch (nFestMode)
	{
	case	1:
		if (nDayDiff == 0)
			strResult += AnsiString(nMonth) + "月" + AnsiString(nDay) + "日";
		else
			strResult += AnsiString("距") + AnsiString(nMonth) + "月" + AnsiString(nDay) + "日" + AnsiString(nDayDiff) + "天";
		break;
	case	2:
		strResult += ((nMonth >= 1 && nMonth <= 12) ? (AnsiString(nMonth) + "月第") : AnsiString("年度第")) + AnsiString(nWeekNo) + "个" + ChineseCode (nWeekDay, WeekDay);
		break;
	case	3:
		strResult += ChineseCode(nTerm + 1, TermCode);
		break;
	case	-1:
		if (nDayDiff == 0)
			strResult += AnsiString("农历") + ChineseCode(nMonth, MoonMonth) + "月" + ChineseCode(nDay, MoonDay);
		else
			strResult += AnsiString("农历距") + ChineseCode(nMonth, MoonMonth) + "月" + ChineseCode(nDay, MoonDay) + "日" + ChineseCode(nDayDiff, NumCode) + "天";
		break;
	}
	return strResult;
}
//---------------------------------------------------------------------------
int		CFestItem::IsFestival (const CDateTime &cDateTime, const MoonDate &cMoonDate)
{
	CDateTime	cFestDate;
	MoonDate	cFestMoonDate;

	if (nYearFrom > 0)
	{
		if (nYearTo <=0)
		{
			if (cDateTime.Year () < nYearFrom)
				return false;
		}
		else
		{
			if (cDateTime.Year () < nYearFrom || cDateTime.Year() > nYearTo)
				return false;
		}
	}

	switch (nFestMode)
	{
	case	1:
		cFestDate = CDateTime (cDateTime.Year(), nMonth, nDay);
		cFestDate += nDayDiff;
		break;
	case	2:
		if (nMonth >= 1 && nMonth <= 12)
		{
			cFestDate = CDateTime (cDateTime.Year(), nMonth, 1);
			if (nWeekDay >= cFestDate.DayOfWeek())
				cFestDate += nWeekDay - cFestDate.DayOfWeek() + (nWeekNo - 1) * 7;
			else
				cFestDate += nWeekDay - cFestDate.DayOfWeek() + nWeekNo * 7;
		}
		else
		{
			cFestDate = CDateTime (cDateTime.Year(), nMonth, 1);
			cFestDate += nWeekDay - cFestDate.DayOfWeek () + (nWeekNo - cFestDate.WeekOfYear (eFirstDayOfYear)) * 7;
		}
		break;
	case	3:
		if (CaleSunTerm (cDateTime - nDayDiff) == (nTerm + 1))
			return 1;
		else if (nFestDays >= 1)
		{
			long	nFestDayCount;
			long	nFestDayLimit;

			nFestDayLimit = nFestDays;
			for (nFestDayCount = 1; nFestDayCount < nFestDays + 2; nFestDayCount ++)
			{
				if (nFestDayCount <= nFestDayLimit)
				{
					if (bFestAtWeekend && ((cDateTime - nDayDiff - nFestDayCount).DayOfWeek() % 7) <= 1)
						nFestDayLimit ++;
					if (nFestDayCount < nFestDayLimit && CaleSunTerm (cDateTime - nDayDiff - nFestDayCount) == (nTerm + 1))
						return -1;
				}
				else
					break;
			}
		}
		return 0;
	case	-1:
		if (nDayDiff == 0)
			cFestMoonDate = cMoonDate;
		else
			cFestMoonDate = CaleMoonDate (cDateTime - nDayDiff);
		if (cFestMoonDate.MoonMonth == nMonth && cFestMoonDate.MoonDay == nDay && !(cFestMoonDate.MoonDouble && bIgnorLeepMonth))
			return 1;
		else if (nFestDays >= 1)
		{
			long	nFestDayCount;
			long	nFestDayLimit;

			nFestDayLimit = nFestDays;
			for (nFestDayCount = 1; nFestDayCount < nFestDays + 2; nFestDayCount ++)
			{
				if (nFestDayCount <= nFestDayLimit)
				{
					if (bFestAtWeekend && ((cDateTime - nDayDiff - nFestDayCount).DayOfWeek() % 7) <= 1)
						nFestDayLimit ++;
					if (nFestDayCount < nFestDayLimit)
					{
						cFestMoonDate = CaleMoonDate (cDateTime - nDayDiff - nFestDayCount);
						if (cFestMoonDate.MoonMonth == nMonth && cFestMoonDate.MoonDay == nDay && !(cFestMoonDate.MoonDouble && bIgnorLeepMonth))
							return -1;
					}
				}
				else
					break;
			}
		}
		return 0;
	default:
		return 0;
	}

	if (cFestDate.SameDate (cDateTime))
		return 1;
	else if (nFestDays >= 1 && ((long)cDateTime - (long)cFestDate) > 0 && \
		((((long)cDateTime - (long)cFestDate) < nFestDays) ||	\
		 (bFestAtWeekend && ((long)cDateTime - (long)cFestDate) < (nFestDays + (long)(((long)cDateTime - (long)cFestDate - cDateTime.DayOfWeek() + cFestDate.DayOfWeek()) / 7) * 2 + (cFestDate.DayOfWeek() == 1 ? 1 : 0)))))
		return -1;
	else
		return 0;
}
//---------------------------------------------------------------------------
bool    CFestList::RegSaveList (void)
{
	TRegistry	*RegKey;
	long		ItemCount;
	CFestItem	*cpFestItem;

	if (!bDirty)
		return true;

	RegKey = new (TRegistry);
	RegKey->RootKey = HKEY_CURRENT_USER;
	if (!RegKey->OpenKey (strRegRoot, true))
	{
		delete RegKey;
		return false;
	}

	if (RegKey->HasSubKeys ())
	{
		//Delete the old keys
		ItemCount = 0;
		while (RegKey->KeyExists (AnsiString(ItemCount)))
		{
			RegKey->DeleteKey (AnsiString (ItemCount));
			ItemCount ++;
		}
	}
	for (ItemCount = 0, cpFestItem = (CFestItem *)cpFirstItem; cpFestItem != NULL; ItemCount ++)
	{
		if (RegKey->OpenKey (AnsiString (ItemCount), true))
		{
			if (!cpFestItem->RegSaveItem (RegKey))
			{
				RegKey->OpenKey (strRegRoot, true);
				delete RegKey;
				return false;
			}
			RegKey->OpenKey (strRegRoot, true);
		}
		cpFestItem = (CFestItem *)cpFestItem->cpNextItem;
	}
	bDirty = false;
	delete RegKey;
	return true;
}
//---------------------------------------------------------------------------
bool    CFestList::RegReadList (void)
{
	TRegistry	*RegKey;

	RegKey = new (TRegistry);
	RegKey->RootKey = HKEY_CURRENT_USER;
	if (!RegKey->OpenKey (strRegRoot, false))
	{
		delete RegKey;
		return false;
	}

	long		ItemCount;
	CFestItem	*cpFestItem;

	if (RegKey->HasSubKeys ())
	{
		//Read sub Keys
		Clear ();
		ItemCount = 0;
		while (RegKey->KeyExists (AnsiString(ItemCount)))
		{
			if (RegKey->OpenKey (AnsiString (ItemCount), false))
			{
				cpFestItem = new CFestItem;
				if (cpFestItem != NULL)
				{
					if (cpFestItem->RegReadItem (RegKey))
					{
						AddItem (cpFestItem);
					}
					else
						delete cpFestItem;
				}
				RegKey->OpenKey (strRegRoot, true);
			}
			ItemCount ++;
		}
	}
	bDirty = false;
	delete RegKey;
	return true;
}
//---------------------------------------------------------------------------
bool	CFestList::ShowList (TListView *cpListView)
{
	CFestItem	*cpCurItem;
	long		nItemCount;
	TListItem	*NewListItem;

	cpListView->Items->Clear ();
	for (nItemCount = 0, cpCurItem = (CFestItem *)cpFirstItem; cpCurItem != NULL; nItemCount ++)
	{
		NewListItem = cpListView->Items->Add ();
		NewListItem->Data = (void *)nItemCount;
		cpCurItem->ShowItem (NewListItem);
		cpCurItem = (CFestItem *)cpCurItem->cpNextItem;
	}
	return true;
}
//---------------------------------------------------------------------------
AnsiString	CFestList::GetFestival (const CDateTime &cDateTime, const MoonDate &cMoonDate, bool bAllFestival, bool *bpIsFestival, bool *bpIsHoliday)
{
	CFestItem	*cpCurItem;
	AnsiString	strResult = "";

	if (bpIsFestival != NULL)
		*bpIsFestival = false;
	if (bpIsHoliday != NULL)
		*bpIsHoliday = false;

	for (cpCurItem = (CFestItem *)cpFirstItem; cpCurItem != NULL; cpCurItem = (CFestItem *)cpCurItem->cpNextItem)
	{
		switch (cpCurItem->IsFestival (cDateTime, cMoonDate))
		{
		case	1:
			if (bpIsFestival != NULL)
				*bpIsFestival = true;

			if (!bAllFestival)
			{
				if (strResult.IsEmpty ())
					strResult = cpCurItem->strShortName.IsEmpty() ? cpCurItem->strName : cpCurItem->strShortName;
			}
			else
			{
				if (strResult.IsEmpty ())
					strResult = cpCurItem->strName;
				else
					strResult += strNewLine + cpCurItem->strName;
				if (cpCurItem->bShowYearCount && cpCurItem->nYearFrom > 0)
					strResult += AnsiString(" ") + AnsiString (cDateTime.Year() - cpCurItem->nYearFrom) + "周年";
			}
		case	-1:
			if (bpIsHoliday != NULL)
				*bpIsHoliday |= cpCurItem->bIsHoliday;
			else if (!bAllFestival)
				return strResult;
			break;
		}
	}
	return strResult;
}
//---------------------------------------------------------------------------
bool		CFestList::IsFestival (const CDateTime &cDateTime)
{
	MoonDate	cMoonDate;
	CFestItem	*cpCurItem;

	cMoonDate = CaleMoonDate (cDateTime);
	for (cpCurItem = (CFestItem *)cpFirstItem; cpCurItem != NULL; cpCurItem = (CFestItem *)cpCurItem->cpNextItem)
	{
		if (cpCurItem->IsFestival (cDateTime, cMoonDate) == 1)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool		CFestList::IsHoliday (const CDateTime &cDateTime)
{
	MoonDate	cMoonDate;
	CFestItem	*cpCurItem;

	cMoonDate = CaleMoonDate (cDateTime);
	for (cpCurItem = (CFestItem *)cpFirstItem; cpCurItem != NULL; cpCurItem = (CFestItem *)cpCurItem->cpNextItem)
	{
		if (cpCurItem->IsFestival (cDateTime, cMoonDate) != 0 && cpCurItem->bIsHoliday)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------

