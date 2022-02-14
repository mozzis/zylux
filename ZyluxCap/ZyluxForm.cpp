/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// ZyluxForm.cpp : implementation file
// This is the control window of the ZyluxCap program
/////////////////////////////////////////////////////////////////////////////
/*
* $History: ZyluxForm.cpp $ * 
// 
// *****************  Version 9  *****************
// User: Maynard      Date: 9/25/00    Time: 2:29p
// Updated in $/ZyluxCap/2.0
// Change call of SetupConnection to OpenConnection in SetPort function
// 
// *****************  Version 8  *****************
// User: Maynard      Date: 5/15/00    Time: 11:35a
// Updated in $/ZyluxCap/2.0
// Do a ShowWindow when positioning app via COM calls, so app shows up as
// it is initially invisible when started from COM
// 
// *****************  Version 7  *****************
// User: Maynard      Date: 5/15/00    Time: 10:45a
// Updated in $/ZyluxCap/2.0
// Add serial port property settings accesible via COM
// Add m_bAutomated flag to know if app is controlled by another program
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 4/14/00    Time: 4:25p
 * Updated in $/ZyluxCap/2.0
 * Put main window on top when CenterOnRect is called
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:15p
 * Updated in $/ZyluxCap/2.0
 * Add SetWindowPosition and CenterOnRect methods for form
 * Use referencing technique from ZyluxZip to know when to delete
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:21a
 * Updated in $/ZyluxCap/2.0
 * Add autoproxy link, notifier routines, Advise and UnAdvise
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 6/29/99    Time: 7:00p
 * Updated in $/ZyluxCap/1.1
 * Fix OnExit handler; posting ID_FILE_CLOSE didn't work anymore, needed
 * to post WM_QUIT
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:29a
 * Updated in $/ZyluxCap/2.0
 * Change settings dialog to propery sheet and pages
*/

#include "stdafx.h"
#include <afxpriv.h>
#include "ZyluxCap.h"
#include "DlgProxy.h"
#include "ZyluxForm.h"
#include "Zyluxtlb.h"
#include "pssettings.h"
#include "tty.h"
#include "WndData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZyluxForm

IMPLEMENT_DYNCREATE(CZyluxForm, CFormView)

CZyluxForm::CZyluxForm()
	: CFormView(CZyluxForm::IDD)
{
	EnableAutomation();
	m_pAutoProxy = NULL;
  m_bAutomated = false;
  m_pSettings = 0;
  m_pWndData = 0;
  m_pTTYInfo = new CTTYInfo;
  m_ppRef = 0;
	//{{AFX_DATA_INIT(CZyluxForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CZyluxForm::~CZyluxForm()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
  // delete child windows
  delete m_pTTYInfo;
  delete m_pWndData;
  // let parent know this window is gone
  if (m_ppRef)
    *m_ppRef = 0;

  m_NotifyList.RemoveAll();
}

void CZyluxForm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	CFormView::OnFinalRelease();
}

BOOL CZyluxForm::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
    ShowWindow(SW_HIDE);
		return FALSE;
	}
	return TRUE;
}

void CZyluxForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZyluxForm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZyluxForm, CFormView)
	//{{AFX_MSG_MAP(CZyluxForm)
	ON_COMMAND(IDM_CONNECT, OnConnect)
	ON_COMMAND(IDM_DISCONNECT, OnDisconnect)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_SHOWTTY, OnShowData)
	ON_UPDATE_COMMAND_UI(IDC_CHK_CONNECT, OnUpdateChkConnect)
	ON_UPDATE_COMMAND_UI(IDM_CONNECT, OnUpdateConnect)
	ON_UPDATE_COMMAND_UI(IDM_DISCONNECT, OnUpdateDisconnect)
	ON_UPDATE_COMMAND_UI(IDM_SHOWTTY, OnUpdateShowData)
	ON_UPDATE_COMMAND_UI(IDM_SETTINGS, OnUpdateSettings)
	ON_BN_CLICKED(IDC_CHK_CONNECT, OnChkConnect)
	ON_COMMAND(IDM_EXIT, OnExit)
  ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CZyluxForm, CFormView)
	//{{AFX_DISPATCH_MAP(CZyluxForm)
	DISP_PROPERTY_EX(CZyluxForm, "Baud", GetBaud, SetBaud, VT_I4)
	DISP_PROPERTY_EX(CZyluxForm, "Port", GetPort, SetPort, VT_I2)
	DISP_PROPERTY_EX(CZyluxForm, "FlowCtrl", GetFlowCtrl, SetFlowCtrl, VT_I2)
	DISP_PROPERTY_EX(CZyluxForm, "DBits", GetDBits, SetDBits, VT_I2)
	DISP_PROPERTY_EX(CZyluxForm, "Parity", GetParity, SetParity, VT_I2)
	DISP_PROPERTY_EX(CZyluxForm, "StopBits", GetStopBits, SetStopBits, VT_I2)
	DISP_FUNCTION(CZyluxForm, "Advise", Advise, VT_ERROR, VTS_UNKNOWN)
	DISP_FUNCTION(CZyluxForm, "UnAdvise", UnAdvise, VT_ERROR, VTS_UNKNOWN)
	DISP_FUNCTION(CZyluxForm, "SetWindowPos", OleSetWindowPos, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CZyluxForm, "CenterOnRect", CenterOnRect, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IZyluxForm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {EEF10E19-C379-11D2-88A4-00104BF194E2}
static const IID IID_IZyluxForm =
{ 0xeef10e19, 0xc379, 0x11d2, { 0x88, 0xa4, 0x0, 0x10, 0x4b, 0xf1, 0x94, 0xe2 } };

BEGIN_INTERFACE_MAP(CZyluxForm, CFormView)
	INTERFACE_PART(CZyluxForm, IID_IZyluxForm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZyluxForm diagnostics

#ifdef _DEBUG
void CZyluxForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CZyluxForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

bool CZyluxForm::IsConnected()
{
  return m_pTTYInfo->fConnected != 0;
}

/////////////////////////////////////////////////////////////////////////////
// CZyluxForm message handlers

void CZyluxForm::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
  GetParentFrame()->RecalcLayout();
  ResizeParentToFit();
  m_pTTYInfo->m_bAutomated = m_bAutomated;
  if (m_pTTYInfo->m_bAutoConnect)
    {
    if (!m_pTTYInfo->OpenConnection())
      AfxMessageBox(_T("Automatic connect failed.\n"
                       "Check the serial port settings."), MB_ICONEXCLAMATION);
    }
  CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_CONNECT);
  pBtn->SetCheck(m_pTTYInfo->fConnected);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.
/////////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnClose() 
{
	if (CanExit())
    {
    CFormView::OnClose();
    if (m_ppRef)
      *m_ppRef = 0;
    }
}

// handles the Exit menu item
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnExit() 
{
	GetParentFrame()->PostMessage(WM_CLOSE, 0, 0);
}

// handles the Actions...Connect menu item
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnConnect() 
{
  if (!m_pTTYInfo->OpenConnection())
    AfxMessageBox(_T("Connection failed."), MB_ICONEXCLAMATION);
  CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_CONNECT);
  pBtn->SetCheck(m_pTTYInfo->fConnected);
}

// handles the Actions...Disconnect menu item
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnDisconnect() 
{
  if (!m_pTTYInfo->CloseConnection())
    AfxMessageBox(_T("Close Connection failed."), MB_ICONEXCLAMATION);
  CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_CONNECT);
  pBtn->SetCheck(m_pTTYInfo->fConnected);
}

// handles clicking on the Connect checkbox
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnChkConnect() 
{
  if (!m_pTTYInfo->fConnected)
    OnConnect();
  else
    OnDisconnect();
  GetParentFrame()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
}

// Shows the settings dialog
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnSettings() 
{
  if (!m_pSettings)
    m_pSettings = new CPSSettings(IDS_SETTINGS, this, 0, m_pTTYInfo, m_bAutomated);
  if (IDOK == m_pSettings->DoModal())
    {
    if (m_pTTYInfo->fConnected && !m_pTTYInfo->SetupConnection())
      {
      DWORD dwError = GetLastError();
      AfxMessageBox(_T("Settings Failed"), MB_ICONEXCLAMATION);
      }
    if (m_pWndData) // if the show data window is open, update its font
      {
       if (m_pTTYInfo->hTTYFont)
         DeleteObject(m_pTTYInfo->hTTYFont);
      CFont mFont;
      if (mFont.CreateFontIndirect(&m_pTTYInfo->lfTTYFont))
        {
        m_pWndData->SetFont(&mFont);
        m_pTTYInfo->hTTYFont = (HFONT)mFont.Detach();
        }
      }
    }
  if (m_pSettings)
    delete m_pSettings;
  m_pSettings = 0;
}

// Shows or hides the data display window
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnShowData() 
{
  if (!m_pWndData) // if not shown, show
    {
    m_pWndData = new CWndData(this, &m_pWndData, m_pTTYInfo);
    m_pWndData->Create(IDD_DATAWIN, this);
    m_pTTYInfo->hWndTerm = m_pWndData->GetSafeHwnd();
    }
  else // if shown, hide
    {
    m_pWndData->SendMessage(WM_CLOSE);
    m_pWndData = 0;
    }
}

// update menu items. called during idle processing
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnUpdateChkConnect(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(m_pTTYInfo && m_pTTYInfo->fConnected);
}

// update menu items. called during idle processing
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnUpdateConnect(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(!m_pTTYInfo->fConnected);
}

// update menu items. called during idle processing
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnUpdateDisconnect(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_pTTYInfo->fConnected);
}

// update menu items. called during idle processing
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnUpdateShowData(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_pWndData != 0);
}

// update menu items. called during idle processing
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnUpdateSettings(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_pSettings != 0);
}

// Common things to do before destructor is called
// when shutting down
BOOL CZyluxForm::DestroyWindow() 
{
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->CloseConnection();  // clean up COM port
  SetEvent(m_pTTYInfo->m_hEventWait); // signal thread stop waiting
  m_pTTYInfo->m_hEventWait = 0;  // signal thread event closed
	return CFormView::DestroyWindow();
}

// This is here to check/uncheck the "Show Data" menu item
// in the system menu
//////////////////////////////////////////////////////////////////////////
void CZyluxForm::OnInitMenu(CMenu* pMenu) 
{
	CMenu* pSysMenu = GetParentFrame()->GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
    {
    CCmdUI cmdUI;
    cmdUI.m_nIndexMax = pSysMenu->GetMenuItemCount();
    for (UINT n = 0; n < pSysMenu->GetMenuItemCount(); ++n) 
      {
      if (pSysMenu->GetMenuItemID(n) != IDM_SHOWTTY)
        continue;
      cmdUI.m_nIndex = n;
      cmdUI.m_nID = pSysMenu->GetMenuItemID(n);
      cmdUI.m_pMenu = pSysMenu;
      cmdUI.DoUpdate(this, FALSE);  
      }
    }
	CFormView::OnInitMenu(pMenu);
}

SCODE CZyluxForm::Advise(LPUNKNOWN pNotifier) 
{
  IZyluxNotify *pNotify;
  IID ZIID = __uuidof(IZyluxNotify);
  SCODE sRes = pNotifier->QueryInterface(ZIID, (void **)&pNotify);
  if (SUCCEEDED(sRes))
    {
    m_NotifyList.AddTail(pNotify);
	  return S_OK;
    }
  else
    return sRes;
}

SCODE CZyluxForm::UnAdvise(LPUNKNOWN pNotifier) 
{
	POSITION pos = m_NotifyList.Find(pNotifier);
  if (pos)
    {
    IZyluxNotify *pNotify = m_NotifyList.GetAt(pos);
    if (pNotify) pNotify->Release();
    m_NotifyList.RemoveAt(pos);
    }

	return S_OK;
}

bool CZyluxForm::DoNotify(long lCategory, long lReason)
{
  POSITION pos = m_NotifyList.GetHeadPosition();
  while (pos)
    {
    IZyluxNotify *pNotify = m_NotifyList.GetNext(pos);
    try 
      { 
      if (pNotify)
        pNotify->Notify(lCategory, lReason, 0);
      }
    catch (COleException * /* pE */)
      {
      }
    }
  return true;
}

void CZyluxForm::OleSetWindowPos(long left, long top, long right, long bottom) 
{
  CWnd *pWnd = GetParentFrame();
  CRect cRect;
  pWnd->GetWindowRect(&cRect);
  cRect.right = left + cRect.Width();
  cRect.bottom = top + cRect.Height();
  cRect.left = left;
  cRect.top = top;
  pWnd->MoveWindow(&cRect);
  pWnd->ShowWindow(SW_SHOWNORMAL);
  pWnd->UpdateWindow();
}


void CZyluxForm::CenterOnRect(long left, long top, long right, long bottom) 
{
  CWnd *pWnd = GetParentFrame();
  CRect cRectChi, cRectPar(left, top, right, bottom);
  pWnd->GetWindowRect(&cRectChi);
  int nWid = cRectChi.Width(), nLen = cRectChi.Height();
  cRectChi.right = cRectPar.CenterPoint().x + nWid / 2;
  cRectChi.left = cRectChi.right - nWid;
  cRectChi.bottom = cRectPar.CenterPoint().y + nLen / 2;
  cRectChi.top = cRectChi.bottom - nLen;
  pWnd->MoveWindow(&cRectChi);
  pWnd->ShowWindow(SW_SHOWNORMAL);
  pWnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
  pWnd->UpdateWindow();
}

long CZyluxForm::GetBaud() 
{
  return m_pTTYInfo->dwBaudRate;
}

void CZyluxForm::SetBaud(long nNewValue) 
{
  m_pTTYInfo->dwBaudRate = nNewValue;
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->SetupConnection();
}

short CZyluxForm::GetPort() 
{
  return m_pTTYInfo->bPort;
}

void CZyluxForm::SetPort(short nNewValue) 
{
  m_pTTYInfo->bPort = (BYTE)nNewValue;
  if (m_pTTYInfo->fConnected)
    {
    m_pTTYInfo->CloseConnection();
    m_pTTYInfo->OpenConnection();
    }
}

short CZyluxForm::GetFlowCtrl() 
{
  return m_pTTYInfo->bFlowCtrl;
}

void CZyluxForm::SetFlowCtrl(short nNewValue) 
{
  m_pTTYInfo->bFlowCtrl = (BYTE)nNewValue;
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->SetupConnection();
}

short CZyluxForm::GetDBits() 
{
  return m_pTTYInfo->bByteSize;
}

void CZyluxForm::SetDBits(short nNewValue) 
{
  m_pTTYInfo->bByteSize = (BYTE)nNewValue;
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->SetupConnection();
}

short CZyluxForm::GetParity() 
{
  return m_pTTYInfo->bParity;
}

void CZyluxForm::SetParity(short nNewValue) 
{
  m_pTTYInfo->bParity = (BYTE)nNewValue;
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->SetupConnection();
}

short CZyluxForm::GetStopBits() 
{
  return m_pTTYInfo->bStopBits;
}

void CZyluxForm::SetStopBits(short nNewValue)
{
  m_pTTYInfo->bStopBits = (BYTE)nNewValue;
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->SetupConnection();
}
