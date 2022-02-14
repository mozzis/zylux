// DlgGetVer.cpp : implementation file
//

#include "stdafx.h"
#include "InstZApp.h"
#include "DlgGetVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetVer dialog


CDlgGetVer::CDlgGetVer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetVer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetVer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_eChoice = UPGRADE_US;
  m_bPrevVerPresent = false;
}


void CDlgGetVer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetVer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetVer, CDialog)
	//{{AFX_MSG_MAP(CDlgGetVer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetVer message handlers

void CDlgGetVer::OnOK() 
{
  switch (GetCheckedRadioButton(IDC_RADIO_US, IDC_RADIO_NO))
    {
    case IDC_RADIO_US:
      m_eChoice = UPGRADE_US;
    break;
    case IDC_RADIO_UK:
      m_eChoice = UPGRADE_UK;
    break;
    case IDC_RADIO_NO:
    default:
      m_eChoice = UPGRADE_NO;
    }
  CDialog::OnOK();
}

CDlgGetVer::E_CHOICES CDlgGetVer::GetUserChoice(void)
{
  return m_eChoice;
}

BOOL CDlgGetVer::OnInitDialog() 
{	
  CDialog::OnInitDialog();

  CString csMsg, csTxt;
  if (m_bPrevVerPresent)
    csTxt.LoadString(IDS_DLGVER_MSG1);
  else
    csTxt.LoadString(IDS_DLGVER_MSG2);
  csMsg.Format(csTxt, m_csVersion);
  SetDlgItemText(IDC_VERMSG, csMsg);

  SetForegroundWindow();
	
  CheckRadioButton(IDC_RADIO_US, IDC_RADIO_UK, IDC_RADIO_US);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
