/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// MainFrame.cpp : implementation file
//
/*
* $History: MainFrame.cpp $ * 
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 6/08/00    Time: 7:10a
// Updated in $/ZyluxCap/2.0
// Add another digit to the version number displayed
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 5/15/00    Time: 11:32a
// Updated in $/ZyluxCap/2.0
// Don't restore app window position if program is started via COM -
// causes window to flash before it is repositioned
// 
// *****************  Version 9  *****************
// User: Maynard      Date: 5/15/00    Time: 10:47a
// Updated in $/ZyluxCap/2.0
// Use m_bAutomated flag to determine whether to save window position on
// exit; also pass along value to child dialog when it is created
*/

#include "stdafx.h"
#include <afxpriv.h>
#include "ZyluxCap.h"
#include "Zyluxtlb.h"
#include "MainFrame.h"
#include "resource.h"
#include "winplace.h"
#include "zyluxform.h"
#include "tty.h"

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

class CAboutDlg : public CDialog
{
public:
  CAboutDlg() : CDialog(IDD) { }

	enum { IDD = IDD_ABOUTBOX };

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual BOOL OnInitDialog() { ShowVerInfo(); return CDialog::OnInitDialog(); }
	//}}AFX_VIRTUAL
  // Gets version info from app's version resource and puts it into controls
  /////////////////////////////////////////////////////////////////////////////
  void ShowVerInfo()
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
            SetDlgItemText(IDC_APPNAME, csInfo);
            }

          pStrQuery = TEXT("\\StringFileInfo\\040904b0\\FileVersion");
          if (VerQueryValue(pVerInfo, pStrQuery, (LPVOID*)&pvInfo, &cbTranslate))
            {
            CString csCopy = pvInfo, csInfo;
            LPCTSTR pDel = TEXT(" ,");
            LPTSTR pCh1 = _tcstok(csCopy.GetBuffer(0), pDel),
                   pCh2 = _tcstok(0, pDel),
                   pCh3 = _tcstok(0, pDel);
            csInfo.Format("Program Version %s.%s.%s", pCh1, pCh2, pCh3);
#ifdef _ZYLUX_BRITISH
            csInfo += TEXT("B (British Version)");
#endif
            SetDlgItemText(IDC_VERINFO, csInfo);
            }
          }
        delete [] pVerInfo;
        }
      }
  }
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

CMainFrame::CMainFrame()
{
  m_bAutomated = false; // default
}

CMainFrame::~CMainFrame()
{
}

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
  ON_WM_MENUSELECT()
	ON_COMMAND(IDM_ABOUTBOX, OnAboutBox)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

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

// Utility used by OnCreate
//////////////////////////////////////////////////////////////////////////
static void DeleteSysMenu(CWnd *pWnd, UINT uMenuID)
{
	// Menu ID must be in the system command range.
	ASSERT((uMenuID & 0xFFF0) == uMenuID);

  CMenu* pSysMenu = pWnd->GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
    pSysMenu->DeleteMenu(uMenuID, MF_BYCOMMAND);
}

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
  if (!m_bAutomated)
    CWindowPlacement().Restore(IDR_ENT_APP, this, FALSE, FALSE);

  // put these two actions "out of the way" on the system menu
  AppendSysMenu(this, IDM_SHOWTTY, IDS_DATA);
  AppendSysMenu(this, IDM_ABOUTBOX, IDS_ABOUTBOX);
  // remove these two actions from the system menu
  DeleteSysMenu(this, SC_MAXIMIZE);
  DeleteSysMenu(this, SC_SIZE);
  // Keep app around as long as this window exists
  AfxOleLockApp(); // "add strong ref on behalf of user"

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
   	pContext->m_pNewViewClass = RUNTIME_CLASS(CZyluxForm);
		if (0 == (m_pDlg = (CZyluxForm *)CreateView(pContext, AFX_IDW_PANE_FIRST)))
			return FALSE;
    // give dialog pointer to pointer in this window
    m_pDlg->SetRef((CWnd **)&m_pDlg);
    m_pDlg->m_bAutomated = this->m_bAutomated;
    }
	return TRUE;
}

// do window clean up where window handle still needed
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnDestroy() 
{
  delete m_pDlg;
	CFrameWnd::OnDestroy();
}

BOOL CMainFrame::DestroyWindow() 
{
  // save the app's window position for next time
  if (!m_bAutomated)
    CWindowPlacement().Save(IDR_ENT_APP, this);	
  m_pDlg = 0; // once this is gone, no way to deal with children

	BOOL bRet = CFrameWnd::DestroyWindow();
  return bRet;
}

// Defer message processing to the child FormView
///////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  if (m_pDlg && m_pDlg->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// This override chooses which message to display while idle
void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
  if (AFX_IDS_IDLEMESSAGE == nID && m_pDlg && m_pDlg->IsConnected())
    {
    if (m_pDlg->m_pTTYInfo->m_bReadingData)
      rMessage = _T("Reading data...");
    else if (m_pDlg->m_pTTYInfo->m_bPushingData)
      rMessage = _T("Sending data to Excel...");
    else
      rMessage = _T("Waiting for data...");
    }
  else
    CFrameWnd::GetMessageString(nID, rMessage);
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
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
    }
	else if ((nID & 0xFFF0) == IDM_SHOWTTY)
    m_pDlg->SendMessage(WM_COMMAND, IDM_SHOWTTY, 0);
	else
		CFrameWnd::OnSysCommand(nID, lParam);
}


void CMainFrame::OnAboutBox() 
{
  OnSysCommand(IDM_ABOUTBOX, 0);	
}

void CMainFrame::OnClose() 
{
  if (m_pDlg)
    {
    m_pDlg->DoNotify(ZYNOTIFY_APP, ZYCODE_COMPLETE);
    if (m_pDlg && !IsWindow(m_pDlg->GetSafeHwnd()))
      m_pDlg->SendMessage(WM_CLOSE, 0, 0);
    }
  CFrameWnd::OnClose();
  AfxOleUnlockApp();
}
