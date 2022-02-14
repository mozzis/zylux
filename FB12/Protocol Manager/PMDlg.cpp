// PMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol Manager.h"
#include "PMDlg.h"
#include "OptDlg.h"
#include "General.h"
#include <mmsystem.h>
#include <shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// The following define, when set, allows you to create the
// serial number file when the application's About... button
// is pressed.  A dialog is presented for you to chose the
// name and location of the serial numbers file.
//#define SERNUM_MAKEFILE

#ifdef SERNUM_MAKEFILE
#include "SCSerialNumber.h"
#endif

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

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPMDlg dialog

CPMDlg::CPMDlg(CString filename, CWnd* pParent /*=NULL*/)
	: CDialog(CPMDlg::IDD, pParent), m_filename(filename)
	//, m_waiting(false)
	//, m_timer_id(0)
{
	//{{AFX_DATA_INIT(CPMDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Set the version number and save it
	//m_options.m_version = "1.1";
	//m_options.Write();
}

CPMDlg::~CPMDlg()
{
}

void CPMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPMDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPMDlg, CDialog)
	//{{AFX_MSG_MAP(CPMDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_LBN_SELCHANGE(IDC_LIST_PROTOCOLS, OnSelchangeListProtocols)
	ON_BN_CLICKED(IDC_RUN, OnProtocolRun)
	ON_BN_CLICKED(IDC_EDIT, OnProtocolEdit)
	ON_BN_CLICKED(IDC_RETRIEVE, OnRetrieve)
	ON_BN_CLICKED(IDC_DELETE, OnProtocolDelete)
	ON_BN_CLICKED(ID_APP_ABOUT, OnAppAbout)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST_PROTOCOLTYPES, OnSelchangeListProtocoltypes)
	ON_BN_CLICKED(IDC_CREATE, OnProtocolCreate)
	ON_COMMAND(IDC_VIEWFILE, OnViewfile)
	ON_COMMAND(IDC_PROTOCOLDONE, OnProtocoldone)
	//}}AFX_MSG_MAP

	ON_LBN_DBLCLK(IDC_LIST_PROTOCOLS, OnProtocolRun)
	ON_LBN_DBLCLK(IDC_LIST_PROTOCOLTYPES, OnProtocolCreate)
	ON_WM_DROPFILES()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPMDlg message handlers

BOOL CPMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DragAcceptFiles();

	// Load some stuff from the registry
	WINDOWPLACEMENT placement;
	if (SCGetAppProfileBinary("STLS\\Protocol Manager", "Settings", "DlgFrame",
						   (BYTE*)&placement, sizeof(placement)))
	{
		SetWindowPlacement(&placement);
	}
/*
	HKEY key;
	CString key_str;
	key_str.Format("Software\\Softstep\\%s\\Settings", AfxGetApp()->m_pszAppName);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T(key_str),
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		DWORD type;
		DWORD size;
		WINDOWPLACEMENT placement;

		// Load the grid position information
		type = REG_BINARY;
		size = sizeof(placement);
		if (RegQueryValueEx(key, _T("DlgFrame"), NULL, &type, (BYTE*)&placement, &size)
			== ERROR_SUCCESS)
		{
			SetWindowPlacement(&placement);
		}

		RegCloseKey(key);
	}
*/

	MySize();

//	m_timer_id = timeSetEvent(1000, 1000, TimerCallback, (DWORD)this, TIME_PERIODIC);
//	if (m_timer_id == 0)
//	{
//		AfxMessageBox("Could not allocate timer.");
//		return FALSE;
//	}

	// Change to the working directory
	SCSetCurrentDir(m_options.m_workdir);

	// Build the initial protocol array
	BuildProtocolArray();

	// View a file if there is one to view
	//PostMessage(WM_PM_VIEWFILE);
	AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, IDC_VIEWFILE, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAppAbout();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CPMDlg::OnDestroy()
{
	//if (m_timer_id != 0)
	//{
	//	timeKillEvent(m_timer_id);
	//}

	WinHelp(0L, HELP_QUIT);

	// Save the window placement
	WINDOWPLACEMENT placement;
	memset(&placement, 0, sizeof(placement));
	placement.length = sizeof(placement);
	if (GetWindowPlacement(&placement))
	{
		SCWriteAppProfileBinary("STLS\\Protocol Manager", "Settings", "DlgFrame",
							   (BYTE*)&placement, sizeof(placement));

/*
		HKEY key;
		CString key_str;
		key_str.Format("Software\\Softstep\\%s\\Settings", AfxGetApp()->m_pszAppName);
		if (RegOpenKeyEx(HKEY_CURRENT_USER, _T(key_str),
			0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
		{
			// Save the grid position information
			RegSetValueEx(key, _T("DlgFrame"), NULL, REG_BINARY,
				(BYTE*)&placement, sizeof(placement));

			RegCloseKey(key);
		}
*/
	}

	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPMDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPMDlg::OnOptions() 
{
	// TODO: Add your control notification handler code here
	COptDlg dlg(m_options);
	if (dlg.DoModal() == IDOK)
	{
		m_options = dlg.m_options;
		m_options.Write();
	}
}

bool CPMDlg::BuildProtocolArray()
{
	// Get the pointer to the list box
	CListBox* pProt = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLS);
	ASSERT(pProt != NULL);
	CListBox* pType = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLTYPES);
	ASSERT(pType != NULL);

	// Find the current selection
	int curselprot = pProt->GetCurSel();
	int curseltype = pType->GetCurSel();
	CString curstrprot;		// holds the name of the currently selected protocol
	CString curstrtype;		// holds the name of the currently selected protocol
	if ((curselprot != LB_ERR) && (curselprot <= m_protocols.GetSize()))
	{
		curstrprot = m_protocols[curselprot].m_name;
	}
	if ((curseltype != LB_ERR) && (curseltype <= m_protocol_types.GetSize()))
	{
		curstrtype = m_protocol_types[curseltype].m_name;
	}

	CString curdir = SCSetCurrentDir(m_options.m_maindir);

	// Build a list of protocol filenames from the drive
	CArray<CString, CString&> names;
	int num_names = CPPS::BuildProtocolArray(names, true);

	// Remember how many protocol there were
	int old_count = m_protocols.GetSize();

	// Copy the old list
	CArray<CProtocolItem, CProtocolItem&> m_old_protocols;
	m_old_protocols.SetSize(old_count);
	int i;
	for (i = 0; i < old_count; i++)
	{
		m_old_protocols[i] = m_protocols[i];
	}

	// Remove any existing protocols
	m_protocols.RemoveAll();
	m_protocol_types.RemoveAll();

	// Build the protocol array from the given filenames.
	// Make sure they are sorted with base protocols first,
	// then sorted by name.
	CString filepath;
	CString err_str;
	CFile pps_file;
	CPPS pps;
	for (i = 0; i < num_names; i++)
	{
		filepath = "protocols\\" + names[i];
		if (pps_file.Open(filepath, CFile::modeRead))
		{
			if (pps.Read(pps_file))
			{
				if (!pps.IsRunable())
				{
					InsertProtocolType(names[i], pps);
				}
				else
				{
					InsertProtocol(names[i], pps);
				}
			}
			else
			{
				err_str.Format("Unable to read file \"%s\"!", names[i]);
				AfxMessageBox(err_str);
			}
			pps_file.Close();
		}
		else
		{
			err_str.Format("Unable to open file \"%s\"!", names[i]);
			AfxMessageBox(err_str);
		}
	}

	SCSetCurrentDir(curdir);

	// Fill the listbox on the dialog
	pProt->ResetContent();		// delete any existing content
	curselprot = 0;
	for (i = 0; i < m_protocols.GetSize(); i++)
	{
		pProt->AddString(m_protocols[i].m_name);
		if (m_protocols[i].m_name == curstrprot)
		{
			curselprot = i;
		}
	}
	pType->ResetContent();		// delete any existing content
	curseltype = 0;
	for (i = 0; i < m_protocol_types.GetSize(); i++)
	{
		pType->AddString(m_protocol_types[i].m_name);
		if (m_protocol_types[i].m_name == curstrtype)
		{
			curseltype = i;
		}
	}

	// Select the last selected protocol in the list
	pType->SetCurSel(curseltype);
	OnSelchangeListProtocoltypes();
	if (old_count < m_protocols.GetSize())
	{
		// Find the new protocol and select it
		curselprot = -1;  // start with no selection

		for (i = 0; i < m_protocols.GetSize(); i++)
		{
			// Search the old list to see if this protocol name is in it or not
			bool found = false;
			int j;
			for (j = 0; j < old_count; j++)
			{
				if (m_protocols[i].m_name == m_old_protocols[j].m_name)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				// This is the new protocol name, so select it
				curselprot = i;
				break;
			}
		}
	}
	pProt->SetCurSel(curselprot);
	OnSelchangeListProtocols();

	return true;
}

void CPMDlg::InsertProtocol(CString& filename, CPPS& pps)
{
	CProtocolItem new_item(filename.Left(filename.GetLength() - 4), pps);
	int len = m_protocols.GetSize();
	for (int i = 0; i < len; i++)
	{
		if (new_item < m_protocols[i])
		{
			m_protocols.InsertAt(i, new_item);
			break;
		}
	}
	if (i >= len)
	{
		m_protocols.Add(new_item);
	}
}

void CPMDlg::InsertProtocolType(CString& filename, CPPS& pps)
{
	CProtocolItem new_item(filename.Left(filename.GetLength() - 4), pps);
	int len = m_protocol_types.GetSize();
	for (int i = 0; i < len; i++)
	{
		if (new_item < m_protocol_types[i])
		{
			m_protocol_types.InsertAt(i, new_item);
			break;
		}
	}
	if (i >= len)
	{
		m_protocol_types.Add(new_item);
	}
}

void CPMDlg::OnSelchangeListProtocoltypes() 
{
	// TODO: Add your control notification handler code here
	
	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLTYPES);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	// Update the comment
	CWnd* button = GetDlgItem(IDC_CREATE);
	ASSERT(button != NULL);
	CWnd* comment = GetDlgItem(IDC_EDIT_TYPECOMMENT);
	ASSERT(comment != NULL);
	if ((sel == LB_ERR) || (sel >= m_protocol_types.GetSize()))
	{
		comment->SetWindowText("");
		button->EnableWindow(FALSE);
	}
	else
	{
		comment->SetWindowText(m_protocol_types[sel].m_pps.m_comment);
		button->EnableWindow(TRUE);
	}
}

void CPMDlg::OnSelchangeListProtocols() 
{
	// TODO: Add your control notification handler code here

	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	int num_protocols = m_protocols.GetSize();

	// Update the comment
	CWnd* comment = GetDlgItem(IDC_EDIT_COMMENT);
	ASSERT(comment != NULL);
	if ((sel == LB_ERR) || (sel >= num_protocols))
	{
		comment->SetWindowText("");
	}
	else
	{
		comment->SetWindowText(m_protocols[sel].m_pps.m_comment);
	}

	CWnd* button;
	// Update the Run button
	button = GetDlgItem(IDC_RUN);
	ASSERT(button != NULL);
	button->EnableWindow(((sel == LB_ERR) || (sel >= num_protocols) ||
		!m_protocols[sel].m_pps.IsRunable()) ? FALSE : TRUE);

	// Update the Edit button
	button = GetDlgItem(IDC_EDIT);
	ASSERT(button != NULL);
	button->EnableWindow(((sel == LB_ERR) || (sel >= num_protocols)) ? FALSE : TRUE);

	// Update the Delete button
	button = GetDlgItem(IDC_DELETE);
	ASSERT(button != NULL);
	button->EnableWindow(((sel == LB_ERR) || (sel >= num_protocols) ||
		!m_protocols[sel].m_pps.IsDeleteable()) ? FALSE : TRUE);
}

void CPMDlg::OnProtocolRun() 
{
	// TODO: Add your control notification handler code here
	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	if (((sel != LB_ERR) || (sel < m_protocols.GetSize())) &&
		m_protocols[sel].m_pps.IsRunable())
	{
		CString str;
		str.Format("%s\\classes\\%s", m_options.m_maindir, m_protocols[sel].m_pps.m_protocolexe);
		CFileFind finder;
		if (finder.FindFile(str))
		{
			// Build the commandline string
			CString cmdline_str;
			cmdline_str.Format("\"classes\\%s\" /r /f%d /p%d /b%ld \"/w%s\" \"%s.pps\"",
				m_protocols[sel].m_pps.m_protocolexe, m_options.m_beep ? 1 : 0, m_options.m_lumiport, m_options.m_lumibaud,
				m_options.m_workdir, m_protocols[sel].m_name);
			char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
			strcpy(cmdline_ptr, cmdline_str);

			// Start the protocol and wait for it to finish
			if (!StartProtocolAndWait(cmdline_ptr))
			{
				AfxMessageBox(IDS_PROC_RUN);
			}

			delete [] cmdline_ptr;
		}
		else
		{
			str.Format("Protocol type does not exist:\n\n%s",
				m_protocols[sel].m_pps.m_protocolexe);
			AfxMessageBox(str);
		}
	}
}

void CPMDlg::OnProtocolEdit() 
{
	// TODO: Add your control notification handler code here
	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	if ((sel != LB_ERR) || (sel < m_protocols.GetSize()))
	{
		CString str;
		str.Format("%s\\classes\\%s", m_options.m_maindir, m_protocols[sel].m_pps.m_protocolexe);
		CFileFind finder;
		if (finder.FindFile(str))
		{
			// Build the commandline string
			CString cmdline_str;
			cmdline_str.Format("\"classes\\%s\" /e \"%s.pps\"",
				m_protocols[sel].m_pps.m_protocolexe,
				m_protocols[sel].m_name);
			char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
			strcpy(cmdline_ptr, cmdline_str);

			// Start the protocol and wait for it to finish
			if (!StartProtocolAndWait(cmdline_ptr, true))
			{
				AfxMessageBox(IDS_PROC_EDIT);
			}

			delete [] cmdline_ptr;
		}
		else
		{
			str.Format("Protocol type does not exist:\n\n%s",
				m_protocols[sel].m_pps.m_protocolexe);
			AfxMessageBox(str);
		}
	}
}

void CPMDlg::OnProtocolCreate() 
{
	// TODO: Add your control notification handler code here
	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLTYPES);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	if ((sel != LB_ERR) || (sel < m_protocol_types.GetSize()))
	{
		CString str;
		str.Format("%s\\classes\\%s", m_options.m_maindir, m_protocol_types[sel].m_pps.m_protocolexe);
		CFileFind finder;
		if (finder.FindFile(str))
		{
			// Build the commandline string
			CString cmdline_str;
			cmdline_str.Format("\"classes\\%s\" /e \"%s.pps\"",
				m_protocol_types[sel].m_pps.m_protocolexe,
				m_protocol_types[sel].m_name);
			char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
			strcpy(cmdline_ptr, cmdline_str);

			// Start the protocol and wait for it to finish
			if (!StartProtocolAndWait(cmdline_ptr, true))
			{
				AfxMessageBox(IDS_PROC_EDIT);
			}

			delete [] cmdline_ptr;
		}
		else
		{
			str.Format("Protocol type does not exist:\n\n%s",
				m_protocol_types[sel].m_pps.m_protocolexe);
			AfxMessageBox(str);
		}
	}
}

void CPMDlg::OnRetrieve() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(
		TRUE,
		_T(".mds"),
		NULL,
		OFN_HIDEREADONLY,
		_T("Measurement Data Files (*.mds)|*.mds|All Files (*.*)|*.*||"));

	if (fileDlg.DoModal() == IDCANCEL)
	{
		return;
	}

	CString err_str;
	CFile pps_file;
	if (pps_file.Open(fileDlg.GetPathName(), CFile::modeRead))
	{
		CPPS pps;
		bool success = pps.Read(pps_file);
		pps_file.Close();

		if (success)
		{
			CString str;
			str.Format("%s\\classes\\%s", m_options.m_maindir, pps.m_protocolexe);
			CFileFind finder;
			if (finder.FindFile(str))
			{
				// Build the commandline string
				CString cmdline_str;
				cmdline_str.Format("\"classes\\%s\" /v \"/w%s\" \"%s\"",
					pps.m_protocolexe, m_options.m_workdir,
					fileDlg.GetPathName());
				char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
				strcpy(cmdline_ptr, cmdline_str);

				// Start the protocol and wait for it to finish
				if (!StartProtocolAndWait(cmdline_ptr))
				{
					AfxMessageBox(IDS_PROC_VIEW);
				}

				delete [] cmdline_ptr;
			}
			else
			{
				str.Format("Protocol type does not exist:\n\n%s",
					pps.m_protocolexe);
				AfxMessageBox(str);
			}
		}
		else
		{
			err_str.Format("Error reading file %s!", fileDlg.GetPathName());
			SCMessageBox(err_str);
		}
	}
	else
	{
		err_str.Format("File %s could not be opened!", fileDlg.GetPathName());
		SCMessageBox(err_str);
	}
}

void CPMDlg::OnProtocolDelete() 
{
	// TODO: Add your control notification handler code here
	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	if ((sel != LB_ERR) || (sel < m_protocols.GetSize()))
	{
		if (m_protocols[sel].m_pps.IsBase())
		{
			AfxMessageBox("This protocol cannot be deleted.\nIt is a base protocol type.");
		}
		else
		{
			CString msg_str;
			msg_str.Format("Are you sure you want to remove this protocol?\n\n%s", m_protocols[sel].m_name);
			if (AfxMessageBox(msg_str, MB_YESNO) == IDYES)
			{
				CString prot_path = m_options.m_maindir + '\\';
				prot_path += "protocols\\";
				prot_path += m_protocols[sel].m_name + ".pps";
				CFile::Remove(prot_path);
				BuildProtocolArray();
			}
		}
	}
}

bool CPMDlg::StartProtocolAndWait(LPTSTR cmdline, bool rebuild)
{
	bool success = false;

	CString cur_dir = SCSetCurrentDir(m_options.m_maindir);

	STARTUPINFO suinfo;
	memset(&suinfo, 0, sizeof(suinfo));
	suinfo.cb = sizeof(suinfo);
	if (::CreateProcess(NULL, cmdline, 0, 0, FALSE, 0, NULL, NULL, &suinfo, &m_pi))
	{
		// We better hide ourselves
		ShowWindow(SW_HIDE);

		m_rebuild = rebuild;
		//m_waiting = true;

		success = true;
/*
		// Try this
		if (WaitForSingleObject(m_pi.hProcess, INFINITE) == WAIT_OBJECT_0)
		{
			m_waiting = false;

			CloseHandle(m_pi.hProcess);
			CloseHandle(m_pi.hThread);

			if (m_rebuild)
			{
				BuildProtocolArray();
			}

			// We better show ourselves again
			ShowWindow(SW_SHOW);
			SetForegroundWindow();
		}
		// End of Try this
*/
		AfxBeginThread(ProtocolThreadFunction, this);
	}

	SCSetCurrentDir(cur_dir);

	return success;
}
/*
void CPMDlg::InstanceTimerCallback()
{
	if (m_waiting)
	{
		if (WaitForSingleObject(m_pi.hProcess, 100) != WAIT_TIMEOUT)
		{
			m_waiting = false;

			CloseHandle(m_pi.hProcess);
			CloseHandle(m_pi.hThread);

			if (m_rebuild)
			{
				BuildProtocolArray();
			}

			// We better show ourselves again
			ShowWindow(SW_SHOW);
			SetForegroundWindow();
		}
	}
}

void CALLBACK CPMDlg::TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	((CPMDlg*)dwUser)->InstanceTimerCallback();
}
*/
void CPMDlg::OnAppAbout() 
{
	// TODO: Add your control notification handler code here
#ifdef SERNUM_MAKEFILE
	CSCSerialNumber::MakeSerialFile();
#endif

	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CPMDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType == SIZE_RESTORED);
	{
		MySize();
	}
}

void CPMDlg::MySize()
{
	CRect dlg_rect, rect, limit_rect;
	CWnd* wnd;

	// Get the dlg rect
	GetWindowRect(&dlg_rect);

	// Vertical
	int yborder = 10;

	// Change the height of the user-created protocol list box
	wnd = GetDlgItem(IDC_LIST_PROTOCOLS);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		GetDlgItem(IDC_DELETE)->GetWindowRect(&limit_rect);
		wnd->GetWindowRect(&rect);
		rect.bottom = dlg_rect.bottom - yborder - yborder / 2;
		if (rect.bottom < limit_rect.bottom)
		{
			rect.bottom = limit_rect.bottom;
		}
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the height of the comment box
	wnd = GetDlgItem(IDC_EDIT_COMMENT);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		// use the same limit rect as above
		wnd->GetWindowRect(&rect);
		rect.bottom = dlg_rect.bottom - yborder - yborder / 2;
		if (rect.bottom < limit_rect.bottom)
		{
			rect.bottom = limit_rect.bottom;
		}
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the height of the user-created protocol group box
	wnd = GetDlgItem(IDC_STATIC_USER);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		GetDlgItem(IDC_LIST_PROTOCOLS)->GetWindowRect(&limit_rect);
		wnd->GetWindowRect(&rect);
		rect.bottom = limit_rect.bottom + yborder / 2;
		limit_rect = rect;	// save for buttons
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Find the spacing for the buttons
	int button_height_diff = 25;
	int button_height = 10;
	int button_width = 10;
	wnd = GetDlgItem(IDOK);
	if (wnd)
	{
		wnd->GetWindowRect(&rect);
		button_height_diff = rect.top;
		button_height = rect.Height();
		button_width = rect.Width();
		wnd = GetDlgItem(ID_APP_ABOUT);
		if (wnd)
		{
			wnd->GetWindowRect(&rect);
			button_height_diff -= rect.top;
		}
		else
		{
			button_height_diff = 25;
		}
	}

	// Change the Exit button
	wnd = GetDlgItem(IDOK);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.top = limit_rect.bottom - button_height;
		limit_rect = rect;	// save for other buttons
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the Help button
	//wnd = GetDlgItem(ID_HELP);
	//if (wnd)
	//{
	//	//wnd->InvalidateRect(NULL, TRUE);
	//	wnd->GetWindowRect(&rect);
	//	rect.top = limit_rect.top - button_height_diff;
	//	limit_rect = rect;
	//	ScreenToClient(&rect);
	//	wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
	//	//wnd->InvalidateRect(NULL, FALSE);
	//}

	// Change the About button
	wnd = GetDlgItem(ID_APP_ABOUT);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.top = limit_rect.top - button_height_diff;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}


	// Horizontal
	int xborder = 10;
	int min_comment_width = 100;

	// Change the protocol type comment width
	wnd = GetDlgItem(IDC_EDIT_TYPECOMMENT);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.right = dlg_rect.right - 2 * xborder - button_width - xborder / 2;
		if (rect.Width() < min_comment_width)
		{
			rect.right = rect.left + min_comment_width - 1;
		}
		limit_rect = rect;	// save rect for other comment next
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the protocol comment width
	wnd = GetDlgItem(IDC_EDIT_COMMENT);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.right = limit_rect.right;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the protocol type group box width
	wnd = GetDlgItem(IDC_STATIC_TYPES);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.right = limit_rect.right + xborder / 2;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the protocol group box width
	wnd = GetDlgItem(IDC_STATIC_USER);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.right = limit_rect.right + xborder / 2;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the Options button
	wnd = GetDlgItem(IDC_RETRIEVE);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.left = limit_rect.right + xborder / 2 + xborder;
		limit_rect = rect;	// save button rect for next buttons
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the Options button
	wnd = GetDlgItem(IDC_OPTIONS);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.left = limit_rect.left;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the About button
	wnd = GetDlgItem(ID_APP_ABOUT);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.left = limit_rect.left;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	// Change the Help button
	//wnd = GetDlgItem(ID_HELP);
	//if (wnd)
	//{
	//	//wnd->InvalidateRect(NULL, TRUE);
	//	wnd->GetWindowRect(&rect);
	//	rect.left = limit_rect.left;
	//	ScreenToClient(&rect);
	//	wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
	//	//wnd->InvalidateRect(NULL, FALSE);
	//}

	// Change the Exit button
	wnd = GetDlgItem(IDOK);
	if (wnd)
	{
		//wnd->InvalidateRect(NULL, TRUE);
		wnd->GetWindowRect(&rect);
		rect.left = limit_rect.left;
		ScreenToClient(&rect);
		wnd->MoveWindow(rect.left, rect.top, button_width, button_height, FALSE);
		//wnd->InvalidateRect(NULL, FALSE);
	}

	InvalidateRect(NULL, TRUE);
}

void CPMDlg::OnDropFiles(HDROP hDropInfo)
{
	SetActiveWindow();      // activate us first !
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	if (nFiles > 0)
	{
		bool file_ok;
		bool is_pps;
		CPPS pps;
		TCHAR szFileName[MAX_PATH];
		UINT i;
		for (i = 0; i < nFiles; i++)
		{
			file_ok = false;
			::DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
			if (strlen(szFileName) > 4)
			{
				if (strcmp(&szFileName[strlen(szFileName) - 4], ".pps") == 0)
				{
					ResolveLink(m_hWnd, szFileName);
					file_ok = true;
					is_pps = true;
				}
				else if (strcmp(&szFileName[strlen(szFileName) - 4], ".mds") == 0)
				{
					ResolveLink(m_hWnd, szFileName);
					file_ok = true;
					is_pps = false;
				}
			}
			if (file_ok)
			{
				// Read the pps info
				file_ok = false;
				CFile pps_file;
				if (pps_file.Open(szFileName, CFile::modeRead))
				{
					if (pps.Read(pps_file))
					{
						file_ok = true;
					}
					pps_file.Close();
				}
			}
			if (file_ok)
			{
				CString str;
				str.Format("%s\\classes\\%s", m_options.m_maindir, pps.m_protocolexe);
				CFileFind finder;
				if (!finder.FindFile(str))
				{
					str.Format("Protocol does not exist:\n\n%s", pps.m_protocolexe);
					AfxMessageBox(str);
					file_ok = false;
				}
			}
			if (file_ok)
			{
				if (is_pps)
				{
					if (pps.IsRunable())
					{
						// Build the commandline string
						CString cmdline_str;
						cmdline_str.Format("\"classes\\%s\" /r /p%d /b%ld \"/w%s\" \"%s\"",
							pps.m_protocolexe, m_options.m_lumiport, m_options.m_lumibaud,
							m_options.m_workdir, szFileName);
						char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
						strcpy(cmdline_ptr, cmdline_str);

						// Start the protocol and wait for it to finish
						if (!StartProtocolAndWait(cmdline_ptr))
						{
							AfxMessageBox(IDS_PROC_RUN);
						}

						delete [] cmdline_ptr;
					}
					else
					{
						// Build the commandline string
						CString cmdline_str;
						cmdline_str.Format("\"classes\\%s\" /e \"%s\"",
							pps.m_protocolexe, szFileName);
						char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
						strcpy(cmdline_ptr, cmdline_str);

						// Start the protocol and wait for it to finish
						if (!StartProtocolAndWait(cmdline_ptr, true))
						{
							AfxMessageBox(IDS_PROC_EDIT);
						}

						delete [] cmdline_ptr;
					}
				}
				else
				{
					// View the .mds file
					// Build the commandline string
					CString cmdline_str;
					cmdline_str.Format("\"classes\\%s\" /v \"/w%s\" \"%s\"",
						pps.m_protocolexe, m_options.m_workdir, szFileName);
					char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
					strcpy(cmdline_ptr, cmdline_str);

					// Start the protocol and wait for it to finish
					if (!StartProtocolAndWait(cmdline_ptr))
					{
						AfxMessageBox(IDS_PROC_VIEW);
					}

					delete [] cmdline_ptr;
				}
				break;
			}
		}
	}

	::DragFinish(hDropInfo);
}

HRESULT CPMDlg::ResolveLink(HWND hwnd, LPSTR link_path)
{
    HRESULT hres;
    IShellLink* psl;
    char szGotPath[MAX_PATH];
    char szDescription[MAX_PATH];
    WIN32_FIND_DATA wfd;

    // Get a pointer to the IShellLink interface.
    hres = CoCreateInstance(CLSID_ShellLink, NULL,
            CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
    if (SUCCEEDED(hres))
	{
        IPersistFile* ppf;

        // Get a pointer to the IPersistFile interface.
        hres = psl->QueryInterface(IID_IPersistFile,
            (void**)&ppf);
        if (SUCCEEDED(hres))
		{
            WORD wsz[MAX_PATH];

            // Ensure that the string is Unicode.
            MultiByteToWideChar(CP_ACP, 0, link_path, -1, wsz,
                MAX_PATH);

            // Load the shortcut.
            hres = ppf->Load(wsz, STGM_READ);
            if (SUCCEEDED(hres))
			{
                // Resolve the link.
                hres = psl->Resolve(hwnd, SLR_ANY_MATCH);
                if (SUCCEEDED(hres))
				{
                    // Get the path to the link target.
                    hres = psl->GetPath(szGotPath,
                        MAX_PATH, (WIN32_FIND_DATA *)&wfd,
                        SLGP_SHORTPATH );
                    if (SUCCEEDED(hres))
					{
						// Get the description of the target.
						hres = psl->GetDescription(
							szDescription, MAX_PATH);
						if (SUCCEEDED(hres))
						{
							strcpy(link_path, szGotPath);
						}
					}
                }
            }
			// Release the pointer to the IPersistFile interface.
			ppf->Release();
        }
		// Release the pointer to the IShellLink interface.
		psl->Release();
    }

    return hres;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//CString serial_string = AfxGetApp()->GetProfileString(_T("Settings"), _T("SerialNumber"), "");
	//CString ser_str;
	//ser_str.Format("serial number: %s-%s", serial_string.Left(5), serial_string.Right(5));
	//GetDlgItem(IDC_STATIC_SERSTR)->SetWindowText(ser_str);

	// Set the version string
	COptions options;
	CString ver;
	ver.Format("Version %s", options.m_version);
	SetDlgItemText(IDC_STATIC_VERSION, ver);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPMDlg::OnViewfile() 
{
	// TODO: Add your command handler code here
	if (m_filename.GetLength() > 4)
	{
		TCHAR szFileName[MAX_PATH];
		strncpy(szFileName, m_filename, MAX_PATH);
		if (strcmp(&szFileName[strlen(szFileName) - 4], ".mds") == 0)
		{
			ResolveLink(m_hWnd, szFileName);
			CPPS pps;
			CFile pps_file;
			if (pps_file.Open(szFileName, CFile::modeRead))
			{
				bool file_ok = pps.Read(pps_file);
				pps_file.Close();
				if (file_ok)
				{
					CString str;
					str.Format("%s\\classes\\%s", m_options.m_maindir, pps.m_protocolexe);
					CFileFind finder;
					if (!finder.FindFile(str))
					{
						str.Format("Protocol does not exist:\n\n%s", pps.m_protocolexe);
						AfxMessageBox(str);
						file_ok = false;
					}
				}
				if (file_ok)
				{
					// View the .mds file
					// Build the commandline string
					CString cmdline_str;
					cmdline_str.Format("\"classes\\%s\" /v \"/w%s\" \"%s\"",
						pps.m_protocolexe, m_options.m_workdir, szFileName);
					char* cmdline_ptr = new char[cmdline_str.GetLength() + 1];
					strcpy(cmdline_ptr, cmdline_str);

					// Start the protocol and wait for it to finish
					if (!StartProtocolAndWait(cmdline_ptr))
					{
						AfxMessageBox(IDS_PROC_VIEW);
					}

					delete [] cmdline_ptr;
				}
			}
		}
	}
}

void CPMDlg::OnProtocoldone() 
{
	CloseHandle(m_pi.hProcess);
	CloseHandle(m_pi.hThread);

	if (m_rebuild)
	{
		BuildProtocolArray();
	}

	// We better show ourselves again
	ShowWindow(SW_SHOW);
	SetForegroundWindow();
}

UINT CPMDlg::ProtocolThreadFunction(LPVOID pParam)
{
	CPMDlg* dlg = (CPMDlg*)pParam;

	if (WaitForSingleObject(dlg->m_pi.hProcess, INFINITE) == WAIT_OBJECT_0)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, IDC_PROTOCOLDONE, 0);
	}

	return 0;
}
