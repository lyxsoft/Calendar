//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ChsCalendar.h"
#include "ChsCode.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const AnsiString YMDHCode = "年月日时闰";

typedef long double  DATA;

const DATA Pi = 3.14159265358979;
const DATA SunCycle = 365.242193287037;

const DATA SunTerm = SunCycle / 24;
const DATA SunStart = 5.26359025371382;
const DATA SunTermFixRate = 1.94352924864967;
const DATA SunTermFixPhase = 0.874999999413545;

const DATA MoonTerm = 29.53058796;
const DATA MoonStart = -2.89615554886404;

const DATA MoonFixTerm = 6.966;
const DATA MoonFixTermPhase = -0.539;

const DATA MoonFixRateTerm = 58.74924485;
const DATA MoonFixRateRate = 0.143;
const DATA MoonFixRateStart = 0.463888889;
const DATA MoonFixRatePhase = -0.2;

const DATA MoonFixPhaseTerm = 58.74924485;
const DATA MoonFixPhaseRate = -0.104;
const DATA MoonFixPhaseStart = -0.0675;
const DATA MoonFixPhasePhase = 0.3105;

const CDateTime StartDate = CDateTime (100, 1, 1);

typedef struct
{
    long        DateValue;
    int         AdjustValue;
}AdjustDate;

AdjustDate AdjustDates[4];

static long CountDate(const CDateTime &SunDate)
{
	return (long)SunDate - (long)StartDate;
}

static void InitAdjustDate()
{
	static bool AdjustDateInited = false;

	if (AdjustDateInited == False)
	{
		AdjustDates[0].DateValue = CountDate(CDateTime(1995, 7,28));
		AdjustDates[0].AdjustValue = -1;
		AdjustDates[1].DateValue = CountDate(CDateTime(1998, 2,26));
		AdjustDates[1].AdjustValue = 1;
		AdjustDates[2].DateValue = CountDate(CDateTime(2000,12,25));
		AdjustDates[2].AdjustValue = 1;
		AdjustDates[3].DateValue = CountDate(CDateTime(2004, 9,15));
		AdjustDates[3].AdjustValue = -1;
		AdjustDateInited = true;
	}
}

static int AdjustDateValue(long DateValue)
{
	int AdjustCount;

	for (AdjustCount = 0; AdjustCount < 4; AdjustCount++)
    {
        if (AdjustDates[AdjustCount].DateValue == DateValue)
            return AdjustDates[AdjustCount].AdjustValue;
    }
    return 0;
}

/*
*   Find the last sun-term before the giving date
CDateTime CaleLastTerm(CDateTime SunDate)
{
    long        DateValue;
    DATA        TermFix;
    DATA        TimeValue;
    CDateTime   DateResult;

    DateValue = CountDate(SunDate);
    TermFix = -sinl(Pi * ((DATA)((long)((DateValue - SunStart) / SunTerm) % 24) + 1.0 - SunTermFixPhase) / 12.0) * SunTermFixRate;
	TimeValue = (DATA)((long)((DateValue - SunStart) / SunTerm)) * SunTerm + SunStart + TermFix;
    TimeValue = modfl (TimeValue, NULL);
    DateResult = StartDate + ((long)((DateValue - SunStart) / SunTerm) * SunTerm + SunStart + TermFix);
    DateResult = DateResult + (double)TimeValue;
    return DateResult;
}
*/

/*
*   Find the sun term of the giving date
*   If it is the right date, return +
*   If not return -
*/
long    CaleSunTerm(const CDateTime &SunDate)
{
	long    DateValue;
	DATA    TermFix;

	DateValue = CountDate(SunDate) + 7;
	TermFix = -sinl(Pi * ((DATA)((long)((DateValue - SunStart) / SunTerm) % 24 + 1) - SunTermFixPhase) / (DATA)12) * SunTermFixRate;
	if ((long)((long)((DateValue - SunStart) / SunTerm) * SunTerm + SunStart + TermFix) == DateValue - 7)
		return (int)((DateValue - SunStart) / SunTerm) % 24 + 1;
	else
		return -((int)((DateValue - SunStart) / SunTerm) % 24 + 1);
}

/*
*   Get the eight-char date of the giving date
*/
AnsiString CaleEightDate(const CDateTime &cSunDate)
{
	CDateTime	SunDate;
	AnsiString  Result;
	long        DateValue;
	long        YearNum;
	long        DayNum;
	long        HourNum;
	long        Term;
	long        TermCount;
	long        TermDate;

	SunDate = cSunDate + (double)1.0 / 24;
	YearNum = SunDate.Year ();
	DateValue = CountDate(SunDate);

	Term = (long)(((DATA)CountDate(CDateTime(YearNum, 1, 1)) - SunStart) / SunTerm) + 3;
	TermDate = (long)((DATA)Term * SunTerm + SunStart - sinl(Pi * ((DATA)(Term % 24 + 1) - SunTermFixPhase) / (DATA)12) * SunTermFixRate);
	if (DateValue < TermDate)
		YearNum --;

	//Year
	YearNum = (unsigned short)((YearNum + 56) % 60);
	Result = ChineseCode(YearNum, SkyCode) + ChineseCode(YearNum, EarthCode) + YMDHCode.SubString(1, 2);

	//Month
	TermCount = (long)((DateValue - SunStart) / SunTerm);
    while ((long)(TermCount * SunTerm + SunStart - sinl(Pi * ((DATA)(TermCount % 24 + 1) - SunTermFixPhase) / (DATA)12) * SunTermFixRate) <= DateValue)
		TermCount = TermCount + 1;
    Term = (long)(((TermCount - 1) % 24) / 2);
    if (Term == 0)
        Term = 12;
    Result += ChineseCode((YearNum % 5) * 2 + Term + 1, SkyCode) + ChineseCode(Term + 1, EarthCode) + YMDHCode.SubString(3, 2);

    //Day
    DayNum = (DateValue + 54) % 60;
    Result += ChineseCode(DayNum, SkyCode) + ChineseCode(DayNum, EarthCode) + YMDHCode.SubString(5, 2);

    //Hour
    HourNum = SunDate.Hour() / 2;
    Result += ChineseCode((DayNum % 5) * 2 + HourNum, SkyCode) + ChineseCode(HourNum, EarthCode) + YMDHCode.SubString(7, 2);
    return Result;
}

/*
*   Get the moon date of the giving date
*/
MoonDate CaleMoonDate(const CDateTime &cSunDate)
{
	CDateTime	SunDate;
	long    DateValue;
	long    FirstDate;
	long    NextDate;
	long    MoonMonths;
	DATA    MoonFixPhase;
	DATA    MoonFixRate;
	DATA    TermDate;
	int     MidTerm;
	long    TermCount;
	MoonDate    Result;

	InitAdjustDate ();

	SunDate = cSunDate + (double)1.0 / 24;
    DateValue = CountDate(SunDate);
    MoonMonths = (long)(DateValue / MoonTerm) - 1;
    NextDate = 0;
    do
    {
        FirstDate = NextDate;
        MoonMonths = MoonMonths + 1;
		MoonFixPhase = sinl(Pi * ((DATA)MoonMonths / MoonFixPhaseTerm - MoonFixPhasePhase)) * MoonFixPhaseRate + MoonFixPhaseStart;
        MoonFixRate = sinl(Pi * ((DATA)MoonMonths / MoonFixRateTerm - MoonFixRatePhase)) * MoonFixRateRate + MoonFixRateStart;
        NextDate = (long)(MoonMonths * MoonTerm + sinl(Pi * ((DATA)MoonMonths / MoonFixTerm - MoonFixTermPhase - MoonFixPhase)) * MoonFixRate + MoonStart);
        NextDate = NextDate + AdjustDateValue(NextDate);
    }while (NextDate <= DateValue);

    MidTerm = 0;
    TermDate = FirstDate;
    TermCount = (long)((TermDate - SunStart) / SunTerm);
    while (TermDate < NextDate)
    {
        TermDate = TermCount * SunTerm + SunStart - sinl(Pi * ((DATA)(TermCount % 24 + 1) - SunTermFixPhase) / (DATA)12) * SunTermFixRate;
        if (TermDate >= FirstDate && TermDate < NextDate)
        {
			MidTerm = TermCount % 24 + 1;
            if (MidTerm % 2 == 1)
                MidTerm = 0;
            else
                break;
        }
        TermCount ++;
    }

	if (MidTerm <= 0)
    {
        //Is double-month
        TermCount = (long)((TermDate - SunStart) / SunTerm);
        while (MidTerm == 0)
        {
            TermDate = TermCount * SunTerm + SunStart - sinl(Pi * ((DATA)(TermCount % 24 + 1) - SunTermFixPhase) / (DATA)12) * SunTermFixRate;
            if (TermDate < FirstDate)
            {
                MidTerm = TermCount % 24 + 1;
                if (MidTerm % 2 == 1)
                    MidTerm = 0;
                else
                    break;
            }
            TermCount --;
        }
        Result.MoonDouble = true;
	}
	else
		Result.MoonDouble = false;

	MidTerm = (long)(MidTerm / 2) - 1;

	if (MidTerm == 0)
	{
		MidTerm = 12;
		Result.MoonYear = ((CDateTime)StartDate + (long)TermDate).Year () - 1;
	}
	else
		Result.MoonYear = ((CDateTime)StartDate + (long)TermDate).Year ();

	Result.MoonYear = (Result.MoonYear + 56) % 60;
	Result.MoonMonth = MidTerm;
	Result.MoonDay = (long)(DateValue) - (long)(FirstDate) + 1;
	Result.MoonHour = SunDate.Hour () / 2 + 1;
	Result.MoonLength = NextDate - FirstDate;
	return Result;
}

/*
*   Return the moon date name
*/
AnsiString FormatMoonDate(const MoonDate &MoonDateValue, bool WithYear, bool WithMonth, bool WithDay, bool WithHour, bool ShortString)
{
	AnsiString ResultString;

	if (WithYear)
		ResultString = ChineseCode(MoonDateValue.MoonYear, SkyCode) + \
					   ChineseCode(MoonDateValue.MoonYear, EarthCode) + \
					   YMDHCode.SubString(1, 2);

	if (WithMonth)
		ResultString += (MoonDateValue.MoonDouble ? YMDHCode.SubString(9, 2) : AnsiString("")) + \
						ChineseCode(MoonDateValue.MoonMonth, ShortString ? MoonMonthShort : MoonMonth) + \
						YMDHCode.SubString(3, 2);

	if (WithDay)
		ResultString += ChineseCode(MoonDateValue.MoonDay, ShortString ? MoonDayShort : MoonDay);

	if (WithHour)
		ResultString += ChineseCode(MoonDateValue.MoonHour - 1, EarthCode) + "时";

	return ResultString;
}
//---------------------------------------------------------------------------

