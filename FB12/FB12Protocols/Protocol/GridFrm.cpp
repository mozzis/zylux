// GridFrm.cpp : implementation of the CGridFrame class
//

#include "stdafx.h"

#include "GridFrm.h"
#include "Protocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridFrame

IMPLEMENT_DYNCREATE(CGridFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CGridFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGridFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridFrame construction/destruction

CGridFrame::CGridFrame()
{
	// TODO: add member initialization code here

}

CGridFrame::~CGridFrame()
{
}

BOOL CGridFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGridFrame diagnostics

#ifdef _DEBUG
void CGridFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CGridFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridFrame message handlers

int CGridFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	HICON hIcon = AfxGetApp()->LoadIcon(ProtGetApp()->m_doc_icon_id);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	ProtGetApp()->m_pDoc->m_grid_frame = this;

	return 0;
}

void CGridFrame::OnDestroy() 
{
	CMDIChildWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	// Update some info in the document
	CProtocolDoc* pDoc = ProtGetApp()->m_pDoc;
	if (pDoc->m_grid_placement.length == 0)
	{
		// Initialize the kinetics window placement structure
		pDoc->m_grid_placement.length = sizeof(pDoc->m_grid_placement);
	}
	// Grab the kinetics window placement information
	GetWindowPlacement(&pDoc->m_grid_placement);

	ProtGetApp()->m_pDoc->m_grid_frame = NULL;
}
