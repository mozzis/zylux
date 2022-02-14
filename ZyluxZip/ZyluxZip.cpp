// ZyluxZip.cpp : Defines the class behaviors for the application.
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: ZyluxZip.cpp $ * 
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:58p
 * Updated in $/ZyluxZip
 * Move Set/GetInt/StringSetting to app module so they can be reused
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:21p
 * Updated in $/ZyluxZip
 * Add ATL support to make using the notify interface easier
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/15/00    Time: 2:00p
 * Updated in $/ZyluxZip
 * Load profile settings (MRU list) in InitInstance
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZyluxZip.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipApp

BEGIN_MESSAGE_MAP(CZyluxZipApp, CWinApp)
	//{{AFX_MSG_MAP(CZyluxZipApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipApp construction

CZyluxZipApp::CZyluxZipApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CZyluxZipApp object

CZyluxZipApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipApp initialization

BOOL CZyluxZipApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	if (!InitATL())
		return FALSE;

	AfxEnableControlContainer();

  SetRegistryKey(_T("Zylux Corp"));
	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

  // Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);

	}
	else
	{
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
		COleObjectFactory::UpdateRegistryAll();
	}

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

	
CZyluxZipModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG CZyluxZipModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CZyluxZipModule::Lock()
{
	AfxOleLockApp();
	return 1;
}


int CZyluxZipApp::ExitInstance()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}

	return CWinApp::ExitInstance();

}

BOOL CZyluxZipApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}

// helpers for reading/writing settings

int CZyluxZipApp::GetIntSetting(UINT uIDSet, int nDefault)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return GetProfileInt(csSect, csEnt, nDefault);
}

int CZyluxZipApp::SetIntSetting(UINT uIDSet, int nSetVal)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return WriteProfileInt(csSect, csEnt, nSetVal);
}

CString CZyluxZipApp::GetStringSetting(UINT uIDSet, LPCTSTR sDefault)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_TTYSETTINGS);
  csEnt.LoadString(uIDSet);
  return GetProfileString(csSect, csEnt, sDefault);
}

int CZyluxZipApp::SetStringSetting(UINT uIDSet, LPCTSTR sSetVal)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_TTYSETTINGS);
  csEnt.LoadString(uIDSet);
  return WriteProfileString(csSect, csEnt, sSetVal);
}

