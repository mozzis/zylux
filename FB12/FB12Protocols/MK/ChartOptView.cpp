// ChartOptView.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "MKDoc.h"
#include "MKHint.h"
#include "ChartView.h"
#include "General.h"
#include "ChartOptView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartOptView

IMPLEMENT_DYNCREATE(CChartOptView, CFormView)

CChartOptView::CChartOptView()
	: CFormView(CChartOptView::IDD)
{
	//{{AFX_DATA_INIT(CChartOptView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CChartOptView::~CChartOptView()
{
}

void CChartOptView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartOptView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartOptView, CFormView)
	//{{AFX_MSG_MAP(CChartOptView)
	ON_BN_CLICKED(IDC_CHECK_LOG, OnCheckLog)
	ON_BN_CLICKED(IDC_CHECK_SMOOTHING, OnCheckSmoothing)
	ON_EN_KILLFOCUS(IDC_EDIT_MAX, OnKillfocusEditMax)
	ON_EN_KILLFOCUS(IDC_EDIT_MIN, OnKillfocusEditMin)
	ON_BN_CLICKED(IDC_RADIO_AUTOMATIC, OnRadioAutomatic)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, OnRadioManual)
	ON_LBN_SELCHANGE(IDC_LIST_REPLICATES, OnSelchangeListReplicates)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_KINETICS_ZOOMOUT, OnUpdateKineticsZoomout)
	ON_COMMAND(ID_KINETICS_ZOOMOUT, OnKineticsZoomout)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_BN_CLICKED(IDC_RADIO_ACTUAL, OnRadioActual)
	ON_BN_CLICKED(IDC_RADIO_NOMINAL, OnRadioNominal)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_LBN_DBLCLK(IDC_LIST_REPLICATES, OnSelchangeListReplicates)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartOptView diagnostics

#ifdef _DEBUG
void CChartOptView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChartOptView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartOptView message handlers

void CChartOptView::OnCheckLog()
{
	// TODO: Add your control notification handler code here
	CButton* pLog = (CButton*)GetDlgItem(IDC_CHECK_LOG);
	ASSERT(pLog != NULL);
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_log = (pLog->GetCheck() == 1) ? true : false;

	AdjustLog();

	CChartView* pView = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	pView->m_graph.SetSignificantChanges();
	pView->Invalidate(FALSE);
}

void CChartOptView::OnCheckSmoothing()
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_smoothing = !pDoc->m_graph_smoothing;
	((CChartView*)pDoc->m_graph_view)->OnUpdate(NULL, 0, NULL);
	OnUpdate(NULL, 0, NULL);
}

void CChartOptView::OnKillfocusEditMax()
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	CString value_str;

	CEdit* pMax = (CEdit*)GetDlgItem(IDC_EDIT_MAX);
	pMax->GetWindowText(value_str);
	pDoc->m_graph_RLU_max = strtol(value_str, NULL, 10);

	AdjustMax();

	CChartView* pView = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	pView->m_graph.SetSignificantChanges();
	pView->Invalidate(FALSE);
}

void CChartOptView::OnKillfocusEditMin()
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	CString value_str;

	CEdit* pMin = (CEdit*)GetDlgItem(IDC_EDIT_MIN);
	pMin->GetWindowText(value_str);
	pDoc->m_graph_RLU_min = strtol(value_str, NULL, 10);

	AdjustMin();

	CChartView* pView = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	pView->m_graph.SetSignificantChanges();
	pView->Invalidate(FALSE);
}

void CChartOptView::OnRadioAutomatic()
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd = GetDlgItem(IDC_EDIT_MIN);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDC_EDIT_MAX);
	pWnd->EnableWindow(FALSE);

	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_manual = false;

	SetAutomatic();

	CChartView* pView = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	pView->m_graph.SetSignificantChanges();
	pView->Invalidate(FALSE);
}

void CChartOptView::OnRadioManual()
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_EDIT_MIN);
	pWnd->EnableWindow(TRUE);
	pWnd = GetDlgItem(IDC_EDIT_MAX);
	pWnd->EnableWindow(TRUE);

	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_manual = true;

	SetManual();

	CChartView* pView = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	pView->m_graph.SetSignificantChanges();
	pView->Invalidate(FALSE);
}

void CChartOptView::OnSelchangeListReplicates()
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	int item = m_list_replicates.GetCurSel();
	if (item != LB_ERR)
	{
		UINT sample = item / (pDoc->m_numreps + 1);
		UINT rep = item % (pDoc->m_numreps + 1);

		CMKHint hint(1, pDoc->m_numsamps, 0);
		pDoc->m_graph_replicates[item] = (m_list_replicates.GetCheck(item) == 1) ? true : false;
		((CChartView*)pDoc->m_graph_view)->OnUpdate(NULL, 0, NULL);
		if (rep == pDoc->m_numreps)
		{
			// this is an average item
			UpdateAverage(sample);
		}
		else
		{
			// this is a replicate item
			UpdateReplicate(sample, rep);
		}
		m_list_replicates.Invalidate();
	}
}

void CChartOptView::SetAutomatic()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	SRGraphDisplay* pD = ((CChartView*)pDoc->m_graph_view)->m_compound_display->GetYAxisA()->GetDisplay();
	pD->GetStyle()->SetUseMaxScale(pDoc->m_graph_manual ? TRUE : FALSE);
	pD->GetStyle()->SetAlwaysShowZero(pDoc->m_graph_manual ? FALSE : TRUE);
}

void CChartOptView::SetManual()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	SRGraphDisplay* pD = ((CChartView*)pDoc->m_graph_view)->m_compound_display->GetYAxisA()->GetDisplay();
	pD->GetStyle()->SetUseMaxScale(pDoc->m_graph_manual ? TRUE : FALSE);
	pD->GetStyle()->SetAlwaysShowZero(pDoc->m_graph_manual ? FALSE : TRUE);

	AdjustMin();
	AdjustMax();
}

void CChartOptView::AdjustMin()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	if (pDoc->m_graph_RLU_max < pDoc->m_graph_RLU_min)
	{
		pDoc->m_graph_RLU_max = pDoc->m_graph_RLU_min + 1;
		CWnd *pMax = (CEdit*)GetDlgItem(IDC_EDIT_MAX);
		CString value_str;
		value_str.Format("%ld", pDoc->m_graph_RLU_max);
		pMax->SetWindowText(value_str);
		AdjustMax();
	}

	SRGraphDisplay* pD = ((CChartView*)pDoc->m_graph_view)->m_compound_display->GetYAxisA()->GetDisplay();
	pD->SetMinRangeY(pDoc->m_graph_RLU_min);
}

void CChartOptView::AdjustMax()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	if (pDoc->m_graph_RLU_min > pDoc->m_graph_RLU_max)
	{
		pDoc->m_graph_RLU_min = pDoc->m_graph_RLU_max - 1;
		CWnd *pMin = (CEdit*)GetDlgItem(IDC_EDIT_MIN);
		CString value_str;
		value_str.Format("%ld", pDoc->m_graph_RLU_min);
		pMin->SetWindowText(value_str);
		AdjustMin();
	}

	SRGraphDisplay* pD = ((CChartView*)pDoc->m_graph_view)->m_compound_display->GetYAxisA()->GetDisplay();
	pD->SetMaxRangeY(pDoc->m_graph_RLU_max);
}

void CChartOptView::AdjustLog()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	SRGAxisManager* pAxis = ((CChartView*)pDoc->m_graph_view)->m_compound_display->GetYAxisA();
	SRGraphStyle* pStyle = pAxis->GetDisplay()->GetStyle();
	pAxis->UnregisterLabels(TRUE);
	if (pDoc->m_graph_log)
	{
		SRGLogScale *pScale = new SRGLogScale;
		//SRGDecimalScale* pScale = new SRGDecimalScale;
		pAxis->RegisterLabels(pScale);
		pStyle->SetLog(TRUE);

		//CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_AUTOMATIC);
		//pButton->SetCheck(1);
		//OnRadioAutomatic();
		//pButton->EnableWindow(FALSE);
		//pButton = (CButton*)GetDlgItem(IDC_RADIO_MANUAL);
		//pButton->SetCheck(0);
		//pButton->EnableWindow(FALSE);
		//CWnd* pWnd = GetDlgItem(IDC_STATIC_RLURANGE);
		//pWnd->EnableWindow(FALSE);
	}
	else
	{
		SRGDecimalScale *pScale = new SRGDecimalScale;
		pAxis->RegisterLabels(pScale);
		pStyle->SetLog(FALSE);

		//CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_AUTOMATIC);
		//pButton->EnableWindow(TRUE);
		//pButton = (CButton*)GetDlgItem(IDC_RADIO_MANUAL);
		//pButton->EnableWindow(TRUE);
		//CWnd* pWnd = GetDlgItem(IDC_STATIC_RLURANGE);
		//pWnd->EnableWindow(TRUE);
	}
}

BOOL CChartOptView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		bool post;
		UINT message;

		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (SCHasFocus(IDC_EDIT_MIN))
			{
				OnKillfocusEditMin();
				post = false;
			}
			else if (SCHasFocus(IDC_EDIT_MAX))
			{
				OnKillfocusEditMax();
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

	return CFormView::PreTranslateMessage(pMsg);
}

bool CChartOptView::EditsActive()
{
	return (SCHasFocus(IDC_EDIT_MIN) || SCHasFocus(IDC_EDIT_MAX));
}

void CChartOptView::OnInitialUpdate()
{
	// Sublass the list box
	m_list_replicates.SubclassDlgItem(IDC_LIST_REPLICATES, this);

	// Update the options
	CMKDoc* pDoc = (CMKDoc*)GetDocument();

	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_CHECK_SMOOTHING);
	pButton->SetCheck(pDoc->m_graph_smoothing ? 1 : 0);

	CEdit* pMin = (CEdit*)GetDlgItem(IDC_EDIT_MIN);
	CEdit* pMax = (CEdit*)GetDlgItem(IDC_EDIT_MAX);
	CString num_str;
	num_str.Format("%ld", pDoc->m_graph_RLU_min);
	pMin->SetWindowText(num_str);
	num_str.Format("%ld", pDoc->m_graph_RLU_max);
	pMax->SetWindowText(num_str);
	AdjustMin();
	AdjustMax();

	// Setup manual/automatic mode
	if (pDoc->m_graph_manual)
	{
		pButton = (CButton*)GetDlgItem(IDC_RADIO_MANUAL);
		pButton->SetCheck(1);
		pMin->EnableWindow(TRUE);
		pMax->EnableWindow(TRUE);
		SetManual();
	}
	else
	{
		pButton = (CButton*)GetDlgItem(IDC_RADIO_AUTOMATIC);
		pButton->SetCheck(1);
		pMin->EnableWindow(FALSE);
		pMax->EnableWindow(FALSE);
		SetAutomatic();
	}

	// Setup regular/log scale
	pButton = (CButton*)GetDlgItem(IDC_CHECK_LOG);
	pButton->SetCheck(pDoc->m_graph_log ? 1 : 0);
	AdjustLog();

	// Setup graph by mode
	if (pDoc->m_graph_nominal)
	{
		pButton = (CButton*)GetDlgItem(IDC_RADIO_NOMINAL);
		pButton->SetCheck(1);
	}
	else
	{
		pButton = (CButton*)GetDlgItem(IDC_RADIO_ACTUAL);
		pButton->SetCheck(1);
	}

	// TODO: Add your specialized code here and/or call the base class
	UINT i, j, k;
	for (i = 0, k = 0; i < pDoc->m_numsamps; i++)
	{
		for (j = 0; j <= pDoc->m_numreps; j++, k++)
		{
			CString rep_str;
			if (j == pDoc->m_numreps)
			{
				rep_str.Format("S%ld Average", i + 1);
			}
			else
			{
				rep_str.Format("S%ld Rep %ld", i + 1, j + 1);
			}
			m_list_replicates.AddString(rep_str);
			m_list_replicates.SetCheck(k, pDoc->m_graph_replicates[k] ? 1 : 0);
			m_list_replicates.SetInfo(k, RepInfo());
		}
	}
	m_list_replicates.AdjustSize();

	// We now must adjust the scroll bars
	CRect rect;
	m_list_replicates.GetWindowRect(rect);
	ScreenToClient(&rect);
	SetScrollSizes(MM_TEXT, CSize(rect.right + 1, rect.bottom + 1));
	ScrollToPosition(pDoc->m_graph_scroll_pt);

	CFormView::OnInitialUpdate();
}

void CChartOptView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if ((lHint == 0) && (pHint == 0))
	{
		CMKDoc* pDoc = (CMKDoc*)GetDocument();
		UINT i, j;
		for (i = 0; i < pDoc->m_numsamps; i++)
		{
			for (j = 0; j < pDoc->m_numreps; j++)
			{
				UpdateReplicate(i, j);
			}
			UpdateAverage(i);
		}
		Invalidate();
	}
	else if (pHint)
	{
		CMKHint* hint = (CMKHint*)pHint;
		UpdateReplicate(hint->m_samp, hint->m_rep);
		UpdateAverage(hint->m_samp);
		Invalidate();
	}
}

// replicate_num = 0 to (m_numreplicates - 1)
void CChartOptView::UpdateReplicate(UINT sample_num, UINT replicate_num)
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	// Update the replicate
	int item = (sample_num * (pDoc->m_numreps + 1)) + replicate_num;
	m_list_replicates.SetInfo(item, BuildRepInfo(item));
	//m_list_replicates.SetInfo(replicate_num + 1, BuildRepInfo(replicate_num + 1));
}

void CChartOptView::UpdateAverage(UINT sample_num)
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	// Update the average
	int item = (sample_num * (pDoc->m_numreps + 1)) + pDoc->m_numreps;
	m_list_replicates.SetInfo(item, BuildRepInfo(item));
	//m_list_replicates.SetInfo(0, BuildRepInfo(0));
}

RepInfo CChartOptView::BuildRepInfo(UINT rep)
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	CChartView* chart_view = (CChartView*)pDoc->m_graph_view;

	__int64 sum = 0;
	int count = 0;
	long max = 0;
	UINT max_index = chart_view->m_sample_start;
	long rlu;
	UINT i;
	for (i = chart_view->m_sample_start;
		i <= chart_view->m_sample_end; i++)
	{
		if (chart_view->m_graph.GetGroup(rep)->GetIndex(i)->GetNull() == FALSE)
		{
			rlu = (long)chart_view->m_graph.GetValue(i, rep);
			sum += (__int64)rlu;
			count++;
			if (rlu > max)
			{
				max = rlu;
				max_index = i;
			}
		}
	}
	if (count > 0)
	{
		long halfmax = (long)SCNearestInt((double)max / 2.0);
		// Search for Time of Half Max
		int halfrise = -2;
		i = max_index;	// we always check max_index, but does no harm
		while (true)
		{
			if ((chart_view->m_graph.GetGroup(rep)->GetIndex(i)->GetNull() == FALSE) &&
				((long)chart_view->m_graph.GetValue(i, rep) <= halfmax))
			{
				halfrise = i;
				break;
			}
			if (i <= chart_view->m_sample_start)
			{
				break;
			}
			i--;
		}
		if (halfrise >= 0)
		{
			int next = -1;
			i = halfrise + 1;
			while (true)
			{
				if (chart_view->m_graph.GetGroup(rep)->GetIndex(i)->GetNull() == FALSE)
				{
					next = i;
					break;
				}
				if (i >= chart_view->m_sample_end)
				{
					break;
				}
				i++;
			}
			if (next >= 0)
			{
				double x0 = (double)halfrise;
				double x1 = (double)next;
				double y0 = chart_view->m_graph.GetValue(halfrise, rep);
				double y1 = chart_view->m_graph.GetValue(next, rep);
				double dx = x1 - x0;
				double dy = y1 - y0;
				if ((dx != 0.0) && (dy != 0))
				{
					double y = (double)max / 2.0;
					double x =  (y - y0 + dy * x0 / dx) * dx / dy;
					halfrise = (long)SCNearestInt(x);
				}
				else
				{
					halfrise = -2;
				}
			}
			else
			{
				halfrise = -2;
			}
		}

		// Search for Time of Max Decay
		int halfdecay = -2;
		i = max_index;	// we always check max_index, but does no harm
		while (true)
		{
			if ((chart_view->m_graph.GetGroup(rep)->GetIndex(i)->GetNull() == FALSE) &&
				((long)chart_view->m_graph.GetValue(i, rep) <= halfmax))
			{
				halfdecay = i;
				break;
			}
			if (i >= chart_view->m_sample_end)
			{
				break;
			}
			i++;
		}
		if (halfdecay >= 1)
		{
			int prev = -1;
			i = halfdecay - 1;
			while (true)
			{
				if (chart_view->m_graph.GetGroup(rep)->GetIndex(i)->GetNull() == FALSE)
				{
					prev = i;
					break;
				}
				if (i <= chart_view->m_sample_start)
				{
					break;
				}
				i--;
			}
			if (prev >= 0)
			{
				double x0 = (double)halfdecay;
				double x1 = (double)prev;
				double y0 = chart_view->m_graph.GetValue(halfdecay, rep);
				double y1 = chart_view->m_graph.GetValue(prev, rep);
				double dx = x1 - x0;
				double dy = y1 - y0;
				if ((dx != 0.0) && (dy != 0))
				{
					double y = (double)max / 2.0;
					double x =  (y - y0 + dy * x0 / dx) * dx / dy;
					halfdecay = (long)SCNearestInt(x);
				}
				else
				{
					halfdecay = -2;
				}
			}
			else
			{
				halfdecay = -2;
			}
		}

		return RepInfo((long)SCNearestInt((double)sum / (double)count),
			max, max_index, halfrise, halfdecay);
	}
	else
	{
		return RepInfo();
	}
}

void CChartOptView::OnDestroy()
{
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_scroll_pt = GetScrollPosition();

	CFormView::OnDestroy();
}

void CChartOptView::OnUpdateKineticsZoomout(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CChartView* view = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	view->OnUpdateZoomout(pCmdUI);
}

void CChartOptView::OnKineticsZoomout()
{
	// TODO: Add your command handler code here
	CChartView* view = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	view->OnZoomout();
}


void CChartOptView::OnFilePrint()
{
	// TODO: Add your command handler code here
	CChartView* view = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	view->OnFilePrint();
}

void CChartOptView::OnFilePrintPreview()
{
	// TODO: Add your command handler code here
	CChartView* view = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	view->OnFilePrintPreview();
}

void CChartOptView::OnEditCopy()
{
	// TODO: Add your command handler code here
	CChartView* view = (CChartView*)((CMKDoc*)GetDocument())->m_graph_view;
	view->OnEditCopy();
}

void CChartOptView::OnRadioActual() 
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_nominal = false;
	((CChartView*)pDoc->m_graph_view)->OnUpdate(NULL, 0, NULL);
	OnUpdate(NULL, 0, NULL);
}

void CChartOptView::OnRadioNominal() 
{
	// TODO: Add your control notification handler code here
	CMKDoc* pDoc = (CMKDoc*)GetDocument();
	pDoc->m_graph_nominal = true;
	((CChartView*)pDoc->m_graph_view)->OnUpdate(NULL, 0, NULL);
	OnUpdate(NULL, 0, NULL);
}
