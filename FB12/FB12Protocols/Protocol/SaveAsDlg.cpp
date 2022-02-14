// SaveAsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaveAsDlg.h"
#include "General.h"
#include "PPS.h"
#include "Protocol.h"

//#include <dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveAsDlg dialog

CSaveAsDlg::CSaveAsDlg(LPCTSTR default_name, bool allow_base_overwrite,
	CWnd* pParent /*=NULL*/)
	: CDialog(CSaveAsDlg::IDD, pParent), m_protocolname(default_name),
	m_allow_base_overwrite(allow_base_overwrite)
{
	//{{AFX_DATA_INIT(CSaveAsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSaveAsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveAsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveAsDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveAsDlg)
	ON_LBN_SELCHANGE(PPS_IDC_LIST_PROTOCOLS, OnSelchangeListProtocols)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveAsDlg message handlers

BOOL CSaveAsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	// Set the default protocol name
	CEdit* prot_edit = (CEdit*)GetDlgItem(PPS_IDC_EDIT_PROTOCOL);
	ASSERT(prot_edit != NULL);
	prot_edit->SetLimitText(CPPS::PROTOCOLNAME_SIZE - 1);
	prot_edit->SetWindowText(m_protocolname);

	// Get an array of protocols
	CString curdir = SCSetCurrentDir(ProtGetApp()->m_maindir);
	CPPS::BuildProtocolArray(m_protocols);
	SCSetCurrentDir(curdir);

	// Add protocol names to list box
	CListBox* pList = (CListBox*)GetDlgItem(PPS_IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	for (int i = 0; i < m_protocols.GetSize(); i++)
	{
		pList->AddString(m_protocols[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveAsDlg::OnSelchangeListProtocols() 
{
	// TODO: Add your control notification handler code here

	// Get the selected protocol
	CListBox* pList = (CListBox*)GetDlgItem(PPS_IDC_LIST_PROTOCOLS);
	ASSERT(pList != NULL);
	int sel = pList->GetCurSel();
	
	// Update the protocol name
	CWnd* protocol = GetDlgItem(PPS_IDC_EDIT_PROTOCOL);
	ASSERT(protocol != NULL);
	if ((sel == LB_ERR) || (sel >= pList->GetCount()))
	{
		protocol->SetWindowText("");
	}
	else
	{
		protocol->SetWindowText(m_protocols[sel]);
	}
}

void CSaveAsDlg::OnOK()
{
	CString curdir = SCSetCurrentDir(ProtGetApp()->m_protocoldir);

	GetDlgItemText(PPS_IDC_EDIT_PROTOCOL, m_protocolname);

	bool exists = false;
	for (int i = 0; i < m_protocols.GetSize(); i++)
	{
		if (m_protocolname == m_protocols[i])
		{
			exists = true;
			break;
		}
	}

	bool is_ok = true;
	if (exists)
	{
		CString msg_str;
		if (!m_allow_base_overwrite && CPPS::IsFileBase(m_protocolname))
		{
			msg_str.Format("The protocol %s cannot be overwritten.", m_protocolname);
			SCMessageBox(msg_str);
			is_ok = false;
		}
		else
		{
			msg_str.Format("%s\nThis protocol already exists.\n\nReplace existing protocol?", m_protocolname);
			if (SCMessageBox(msg_str, MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
			{
				is_ok = false;
			}
		}
	}

	if (is_ok)
	{
		CDialog::OnOK();
	}

	SCSetCurrentDir(curdir);
}
