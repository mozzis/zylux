// MainFrm.cpp : implementation of the CMainFrame class
//



#include "stdafx.h"
#include "CA.h"
#include "CADoc.h"
#include "General.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame


IMPLEMENT_DYNAMIC(CMainFrame, CProtocolFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CProtocolFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_RUNBAR, OnViewRunbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RUNBAR, OnUpdateViewRunbar)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_FB12_DOORSTATUS, OnUpdateDoorStatus)
	ON_UPDATE_COMMAND_UI(ID_FB12_TIMER, OnUpdateTimer)
	ON_UPDATE_COMMAND_UI(ID_FB12_RX, OnUpdateRX)
#ifdef FB12_SIMULATE
	ON_COMMAND(ID_FB12_DOOR, OnToggleDoor)
	ON_UPDATE_COMMAND_UI(ID_FB12_DOOR, OnUpdateDoor)
#endif
END_MESSAGE_MAP()




static UINT indicators_run[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_FB12_TIMER,			// countdown delay and measurement timer
	ID_FB12_DOORSTATUS,		// FB12 door status
	ID_FB12_RX,				// FB12 communication status
};

static UINT indicators_view[] =
{
	ID_SEPARATOR,           // status line indicator
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()  //: m_wndRunBar(NULL)
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CProtocolFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	bool run_mode = (CAGetApp()->m_mode == CCAApp::APPMODE_RUN) ? true : false;

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	// Setup the main toolbar
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP |
			CBRS_TOOLTIPS | CBRS_FLYBY) ||
			!m_wndToolBar.LoadToolBar(run_mode ? IDR_MAINFRAME : IDR_VIEWFRAME))
	{
		TRACE0("Failed to create main toolbar\n");
		return -1;      // fail to create
	}

	// Create m_wndRunBar
	if (!m_wndRunBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP |
			CBRS_TOOLTIPS | CBRS_FLYBY, IDW_RUNBAR) ||
			!m_wndRunBar.LoadToolBar(IDR_MEASURE))	{
		TRACE0("Failed to create run toolbar\n");
		return -1;
	}

	// Setup the FB12 toolbar
	if (!m_wndFB12Bar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP |
		CBRS_TOOLTIPS | CBRS_FLYBY, IDW_FB12BAR) ||
		!m_wndFB12Bar.LoadToolBar(IDR_FB12))
	{
		TRACE0("Failed to create FB12 toolbar\n");
		return -1;      // fail to create
	}

	// Setup the status bar
	UINT* ind =  run_mode ? indicators_run : indicators_view;
	int ind_sz = (run_mode ? sizeof(indicators_run) :
		sizeof(indicators_view)) / sizeof(UINT);
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(ind, ind_sz))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetWindowText(_T("Standard"));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY | CBRS_FLOAT_MULTI);

	m_wndRunBar.SetWindowText(_T("Measure"));
	m_wndRunBar.EnableDocking(CBRS_ALIGN_ANY | CBRS_FLOAT_MULTI);

	m_wndFB12Bar.SetWindowText(_T("FB12"));
	m_wndFB12Bar.EnableDocking(CBRS_ALIGN_ANY | CBRS_FLOAT_MULTI);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBarRightOf(&m_wndRunBar, &m_wndToolBar);
	DockControlBarRightOf(&m_wndFB12Bar, &m_wndRunBar);

	LoadBarState(_T("Toolbars"));

	ShowControlBar(&m_wndRunBar, run_mode ? TRUE : FALSE, FALSE);
#ifdef FB12_SIMULATE
	ShowControlBar(&m_wndFB12Bar, run_mode ? TRUE : FALSE, FALSE);
#else
	ShowControlBar(&m_wndFB12Bar, FALSE, FALSE);
#endif

	//RecalcLayout();
	//if (!run_mode)
	//{
	//	SetMessageText(IDS_VIEW_IDLEMESSAGE);
	//}

	return 0;

}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CProtocolFrame::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CProtocolFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CProtocolFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewRunbar()
{
	// TODO: Add your command handler code here
	bool bVisible = ((m_wndRunBar.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndRunBar, !bVisible, FALSE);
	RecalcLayout();
}

void CMainFrame::OnUpdateViewRunbar(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CAGetApp()->m_mode == CCAApp::APPMODE_RUN);
	pCmdUI->SetCheck((m_wndRunBar.GetStyle() & WS_VISIBLE) != 0);
}


void CMainFrame::OnUpdateDoorStatus(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	LPCTSTR txt = "Door ?";
	CCAApp* pApp = CAGetApp();
	if (pApp->m_pFB12Device && pApp->m_pFB12Device->get_dooropen())
	{
		txt = "Door Open";
	}
	else
	{
		txt = "Door Closed";
	}

	pCmdUI->SetText(txt);
}

void CMainFrame::OnUpdateTimer(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString txt;
	CCADoc* pDoc = CAGetDoc();
	if (pDoc != NULL)
	{
		if (pDoc->m_delaycount > 0)
		{
			txt.Format("D %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_delaycount * (10 / SAMPLES_PER_SEC)));
		}
		else if (pDoc->m_meascount > 0)
		{
			txt.Format("M %s", (LPCTSTR)SCFormatDeciseconds(pDoc->m_meascount * (10 / SAMPLES_PER_SEC)));
		}
	}
	pCmdUI->SetText(txt);
}

void CMainFrame::OnUpdateRX(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CCAApp* pApp = CAGetApp();
	pCmdUI->Enable(pApp->m_pFB12Device && pApp->m_pFB12Device->get_communicating());
}

#ifdef FB12_SIMULATE
void CMainFrame::OnToggleDoor()
{
	if (CAGetApp()->m_pFB12Device)
	{
		CAGetApp()->m_pFB12Device->SetDoorOpen(!CAGetApp()->m_pFB12Device->get_dooropen());
	}
}

void CMainFrame::OnUpdateDoor(CCmdUI* pCmdUI)
{
	if (CAGetApp()->m_pFB12Device)
	{
		pCmdUI->SetCheck(CAGetApp()->m_pFB12Device->get_dooropen() ? 1 : 0);
	}
}
#endif

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SaveBarState(_T("Toolbars"));
	
	CProtocolFrame::OnClose();
}
