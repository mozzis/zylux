// ChartView.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "SKDoc.h"
#include "SKHint.h"
#include "ChartView.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartView

IMPLEMENT_DYNCREATE(CChartView, CView)

CChartView::CChartView()
{
	//{{AFX_DATA_INIT(CChartView)
	//}}AFX_DATA_INIT
}

CChartView::~CChartView()
{
}

void CChartView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartView, CView)
	//{{AFX_MSG_MAP(CChartView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_KINETICS_ZOOMOUT, OnZoomout)
	ON_UPDATE_COMMAND_UI(ID_KINETICS_ZOOMOUT, OnUpdateZoomout)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CChartView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CChartView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CChartView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartView diagnostics

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CView::AssertValid();
}

void CChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartView message handlers

int CChartView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// Update the view pointer in the document
	((CProtocolDoc*)GetDocument())->m_graph_view = this;

	return 0;
}

void CChartView::OnDestroy() 
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

void CChartView::OnInitialUpdate() 
{
	CSKDoc* pDoc = (CSKDoc*)GetDocument();

	// zooming init
	m_zoomed = false;
	m_selecting = false;
	m_sample_start = 0;
	m_sample_end = pDoc->m_pps.m_numsamples - 1;

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
	pT->SetMinorTickRatio(1);
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
	//pL->SetKeySize(20);
	//pL->GetStyle()->SetLegendLine(FALSE);
	//pL->GetStyle()->SetLegendKeyStyle(CX_KEY_BOX);
	m_graph.AddComponent(pL);

	// Set up some graph stuff
	UINT i;
	for (i = 0; i <= pDoc->m_pps.m_numreplicates; i++)
	{
		if (i == 0)
		{
			m_graph.SetHeader(i, "Avg");
		}
		else
		{
			CString rep_str;
			rep_str.Format("Rep %ld", i);
			m_graph.SetHeader(i, rep_str);
		}
		UINT j;
		for (j = 0; j < pDoc->m_pps.m_numsamples; j++)
		{
			m_graph.GetGroup(i)->GetIndex(j)->SetNull(TRUE);
		}
	}
	TCHAR dsec_str[32];
	for (i = 0; i < pDoc->m_pps.m_numsamples; i++)
	{
		SCFormatDecisecondsCh(i * pDoc->m_pps.m_intervaltime, dsec_str);
		strcat(dsec_str, " ");
		m_graph.GetGroup(0)->GetIndex(i)->SetAnnotation(dsec_str);
	}

	SRGraphStyle style;
	style.SetObjectStyle(CX_OBJECT_LINE);
	m_graph.SetGlobalStyle(-1, -1, -1, -1, &style, TRUE);

	CView::OnInitialUpdate();
}

void CChartView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if ((lHint >= 0) || (pHint != NULL))
	{
		// Get a pointer to the document
		CSKDoc* pDoc = (CSKDoc*)GetDocument();

		if ((lHint == 0) && (pHint == NULL))
		{
			// Update all the samples
			UINT sample_num;
			for (sample_num = 0; sample_num < pDoc->m_numsamples; sample_num++)
			{
				UINT replicate_num;
				for (replicate_num = 0; replicate_num < pDoc->m_pps.m_numreplicates; replicate_num++)
				{
					UpdateSample(sample_num, replicate_num);
				}
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
				UpdateSample(sample_num - 1, ((CSKHint*)pHint)->m_replicate);
			}
		}
		Invalidate(FALSE);
	}
}

void CChartView::UpdateSample(UINT sample_num, UINT replicate_num)
{
	CSKDoc* pDoc = (CSKDoc*)GetDocument();

	UINT graph_index = replicate_num + 1;
	CSample* sample = &pDoc->m_samples[sample_num];
	if (sample->m_replicates[replicate_num].m_used && pDoc->m_graph_replicates[replicate_num])
	{
		if (pDoc->m_graph_smoothing)
		{
			double sum = sample->m_replicates[replicate_num].m_RLU;
			long num = 1;
			if ((sample_num > 0) && (sample_num < (pDoc->m_pps.m_numsamples - 1)))
			{
				sample_num--;
				if (pDoc->m_samples[sample_num].m_replicates[replicate_num].m_used)
				{
					sum += pDoc->m_samples[sample_num].m_replicates[replicate_num].m_RLU;
					num++;
				}
				sample_num += 2;
				if (pDoc->m_samples[sample_num].m_replicates[replicate_num].m_used)
				{
					sum += pDoc->m_samples[sample_num].m_replicates[replicate_num].m_RLU;
					num++;
				}
				// Put sample_num back to original value
				sample_num--;
			}
			else if (sample_num == 0)
			{
				sample_num++;
				if ((sample_num < pDoc->m_pps.m_numsamples) &&
					(pDoc->m_samples[sample_num].m_replicates[replicate_num].m_used))
				{
					sum += pDoc->m_samples[sample_num].m_replicates[replicate_num].m_RLU;
					num++;
				}
				// Put sample_num back to original value
				sample_num--;
			}
			else
			{
				sample_num--;
				if (pDoc->m_samples[sample_num].m_replicates[replicate_num].m_used)
				{
					sum += pDoc->m_samples[sample_num].m_replicates[replicate_num].m_RLU;
					num++;
				}
				// Put sample_num back to original value
				sample_num++;
			}
			m_graph.SetValue(sample_num, graph_index, sum / (double)num);
		}
		else
		{
			m_graph.SetValue(sample_num, graph_index, sample->m_replicates[replicate_num].m_RLU);
		}
	}
	else
	{
		m_graph.GetGroup(graph_index)->GetIndex(sample_num)->SetNull(TRUE);
	}

	// Display the average
	if (pDoc->m_graph_showaverage && (sample->GetNumReplicates() > 0))
	{
		if (pDoc->m_graph_smoothing)
		{
			double sum = sample->m_average;
			long num = 1;
			if ((sample_num > 0) && (sample_num < (pDoc->m_pps.m_numsamples - 1)))
			{
				sample_num--;
				if (pDoc->m_samples[sample_num].GetNumReplicates() > 0)
				{
					sum += pDoc->m_samples[sample_num].m_average;
					num++;
				}
				sample_num += 2;
				if (pDoc->m_samples[sample_num].GetNumReplicates() > 0)
				{
					sum += pDoc->m_samples[sample_num].m_average;
					num++;
				}
				// Put sample_num back to original value
				sample_num--;
			}
			else if (sample_num == 0)
			{
				sample_num++;
				if ((sample_num < pDoc->m_pps.m_numsamples) &&
					(pDoc->m_samples[sample_num].GetNumReplicates() > 0))
				{
					sum += pDoc->m_samples[sample_num].m_average;
					num++;
				}
				// Put sample_num back to original value
				sample_num--;
			}
			else
			{
				sample_num--;
				if (pDoc->m_samples[sample_num].GetNumReplicates() > 0)
				{
					sum += pDoc->m_samples[sample_num].m_average;
					num++;
				}
				// Put sample_num back to original value
				sample_num++;
			}
			m_graph.SetValue(sample_num, 0, sum / (double)num);
		}
		else
		{
			m_graph.SetValue(sample_num, 0, sample->m_average);
		}
	}
	else
	{
		m_graph.GetGroup(0)->GetIndex(sample_num)->SetNull(TRUE);
	}
}

BOOL CChartView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		bool post;
		UINT message;

		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			post = true;
			message = ID_MEASURE_START;
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

	return CView::PreTranslateMessage(pMsg);
}

void CChartView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_graph.DrawComponentList(pDC, this);
}

BOOL CChartView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CChartView::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CChartView::OnLButtonUp(UINT nFlags, CPoint point) 
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

void CChartView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CChartView::DrawSelection()
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

void CChartView::OnZoomout() 
{
	// TODO: Add your command handler code here
	CSKDoc* pDoc = (CSKDoc*)GetDocument();
	m_sample_start = 0;
	m_sample_end = pDoc->m_pps.m_numsamples - 1;
	SetSampleRange();
	m_zoomed = false;
}

void CChartView::SetSampleRange()
{
	CWaitCursor wait_cursor;
	SRGraphDisplay* display = m_compound_display->GetYAxisA()->GetDisplay();
	display->SetMinIndex(m_sample_start);
	display->SetMaxIndex(m_sample_end);
	display->SetSignificantChange();
	//Invalidate();
	GetDocument()->UpdateAllViews(NULL, 0, NULL);
}

void CChartView::OnUpdateZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_zoomed ? TRUE : FALSE);
}

BOOL CChartView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	return CView::DoPreparePrinting(pInfo);
}

void CChartView::OnEditCopy() 
{
	CRect rect;
	CDC memDC, *pDC = GetDC();
	GetClientRect(&rect);
	memDC.CreateCompatibleDC(pDC);
	CBitmap CopyBitmap;
	CopyBitmap.CreateCompatibleBitmap(pDC, rect.Width(),rect.Height());
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
