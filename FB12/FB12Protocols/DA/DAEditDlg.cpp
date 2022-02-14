// DAEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DA.h"
#include "DAEditDlg.h"
#include "DAAdvanced.h"
#include "General.h"
#include "ExcelOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAEditDlg dialog


CDAEditDlg::CDAEditDlg(CDAPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CDAEditDlg::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CDAEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDAEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDAEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDAEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CDAEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_RADIO_DOORCLOSE, OnRadioDoorclose)
	ON_BN_CLICKED(IDC_RADIO_STARTBUTTON, OnRadioStartbutton)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAEditDlg message handlers

BOOL CDAEditDlg::OnInitDialog()
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

	// Set radio button
	if (m_pps.UseStartButton())
	{
		CButton* pStart = (CButton*)GetDlgItem(IDC_RADIO_STARTBUTTON);
		ASSERT(pStart != NULL);
		pStart->SetCheck(1);
	}
	else
	{
		CButton* pDoor = (CButton*)GetDlgItem(IDC_RADIO_DOORCLOSE);
		ASSERT(pDoor != NULL);
		pDoor->SetCheck(1);
	}

	// Set the spin controls
	CSpinButtonCtrl* pDelayA = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYA);
	ASSERT(pDelayA != NULL);
	CSpinButtonCtrl* pMeasA = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_MEASA);
	ASSERT(pMeasA != NULL);
	CSpinButtonCtrl* pDelayB = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYB);
	ASSERT(pDelayB != NULL);
	CSpinButtonCtrl* pMeasB = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_MEASB);
	ASSERT(pMeasB != NULL);
	CSpinButtonCtrl* pSamp = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NUMSAMP);
	ASSERT(pSamp != NULL);
	CSpinButtonCtrl* pRep = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NUMREP);
	ASSERT(pRep != NULL);

	pDelayA->SetRange(0, UD_MAXVAL);
	pDelayB->SetRange(0, UD_MAXVAL);

	pDelayA->SetPos(m_pps.m_delaytime_a / 2);
	pDelayB->SetPos(m_pps.m_delaytime_b / 2);
	if (m_pps.UseStartButton())
	{
		GetDlgItem(IDC_EDIT_DELAYA)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DELAYB)->EnableWindow(FALSE);
		pDelayA->EnableWindow(FALSE);
		pDelayB->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DELAYA)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DELAYB)->EnableWindow(TRUE);
		pDelayA->EnableWindow(TRUE);
		pDelayB->EnableWindow(TRUE);
	}

	pMeasA->SetRange(1, UD_MAXVAL);
	pMeasA->SetPos(m_pps.m_meastime_a / 2);
	pMeasB->SetRange(1, UD_MAXVAL);
	pMeasB->SetPos(m_pps.m_meastime_b / 2);
	pSamp->SetRange(1, UD_MAXVAL);
	pSamp->SetPos(m_pps.m_numsamples);
	pRep->SetRange(1, UD_MAXVAL);
	pRep->SetPos(m_pps.m_numreplicates);

	// Set the edit boxes
	SetDelayAText();
	SetMeasAText();
	SetDelayBText();
	SetMeasBText();
	CEdit* pComment = (CEdit*)GetDlgItem(IDC_EDIT_COMMENT);
	ASSERT(pComment != NULL);
	pComment->SetLimitText(CPPS::COMMENT_SIZE - 1);
	pComment->SetWindowText(m_pps.m_comment);

	// Set the combo boxes
	CComboBox* pXform = (CComboBox*)GetDlgItem(IDC_COMBO_XFORM);
	ASSERT(pXform != NULL);
	CComboBox* pOrder = (CComboBox*)GetDlgItem(IDC_COMBO_ORDER);
	ASSERT(pOrder != NULL);
	pXform->SetCurSel(m_pps.m_transform);
	pOrder->SetCurSel(m_pps.m_order);


	// Set checkboxes
	CButton* pBackground = (CButton*)GetDlgItem(IDC_CHECK_BACKGROUND);
	ASSERT(pBackground != NULL);
	pBackground->SetCheck(m_pps.UseBackground() ? 1 : 0);
	//CButton* pStamp = (CButton*)GetDlgItem(IDC_CHECK_TIMESTAMPS);
	//ASSERT(pStamp != NULL);
	//pStamp->SetCheck(m_pps.UseTimestamps() ? 1 : 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAEditDlg::SetDelayAText()
{
	SetDlgItemText(IDC_EDIT_DELAYA,
		SCFormatDeciseconds(m_pps.UseStartButton() ? 0 : m_pps.m_delaytime_a));
}

void CDAEditDlg::SetDelayBText()
{
	SetDlgItemText(IDC_EDIT_DELAYB,
		SCFormatDeciseconds(m_pps.UseStartButton() ? 0 : m_pps.m_delaytime_b));
}

void CDAEditDlg::SetMeasAText()
{
	SetDlgItemText(IDC_EDIT_MEASA, SCFormatDeciseconds(m_pps.m_meastime_a));
}

void CDAEditDlg::SetMeasBText()
{
	SetDlgItemText(IDC_EDIT_MEASB, SCFormatDeciseconds(m_pps.m_meastime_b));
}

void CDAEditDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if (VerifyFields())
	{
		ReadFields();
		m_pps.Save(m_protocolname);
		EndDialog(IDC_SAVE);
	}
}

void CDAEditDlg::OnSaveas()
{
	// TODO: Add your control notification handler code here
	m_pps.SetBase(false);
	m_pps.SetRunable(true);
	m_pps.SetDeleteable(true);
	m_pps.SetSaveable(true);
	if (VerifyFields())
	{
		ReadFields();
		if (m_pps.SaveAs(m_protocolname, false))
		{
			EndDialog(IDC_SAVEAS);
		}
	}
}

void CDAEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nControl = pScrollBar->GetDlgCtrlID();
	CSpinButtonCtrl* pControl = (CSpinButtonCtrl*) GetDlgItem(nControl);

	switch (nControl)
	{
		case IDC_SPIN_DELAYA:
			ASSERT(pControl != NULL);
			m_pps.m_delaytime_a = (pControl->GetPos() & 0x0000ffff) * 2;
			SetDelayAText();
			break;

		case IDC_SPIN_MEASA:
			ASSERT(pControl != NULL);
			m_pps.m_meastime_a = (pControl->GetPos() & 0x0000ffff) * 2;
			SetMeasAText();
			break;

		case IDC_SPIN_DELAYB:
			ASSERT(pControl != NULL);
			m_pps.m_delaytime_b = (pControl->GetPos() & 0x0000ffff) * 2;
			SetDelayBText();
			break;

		case IDC_SPIN_MEASB:
			ASSERT(pControl != NULL);
			m_pps.m_meastime_b = (pControl->GetPos() & 0x0000ffff) * 2;
			SetMeasBText();
			break;

		default:
			CProtocolDlg::OnVScroll(nSBCode, nPos, pScrollBar);
			break;
	}
}

void CDAEditDlg::ReadFields()
{
	CWnd* pWnd;

	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_NUMREP, NULL, TRUE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_NUMSAMP, NULL, TRUE));

	//BOOL success;
	//UINT value;
	//// Read the number of samples
	//value = GetDlgItemInt(IDC_EDIT_NUMSAMP, &success);
	//if (success)
	//{
	//	m_pps.m_numsamples = value;
	//}

	//// Read the number of replicates
	//value = GetDlgItemInt(IDC_EDIT_NUMREP, &success);
	//if (success)
	//{
	//	m_pps.m_numreplicates = value;
	//}

	// Read the comment
	GetDlgItemText(IDC_EDIT_COMMENT, m_pps.m_comment, CPPS::COMMENT_SIZE);
	//GetDlgItemText(IDC_EDIT_MACRO, m_pps.m_macroname, CGPPS::MACRONAME_SIZE);

	// Read the "start by" radio
	pWnd = GetDlgItem(IDC_RADIO_STARTBUTTON);
	ASSERT(pWnd != NULL);
	m_pps.SetUseStartButton((((CButton*)pWnd)->GetCheck() == 1) ? true : false);

	// Read the background and timestamps checkboxes
	pWnd = GetDlgItem(IDC_CHECK_BACKGROUND);
	ASSERT(pWnd != NULL);
	m_pps.SetUseBackground((((CButton*)pWnd)->GetCheck() == 1) ? true : false);
	//pWnd = GetDlgItem(IDC_CHECK_TIMESTAMPS);
	//ASSERT(pWnd != NULL);
	//m_pps.SetUseTimestamps((((CButton*)pWnd)->GetCheck() == 1) ? true : false);

	// Read the combo boxes
	int cursel;
	pWnd = GetDlgItem(IDC_COMBO_XFORM);
	ASSERT(pWnd != NULL);
	cursel = ((CComboBox*)pWnd)->GetCurSel();
	if (cursel != CB_ERR)
	{
		m_pps.m_transform = cursel;
	}
	pWnd = GetDlgItem(IDC_COMBO_ORDER);
	ASSERT(pWnd != NULL);
	cursel = ((CComboBox*)pWnd)->GetCurSel();
	if (cursel != CB_ERR)
	{
		m_pps.m_order = cursel;
	}
}

bool CDAEditDlg::VerifyFields()
{
	CWnd* pWnd;

	BOOL success;
	UINT value;
	// Verify number of samples
	value = GetDlgItemInt(IDC_EDIT_NUMSAMP, &success);
	if (!success || (value < 1) || (value > 32767))
	{
		SCMessageBox("Number of samples must be a between 1 and 32767.");
		pWnd = GetDlgItem(IDC_EDIT_NUMSAMP);
		ASSERT(pWnd != NULL);
		pWnd->SetFocus();
		((CEdit*)pWnd)->SetSel(0, -1, TRUE);
		return false;
	}

	// Verify number of replicates
	value = GetDlgItemInt(IDC_EDIT_NUMREP, &success);
	if (!success || (value < 1) || (value > 32767))
	{
		SCMessageBox("Number of replicates must be a between 1 and 32767.");
		pWnd = GetDlgItem(IDC_EDIT_NUMREP);
		ASSERT(pWnd != NULL);
		pWnd->SetFocus();
		((CEdit*)pWnd)->SetSel(0, -1, TRUE);
		return false;
	}

	int cursel;
	// Verify the transform
	pWnd = GetDlgItem(IDC_COMBO_XFORM);
	ASSERT(pWnd != NULL);
	cursel = ((CComboBox*)pWnd)->GetCurSel();
	if ((cursel == CB_ERR) ||
		(cursel < 0) || (cursel >= CDAPPS::XFORM_MAX))
	{
		SCMessageBox("Invalid transform selection.");
		pWnd->SetFocus();
		return false;
	}

	// Verify the transform
	pWnd = GetDlgItem(IDC_COMBO_ORDER);
	ASSERT(pWnd != NULL);
	cursel = ((CComboBox*)pWnd)->GetCurSel();
	if ((cursel == CB_ERR) ||
		(cursel < 0) || (cursel >= CDAPPS::ORDER_MAX))
	{
		SCMessageBox("Invalid order selection.");
		pWnd->SetFocus();
		return false;
	}

	return true;
}

void CDAEditDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here
	if (!VerifyFields())
	{
		return;
	}

	//ReadFields();
	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_NUMREP, NULL, TRUE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_NUMSAMP, NULL, TRUE));
	
	CDAAdvanced dlg(m_pps, m_protocolname);

	int nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
		SetDlgItemInt(IDC_EDIT_NUMREP, m_pps.m_numreplicates, FALSE);
		SetDlgItemInt(IDC_EDIT_NUMSAMP, m_pps.m_numsamples, FALSE);
	}	
}

void CDAEditDlg::OnRadioDoorclose() 
{
	// TODO: Add your control notification handler code here
	CSpinButtonCtrl* pDelayA = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYA);
	ASSERT(pDelayA != NULL);
	CSpinButtonCtrl* pDelayB = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYB);
	ASSERT(pDelayB != NULL);

	m_pps.SetUseStartButton(false);	
	GetDlgItem(IDC_EDIT_DELAYA)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DELAYB)->EnableWindow(TRUE);
	pDelayA->EnableWindow(TRUE);
	pDelayB->EnableWindow(TRUE);
	SetDelayAText();	
	SetDelayBText();	
}

void CDAEditDlg::OnRadioStartbutton() 
{
	// TODO: Add your control notification handler code here
	CSpinButtonCtrl* pDelayA = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYA);
	ASSERT(pDelayA != NULL);
	CSpinButtonCtrl* pDelayB = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAYB);
	ASSERT(pDelayB != NULL);

	m_pps.SetUseStartButton(true);
	GetDlgItem(IDC_EDIT_DELAYA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DELAYB)->EnableWindow(FALSE);
	pDelayA->EnableWindow(FALSE);
	pDelayB->EnableWindow(FALSE);

	SetDelayAText();	
	SetDelayBText();	
}

void CDAEditDlg::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CExcelOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}
