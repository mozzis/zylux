// InjectorWarning.cpp : implementation file
//

#include "stdafx.h"
#include "sk.h"
#include "InjectorWarning.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInjectorWarning dialog


CInjectorWarning::CInjectorWarning(bool show, CWnd* pParent /*=NULL*/)
	: CDialog(CInjectorWarning::IDD, pParent), m_warnflag(show)
{
	//{{AFX_DATA_INIT(CInjectorWarning)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInjectorWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInjectorWarning)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInjectorWarning, CDialog)
	//{{AFX_MSG_MAP(CInjectorWarning)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectorWarning message handlers

void CInjectorWarning::OnOK() 
{
	// TODO: Add extra validation here
	//	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_AUTOSEND);
	//ASSERT(button != NULL);

	CButton* hide_it = (CButton*)GetDlgItem(IDC_CHECK_HIDE);
	ASSERT(hide_it != NULL);
	if (hide_it->GetCheck() == 0)
		m_warnflag = true;
	else
		m_warnflag = false;
	
	CDialog::OnOK();
}
