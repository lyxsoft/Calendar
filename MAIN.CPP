//---------------------------------------------------------------------------
#include <vcl.h>
#include <Shellapi.h>
#pragma hdrstop

#include "Main.h"
#include "Externs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LyxDateTimePicker"
#pragma resource "*.dfm"
TfrmMain *frmMain;

long    		CurYear, CurMonth, CurDay;
EFirstDayOfYear	eCurFirstDayOfYear = FirstJan1;
TLabel			*ControlID[4][42];
TLabel			*WeekNoID[6];

//---------------------------------------------------------------------------
extern CFestList	cFestList;

//---------------------------------------------------------------------------
void    FocusAt (long FocusID)
{
	static TLabel *LastFocus = NULL;

	if (FocusID >= 0 && FocusID < 42)
	{
		if (LastFocus != NULL)
			LastFocus->Transparent = true;

		LastFocus = ControlID[0][FocusID];
		LastFocus->Transparent = false;
	}
}
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner)
{
	int         ControlIndex;

	for (ControlIndex = ControlCount - 1; ControlIndex >=0; ControlIndex--)
	{
		switch (Controls[ControlIndex]->Name[1])
		{
		case    'B':
			Controls[ControlIndex]->Tag = Controls[ControlIndex]->Name.SubString(2,2).ToInt();
			ControlID[0][Controls[ControlIndex]->Tag - 1] = (TLabel *)Controls[ControlIndex];
			break;
		case    'T':
			Controls[ControlIndex]->Tag = Controls[ControlIndex]->Name.SubString(2,2).ToInt();
			ControlID[1][Controls[ControlIndex]->Tag - 1] = (TLabel *)Controls[ControlIndex];
			break;
		case    'M':
			Controls[ControlIndex]->Tag = Controls[ControlIndex]->Name.SubString(2,2).ToInt();
			ControlID[2][Controls[ControlIndex]->Tag - 1] = (TLabel *)Controls[ControlIndex];
			break;
		case    'D':
			Controls[ControlIndex]->Tag = Controls[ControlIndex]->Name.SubString(2,2).ToInt();
			ControlID[3][Controls[ControlIndex]->Tag - 1] = (TLabel *)Controls[ControlIndex];
			break;
		case	'W':
			WeekNoID[Controls[ControlIndex]->Name.SubString(2,1).ToInt() - 1] = (TLabel *)Controls[ControlIndex];
			break;
		}
	}
	switch (eFirstDayOfYear)
	{
	case	FirstFourDays:
		mnuFirstDayOption2->Checked = true;
		break;
	case	FirstFullWeek:
		mnuFirstDayOption3->Checked = true;
		break;
	default:
		mnuFirstDayOption1->Checked = true;
		break;
	}
	mniShowFestival->Checked = !bDisplayFest;
	dtpDateTimeChange (NULL);
	mniShowFestivalClick (NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::B01Click(TObject *Sender)
{
	CDateTime       CurDate;
	long            nHour, nMin, nSec, nMSec;

	dtpDateTime->GetDateTime().DecodeTime (&nHour, &nMin, &nSec, &nMSec);
	CurDate = CDateTime (CurYear, CurMonth, 1);
	CurDate += ((TControl *)Sender)->Tag - CurDate.DayOfWeek ();
	CurDate += CDateTime (nHour, nMin, nSec, nMSec);

    dtpDateTime->SetDateTime (CurDate);
    dtpDateTimeChange (NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dtpDateTimeChange(TObject *Sender)
{
	CDateTime       EachDate;
	CDateTime       FirstDate;
	long            EachItem;
	long            EachYear, EachMonth, EachDay;
	MoonDate        MD;
	bool            bIsFestival, bIsHoliday;

	EachDate = dtpDateTime->GetDateTime ();
	EachDate.DecodeDate (&EachYear, &EachMonth, &EachDay);
	stbStatus->Panels->Items[0]->Text = "Å©Àú:" + FormatMoonDate (CaleMoonDate(EachDate), true, true, true, true, false);
	stbStatus->Panels->Items[1]->Text = "°Ë×Ö:" + CaleEightDate (EachDate);
	if (EachYear == CurYear && EachMonth == CurMonth)
	{
		if (EachDay != CurDay)
		{
			CurDay = EachDay;
			FirstDate = CDateTime (CurYear, CurMonth, 1);
			FocusAt (CurDay + FirstDate.DayOfWeek() - 2);
		}
		if (eCurFirstDayOfYear == eFirstDayOfYear ||
			EachDate.WeekOfYear(eCurFirstDayOfYear) == EachDate.WeekOfYear(eFirstDayOfYear))
			return;
	}

	CurYear = EachYear;
	CurMonth = EachMonth;
	CurDay = EachDay;
	eCurFirstDayOfYear = eFirstDayOfYear;

	FirstDate = CDateTime (CurYear, CurMonth, 1);
	FocusAt (CurDay + FirstDate.DayOfWeek() - 2);
	EachDay = FirstDate.WeekOfYear (eFirstDayOfYear);
	for (EachItem = 0; EachItem < 6; EachItem ++)
		WeekNoID[EachItem]->Caption = AnsiString(EachDay + EachItem);
	for (EachItem = 0; EachItem < 42; EachItem ++)
	{
		EachDate = FirstDate + (long)(EachItem + 1 - FirstDate.DayOfWeek());

		ControlID[3][EachItem]->Caption = AnsiString(EachDate.Day ());
		MD = CaleMoonDate (EachDate);
		if (MD.MoonDay == 1)
			ControlID[2][EachItem]->Caption = FormatMoonDate(MD, false, true, false, false, true);
		else
			ControlID[2][EachItem]->Caption = FormatMoonDate(MD, false, false, true, false, true);

		ControlID[1][EachItem]->Caption = cFestList.GetFestival (EachDate, MD, false, &bIsFestival, &bIsHoliday);
		if (!bIsFestival)
		{
			ControlID[1][EachItem]->Caption = ChineseCode(CaleSunTerm(EachDate), TermCode);
			ControlID[1][EachItem]->Hint = "";
		}
		else
			ControlID[1][EachItem]->Hint = cFestList.GetFestival (EachDate, MD, true);

		if (EachDate.Month () != CurMonth)
			ControlID[1][EachItem]->Font->Color = clDkGray;
		else
			ControlID[1][EachItem]->Font->Color = (bIsHoliday || EachDate.DayOfWeek() == 1 || EachDate.DayOfWeek() == 7) ? clRed : clWindowText;
		ControlID[2][EachItem]->Font->Color = ControlID[1][EachItem]->Font->Color;
		ControlID[3][EachItem]->Font->Color = ControlID[1][EachItem]->Font->Color;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniAboutClick(TObject *Sender)
{
	frmAbout->ShowModal ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniExitClick(TObject *Sender)
{
    Close ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniTodayClick(TObject *Sender)
{
    dtpDateTime->SetDateTime (CDateTime::Now());
    dtpDateTimeChange (NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniShowFestivalClick(TObject *Sender)
{
    int             EachItem;

	mniShowFestival->Checked = !mniShowFestival->Checked;
	bDisplayFest = mniShowFestival->Checked;
    for (EachItem = 0; EachItem < 42; EachItem ++)
		ControlID[1][EachItem]->Visible = mniShowFestival->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniEditFestivalClick(TObject *Sender)
{
	frmFestival->CurDate = dtpDateTime->GetDateTime ();
	frmFestival->ShowModal ();

	CDateTime       FirstDate;
	CDateTime       EachDate;
	long            EachItem;
	MoonDate        MD;
	bool            bIsFestival, bIsHoliday;

	FirstDate = CDateTime (CurYear, CurMonth, 1);
	for (EachItem = 0; EachItem < 42; EachItem ++)
	{
		EachDate = FirstDate + (long)(EachItem + 1 - FirstDate.DayOfWeek());
		MD = CaleMoonDate (EachDate);
		ControlID[1][EachItem]->Caption = cFestList.GetFestival (EachDate, MD, false, &bIsFestival, &bIsHoliday);
		if (!bIsFestival)
		{
			ControlID[1][EachItem]->Caption = ChineseCode(CaleSunTerm(EachDate), TermCode);
			ControlID[1][EachItem]->Hint = "";
		}
		else
			ControlID[1][EachItem]->Hint = cFestList.GetFestival (EachDate, MD, true);

		if (ControlID[1][EachItem]->Font->Color != clDkGray)
			ControlID[1][EachItem]->Font->Color = (bIsHoliday || EachDate.DayOfWeek() == 1 || EachDate.DayOfWeek() == 7) ? clRed : clWindowText;
		ControlID[2][EachItem]->Font->Color = ControlID[1][EachItem]->Font->Color;
		ControlID[3][EachItem]->Font->Color = ControlID[1][EachItem]->Font->Color;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFestShowClick(TObject *Sender)
{
	frmFestShow->CurDate = dtpDateTime->GetDateTime ();
	frmFestShow->ShowModal ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniSetDateClick(TObject *Sender)
{
	dtpDateTime->GetDateTime ().SetDate ();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSetTimeClick(TObject *Sender)
{
	dtpDateTime->GetDateTime ().SetTime ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mniLyxSoftWebClick(TObject *Sender)
{
	ShellExecute (NULL, NULL, strHomepage, NULL, NULL, SW_MAXIMIZE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFirstDayOptionClick(TObject *Sender)
{

	if (Sender != NULL)
	{
		((TMenuItem *)Sender)->Checked = true;
		eFirstDayOfYear = ToEFirstDayOfYear (((TMenuItem *)Sender)->Tag);
	}
	dtpDateTimeChange (NULL);
	return;
}
//---------------------------------------------------------------------------

