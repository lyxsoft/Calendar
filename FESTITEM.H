//---------------------------------------------------------------------------
#ifndef FestItemH
#define FestItemH
#include <vcl.h>
#include <Registry.hpp>

#include "Chain.h"
#include "LyxDateTime.h"
#include "ChsCalendar.h"

//---------------------------------------------------------------------------
class CFestItem : public CChainItem
{
private:
public:
	AnsiString  strName;
	AnsiString	strShortName;
	AnsiString  strRemarks;
	long		nYearFrom;  //<=0 Every Year
	long		nYearTo;
	long		nFestMode;  //>0 Sun Calendar, <0 Moon Calendar
	long		nMonth;
	long		nDay;
	long		nDayDiff;
	long		nWeekNo;
	long		nWeekDay;
	long		nTerm;
	bool        bIgnorLeepMonth;
	bool		bShowYearCount;
	bool		bIsHoliday;
	long		nFestDays;
	bool		bFestAtWeekend;

	bool        RegSaveItem (TRegistry *);
	bool        RegReadItem (TRegistry *);
	bool		ShowItem (TListItem *);
	AnsiString	DateText ();
	int			IsFestival (const CDateTime &, const MoonDate &);
				//	Return 1:Festival(right day), 0:None, -1:Holidays
	~CFestItem () {};
};

class CFestList : public CBasicChain
{
protected:
	virtual CChainItem *NewChainItem ()
	{
		bDirty = true;
		return (CChainItem *)(new CFestItem);
	}

public:
	bool		bDirty;

	long	    AddItem (CFestItem *cpFestItem)
	{
		bDirty = true;
		return CBasicChain::AddItem ((CChainItem *)cpFestItem);
	}

	CFestItem	*GetItem (long nItemIndex)
	{
		return (CFestItem *)CBasicChain::GetItem (nItemIndex);
	}

	void	    DelItem (long nItemIndex)
	{
		bDirty = true;
		CBasicChain::DelItem (nItemIndex);
	}

	long	    LocateItem (CFestItem *cpFestItem)
	{
		return CBasicChain::LocateItem ((CChainItem *)cpFestItem);
	}

	bool    	RegSaveList (void);
	bool		RegReadList (void);
	bool		ShowList (TListView *);
	AnsiString	GetFestival (const CDateTime &cDateTime, const MoonDate &cMoonDate, bool bAllFestival, bool *bpIsFestival = NULL, bool *bpIsHoliday = NULL);
	bool		IsFestival (const CDateTime &cDateTime);
	bool		IsHoliday (const CDateTime &cDateTime);
};

#endif
