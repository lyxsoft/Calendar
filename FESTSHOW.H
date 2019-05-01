//---------------------------------------------------------------------------
#ifndef FestShowH
#define FestShowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "LyxDateTime.h"

//---------------------------------------------------------------------------
class TfrmFestShow : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *btnClose;
	TShape *Shape1;
	TImage *Image1;
	TShape *Shape2;
	TLabel *lblDate;
	TCheckBox *chkShowFest;
	TLabel *lblWeekDay;
	TLabel *lblMoonDate;
	TLabel *lblFestival;
	TLabel *lblFestTitle;
	TSpeedButton *btnCalendar;
	TImage *imgLyxSoft;
	void __fastcall btnCloseClick(TObject *Sender);


	void __fastcall FormShow(TObject *Sender);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCalendarClick(TObject *Sender);
	void __fastcall imgLyxSoftClick(TObject *Sender);
private:	// User declarations
	void __fastcall virtual HitTest(TMessage &);
	BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_NCHITTEST, TMessage, HitTest)
	END_MESSAGE_MAP(TForm)

public:		// User declarations
	CDateTime   CurDate;
	__fastcall TfrmFestShow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFestShow *frmFestShow;
//---------------------------------------------------------------------------
#endif
