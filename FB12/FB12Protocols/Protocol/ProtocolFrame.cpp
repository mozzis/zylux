// ProtocolFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "ProtocolFrame.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtocolFrame

IMPLEMENT_DYNCREATE(CProtocolFrame, CMDIFrameWnd)

CProtocolFrame::CProtocolFrame() : m_placement_loaded(false)
{
}

CProtocolFrame::~CProtocolFrame()
{
}


BEGIN_MESSAGE_MAP(CProtocolFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CProtocolFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolFrame message handlers

int CProtocolFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HICON hIcon = AfxGetApp()->LoadIcon(ProtGetApp()->m_main_icon_id);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	
	// Load some stuff from the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	WINDOWPLACEMENT placement;
	if (SCGetAppProfileBinary(appname, "Settings", "MainFrame",
		(BYTE*)&placement, sizeof(placement)))
	{
		SetWindowPlacement(&placement);
		m_placement_loaded = true;
	}

	return 0;
}

void CProtocolFrame::OnDestroy() 
{
	// Save the window placement
	WINDOWPLACEMENT placement;
	memset(&placement, 0, sizeof(placement));
	placement.length = sizeof(placement);
	if (GetWindowPlacement(&placement))
	{
		CString appname = "STLS\\";
		appname += AfxGetApp()->m_pszAppName;
		SCWriteAppProfileBinary(appname, "Settings", "MainFrame",
			(BYTE*)&placement, sizeof(placement));
	}

	CMDIFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CProtocolFrame::DockControlBarRightOf(CToolBar* Bar,CToolBar* RightOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	RightOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=RightOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

void CProtocolFrame::SetMessageText(LPCTSTR lpszText)
{
	m_status_str = lpszText;
	CMDIFrameWnd::SetMessageText(AFX_IDS_IDLEMESSAGE);
}

void CProtocolFrame::SetMessageText(UINT nID)
{
	m_status_str.LoadString(nID);
	CMDIFrameWnd::SetMessageText(AFX_IDS_IDLEMESSAGE);
}

UINT CProtocolFrame::GetLastStatusID() const
{
	return m_nIDLastMessage;
}
