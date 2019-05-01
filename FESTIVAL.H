//---------------------------------------------------------------------------
#ifndef FestivalH
#define FestivalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include "LyxDateTime.h"
#include <ImgList.hpp>

class TfrmFestival : public TForm
{
__published:	// IDE-managed Components
	TListView *lstFestival;
    TCoolBar *cbMain;
	TToolBar *tblMain;
    TToolButton *btnNew;
    TImageList *iglMain;
    TToolButton *btnSave;
    TToolButton *ToolButton3;
    TToolButton *btnDelete;
    TImageList *iglList;
    TLabel *Label3;
    TEdit *txtName;
    TLabel *Label10;
    TPageControl *pgcFestival;
    TTabSheet *tabSun;
    TLabel *lblYearFrom;
    TLabel *lblYearTo;
    TPageControl *pgcDateFunc;
	TTabSheet *tabDate;
    TLabel *lblDay1;
    TComboBox *cmbMonth1;
    TEdit *cmbDay1;
    TUpDown *udDay1;
	TTabSheet *tabWeekday;
    TLabel *Label5;
    TLabel *Label6;
    TComboBox *cmbMonth2;
    TComboBox *cmbWeekDay;
    TEdit *cmbWeekNo;
    TUpDown *udWeekNo;
    TComboBox *cmbYearFunc;
    TEdit *txtYearFrom;
    TUpDown *udYearFrom;
    TComboBox *cmbYearFunc2;
    TEdit *txtYearTo;
    TUpDown *udYearTo;
    TTabSheet *tabMoon;
    TLabel *Label1;
    TLabel *Label2;
    TComboBox *cmbMoonMonth;
    TCheckBox *chkIgnorDoubleMoon;
    TComboBox *cmbMoonDay;
    TEdit *txtDayDiff2;
    TUpDown *udDayDiff2;
    TMemo *memRemarks;
	TStatusBar *stbMain;
    TLabel *Label4;
    TEdit *txtDayDiff1;
    TUpDown *udDayDiff1;
	TLabel *lblDayDiff1;
	TLabel *Label8;
	TEdit *txtShortName;
	TCheckBox *chkShowYearCount;
	TToolButton *btnSaveAdd;
	TCheckBox *chkIsHoliday;
	TEdit *txtFestDays;
	TUpDown *udFestDays;
	TLabel *Label9;
	TCheckBox *chkFestAtWeekend;
	TTabSheet *tabTerm;
	TComboBox *cmbTerm;
	TLabel *Label11;
    void __fastcall pgcFestivalChange(TObject *Sender);
    
    
    void __fastcall btnNewClick(TObject *Sender);
    void __fastcall cmbYearFuncChange(TObject *Sender);
    void __fastcall cmbYearFunc2Change(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
	
	void __fastcall btnSaveClick(TObject *Sender);
	
	void __fastcall lstFestivalClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
	
	
	void __fastcall btnSaveAddClick(TObject *Sender);
	void __fastcall cmbMonth2Change(TObject *Sender);
	void __fastcall chkIsHolidayClick(TObject *Sender);
	void __fastcall pgcDateFuncChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    CDateTime   CurDate;
    __fastcall TfrmFestival(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFestival *frmFestival;
//---------------------------------------------------------------------------
#endif
