//---------------------------------------------------------------------------
#ifndef ChsCalendarH
#define ChsCalendarH
//---------------------------------------------------------------------------
#include "LyxDateTime.h"

typedef struct
{
    long		MoonYear;
	long		MoonMonth;
	long		MoonDay;
	long		MoonHour;
	long		MoonLength;
    bool        MoonDouble;
} MoonDate;

/*
*   DateTime Extern Function
*/

long        CaleSunTerm(const CDateTime &SunDate);
AnsiString  CaleEightDate(const CDateTime &SunDate);
AnsiString  FormatTerm(long TermNo);
MoonDate    CaleMoonDate(const CDateTime &SunDate);
AnsiString  FormatMoonDate(const MoonDate &MoonDateValue, bool WithYear, bool WithMonth, bool WithDay, bool WithHour, bool ShortString);

#endif
