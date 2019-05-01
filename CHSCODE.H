//---------------------------------------------------------------------------
#ifndef ChsCodeH
#define ChsCodeH
//---------------------------------------------------------------------------
enum	CodeIndex
{
	NumCode = 1,
	SkyCode,
	EarthCode,
	WeekDay,
	MoonMonth,
	MoonMonthShort,
	MoonDay,
	MoonDayShort,
	BirthCode,
	TermCode
};

AnsiString	ChineseCode (long, CodeIndex);
#endif
 