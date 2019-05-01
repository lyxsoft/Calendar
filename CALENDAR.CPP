//---------------------------------------------------------------------------
#include <vcl.h>
#include <values.h>
#pragma hdrstop

USERES("Calendar.res");
USEFORM("Main.cpp", frmMain);
USEUNIT("ChsCalendar.cpp");
USEFORM("Festival.cpp", frmFestival);
USEUNIT("..\COMMON\DateTime\LyxDateTime.cpp");
USEUNIT("FestItem.cpp");
USEUNIT("..\COMMON\Chain\Chain.cpp");
USEFORM("FestShow.cpp", frmFestShow);
USEUNIT("ChsCode.cpp");
USEFORM("..\COMMON\About\LyxAbout.cpp", frmAbout);
USERES("App.res");
//---------------------------------------------------------------------------
#include "Externs.h"

CFestList				cFestList;
bool					bDisplayFest;
bool					bShowFest;
bool					bFestShowing;
EFirstDayOfYear			eFirstDayOfYear = FirstJan1;
const AnsiString		strRegRoot("\\Software\\LyxSoft Software Inc.\\LyxSoft Calendar\\");
const char 				*strHomepage = "http://www.lyxsoft.f2s.com";

void	ReadOptions ()
{
	TRegistry	*cpRegistry = new (TRegistry);

	bShowFest = true;
	bDisplayFest = true;
	if (!cpRegistry->OpenKey (strRegRoot, false))
	{
		delete cpRegistry;
		return;
	}

	if (cpRegistry->ValueExists ("ShowFestival"))
		bShowFest = cpRegistry->ReadBool ("ShowFestival");
	if (cpRegistry->ValueExists ("DisplayFestival"))
		bDisplayFest = cpRegistry->ReadBool ("DisplayFestival");
	if (cpRegistry->ValueExists ("FirstDayOfYear"))
		eFirstDayOfYear = ToEFirstDayOfYear (cpRegistry->ReadInteger ("FirstDayOfYear"));
	delete	cpRegistry;
}

void	SaveOptions ()
{
	TRegistry	*cpRegistry = new (TRegistry);

	if (!cpRegistry->OpenKey (strRegRoot, true))
	{
		delete cpRegistry;
		return;
	}
	cpRegistry->WriteBool ("ShowFestival", bShowFest);
	cpRegistry->WriteBool ("DisplayFestival", bDisplayFest);
	cpRegistry->WriteInteger ("FirstDayOfYear", eFirstDayOfYear);

	delete	cpRegistry;
}

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR , int)
{
	try
	{
		TSysCharSet	SwitchChars;

		Application->Initialize();
		Application->Title = "LyxSoft Calendar";
		ReadOptions ();
		cFestList.RegReadList ();

		SwitchChars.Clear ();
		SwitchChars << '-' << '/';
		if (FindCmdLineSwitch ("auto", SwitchChars, true))
		{
			if (!bShowFest || !cFestList.IsFestival (CDateTime::Now()))
				return 0;
			bFestShowing = true;
		}
		else
			bFestShowing = false;


		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmFestival), &frmFestival);
		Application->CreateForm(__classid(TfrmFestShow), &frmFestShow);
		Application->CreateForm(__classid(TfrmAbout), &frmAbout);
		if (bFestShowing)
		{
			Application->ShowMainForm = false;
			frmFestShow->Show ();
		}
		Application->HintPause = 0;
		Application->HintShortPause = 0;
		Application->HintHidePause = MAXINT;
		Application->Run();
		cFestList.RegSaveList ();
		SaveOptions ();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------




