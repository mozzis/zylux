// CAGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CA.h"
#include "CAGridWnd.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CCAGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CCAGridWnd

CCAGridWnd::CCAGridWnd()
{
}

CCAGridWnd::~CCAGridWnd()
{
}


BEGIN_MESSAGE_MAP(CCAGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CCAGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCAGridWnd message handlers

void CCAGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT));

	CCAPPS* pps = &CAGetApp()->m_pps;

	ROWCOL num_rows = pps->m_numsamps;
	if (pps->UseBackground())
		num_rows++;
	if (pps->m_numnegreps > 0)
		num_rows++;
	if (pps->m_numposreps > 0)
		num_rows++;

	ROWCOL num_cols, max_cols;

	if ((pps->m_numreps == 1) && (pps->m_numposreps == 1) && (pps->m_numnegreps == 1))
	{
		num_cols = 4;
		max_cols = 1;
	}
	else if ((pps->m_numreps == 1) && (pps->m_numposreps == 0) && (pps->m_numnegreps == 0))
	{
		num_cols = 4;
		max_cols = 1;
	}
	else
	{
		max_cols = pps->m_numreps;
		if (pps->m_numposreps > max_cols)
			max_cols = pps->m_numposreps;
		if (pps->m_numnegreps > max_cols)
			max_cols = pps->m_numnegreps;
		num_cols = max_cols + 6;
	}

	SetRowCount(num_rows);
	SetColCount(num_cols);

	// Allow changes to the grid
	param->SetLockReadOnly(FALSE);

	// Set all the cells to read-only
	SetStyleRange(CGXRange(0, 0, num_rows, num_cols), CGXStyle()
		.SetReadOnly(TRUE));

	// Set non-header cells to static (will change as necessary)
	SetStyleRange(CGXRange(1, 1, num_rows, num_cols), CGXStyle()
		.SetControl(GX_IDS_CTRL_STATIC));

	UINT i;
	CString head_str;

	// Setup the column headings
	ROWCOL col = 1;

	// Corner
	SetStyleRange(CGXRange(0, 0), CGXStyle().SetValue(""));

	// Sample column heading
	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Sample"));


	// Set the replicate column headings and alignment
	for (i = 1; i <= max_cols; i++)
	{
		head_str.Format("Rep %d", i);
		// Set all the number holding cells to right alignment
		SetStyleRange(CGXRange(1, col, num_rows, col), CGXStyle()
			.SetHorizontalAlignment(DT_RIGHT));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));

	}

	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Result"));
	// Show the rest of the columns when there is more than one replicate
	if (max_cols > 1)
	{
		// Set all the number holding cells to right alignment
		SetStyleRange(CGXRange(1, col, num_rows, col+3), CGXStyle()
			.SetHorizontalAlignment(DT_RIGHT));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
	}
	else
	{
		// Set all the number holding cells to right alignment
		SetStyleRange(CGXRange(1, col, num_rows, col), CGXStyle()
			.SetHorizontalAlignment(DT_RIGHT));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
	}


	ROWCOL row = 1;

	// Set the sample names

	// If there is a background, set up the background row
	if (pps->UseBackground())
	{
		// Make background row "B"
		SetStyleRange(CGXRange(row, 0), CGXStyle().SetValue("B"));
		if (pps->m_numreps < max_cols)
		{
			// Set unused replicate cells and Results column to gray.
			SetStyleRange(CGXRange(row, pps->m_numreps+2, row, max_cols+2 ),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}
		else
		{
			// Set Results column to gray.
			SetStyleRange(CGXRange(row, max_cols+2),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}

		SetStyleRange(CGXRange(row++, 1), CGXStyle().SetValue("Background"));
	}


	// Make the Neg and Pos rows
	if (pps->m_numnegreps > 0)
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle().SetValue("N"));
		if (pps->m_numnegreps < max_cols)
		{
			// Set unused replicate cells and Results column to gray.
			SetStyleRange(CGXRange(row, pps->m_numnegreps+2, row, max_cols+2 ),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}
		else
		{
			// Just set Results column to gray.
			SetStyleRange(CGXRange(row, max_cols+2),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}
		SetStyleRange(CGXRange(row++, 1), CGXStyle().SetValue("Negative Control"));
	}

	if (pps->m_numposreps > 0)
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle().SetValue("P"));
		if (pps->m_numposreps < max_cols)
		{
			// Set unused replicate cells and Results column to gray.
			SetStyleRange(CGXRange(row, pps->m_numposreps+2, row, max_cols+2 ),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}
		else
		{
			// Set Results column to gray.
			SetStyleRange(CGXRange(row, max_cols+2),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}

		SetStyleRange(CGXRange(row++, 1), CGXStyle().SetValue("Positive Control"));
	}

	for (i = 1; i <= pps->m_numsamps; i++)
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle()
			.SetValue((short)i));
		if (pps->m_numreps < max_cols)
		{
			// Set unused replicate cells to gray.
			SetStyleRange(CGXRange(row, pps->m_numreps+2, row, max_cols+1 ),
				CGXStyle().SetInterior(RGB(192, 192, 192)));
		}
		SetStyleRange(CGXRange(row++, 1), CGXStyle().SetReadOnly(FALSE)
			.SetControl(GX_IDS_CTRL_EDIT)
			.SetMaxLength(CCAPPS::SAMPLENAME_SIZE - 1));

	}


	// Fit these columns to the text I've put in them
	ResizeColWidthsToFit(CGXRange(0, 0, num_rows, num_cols));

	param->SetActivateCellFlags(GX_CAFOCUS_SETCURRENT);

	// Disallow changes to the grid
	param->SetLockReadOnly(TRUE);

}


void CCAGridWnd::CMCreateMenu(CMenu& menu)
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
		// Add the background
		item_str.Format("%s %ld", _T("&Set background to"), m_ctxt_cell_int);
		CMAddItemNG(menu, ID_CONTEXT_BACKGROUND, item_str);

	}

}


BOOL CCAGridWnd::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt,
					  int nType)
{
	if (CProtocolGridWnd::StoreStyleRowCol(nRow, nCol, pStyle, mt, nType))
	{
		CCAPPS* pps = &CAGetApp()->m_pps;
		ROWCOL first_row = 1;
		if (pps->UseBackground())
			first_row++;
		if (pps->m_numnegreps > 0)
			first_row++;
		if (pps->m_numposreps > 0)
			first_row++;

		if ((nCol == 1) && (nRow >= first_row) &&
			pStyle->GetIncludeValue())
		{
			CCADoc* pDoc = CAGetDoc();
			if (pDoc)
			{
				CString val = pStyle->GetValue();
				//strcpy(pps->m_samplelist[nRow - first_row].sampname, pStyle->GetValue());
				if (pps->m_samplelist[nRow - first_row] != val)
				{
					pps->m_samplelist[nRow - first_row] = val;
					pDoc->SetModifiedFlag(TRUE);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}
