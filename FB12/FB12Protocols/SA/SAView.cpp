// SAView.cpp : implementation file
//

#include "stdafx.h"
#include "SA.h"
#include "SAView.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSAView

IMPLEMENT_DYNCREATE(CSAView, CGridView)

CSAView::CSAView()
	: CGridView(CSAView::IDD), hilite_row(0xFFFFFFFF), hilite_col(0xFFFFFFFF)
{
	//{{AFX_DATA_INIT(CSAView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSAView::~CSAView()
{
}

BOOL CSAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CSAView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSAView, CGridView)
	//{{AFX_MSG_MAP(CSAView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE_AS_TEXT, OnFileSaveAsText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_ADDREP, OnAddRep)
	ON_BN_CLICKED(IDC_ADDSAMP, OnAddSamp)
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
// CSAView diagnostics

#ifdef _DEBUG
void CSAView::AssertValid() const
{
	CGridView::AssertValid();
}

void CSAView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CSADoc* CSAView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSADoc)));
	return (CSADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSAView drawing

void CSAView::OnDraw(CDC* pDC)
{
	CSADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSAView printing

BOOL CSAView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// Set the print header
	CSADoc* pDoc = (CSADoc *)GetDocument();
	CGXProperties* pProp = m_grid.GetParam()->GetProperties();
	pProp->SetCenterHorizontal(FALSE);
	CString hd_str;
	hd_str.Format("Protocol name: %s", SCGetFileTitle(pDoc->m_pps.m_protocolname));
	pProp->GetDataHeader().StoreStyleRowCol(1, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Date: %s", pDoc->m_datetime.Format("%x"));
	pProp->GetDataHeader().StoreStyleRowCol(2, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Time: %s", pDoc->m_datetime.Format("%X"));
	pProp->GetDataHeader().StoreStyleRowCol(3, 1, CGXStyle().SetValue(hd_str), gxCopy);

	hd_str.Format("Delay time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_delaytime));
	pProp->GetDataHeader().StoreStyleRowCol(4, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Measurement time: %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_pps.m_meastime));
	pProp->GetDataHeader().StoreStyleRowCol(5, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Background: %ld RLU/s", CSample::m_background);
	pProp->GetDataHeader().StoreStyleRowCol(6, 1, CGXStyle().SetValue(hd_str), gxCopy);


	// File title
	pProp->GetDataFooter().StoreStyleRowCol(1, 2,
		CGXStyle().SetValue(GetDocument()->GetTitle()), gxCopy);

	// Set header and footer to 1 inch from edge
	pProp->SetDistances(72, 72);

	// Set main margins to left and right 1" and
	// top and bottom just below the header and above the footer
	int font_height = m_grid.GetFontHeight();
	pProp->SetMargins(72 + font_height * 6, 72, 72 + font_height, 72);

	pInfo->SetMaxPage(0xffff);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSAView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	SAGetApp()->FB12Inhibit();
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CSAView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	SAGetApp()->FB12Uninhibit();
}

void CSAView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CSAView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSAView message handlers

void CSAView::OnInitialUpdate()
{

	// TODO: Add your specialized code here and/or call the base class
	m_grid.SubclassDlgItem(IDC_SAGRID, this);

	m_grid.Initialize();
	CGridView::OnInitialUpdate();

	MyGridResize();

	CButton* pAddRep = (CButton*) GetDlgItem(IDC_ADDREP);
	CButton* pAddSamp = (CButton*) GetDlgItem(IDC_ADDSAMP);
	ASSERT((pAddRep != NULL) && (pAddSamp != NULL));

	CSADoc* pDoc = (CSADoc*)GetDocument();

	if ((pAddRep != NULL) && (!pDoc->m_pps.IsFlexibleNumReps()))
	{
		pAddRep->ShowWindow(SW_HIDE);
	}

	if ((pAddSamp != NULL) && (!pDoc->m_pps.IsFlexibleNumSamps()))
	{
		pAddSamp->ShowWindow(SW_HIDE);
	}

	if (SAGetApp()->m_mode != CSAApp::APPMODE_RUN)
	{
		pAddSamp->ShowWindow(SW_HIDE);
		pAddRep->ShowWindow(SW_HIDE);

		// Set sample names to Static Controls (read-only)
		m_grid.SetStyleRange(CGXRange(1, 1, m_grid.GetRowCount(), 1), CGXStyle()
			.SetControl(GX_IDS_CTRL_STATIC));
	}

	//CString display_str;
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


}

void CSAView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CSAView::MyGridResize()
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

// if lHint
//    == any value  updates AddRep and AddSamp buttons
//    == -1         no update here (updates the kinetics view only)
//    == -2         re-initialize grid (when "new" document chosen)
//    <= -3         enable/disable rep and samp buttons
//    == 0          update all
//    >  0          update a specific grid row

void CSAView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CSADoc* pDoc = (CSADoc*)GetDocument();

	CWnd *pAddRep, *pAddSamp;
	pAddRep = GetDlgItem(IDC_ADDREP);
	pAddSamp = GetDlgItem(IDC_ADDSAMP);
	ASSERT((pAddRep != NULL) && (pAddSamp != NULL));
	pAddRep->EnableWindow((pDoc->GetMode() != pDoc->MODE_MEASURING));
	pAddSamp->EnableWindow((pDoc->GetMode() != pDoc->MODE_MEASURING));

	if (lHint >= 0)
	{
		// TODO: Add your specialized code here and/or call the base class
		BOOL bOldLock = m_grid.LockUpdate(TRUE);

		m_grid.GetParam()->SetLockReadOnly(FALSE);

		if (lHint == 0)
		{
 			// Ensure that each views current cell is stored
			m_grid.TransferCurrentCell(TRUE, GX_INVALIDATE, FALSE);

			// Date
			SetDlgItemText(IDC_EDIT_DATE, pDoc->m_datetime.Format("%x"));

			// Time
			SetDlgItemText(IDC_EDIT_TIME, pDoc->m_datetime.Format("%X"));


			// Number of replicates (columns)
			SetDlgItemInt(IDC_EDIT_NUMREPS, (UINT) pDoc->m_pps.m_numreps, TRUE);

			// Nuber of samples (rows)
			SetDlgItemInt(IDC_EDIT_NUMSAMPS, (UINT) pDoc->m_pps.m_numsamps, TRUE);

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
				CString bg_str;

				CSample::m_background = (long)SCNearestInt(pDoc->m_samples[0].m_average);
				bg_str.Format("%ld", CSample::m_background);
				SetDlgItemText(IDC_EDIT_BACKGROUND, bg_str);
			}

		}

		CString display_str;
		// Background
		display_str.Format("%ld", CSample::m_background);
		SetDlgItemText(IDC_EDIT_BACKGROUND, display_str);

		// Fit these columns to the text I've put in them
		m_grid.ResizeColWidthsToFit(
			CGXRange(0, 0, m_grid.GetRowCount(), m_grid.GetColCount()));

		HiliteCell(lHint);

		m_grid.GetParam()->SetLockReadOnly(TRUE);
		m_grid.LockUpdate(bOldLock);
		m_grid.Redraw();
	}
	else if (lHint == -2)
	{
		// On a new, re-init the grid, reset date & time, and re-set the 
		// number of reps and samps.
		m_grid.Initialize();
		// Date
		SetDlgItemText(IDC_EDIT_DATE, pDoc->m_datetime.Format("%x"));

		// Time
		SetDlgItemText(IDC_EDIT_TIME, pDoc->m_datetime.Format("%X"));

		// Number of replicates (columns)
		SetDlgItemInt(IDC_EDIT_NUMREPS, (UINT) pDoc->m_pps.m_numreps, TRUE);

		// Nuber of samples (rows)
		SetDlgItemInt(IDC_EDIT_NUMSAMPS, (UINT) pDoc->m_pps.m_numsamps, TRUE);
	}
}

void CSAView::OnFileSaveAsText()
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

void CSAView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CSAView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}


void CSAView::OnExcel()
{
	// TODO: Add your command handler code here
	SAGetApp()->FB12Inhibit();

 	// Ensure that each views current cell is stored
	m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	CSAPPS* pps = &SAGetApp()->m_pps;

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

	SAGetApp()->FB12Uninhibit();
}


void CSAView::OnAddRep()
{
	// TODO: Add your control notification handler code here
	CSADoc* pDoc = (CSADoc*)GetDocument();

	if (pDoc != NULL)
	{
		UINT reps;
		pDoc->SetModifiedFlag(TRUE);


		reps = GetDlgItemInt(IDC_EDIT_NUMREPS, NULL, FALSE);
		reps++;
		pDoc->m_pps.SetNumReps(reps);

		for (UINT i = 0; i < pDoc->m_numsamples; i++)
		{
			pDoc->m_samples[i].m_replicates.SetSize(reps);
		}

		m_grid.AddReplicate(reps-1);


		SetDlgItemInt(IDC_EDIT_NUMREPS, reps, FALSE);

		// (pDoc->m_sample_num <= m_grid.GetRowCount())
		if ((pDoc->m_replicate_num == 1) && (pDoc->m_sample_num == (pDoc->m_last_sample + 1))
			&& (pDoc->m_sample_num != 1) && (pDoc->m_pps.UseRowOrder()) && (pDoc->m_last_sample > 0))
		{
			if ((pDoc->m_sample_num == (pDoc->m_numsamples + 1)) ||
				(pDoc->m_samples[pDoc->m_sample_num - 1].m_replicates[0].m_used == false))
			{
				pDoc->m_sample_num = pDoc->m_last_sample;
				pDoc->m_replicate_num = pDoc->m_last_replicate;
				pDoc->GetNext(pDoc->m_replicate_num, pDoc->m_sample_num);
			}
		}
		pDoc->SetStatus();
		GetDocument()->UpdateAllViews(NULL);

	}

}

void CSAView::OnAddSamp()
{
	// TODO: Add your control notification handler code here
	CSADoc* pDoc = (CSADoc*)GetDocument();

	if (pDoc != NULL)
	{
		UINT samps;
		pDoc->SetModifiedFlag(TRUE);

		samps = GetDlgItemInt(IDC_EDIT_NUMSAMPS, NULL, FALSE);
		samps++;
		pDoc->m_pps.SetNumSamps(samps);

		if (pDoc->m_pps.UseBackground())
		{
			pDoc->m_samples.SetSize(samps + 1);
			pDoc->m_samples[samps].m_replicates.SetSize(pDoc->m_pps.m_numreps);
			m_grid.AddSample(samps, true);
		}
		else
		{
			pDoc->m_samples.SetSize(samps);
			pDoc->m_samples[samps-1].m_replicates.SetSize(pDoc->m_pps.m_numreps);
			m_grid.AddSample(samps, false);
		}
		pDoc->m_numsamples = ((pDoc->m_pps.UseBackground()) ? (pDoc->m_pps.m_numsamps + 1) : pDoc->m_pps.m_numsamps);

		SetDlgItemInt(IDC_EDIT_NUMSAMPS, samps, FALSE);

		//((int)pDoc->m_replicate_num <= pDoc->m_pps.m_numreps)
		if ((pDoc->m_sample_num == 1) && (pDoc->m_replicate_num == (pDoc->m_last_replicate + 1))
			&& (pDoc->m_replicate_num != 1) && (!pDoc->m_pps.UseRowOrder()) && (pDoc->m_last_replicate > 0))
		{
			if ((pDoc->m_replicate_num == (pDoc->m_pps.m_numreps + 1)) ||
				(pDoc->m_samples[0].m_replicates[pDoc->m_replicate_num - 1].m_used == false))
			{
				pDoc->m_sample_num = pDoc->m_last_sample;
				pDoc->m_replicate_num = pDoc->m_last_replicate;
				pDoc->GetNext(pDoc->m_replicate_num, pDoc->m_sample_num);
			}
		}
		pDoc->SetStatus();
		GetDocument()->UpdateAllViews(NULL);
	}

}



void CSAView::UpdateSample(UINT sample_num)
{

	CSADoc* pDoc = (CSADoc*)GetDocument();
	if (pDoc != NULL)
	{
		ROWCOL row, col;
		row = sample_num;
		col = 1;

		UINT num_reps, i;

		num_reps = pDoc->m_pps.m_numreps;
		CSample *pSample = &(pDoc->m_samples[row-1]);

		// Sample name
		if ((sample_num == 1) && pDoc->m_pps.UseBackground())
		{
			m_grid.SetValueRange(CGXRange(row, col++), "Background");
		}
		else
		{
			m_grid.SetValueRange(CGXRange(row, col++),
				pDoc->m_pps.m_samplelist[row - ((pDoc->m_pps.UseBackground()) ? 2 : 1)]);
		}

		// RLU values for reps
		for (i=0; i < num_reps; i++)
		{
			if (pSample->m_replicates[i].m_used)
			{
				m_grid.SetValueRange(CGXRange(row, col++),
					pSample->m_replicates[i].m_RLU);
			}
			else
			{
				m_grid.SetValueRange(CGXRange(row, col++), "");
			}
		}

		CString double_str;

		if (pSample->NumReplicatesUsed() > 0)
		{
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
					{
						m_grid.SetValueRange(CGXRange(row, col++), "N/A");
					}
				}
				else if (!pSample->m_netprecision_overflow)
				{
					double_str.Format("%.2f", pSample->m_precision_net);
					m_grid.SetValueRange(CGXRange(row, col++), double_str);
				}
				else
				{
						m_grid.SetValueRange(CGXRange(row, col++),
							"Div by zero");
				}
			}
			else  // There is just one replicate, so just set the Net
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
			if (num_reps > 1)
			{
				// Blank out all the columns if all reps are unused
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
		{
			m_grid.ScrollCellInView(row, pDoc->m_last_replicate + 1);
		}

	}

}

void CSAView::OnKillfocusEditBackground()
{
	// TODO: Add your control notification handler code here
	CString background_str;
	GetDlgItemText(IDC_EDIT_BACKGROUND, background_str);
	long background_val = atol(background_str);
	if (background_val != CSample::m_background)
	{
		CSample::m_background = background_val;
		CSADoc* pDoc = (CSADoc*)GetDocument();
		int i;
		for (i = 0; i < pDoc->m_samples.GetSize(); i++)
		{
			pDoc->m_samples[i].Recalculate();
		}
		GetDocument()->UpdateAllViews(NULL);
	}
}


void CSAView::OnContextBackground()
{
	// TODO: Add your command handler code here
	CString back_str;
	back_str.Format("%ld", m_grid.m_ctxt_cell_int);
	SetDlgItemText(IDC_EDIT_BACKGROUND, back_str);
	OnKillfocusEditBackground();
}


void CSAView::HiliteCell(UINT current_row)
{
	if (SAGetApp()->m_mode == CSAApp::APPMODE_RUN)
	{
		CSADoc *pDoc = SAGetDoc();

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
				hilite_col = pDoc->m_replicate_num; 
				hilite_row = pDoc->m_sample_num; 
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

void CSAView::OnDestroy()
{
	CGridView::OnDestroy();

	// TODO: Add your message handler code here

	if (m_grid.GetParam())
	{
 		// Ensure that the current cell can be stored
 		m_grid.TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE);
	}

}


BOOL CSAView::PreTranslateMessage(MSG* pMsg)
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

bool CSAView::EditsActive()
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

void CSAView::SendToExcel()
{
	OnExcel();
}
