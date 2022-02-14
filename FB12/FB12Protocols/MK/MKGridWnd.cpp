// MKGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "MKGridWnd.h"
#include "General.h"
#include "MKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CMKGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CMKGridWnd

CMKGridWnd::CMKGridWnd()
{
}

CMKGridWnd::~CMKGridWnd()
{
}


BEGIN_MESSAGE_MAP(CMKGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CMKGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMKGridWnd message handlers

void CMKGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT));

	AdjustGrid(true);
}

void CMKGridWnd::CMCreateMenu(CMenu& menu)
{
	CString item_str;

	CProtocolGridWnd::CMCreateMenu(menu);
/*
	// Add the Copy if we can
	if (CanCopy())
	{
		// Add the copy item
		CMAddItemNG(menu, ID_EDIT_COPY, _T("&Copy"));
	}
*/
	// Add the background if applicable
	if (!m_ctxt_cell_str.IsEmpty() && (m_ctxt_cell_val != 0.0))
	{
		// Add the background item
		item_str.Format("%s %ld", _T("&Set background to"), m_ctxt_cell_int);
		CMAddItemNG(menu, ID_CONTEXT_BACKGROUND, item_str);
	}
}

void CMKGridWnd::AdjustGrid(bool nominal)
{
	CGXGridParam *param = GetParam();

	CMKPPS* pps = &MKGetApp()->m_pps;

	ROWCOL num_rows = pps->m_nummeasurements;
	if (!nominal)
	{
		num_rows *= pps->m_numsamps;
	}
	ROWCOL num_cols = 1 +
		((pps->m_numreps + ((pps->m_numreps > 1) ? 4 : 1)) * pps->m_numsamps);

	// Allow changes to the grid
	GetParam()->SetLockReadOnly(FALSE);

	// Don't show changes to grid
	BOOL bOldLock = LockUpdate(TRUE);

	// Set the grid size
	SetRowCount(num_rows);
	SetColCount(num_cols);

	// Clear all the cells in the grid : )
	SetStyleRange(CGXRange(0, 0, num_rows, num_cols), CGXStyle().SetValue(""));

	// Set all the cells to read-only
	SetStyleRange(CGXRange(0, 0, num_rows, num_cols), CGXStyle()
		.SetReadOnly(TRUE));
	// Set non-header cells to static (will change as necessary)
	SetStyleRange(CGXRange(1, 1, num_rows, num_cols), CGXStyle()
		.SetControl(GX_IDS_CTRL_STATIC));

	ROWCOL i;
	CString head_str;

	// Setup the column headings
	ROWCOL col = 0;

	// upper, left corner
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(""));

	// Time column
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Time"));

	// Samples
	UINT j;
	for (j = 1; j <= pps->m_numsamps; j++)
	{
		// Replicates columns
		for (i = 1; i <= pps->m_numreps; i++)
		{
			head_str.Format("S%d Rep %d", j, i);
			SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));
		}
		if (pps->m_numreps > 1)
		{
			SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average"));
			SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
		}
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
		if (pps->m_numreps > 1)
		{
			SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
		}
	}

	// Setup the sample numbers
	ROWCOL row = 1;
	for (i = 0; i < pps->m_nummeasurements; i++)
	{
		CString t_str;
		t_str.Format("T%ld", i);
		if (nominal)
		{
			// set sample number
			SetStyleRange(CGXRange(row++, 0), CGXStyle().SetValue(t_str));
		}
		else
		{
			for (j = 0; j < pps->m_numsamps; j++)
			{
				// set sample number
				SetStyleRange(CGXRange(row++, 0), CGXStyle().SetValue(t_str));
			}
		}
	}

	// Set all the number holding cells to right alignment
	SetStyleRange(CGXRange(1, 1, num_rows, num_cols), CGXStyle()
		.SetHorizontalAlignment(DT_RIGHT));

	ResizeColWidthsToFit(CGXRange(0, 0, num_rows, 0));

	// Make the first 2 columns frozen
	SetFrozenCols(1, 0);

	// Can use tooltips
	EnableGridToolTips();
	param->GetStylesMap()->AddUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));

	//param()->EnableUndo(TRUE);

	// Show grid changes
	LockUpdate(bOldLock);
	Redraw();

	// Disallow changes to the grid
	GetParam()->SetLockReadOnly(TRUE);
}
