// SAGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SA.h"
#include "SAGridWnd.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CSAGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CSAGridWnd

CSAGridWnd::CSAGridWnd()
{
}

CSAGridWnd::~CSAGridWnd()
{
}


BEGIN_MESSAGE_MAP(CSAGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CSAGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSAGridWnd message handlers

void CSAGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	ChangeStandardStyle(CGXStyle().SetControl(GX_IDS_CTRL_EDIT));

	CSAPPS* pps = &SAGetApp()->m_pps;

	ROWCOL num_rows = pps->m_numsamps + (pps->UseBackground() ? 1 : 0);

	ROWCOL num_cols = (pps->m_numreps > 1) ? pps->m_numreps + 5 : 3;
	//if (pps->Use95ConfCol())
	//	num_cols++;
	//if(pps->Use99ConfCol())
	//	num_cols++;


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


	// Set the replicate column headings
	for (i = 1; i <= pps->m_numreps; i++)
	{
		head_str.Format("Rep %d", i);
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));
	}

	// Show the rest of the columns when there is more than one replicate
	if (pps->m_numreps > 1)
	{
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));
	}
	else  // m_numreps == 1
	{
		// Just one replicate, so show the Net column
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
	}

	//if (pps->Use95ConfCol())
	//	SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("95% Conf"));
	//if(pps->Use99ConfCol())
	//	SetStyleRange(CGXRange(0, col), CGXStyle().SetValue("99% Conf"));

	ROWCOL row = 1;

	// Set the sample names

	// If there is a background, set up the background row
	if (pps->UseBackground())
	{
		// Make background row "B"
		SetStyleRange(CGXRange(row, 0), CGXStyle()
			.SetValue("B"));
		SetStyleRange(CGXRange(row++, 1), CGXStyle()
			.SetValue("Background"));
	}


	for (i = 1; i <= pps->m_numsamps; i++)
	{
		SetStyleRange(CGXRange(row, 0), CGXStyle().SetValue(i));
		SetStyleRange(CGXRange(row++, 1), CGXStyle().SetReadOnly(FALSE)
			.SetControl(GX_IDS_CTRL_EDIT)
			.SetMaxLength(CSAPPS::SAMPLENAME_SIZE - 1));
	}

	// Set all the number holding cells to right alignment
	SetStyleRange(CGXRange(1, 2, num_rows, num_cols), CGXStyle()
		.SetHorizontalAlignment(DT_RIGHT));

	// Fit these columns to the text I've put in them
	ResizeColWidthsToFit(CGXRange(0, 0, num_rows, num_cols));

	param->SetActivateCellFlags(GX_CAFOCUS_SETCURRENT);

	// Disallow changes to the grid
	param->SetLockReadOnly(TRUE);

}


void CSAGridWnd::AddReplicate(UINT last_replicate)
{
	CString head_str;
	ROWCOL num_rows	= GetRowCount();

	// Allow changes to the grid
	GetParam()->SetLockReadOnly(FALSE);

	if (last_replicate == 1)
	{
		InsertCols((ROWCOL)3, (ROWCOL)3);
		InsertCols((ROWCOL)7, (ROWCOL)1);

		UINT col = last_replicate + 2;
		head_str.Format("Rep %d", last_replicate+1);
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue(head_str));

		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Average"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Avg"));
		col++; // Replace where the "Net" label used to go.
		//SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("Net"));
		SetStyleRange(CGXRange(0, col++), CGXStyle().SetValue("% SD/Net"));

		// Fit these columns to the text I've put in them
		ResizeColWidthsToFit(CGXRange(0, 3, num_rows, GetColCount()));

		// Set all the number holding cells to right alignment, Static control, and
		// read-only
		SetStyleRange(CGXRange(1, 2, num_rows, GetColCount()), CGXStyle()
			.SetHorizontalAlignment(DT_RIGHT).SetControl(GX_IDS_CTRL_STATIC)
			.SetReadOnly(TRUE));
	}
	else
	{
		InsertCols((ROWCOL)last_replicate+2, (ROWCOL)1);

		head_str.Format("Rep %d", last_replicate+1);
		SetStyleRange(CGXRange(0, last_replicate+2), CGXStyle().SetValue(head_str));

		// Set all the number holding cells to right alignment, Static control, and
		// read-only
		SetStyleRange(CGXRange(1, last_replicate+2, num_rows, last_replicate+2), CGXStyle()
			.SetHorizontalAlignment(DT_RIGHT).SetControl(GX_IDS_CTRL_STATIC)
			.SetReadOnly(TRUE));

		// Fit these columns to the text I've put in them
		ResizeColWidthsToFit(CGXRange(0, last_replicate+2, num_rows, last_replicate+2));

	}
	// Disallow changes to the grid
	GetParam()->SetLockReadOnly(TRUE);

}

void CSAGridWnd::AddSample(UINT last_sample, bool use_background)
{
	ROWCOL num_cols	= GetColCount();
	ROWCOL new_row;

	GetParam()->SetLockReadOnly(FALSE);

	new_row = (use_background) ? (last_sample + 1) : last_sample;


	InsertRows((ROWCOL)new_row, (ROWCOL)1);

	CSAPPS& pps = SAGetApp()->m_pps;
	CString samp_str;
	samp_str.Format("Sample %ld", pps.m_numsamps);
	pps.m_samplelist[pps.m_numsamps - 1] = samp_str;
	SetStyleRange(CGXRange(new_row, 1), CGXStyle().SetReadOnly(FALSE)
		.SetControl(GX_IDS_CTRL_EDIT).SetMaxLength(CSAPPS::SAMPLENAME_SIZE - 1)
		.SetValue(pps.m_samplelist[pps.m_numsamps - 1]));
	SetStyleRange(CGXRange(new_row, 0), CGXStyle().SetValue(last_sample));

	// Set all the non-samplename cells to readonly and static control
	SetStyleRange(CGXRange(new_row, 2, new_row, num_cols), CGXStyle()
		.SetHorizontalAlignment(DT_RIGHT)
		.SetControl(GX_IDS_CTRL_STATIC).SetReadOnly(TRUE));

	GetParam()->SetLockReadOnly(TRUE);
}


void CSAGridWnd::CMCreateMenu(CMenu& menu)
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



BOOL CSAGridWnd::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt,
					  int nType)
{
	if (CProtocolGridWnd::StoreStyleRowCol(nRow, nCol, pStyle, mt, nType))
	{
		CSAPPS* pps = &SAGetApp()->m_pps;
		ROWCOL first_row = pps->UseBackground() ? 2 : 1;
		if ((nCol == 1) && (nRow >= first_row) &&
			pStyle->GetIncludeValue())
		{
			CSADoc* pDoc = SAGetDoc();
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
