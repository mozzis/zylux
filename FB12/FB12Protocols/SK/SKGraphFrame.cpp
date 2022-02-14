// SKGraphFrame.cpp : implementation file
//

#include "stdafx.h"
#include "sk.h"
#include "SKGraphFrame.h"
#include "ChartView.h"
#include "ChartOptView.h"
#include "SKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKGraphFrame

IMPLEMENT_DYNCREATE(CSKGraphFrame, CGraphFrame)

CSKGraphFrame::CSKGraphFrame()
{
}

CSKGraphFrame::~CSKGraphFrame()
{
}


BEGIN_MESSAGE_MAP(CSKGraphFrame, CGraphFrame)
	//{{AFX_MSG_MAP(CSKGraphFrame)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKGraphFrame message handlers

BOOL CSKGraphFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CGraphFrame::OnCreateClient(lpcs, pContext);

	BOOL b = m_splitter.CreateStatic(this, 2, 1);

	if (b)
	{
		CSKDoc* pDoc = SKGetDoc();
		m_splitter.CreateView(1, 0, RUNTIME_CLASS(CChartView), CSize(300, 300), pContext);
		m_splitter.CreateView(0, 0, RUNTIME_CLASS(CChartOptView), CSize(300, pDoc->m_graph_cy), pContext);
	}

	return b;
}

BOOL CSKGraphFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CGraphFrame::PreCreateWindow(cs);
}

void CSKGraphFrame::OnDestroy() 
{
	CSKDoc* pDoc = SKGetDoc();
	CChartOptView* view = (CChartOptView*)m_splitter.GetPane(0, 0);
	if (view)
	{
		CRect rect;
		view->GetWindowRect(rect);
		pDoc->m_graph_cy = rect.Height();
	}

	CGraphFrame::OnDestroy();
}
