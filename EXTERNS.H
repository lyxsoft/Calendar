//---------------------------------------------------------------------------
#ifndef ExternsH
#define ExternsH

/*
 *	Common Interfaces
*/
#include <Registry.hpp>
#include "LyxDateTime.h"
#include "FestItem.h"
#include "ChsCalendar.h"
#include "ChsCode.h"

/*
 *	Extern Datas
*/
#include "Main.h"
#include "LyxAbout.h"
#include "Festival.h"
#include "FestShow.h"

extern CFestList		cFestList;
extern bool				bShowFest;
extern bool				bDisplayFest;
extern bool				bFestShowing;
extern EFirstDayOfYear	eFirstDayOfYear;

extern const AnsiString	strRegRoot;
extern const char 		*strHomepage;

//---------------------------------------------------------------------------
#endif
