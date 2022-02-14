// Protocol Manager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Protocol Manager.h"
#include "PMDlg.h"
#include "General.h"
#include "PMActWatch.h"
//#include "SCSerialNumber.h"
//#include "SerialDialog.h"
#include <objbase.h>
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPMApp

BEGIN_MESSAGE_MAP(CPMApp, CWinApp)
	//{{AFX_MSG_MAP(CPMApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPMApp construction

CPMApp::CPMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pShutdownEvent = NULL;
	m_pInstanceEvent = NULL;
	m_pActivationWatch = NULL;
}

CPMApp::~CPMApp()
{
	// if we've not shutdown, do it!
	if (m_pShutdownEvent != NULL)
	{
		m_pShutdownEvent->SetEvent();
		if (m_pActivationWatch != NULL)
			::WaitForSingleObject(m_pActivationWatch->m_hThread, INFINITE);
		delete m_pShutdownEvent;
		m_pShutdownEvent = NULL;
	}

	// kill the instance handle, too
	if (m_pInstanceEvent != NULL)
	{
		delete m_pInstanceEvent;
		m_pInstanceEvent = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPMApp object

CPMApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPMApp initialization

BOOL CPMApp::InitInstance()
{
	TCHAR locale[256];
	if (GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, locale, 256) > 0)
	{
		setlocale(LC_ALL, locale);
	}

	CoInitialize(NULL);

	m_pInstanceEvent = new CEvent(FALSE, FALSE, AfxGetAppName());
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		m_pInstanceEvent->SetEvent();
		return FALSE;
	}

	m_pShutdownEvent = new CEvent();
	m_pActivationWatch = (CPMActivationWatcher*)
			AfxBeginThread(RUNTIME_CLASS(CPMActivationWatcher));
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Set the registry key to the company name
	SetRegistryKey(_T("Softstep\\STLS"));
/*
	// Read the installation directory
	CString main_dir = GetProfileString(_T("Settings"), _T("MainDir"), SCGetCurrentDir());

	// Read the port and baud from the registry
	short port = GetProfileInt(_T("Serial"), _T("Port"), 1);
	long baud = GetProfileInt(_T("Serial"), _T("Baud"), 9600);
	CString work_dir = GetProfileString(_T("Settings"), _T("WorkDir"), main_dir + "\\Data");
	bool beep = GetProfileInt(_T("Settings"), _T("Beep"), TRUE) ? true : false;
*/
/*
	// Check the serial number
	CString serial_string = GetProfileString(_T("Settings"), _T("SerialNumber"), "");
	if (!(CSCSerialNumber::ExtractSerialNumber(serial_string) >= 2))
	{
		CSerialDialog serial_dlg((serial_string.GetLength() == 0) ? true : false);
		if (serial_dlg.DoModal() == IDOK)
		{
			WriteProfileString(_T("Settings"), _T("SerialNumber"),
				serial_dlg.m_serial_string);
		}
		else
		{
			return FALSE;
		}
	}
*/
	// Handle command line
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	//AfxMessageBox(cmdInfo.m_strFileName);

	// Build and show the main dialog
	CPMDlg dlg(cmdInfo.m_strFileName);
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Store the port and baud in the registry
/*
	WriteProfileInt(_T("Serial"), _T("Port"), dlg.m_port);
	WriteProfileInt(_T("Serial"), _T("Baud"), dlg.m_baud);
	WriteProfileString(_T("Settings"), _T("WorkDir"), dlg.m_workdir);
	WriteProfileInt(_T("Settings"), _T("Beep"), beep ? TRUE : FALSE);
*/

	CoUninitialize();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
