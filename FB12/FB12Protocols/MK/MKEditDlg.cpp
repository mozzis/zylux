// MKEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "MKEditDlg.h"
#include "General.h"
#include "ExcelOptions.h"

#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKEditDlg dialog

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


CMKEditDlg::CMKEditDlg(CMKPPS& ed_pps, LPCTSTR protocol_name, CWnd* pParent) : CProtocolDlg(protocol_name, CMKEditDlg::IDD, pParent),
			m_pps(ed_pps)
{
	//{{AFX_DATA_INIT(CMKEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMKEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMKEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMKEditDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CMKEditDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMKEditDlg message handlers

BOOL CMKEditDlg::OnInitDialog() 
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
	ASSERT(pDelay != NULL);
	CSpinButtonCtrl* pMeas = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_MEAS);
	ASSERT(pMeas != NULL);
	CSpinButtonCtrl* pDurationMin = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DURATIONMIN);
	ASSERT(pDurationMin != NULL);
	CSpinButtonCtrl* pDurationSec = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_DURATIONSEC);
	ASSERT(pDurationSec != NULL);
	CSpinButtonCtrl* pNumMeas = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_NUMMEAS);
	ASSERT(pNumMeas != NULL);
	CSpinButtonCtrl* pReps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_REPS);
	ASSERT(pReps != NULL);
	CSpinButtonCtrl* pSamps = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_SAMPS);
	ASSERT(pSamps != NULL);

	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);
	ASSERT(pComments != NULL);

	// Set Ranges and Positions on spinners.
	pDelay->SetRange(0, UD_MAXVAL);
	pDelay->SetPos(m_pps.m_delaytime / 2);
	pDelay->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);
	pMeas->SetRange(1, UD_MAXVAL);
	pMeas->SetPos(m_pps.m_meastime / 2);
	pMeas->SetAccel(sizeof(time_accel) / sizeof(UDACCEL), time_accel);
	m_duration = m_pps.m_intervaltime * m_pps.m_nummeasurements;
	pDurationMin->SetRange(0, UD_MAXVAL);
	pDurationMin->SetPos(m_duration / 600);
	pDurationMin->SetAccel(sizeof(durationmin_accel) / sizeof(UDACCEL), durationmin_accel);
	pDurationSec->SetRange(0, 299);	// 598 deciseconds / 2
	pDurationSec->SetPos((m_duration % 600) / 2);
	pNumMeas->SetRange(1, UD_MAXVAL);
	pNumMeas->SetPos(m_pps.m_nummeasurements);
	pReps->SetRange(1, UD_MAXVAL);
	pReps->SetPos(m_pps.m_numreps);
	pSamps->SetRange(1, UD_MAXVAL);
	pSamps->SetPos(m_pps.m_numsamps);

	//m_mininterval = (m_pps.m_delaytime + m_pps.m_meastime) * m_pps.m_numreps * m_pps.m_numsamps;

	// Initialize Text to m_pps values
	SetDelayText();
	SetMeasText();
	SetIntervalText();
	SetDurationText();

	pComments->LimitText(m_pps.COMMENT_SIZE - 1);
	pComments->SetWindowText(m_pps.m_comment);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMKEditDlg::SetDelayText()
{
	SetDlgItemText(IDC_EDIT_DELAY, SCFormatDeciseconds(m_pps.m_delaytime));
}

void CMKEditDlg::SetMeasText()
{
	SetDlgItemText(IDC_EDIT_MEAS, SCFormatDeciseconds(m_pps.m_meastime));
}


void CMKEditDlg::SetIntervalText()
{
	SetDlgItemText(IDC_EDIT_INTERVAL, SCFormatDeciseconds(m_pps.m_intervaltime));
}


void CMKEditDlg::SetDurationText()
{
	// Question: What is the duration?  interval * numsamps or interval * num_reps?
	//SetDlgItemText(IDC_EDIT_DURATION, 
	//	SCFormatDeciseconds(m_pps.m_intervaltime * m_pps.m_nummeasurements));
	SetDlgItemText(IDC_EDIT_DURATION, SCFormatDeciseconds(m_duration));

}

void CMKEditDlg::OnSave() 
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

void CMKEditDlg::OnSaveas() 
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


void CMKEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
			m_pps.m_intervaltime = m_duration / m_pps.m_nummeasurements;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_duration = m_pps.m_intervaltime * m_pps.m_nummeasurements;
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
			m_pps.m_intervaltime = m_duration / m_pps.m_nummeasurements;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_duration = m_pps.m_intervaltime * m_pps.m_nummeasurements;
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

		case IDC_SPIN_NUMMEAS:
			ASSERT(pControl != NULL);
			m_pps.m_nummeasurements = pControl->GetPos() & 0x0000ffff;
			m_pps.m_intervaltime = m_duration / m_pps.m_nummeasurements;
			m_pps.m_intervaltime = m_pps.m_intervaltime / 2 * 2;
			if (m_pps.m_intervaltime < 2)
			{
				m_pps.m_intervaltime = 2;
				m_pps.m_nummeasurements = m_duration / m_pps.m_intervaltime;
				pControl->SetPos(m_pps.m_nummeasurements);
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
/*
		case IDC_SPIN_SAMPS:
			{
				ASSERT(pControl != NULL);
				UINT numsamps = pControl->GetPos() & 0x0000ffff;
				if (m_pps.m_intervaltime < 
					((m_pps.m_delaytime + m_pps.m_meastime) * m_pps.m_numreps * numsamps))
				{
					m_pps.m_intervaltime = m_mininterval;
				}
			}
			break;

		case IDC_SPIN_REPS:
			ASSERT(pControl != NULL);
			m_pps.m_numreps = pControl->GetPos() & 0x0000ffff;
			m_mininterval = (m_pps.m_delaytime + m_pps.m_meastime) * m_pps.m_numreps * m_pps.m_numsamps;
			break;
*/
		default:
			CProtocolDlg::OnVScroll(nSBCode, nPos, pScrollBar);
			break;
	}
}

BOOL CMKEditDlg::VerifyEntries()
{
	UINT val = 0;
	BOOL is_ok = TRUE;

	val = GetDlgItemInt(IDC_EDIT_NUMMEAS, &is_ok, FALSE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of measurements.");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of measurements.");
			return FALSE;
		}
	}

	val = GetDlgItemInt(IDC_EDIT_REPS, &is_ok, FALSE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of replicates.");
		return FALSE;
	}
	else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of replicates.");
			return FALSE;
		}
	}

	val = 0;
	is_ok = TRUE;
	val = GetDlgItemInt(IDC_EDIT_SAMPS, &is_ok, FALSE);
	if (!is_ok)
	{
		SCMessageBox("Please enter an integer between 1 and 32,766 for number of samples.");
		return FALSE;
	} else 
	{
		if (val == 0)
		{
			SCMessageBox("Please enter an integer between 1 and 32,766 for number of samples.");
			return FALSE;
		}
	}


	return TRUE;
}


void CMKEditDlg::SetEntries()
{
	CString entry;
	entry.Empty();

	CEdit* pComments = (CEdit*) GetDlgItem(IDC_EDIT_COMMENTS);
	ASSERT(pComments != NULL);

	m_pps.SetNumReps(GetDlgItemInt(IDC_EDIT_REPS, NULL, FALSE));
	m_pps.SetNumSamps(GetDlgItemInt(IDC_EDIT_SAMPS, NULL, FALSE));
	m_pps.m_nummeasurements = GetDlgItemInt(IDC_EDIT_NUMMEAS, NULL, FALSE);

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

void CMKEditDlg::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CExcelOptions dlg(m_pps, m_protocolname);

	dlg.DoModal();
}
