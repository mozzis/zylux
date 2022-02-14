// DAGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DA.h"
#include "DAGridWnd.h"
#include "General.h"
#include "DADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CDAGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CDAGridWnd

char* CDAGridWnd::m_xform_net_str[] =
{
	"Net A - Net B",
	"Net B - Net A",
	"Net A / Net B",
	"Net B / Net A",
	"Net A / (Net B - Net A)",
};

char* CDAGridWnd::m_xform_norm_str[] =
{
	"Norm A - Norm B",
	"Norm B - Norm A",
	"Norm A / Norm B",
	"Norm B / Norm A",
	"Norm A / (Norm B - Norm A)",
};

CDAGridWnd::CDAGridWnd()
{
}

CDAGridWnd::~CDAGridWnd()
{
}


BEGIN_MESSAGE_MAP(CDAGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CDAGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAGridWnd message handlers

void CDAGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT));

	CDAPPS* pps = &DAGetApp()->m_pps;

	ROWCOL num_rows = pps->m_numsamples + (pps->UseBackground() ? 1 : 0);
	ROWCOL num_cols = ((pps->m_numreplicates > 1) ? 13 : 6) + pps->m_numreplicates * 2;

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

	// Sample column
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Sample"));

	// start of Transform section
	col += (pps->m_numreplicates > 1) ? 4 : 3;

	// start of Series A section
	for (i = 1; i <= pps->m_numreplicates; i++)
	{
		head_str.Format("Rep %d A", i);
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));
	}
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average A"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
	}
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net A"));
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
	}

	// start of Series B section
	for (i = 1; i <= pps->m_numreplicates; i++)
	{
		head_str.Format("Rep %d B", i);
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));
	}
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average B"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
	}
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net B"));
	if (pps->m_numreplicates > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
	}

	// Setup the sample numbers, and make sample fields editable
	ROWCOL row = 1;
	if (pps->UseBackground())
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle()
			.SetValue("B"));
		SetStyleRange(CGXRange(row++, 1), CGXStyle()
			.SetValue("Background"));
	}
	bool run_mode = (DAGetApp()->m_mode == CDAApp::APPMODE_RUN) ? true : false;
	for (i = 1; i <= pps->m_numsamples; i++)
	{
		// set sample number
		SetStyleRange(CGXRange(row, 0), CGXStyle()
			.SetValue(i));
		// set sample edit to read/write, edit control with max length
		SetStyleRange(CGXRange(row++, 1), CGXStyle()
			.SetReadOnly(run_mode ? FALSE : TRUE)
			.SetControl(run_mode ? GX_IDS_CTRL_EDIT : GX_IDS_CTRL_STATIC)
			.SetMaxLength(CDAPPS::SAMPLENAME_SIZE - 1));
	}

	// Set all the number holding cells to right alignment
	SetStyleRange(CGXRange(1, 2, num_rows, num_cols), CGXStyle()
		.SetHorizontalAlignment(DT_RIGHT));

	// Make the first five or six columns frozen
	SetFrozenCols((pps->m_numreplicates > 1) ? 5 : 4, 0);

	// Can use tooltips
	EnableGridToolTips();
	param->GetStylesMap()->AddUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));

	ROWCOL border = (pps->m_numreplicates > 1) ? 5 : 4;
	SetStyleRange(CGXRange().SetCols(border),
		CGXStyle().SetBorders(gxBorderRight, CGXPen(PS_SOLID, 2, RGB(0, 0, 0))));
	border += pps->m_numreplicates + ((pps->m_numreplicates > 1) ? 4 : 1);
	SetStyleRange(CGXRange().SetCols(border),
		CGXStyle().SetBorders(gxBorderRight, CGXPen(PS_SOLID, 1, RGB(0, 0, 0))));

	//param()->EnableUndo(TRUE);

	// Disallow changes to the grid
	GetParam()->SetLockReadOnly(TRUE);
}

void CDAGridWnd::CMCreateMenu(CMenu& menu)
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
		// Add the background A item
		item_str.Format("%s %ld", _T("Set background &A to"), m_ctxt_cell_int);
		CMAddItemNG(menu, ID_CONTEXT_BACKGROUNDA, item_str);

		// Add the background B item
		item_str.Format("%s %ld", _T("Set background &B to"), m_ctxt_cell_int);
		CMAddItem(menu, ID_CONTEXT_BACKGROUNDB, item_str);
	}

	// Add the normalize if applicable
	if (!m_ctxt_cell_str.IsEmpty() && (m_ctxt_cell_val != 0.0))
	{
		// Add the normalize item
		item_str.Format("%s %.2f", _T("&Normalize B to"), m_ctxt_cell_val);
		CMAddItemNG(menu, ID_CONTEXT_NORMALIZE, item_str);
	}
}

BOOL CDAGridWnd::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol,
	const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	if (CProtocolGridWnd::StoreStyleRowCol(nRow, nCol, pStyle, mt, nType))
	{
		CDAPPS* pps = &DAGetApp()->m_pps;
		ROWCOL first_row = pps->UseBackground() ? 2 : 1;
		if ((nCol == 1) && (nRow >= first_row) &&
			pStyle->GetIncludeValue())
		{
			CDADoc* pDoc = DAGetDoc();
			if (pDoc)
			{
				CString val = pStyle->GetValue();
				if (pDoc->m_pps.m_samplelist[nRow - first_row] != val)
				{
					pDoc->m_pps.m_samplelist[nRow - first_row] = val;
					pDoc->SetModifiedFlag(TRUE);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}
