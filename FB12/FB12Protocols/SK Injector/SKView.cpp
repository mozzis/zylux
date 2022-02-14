// SKView.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "General.h"
#include "SKView.h"
#include "SKHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKView

IMPLEMENT_DYNCREATE(CSKView, CGridView)

CSKView::CSKView()
	: CGridView(CSKView::IDD), hilite_row(0xFFFFFFFF), hilite_col(0xFFFFFFFF), m_showinject(false)
{
	//{{AFX_DATA_INIT(CSKView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSKView::~CSKView()
{
}

BOOL CSKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CSKView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSKView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSKView, CGridView)
	//{{AFX_MSG_MAP(CSKView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE_AS_TEXT, OnFileSaveAsText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_EN_KILLFOCUS(IDC_EDIT_BACKGROUND, OnKillfocusEditBackground)
	ON_COMMAND(ID_CONTEXT_BACKGROUND, OnContextBackground)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGridView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKView diagnostics

#ifdef _DEBUG
void CSKView::AssertValid() const
{
	CGridView::AssertValid();
}

void CSKView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CSKDoc* CSKView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSKDoc)));
	return (CSKDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSKView drawing

void CSKView::OnDraw(CDC* pDC)
{
	CSKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSKView printing

BOOL CSKView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Set the print header
	CSKDoc* pDoc = GetDocument();
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
	hd_str.Format("Delay time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_delaytime));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Sampling time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_meastime));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Interval time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_intervaltime));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Duration: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_intervaltime * pDoc->m_pps.m_numsamples));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background: %ld RLU/s", CSample::m_background);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	//hd_str.Format("Background: %ld RLU/s", CSample::m_background);
	if ((SKGetApp()->m_skoptions.m_num_injectors > 0) && ((SKGetApp()->m_pps.GetTotalInjectVolume(1) > 0) ||
		(SKGetApp()->m_pps.GetTotalInjectVolume(2) > 0)))
	{
		pProp->GetDataHeader().StoreStyleRowCol(1, 2, CGXStyle().SetHorizontalAlignment(DT_CENTER)
			.SetValue("Injections:"), gxCopy);
		pProp->GetDataHeader().StoreStyleRowCol(1, 3, CGXStyle().SetHorizontalAlignment(DT_CENTER)
			.SetValue(""), gxCopy);
		pProp->GetDataHeader().StoreStyleRowCol(2, 2, CGXStyle().SetHorizontalAlignment(DT_LEFT)
			.SetValue("Injector  Times"), gxCopy);
		pProp->GetDataHeader().StoreStyleRowCol(2, 3, CGXStyle().SetHorizontalAlignment(DT_LEFT)
			.SetValue("Volumes"), gxCopy);
		int oth_row = 2;
		for (int i=0; i < pDoc->m_pps.MAX_INJECTIONS; i++)
		{
			if (pDoc->m_pps.m_injections[i].m_used > 0)
			{
				hd_str.Format("%d     %s", pDoc->m_pps.m_injections[i].m_used, SCFormatDeciseconds(pDoc->m_pps.m_injections[i].m_time));
				pProp->GetDataHeader().StoreStyleRowCol(++oth_row, 2, CGXStyle().SetHorizontalAlignment(DT_LEFT)
					.SetValue(hd_str), gxCopy);

				hd_str.Format("%d uL", pDoc->m_pps.m_injections[i].m_volume);
				pProp->GetDataHeader().StoreStyleRowCol(oth_row, 3, CGXStyle().SetHorizontalAlignment(DT_LEFT)
					.SetValue(hd_str), gxCopy);
			}
		}
	}
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

void CSKView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	SKGetApp()->FB12Inhibit();
	//m_grid.UnhiliteCell(hilite_row, hilite_col);
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CSKView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	//m_grid.HiliteCell(hilite_row, hilite_col);
	SKGetApp()->FB12Uninhibit();
}

void CSKView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CSKView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSKView message handlers

void CSKView::OnInitialUpdate()
{
	m_grid.SubclassDlgItem(IDC_SKGRID, this);
	m_grid.Initialize();

	CGridView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	MyGridResize();

	CSKDoc* pDoc = (CSKDoc*)GetDocument();

	// Set the display header information
	CString display_str;
	CWnd* pWnd;

	// Delay time
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.UseStartButton() ? 0 :pDoc->m_pps.m_delaytime));
	pWnd->EnableWindow(pDoc->m_pps.UseStartButton() ? FALSE : TRUE);

	// Meas time
	pWnd = GetDlgItem(IDC_EDIT_MEASTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_meastime));

	// Interval time
	pWnd = GetDlgItem(IDC_EDIT_INTERVALTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_intervaltime));

	// Duration
	pWnd = GetDlgItem(IDC_EDIT_DURATIONTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_intervaltime * pDoc->m_pps.m_numsamples));

	// Background
	pWnd = GetDlgItem(IDC_EDIT_BACKGROUND);
	ASSERT(pWnd != NULL);
	display_str.Format("%ld", CSample::m_background);
	pWnd->SetWindowText(display_str);

	// Injections
	CListBox *pInject = (CListBox *)GetDlgItem(IDC_LIST_INJECTS);
	ASSERT(pInject != NULL);

	if ((SKGetApp()->m_skoptions.m_num_injectors > 0) && 
		((SKGetApp()->m_pps.GetTotalInjectVolume(1) + SKGetApp()->m_pps.GetTotalInjectVolume(2)) > 0))
	{
		InitInjectList(pInject);
		if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
			m_showinject = true;
		else
			m_showinject = false;
	}
	else
	{
		pInject->EnableWindow(FALSE);
		m_showinject = false;
	}


}				

void CSKView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CSKView::MyGridResize()
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

void CSKView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Allow changes to the grid
	m_grid.GetParam()->SetLockReadOnly(FALSE);

	if ((lHint >= 0) || (pHint != NULL))
	{
		// TODO: Add your specialized code here and/or call the base class
		BOOL bOldLock = m_grid.LockUpdate(TRUE);

		// Get a pointer to the document
		CSKDoc* pDoc = (CSKDoc*)GetDocument();

		if (m_showinject)
		{
			CListBox *pInject = (CListBox *)GetDlgItem(IDC_LIST_INJECTS);
			if (pDoc->m_nextinjection >= 0)
			{
				pInject->SetCurSel(pDoc->m_nextinjection);
			}
			else
			{
				pInject->SetCurSel(-1);
			}
		}


		if ((lHint == 0) && (pHint == NULL))
		{
 			// Ensure that each views current cell is stored
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

			// Update all the samples
			UINT sample_num;
			for (sample_num = 1; sample_num <= pDoc->m_numsamples; sample_num++)
			{
				UpdateSample(sample_num);
			}
		}
		else if (pHint)
		{
			// Update only new samples
			UINT sample_num;
			for (sample_num = ((CSKHint*)pHint)->m_first;
				sample_num <= ((CSKHint*)pHint)->m_last;
				sample_num++)
			{
				UpdateSample(sample_num);
			}
			if ((((CSKHint*)pHint)->m_first <= 1) &&
				(((CSKHint*)pHint)->m_last >= 1) &&
				pDoc->m_pps.UseBackground())
			{
				// sample 1 was involved in the update and background is in use

				// We update the backgrounds and corresponding edit boxes
				CString back_str;

				// get averaged background, rounding to nearest integer
				CSample::m_background = (long)SCNearestInt(pDoc->m_samples[0].m_average);
				back_str.Format("%ld", CSample::m_background);
				SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
			}
		}

		// Fit these columns to the text I've put in them
		//m_grid.ResizeColWidthsToFit(
		//	CGXRange(0, 0, m_grid.GetRowCount(), m_grid.GetColCount()));

		m_grid.LockUpdate(bOldLock);
		m_grid.Redraw();
	}

	HiliteCell();

	// Disallow changes to the grid
	m_grid.GetParam()->SetLockReadOnly(TRUE);
}

void CSKView::HiliteCell()
{
	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		// Get a pointer to the document
		CSKDoc* pDoc = GetDocument();

		// Unhighlight the current cell
		m_grid.UnhiliteCell(hilite_row, hilite_col);

		// Indicate that nothing is highlighted
		hilite_row = 0xFFFFFFFF;
		hilite_col = 0xFFFFFFFF;

		// Highlight the correct cell
		if (pDoc->m_replicate_num < pDoc->m_pps.m_numreplicates)
		{
			// Calculate the hilite row and col
			hilite_row = pDoc->m_sample_num + 1;
			hilite_col = 2 + pDoc->m_replicate_num;
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

void CSKView::UpdateSample(UINT sample_num)
{
	CSKDoc* pDoc = (CSKDoc*)GetDocument();

	ROWCOL row = sample_num;
	sample_num--;

	CSample* sample = &pDoc->m_samples[sample_num];

	ROWCOL col;

	CString double_str;

	int reps = sample->GetNumReplicates();

	col = 1;

	// Sample time
	if ((sample_num == 0) && pDoc->m_pps.UseBackground())
	{
		m_grid.SetValueRange(CGXRange(row, col++), "Background");
	}
	else
	{
		UINT time_num = sample_num - (pDoc->m_pps.UseBackground() ? 1 : 0);
		m_grid.SetValueRange(CGXRange(row, col++), SCFormatDeciseconds(time_num * pDoc->m_pps.m_intervaltime));
	}

	int rep;

	// Replicates
	if (reps > 0)
	{
		if (sample->m_replicates.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates.GetSize(); rep++)
			{
				if (sample->m_replicates[rep].m_used)
				{
					m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates[rep].m_RLU);
				}
				else
				{
					m_grid.SetValueRange(CGXRange(row, col++), "");
				}
			}

			// Average
			double_str.Format("%.2f", sample->m_average);
			m_grid.SetValueRange(CGXRange(row, col++), double_str);

			// Precision
			if (sample->m_precision_overflow)
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
			}
			else
			{
				double_str.Format("%.2f", sample->m_precision);
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
				double_str.Format("%.2f", sample->m_net);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);

				// Precision of net
				if (sample->m_precision_net_overflow)
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
				}
				else
				{
					double_str.Format("%.2f", sample->m_precision_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
		}
		else
		{
			// Rep 1
			m_grid.SetValueRange(CGXRange(row, col++), sample->m_replicates[0].m_RLU);

			// If background, do something different
			if (pDoc->m_pps.UseBackground() && (sample_num == 0))
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "N/A");
			}
			else
			{
				// Net
				double_str.Format("%.2f", sample->m_net);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);
			}
		}
	}
	else
	{
		if (sample->m_replicates.GetSize() > 1)
		{
			// Reps
			for (rep = 0; rep < sample->m_replicates.GetSize(); rep++)
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

void CSKView::OnFileSaveAsText()
{
	// TODO: Add your command handler code here
	ProtGetApp()->FB12Inhibit();

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

	ProtGetApp()->FB12Uninhibit();
}

void CSKView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CSKView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}

void CSKView::OnExcel()
{
	// TODO: Add your command handler code here
	SKGetApp()->FB12Inhibit();

 	// Ensure that each views current cell is stored
	m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	CSKPPS* pps = &SKGetApp()->m_pps;

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

	SKGetApp()->FB12Uninhibit();
}

void CSKView::OnKillfocusEditBackground()
{
	// TODO: Add your control notification handler code here
	CEdit* wnd = (CEdit*)GetDlgItem(IDC_EDIT_BACKGROUND);
	ASSERT(wnd != NULL);

	CString background_str;
	DWORD pos;
	pos = wnd->GetSel();
	wnd->GetWindowText(background_str);
	long background_val = (long)SCNearestInt(atof(background_str));
	background_str.Format("%ld", background_val);
	wnd->SetWindowText(background_str);
	wnd->SetSel(pos);

	if (background_val != CSample::m_background)
	{
		CSample::m_background = background_val;
		CSKDoc* pDoc = (CSKDoc*)GetDocument();
		UINT i;
		for (i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].Recalculate();
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CSKView::OnContextBackground()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
	OnKillfocusEditBackground();
}

BOOL CSKView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		bool post;
		UINT message;

		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (SCHasFocus(IDC_EDIT_BACKGROUND))
			{
				OnKillfocusEditBackground();
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
/*
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
*/
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

bool CSKView::EditsActive()
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

	// Check for background edits
	CWnd* focus_wnd = CWnd::GetFocus();
	if (focus_wnd)
	{
		int ctrl_id = focus_wnd->GetDlgCtrlID();
		if (ctrl_id == IDC_EDIT_BACKGROUND)
		{
			edit_active = true;
		}
	}

	return edit_active;
}

void CSKView::OnDestroy()
{
	CGridView::OnDestroy();

	// TODO: Add your message handler code here
	if (m_grid.GetParam())
	{
		m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	}
}

void CSKView::SendToExcel()
{
	OnExcel();
}

void CSKView::InitInjectList(CListBox *pList)
{
	CString display_str;
	CRect rectList;
	CSKDoc* pDoc = (CSKDoc*)GetDocument();

	pList->GetWindowRect(&rectList);
	// measure the dialog box and make a tabstop smack-dab in the middle of it.
	// this isn't as easy as it looks because CListBox::SetTabStops() expects stops
	// to be in dialog units.  Dialog units are based on the font in the dailog,
	// though, so we need to do the conversion.  If you're dialog uses the system
	// font, you can do this by using ::GetDialogMetrics().  Since we're not,
	// we need to do the measurement ourselves.

	int nTabStop;

	CDC* dc = GetDC();
	CRect size = rectList;
	CFont* pOldFont;

	// figure out what font the box has, and select it

	pOldFont = dc->SelectObject(GetFont());

	// accurately measure the average width of a character

  	dc->DrawText(_T("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"), -1, &size,
  		DT_SINGLELINE | DT_NOCLIP | DT_CALCRECT);

	//  find the tab stop, being careful with rounding

	nTabStop = ((rectList.Width()*4) / ((25+size.Width())/52)) /3;
	
	dc->SelectObject(pOldFont);
	ReleaseDC(dc);

	pList->SetTabStops(1, &nTabStop);

	int i;
	for (i=0; i < pDoc->m_pps.MAX_INJECTIONS; i++)
	{
		if (pDoc->m_pps.m_injections[i].m_used)
		{
			display_str.Format("%d\t%s\t%d", pDoc->m_pps.m_injections[i].m_used, 
								SCFormatDeciseconds(pDoc->m_pps.m_injections[i].m_time),
								pDoc->m_pps.m_injections[i].m_volume);
			pList->AddString(display_str);
		}
	}
}

