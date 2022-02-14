// SampGridWnd.cpp: implementation of the CSampGridWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DA.h"
#include "SampGridWnd.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CSampGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CSampGridWnd

CSampGridWnd::CSampGridWnd() : m_initialized(false)
{
}

CSampGridWnd::~CSampGridWnd()
{
}


BEGIN_MESSAGE_MAP(CSampGridWnd, CGXGridWnd)
	//{{AFX_MSG_MAP(CSampGridWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSampGridWnd message handlers

void CSampGridWnd::OnInitialUpdate()
{
	CGXGridWnd::OnInitialUpdate();

	GetParam()->EnableUndo(FALSE);

	SetRowCount(1);
	SetColCount(1);

	SetStyleRange(CGXRange(0, 1), CGXStyle().SetValue("Sample Name"));
	SetStyleRange(CGXRange(0, 0), CGXStyle().SetReadOnly(TRUE).SetControl(GX_IDS_CTRL_STATIC));
	//ResizeColWidthsToFit(CGXRange(0,1));
	CRect rect;
	GetClientRect(rect);
	SetColWidth(1, 1, rect.Width() - GetColWidth(0) - 25);
	//SetCanAppend(TRUE);

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT)
		.SetReadOnly(FALSE)
		.SetAutoSize(TRUE));

	GetParam()->SetActivateCellFlags(GX_CAFOCUS_SETCURRENT);

	//GetParam()->EnableUndo(TRUE);
}

BOOL CSampGridWnd::ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	if (nMessage == WM_KEYDOWN)
	{
		switch (nChar)
		{
		case VK_TAB:		// Tab-Key
		case VK_RETURN:		// Enter-Key
			{
				ROWCOL nRow = 1, nCol = 1;
				GetCurrentCell(nRow, nCol);
				if (!bShift)

					{
					// Jump to the right cell or move down a row, 
					// if cell positioned at last cell
					if (nCol < GetColCount( ))
						MoveCurrentCell(GX_RIGHT);
					else if (nRow < GetRowCount( ))
					{
						MoveCurrentCell(GX_MOSTLEFT);
						MoveCurrentCell(GX_DOWN);
					}
					else
					{
						// Add a new row
						SetRowCount(GetRowCount( )+1);
						MoveCurrentCell(GX_MOSTLEFT);
						MoveCurrentCell(GX_DOWN);
					}
				}
				else
				{
					// Jump to the left cell or move up a row

					if (nCol > 1)
						MoveCurrentCell(GX_LEFT);
					else if (nRow > 1)
					{
						MoveCurrentCell(GX_MOSTRIGHT);
						MoveCurrentCell(GX_UP);
					}
					else
					{
						MoveCurrentCell(GX_BOTTOMRIGHT);
					}
				}
				return TRUE;
			}
		}
	}
	return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
}


void CSampGridWnd::SetGridValues(CDAPPS& pps)
{
	UINT i;
		
	ChangeStandardStyle(CGXStyle().SetMaxLength(pps.SAMPLENAME_SIZE - 1));

	SetRowCount(pps.m_numsamples);


	// Only set the list entries into the grid.
	for (i=1; i<=pps.m_numsamples; i++)
	{
		SetValueRange(CGXRange(i, 1), pps.m_samplelist[i-1]);
	}


}

void CSampGridWnd::GetGridValues(CDAPPS& pps)
{
	ROWCOL i;
	ROWCOL size = GetRowCount();	
	
	if(size > 0)
	{
		CString cell_txt;
		pps.SetNumSamps(size);
		for (i = 1; i <= size; i++)
		{
			cell_txt = GetValueRowCol(i, 1);
			pps.AddSample(LPCTSTR(cell_txt), i);
		}
	}
}


void CSampGridWnd::ClearSelRows()
{
	CRowColArray from_list, to_list;

	if (GetSelectedRows(from_list, to_list, FALSE, TRUE)) 
	{
		CGXRange a_range;

		for (ROWCOL n =0; n < (ROWCOL)from_list.GetSize(); n++)
		{	
			if (from_list[n] == 0)
				from_list[n] = 1;
			if (to_list[n] == 0)
				to_list[n] = 1;
			a_range.SetCells(from_list[n], 1, to_list[n], 1);
			SetValueRange(a_range, "");
		}
	}

}


void CSampGridWnd::DeleteSelRows()
{
	CRowColArray from_list, to_list;

	if (GetSelectedRows(from_list, to_list, FALSE, FALSE)) 
	{
		if (SCMessageBox("Are you sure you want to delete the selected sample names?", 
						MB_ICONQUESTION|MB_YESNO) == IDYES)
		{

			for (ROWCOL n =0; n < (ROWCOL)from_list.GetSize(); n++)
			{
				if (from_list[n] == 0)
					from_list[n] = 1;
				if (to_list[n] == 0)
					to_list[n] = 1;
				RemoveRows(from_list[n], to_list[n]);
			}
			// if all rows deleted, put one back.
			if (GetRowCount() == 0)
			{
				SetRowCount(1);
			}
		}
	}
}


void CSampGridWnd::AppendSamplesFromBuffer(LPTSTR buffer, DWORD size)
{
	ROWCOL last_row = GetRowCount();
	CString cell_txt;

	if (last_row > 0) 
	{
		cell_txt = GetValueRowCol(last_row, 1);
		if (!cell_txt.IsEmpty())
		{
			SetRowCount(last_row + 1);
			last_row++;
		}
	}
	else
	{
		SetRowCount(1);
		last_row = 1;
	}
	
	PasteTextFromBuffer(buffer, size, CGXRange(last_row,1));
	if (GetColCount() > 1)
		SetColCount(1);
}