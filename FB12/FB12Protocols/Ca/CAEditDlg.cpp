// CAEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CA.h"
#include "CAEditDlg.h"
#include "CAAdvancedDlg.h"
#include "General.h"
#include "ExcelOptions.h"

#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAEditDlg dialog


CCAEditDlg::CCAEditDlg(CCAPPS& ed_pps, LPCTSTR protocol_name, CWnd* pParent) : CProtocolDlg(protocol_name, CCAEditDlg::IDD, pParent),
			m_pps(ed_pps)
{
	//{{AFX_DATA_INIT(CCAEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCAEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCAEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CCAEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_RB_STARTBUTTON, OnRbStartbutton)
	ON_BN_CLICKED(IDC_RB_DOORCLOSE, OnRbDoorclose)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAEditDlg message handlers

BOOL CCAEditDlg::OnInitDialog() 
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
	CSpinButtonCtrl* pAnaReps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_ANAREPS);
	CSpinButtonCtrl* pAnaSamps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_ANASAMPS);
	CSpinButtonCtrl* pPosReps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_POSREPS);
	CSpinButtonCtrl* pNegReps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NEGREPS);

	//CButton* pTimestamp = (CButton*) GetDlgItem(IDC_CB_TIMESTAMP);
	CButton* pDoorClose = (CButton*) GetDlgItem(IDC_RB_DOORCLOSE);
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CButton* pBackground = (CButton*) GetDlgItem(IDC_CB_BACKGROUND);
	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);

	// Set the appropriate checkbox for start measurement by...
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
	// Disable delay time (and make it zero) if start button used.
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
	pAnaReps->SetRange(1, UD_MAXVAL);
	pAnaReps->SetPos(m_pps.m_numreps);
	pAnaSamps->SetRange(1, UD_MAXVAL);
	pAnaSamps->SetPos(m_pps.m_numsamps);
	pPosReps->SetRange(0, UD_MAXVAL);
	pPosReps->SetPos(m_pps.m_numposreps);
	pNegReps->SetRange(0, UD_MAXVAL);
	pNegReps->SetPos(m_pps.m_numnegreps);
	
	// Initialize Text to m_pps values
	SetDelayText();
	SetMeasText();
	SetCalculationsText();
	SetDlgItemInt(IDC_EDIT_ANAREPS, m_pps.m_numreps, FALSE);
	SetDlgItemInt(IDC_EDIT_ANASAMPS, m_pps.m_numsamps, FALSE);
	SetDlgItemInt(IDC_EDIT_POSREPS, m_pps.m_numposreps, FALSE);
	SetDlgItemInt(IDC_EDIT_NEGREPS, m_pps.m_numnegreps, FALSE);

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

void CCAEditDlg::SetDelayText()
{
	SetDlgItemText(IDC_EDIT_DELAY, SCFormatDeciseconds(m_pps.UseStartButton() ? 0 : m_pps.m_delaytime));
}

void CCAEditDlg::SetMeasText()
{
	SetDlgItemText(IDC_EDIT_MEAS, SCFormatDeciseconds(m_pps.m_meastime));
}


void CCAEditDlg::SetCalculationsText()
{
	CString double_str;

	// low cut-off offset
	double_str.Format("%ld", m_pps.m_lowoffset);
	SetDlgItemText(IDC_EDIT_LOWOFF, double_str);
	// high cut-off offset
	double_str.Format("%ld", m_pps.m_highoffset);
	SetDlgItemText(IDC_EDIT_HIGHOFF, double_str);
	// low cut-off factor
	double_str.Format("%.2f", m_pps.m_lowfactor);
	SetDlgItemText(IDC_EDIT_LOWFACTOR, double_str);
	// high cut-off factor
	double_str.Format("%.2f", m_pps.m_highfactor);
	SetDlgItemText(IDC_EDIT_HIGHFACTOR, double_str);
	// low cut-off lpos. factor
	double_str.Format("%.2f", m_pps.m_low_lposfactor);
	SetDlgItemText(IDC_EDIT_LOWLPOSFACT, double_str);
	// high cut-off lpos. factor
	double_str.Format("%.2f", m_pps.m_high_lposfactor);
	SetDlgItemText(IDC_EDIT_HIGHLPOSFACT, double_str);
}


void CCAEditDlg::OnSave() 
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

void CCAEditDlg::OnSaveas() 
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


void CCAEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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

void CCAEditDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here

	if (!VerifyEntries())
	{
		return;
	}

	SetEntries();
	
	CCAAdvancedDlg dlg(m_pps, m_protocolname);

	int nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
		SetDlgItemInt(IDC_EDIT_ANAREPS, (UINT) m_pps.m_numreps, TRUE);
		SetDlgItemInt(IDC_EDIT_ANASAMPS, (UINT) m_pps.m_numsamps, TRUE);
	}

}


BOOL CCAEditDlg::VerifyEntries()
{
	UINT val = 0;
	BOOL is_ok = TRUE;

	val = GetDlgItemInt(IDC_EDIT_ANAREPS, &is_ok, TRUE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of analyte replicates.");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of analyte replicates.");
			return FALSE;
		}
	}

	val = 0;
	is_ok = TRUE;
	val = GetDlgItemInt(IDC_EDIT_ANASAMPS, &is_ok, TRUE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of analyte samples.");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of analyte samples.");
			return FALSE;
		}
	}

	val = 0;
	is_ok = TRUE;
	val = GetDlgItemInt(IDC_EDIT_NEGREPS, &is_ok, TRUE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 0 and 32,766 for\nthe number of negative control replicates.");
		return FALSE;
	}

	val = 0;
	is_ok = TRUE;
	val = GetDlgItemInt(IDC_EDIT_POSREPS, &is_ok, TRUE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 0 and 32,766 for\nthe number of positive control replicates.");
		return FALSE;
	} 


	CString entry;


	if (GetDlgItemText(IDC_EDIT_LOWFACTOR, entry) == 0)
	{
		SCMessageBox("Please enter a value for the low cut-off negative factor.");
		return FALSE;
	}

	if (GetDlgItemText(IDC_EDIT_HIGHFACTOR, entry) == 0)
	{
		SCMessageBox("Please enter a value for the high cut-off negative factor.");
		return FALSE;
	}

	if (GetDlgItemText(IDC_EDIT_LOWLPOSFACT, entry) == 0)
	{
		SCMessageBox("Please enter a value for the low cut-off positive factor.");
		return FALSE;
	}

	if (GetDlgItemText(IDC_EDIT_HIGHLPOSFACT, entry) == 0)
	{
		SCMessageBox("Please enter a value for the high cut-off positive factor.");
		return FALSE;
	}


	if (GetDlgItemText(IDC_EDIT_LOWOFF, entry) == 0)
	{
		SCMessageBox("Please enter a value for the low cut-off offset.");
		return FALSE;
	}
	if (GetDlgItemText(IDC_EDIT_HIGHOFF, entry) == 0)
	{
		SCMessageBox("Please enter a value for the high cut-off offset.");
		return FALSE;
	}


	return TRUE;
}


void CCAEditDlg::SetEntries()
{
	CString entry;
	entry.Empty();

	//CButton* pTimestamp = (CButton*) GetDlgItem(IDC_CB_TIMESTAMP);
	CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CButton* pBackground = (CButton*) GetDlgItem(IDC_CB_BACKGROUND);
	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);

	if (pStartButton->GetCheck())
	{
		m_pps.SetUseStartButton(true);
	}
	else
	{
		m_pps.SetUseStartButton(false);
	}

	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_ANAREPS, NULL, TRUE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_ANASAMPS, NULL, TRUE));
	m_pps.SetNegReps(GetDlgItemInt(IDC_EDIT_NEGREPS, NULL, FALSE));
	m_pps.SetPosReps(GetDlgItemInt(IDC_EDIT_POSREPS, NULL, FALSE));

	GetDlgItemText(IDC_EDIT_LOWFACTOR, entry);
	m_pps.m_lowfactor = atof(LPCTSTR(entry));
	GetDlgItemText(IDC_EDIT_HIGHFACTOR, entry);
	m_pps.m_highfactor = atof(LPCTSTR(entry));
	GetDlgItemText(IDC_EDIT_LOWLPOSFACT, entry);
	m_pps.m_low_lposfactor = atof(LPCTSTR(entry));
	GetDlgItemText(IDC_EDIT_HIGHLPOSFACT, entry);
	m_pps.m_high_lposfactor = atof(LPCTSTR(entry));

	GetDlgItemText(IDC_EDIT_LOWOFF, entry);
	m_pps.m_lowoffset = atol(LPCTSTR(entry));
	GetDlgItemText(IDC_EDIT_HIGHOFF, entry);
	m_pps.m_highoffset = atol(LPCTSTR(entry));

	if (pBackground->GetCheck())
	{
		m_pps.SetUseBackground(true);
	}
	else
	{
		m_pps.SetUseBackground(false);
	}

	//if (pTimestamp->GetCheck())
	//{
	//	m_pps.SetUseTimestamps(true);
	//}
	//else
	//{
	//	m_pps.SetUseTimestamps(false);
	//}
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


void CCAEditDlg::OnRbStartbutton() 
{
	// TODO: Add your control notification handler code here
	//CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);

	m_pps.SetUseStartButton(true);
	//pDelay->SetPos(0);
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(FALSE);
	pDelay->EnableWindow(FALSE);
	SetDelayText();
}

void CCAEditDlg::OnRbDoorclose() 
{
	// TODO: Add your control notification handler code here
	//CButton* pStartButton = (CButton*) GetDlgItem(IDC_RB_STARTBUTTON);
	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);

	m_pps.SetUseStartButton(false);	
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(TRUE);
	pDelay->EnableWindow(TRUE);
	//pDelay->SetPos(m_pps.m_delaytime / 2);
	SetDelayText();
}

void CCAEditDlg::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CExcelOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}
