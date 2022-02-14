// QM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "QM.h"

#include "GridFrm.h"
#include "QMDoc.h"
#include "QMView.h"
#include "QMEditDlg.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQMApp

BEGIN_MESSAGE_MAP(CQMApp, CProtocolApp)
	//{{AFX_MSG_MAP(CQMApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQMApp construction

CQMApp::CQMApp() : CProtocolApp(IDR_MAINFRAME, IDR_QMTYPE, 0)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CQMApp::~CQMApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQMApp object

CQMApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
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

BOOL CAboutDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	static bool normal = true;
	static CString m_normal_str;
	static CString m_other_str;
	if ((LOWORD(wParam) == IDC_STATIC_PROGICON) &&
		(HIWORD(wParam) == STN_DBLCLK) && 
		(GetKeyState(VK_CONTROL) & 0x8000))
	{
		if (m_normal_str.IsEmpty())
		{
			GetDlgItemText(IDC_STATIC_PROGSTR, m_normal_str);
		}
		if (m_other_str.IsEmpty())
		{
			m_other_str = _strrev("samohT kraM yb demmargorP");
		}
		SetDlgItemText(IDC_STATIC_PROGSTR, normal ? m_other_str : m_normal_str);
		normal = !normal;
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set the version string
	COptions options;
	CString ver;
	ver.Format("Version %s", options.m_version);
	SetDlgItemText(IDC_STATIC_VERSION, ver);
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CQMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	FB12Inhibit();
	aboutDlg.DoModal();
	FB12Uninhibit();
}

/////////////////////////////////////////////////////////////////////////////
// CQMApp commands

BOOL CQMApp::ModeGen()
{
	// Call the base class
	if (!CProtocolApp::ModeGen())
	{
		return FALSE;
	}

	if (!m_pps.Save(_T("Quick Measurement")))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CQMApp::ModeRun()
{
	// Load the PPS data
	if (!m_pps.Load(m_filetitle))
	{
		return FALSE;
	}

	// Call the base class
	return CProtocolApp::ModeRun();
}

BOOL CQMApp::ModeView()
{
	// Call the base class
	if (!CProtocolApp::ModeView())
	{
		return FALSE;
	}

	// To Do: Change the message on the status bar
	//m_pMainFrame->SetMessageText(IDS_VIEW_IDLEMESSAGE);

	return TRUE;
}

BOOL CQMApp::ModeRunView()
{
	// Call the base class
	if (!CProtocolApp::ModeRunView())
	{
		return FALSE;
	}

	// Init OLE/COM
	AfxOleInit();

	// Run and View mode require Objective Grid
	GXInit();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_grid_template = new CMultiDocTemplate(
		(m_mode == APPMODE_RUN) ? IDR_QMTYPE : IDR_QMVIEWTYPE,
		RUNTIME_CLASS(CQMDoc),
		RUNTIME_CLASS(CGridFrame), // custom MDI child frame
		RUNTIME_CLASS(CQMView));
	AddDocTemplate(m_grid_template);

	// create main MDI Frame window
	m_pMainFrame = new CMainFrame;
	if (!m_pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = m_pMainFrame;

	// The main window has been initialized, so show and update it.
	if (!m_pMainFrame->m_placement_loaded)
	{
		m_pMainFrame->ShowWindow(m_nCmdShow);
	}
	m_pMainFrame->UpdateWindow();

	// Create the document
	if (m_mode == APPMODE_RUN)
	{
		// We're running, so create a new document
		m_grid_template->OpenDocumentFile(NULL);
	}
	else
	{
		// We're editing, so load the existing document
		m_grid_template->OpenDocumentFile(m_filepath);
	}

	// Was the document created okay?
	if (m_pDoc)
	{
		if (m_pDoc->m_grid_placement.length == 0)
		{
			m_pMainFrame->MDIMaximize(m_pDoc->m_grid_frame);
		}
		else
		{
			m_pDoc->m_grid_frame->SetWindowPlacement(&m_pDoc->m_grid_placement);
		}
	}

	return TRUE;
}

BOOL CQMApp::ModeEdit()
{
	// Call the base class
	if (!CProtocolApp::ModeEdit())
	{
		return FALSE;
	}

	// Load the specified PPS file
	if (!m_pps.Load(m_filetitle))
	{
		return FALSE;
	}

	// Let the user edit the PPS file
	CQMEditDlg dlg(m_pps, m_filetitle);

	dlg.DoModal();

	return TRUE;
}
