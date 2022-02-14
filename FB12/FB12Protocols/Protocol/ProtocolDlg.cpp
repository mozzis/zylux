// ProtocolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "ProtocolDlg.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg dialog


CProtocolDlg::CProtocolDlg(LPCTSTR protocolname, UINT nIDTemplate,
	CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd),
	m_protocolname(protocolname)
{
	//{{AFX_DATA_INIT(CProtocolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CProtocolDlg, CDialog)
	//{{AFX_MSG_MAP(CProtocolDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg message handlers

BOOL CProtocolDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (strlen(m_protocolname) > 0)
	{
		CString title;
		GetWindowText(title);
		title += " - ";
		title += m_protocolname;
		SetWindowText(title);
	}

	HICON hIcon = AfxGetApp()->LoadIcon(ProtGetApp()->m_main_icon_id);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
