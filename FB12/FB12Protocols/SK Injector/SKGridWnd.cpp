// SKGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "SKGridWnd.h"
#include "General.h"
#include "SKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CSKGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CSKGridWnd

CSKGridWnd::CSKGridWnd()
{
}

CSKGridWnd::~CSKGridWnd()
{
}


BEGIN_MESSAGE_MAP(CSKGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CSKGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSKGridWnd message handlers

void CSKGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT));

	CSKPPS* pps = &SKGetApp()->m_pps;

	ROWCOL num_rows = pps->m_numsamples + (pps->UseBackground() ? 1 : 0);
	ROWCOL num_cols = ((pps->m_numreplicates > 1) ? 5 : 2) + pps->m_numreplicates;

	// Set the grid size
	SetRowCount(num_rows);
	SetColCount(num_cols);

	// Allow changes to the grid
	GetParam()->SetLockReadOnly(FALSE);

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

	// Replicates columns
	for (i = 1; i <= pps->m_numreplicates; i++)
	{
		head_str.Format("Rep %d", i);
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));
	}
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
	}
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
	}

	// Setup the sample numbers
	ROWCOL row = 1;
	if (pps->UseBackground())
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle()
			.SetValue("B"));
		SetStyleRange(CGXRange(row++, 1), CGXStyle()
			.SetValue("Background"));
	}
	for (i = 1; i <= pps->m_numsamples; i++)
	{
		// set sample number
		SetStyleRange(CGXRange(row++, 0), CGXStyle()
			.SetValue(i));
	}

	// Set all the number holding cells to right alignment
	SetStyleRange(CGXRange(1, 1, num_rows, num_cols), CGXStyle()
		.SetHorizontalAlignment(DT_RIGHT));

	ResizeColWidthsToFit(CGXRange(0, 0, num_rows, 0));

	// Can use tooltips
	EnableGridToolTips();
	param->GetStylesMap()->AddUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));

	//param()->EnableUndo(TRUE);

	// Disallow changes to the grid
	GetParam()->SetLockReadOnly(TRUE);
}

void CSKGridWnd::CMCreateMenu(CMenu& menu)
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
