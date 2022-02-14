// ZyluxZipDlg.cpp : implementation file
// CZyluxZipDlg is the main window for this application
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: ZyluxZipDlg.cpp $ * 
// 
// *****************  Version 19  *****************
// User: Maynard      Date: 9/28/00    Time: 4:22p
// Updated in $/ZyluxZip
// Call RedrawWindow instead of WM_NCACTIVATE in OnDialogOpened/Closed;
// the old function didn't update the window in NT 4.0
// 
// *****************  Version 18  *****************
// User: Maynard      Date: 9/26/00    Time: 9:20a
// Updated in $/ZyluxZip
// Send local serial settings to capture app if it is up.
// 
// *****************  Version 17  *****************
// User: Maynard      Date: 9/04/00    Time: 12:59p
// Updated in $/ZyluxZip
// Make separate menu item update handler for Capture
// Add Invalidate to OnDialogOpened and OnDialogClosed handlers so menu
// gets redrawn
// Catch COM exceptions in OnCapture handler
// 
// *****************  Version 16  *****************
// User: Maynard      Date: 7/22/00    Time: 2:14p
// Updated in $/ZyluxZip
// Fix so app window gets repainted when capture app launched, so the menu
// changes get displayed.
// 
// *****************  Version 15  *****************
// User: Maynard      Date: 7/21/00    Time: 3:14p
// Updated in $/ZyluxZip
// Arrange for some but not all toplevel menu items to be grayed when a
// sub-dialog (including the external capture program) is open
// 
// *****************  Version 14  *****************
// User: Maynard      Date: 6/08/00    Time: 7:22a
// Updated in $/ZyluxZip
// Move the ZyluxCapApp COM object coclass def to this file from the
// header
// Use #import to get ZyluxCap defs instead of private header
// m_pWndData is now dynamically allocated and released
// ZyluxCapApp object is closed and released when this app exits, so it
// doesn't become a ghost
 * 
 * *****************  Version 13  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:25p
 * Updated in $/ZyluxZip
 * Pass ttyinfo to run protocol dialog so can use to send data
 * Don't use ttyinfo reference list anymore
 * Don't mess with fonts in data window, let it worry about them itself
 * 
 * *****************  Version 12  *****************
 * User: Maynard      Date: 3/27/00    Time: 3:04p
 * Updated in $/ZyluxZip
 * Hook settings dialog up to data window
 * 
 * *****************  Version 11  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:43p
 * Updated in $/ZyluxZip
 * Add settings dialog and data window
 * 
 * *****************  Version 10  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:22p
 * Updated in $/ZyluxZip
 * Add OnCapture handler with Notifier to handle launching the ZyluxCap
 * program and detecting when it goes away
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:53p
 * Updated in $/ZyluxZip
 * Call function to initialize run protocol dialog with site list in
 * response to "New" command
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:39p
 * Updated in $/ZyluxZip
 * Add routine to disable MRU items if Run Protocol editor is already open
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/15/00    Time: 2:02p
 * Updated in $/ZyluxZip
 * Add routine to respond to selection from MRU list in Run Protocol menu
 * item
 * Separate RunProtocol open code into DoOpenRunProtocol called by both
 * regular and MRU versions of menu open
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:58a
 * Updated in $/ZyluxZip
 * Add code to actually open the Run Protocol editor dialog and load it up
 * with a pre-existing run protocol list
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/02/00    Time: 8:39p
 * Updated in $/ZyluxZip
 * Add NameList and RunProtocol dialogs
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/01/00    Time: 10:47a
 * Updated in $/ZyluxZip
 * Fix to allow message map to chain to modeless child dialogs:
 *   Keep pointer to modeless in member variable
 *   Clear pointer in OnCloseDialog
 *   Call dialog's OnCmdMsg from this class's OnCmdMsg
 *   Have to lock out recursion in OnCmdMsg since CWnd's version looks for
 * parent windows and calls *their* OnCmdMsg!
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:42p
 * Updated in $/ZyluxZip
 * Add RunProtocolOpen handler
 * Remove OnMenuInit handler
 * Show and hide version info controls when dialogs open or close -
 * otherwise, the grid control doesn't obscure them until a cell is edited
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 2/27/00    Time: 4:42p
 * Created in $/ZyluxZip
 * 
*/
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <afximpl.h> // need to add \tools\msdev\vc98\mfc to include path for this!!
#include "ZyluxZip.h"
#include "ZyluxZipDlg.h"
#include "DlgProxy.h"
#include "dlgsitelist.h"
#include "dlgnamelist.h"
#include "dlgrunprotocol.h"
#include "pssettings.h"
#include "tty.h"
#include "wnddata.h"
#include "messages.h"

#ifdef _DEBUG
#import "..\Debug\ZyluxCap.exe"   
#else                              
#import "..\Release\ZyluxCap.exe" 
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Map toplevel menu items to index
static UINT uMenuIDMap[] = {
  0, // IDM_EDIT
  IDM_SITELIST,
  IDM_RUN_NAMES, 
  IDM_RUN_PROTOCOL,
  0, // IDM_SETTINGS,
  IDM_CAPTURE,
  0, //IDM_ABOUTBOX,
  };

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlg dialog
IID LIBID_ZyluxCap = {0xF0CB6024,0x7876,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};
// {9E6089BA-29F0-4b89-887B-264F9BB6129F}
CLSID CLSID_ZNotify = 
{ 0x9e6089ba, 0x29f0, 0x4b89, { 0x88, 0x7b, 0x26, 0x4f, 0x9b, 0xb6, 0x12, 0x9f } };

namespace ZyluxCap {
  class CZyluxNotify : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CZyluxNotify, &CLSID_ZNotify>,
    public IDispatchImpl<IZyluxNotify, &__uuidof(IZyluxNotify), &LIBID_ZyluxCap>
  {
    public:
      CZyluxNotify() { m_pZipDlg = 0; pOnNotify = 0; }

    BEGIN_COM_MAP(CZyluxNotify)
      COM_INTERFACE_ENTRY(IZyluxNotify)
      COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()
  
    CZyluxZipDlg *m_pZipDlg;
  public:
    void (*pOnNotify)(long lCat, long lCode, IUnknown *pUnk);
  // IZyluxNotify
  public:
    STDMETHOD(Notify)(LONG lCat, LONG lCode, IUnknown * pUnk)
      {
        TRACE("Got notified! Cat = %d, Code = %d\n", lCat, lCode);
        if (pOnNotify)
          pOnNotify(lCat, lCode, pUnk);
        return S_OK;
      }
    long __stdcall raw_Notify(long lCat,long lCode,struct IUnknown *pUnk)
      {
      return Notify(lCat, lCode, pUnk);
      }
  };

}

static ZyluxCap::IZyluxCapPtr g_pCapApp = 0;
static ZyluxCap::CZyluxNotify *g_pNotify = 0;

IMPLEMENT_DYNCREATE(CZyluxZipDlg, CFormView);

CZyluxZipDlg::CZyluxZipDlg(CWnd **ppRef)
	: CFormView(CZyluxZipDlg::IDD)
{
	//{{AFX_DATA_INIT(CZyluxZipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  EnableAutomation();
  CoInitialize(NULL);
	m_pAutoProxy = NULL;
  m_pDlg = 0;
  m_uIdDlg = 0;
  m_ppRef = ppRef; // Save address of pointer from parent
  m_pTTYInfo = new CTTYInfo;
  m_pWndData = new CWndData(this, &m_pWndData, m_pTTYInfo);
  if (ppRef)
    *ppRef = this; // if pointer was provided, set it to our address
}

CZyluxZipDlg::~CZyluxZipDlg()
{
  if (g_pCapApp)
    {
    g_pCapApp->Quit();
    g_pCapApp.Release();
    }
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
  delete m_pWndData;
  delete m_pTTYInfo;
  if (m_ppRef)
    *m_ppRef = 0;
  CoUninitialize();
}

void CZyluxZipDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZyluxZipDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZyluxZipDlg, CFormView)
	//{{AFX_MSG_MAP(CZyluxZipDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_WM_CLOSE()
  ON_COMMAND(IDM_SITELIST, OnSiteList)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_SHOWDATA, OnShowData)
	ON_COMMAND(IDM_RUN_PROTOCOL_OPEN, OnRunProtocolOpen)
	ON_COMMAND(IDM_RUN_NAMES, OnRunNames)
	ON_COMMAND(IDM_RUN_PROTOCOL_NEW, OnRunProtocolNew)
	ON_COMMAND(IDM_CAPTURE, OnCapture)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentProtList)
  ON_MESSAGE(WM_DLGCLOSED, OnDialogClosed)
	ON_UPDATE_COMMAND_UI(IDM_SITELIST, OnUpdateMenuItem)
  ON_UPDATE_COMMAND_UI_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnUpdateMRUItem)
	ON_UPDATE_COMMAND_UI(IDM_RUN_NAMES, OnUpdateMenuItem)
	ON_UPDATE_COMMAND_UI(IDM_RUN_PROTOCOL_NEW, OnUpdateMenuItem)
	ON_UPDATE_COMMAND_UI(IDM_RUN_PROTOCOL_OPEN, OnUpdateMenuItem)
	ON_UPDATE_COMMAND_UI(IDM_CAPTURE, OnUpdateCapture)
	ON_UPDATE_COMMAND_UI(IDM_SHOWDATA, OnUpdateShowData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlg message handlers

// Fit frame to dialog size
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

  GetParentFrame()->RecalcLayout();
  ResizeParentToFit();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CFormView::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
/////////////////////////////////////////////////////////////////////////////
HCURSOR CZyluxZipDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnClose() 
{
	if (CanExit())
    {
    if (m_uIdDlg && m_pDlg) // make sure child dialogs get notified!
      m_pDlg->SendMessage(WM_CLOSE, 0, 0);
    if (!m_uIdDlg) // if children are all closed, close the form
      {
	    CFormView::OnClose();
      if (m_ppRef)
        *m_ppRef = 0;
      }
    }
}

BOOL CZyluxZipDlg::CanExit()
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

// Displays the Site List Editor
//////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnSiteList() 
{
  m_pDlg = new CDlgSiteList(this);
  OnDialogOpened(IDM_SITELIST, 0);
}

// Keeps certain menu items from working if a dialog is open
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnUpdateMenuItem(CCmdUI* pCmdUI) 
{
  BOOL bOn = 0 == m_uIdDlg && 0 == g_pCapApp;
  pCmdUI->Enable(bOn);
}

void CZyluxZipDlg::OnUpdateShowData(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_pWndData->GetSafeHwnd() != 0);
}

void CZyluxZipDlg::OnUpdateCapture(CCmdUI* pCmdUI) 
{
  BOOL bOn = 0 == m_uIdDlg && 0 == g_pCapApp;
  if (bOn)
    {
//    CRegKey cRK1;
//    if (ERROR_SUCCESS != cRK1.Open(HKEY_CLASSES_ROOT, "ZyluxCap.Application"))
//      bOn = FALSE;
    // cause menu to be redrawn
//    GetParent()->PostMessage(WM_NCACTIVATE, true, 0L);
    }
  pCmdUI->Enable(bOn);
}

// More work to do if the menu item is one of the MRU file items
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnUpdateMRUItem(CCmdUI* pCmdUI) 
{
  if (!m_uIdDlg && 0 == g_pCapApp)
    {
    CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
    CRecentFileList *pList = pApp->GetRecentFileList();
	  if (pList == NULL) // no MRU files
		  pCmdUI->Enable(FALSE);
	  else
		  pList->UpdateMenu(pCmdUI); // make menu refresh from MRU list
    }
  else
    pCmdUI->Enable(FALSE); // another dialog running, disable this item
}

// Open the Settings property page
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnSettings() 
{
  PSSettingsInfo tInfo = { m_pTTYInfo, m_pWndData };
  CPSSettings *pSettings = new CPSSettings(IDS_SETTINGS, this, 0, &tInfo);
  if (IDOK == pSettings->DoModal())
    {
    if (g_pCapApp)
      {
      // make sure the other app's serial setttings match this one's
      g_pCapApp->Baud     = m_pTTYInfo->dwBaudRate;
      g_pCapApp->StopBits = m_pTTYInfo->bStopBits;
      g_pCapApp->DBits    = m_pTTYInfo->bByteSize;
      g_pCapApp->FlowCtrl = m_pTTYInfo->bFlowCtrl;
      g_pCapApp->Parity   = m_pTTYInfo->bParity;
      g_pCapApp->Port     = m_pTTYInfo->bPort;
      }
    // this app can't be connected if the capture app is up
    else if (m_pTTYInfo->fConnected && !m_pTTYInfo->SetupConnection())
      {
      DWORD dwError = GetLastError();
      AfxMessageBox(_T("Failed to change serial settings."), MB_ICONEXCLAMATION);
      }
    }
  if (pSettings)
    delete pSettings;
}

// Call this whenever a dialog opens, to disable other menu items
// This has to be called by whatever function opens the dialog
/////////////////////////////////////////////////////////////////////////////
LRESULT CZyluxZipDlg::OnDialogOpened(WPARAM uIdOpen, LPARAM)
{
  m_uIdDlg = uIdOpen;
  CMenu *pMenu = GetParent()->GetMenu();
  for (int i = 0; i < _countof(uMenuIDMap); i++)
    {
    if (uMenuIDMap[i])
      {
      pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_GRAYED);
      }
    }

  // cause menu to be redrawn
  // Needed this for NT 4.0 only:
   GetParentFrame()->RedrawWindow(0,0,RDW_INVALIDATE|RDW_UPDATENOW|RDW_FRAME);
  //GetParentFrame()->SendMessage(WM_NCACTIVATE, true, 0L);
  // hide version info in static controls
  GetDlgItem(IDC_APPNAME)->ShowWindow(SW_HIDE);
  GetDlgItem(IDC_VERINFO)->ShowWindow(SW_HIDE);
  return 0;
}

// Call this whenever a dialog closes, to re-enable other menu items
// Modeless dialogs send a custom message when they close, which causes this
// Event handler to fire
/////////////////////////////////////////////////////////////////////////////
LRESULT CZyluxZipDlg::OnDialogClosed(WPARAM, LPARAM)
{
  UINT tUID = m_uIdDlg;
  m_uIdDlg = 0;
  m_pDlg = 0;
  CMenu *pMenu = GetParent()->GetMenu();
  for (int i = 0; i < _countof(uMenuIDMap); i++)
    {
    if (uMenuIDMap[i])
      {
      pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);
      }
    }

  // cause menu to be redrawn
  // Needed this for NT 4.0 only:
  GetParentFrame()->RedrawWindow(0,0,RDW_INVALIDATE|RDW_UPDATENOW|RDW_FRAME);
//  GetParentFrame()->SendMessage(WM_NCACTIVATE, true, 0L);
  // show version info in static controls
  GetDlgItem(IDC_APPNAME)->ShowWindow(SW_SHOW);
  GetDlgItem(IDC_VERINFO)->ShowWindow(SW_SHOW);
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CZyluxZipDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  static bool bAlreadyDoingThis = false;
  BOOL bResult = FALSE;

  if (!bAlreadyDoingThis)
    {
    bAlreadyDoingThis = true;

    if (m_pDlg)
      bResult = m_pDlg->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
    bAlreadyDoingThis = false;
    }
  if (bResult) return bResult;
	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnRunNames() 
{
  m_pDlg = new CDlgNameList(this);
  OnDialogOpened(IDM_RUN_NAMES, 0);
}

/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnRunProtocolNew() 
{
  m_pDlg = new CDlgRunProtocol(this, m_pTTYInfo);
  OnDialogOpened(IDM_RUN_PROTOCOL, 0);
  if (!((CDlgRunProtocol *)m_pDlg)->New())
    {
    AfxMessageBox(_T("Failed to create Run Protocol"), MB_OK|MB_ICONSTOP);
    m_pDlg->PostMessage(WM_CLOSE);
    }
}

/////////////////////////////////////////////////////////////////////////////
BOOL CZyluxZipDlg::DoRunProtocolOpen(LPCTSTR szFileName)
{
  m_pDlg = new CDlgRunProtocol(this, m_pTTYInfo);
  OnDialogOpened(IDM_RUN_PROTOCOL, 0);
  if (!((CDlgRunProtocol *)m_pDlg)->Open(szFileName))
    {
    AfxMessageBox(_T("Failed to open Run Protocol"), MB_OK|MB_ICONSTOP);
    m_pDlg->PostMessage(WM_CLOSE);
    return FALSE;
    }
  return TRUE;
}

// Open the run protocol editor with a file from disk
/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnRunProtocolOpen() 
{
  // Run File Open dialog to select filename
  CSingleDocTemplate cTemplate(IDR_ZYLTYPE, 0, 0, 0);
  CString csFilter, csExt;
  cTemplate.GetDocString(csFilter, CDocTemplate::filterName);
  cTemplate.GetDocString(csExt, CDocTemplate::filterExt);
  csFilter = csFilter + _T("|*") + csExt + _T("||");

  CString csName;
  CFileDialog mDlgFile(TRUE, 0, 0, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, csFilter);

  mDlgFile.m_ofn.lpstrTitle = _T("Choose a Run Protocol:");
  mDlgFile.m_ofn.lpstrFile = csName.GetBuffer(_MAX_PATH);
  mDlgFile.m_ofn.nMaxFile = _MAX_PATH;
  ZeroMemory(mDlgFile.m_ofn.lpstrFile, _MAX_PATH);
  int oldIndex = mDlgFile.m_ofn.nFilterIndex;

  // run the file dialog
  BOOL bResult = mDlgFile.DoModal() == IDOK ? TRUE : FALSE;
  csName.ReleaseBuffer();
  if (bResult)
    DoRunProtocolOpen(csName);
}

// MRU file list implementation for run protocols
/////////////////////////////////////////////////////////////////////////////
BOOL CZyluxZipDlg::OnOpenRecentProtList(UINT nID)
{
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  CRecentFileList *pList = pApp->GetRecentFileList();
	ASSERT(pList != NULL);
	ASSERT(nID >= ID_FILE_MRU_FILE1);
	ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)pList->GetSize());
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*pList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(LPCTSTR)(*pList)[nIndex]);

	if (!DoRunProtocolOpen((*pList)[nIndex]))
		pList->Remove(nIndex);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
/* static */ void CZyluxZipDlg::OnNotify(LONG lCat, LONG lCode, IUnknown * pUnk)
{
  using namespace ZyluxCap;
  if ((0 != g_pNotify) && (ZYNOTIFY_APP == lCat) && (ZYCODE_COMPLETE == lCode))
    {
    // indirect way of calling OnDialogClosed, since this is a static function
    if (g_pNotify->m_pZipDlg)
      g_pNotify->m_pZipDlg->PostMessage(WM_DLGCLOSED, 0);
    g_pCapApp->UnAdvise(g_pNotify);
    g_pNotify->Release();
    g_pNotify = 0;
    g_pCapApp.Release();
    }
}

/////////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnCapture() 
{
  if (g_pNotify)
    return;
  OnDialogOpened(IDM_CAPTURE, 0);
  if (S_OK == g_pCapApp.CreateInstance(_T("ZyluxCap.Application")))
    {
    try 
      {
      g_pNotify = new CComObject<ZyluxCap::CZyluxNotify>;
        {
        // set derived class' pointer here
        g_pNotify->pOnNotify = OnNotify;
        g_pNotify->m_pZipDlg = this;
        g_pCapApp->Advise(g_pNotify);
        CRect cRect;
        GetParentFrame()->GetClientRect(&cRect);
        GetParentFrame()->ClientToScreen(&cRect);
        g_pCapApp->CenterOnRect(cRect.left, cRect.top, cRect.right, cRect.bottom);
        // make sure the other app's serial setttings match this one's
        g_pCapApp->Baud     = m_pTTYInfo->dwBaudRate;
        g_pCapApp->StopBits = m_pTTYInfo->bStopBits;
        g_pCapApp->DBits    = m_pTTYInfo->bByteSize;
        g_pCapApp->FlowCtrl = m_pTTYInfo->bFlowCtrl;
        g_pCapApp->Parity   = m_pTTYInfo->bParity;
        g_pCapApp->Port     = m_pTTYInfo->bPort;
        }
      }
    catch (_com_error &e)
      {
      }
    }
  else
    OnDialogClosed(IDM_CAPTURE, 0);
}

// Shows or hides the data display window
//////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnShowData() 
{
  if (!m_pWndData->GetSafeHwnd()) // if not shown, show
    {
    m_pWndData->Create(IDD_DATAWIN, this);
    m_pTTYInfo->m_hWndTerm = m_pWndData->GetSafeHwnd();
    }
  else // if shown, hide
    {
    m_pWndData->SendMessage(WM_CLOSE);
    }
}

// This is here to check/uncheck the "Show Data" menu item
// in the system menu
//////////////////////////////////////////////////////////////////////////
void CZyluxZipDlg::OnInitMenu(CMenu* pMenu) 
{
	CMenu* pSysMenu = GetParentFrame()->GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
    {
    CCmdUI cmdUI;
    cmdUI.m_nIndexMax = pSysMenu->GetMenuItemCount();
    for (UINT n = 0; n < pSysMenu->GetMenuItemCount(); ++n) 
      {
      if (pSysMenu->GetMenuItemID(n) != IDM_SHOWDATA)
        continue;
      cmdUI.m_nIndex = n;
      cmdUI.m_nID = pSysMenu->GetMenuItemID(n);
      cmdUI.m_pMenu = pSysMenu;
      cmdUI.DoUpdate(this, FALSE);  
      }
    }
	CFormView::OnInitMenu(pMenu);
}
