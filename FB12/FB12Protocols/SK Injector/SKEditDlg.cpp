// SKEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "SKEditDlg.h"
#include "General.h"
#include "SKAdvanced.h"
#include "ExcelOptions.h"
#include "InjectorOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKEditDlg dialog


CSKEditDlg::CSKEditDlg(CSKPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CSKEditDlg::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CSKEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSKEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSKEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSKEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CSKEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_NUMSAMP, OnKillfocusEditNumsamp)
	ON_BN_CLICKED(IDC_RADIO_STARTBUTTON, OnRadioStartbutton)
	ON_BN_CLICKED(IDC_RADIO_DOORCLOSE, OnRadioDoorclose)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_INJECTOR, OnInjector)
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

static UDACCEL durationmin_accel[] =
{
	{ 0, 1 },		// minutes
	{ 4, 5 },		// 5 minutes
	{ 8, 10 },		// 10 minutes
	{ 12, 100 },	// 100 minutes
	{ 16, 1000 }	// 1000 minutes
};

/////////////////////////////////////////////////////////////////////////////
// CSKEditDlg message handlers

BOOL CSKEditDlg::OnInitDialog()
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

	//if (!SKGetApp()->m_skoptions.m_injector)
	//{
	//	GetDlgItem(IDC_INJECTOR)->ShowWindow(SW_HIDE);
	//}

	// Set the spin controls
	CSpinButtonCtrl* pDelay = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DELAY);
	ASSERT(pDelay != NULL);
	CSpinButtonCtrl* pMeas = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_MEAS);
	ASSERT(pMeas != NULL);
	CSpinButtonCtrl* pDurationMin = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DURATIONMIN);
	ASSERT(pDurationMin != NULL);
	CSpinButtonCtrl* pDurationSec = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DURATIONSEC);
	ASSERT(pDurationSec != NULL);
	CSpinButtonCtrl* pSamp = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NUMSAMP);
	ASSERT(pSamp != NULL);
	CSpinButtonCtrl* pRep = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NUMREP);
	ASSERT(pRep != NULL);

	pDelay->SetRange(0, UD_MAXVAL);
	pDelay->SetPos(m_pps.m_delaytime / 2);
	pDelay->EnableWindow(!m_pps.UseStartButton());
	pDelay->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);
	CWnd* pWnd = GetDlgItem(IDC_EDIT_DELAY);
	pWnd->EnableWindow(!m_pps.UseStartButton());
	pMeas->SetRange(1, UD_MAXVAL);
	pMeas->SetPos(m_pps.m_meastime / 2);
	pMeas->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);
	m_duration = m_pps.m_intervaltime * m_pps.m_numsamples;
	pDurationMin->SetRange(0, UD_MAXVAL);
	pDurationMin->SetPos(m_duration / 600);
	pDurationMin->SetAccel(sizeof(durationmin_accel) / sizeof(UDACCEL), durationmin_accel);
	pDurationSec->SetRange(0, 299);	// 598 deciseconds / 2
	pDurationSec->SetPos((m_duration % 600) / 2);
	pSamp->SetRange(1, UD_MAXVAL);
	pSamp->SetPos(m_pps.m_numsamples);
	pRep->SetRange(1, UD_MAXVAL);
	pRep->SetPos(m_pps.m_numreplicates);

	// Set the edit boxes
	SetDelayText();
	SetMeasText();
	SetIntervalText();
	SetDurationText();
	CEdit* pComment = (CEdit*)GetDlgItem(IDC_EDIT_COMMENT);
	ASSERT(pComment != NULL);
	pComment->SetLimitText(CPPS::COMMENT_SIZE - 1);
	pComment->SetWindowText(m_pps.m_comment);

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

	// Set background and time basis checkboxes
	//CButton* pBackground = (CButton*)GetDlgItem(IDC_CHECK_BACKGROUND);
	//ASSERT(pBackground != NULL);
	//pBackground->SetCheck(m_pps.UseBackground() ? 1 : 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSKEditDlg::SetDelayText()
{
	SetDlgItemText(IDC_EDIT_DELAY, SCFormatDeciseconds(m_pps.UseStartButton() ? 0 : m_pps.m_delaytime));
}

void CSKEditDlg::SetMeasText()
{
	SetDlgItemText(IDC_EDIT_MEAS, SCFormatDeciseconds(m_pps.m_meastime));
}

void CSKEditDlg::SetIntervalText()
{
	SetDlgItemText(IDC_EDIT_INTERVAL, SCFormatDeciseconds(m_pps.m_intervaltime));
}

void CSKEditDlg::SetDurationText()
{
	SetDlgItemText(IDC_EDIT_DURATION,
		SCFormatDeciseconds(m_duration));
}

void CSKEditDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if (VerifyFields())
	{
		ReadFields();
		SKGetApp()->m_skoptions.Write();
		m_pps.Save(m_protocolname);
		EndDialog(IDC_SAVE);
	}
}

void CSKEditDlg::OnSaveas()
{
	// TODO: Add your control notification handler code here
	m_pps.SetBase(false);
	m_pps.SetRunable(true);
	m_pps.SetDeleteable(true);
	m_pps.SetSaveable(true);
	if (VerifyFields())
	{
		ReadFields();
		SKGetApp()->m_skoptions.Write();
		if (m_pps.SaveAs(m_protocolname, false))
		{
			EndDialog(IDC_SAVEAS);
		}
	}
}

void CSKEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
			if (m_pps.m_meastime > m_pps.m_intervaltime)
			{
				m_pps.m_meastime = m_pps.m_intervaltime;
				pControl->SetPos(m_pps.m_meastime / 2);
			}
			SetMeasText();
			break;
/*
		case IDC_SPIN_DURATIONMIN:
			ASSERT(pControl != NULL);
			m_duration = (pControl->GetPos() & 0x0000ffff) * 2;
			m_pps.m_intervaltime = m_duration / m_pps.m_numsamples;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_duration = m_pps.m_intervaltime * m_pps.m_numsamples;
				pControl->SetPos(m_duration / 2);
			}
			if (m_pps.m_intervaltime < m_pps.m_meastime)
			{
				m_pps.m_meastime = m_pps.m_intervaltime;
				pControl = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MEAS);
				ASSERT(pControl != NULL);
				pControl->SetPos(m_pps.m_meastime / 2);
				SetMeasText();
			}
			SetDurationText();
			SetIntervalText();
			break;
*/
		case IDC_SPIN_DURATIONMIN:
			ASSERT(pControl != NULL);
			m_duration = (pControl->GetPos() & 0x0000ffff) * 600;
			m_duration += (((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONSEC))->GetPos() & 0x0000ffff) * 2;
			if (m_duration < 2)
			{
				m_duration = 2;
				pControl->SetPos(m_duration / 600);
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONSEC))->SetPos((m_duration % 600) / 2);
			}
			m_pps.m_intervaltime = m_duration / m_pps.m_numsamples;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_duration = m_pps.m_intervaltime * m_pps.m_numsamples;
				pControl->SetPos(m_duration / 600);
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONSEC))->SetPos((m_duration % 600) / 2);
			}
			if (m_pps.m_intervaltime < m_pps.m_meastime)
			{
				m_pps.m_meastime = m_pps.m_intervaltime;
				pControl = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MEAS);
				ASSERT(pControl != NULL);
				pControl->SetPos(m_pps.m_meastime / 2);
				SetMeasText();
			}
			SetDurationText();
			SetIntervalText();
			break;

		case IDC_SPIN_DURATIONSEC:
			ASSERT(pControl != NULL);
			m_duration = (pControl->GetPos() & 0x0000ffff) * 2;
			m_duration += (((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONMIN))->GetPos() & 0x0000ffff) * 600;
			if (m_duration < 2)
			{
				m_duration = 2;
				pControl->SetPos((m_duration % 600) / 2);
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONMIN))->SetPos(m_duration / 600);
			}
			m_pps.m_intervaltime = m_duration / m_pps.m_numsamples;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_duration = m_pps.m_intervaltime * m_pps.m_numsamples;
				pControl->SetPos((m_duration % 600) / 2);
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DURATIONMIN))->SetPos(m_duration / 600);
			}
			if (m_pps.m_intervaltime < m_pps.m_meastime)
			{
				m_pps.m_meastime = m_pps.m_intervaltime;
				pControl = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MEAS);
				ASSERT(pControl != NULL);
				pControl->SetPos(m_pps.m_meastime / 2);
				SetMeasText();
			}
			SetDurationText();
			SetIntervalText();
			break;

		case IDC_SPIN_NUMSAMP:
			ASSERT(pControl != NULL);
			m_pps.m_numsamples = pControl->GetPos() & 0x0000ffff;
			m_pps.m_intervaltime = m_duration / m_pps.m_numsamples;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_pps.m_numsamples = m_duration / m_pps.m_intervaltime;
				pControl->SetPos(m_pps.m_numsamples);
			}
			if (m_pps.m_intervaltime < m_pps.m_meastime)
			{
				m_pps.m_meastime = m_pps.m_intervaltime;
				pControl = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MEAS);
				ASSERT(pControl != NULL);
				pControl->SetPos(m_pps.m_meastime / 2);
				SetMeasText();
			}
			SetIntervalText();
			break;

		default:
			CProtocolDlg::OnVScroll(nSBCode, nPos, pScrollBar);
			break;
	}
}

void CSKEditDlg::ReadFields()
{
	BOOL success;
	UINT value;
	// Read the number of samples
	value = GetDlgItemInt(IDC_EDIT_NUMSAMP, &success);
	if (success)
	{
		m_pps.m_numsamples = value;
	}

	// Read the number of replicates
	value = GetDlgItemInt(IDC_EDIT_NUMREP, &success);
	if (success)
	{
		m_pps.m_numreplicates = value;
	}

	// Read the comment
	GetDlgItemText(IDC_EDIT_COMMENT, m_pps.m_comment, CPPS::COMMENT_SIZE);

	// Read the "start by" radio
	//pWnd = GetDlgItem(IDC_RADIO_STARTBUTTON);
	//ASSERT(pWnd != NULL);
	//m_pps.SetUseStartButton((((CButton*)pWnd)->GetCheck() == 1) ? true : false);

	// Read the background and time basis checkboxes
	//pWnd = GetDlgItem(IDC_CHECK_BACKGROUND);
	//ASSERT(pWnd != NULL);
	//m_pps.SetUseBackground((((CButton*)pWnd)->GetCheck() == 1) ? true : false);
}

bool CSKEditDlg::VerifyFields()
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


	UINT max_time = (m_pps.m_intervaltime * value) + m_pps.m_delaytime;
	bool any_changed = false;
	for (int i=0; i < CSKPPS::MAX_INJECTIONS; i++)
	{
		if (m_pps.m_injections[i].m_time > max_time)
		{
			m_pps.m_injections[i].m_time = max_time;
			any_changed = true;
		}
	}
	if (any_changed)
	{
		SCMessageBox("Injection Times were changed to occur within the duration time");
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


	return true;
}

void CSKEditDlg::OnKillfocusEditNumsamp() 
{
	// TODO: Add your control notification handler code here
	// Read the number of samples
	BOOL success;
	UINT value;
	value = GetDlgItemInt(IDC_EDIT_NUMSAMP, &success);
	if (success)
	{
		CSpinButtonCtrl* pControl = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_NUMSAMP);
		ASSERT(pControl != NULL);
		pControl->SetPos(value);
		if (value != m_pps.m_numsamples)
		{
			m_pps.m_numsamples = value;
			SetDurationText();
		}
	}
}

BOOL CSKEditDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ((pMsg->message == WM_KEYDOWN) &&
		(pMsg->wParam == VK_RETURN))
	{
		if (SCHasFocus(IDC_EDIT_NUMSAMP))
		{
			OnKillfocusEditNumsamp();
			return TRUE;
		}
	}
		
	return CProtocolDlg::PreTranslateMessage(pMsg);
}

void CSKEditDlg::OnRadioStartbutton() 
{
	// TODO: Add your control notification handler code here
	m_pps.SetUseStartButton(true);
	CWnd* pDelay = GetDlgItem(IDC_SPIN_DELAY);
	pDelay->EnableWindow(false);
	pDelay = GetDlgItem(IDC_EDIT_DELAY);
	pDelay->EnableWindow(false);
	SetDelayText();
}

void CSKEditDlg::OnRadioDoorclose() 
{
	// TODO: Add your control notification handler code here
	m_pps.SetUseStartButton(false);
	CWnd* pDelay = GetDlgItem(IDC_SPIN_DELAY);
	pDelay->EnableWindow(true);
	pDelay = GetDlgItem(IDC_EDIT_DELAY);
	pDelay->EnableWindow(true);
	SetDelayText();
}

void CSKEditDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here
	if (!VerifyFields())
	{
		return;
	}

	CSKAdvanced dlg(m_pps, m_protocolname);

	dlg.DoModal();
}

void CSKEditDlg::OnExcel() 
{
	// TODO: Add your control notification handler code here
	if (!VerifyFields())
	{
		return;
	}

	CExcelOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}

void CSKEditDlg::OnInjector() 
{
	// TODO: Add your control notification handler code here
	CInjectorOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}
