// MKView.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "General.h"
#include "MKView.h"
#include "MKHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKView

IMPLEMENT_DYNCREATE(CMKView, CGridView)

CMKView::CMKView()
	: CGridView(CMKView::IDD), hilite_row(0xFFFFFFFF), hilite_col(0xFFFFFFFF),
	m_nominal(true)
{
	//{{AFX_DATA_INIT(CMKView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMKView::~CMKView()
{
}

BOOL CMKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CMKView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMKView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMKView, CGridView)
	//{{AFX_MSG_MAP(CMKView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE_AS_TEXT, OnFileSaveAsText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_EN_KILLFOCUS(IDC_EDIT_BACKGROUND, OnKillfocusEditBackground)
	ON_COMMAND(ID_CONTEXT_BACKGROUND, OnContextBackground)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_NOMINAL, OnRadioNominal)
	ON_BN_CLICKED(IDC_RADIO_ACTUAL, OnRadioActual)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGridView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMKView diagnostics

#ifdef _DEBUG
void CMKView::AssertValid() const
{
	CGridView::AssertValid();
}

void CMKView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CMKDoc* CMKView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMKDoc)));
	return (CMKDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMKView drawing

void CMKView::OnDraw(CDC* pDC)
{
	CMKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMKView printing

BOOL CMKView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Set the print header
	CMKDoc* pDoc = GetDocument();
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
	hd_str.Format("Duration: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_intervaltime * pDoc->m_pps.m_numsamps));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background: %ld RLU/s", CSample::m_background);
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

void CMKView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	MKGetApp()->FB12Inhibit();
	//m_grid.UnhiliteCell(hilite_row, hilite_col);
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CMKView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	//m_grid.HiliteCell(hilite_row, hilite_col);
	MKGetApp()->FB12Uninhibit();
}

void CMKView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CMKView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMKView message handlers

void CMKView::OnInitialUpdate()
{
	m_grid.SubclassDlgItem(IDC_MKGRID, this);
	m_grid.Initialize();

	CGridView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	MyGridResize();

	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	// Set the display header information
	CString display_str;
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_RADIO_NOMINAL);
	ASSERT(pWnd != NULL);
	((CButton*)pWnd)->SetCheck(1);

	// Delay time
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.UseStartButton() ? 0 : pDoc->m_pps.m_delaytime));
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
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_intervaltime * pDoc->m_pps.m_nummeasurements));

	// Background
	pWnd = GetDlgItem(IDC_EDIT_BACKGROUND);
	ASSERT(pWnd != NULL);
	display_str.Format("%ld", CSample::m_background);
	pWnd->SetWindowText(display_str);
}

void CMKView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CMKView::MyGridResize()
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

void CMKView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Allow changes to the grid
	m_grid.GetParam()->SetLockReadOnly(FALSE);

	if ((lHint >= 0) || (pHint != NULL))
	{
		// TODO: Add your specialized code here and/or call the base class
		BOOL bOldLock = m_grid.LockUpdate(TRUE);

		// Get a pointer to the document
		CMKDoc* pDoc = (CMKDoc*)GetDocument();

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

			// Update all the measurements
			UINT meas_num;
			for (meas_num = 0; meas_num < pDoc->m_nummeas; meas_num++)
			{
				UpdateSample(meas_num);
			}
		}
		else if (pHint)
		{
			// Update only new sample
			UpdateSample(((CMKHint*)pHint)->m_meas);
		}
/*
		else if (lHint)
		{
			// update a single measurement
			UpdateSample(lHint);
		}
*/
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

void CMKView::HiliteCell()
{
	if (MKGetApp()->m_mode == CMKApp::APPMODE_RUN)
	{
		// Get a pointer to the document
		CMKDoc* pDoc = GetDocument();

		// Unhighlight the current cell
		m_grid.UnhiliteCell(hilite_row, hilite_col);

		// Indicate that nothing is highlighted
		hilite_row = 0xFFFFFFFF;
		hilite_col = 0xFFFFFFFF;

		// Highlight the correct cell
		if (pDoc->GetMode() != CMKDoc::MODE_FINISHED)
		{
			if (m_nominal)
			{
				// Calculate the hilite row and col
				hilite_row = pDoc->m_meas_num + 1;
			}
			else
			{
				hilite_row = 1 + (pDoc->m_meas_num * pDoc->m_numsamps) + pDoc->m_samp_num;
			}

			hilite_col = 2 + (pDoc->m_samp_num * 
				(((pDoc->m_numreps > 1) ? 4 : 1) + pDoc->m_numreps)) + pDoc->m_rep_num;

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

void CMKView::UpdateSample(UINT meas_num)
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	//meas_num--;

	CString double_str;
	int rep;

	if (m_nominal)
	{
		ROWCOL row = meas_num + 1;
		ROWCOL col = 1;

		// Measurement time
		m_grid.SetValueRange(CGXRange(row, col++),
			SCFormatDeciseconds(meas_num * pDoc->m_pps.m_intervaltime));

		int samp;
		for (samp = 0; samp < pDoc->m_samples.GetSize(); samp++)
		{
			CMeasurement* measurement = &pDoc->m_samples[samp].m_measurements[meas_num];

			int reps = measurement->GetNumReplicates();

			// Replicates
			if (reps > 0)
			{
				if (measurement->m_replicates.GetSize() > 1)
				{
					// Reps
					for (rep = 0; rep < measurement->m_replicates.GetSize(); rep++)
					{
						if (measurement->m_replicates[rep].m_used)
						{
							m_grid.SetValueRange(CGXRange(row, col++), measurement->m_replicates[rep].m_RLU);
						}
						else
						{
							m_grid.SetValueRange(CGXRange(row, col++), "");
						}
					}

					// Average
					double_str.Format("%.2f", measurement->m_average);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);

					// Precision
					if (measurement->m_precision_overflow)
					{
						m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
					}
					else
					{
						double_str.Format("%.2f", measurement->m_precision);
						m_grid.SetValueRange(CGXRange(row, col++), double_str);
					}

					// Net
					double_str.Format("%.2f", measurement->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);

					// Precision of net
					if (measurement->m_precision_net_overflow)
					{
						m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
					}
					else
					{
						double_str.Format("%.2f", measurement->m_precision_net);
						m_grid.SetValueRange(CGXRange(row, col++), double_str);
					}
				}
				else
				{
					// Rep 1
					m_grid.SetValueRange(CGXRange(row, col++), measurement->m_replicates[0].m_RLU);

					// Net
					double_str.Format("%.2f", measurement->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
			else
			{
				if (measurement->m_replicates.GetSize() > 1)
				{
					// Reps
					for (rep = 0; rep < measurement->m_replicates.GetSize(); rep++)
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
	}
	else
	{
		ROWCOL row = meas_num * pDoc->m_pps.m_numsamps + 1;
		ROWCOL col = 2;

		int samp;
		for (samp = 0; samp < pDoc->m_samples.GetSize(); samp++, row++)
		{
			CMeasurement* measurement = &pDoc->m_samples[samp].m_measurements[meas_num];

			// Measurement time
			m_grid.SetValueRange(CGXRange(row, 1),
				measurement->m_time_valid ?
					SCFormatDeciseconds(measurement->m_time) : "N/A");

			// Replicates
			int reps = measurement->GetNumReplicates();
			if (reps > 0)
			{
				if (measurement->m_replicates.GetSize() > 1)
				{
					// Reps
					for (rep = 0; rep < measurement->m_replicates.GetSize(); rep++)
					{
						if (measurement->m_replicates[rep].m_used)
						{
							m_grid.SetValueRange(CGXRange(row, col++), measurement->m_replicates[rep].m_RLU);
						}
						else
						{
							m_grid.SetValueRange(CGXRange(row, col++), "");
						}
					}

					// Average
					double_str.Format("%.2f", measurement->m_average);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);

					// Precision
					if (measurement->m_precision_overflow)
					{
						m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
					}
					else
					{
						double_str.Format("%.2f", measurement->m_precision);
						m_grid.SetValueRange(CGXRange(row, col++), double_str);
					}

					// Net
					double_str.Format("%.2f", measurement->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);

					// Precision of net
					if (measurement->m_precision_net_overflow)
					{
						m_grid.SetValueRange(CGXRange(row, col++), "Div by 0 err");
					}
					else
					{
						double_str.Format("%.2f", measurement->m_precision_net);
						m_grid.SetValueRange(CGXRange(row, col++), double_str);
					}
				}
				else
				{
					// Rep 1
					m_grid.SetValueRange(CGXRange(row, col++), measurement->m_replicates[0].m_RLU);

					// Net
					double_str.Format("%.2f", measurement->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
			else
			{
				if (measurement->m_replicates.GetSize() > 1)
				{
					// Reps
					for (rep = 0; rep < measurement->m_replicates.GetSize(); rep++)
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
	}
}

void CMKView::OnFileSaveAsText()
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

void CMKView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CMKView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}

void CMKView::OnExcel()
{
	// TODO: Add your command handler code here
	MKGetApp()->FB12Inhibit();

 	// Ensure that each views current cell is stored
	m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	CMKPPS* pps = &MKGetApp()->m_pps;

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

	MKGetApp()->FB12Uninhibit();
}

void CMKView::OnKillfocusEditBackground()
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
		CMKDoc* pDoc = (CMKDoc*)GetDocument();
		UINT i, j;
		for (i = 0; i < pDoc->m_numsamps; i++)
		{
			for (j = 0; j < pDoc->m_nummeas; j++)
			{
				pDoc->m_samples[i].m_measurements[j].Recalculate();
			}
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CMKView::OnContextBackground()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
	OnKillfocusEditBackground();
}

BOOL CMKView::PreTranslateMessage(MSG* pMsg)
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

bool CMKView::EditsActive()
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

void CMKView::OnDestroy()
{
	CGridView::OnDestroy();

	// TODO: Add your message handler code here
	if (m_grid.GetParam())
	{
		m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	}
}

void CMKView::OnRadioNominal() 
{
	// TODO: Add your control notification handler code here
	m_nominal = true;
	m_grid.AdjustGrid(m_nominal);
	OnUpdate(NULL, 0, NULL);
}

void CMKView::OnRadioActual() 
{
	// TODO: Add your control notification handler code here
	m_nominal = false;
	m_grid.AdjustGrid(m_nominal);
	OnUpdate(NULL, 0, NULL);
}

void CMKView::SendToExcel()
{
	OnExcel();
}
