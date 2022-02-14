// GraphFrm.cpp : implementation of the CGraphFrame class
//

#include "stdafx.h"

#include "GraphFrm.h"
#include "Protocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphFrame

IMPLEMENT_DYNCREATE(CGraphFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CGraphFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGraphFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphFrame construction/destruction

CGraphFrame::CGraphFrame()
{
	// TODO: add member initialization code here

}

CGraphFrame::~CGraphFrame()
{
}

BOOL CGraphFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphFrame diagnostics

#ifdef _DEBUG
void CGraphFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CGraphFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphFrame message handlers

int CGraphFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	HICON hIcon = AfxGetApp()->LoadIcon(ProtGetApp()->m_graph_icon_id);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	return 0;
}
