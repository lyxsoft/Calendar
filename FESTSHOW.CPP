//---------------------------------------------------------------------------
#include <vcl.h>
#include <Shellapi.h>
#pragma hdrstop

#include "FestShow.h"
#include "Externs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFestShow *frmFestShow;

//---------------------------------------------------------------------------
__fastcall TfrmFestShow::TfrmFestShow(TComponent* Owner)
	: TForm(Owner)
{
	CurDate = CDateTime::Now();
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestShow::btnCloseClick(TObject *Sender)
{
	Close ();	
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestShow::FormShow(TObject *Sender)
{
	MoonDate	cMoonDate;

	chkShowFest->Checked = !bShowFest;
	btnCalendar->Visible =  bFestShowing;
	
	cMoonDate = CaleMoonDate (CurDate);
	lblDate->Caption = (CurDate.Month () < 10 ? AnsiString(" ") : AnsiString ("")) + AnsiString (CurDate.Month ()) + "月" + (CurDate.Day () < 10 ? AnsiString(" ") : AnsiString ("")) + AnsiString (CurDate.Day ()) + "日";
	lblWeekDay->Caption = ChineseCode (CurDate.DayOfWeek (), WeekDay) + " " + ChineseCode(CaleSunTerm(CurDate), TermCode);;
	lblMoonDate->Caption = AnsiString("农历") + FormatMoonDate (cMoonDate, true, true, true, false, false);
	lblFestival->Caption = cFestList.GetFestival (CurDate, cMoonDate, true);
	lblFestTitle->Visible = !lblFestival->Caption.IsEmpty ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestShow::FormClose(TObject *Sender,
	  TCloseAction &Action)
{
	bShowFest = !chkShowFest->Checked;
	if (bFestShowing)
		frmMain->Close ();
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestShow::btnCalendarClick(TObject *Sender)
{
	bFestShowing = false;
	Close ();
	frmMain->Show ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestShow::imgLyxSoftClick(TObject *Sender)
{
	ShellExecute (NULL, NULL, strHomepage, NULL, NULL, SW_MAXIMIZE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestShow::HitTest(TMessage &Message)
{
	POINT	cMousePos;

	cMousePos.x = Message.LParamLo;
	cMousePos.y = Message.LParamHi;
	cMousePos = ScreenToClient (cMousePos);

	if (PtInRect (&((RECT)btnClose->BoundsRect), cMousePos) || \
	   (btnCalendar->Visible && PtInRect (&((RECT)btnCalendar->BoundsRect), cMousePos)) || \
	   (imgLyxSoft->Visible && PtInRect (&((RECT)imgLyxSoft->BoundsRect), cMousePos)))
		Message.Result = HTCLIENT;
	else
		Message.Result = HTCAPTION;
}
//---------------------------------------------------------------------------

