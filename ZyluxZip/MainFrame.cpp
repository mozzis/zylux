// MainFrame.cpp : implementation file
// Mainframe is a container for the main window for this application
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: MainFrame.cpp $ * 
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:40p
 * Updated in $/ZyluxZip
 * Put back special system menu handling (defers to child form)
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:17p
 * Updated in $/ZyluxZip
 * Check m_pDlg pointer for zero a couple of places (no crash noted, but
 * is safer)
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:36p
 * Updated in $/ZyluxZip
 * Add comments
 * Remove un-needed overrides of OnDestroy, OnMenuSelect and OnSysCommand
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxpriv.h>
#include "MainFrame.h"
#include "resource.h"
#include "winplace.h"
#include "zyluxzipdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

// Gets version info from app's version resource and puts it into controls
/////////////////////////////////////////////////////////////////////////////
static void ShowVerInfo(CWnd *pWnd)
{
  TCHAR szFileName[_MAX_PATH];
  if (GetModuleFileName(0, szFileName, sizeof(szFileName)))
    {
    DWORD dwDummy, dwSize = GetFileVersionInfoSize(szFileName, &dwDummy);
    if (dwSize)
      {
      BYTE *pVerInfo = new BYTE[dwSize];
      if (GetFileVersionInfo(szFileName, 0, dwSize, pVerInfo))
        {
        UINT cbTranslate = 0;
        LPTSTR pvInfo = 0;
        // 040904b0 means English(US)
        LPTSTR pStrQuery = TEXT("\\StringFileInfo\\040904b0\\FileDescription");

        if (VerQueryValue(pVerInfo, pStrQuery, (LPVOID*)&pvInfo, &cbTranslate))
          {
          CString csInfo = pvInfo;
          pWnd->SetDlgItemText(IDC_APPNAME, csInfo);
          }

        pStrQuery = TEXT("\\StringFileInfo\\040904b0\\FileVersion");
        if (VerQueryValue(pVerInfo, pStrQuery, (LPVOID*)&pvInfo, &cbTranslate))
          {
          CString csCopy = pvInfo, csInfo;
          LPCTSTR pDel = TEXT(" ,");
          LPTSTR pCh1 = _tcstok(csCopy.GetBuffer(0), pDel),
                 pCh2 = _tcstok(0, pDel),
                 pCh3 = _tcstok(0, pDel);
          csInfo.Format("Program Version %s.%s%s", pCh1, pCh2, pCh3);
          pWnd->SetDlgItemText(IDC_VERINFO, csInfo);
          }
        pStrQuery = TEXT("\\StringFileInfo\\040904b0\\LegalCopyright");
        if (VerQueryValue(pVerInfo, pStrQuery, (LPVOID*)&pvInfo, &cbTranslate))
          {
          CString csInfo = pvInfo;
          if (pWnd->GetDlgItem(IDC_COPYRIGHT))
            pWnd->SetDlgItemText(IDC_COPYRIGHT, csInfo);
          }
        }
      delete [] pVerInfo;
      }
    }
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  ShowVerInfo(this);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
  ON_WM_MENUSELECT()
	ON_COMMAND(IDM_ABOUTBOX, OnAboutBox)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// Called by the system before OnCreate
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
  // get rid of maximize box and disable resizing
  cs.style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME | WS_VISIBLE);
  // make sure there is a title bar and a frame border
  cs.style |= WS_CAPTION | WS_BORDER;
  // in general, window looks like overlapped window and
  // acts like dialog
  cs.dwExStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_DLGMODALFRAME;
	
	return CFrameWnd::PreCreateWindow(cs);
}

// Add a command to the "system" menu
// Utility used by OnCreate
//////////////////////////////////////////////////////////////////////////
static void AppendSysMenu(CWnd *pWnd, UINT uMenuID, UINT uStrID)
{
	// Menu ID must be in the system command range.
	ASSERT((uMenuID & 0xFFF0) == uMenuID);
	ASSERT(uMenuID < 0xF000);

	CMenu* pSysMenu = pWnd->GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
    {
		CString strMenu;
		strMenu.LoadString(uStrID);
		if (!strMenu.IsEmpty())
      {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, uMenuID, strMenu);
      }
    }
}

// Utility used by on create to modify system menu
/////////////////////////////////////////////////////////////////////////////
static void DeleteSysMenu(CWnd *pWnd, UINT uMenuID)
{
	// Menu ID must be in the system command range.
	ASSERT((uMenuID & 0xFFF0) == uMenuID);

  CMenu* pSysMenu = pWnd->GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
    pSysMenu->DeleteMenu(uMenuID, MF_BYCOMMAND);
}

// Called by the system to create this window
//////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  // OnCreateClient needs a CCreateContext
  CCreateContext cCtx;
  cCtx.m_pCurrentFrame = this;
  lpCreateStruct->lpCreateParams = &cCtx;
  // this eventually calls OnCreateClient
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
  // Create the status (message) bar	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
    {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
    }

  // restore the window's previous position, if any
  CWindowPlacement().Restore(IDR_ENT_APP, this, FALSE, FALSE);

  AppendSysMenu(this, IDM_SHOWDATA, IDS_DATA);

  // remove these two actions from the system menu
  DeleteSysMenu(this, SC_MAXIMIZE);
  DeleteSysMenu(this, SC_SIZE);

  return 0;
}

// Force the frame window to create a client form view even though
// no "document" is open - this app just wants to display a form
// containing controls
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
  // default create client will create a view if asked for it
	if (pContext)
    {
   	pContext->m_pNewViewClass = RUNTIME_CLASS(CZyluxZipDlg);
		if (0 == (m_pDlg = (CZyluxZipDlg *)CreateView(pContext, AFX_IDW_PANE_FIRST)))
			return FALSE;
    m_pDlg->SetRef((CWnd **)&m_pDlg);
    ShowVerInfo(m_pDlg);
    }
	return TRUE;
}

// Do cleanup which requires a window handle
/////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::DestroyWindow() 
{
  // save the app's window position for next time
  CWindowPlacement().Save(IDR_ENT_APP, this);	
	return CFrameWnd::DestroyWindow();
}

// Defer WM_COMMAND message processing to the child FormView
///////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  if (m_pDlg && m_pDlg->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE; // if child handled, return now

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// This override chooses which message to display while idle
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
  if (nID == AFX_IDS_IDLEMESSAGE)
    {
    if (m_pDlg)
      {
      rMessage = _T("Ready");
      }
    }
  else
    CFrameWnd::GetMessageString(nID, rMessage);
}

// Displays the about box in response to menu choice
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnAboutBox() 
{
  CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CMainFrame::OnClose() 
{
  // attempt to close the form first
  if (m_pDlg)
    m_pDlg->SendMessage(WM_CLOSE, 0, 0);
  if (!m_pDlg) // if form really did close
    CFrameWnd::OnClose(); // finish up
}

// Let child form handle checking/unchecking, etc. of items
// on the "system" menu in upper left corner of app window
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
  // ID == 0 if initializing menu; want only "system" menu
  // of box in upper left corner of App window
  if (nItemID == 0 && (nFlags & MF_SYSMENU))
    {
    // if the child form exists, defer menu initialization
    // to child form
    if (m_pDlg)
      m_pDlg->OnInitMenu(CMenu::FromHandle(hSysMenu));
    }
  CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
}

// This is called when the user selects an item in the
// "system" menu (click on box in upper-left corner of window)
// Overridden here to route processing to the child form
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_SHOWDATA)
    m_pDlg->SendMessage(WM_COMMAND, IDM_SHOWDATA, 0);
	else
		CFrameWnd::OnSysCommand(nID, lParam);
}
