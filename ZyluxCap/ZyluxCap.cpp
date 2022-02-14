/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// ZyluxCap.cpp : Defines the class behaviors for the application.
//
/////////////////////////////////////////////////////////////////////////////
/*
* $History: ZyluxCap.cpp $ * 
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 6/08/00    Time: 8:18a
// Updated in $/ZyluxCap/2.0
// Add a pointer check in message string handler
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 5/15/00    Time: 11:32a
// Updated in $/ZyluxCap/2.0
// Only allow one instance of the program to be started
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 4/14/00    Time: 10:00a
 * Updated in $/ZyluxCap/2.0
 * Add message handler for custom quit message sent from TTY monitor code
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:13p
 * Updated in $/ZyluxCap/2.0
 * Don't delete mainframe from ExitInstance; letting it delete itself is
 * safer and avoids a debug warning during shutdown
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:19a
 * Updated in $/ZyluxCap/2.0
 * Remove custom code to register interface, just use CComModule instead
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:15a
 * Updated in $/ZyluxCap/2.0
 * Add code to register typelib and notifier interface
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:06a
 * Updated in $/ZyluxCap/1.2
 * Add handler to pass WM_SETMESSAGESTRING from other thread along to
 * mainframe
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:26a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlbase.h>
#include <statreg.h>
#include <afxpriv.h>
#include "ZyluxCap.h"
#include "mainframe.h"
#include "zyluxtlb.h"
#include "zyluxtlb.c"
#include "messages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZyluxCapApp

BEGIN_MESSAGE_MAP(CZyluxCapApp, CWinApp)
	//{{AFX_MSG_MAP(CZyluxCapApp)
  ON_THREAD_MESSAGE(WM_SETMESSAGESTRING, OnMessageString)
  ON_THREAD_MESSAGE(WM_APPQUIT, OnAppQuit)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZyluxCapApp construction

CZyluxCapApp::CZyluxCapApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CZyluxCapApp object

CZyluxCapApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CZyluxCapApp initialization

// Check to see if this is the first/only instance of the program
/////////////////////////////////////////////////////////////////////////////
BOOL IsFirstInstance(HINSTANCE hInstance)
{
  // define a global semaphore to see if an instance is already running
  HANDLE gbl_hSem = 
    CreateSemaphore(NULL, 0, 1, "ZyluxCapRunning");
  // if the semaphore handle returned is valid, but the last error
  // indicates that it already exists, then activate the previous instance
  // and kill this instance
  if (gbl_hSem != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
    {
    AfxSetResourceHandle(hInstance);
    CloseHandle(gbl_hSem);
    CString cStr;
    cStr.LoadString(IDR_MAINFRAME);
    HWND hWnd = FindWindow(NULL, cStr);
    if (hWnd != NULL)
      {
      if (IsIconic(hWnd))
        ShowWindow(hWnd, SW_SHOWNORMAL);
      SetForegroundWindow(hWnd);
      ShowWindow(hWnd, SW_SHOWNORMAL);
      ShowOwnedPopups(hWnd, TRUE);
	    SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
		               SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
      }
    return 0; // flag to kill this instance
    }
  else
    return 1; // flag to keep runnning this instance
}

BOOL CZyluxCapApp::InitInstance()
{
  if (!IsFirstInstance(AfxGetInstanceHandle()))
    return FALSE;

  // Initialize OLE libraries
  if (!AfxOleInit())
    {
    AfxMessageBox(IDP_OLE_INIT_FAILED);
    return FALSE;
    }
  
  CoInitialize(NULL); // initialize COM so can call Excel via automation
  AfxEnableControlContainer();
  
  SetRegistryKey(_T("Zylux Corp"));
  
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.
  
#ifdef _AFXDLL
  Enable3dControls();     // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif
  
    CComModule _Module;
    _Module.Init(0, AfxGetInstanceHandle(), &LIBID_ZyluxCap);
    _Module.RegisterTypeLib();
    _Module.UpdateRegistryFromResourceD(IDR_ZNOTIFY, TRUE);

   bool bAutomated = false;
  // Parse the command line to see if launched as OLE server
  if (RunEmbedded() || RunAutomated())
    {
    // Register all OLE server (factories) as running.  This enables the
    //  OLE libraries to create objects from other applications.
    COleTemplateServer::RegisterAll();
    bAutomated = true;
    }
  else
    {
    // When a server application is launched stand-alone, it is a good idea
    //  to update the system registry in case it has been damaged.
    COleObjectFactory::UpdateRegistryAll();
    }
  
  // create main Frame window
  CMainFrame* pMainFrame = new CMainFrame;
  pMainFrame->m_bAutomated = bAutomated;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;
  m_pMainWnd = pMainFrame;

  // The main window has been initialized, so show and update it.
  if (!bAutomated)
    {
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();
    }

  return TRUE;
}

int CZyluxCapApp::ExitInstance() 
{
  CoUninitialize(); // clean up COM as required by OS
  return CWinApp::ExitInstance();
}

void CZyluxCapApp::OnMessageString(UINT wParam, LONG lParam)
{
  CWnd *pMainWnd = AfxGetMainWnd();
  if (pMainWnd)
	  pMainWnd->SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
}

void CZyluxCapApp::OnAppQuit(UINT wParam, LONG lParam)
{
  if (m_pMainWnd)
    m_pMainWnd->PostMessage(WM_CLOSE, 0, 0);
}
