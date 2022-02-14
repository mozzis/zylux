// CAView.cpp : implementation file
//

#include "stdafx.h"
#include "CA.h"
#include "CAView.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAView

IMPLEMENT_DYNCREATE(CCAView, CGridView)

CCAView::CCAView()
	: CGridView(CCAView::IDD), hilite_row(0xFFFFFFFF), hilite_col(0xFFFFFFFF)
{
	//{{AFX_DATA_INIT(CCAView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCAView::~CCAView()
{
}

BOOL CCAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CCAView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCAView, CGridView)
	//{{AFX_MSG_MAP(CCAView)
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
// CCAView diagnostics

#ifdef _DEBUG
void CCAView::AssertValid() const
{
	CGridView::AssertValid();
}

void CCAView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CCADoc* CCAView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCADoc)));
	return (CCADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCAView drawing

void CCAView::OnDraw(CDC* pDC)
{
	CCADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCAView printing

BOOL CCAView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// Set the print header
	CCADoc* pDoc = (CCADoc *)GetDocument();
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
	hd_str.Format("Measurement time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_meastime));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Low Cut-off: %ld", CSample::m_lowcutoff);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("High Cut-off: %ld", CSample::m_highcutoff);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background: %ld RLU/s", CSample::m_background);
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);


	// File title
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

void CCAView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	CAGetApp()->FB12Inhibit();
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CCAView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	CAGetApp()->FB12Uninhibit();
}

void CCAView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CCAView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCAView message handlers

void CCAView::OnInitialUpdate()
{

	// TODO: Add your specialized code here and/or call the base class
	m_grid.SubclassDlgItem(IDC_CAGRID, this);
	m_grid.Initialize();

	CGridView::OnInitialUpdate();
	MyGridResize();

	CCADoc* pDoc = (CCADoc*)GetDocument();

	CWnd* pWnd;

	// Delay Time
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.UseStartButton() ? 0 : pDoc->m_pps.m_delaytime));
	pWnd->EnableWindow(pDoc->m_pps.UseStartButton() ? FALSE : TRUE);

	// Measure Time
	pWnd = GetDlgItem(IDC_EDIT_MEASTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_pps.m_meastime));

	CString display_str;

	if (CAGetApp()->m_mode == CProtocolApp::APPMODE_VIEW)
	{
		//Low Cut-off
		pWnd = GetDlgItem(IDC_EDIT_LOWCUTOFF);
		ASSERT(pWnd != NULL);
		display_str.Format("%ld", CSample::m_lowcutoff);
		pWnd->SetWindowText(display_str);
		//High Cut-off
		pWnd = GetDlgItem(IDC_EDIT_HIGHCUTOFF);
		ASSERT(pWnd != NULL);
		display_str.Format("%ld", CSample::m_highcutoff);
		pWnd->SetWindowText(display_str);
		// Invalid Assay Message
		pWnd = GetDlgItem(IDC_STATIC_INVALIDMSG);
		ASSERT(pWnd != NULL);
		if (!pDoc->m_validassay)
			pWnd->ShowWindow(SW_SHOW);
		else
			pWnd->ShowWindow(SW_HIDE);

		// Set sample names to Static Controls (read-only)
		m_grid.SetStyleRange(CGXRange(1, 1, m_grid.GetRowCount(), 1), CGXStyle()
			.SetControl(GX_IDS_CTRL_STATIC));

	}


}

void CCAView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CCAView::MyGridResize()
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

void CCAView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

	if (lHint >= 0)
	{
		// TODO: Add your specialized code here and/or call the base class
		BOOL bOldLock = m_grid.LockUpdate(TRUE);

		CCADoc* pDoc = (CCADoc*)GetDocument();
		m_grid.GetParam()->SetLockReadOnly(FALSE);

		CWnd *pWnd;

		if (lHint == 0)
		{
 			// Ensure that each views current cell is stored
			m_grid.TransferCurrentCell(TRUE, GX_INVALIDATE, FALSE);


			// Date
			SetDlgItemText(IDC_EDIT_DATE, pDoc->m_datetime.Format("%x"));

			// Time
			SetDlgItemText(IDC_EDIT_TIME, pDoc->m_datetime.Format("%X"));

			UINT sample_num;

			for (sample_num = 1; sample_num <= pDoc->m_numsamples; sample_num++)
			{
				UpdateSample(sample_num);
			}

		}
		else
		{
			UpdateSample(lHint);
			if ((pDoc->m_pps.UseBackground()) && (lHint == 1))
			{
				CString back_str;
				
				CSample::m_background = (long)SCNearestInt(pDoc->m_samples[0].m_average);
				back_str.Format("%ld", CSample::m_background);
				SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
			}

		}

		CString display_str;
		
		// Background
		display_str.Format("%ld", CSample::m_background);
		SetDlgItemText(IDC_EDIT_BACKGROUND, display_str);

		// Low Cut-off
		display_str.Format("%ld", CSample::m_lowcutoff);
		SetDlgItemText(IDC_EDIT_LOWCUTOFF, display_str);

		//High Cut-off
		display_str.Format("%ld", CSample::m_highcutoff);
		SetDlgItemText(IDC_EDIT_HIGHCUTOFF, display_str);

		// Invalid Assay Message
		pWnd = GetDlgItem(IDC_STATIC_INVALIDMSG);
		ASSERT(pWnd != NULL);
		if (pDoc->m_sample_num > pDoc->m_possample)
		{
			if (!pDoc->m_validassay)
				pWnd->ShowWindow(SW_SHOW);
			else
				pWnd->ShowWindow(SW_HIDE);
		}


		// Fit these columns to the text I've put in them
		m_grid.ResizeColWidthsToFit(
			CGXRange(0, 0, m_grid.GetRowCount(), m_grid.GetColCount()));

		HiliteCell(lHint);

		m_grid.GetParam()->SetLockReadOnly(TRUE);
		m_grid.LockUpdate(bOldLock);
		m_grid.Redraw();
	}
}

void CCAView::OnFileSaveAsText()
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
	
	dlgFile.m_ofn.lpstrTitle = "Save As Text";

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


void CCAView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CCAView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}


void CCAView::OnExcel()
{
	// TODO: Add your command handler code here
	CAGetApp()->FB12Inhibit();

 	// Ensure that each views current cell is stored
	m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	CCAPPS* pps = &CAGetApp()->m_pps;

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

	CAGetApp()->FB12Uninhibit();
}


void CCAView::UpdateSample(UINT sample_num)
{

	CCADoc* pDoc = (CCADoc*)GetDocument();
	if (pDoc != NULL)
	{
		ROWCOL row, col;
		row = sample_num;
		col = 1;

		UINT num_reps, i;

		CSample *pSample = &(pDoc->m_samples[row-1]);

		// Sample name
		if ((pDoc->m_pps.UseBackground()) && (row == 1))
		{
			m_grid.SetValueRange(CGXRange(row, col++), "Background");
			num_reps = pDoc->m_pps.m_numreps;
		}
		else
		{
			if ((pDoc->m_negsample > 0) && (row == pDoc->m_negsample))
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Negative Control");
				num_reps = pDoc->m_pps.m_numnegreps;
			}
			else if((pDoc->m_possample > 0) && (row == pDoc->m_possample))
			{
				m_grid.SetValueRange(CGXRange(row, col++), "Positive Control");
				num_reps = pDoc->m_pps.m_numposreps;
			}
			else
			{
				UINT offset = 1;
				if (pDoc->m_pps.UseBackground())
					offset++;
				if(pDoc->m_negsample > 0)
					offset++;
				if(pDoc->m_possample > 0)
					offset++;

				m_grid.SetValueRange(CGXRange(row, col++),
					LPCTSTR(pDoc->m_pps.m_samplelist[row - offset]));
				num_reps = pDoc->m_pps.m_numreps;
			}
		}


		// RLU values for reps
		for (i=0; i < num_reps; i++)
		{
			if (pSample->m_replicates[i].m_used)
				m_grid.SetValueRange(CGXRange(row, col++),
					pSample->m_replicates[i].m_RLU);
			else
				m_grid.SetValueRange(CGXRange(row, col++), "");
		}

		CString double_str;
		col = pDoc->m_maxreps + 2;

		if (pSample->NumReplicatesUsed() > 0)
		{
			// Result
			switch(pSample->m_result) {
				case CSample::RESULT_NONE:
					m_grid.SetValueRange(CGXRange(row, col++), "");
					break;
				case CSample::RESULT_BKGD:
					m_grid.SetValueRange(CGXRange(row, col++), "BKGD");
					break;
				case CSample::RESULT_NEGSTD:
					m_grid.SetValueRange(CGXRange(row, col++), "NEG CTRL");
					break;
				case CSample::RESULT_POSCTRL:
					m_grid.SetValueRange(CGXRange(row, col++), "POS CTRL");
					break;
				case CSample::RESULT_NEG:
						m_grid.SetValueRange(CGXRange(row, col++),
							((pDoc->m_validassay) ? pDoc->m_pps.m_negresult : "N/A"));
					break;
				case CSample::RESULT_POS:
						m_grid.SetValueRange(CGXRange(row, col++),
							((pDoc->m_validassay) ? pDoc->m_pps.m_posresult : "N/A"));
					break;
				case CSample::RESULT_EQUIV:
						m_grid.SetValueRange(CGXRange(row, col++),
							((pDoc->m_validassay) ? pDoc->m_pps.m_equivresult : "N/A"));
					break;
			}


			// Average, Net, etc.
			if (num_reps > 1)
			{
				// Average
				double_str.Format("%.2f", pSample->m_average);
				m_grid.SetValueRange(CGXRange(row, col++), double_str);

				// Precision
				if (!pSample->m_precision_overflow)
				{
					double_str.Format("%.2f", pSample->m_precision);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
				else
				{
					m_grid.SetValueRange(CGXRange(row, col++),
						"Div by zero");
				}

				// Net
				if ((row == 1) && (pDoc->m_pps.UseBackground()))
				{
					m_grid.SetValueRange(CGXRange(row, col++), "N/A");
				}
				else
				{
					double_str.Format("%.2f", pSample->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}

				// Precision of Net
				if ((row == 1) && (pDoc->m_pps.UseBackground()))
				{
					// if this is the background row, put N/A
					if ((row == 1) && (pDoc->m_pps.UseBackground()))
						m_grid.SetValueRange(CGXRange(row, col++), "N/A");
				}
				else if (!pSample->m_netprecision_overflow)
				{
					double_str.Format("%.2f", pSample->m_precision_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
				else
				{
					m_grid.SetValueRange(CGXRange(row, col++), "Div by zero");
				}
			}
			else // just one rep, so just update the Net
			{
				// Net
				if ((row == 1) && (pDoc->m_pps.UseBackground()))
				{
					m_grid.SetValueRange(CGXRange(row, col++), "N/A");
				}
				else
				{
					double_str.Format("%.2f", pSample->m_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
			}
		}
		else
		{
			// Blank out all the columns if all reps are unused
			// Results
			m_grid.SetValueRange(CGXRange(row, col++), "");
			if (num_reps > 1)
			{
				// Average
				m_grid.SetValueRange(CGXRange(row, col++), "");
				// Precision
				m_grid.SetValueRange(CGXRange(row, col++), "");
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "");
				// Precision of Net
				m_grid.SetValueRange(CGXRange(row, col++), "");
			}
			else
			{
				// Net
				m_grid.SetValueRange(CGXRange(row, col++), "");
			}
		}
		if (pDoc->m_last_replicate != 0)
			m_grid.ScrollCellInView(row, pDoc->m_last_replicate + 1);

	}

}

void CCAView::OnKillfocusEditBackground()
{
	// TODO: Add your control notification handler code here
	CString background_str;
	GetDlgItemText(IDC_EDIT_BACKGROUND, background_str);
	long background_val = atol(background_str);
	if (background_val != CSample::m_background)
	{
		CSample::m_background = background_val;
		CCADoc* pDoc = (CCADoc*)GetDocument();
		int i;
		for (i = 0; i < pDoc->m_samples.GetSize(); i++)
		{
			pDoc->m_samples[i].Recalculate();
			// After Neg and Pos controls re-calculated, re-calc
			// the cutoffs for the rest of the analyte samples
			if (pDoc->m_possample > 0) // There is a pos. control
			{
				if ((UINT)i == (pDoc->m_possample - 1))
					pDoc->RecalcCutoffs();
			}
			else if (pDoc->m_negsample > 0)  // No pos cntrl, but there is a neg. cntrl
			{
				if ((UINT)i == (pDoc->m_negsample - 1))
					pDoc->RecalcCutoffs();
			}
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}


void CCAView::OnContextBackground()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
	OnKillfocusEditBackground();
}


void CCAView::HiliteCell(UINT current_row)
{
	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
		CCADoc *pDoc = CAGetDoc();

		// Unhighlight the current cell
		m_grid.UnhiliteCell(hilite_row, hilite_col);

		// Reset the highlight row, col variables
		hilite_row = 0xFFFFFFFF;
		hilite_col = 0xFFFFFFFF;

		// Highlight the correct cell
		// Calculate the hilite row and col
		if (pDoc != NULL)
		{
			if (pDoc->MoreToMeasure())
			{
				hilite_col = pDoc->m_replicate_num; //(ROWCOL)hc;
				hilite_row = pDoc->m_sample_num; //(ROWCOL)hr;
			}
			else
			{
				hilite_col = 0;
				hilite_row = 0;
			}
		}
		else
		{
			hilite_row = 1;
			hilite_col = 1;
		}
		hilite_col = hilite_col + 1;


		if ((hilite_row > 0) && (hilite_col > 0))
		{
			m_grid.HiliteCell(hilite_row, hilite_col);


			// Scroll to the new cell
			m_grid.ScrollCellInView(hilite_row, hilite_col);
		}
	}
}

void CCAView::OnDestroy()
{
	CGridView::OnDestroy();

	// TODO: Add your message handler code here

	if (m_grid.GetParam())
	{
 		// Ensure that the current cell can be stored
 		m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	}

}


BOOL CCAView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//if (pMsg->message == WM_CHAR)
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

bool CCAView::EditsActive()
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
		if (ctrl_id == IDC_EDIT_BACKGROUND)
		{
			edit_active = true;
		}
	}

	return edit_active;
}

void CCAView::SendToExcel()
{
	OnExcel();
}
