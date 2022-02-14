// Protocol.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Protocol.h"
#include "General.h"
#include "ProtCmdLineInfo.h"
#include "ProtocolFrame.h"
#include "ActWatch.h"
//#include "SCSerialNumber.h"
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtocolApp

BEGIN_MESSAGE_MAP(CProtocolApp, CWinApp)
	//{{AFX_MSG_MAP(CProtocolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_MESSAGE(WM_FB12, OnFB12Event)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolApp construction

CProtocolApp::CProtocolApp(UINT main_icon_id, UINT doc_icon_id, UINT graph_icon_id)
	: m_main_icon_id(main_icon_id), m_doc_icon_id(doc_icon_id),
	m_graph_icon_id(graph_icon_id), m_mode(APPMODE_NONE), m_port(1),
	m_baud(9600), m_beep(false), m_pFB12Device(NULL), m_pDoc(NULL),
	m_graph_template(NULL)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pShutdownEvent = NULL;
	m_pInstanceEvent = NULL;
	m_pActivationWatch = NULL;
}

CProtocolApp::~CProtocolApp()
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

	if (m_pFB12Device)
	{
		delete m_pFB12Device;
		m_pFB12Device = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProtocolApp initialization

BOOL CProtocolApp::InitInstance()
{
	TCHAR locale[256];
	if (GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, locale, 256) > 0)
	{
		setlocale(LC_ALL, locale);
	}

	m_pInstanceEvent = new CEvent(FALSE, FALSE, AfxGetAppName());
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		m_pInstanceEvent->SetEvent();
		return FALSE;
	}

	m_pShutdownEvent = new CEvent();
	m_pActivationWatch = (CActivationWatcher*)
			AfxBeginThread(RUNTIME_CLASS(CActivationWatcher));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Softstep\\STLS"));
/*
	// Check for valid serial number
	bool valid_sn = false;
	HKEY key;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("Software\\Softstep\\Protocol Manager\\Settings"),
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		UCHAR serial_str[11];
		//memset(serial_str, 0, 11);
		DWORD type = REG_SZ;
		DWORD size = 11;
		if ((RegQueryValueEx(key, _T("SerialNumber"), NULL, &type, serial_str, &size) == ERROR_SUCCESS)
			&& (CSCSerialNumber::ExtractSerialNumber(serial_str) >= 2))
		{
			valid_sn = true;
		}
		RegCloseKey(key);
	}
	if (!valid_sn)
	{
		SCMessageBox(_T("Invalid serial number detected.\n\nRun the Protocol Manager to enter the\nsoftware serial number."));
		return FALSE;
	}
*/
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Parse command line for standard shell commands, DDE, file open
	CProtCmdLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	// Get our startup parameters
	m_filepath = cmdInfo.m_strFileName;
	m_mode = cmdInfo.m_mode;

	//m_port = cmdInfo.m_port;
	//m_baud = cmdInfo.m_baud;
	//m_workdir = cmdInfo.m_workdir;
	//m_beep = cmdInfo.m_beep;

	m_port = m_options.m_lumiport;
	m_baud = m_options.m_lumibaud;
	m_workdir = m_options.m_workdir;
	m_beep = m_options.m_beep;

	// Get the filename and file title
	m_filename = SCGetFileName(m_filepath);
	m_filetitle = SCGetFileTitle(m_filename);

	// Setup some path and logfile parameters
	m_maindir = SCGetCurrentDir();
	m_protocoldir = m_maindir + "\\protocols";
	m_logpath = m_maindir + "\\logfile.mds";

	//CString sh;
	//sh.Format("filepath: %s\nfilename: %s\nfiletitle: %s",
	//	(LPCTSTR)m_filepath, (LPCTSTR)m_filename, (LPCTSTR)m_filetitle);
	//AfxMessageBox(sh);

	//CString sh;
	//sh.Format("cmdline: %s\nmode: %s\nfile: %s\nport: %d\nbaud: %ld",
	//	m_lpCmdLine,
	//	(m_mode == APPMODE_RUN) ? "RUN" :
	//	(m_mode == APPMODE_VIEW) ? "VIEW" :
	//	(m_mode == APPMODE_EDIT) ? "EDIT" :
	//	(m_mode == APPMODE_GEN) ? "GEN" : "NONE",
	//	(LPCTSTR)m_filename, m_port, m_baud);
	//AfxMessageBox(sh);

	// TEMPORARY FOR TESTING
	//m_mode = APPMODE_GEN;
	//m_filename = "Quick Measurement.pps";
	//m_port = 2;
	//m_baud = 9600;

	BOOL bRet = FALSE;
	switch (m_mode)
	{
	case APPMODE_GEN:
		bRet = ModeGen();
		break;

	case APPMODE_EDIT:
		bRet = ModeEdit();
		break;

	case APPMODE_RUN:
		bRet = ModeRun();
		break;

	case APPMODE_VIEW:
		bRet = ModeView();
		break;

	default:
		SCMessageBox("No run mode specified.");
		break;
	}

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CProtocolApp commands

LRESULT CProtocolApp::OnFB12Event(WPARAM wParam, LPARAM lParam)
{
	if (m_pDoc)
	{
		switch(wParam)
		{
		case FB12Device::FB12_MSG_DOORCHANGE:
			m_pDoc->FB12DoorChange((VARIANT_BOOL)lParam);
			break;

		case FB12Device::FB12_MSG_NEWRLU:
			m_pDoc->FB12NewRLU(lParam);
			break;

		case FB12Device::FB12_MSG_ERRORCHANGE:
			m_pDoc->FB12ErrorChange(lParam);
			break;

		case FB12Device::FB12_MSG_COMMUNICATINGCHANGE:
			m_pDoc->FB12CommunicatingChange((VARIANT_BOOL)lParam);
			break;

		case FB12Device::FB12_MSG_OPERATINGCHANGE:
			m_pDoc->FB12OperatingChange((VARIANT_BOOL)lParam);
			break;
		}
	}

	return TRUE;
}

void CProtocolApp::FB12Inhibit()
{
	if (m_pFB12Device)
	{
		m_pFB12Device->InhibitMsg();
	}
}

void CProtocolApp::FB12Uninhibit()
{
	if (m_pFB12Device)
	{
		m_pFB12Device->UninhibitMsg();
	}
}

bool CProtocolApp::FB12IsInibited() const
{
	if (m_pFB12Device)
	{
		return m_pFB12Device->IsInhibitMsg();
	}
	else
	{
		return true;
	}
}

BOOL CProtocolApp::ModeGen()
{
	return TRUE;
}

BOOL CProtocolApp::ModeRun()
{
	if (!ModeRunView())
	{
		return FALSE;
	}

	// Start FB12Device uninhibited
	m_pFB12Device = new FB12Device(WM_FB12, false);
	if (m_pFB12Device == NULL)
	{
		SCMessageBox("Unable to create FB12 Device object.");
		return FALSE;
	}
	if (!m_pFB12Device->Start(m_port, m_baud))
	{
		SCMessageBox("Unable to start FB12 serial communications.");
		return FALSE;
	}

	return TRUE;
}

BOOL CProtocolApp::ModeView()
{
	// To Do: Disable New, Save, Save As menus

	return ModeRunView();
}

BOOL CProtocolApp::ModeRunView()
{
	// Set the current working directory
	SetCurrentDirectory(m_workdir);

	return TRUE;
}

BOOL CProtocolApp::ModeEdit()
{
	return TRUE;
}

BOOL CProtocolApp::OnIdle(LONG lCount)
{
	// TODO: Add your specialized code here and/or call the base class
	CProtocolFrame* mainframe = (CProtocolFrame*)m_pMainWnd;
	if ((lCount == 0) && (mainframe->GetLastStatusID() == AFX_IDS_IDLEMESSAGE))
	{
		mainframe->CMDIFrameWnd::SetMessageText(mainframe->m_status_str);
	}

	return CWinApp::OnIdle(lCount);
}
