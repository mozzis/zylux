// DAView.cpp : implementation file
//

#include "stdafx.h"
#include "DA.h"
#include "General.h"
#include "DAView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAView

IMPLEMENT_DYNCREATE(CDAView, CGridView)

CDAView::CDAView()
	: CGridView(CDAView::IDD), hilite_row(0xFFFFFFFF), hilite_col(0xFFFFFFFF)
{
	//{{AFX_DATA_INIT(CDAView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDAView::~CDAView()
{
}

BOOL CDAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CDAView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDAView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDAView, CGridView)
	//{{AFX_MSG_MAP(CDAView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE_AS_TEXT, OnFileSaveAsText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_CHECK_NORMALIZE, OnCheckNormalize)
	ON_EN_KILLFOCUS(IDC_EDIT_BACKGROUNDA, OnKillfocusEditBackgroundA)
	ON_EN_KILLFOCUS(IDC_EDIT_BACKGROUNDB, OnKillfocusEditBackgroundB)
	ON_EN_KILLFOCUS(IDC_EDIT_NORMALIZE, OnKillfocusEditNormalize)
	ON_COMMAND(ID_CONTEXT_BACKGROUNDA, OnContextBackgroundA)
	ON_COMMAND(ID_CONTEXT_BACKGROUNDB, OnContextBackgroundB)
	ON_COMMAND(ID_CONTEXT_NORMALIZE, OnContextNormalize)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGridView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAView diagnostics

#ifdef _DEBUG
void CDAView::AssertValid() const
{
	CGridView::AssertValid();
}

void CDAView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CDADoc* CDAView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDADoc)));
	return (CDADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDAView drawing

void CDAView::OnDraw(CDC* pDC)
{
	CDADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDAView printing

BOOL CDAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Set the print header
	CDADoc* pDoc = GetDocument();
	CGXProperties* pProp = m_grid.GetParam()->GetProperties();
	pProp->SetCenterHorizontal(FALSE);
	CString hd_str;

	ROWCOL row_hdr = 0;

	hd_str.Format("Protocol name: %s", SCGetFileTitle(pDoc->m_pps.m_protocolname));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Date: %s", pDoc->m_datetime.Format("%x"));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Time: %s", pDoc->m_datetime.Format("%X"));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);

	// Series A
	hd_str.Format("Delay time A: %s", SCFormatDeciseconds(pDoc->m_pps.m_delaytime_a));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Measurement time A: %s", SCFormatDeciseconds(pDoc->m_pps.m_meastime_a));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background A: %ld RLU/s", CSample::m_background_a);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);

	// Series B
	hd_str.Format("Delay time B: %s", SCFormatDeciseconds(pDoc->m_pps.m_delaytime_b));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Measurement time B: %s", SCFormatDeciseconds(pDoc->m_pps.m_meastime_b));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background B: %ld RLU/s", CSample::m_background_b);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);

	// File title in footer
	ROWCOL row_ftr = 0;
	pProp->GetDataFooter().StoreStyleRowCol(++row_ftr, 2,
		CGXStyle().SetValue(GetDocument()->GetTitle()), gxCopy);

	// Set header and footer to 1 inch from edge
	pProp->SetDistances(72, 72);

	// Set main margins to left and right 1" and
	// top and bottom just below the header and above the footer
	int font_height = m_grid.GetFontHeight();
	pProp->SetMargins(72 + font_height * row_hdr, 72, 72 + font_height * row_ftr, 72);

	pInfo->SetMaxPage(0xffff);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDAView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	DAGetApp()->FB12Inhibit();
	//m_grid.UnhiliteCell(hilite_row, hilite_col);
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CDAView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	//m_grid.HiliteCell(hilite_row, hilite_col);
	DAGetApp()->FB12Uninhibit();
}

void CDAView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CDAView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDAView message handlers

void CDAView::OnInitialUpdate()
{
	m_grid.SubclassDlgItem(IDC_DAGRID, this);
	m_grid.Initialize();

	CGridView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	MyGridResize();

	CDADoc* pDoc = (CDADoc*)GetDocument();

	// Set the display header information
	CString display_str;
	CWnd* pWnd;

	// Delay time A
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIMEA);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(
		pDoc->m_pps.UseStartButton() ? 0 : pDoc->m_pps.m_delaytime_a));
	pWnd->EnableWindow(pDoc->m_pps.UseStartButton() ? FALSE : TRUE);

	// Meas time A
	pWnd = GetDlgItem(IDC_EDIT_MEASTIMEA);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_meastime_a));

	// Delay time B
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIMEB);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(
		pDoc->m_pps.UseStartButton() ? 0 : pDoc->m_pps.m_delaytime_b));
	pWnd->EnableWindow(pDoc->m_pps.UseStartButton() ? FALSE : TRUE);

	// Meas time B
	pWnd = GetDlgItem(IDC_EDIT_MEASTIMEB);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_meastime_b));

	// Normalize
	pWnd = GetDlgItem(IDC_EDIT_NORMALIZE);
	ASSERT(pWnd != NULL);
	display_str.Format("%.2f", CSample::m_normalize_value);
	pWnd->SetWindowText(display_str);

	// Background A
	pWnd = GetDlgItem(IDC_EDIT_BACKGROUNDA);
	ASSERT(pWnd != NULL);
	display_str.Format("%ld", CSample::m_background_a);
	pWnd->SetWindowText(display_str);

	// Background B
	pWnd = GetDlgItem(IDC_EDIT_BACKGROUNDB);
	ASSERT(pWnd != NULL);
	display_str.Format("%ld", CSample::m_background_b);
	pWnd->SetWindowText(display_str);
}

void CDAView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CDAView::MyGridResize()
{
	if (::IsWindow(m_hWnd) && ::IsWindow(m_grid.m_hWnd))
	{
		RECT view_rect;
		GetClientRect(&view_rect);

		CPoint view_pt(0, 0), grid_pt(0, 0);
		ClientToScreen(&view_pt);
		m_grid.ClientToScreen(&grid_pt);

		m_grid.SetWindowPos(NULL, 0, 0,
			view_rect.right, view_rect.bottom - (grid_pt.y - view_pt.y),
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
		m_grid.Redraw();
		SetScrollSizes(MM_TEXT, CSize(0, 0));
	}
}

void CDAView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint >= 0)
	{
		// TODO: Add your specialized code here and/or call the base class
		BOOL bOldLock = m_grid.LockUpdate(TRUE);

		// Allow changes to the grid
		m_grid.GetParam()->SetLockReadOnly(FALSE);

		// Get a pointer to the document
		CDADoc* pDoc = (CDADoc*)GetDocument();

		if (lHint == 0)
		{
 			// Ensure that each view's current cell is stored
			m_grid.TransferCurrentCell(TRUE, GX_INVALIDATE, FALSE);

			// Set the display header information
			CWnd* pWnd;

			// Date
			pWnd = GetDlgItem(IDC_EDIT_DATE);
			ASSERT(pWnd != NULL);
			pWnd->SetWindowText(pDoc->m_datetime.Format("%x"));

			// Time
			pWnd = GetDlgItem(IDC_EDIT_TIME);
			ASSERT(pWnd != NULL);
			pWnd->SetWindowText(pDoc->m_datetime.Format("%X"));

			// Change the column headers to appropriate strings
			m_grid.SetStyleRange(CGXRange(0, 2), CGXStyle()
				.SetValue(CSample::m_normalize ? "Norm A" : "Net A"));
			m_grid.SetStyleRange(CGXRange(0, 3), CGXStyle()
				.SetValue(CSample::m_normalize ? "Norm B" : "Net B"));
			m_grid.SetStyleRange(CGXRange(0, 4), CGXStyle()
				.SetValue(CSample::m_normalize ?
					CDAGridWnd::m_xform_norm_str[pDoc->m_pps.m_transform] :
					CDAGridWnd::m_xform_net_str[pDoc->m_pps.m_transform]));
			if (pDoc->m_pps.m_numreplicates > 1)
			{
				m_grid.SetStyleRange(CGXRange(0, 5), CGXStyle()
					.SetValue("% SD/Transform"));
			}

			UINT sample_num;
			for (sample_num = 1; sample_num <= pDoc->m_numsamples; sample_num++)
			{
				UpdateSample(sample_num);
			}
		}
		else
		{
			// Update only the one sample
			UpdateSample(lHint);
			if ((lHint == 1) && pDoc->m_pps.UseBackground())
			{
				// We update the backgrounds and corresponding edit boxes
				CString back_str;

				// get averaged background, rounding to nearest integer
				CSample::m_background_a = (long)SCNearestInt(pDoc->m_samples[0].m_average_a);
				back_str.Format("%ld", CSample::m_background_a);
				SetDlgItemText(IDC_EDIT_BACKGROUNDA, back_str);

				// get averaged background, rounding to nearest integer
				CSample::m_background_b = (long)SCNearestInt(pDoc->m_samples[0].m_average_b);
				back_str.Format("%ld", CSample::m_background_b);
				SetDlgItemText(IDC_EDIT_BACKGROUNDB, back_str);
			}
		}

		// Fit these columns to the text I've put in them
		m_grid.ResizeColWidthsToFit(
			CGXRange(0, 0, m_grid.GetRowCount(), m_grid.GetColCount()));

		HiliteCell();

		// Disallow changes to the grid
		m_grid.GetParam()->SetLockReadOnly(TRUE);

		m_grid.LockUpdate(bOldLock);
		m_grid.Redraw();
	}
}

void CDAView::HiliteCell()
{
	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		// Get a pointer to the document
		CDADoc* pDoc = GetDocument();

		// Unhighlight the current cell
		m_grid.UnhiliteCell(hilite_row, hilite_col);

		// Indicate that nothing is highlighted
		hilite_row = 0xFFFFFFFF;
		hilite_col = 0xFFFFFFFF;

		// Highlight the correct cell
		if (pDoc->m_sample_num < pDoc->m_numsamples)
		{
			// Calculate the hilite row and col
			hilite_row = pDoc->m_sample_num + 1;
			if (pDoc->m_series == CSample::SERIES_A)
			{
				if (pDoc->m_pps.m_numreplicates > 1)
				{
					hilite_col = 6 + pDoc->m_replicate_num;
				}
				else
				{
					hilite_col = 5 + pDoc->m_replicate_num;
				}
			}
			else
			{
				if (pDoc->m_pps.m_numreplicates > 1)
				{
					hilite_col = 10 + pDoc->m_pps.m_numreplicates + pDoc->m_replicate_num;
				}
				else
				{
					hilite_col = 6 + pDoc->m_pps.m_numreplicates + pDoc->m_replicate_num;
				}
			}

			m_grid.HiliteCell(hilite_row, hilite_col);

			// Scroll to the new cell
			m_grid.ScrollCellInView(hilite_row, hilite_col);
		}
	}
}

// UpdateSample()
//
// Update a specific sample
//
// Inputs:
//   sample_num - the sample to update: 1 - m_numsamples
//
// Output: none

void CDAView::UpdateSample(UINT sample_num)
{
	CDADoc* pDoc = (CDADoc*)GetDocument();

	ROWCOL row = sample_num;
	sample_num--;

	CSample* sample = &pDoc->m_samples[sample_num];

	ROWCOL col;

	CString double_str;

	int reps_a = sample->GetNumReplicates(CSample::SERIES_A);
	int reps_b = sample->GetNumReplicates(CSample::SERIES_B);

	// Sample name
	col = 1;
	if ((sample_num == 0) && pDoc->m_pps.UseBackground())
	{
		m_grid.SetValueRange(CGXRange(row, col++), "Background");
	}
	else
	{
		m_grid.SetValueRange(CGXRange(row, col++), 
			pDoc->m_pps.m_samplelist[sample_num - (pDoc->m_pps.UseBackground() ? 1 : 0)]);
	}

	// Transform
	if ((reps_a > 0) && (reps_b > 0))
	{
		// Net A
		if ((sample_num == 0) && pDoc->m_pps.UseBackground())
		{
			m_grid.SetValueRange(CGXRange(row, col++), "N/A");
		}
		else
		{
			if (CSample::m_normalize)
			{
				if (sample->m_xnet_a_overflow)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
				}
				else
				{
					double_str.Format("%.2f", sample->m_xnet_a);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
			else
			{
				double_str.Format("%.2f", sample->m_net_a);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}

		// Net B
		if ((sample_num == 0) && pDoc->m_pps.UseBackground())
		{
			m_grid.SetValueRange(CGXRange(row, col++), "N/A");
		}
		else
		{
			if (CSample::m_normalize)
			{
				double_str.Format("%.2f", sample->m_xnet_b);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
			else
			{
				double_str.Format("%.2f", sample->m_net_b);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}

		// Transform
		if ((sample_num == 0) && pDoc->m_pps.UseBackground())
		{
			m_grid.SetValueRange(CGXRange(row, col++), "N/A");
		}
		else
		{
			if (sample->m_xform_overflow)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
			}
			else
			{
				double_str.Format("%.2f", sample->m_xform);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}

		// Precision of transform
		if (pDoc->m_pps.m_numreplicates > 1)
		{
			if ((sample_num == 0) && pDoc->m_pps.UseBackground())
			{
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				if (sample->m_precision_xform_na)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "N/A");
				}
				else if (sample->m_precision_xform_overflow)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
				}
				else
				{
					double_str.Format("%.2f", sample->m_precision_xform);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
		}
	}
	else
	{
		// Net A
		m_grid.SetValueRange(CGXRange(row, col++), "");

		// Net B
		m_grid.SetValueRange(CGXRange(row, col++), "");

		// Transform
		m_grid.SetValueRange(CGXRange(row, col++), "");

		// Precision of transform
		if (pDoc->m_pps.m_numreplicates > 1)
		{
			m_grid.SetValueRange(CGXRange(row, col++), "");
		}
	}

	int rep;

	// Series A
	if (reps_a > 0)
	{
		if (sample->m_replicates_a.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates_a.GetSize(); rep++)
			{
				if (sample->m_replicates_a[rep].m_used)
				{
					m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates_a[rep].m_RLU);
				}
				else
				{
					m_grid.SetValueRange(CGXRange(row, col++), "");
				}
			}

			// Average
			double_str.Format("%.2f", sample->m_average_a);
			m_grid.SetValueRange(CGXRange(row, col++), double_str);

			// Precision
			if (sample->m_precision_a_overflow)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
			}
			else
			{
				double_str.Format("%.2f", sample->m_precision_a);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}

			// If background, do something different
			if ((sample_num == 0) && pDoc->m_pps.UseBackground())
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");

				// Precision of net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				// Net
				double_str.Format("%.2f", sample->m_net_a);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);

				// Precision of net
				if (sample->m_precision_net_a_overflow)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
				}
				else
				{
					double_str.Format("%.2f", sample->m_precision_net_a);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
		}
		else
		{
			// Rep 1
			m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates_a[0].m_RLU);

			// If background, do something different
			if (pDoc->m_pps.UseBackground() && (sample_num == 0))
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				// Net
				double_str.Format("%.2f", sample->m_net_a);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}
	}
	else
	{
		if (sample->m_replicates_a.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates_a.GetSize(); rep++)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "");
			}

			// Average
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Precision
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Net
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Precision of net
			m_grid.SetValueRange(CGXRange(row, col++), "");
		}
		else
		{
			// Rep 1
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Net
			m_grid.SetValueRange(CGXRange(row, col++), "");
		}
	}

	// Series B
	if (reps_b > 0)
	{
		if (sample->m_replicates_b.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates_b.GetSize(); rep++)
			{
				if (sample->m_replicates_b[rep].m_used)
				{
					m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates_b[rep].m_RLU);
				}
				else
				{
					m_grid.SetValueRange(CGXRange(row, col++), "");
				}
			}

			// Average
			m_grid.SetValueRange(CGXRange(row, col++), sample->m_average_b);

			// Precision
			if (sample->m_precision_b_overflow)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
			}
			else
			{
				double_str.Format("%.2f", sample->m_precision_b);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}

			// If background, do something different
			if ((sample_num == 0) && pDoc->m_pps.UseBackground())
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");

				// Precision of net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				// Net
				double_str.Format("%.2f", sample->m_net_b);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);

				// Precision of net
				if (sample->m_precision_net_b_overflow)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
				}
				else
				{
					double_str.Format("%.2f", sample->m_precision_net_b);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
		}
		else
		{
			// Rep 1
			m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates_b[0].m_RLU);

			// If background, do something different
			if (pDoc->m_pps.UseBackground() && (sample_num == 0))
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				// Net
				double_str.Format("%.2f", sample->m_net_b);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}
	}
	else
	{
		if (sample->m_replicates_b.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates_b.GetSize(); rep++)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "");
			}

			// Average
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Precision
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Net
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Precision of net
			m_grid.SetValueRange(CGXRange(row, col++), "");
		}
		else
		{
			// Rep 1
			m_grid.SetValueRange(CGXRange(row, col++), "");

			// Net
			m_grid.SetValueRange(CGXRange(row, col++), "");
		}
	}
}

void CDAView::OnFileSaveAsText()
{
	// TODO: Add your command handler code here
	DAGetApp()->FB12Inhibit();

	// pop-up file-open dlg to ask for location
	CFileDialog dlgFile(
		FALSE,
		_T(".txt"),
		SCGetFileTitle(GetDocument()->GetTitle()) + ".txt",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));
	dlgFile.m_ofn.lpstrTitle = _T("Save As Text");

	if (dlgFile.DoModal() == IDOK)
	{
		CFile textFile;

		if (textFile.Open(dlgFile.GetFileName(),
			CFile::modeCreate | CFile::modeWrite))
		{
			m_grid.CopyTextToFile(textFile, CGXRange(0, 1,
				m_grid.GetRowCount(), m_grid.GetColCount()));
			textFile.Close();
		}
		else
		{
			CString sz;
			sz.Format("File %s could not be opened!", dlgFile.GetFileName());
			SCMessageBox(sz);
		}
	}

	DAGetApp()->FB12Uninhibit();
}

void CDAView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CDAView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}

void CDAView::OnExcel()
{
	// TODO: Add your command handler code here
	DAGetApp()->FB12Inhibit();

 	// Ensure that each views current cell is stored
	m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	CDAPPS* pps = &DAGetApp()->m_pps;

	// Get the full path to the workbook
	CString wbpathname;
	if (pps->m_workbook.GetLength() > 0)
	{
		CString old_dir = SCSetCurrentDir(ProtGetApp()->m_maindir);
		TCHAR fullpath[_MAX_PATH];
		if (_fullpath(fullpath, pps->m_workbook, MAX_PATH))
		{
			wbpathname = fullpath;
		}
		else
		{
			wbpathname = pps->m_workbook;
		}
		SCSetCurrentDir(old_dir);
	}

	// Send to Excel
	m_grid.SendToExcel(pps->m_macroname, wbpathname, pps->m_worksheet,
		pps->m_cell_col, pps->m_cell_row);

	DAGetApp()->FB12Uninhibit();
}

void CDAView::OnKillfocusEditBackgroundA()
{
	// TODO: Add your control notification handler code here
	CEdit* wnd = (CEdit*)GetDlgItem(IDC_EDIT_BACKGROUNDA);
	ASSERT(wnd != NULL);

	CString background_str;
	DWORD pos;
	pos = wnd->GetSel();
	wnd->GetWindowText(background_str);
	long background_val = (long)SCNearestInt(atof(background_str));
	background_str.Format("%ld", background_val);
	wnd->SetWindowText(background_str);
	wnd->SetSel(pos);

	if (background_val != CSample::m_background_a)
	{
		CSample::m_background_a = background_val;
		CDADoc* pDoc = (CDADoc*)GetDocument();
		UINT i;
		for (i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].Recalculate();
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CDAView::OnKillfocusEditBackgroundB()
{
	// TODO: Add your control notification handler code here
	CEdit* wnd = (CEdit*)GetDlgItem(IDC_EDIT_BACKGROUNDB);
	ASSERT(wnd != NULL);

	CString background_str;
	DWORD pos;
	pos = wnd->GetSel();
	wnd->GetWindowText(background_str);
	long background_val = (long)SCNearestInt(atof(background_str));
	background_str.Format("%ld", background_val);
	wnd->SetWindowText(background_str);
	wnd->SetSel(pos);

	if (background_val != CSample::m_background_b)
	{
		CSample::m_background_b = background_val;
		CDADoc* pDoc = (CDADoc*)GetDocument();
		UINT i;
		for (i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].Recalculate();
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CDAView::OnKillfocusEditNormalize()
{
	// TODO: Add your control notification handler code here
	CEdit* wnd = (CEdit*)GetDlgItem(IDC_EDIT_NORMALIZE);
	ASSERT(wnd != NULL);

	CString norm_str;
	DWORD pos;
	pos = wnd->GetSel();
	wnd->GetWindowText(norm_str);
	double norm_val = SCRound(atof(norm_str));
	norm_str.Format("%.2f", norm_val);
	wnd->SetWindowText(norm_str);
	wnd->SetSel(pos);

	if (norm_val != CSample::m_normalize_value)
	{
		CSample::m_normalize_value = norm_val;
		CDADoc* pDoc = (CDADoc*)GetDocument();
		UINT i;
		for (i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].RecalculateTransform();
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CDAView::OnCheckNormalize()
{
	// TODO: Add your control notification handler code here
	CButton* pNorm = (CButton*)GetDlgItem(IDC_CHECK_NORMALIZE);
	ASSERT(pNorm != NULL);
	CSample::m_normalize = (pNorm->GetCheck() == 0) ? false : true;
	CWnd* pWnd = GetDlgItem(IDC_EDIT_NORMALIZE);
	ASSERT(pWnd != NULL);
	pWnd->EnableWindow(CSample::m_normalize ? TRUE : FALSE);
	GetDocument()->UpdateAllViews(NULL);
}

void CDAView::OnContextBackgroundA()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUNDA, back_str);
	OnKillfocusEditBackgroundA();
}

void CDAView::OnContextBackgroundB()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUNDB, back_str);
	OnKillfocusEditBackgroundB();
}

void CDAView::OnContextNormalize()
{
	// TODO: Add your command handler code here
	SetDlgItemText(IDC_EDIT_NORMALIZE, m_grid.m_ctxt_cell_str);
	if (m_grid.m_ctxt_cell_val != CSample::m_normalize_value)
	{
		CSample::m_normalize_value = m_grid.m_ctxt_cell_val;
		CDADoc* pDoc = (CDADoc*)GetDocument();
		UINT i;
		for (i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].RecalculateTransform();
		}
	}
	CButton* pNorm = (CButton*)GetDlgItem(IDC_CHECK_NORMALIZE);
	ASSERT(pNorm != NULL);
	pNorm->SetCheck(1);
	OnCheckNormalize();
}

BOOL CDAView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		bool post;
		UINT message;

		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (SCHasFocus(IDC_EDIT_BACKGROUNDA))
			{
				OnKillfocusEditBackgroundA();
				m_grid.SetFocus();
				post = false;
			}
			else if (SCHasFocus(IDC_EDIT_BACKGROUNDB))
			{
				OnKillfocusEditBackgroundB();
				m_grid.SetFocus();
				post = false;
			}
			else if (SCHasFocus(IDC_EDIT_NORMALIZE))
			{
				OnKillfocusEditNormalize();
				m_grid.SetFocus();
				post = false;
			}
			else if (EditsActive())
			{
				post = false;
			}
			else
			{
				post = true;
				message = ID_MEASURE_START;
			}
			break;

		case VK_SPACE:
			if (EditsActive())
			{
				post = false;
			}
			else
			{
				post = true;
				message = ID_MEASURE_START;
			}
			break;

		case VK_DELETE:
			if (EditsActive())
			{
				post = false;
			}
			else
			{
				post = true;
				message = ID_MEASURE_DELETE;
			}
			break;

		default:
			post = false;
			break;
		}

		if (post)
		{
			PostMessage(WM_COMMAND, message, 0);
			return TRUE;
		}
	}

	return CGridView::PreTranslateMessage(pMsg);
}

bool CDAView::EditsActive()
{
	bool edit_active = false;

	// Check for grid edits
	ROWCOL row, col;
	if (m_grid.GetCurrentCell(&row, &col) && (col == 1))
	{
		CGXControl* pControl = m_grid.GetControl(row, col);
		if (pControl)
		{
			if (pControl->IsActive())
			{
				edit_active = true;
			}
		}
	}

	// Check for normalize and background edits
	CWnd* focus_wnd = CWnd::GetFocus();
	if (focus_wnd)
	{
		int ctrl_id = focus_wnd->GetDlgCtrlID();
		if ((ctrl_id == IDC_EDIT_NORMALIZE) ||
			(ctrl_id == IDC_EDIT_BACKGROUNDA) ||
			(ctrl_id == IDC_EDIT_BACKGROUNDB))
		{
			edit_active = true;
		}
	}

	return edit_active;
}

void CDAView::OnDestroy()
{
	CGridView::OnDestroy();

	// TODO: Add your message handler code here
	if (m_grid.GetParam())
	{
		m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	}
}

void CDAView::SendToExcel()
{
	OnExcel();
}
