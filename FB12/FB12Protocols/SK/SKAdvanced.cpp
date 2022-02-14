// SKAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "SKAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKAdvanced dialog


CSKAdvanced::CSKAdvanced(CSKPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CSKAdvanced::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CSKAdvanced)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSKAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSKAdvanced)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSKAdvanced, CProtocolDlg)
	//{{AFX_MSG_MAP(CSKAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKAdvanced message handlers

BOOL CSKAdvanced::OnInitDialog()
{
	CProtocolDlg::OnInitDialog();

	// TODO: Add extra initialization here
	//CEdit* pMacro = (CEdit*)GetDlgItem(IDC_EDIT_MACRO);
	//ASSERT(pMacro != NULL);
	//pMacro->SetLimitText(CGPPS::MACRONAME_SIZE - 1);
	//pMacro->SetWindowText(m_pps.m_macroname);

	CButton* pTimebase = (CButton*)GetDlgItem(IDC_CHECK_TIMEBASE);
	ASSERT(pTimebase != NULL);
	pTimebase->SetCheck(m_pps.IsLumiTimeBase() ? 1 : 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSKAdvanced::OnOK()
{
	// TODO: Add extra validation here
	if (VerifyFields())
	{
		ReadFields();
		CProtocolDlg::OnOK();
	}
}

void CSKAdvanced::ReadFields()
{
	//CString entry;
	//CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACRO);

	//entry.Empty();
	//pMacroName->GetWindowText(entry);
	//entry.TrimLeft();
	//entry.TrimRight();
	//if (entry.IsEmpty())
	//{
	//	memset(m_pps.m_macroname, 0, sizeof(m_pps.m_macroname));
	//}
	//else
	//{
	//	strcpy(m_pps.m_macroname, LPCTSTR(entry));
	//}

	CWnd* pWnd = GetDlgItem(IDC_CHECK_TIMEBASE);
	ASSERT(pWnd != NULL);
	m_pps.SetLumiTimeBase((((CButton*)pWnd)->GetCheck() == 1) ? true : false);
}


bool CSKAdvanced::VerifyFields()
{
	// Add field verification later, as needed.
	return TRUE;
}
