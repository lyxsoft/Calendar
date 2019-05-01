//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Festival.h"
#include "Externs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFestival 		*frmFestival;

//---------------------------------------------------------------------------
__fastcall TfrmFestival::TfrmFestival(TComponent* Owner)
	: TForm(Owner)
{
	CurDate = CDateTime::Now();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::pgcFestivalChange(TObject *Sender)
{
	int     PageNo;
	int     ControlCount;

	for (PageNo = 0; PageNo < pgcFestival->PageCount; PageNo ++)
	{
		if (PageNo != pgcFestival->ActivePage->PageIndex)
		{
            for (ControlCount = 0; ControlCount < pgcFestival->Pages[PageNo]->ControlCount; )
            {
                if (pgcFestival->Pages[PageNo]->Controls[ControlCount]->Tag != 0)
                {
                    pgcFestival->Pages[PageNo]->Controls[ControlCount]->Parent = pgcFestival->ActivePage;
                    ControlCount = 0;
                }
                else
					ControlCount ++;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::btnNewClick(TObject *Sender)
{
	MoonDate    CurMoonDate;

	txtName->Text = "";
	txtShortName->Text = "";
	memRemarks->Text = "";

	pgcFestival->ActivePage = pgcFestival->Pages[0];
	pgcFestivalChange (NULL);
	cmbYearFunc->ItemIndex = 0;
	cmbYearFuncChange (NULL);

	pgcDateFunc->ActivePage = pgcDateFunc->Pages[0];
	pgcDateFuncChange (NULL);

	cmbMonth1->ItemIndex = CurDate.Month () - 1;
	udDay1->Position = (short)CurDate.Day ();
	cmbMonth2->ItemIndex = cmbMonth1->ItemIndex;
	cmbMonth2Change (NULL);
	udWeekNo->Position = (short)(CurDate.Day() / 7 + 1);
	cmbWeekDay->ItemIndex = CurDate.DayOfWeek() - 1;

	CurMoonDate = CaleMoonDate (CurDate);
	cmbMoonMonth->ItemIndex = CurMoonDate.MoonMonth - 1;
	cmbMoonDay->ItemIndex = CurMoonDate.MoonDay - 1;
	udDayDiff1->Position = 0;
	udDayDiff2->Position = 0;
	chkIgnorDoubleMoon->Checked = true;
	chkShowYearCount->Checked = false;

	chkIsHoliday->Checked = false;
	chkIsHolidayClick (NULL);
	lstFestival->Selected = NULL;
	udFestDays->Position = 1;
	chkFestAtWeekend->Checked = true;

	txtName->SetFocus ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::cmbYearFuncChange(TObject *Sender)
{
	if (cmbYearFunc->ItemIndex == 0)
	{
		txtYearFrom->Visible = false;
		udYearFrom->Visible = false;
		lblYearFrom->Visible = false;
		cmbYearFunc2->Visible = false;
		chkShowYearCount->Visible = false;
	}
	else
	{
		txtYearFrom->Visible = true;
		udYearFrom->Visible = true;
		lblYearFrom->Visible = true;
		cmbYearFunc2->Visible = true;
		udYearFrom->Position = (short)CurDate.Year ();
		chkShowYearCount->Visible = true;
	}
	cmbYearFunc2->ItemIndex = 0;
	cmbYearFunc2Change (NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::cmbYearFunc2Change(TObject *Sender)
{
	if (cmbYearFunc2->ItemIndex == 0)
	{
		txtYearTo->Visible = false;
		udYearTo->Visible = false;
		lblYearTo->Visible = false;
	}
	else
	{
		txtYearTo->Visible = true;
		udYearTo->Visible = true;
		lblYearTo->Visible = true;
		udYearTo->Position = udYearFrom->Position;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::FormShow(TObject *Sender)
{
	cFestList.ShowList (lstFestival);
	btnNewClick (NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestival::btnSaveClick(TObject *Sender)
{
	CFestItem	*cpFestItem;

	if (lstFestival->Selected != NULL)
		cpFestItem = cFestList.GetItem ((long)lstFestival->Selected->Data);
	else
	{
		lstFestival->Selected = lstFestival->Items->Add ();
		if (lstFestival->Selected == NULL)
			return;

		cpFestItem = new (CFestItem);
		lstFestival->Selected->Data = (void *)cFestList.AddItem (cpFestItem);
	}

	if (cpFestItem != NULL)
	{
		cpFestItem->strName = txtName->Text;
		cpFestItem->strShortName = txtShortName->Text;
		cpFestItem->strRemarks = memRemarks->Text;
		cpFestItem->nYearFrom = (cmbYearFunc->ItemIndex == 0 ? -1 : 1) * udYearFrom->Position;
		cpFestItem->nYearTo = (cmbYearFunc2->ItemIndex == 0 ? -1 : 1) * udYearTo->Position;
		if (pgcFestival->ActivePage->PageIndex == 0)
		{
			if (pgcDateFunc->ActivePage->PageIndex == 0)
			{
				cpFestItem->nFestMode =  1;
				cpFestItem->nMonth = cmbMonth1->ItemIndex + 1;
			}
			else if (pgcDateFunc->ActivePage->PageIndex == 1)
			{
				cpFestItem->nFestMode =  2;
				cpFestItem->nMonth = cmbMonth2->ItemIndex + 1;
			}
			else
			{
				cpFestItem->nFestMode =  3;
				cpFestItem->nMonth = cmbMonth1->ItemIndex + 1;
			}
			cpFestItem->nDay = udDay1->Position;
			cpFestItem->nDayDiff = udDayDiff1->Position;
		}
		else
		{
			cpFestItem->nFestMode =  -1;
			cpFestItem->nMonth = cmbMoonMonth->ItemIndex + 1;
			cpFestItem->nDay = cmbMoonDay->ItemIndex + 1;
			cpFestItem->nDayDiff = udDayDiff2->Position;
		}
		cpFestItem->nWeekNo = udWeekNo->Position;
		cpFestItem->nWeekDay = cmbWeekDay->ItemIndex + 1;
		cpFestItem->nTerm = (cmbTerm->ItemIndex + 2) % 24;
		cpFestItem->bIgnorLeepMonth = chkIgnorDoubleMoon->Checked;
		cpFestItem->bShowYearCount = chkShowYearCount->Checked;
		cpFestItem->bIsHoliday = chkIsHoliday->Checked;
		cpFestItem->nFestDays = udFestDays->Position;
		cpFestItem->bFestAtWeekend = chkFestAtWeekend->Checked;

		cpFestItem->ShowItem (lstFestival->Selected);
		stbMain->SimpleText = cpFestItem->DateText ();
		cFestList.bDirty = true;
	}
	lstFestival->Selected->MakeVisible (false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::btnSaveAddClick(TObject *Sender)
{
	lstFestival->Selected = NULL;
	btnSaveClick (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::btnDeleteClick(TObject *Sender)
{
	if (lstFestival->Selected != NULL && Application->MessageBox ("确认要删除此项节日吗?","删除", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		cFestList.DelItem ((long)lstFestival->Selected->Data);
		cFestList.ShowList (lstFestival);
		btnNewClick (NULL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::lstFestivalClick(TObject *Sender)
{
	CFestItem	*cpFestItem;

	if (lstFestival->Selected != NULL)
	{
		cpFestItem = cFestList.GetItem ((long)lstFestival->Selected->Data);
		if (cpFestItem == NULL)
			return;

		txtName->Text = cpFestItem->strName;
		txtShortName->Text = cpFestItem->strShortName;
		memRemarks->Text = cpFestItem->strRemarks;
		cmbYearFunc->ItemIndex = cpFestItem->nYearFrom > 0 ? 1 : 0;
		cmbYearFunc2->ItemIndex = cpFestItem->nYearTo > 0 ? 1 : 0;
		cmbYearFuncChange (NULL);
		udYearFrom->Position = (short)(cpFestItem->nYearFrom > 0 ? cpFestItem->nYearFrom : -cpFestItem->nYearFrom);
		udYearTo->Position = (short)(cpFestItem->nYearTo > 0 ? cpFestItem->nYearTo : -cpFestItem->nYearTo);
		switch (cpFestItem->nFestMode)
		{
		case	1:
		case	2:
		case	3:
			pgcFestival->ActivePage = pgcFestival->Pages [0];
			pgcDateFunc->ActivePage = pgcDateFunc->Pages [cpFestItem->nFestMode - 1];
			cmbMonth1->ItemIndex = cpFestItem->nMonth - 1;
			cmbMonth2->ItemIndex = cpFestItem->nMonth - 1;
			udDay1->Position = (short)(cpFestItem->nDay);
			break;
		case	-1:
			pgcFestival->ActivePage = pgcFestival->Pages [1];
			pgcDateFunc->ActivePage = pgcDateFunc->Pages [0];
			cmbMoonMonth->ItemIndex = cpFestItem->nMonth - 1;
			cmbMoonDay->ItemIndex = cpFestItem->nDay - 1;
			break;
		}
		cmbMonth2Change (NULL);
		pgcFestivalChange (NULL);
		pgcDateFuncChange (NULL);
		udWeekNo->Position = (short)(cpFestItem->nWeekNo);
		cmbWeekDay->ItemIndex = cpFestItem->nWeekDay - 1;
		udDayDiff1->Position = (short)(cpFestItem->nDayDiff);
		udDayDiff2->Position = (short)(cpFestItem->nDayDiff);
		cmbTerm->ItemIndex = (cpFestItem->nTerm + 22) % 24;
		chkIgnorDoubleMoon->Checked = cpFestItem->bIgnorLeepMonth;
		chkShowYearCount->Checked = cpFestItem->bShowYearCount;
		chkIsHoliday->Checked = cpFestItem->bIsHoliday;
		chkIsHolidayClick (NULL);
		udFestDays->Position = (short)(cpFestItem->nFestDays);
		chkFestAtWeekend->Checked = cpFestItem->bFestAtWeekend;

		stbMain->SimpleText = cpFestItem->DateText ();
	}
	txtName->SetFocus ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFestival::cmbMonth2Change(TObject *Sender)
{
	udWeekNo->Max = (short)(cmbMonth2->ItemIndex == 12 ? 53 : 4);
	if (udWeekNo->Position > udWeekNo->Max)
		udWeekNo->Position = udWeekNo->Max;
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestival::chkIsHolidayClick(TObject *Sender)
{
	txtFestDays->Enabled = chkIsHoliday->Checked;
	udFestDays->Enabled = chkIsHoliday->Checked;
	chkFestAtWeekend->Enabled = chkIsHoliday->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmFestival::pgcDateFuncChange(TObject *Sender)
{
	if (pgcDateFunc->ActivePage->PageIndex != 1)
	{
		txtDayDiff1->Parent = pgcDateFunc->ActivePage;
		udDayDiff1->Parent = pgcDateFunc->ActivePage;
		lblDayDiff1->Parent = pgcDateFunc->ActivePage;
	}
}
//---------------------------------------------------------------------------

