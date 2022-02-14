// QMView.cpp : implementation file
//

#include "stdafx.h"
#include "QM.h"
#include "General.h"
#include "QMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
void TraceVariantArray(VARIANT& v);
#endif

/////////////////////////////////////////////////////////////////////////////
// CQMView

IMPLEMENT_DYNCREATE(CQMView, CGridView)

CQMView::CQMView()
	: CGridView(CQMView::IDD)
{
	//{{AFX_DATA_INIT(CQMView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CQMView::~CQMView()
{
}

BOOL CQMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGridView::PreCreateWindow(cs);
}

void CQMView::DoDataExchange(CDataExchange* pDX)
{
	CGridView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQMView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQMView, CGridView)
	//{{AFX_MSG_MAP(CQMView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE_AS_TEXT, OnFileSaveAsText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_UPDATE_COMMAND_UI(ID_EXCEL, OnUpdateExcel)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGridView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQMView diagnostics

#ifdef _DEBUG
void CQMView::AssertValid() const
{
	CGridView::AssertValid();
}

void CQMView::Dump(CDumpContext& dc) const
{
	CGridView::Dump(dc);
}

CQMDoc* CQMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQMDoc)));
	return (CQMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQMView drawing

void CQMView::OnDraw(CDC* pDC)
{
	CQMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CQMView printing

BOOL CQMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CQMDoc* pDoc = GetDocument();
	CGXProperties* pProp = m_grid.GetParam()->GetProperties();
	pProp->SetCenterHorizontal(FALSE);
	CString hd_str;

	// Set the print header
	ROWCOL row_hdr = 0;
	hd_str.Format("Protocol name: %s", SCGetFileTitle(QMGetApp()->m_pps.m_protocolname));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Date: %s", pDoc->m_datetime.Format("%x"));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Time: %s", pDoc->m_datetime.Format("%X"));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Delay time: %s", SCFormatDeciseconds(pDoc->m_delaytime));
	pProp->GetDataHeader().StoreStyleRowCol(++row_hdr, 1, CGXStyle().SetValue(hd_str), gxCopy);
	hd_str.Format("Measurement time: %s", SCFormatDeciseconds(pDoc->m_meastime));
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

void CQMView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	QMGetApp()->FB12Inhibit();
	m_grid.OnGridBeginPrinting(pDC, pInfo);
}

void CQMView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	m_grid.OnEndPrinting(pDC, pInfo);
	QMGetApp()->FB12Uninhibit();
}

void CQMView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrint(pDC, pInfo);

	//CGridView::OnPrint(pDC, pInfo);
}

void CQMView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	m_grid.OnGridPrepareDC(pDC, pInfo);

	//CGridView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CQMView message handlers

void CQMView::OnInitialUpdate()
{
	m_grid.SubclassDlgItem(IDC_QMGRID, this);
	m_grid.Initialize();

	CGridView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	MyGridResize();

	CQMDoc* pDoc = (CQMDoc*)GetDocument();
	//CString display_str;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_EDIT_DELAYTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_delaytime));
	pWnd = GetDlgItem(IDC_EDIT_MEASTIME);
	ASSERT(pWnd != NULL);
	pWnd->SetWindowText(SCFormatDeciseconds(pDoc->m_meastime));
}

void CQMView::OnSize(UINT nType, int cx, int cy)
{
	CGridView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	MyGridResize();
}

void CQMView::MyGridResize()
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

void CQMView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bOldLock = m_grid.LockUpdate(TRUE);

	CQMDoc* pDoc = (CQMDoc*)GetDocument();

	// Allow changes to the grid
	m_grid.GetParam()->SetLockReadOnly(FALSE);

	if (lHint == 0)
	{
		// Set the display header information
		CString display_str;
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_EDIT_DATE);
		ASSERT(pWnd != NULL);
		pWnd->SetWindowText(pDoc->m_datetime.Format("%x"));
		pWnd = GetDlgItem(IDC_EDIT_TIME);
		ASSERT(pWnd != NULL);
		pWnd->SetWindowText(pDoc->m_datetime.Format("%X"));

		ROWCOL rlu_count = pDoc->m_RLUs.GetSize();
		if (rlu_count == 0)
		{
			// Reset the grid to empty
			m_grid.SetRowCount(1);
			m_grid.SetValueRange(CGXRange(1, 1), "");
			m_grid.ScrollCellInView(lHint, 1);
		}
		else
		{
			// Update all the RLUs in the grid
			m_grid.SetRowCount(rlu_count);
			ROWCOL i;
			for (i = 0; i < rlu_count; i++)
			{
				CGXRange rng(i + 1, 1);
				m_grid.SetValueRange(rng, pDoc->m_RLUs[i]);
				m_grid.SetStyleRange(rng, CGXStyle()
					.SetUserAttribute(GX_IDS_UA_TOOLTIPTEXT, ""));
			}
		}
	}
	else
	{
		if (m_grid.GetRowCount() != (ROWCOL)lHint)
		{
			m_grid.SetRowCount(lHint);
		}
		CGXRange rng(lHint, 1);
		m_grid.SetValueRange(rng, pDoc->m_RLUs[lHint - 1]);
		m_grid.SetStyleRange(rng, CGXStyle()
			.SetUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
			pDoc->m_kinetics.GetMeanString()));

		// Scroll to the new cell
		m_grid.ScrollCellInView(lHint, 1);
	}

	// Disallow changes to the grid
	m_grid.GetParam()->SetLockReadOnly(TRUE);

	m_grid.LockUpdate(bOldLock);
	m_grid.Redraw();
}

void CQMView::OnFileSaveAsText()
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

void CQMView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_grid.Copy();
}

void CQMView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grid.CanCopy());
}

void CQMView::OnExcel()
{
	// TODO: Add your command handler code here
	QMGetApp()->FB12Inhibit();

	m_grid.SendToExcel();

	QMGetApp()->FB12Uninhibit();
}

#ifdef _DEBUG
void TraceVariantArray(VARIANT& v)
{
	TRACE("\tparray = 0x%p\n", v.parray);
	TRACE("\t{\n");
	TRACE("\t\tcDims = %d\n", v.parray->cDims);
	TRACE("\t\tfFeatures = 0x%x\n", v.parray->fFeatures);
	TRACE("\t\tcbElements = %d\n", v.parray->cbElements);
	TRACE("\t\tcLocks = %d\n", v.parray->cLocks);
	TRACE("\t\tpvData = 0x%p\n", v.parray->pvData);
	TRACE("\t\t{\n");
	long ndim = v.parray->cDims;
	long nele = 1;
	COleVariant* pv = (COleVariant*)v.parray->pvData;
	long i;
	for(i = 0; i < ndim; i++)
	{
		nele *= v.parray->rgsabound[i].cElements;
	}
	for(i = 0; i < nele; i++)
	{
		TRACE("\t\t\tpvData[%d] =\n", i);
		TRACE("\t\t\t{");
		afxDump << pv[i];
		TRACE("\n\t\t\t}\n");
	}
	TRACE("\t\t}\n");
	for(i = 0; i < ndim; i++)
	{
		TRACE("\t\trgsabound[%d] =\n", i);
		TRACE("\t\t{\n");
		TRACE("\t\t\tcElements = %d\n", v.parray->rgsabound[i].cElements);
		TRACE("\t\t\tlLbound = %d\n", v.parray->rgsabound[i].lLbound);
		TRACE("\t\t}\n");
	}
	TRACE("\t}\n");
}
#endif

void CQMView::OnUpdateExcel(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CQMDoc* pDoc = (CQMDoc*)GetDocument(); //QMGetApp()->m_pDoc;
	if (pDoc)
	{
		pCmdUI->Enable(((pDoc->GetMode() == CQMDoc::MODE_STOPPED) &&
			(pDoc->m_RLUs.GetSize() > 0)) ? TRUE : FALSE);
	}
}
