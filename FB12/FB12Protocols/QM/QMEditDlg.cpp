// QMEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qm.h"
#include "QMEditDlg.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQMEditDlg dialog


CQMEditDlg::CQMEditDlg(CQMPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CQMEditDlg::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CQMEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQMEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQMEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQMEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CQMEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UDACCEL time_accel[] =
{
	{ 0, 1 },		// deciseconds
	{ 4, 5 },		// seconds, 5x
	{ 8, 50 },		// decaseconds 10x
	{ 12, 300 },	// minutes, 6x
	{ 16, 1500 }	// 2 minutes, 5x
};

/////////////////////////////////////////////////////////////////////////////
// CQMEditDlg message handlers

BOOL CQMEditDlg::OnInitDialog() 
{
	CProtocolDlg::OnInitDialog();

	if (!m_pps.IsSaveable())
	{
		GetDlgItem(IDC_SAVE)->ShowWindow(SW_HIDE);
	}
	if (!m_pps.IsSaveAsable())
	{
		GetDlgItem(IDC_SAVEAS)->ShowWindow(SW_HIDE);
	}

	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);
	CSpinButtonCtrl* pMeas = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_MEAS);

	pDelay->SetRange(0, UD_MAXVAL);
	pDelay->SetPos(m_pps.m_delaytime / 2);
	pDelay->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);
	pMeas->SetRange(1, UD_MAXVAL);
	pMeas->SetPos(m_pps.m_meastime / 2);
	pMeas->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);

	SetDelayText();
	SetMeasText();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQMEditDlg::SetDelayText()
{
	SetDlgItemText(IDC_EDIT_DELAY, SCFormatDeciseconds(m_pps.m_delaytime));
}

void CQMEditDlg::SetMeasText()
{
	SetDlgItemText(IDC_EDIT_MEAS, SCFormatDeciseconds(m_pps.m_meastime));
}

void CQMEditDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	m_pps.Save(m_protocolname);
	EndDialog(IDC_SAVE);
}

void CQMEditDlg::OnSaveas() 
{
/*
	// TODO: Add your control notification handler code here
	// This function is never called since the QM protocol
	// cannot be saved under any different name.
	if (m_pps.SaveAs(m_protocolname, true))
	{
		EndDialog(IDC_SAVEAS);
	}
*/
}

void CQMEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nControl = pScrollBar->GetDlgCtrlID();
	CSpinButtonCtrl* pControl = (CSpinButtonCtrl*) GetDlgItem(nControl);

	switch (nControl)
	{
		case IDC_SPIN_DELAY:
			ASSERT(pControl != NULL);
			m_pps.m_delaytime = (pControl->GetPos() & 0x0000ffff) * 2;
			SetDelayText();
			break;

		case IDC_SPIN_MEAS:
			ASSERT(pControl != NULL);
			m_pps.m_meastime = (pControl->GetPos() & 0x0000ffff) * 2;
			SetMeasText();
			break;

		default:
			CProtocolDlg::OnVScroll(nSBCode, nPos, pScrollBar);
			break;
	}
}
