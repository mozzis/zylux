// SAEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SA.h"
#include "SAEditDlg.h"
#include "SAAdvancedDlg.h"
#include "General.h"
#include "ExcelOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSAEditDlg dialog


CSAEditDlg::CSAEditDlg(CSAPPS& ed_pps, LPCTSTR protocol_name, CWnd* pParent) : CProtocolDlg(protocol_name, CSAEditDlg::IDD, pParent),
			m_pps(ed_pps)
{
	//{{AFX_DATA_INIT(CSAEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSAEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSAEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CSAEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_RB_DOORCLOSE, OnRbDoorclose)
	ON_BN_CLICKED(IDC_RB_STARTBUTTON, OnRbStartbutton)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAEditDlg message handlers

BOOL CSAEditDlg::OnInitDialog() 
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
	CSpinButtonCtrl* pReps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_REPS);
	CSpinButtonCtrl* pSamps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_SAMPS);
	//CButton* pTimestamp = (CButton*) GetDlgItem(IDC_CB_TIMESTAMP);
	CButton* pBackground = (CButton*) GetDlgItem(IDC_CB_BACKGROUND);
	CButton* pDoorClose = (CButton*) GetDlgItem(IDC_RB_DOORCLOSE);
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);


	if (m_pps.UseStartButton())
	{
		pStartButton->SetCheck(1);
	}
	else
	{
		pDoorClose->SetCheck(1);
	}

	// Set Ranges and Positions on spinners.
	pDelay->SetRange(0, UD_MAXVAL);
	pDelay->SetPos(m_pps.m_delaytime / 2);
	if (m_pps.UseStartButton())
	{
		GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(FALSE);
		pDelay->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(TRUE);
		pDelay->EnableWindow(TRUE);
	}
	pMeas->SetRange(1, UD_MAXVAL);
	pMeas->SetPos(m_pps.m_meastime / 2);
	pReps->SetRange(1, UD_MAXVAL);
	pReps->SetPos(m_pps.m_numreps);
	pSamps->SetRange(1, UD_MAXVAL);
	pSamps->SetPos(m_pps.m_numsamps);
	
	// Initialize Text to m_pps values
	SetDelayText();
	SetMeasText();
	SetDlgItemInt(IDC_EDIT_REPS, m_pps.m_numreps, FALSE);
	SetDlgItemInt(IDC_EDIT_SAMPS, m_pps.m_numsamps, FALSE);

	// Initialize Checkboxes
	if (m_pps.UseBackground())
	{
		pBackground->SetCheck(1);
	}
	else
	{
		pBackground->SetCheck(0);
	}

	//if (m_pps.UseTimestamps())
	//{
	//	pTimestamp->SetCheck(1);
	//}
	//else
	//{
	//	pTimestamp->SetCheck(0);
	//}

	pComments->LimitText(m_pps.COMMENT_SIZE - 1);
	pComments->SetWindowText(m_pps.m_comment);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSAEditDlg::SetDelayText()
{
	SetDlgItemText(IDC_EDIT_DELAY, SCFormatDeciseconds(m_pps.UseStartButton() ? 0 : m_pps.m_delaytime));
}

void CSAEditDlg::SetMeasText()
{
	SetDlgItemText(IDC_EDIT_MEAS, SCFormatDeciseconds(m_pps.m_meastime));
}


void CSAEditDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	if (VerifyEntries())
	{
		SetEntries();
		// Save the pps file under same name
		m_pps.Save(m_protocolname);

		EndDialog(IDC_SAVE);
	}
}

void CSAEditDlg::OnSaveas() 
{
	// TODO: Add your control notification handler code here

	if (VerifyEntries())
	{
		m_pps.SetSaveable(true);
		m_pps.SetRunable(true);
		m_pps.SetDeleteable(true);
		m_pps.SetBase(false);
		SetEntries();
		// Let the user choose a new name to save
		// the pps file under
		if (m_pps.SaveAs(m_protocolname, false))
		{
			EndDialog(IDC_SAVEAS);
		}
	}
}


void CSAEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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

void CSAEditDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here

	if (!VerifyEntries())
	{
		return;
	}

	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_REPS, NULL, FALSE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_SAMPS, NULL, FALSE));

	
	CSAAdvancedDlg dlg(m_pps, m_protocolname);

	int nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
		SetDlgItemInt(IDC_EDIT_REPS, m_pps.m_numreps, FALSE);
		SetDlgItemInt(IDC_EDIT_SAMPS, m_pps.m_numsamps, FALSE);
	}

}


BOOL CSAEditDlg::VerifyEntries()
{
	UINT val = 0;
	BOOL is_ok = TRUE;

	val = GetDlgItemInt(IDC_EDIT_REPS, &is_ok, FALSE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of replicates");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of replicates");
			return FALSE;
		}
	}

	val = 0;
	is_ok = TRUE;
	val = GetDlgItemInt(IDC_EDIT_SAMPS, &is_ok, FALSE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of samples");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of replicates");
			return FALSE;
		}
	}

	return TRUE;
}


void CSAEditDlg::SetEntries()
{
	//CButton* pTimestamp = (CButton*) GetDlgItem(IDC_CB_TIMESTAMP);
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CButton* pBackground = (CButton*) GetDlgItem(IDC_CB_BACKGROUND);
	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);


	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_REPS, NULL, TRUE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_SAMPS, NULL, TRUE));

	if (pBackground->GetCheck())
	{
		m_pps.SetUseBackground(true);
	}
	else
	{
		m_pps.SetUseBackground(false);
	}

	if (pStartButton->GetCheck())
	{
		m_pps.SetUseStartButton(true);
	}
	else
	{
		m_pps.SetUseStartButton(false);
	}

	//if (pTimestamp->GetCheck())
	//{
	//	m_pps.SetUseTimestamps(true);
	//}
	//else
	//{
	//	m_pps.SetUseTimestamps(false);
	//}

	CString entry;
	entry.Empty();
	pComments->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	if (entry.IsEmpty())
	{
		memset(m_pps.m_comment, 0, sizeof(m_pps.m_comment));
	}
	else
	{
		strcpy(m_pps.m_comment, LPCTSTR(entry));
	}

}


void CSAEditDlg::OnRbDoorclose() 
{
	// TODO: Add your control notification handler code here
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);

	m_pps.SetUseStartButton(false);	
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(TRUE);
	pDelay->EnableWindow(TRUE);
	//pDelay->SetPos(m_pps.m_delaytime / 2);
	SetDelayText();	
}

void CSAEditDlg::OnRbStartbutton() 
{
	// TODO: Add your control notification handler code here
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);

	m_pps.SetUseStartButton(true);
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(FALSE);
	//pDelay->SetPos(0);
	pDelay->EnableWindow(FALSE);
	SetDelayText();	
}

void CSAEditDlg::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CExcelOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}
