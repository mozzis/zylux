// KineticsView.cpp : implementation file
//

#include "stdafx.h"
#include "KineticsView.h"
#include "ProtocolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKineticsView

IMPLEMENT_DYNCREATE(CKineticsView, CView)

CKineticsView::CKineticsView() : m_kinetics(NULL)
{
}

CKineticsView::~CKineticsView()
{
}


BEGIN_MESSAGE_MAP(CKineticsView, CView)
	//{{AFX_MSG_MAP(CKineticsView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CKineticsView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CKineticsView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CKineticsView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKineticsView drawing

void CKineticsView::OnDraw(CDC* pDC)
{
	m_graph.DrawComponentList(pDC, this);
}

/////////////////////////////////////////////////////////////////////////////
// CKineticsView diagnostics

#ifdef _DEBUG
void CKineticsView::AssertValid() const
{
	CView::AssertValid();
}

void CKineticsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKineticsView message handlers

int CKineticsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// Update the view pointer in the document
	((CProtocolDoc*)GetDocument())->m_graph_view = this;

	return 0;
}

void CKineticsView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	// Update some info in the document
	CProtocolDoc* pDoc = (CProtocolDoc*)GetDocument();
	if (pDoc->m_graph_placement.length == 0)
	{
		// Initialize the kinetics window placement structure
		pDoc->m_graph_placement.length = sizeof(pDoc->m_graph_placement);
	}
	// Grab the kinetics window placement information
	pDoc->m_graph_frame->GetWindowPlacement(&pDoc->m_graph_placement);
	// Update the view pointer
	pDoc->m_graph_view = NULL;
}

void CKineticsView::SetKinetics(CKinetics& kinetics, int max_kinetics)
{
	m_kinetics = &kinetics;
	m_maxkinetics = max_kinetics;

	// Set up the graph
	m_graph.SetHeader(0, "Average");
	m_graph.SetHeader(1, "Sample");
	CString num_str;
	int i;
	for (i = 0; i < m_maxkinetics; i++)
	{
		m_graph.GetGroup(0)->GetIndex(i)->SetNull(TRUE);
		m_graph.GetGroup(1)->GetIndex(i)->SetNull(TRUE);
		num_str.Format("%ld", i + 1);
		m_graph.GetGroup(0)->GetIndex(i)->SetAnnotation(num_str);
	}

	SRGraphStyle style;
	style.SetObjectStyle(CX_OBJECT_LINE);
	m_graph.SetGlobalStyle(-1, -1, -1, -1, &style, TRUE);

	OnUpdate(NULL, 0, NULL);
}

SRGraph* CKineticsView::GetGraph()
{
	return &m_graph;
}

#ifdef _DEBUG
CDocument* CKineticsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
	return m_pDocument;
}
#endif //_DEBUG

void CKineticsView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
	// zooming init
	m_zoomed = false;
	m_selecting = false;
	m_sample_start = 0;
	m_sample_end = 0;

	// Setup the graph
	m_compound_display = new SRGCompoundDisplay;
	m_compound_display->SetMeasurement(CX_PERCENT);
	m_compound_display->SetSizeDefaults();
	m_compound_display->SetRect(0,0,85,100);
	m_compound_display->GetStyle()->SetTierXLabels(TRUE);

	SRGDecimalScale* pDC = new SRGDecimalScale;
	m_compound_display->SetYLabelA(pDC);
	pDC->SetResolution(0);

	SRGIndexScale *pIS = new SRGIndexScale;
	m_compound_display->SetXLabelA(pIS);
	pIS->SetResolution(0);
	pIS->SetNodeAdjust(TRUE);
	pIS->GetStyle()->SetAutoOrientation(FALSE);
	pIS->SetOrientation(0);
	pIS->SetLocationPoint(SRGraphLabel::TopCenter);
	pIS->SetCheckOverlaps(TRUE);

	SRGTickMarks *pT = new SRGTickMarks;
	m_compound_display->SetXTickMarksA(pT);

	pT = new SRGTickMarks;
	pT->SetMinorTickRatio(1);
	m_compound_display->SetYTickMarksA(pT);

	SRGGridLines *pG = new SRGGridLines;
	m_compound_display->SetXGridLinesA(pG);

	pG = new SRGGridLines;
	m_compound_display->SetYGridLinesA(pG);

	SRGraphDisplay *pD = new SRGraphDisplay;
	pD->GetStyle()->SetGraphStyle(CX_GRAPH_LINE);
	pD->GetStyle()->SetAxisStyle(CX_AXIS_CLASSIC);
	pD->GetStyle()->SetDeferDraw(TRUE);
	m_compound_display->SetYGraphDisplayA(pD);				// this sets up the chart data

	SRGraphLabel *pLab = new SRGraphLabel;
	pLab->SetParent(&m_graph);
	pLab->SetAnnotation("Value (RLU/s) ");
	m_compound_display->GetYAxisA()->RegisterTitle(pLab);

	//pLab = new SRGraphLabel;
	//pLab->SetParent(&m_graph);
	//pLab->SetAnnotation("Time");
	//m_compound_display->GetXAxisA()->RegisterTitle(pLab);

	m_graph.AddComponent(m_compound_display);

	SRGraphLegend *pL=new SRGraphLegend;
	pL->SetMeasurement(CX_PERCENT);
	pL->SetSizeDefaults();
	pL->SetRect(85,0,100,100);
	//pL->SetKeySize(10);
	m_graph.AddComponent(pL);

	CView::OnInitialUpdate();
}

BOOL CKineticsView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CKineticsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	// Set up the graph
	if (m_kinetics)
	{
		//int count = m_kinetics->m_RLUs.GetSize();
		int count = m_kinetics->m_num_kinetics;
		double mean = (double)m_kinetics->GetMean();
		int i;
		for (i = 0; i < m_maxkinetics; i++)
		{
			if (i < count)
			{
				m_graph.SetValue(i, 0, mean);
				m_graph.SetValue(i, 1, (double)m_kinetics->m_RLUs[i]);
			}
			else
			{
				m_graph.GetGroup(0)->GetIndex(i)->SetNull(TRUE);
				m_graph.GetGroup(1)->GetIndex(i)->SetNull(TRUE);
			}
		}
		Invalidate();
	}
}

BOOL CKineticsView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	return CView::DoPreparePrinting(pInfo);
}

void CKineticsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_selecting)
	{
		// just a precaution; should never happen
		OnLButtonUp(nFlags, point);
	}

	SRGraphDisplay* display = m_compound_display->GetYAxisA()->GetDisplay();
	CRect rect = display->GetDisplayRect();
	if (rect.PtInRect(point))
	{
		m_selecting = true;
		SetCapture();	// we want to see all mouse movements (inside and outside our wnd)
		m_selection_start = m_selection_end = point;
		// first inversion
		DrawSelection();
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CKineticsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_selecting)
	{
		// last un-inversion
		DrawSelection();

		// Get the end point
		m_selection_end = point;
		SRGraphDisplay* display = m_compound_display->GetYAxisA()->GetDisplay();
		CRect rect = display->GetDisplayRect();
		if (m_selection_end.x < rect.left)
		{
			m_selection_end.x = rect.left;
		}
		if (m_selection_end.x > rect.right)
		{
			m_selection_end.x = rect.right;
		}

		ReleaseCapture();	// we're done watching all mouse movements

		// If the selection is larger than 5 pixels wide.
		// (don't want to zoom on accidental click)
		if ((max(m_selection_start.x, m_selection_end.x) -
			min(m_selection_start.x, m_selection_end.x)) > 5)
		{
			SRGraphPosition start(&m_graph, m_selection_start, this);
			SRGraphPosition end(&m_graph, m_selection_end, this);
			if (start.HasIndex() && end.HasIndex())
			{
				int start_index = start.GetIndex();
				int end_index = end.GetIndex();
				m_sample_start = min(start_index, end_index);
				m_sample_end = max(start_index, end_index);
				SetSampleRange();
				m_zoomed = true;
			}
		}
		m_selecting = false;
	}
	
	CView::OnLButtonUp(nFlags, point);
}

void CKineticsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_selecting)
	{
		// un-invert
		DrawSelection();
		m_selection_end = point;
		// re-invert
		DrawSelection();
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CKineticsView::DrawSelection()
{
	SRGraphDisplay* display = m_compound_display->GetYAxisA()->GetDisplay();
	CRect rect = display->GetDisplayRect();

	// Make sure the start and end points are within our wnd
	if (m_selection_start.x > rect.right)
	{
		m_selection_start.x = rect.right;
	}
	if (m_selection_start.x < rect.left)
	{
		m_selection_start.x = rect.left;
	}
	if (m_selection_end.x > rect.right)
	{
		m_selection_end.x = rect.right;
	}
	if (m_selection_end.x < rect.left)
	{
		m_selection_end.x = rect.left;
	}

	CDC *pDC=GetDC();
	CRect srect;
	srect.SetRect(m_selection_start.x, rect.top, m_selection_end.x, rect.bottom);
	srect.NormalizeRect();
	pDC->InvertRect(srect);
	ReleaseDC(pDC);
}

void CKineticsView::SetSampleRange()
{
	CWaitCursor wait_cursor;
	SRGraphDisplay* display = m_compound_display->GetYAxisA()->GetDisplay();
	display->SetMinIndex(m_sample_start);
	display->SetMaxIndex(m_sample_end);
	display->SetSignificantChange();
	//Invalidate();
	GetDocument()->UpdateAllViews(NULL, 0, NULL);
}

void CKineticsView::OnKineticsZoomout() 
{
	// TODO: Add your command handler code here
	m_sample_start = 0;
	m_sample_end = m_maxkinetics - 1;
	SetSampleRange();
	m_zoomed = false;
}

void CKineticsView::OnUpdateKineticsZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_zoomed ? TRUE : FALSE);
}

void CKineticsView::OnEditCopy() 
{
	CRect rect;
	CDC memDC, *pDC = GetDC();
	GetClientRect(&rect);
	memDC.CreateCompatibleDC(pDC);
	CBitmap CopyBitmap;
	CopyBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *obm = (CBitmap *)memDC.SelectObject(&CopyBitmap);

	BOOL bBkDraw = m_graph.m_bBackgroundDraw;
	m_graph.SetBackgroundDraw(FALSE);
	m_graph.DrawComponentList(&memDC, this);
	m_graph.SetBackgroundDraw(bBkDraw);
	
	memDC.SelectObject(obm);
	memDC.DeleteDC();
	ReleaseDC(pDC);

	if (OpenClipboard())
	{
		EmptyClipboard();
		HBITMAP hbm = (HBITMAP)CopyBitmap.Detach();
		SetClipboardData(CF_BITMAP,hbm);
		CloseClipboard();
	}
	else
	{
		CopyBitmap.DeleteObject();
	}
}
