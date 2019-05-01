//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "..\common\datetime\LyxDateTimePicker.h"
#include <ToolWin.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TBevel *L9;
    TBevel *L10;
    TBevel *L11;
    TBevel *L12;
    TBevel *L13;
    TBevel *L14;
    TBevel *L2;
    TBevel *L3;
    TBevel *L6;
    TBevel *L5;
    TBevel *L4;
	TLabel *C1;
	TLabel *C2;
	TLabel *C3;
	TLabel *C4;
	TLabel *C5;
	TLabel *C6;
	TLabel *C7;
    TLabel *D01;
    TLabel *M01;
    TLabel *T01;
    TLabel *D02;
    TLabel *M02;
    TLabel *T02;
    TLabel *D03;
    TLabel *M03;
    TLabel *T03;
    TLabel *D04;
    TLabel *M04;
    TLabel *T04;
    TLabel *D05;
    TLabel *M05;
    TLabel *T05;
    TLabel *D06;
    TLabel *M06;
    TLabel *T06;
    TLabel *D07;
    TLabel *M07;
    TLabel *T07;
    TLabel *D8;
    TLabel *M8;
    TLabel *T8;
    TLabel *D9;
    TLabel *M9;
    TLabel *T9;
    TLabel *D10;
    TLabel *M10;
    TLabel *T10;
    TLabel *D11;
    TLabel *M11;
    TLabel *T11;
    TLabel *D12;
    TLabel *M12;
    TLabel *T12;
    TLabel *D13;
    TLabel *M13;
    TLabel *T13;
    TLabel *D14;
    TLabel *M14;
    TLabel *T14;
    TLabel *D15;
    TLabel *M15;
    TLabel *T15;
    TLabel *D16;
    TLabel *M16;
    TLabel *T16;
    TLabel *D17;
    TLabel *M17;
    TLabel *T17;
    TLabel *D18;
    TLabel *M18;
    TLabel *T18;
    TLabel *D19;
    TLabel *M19;
    TLabel *T19;
    TLabel *D20;
    TLabel *M20;
    TLabel *T20;
    TLabel *D21;
    TLabel *M21;
    TLabel *T21;
    TLabel *D22;
    TLabel *M22;
    TLabel *T22;
    TLabel *D23;
    TLabel *M23;
    TLabel *T23;
    TLabel *D24;
    TLabel *M24;
    TLabel *T24;
    TLabel *D25;
    TLabel *M25;
    TLabel *T25;
    TLabel *D26;
    TLabel *M26;
    TLabel *T26;
    TLabel *D27;
    TLabel *M27;
    TLabel *T27;
    TLabel *D28;
    TLabel *M28;
    TLabel *T28;
    TLabel *D29;
    TLabel *M29;
    TLabel *T29;
    TLabel *D30;
    TLabel *M30;
    TLabel *T30;
    TLabel *D31;
    TLabel *M31;
    TLabel *T31;
    TLabel *D32;
    TLabel *M32;
    TLabel *T32;
    TLabel *D33;
    TLabel *M33;
    TLabel *T33;
    TLabel *D34;
    TLabel *M34;
    TLabel *T34;
    TLabel *D35;
    TLabel *M35;
    TLabel *T35;
    TLabel *D36;
    TLabel *M36;
    TLabel *T36;
    TLabel *D37;
    TLabel *M37;
    TLabel *T37;
    TLabel *D38;
    TLabel *M38;
    TLabel *T38;
    TLabel *D39;
    TLabel *M39;
    TLabel *T39;
    TLabel *D40;
    TLabel *M40;
    TLabel *T40;
    TLabel *D41;
    TLabel *M41;
    TLabel *T41;
    TLabel *D42;
    TLabel *M42;
    TLabel *T42;
    TLabel *B01;
    TLabel *B02;
    TLabel *B03;
    TLabel *B04;
    TLabel *B05;
    TLabel *B06;
    TLabel *B07;
    TLabel *B8;
    TLabel *B9;
    TLabel *B10;
    TLabel *B11;
    TLabel *B12;
    TLabel *B13;
    TLabel *B14;
    TLabel *B15;
    TLabel *B16;
    TLabel *B17;
    TLabel *B18;
    TLabel *B19;
    TLabel *B20;
    TLabel *B21;
    TLabel *B22;
    TLabel *B23;
    TLabel *B24;
    TLabel *B25;
    TLabel *B26;
    TLabel *B27;
    TLabel *B28;
    TLabel *B29;
    TLabel *B30;
    TLabel *B31;
    TLabel *B32;
    TLabel *B33;
    TLabel *B34;
    TLabel *B35;
    TLabel *B36;
    TLabel *B37;
    TLabel *B38;
    TLabel *B39;
    TLabel *B40;
    TLabel *B41;
    TLabel *B42;
    TBevel *L7;
    TBevel *L15;
    TStatusBar *stbStatus;
    TMainMenu *mnuMain;
    TMenuItem *mnuCalendar;
    TMenuItem *mniAbout;
    TMenuItem *mniExit;
    TMenuItem *mnuFestival;
    TMenuItem *mniShowFestival;
    TMenuItem *mniEditFestival;
    TMenuItem *mniToday;
    TMenuItem *N1;
	TMenuItem *mniFestShow;
	TMenuItem *mniSetDate;
	TMenuItem *N2;
	TMenuItem *mniSetTime;
	TMenuItem *mnuHelp;
	TMenuItem *mniLyxSoftWeb;
	TMenuItem *N4;
	TCoolBar *clbMain;
	TToolBar *tblMain;
	TLyxDateTimePicker *dtpDateTime;
	TToolButton *btnSep1;
	TToolButton *btnToday;
	TToolButton *btnEditFestival;
	TToolButton *btnShowFest;
	TImageList *iglMain;
	TImageList *imgMainDark;
	TBevel *L1;
	TLabel *W1;
	TLabel *W2;
	TLabel *W3;
	TLabel *W4;
	TLabel *W5;
	TLabel *W6;
	TLabel *C0;
	TMenuItem *mnuFirstDayOptions;
	TMenuItem *N3;
	TMenuItem *mnuFirstDayOption1;
	TMenuItem *mnuFirstDayOption2;
	TMenuItem *mnuFirstDayOption3;
        TMenuItem *N5;
    void __fastcall B01Click(TObject *Sender);
    void __fastcall dtpDateTimeChange(TObject *Sender);
    
    
    void __fastcall mniAboutClick(TObject *Sender);
    void __fastcall mniExitClick(TObject *Sender);
    
    void __fastcall mniTodayClick(TObject *Sender);
    void __fastcall mniShowFestivalClick(TObject *Sender);
    void __fastcall mniEditFestivalClick(TObject *Sender);
	void __fastcall mniFestShowClick(TObject *Sender);
	
	void __fastcall mniSetDateClick(TObject *Sender);
	void __fastcall mniSetTimeClick(TObject *Sender);
	void __fastcall mniLyxSoftWebClick(TObject *Sender);
	void __fastcall mnuFirstDayOptionClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
