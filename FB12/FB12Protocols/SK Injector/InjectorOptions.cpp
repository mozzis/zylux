// InjectorOptions.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "InjectorOptions.h"
#include "General.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UDACCEL min_accel[] =
{
	{ 0, 1 },		// minutes
	{ 4, 5 },		// 5 minutes
	{ 8, 10 },		// 10 minutes
	{ 12, 100 },	// 100 minutes
	{ 16, 1000 }	// 1000 minutes
};

  
/////////////////////////////////////////////////////////////////////////////
// CInjectorOptions dialog


CInjectorOptions::CInjectorOptions(CSKPPS &skpps, LPCTSTR protocolname, CWnd* pParent /*=NULL*/)
	: CProtocolDlg(protocolname, CInjectorOptions::IDD, pParent), m_skpps(skpps), 
	m_skoptions(SKGetApp()->m_skoptions)
{
	//{{AFX_DATA_INIT(CInjectorOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for (int i=0; i < CSKPPS::MAX_INJECTIONS; i++)
	{
		m_injections[i] = skpps.m_injections[i];
	}
	m_max_vol = m_skoptions.m_volume;
	m_max_vol2 = m_skoptions.m_volume2;
}


void CInjectorOptions::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInjectorOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInjectorOptions, CProtocolDlg)
	//{{AFX_MSG_MAP(CInjectorOptions)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_VOL1, OnKillfocusEditVol1)
	ON_EN_KILLFOCUS(IDC_EDIT_VOL2, OnKillfocusEditVol2)
	ON_EN_KILLFOCUS(IDC_EDIT_VOL3, OnKillfocusEditVol3)
	ON_EN_KILLFOCUS(IDC_EDIT_VOL4, OnKillfocusEditVol4)
	ON_EN_KILLFOCUS(IDC_EDIT_VOL5, OnKillfocusEditVol5)
	ON_BN_CLICKED(IDC_CHECK_INJECTOR, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_NOINJECT, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_ONEINJECT, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_SKIP1, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_SKIP2, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_SKIP3, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_SKIP4, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_SKIP5, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_TWOINJECT, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE1_1, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE1_2, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE1_3, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE1_4, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE1_5, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE2_1, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE2_2, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE2_3, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE2_4, OnCheckInjector)
	ON_BN_CLICKED(IDC_RADIO_USE2_5, OnCheckInjector)
	ON_CBN_SELENDOK(IDC_COMBO_VOLUME, OnChangeVolume)
	ON_CBN_SELENDOK(IDC_COMBO_VOLUME2, OnChangeVolume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectorOptions message handlers

BOOL CInjectorOptions::OnInitDialog() 
{
	CProtocolDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	ASSERT(pIPort != NULL);
	if ((m_skoptions.m_injectport < 1) || (m_skoptions.m_injectport > 8))
		m_skoptions.m_injectport = 1;

	pIPort->SetCurSel(m_skoptions.m_injectport - 1);

	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	ASSERT(pVolume != NULL);
	switch(m_skoptions.m_volume)
	{
	case 50:
		pVolume->SetCurSel(0);
		break;

	case 100:
		pVolume->SetCurSel(1);
		break;

	case 250:
		pVolume->SetCurSel(2);
		break;

	case 500:
		pVolume->SetCurSel(3);
		break;

	case 1000:
		pVolume->SetCurSel(4);
		break;

	case 2500:
	default:
		pVolume->SetCurSel(5);
		break;
	}

	pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME2);
	ASSERT(pVolume != NULL);
	switch(m_skoptions.m_volume2)
	{
	case 50:
		pVolume->SetCurSel(0);
		break;

	case 100:
		pVolume->SetCurSel(1);
		break;

	case 250:
		pVolume->SetCurSel(2);
		break;

	case 500:
		pVolume->SetCurSel(3);
		break;

	case 1000:
		pVolume->SetCurSel(4);
		break;

	case 2500:
	default:
		pVolume->SetCurSel(5);
		break;
	}

	CComboBox* pSpeed = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED);
	ASSERT(pSpeed != NULL);
	pSpeed->SetCurSel(m_skoptions.m_speed - 1);

	pSpeed = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED2);
	ASSERT(pSpeed != NULL);
	pSpeed->SetCurSel(m_skoptions.m_speed2 - 1);

	// Set the spin controls
	int inject_num = 0;
	m_skips[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_SKIP1);
	m_inject1s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE1_1);
	m_inject2s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE2_1);
	m_times[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_TIME1);
	m_volumes[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_VOL1);
	m_minute_spinners[inject_num] = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_TIME1MIN);
	m_second_spinners[inject_num] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TIME1SEC);
	m_volume_spinners[inject_num++] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_VOL1);

	m_skips[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_SKIP2);
	m_inject1s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE1_2);
	m_inject2s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE2_2);
	m_times[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_TIME2);
	m_volumes[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_VOL2);
	m_minute_spinners[inject_num] = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_TIME2MIN);
	m_second_spinners[inject_num] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TIME2SEC);
	m_volume_spinners[inject_num++] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_VOL2);

	m_skips[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_SKIP3);
	m_inject1s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE1_3);
	m_inject2s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE2_3);
	m_times[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_TIME3);
	m_volumes[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_VOL3);
	m_minute_spinners[inject_num] = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_TIME3MIN);
	m_second_spinners[inject_num] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TIME3SEC);
	m_volume_spinners[inject_num++] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_VOL3);

	m_skips[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_SKIP4);
	m_inject1s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE1_4);
	m_inject2s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE2_4);
	m_times[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_TIME4);
	m_volumes[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_VOL4);
	m_minute_spinners[inject_num] = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_TIME4MIN);
	m_second_spinners[inject_num] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TIME4SEC);
	m_volume_spinners[inject_num++] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_VOL4);

	m_skips[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_SKIP5);
	m_inject1s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE1_5);
	m_inject2s[inject_num] = (CButton *) GetDlgItem(IDC_RADIO_USE2_5);
	m_times[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_TIME5);
	m_volumes[inject_num] = (CEdit *) GetDlgItem(IDC_EDIT_VOL5);
	m_minute_spinners[inject_num] = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_TIME5MIN);
	m_second_spinners[inject_num] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TIME5SEC);
	m_volume_spinners[inject_num++] = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_VOL5);

	InitTimes();
	InitVolumes();

	for (inject_num = 0; inject_num < CSKPPS::MAX_INJECTIONS; inject_num++)
	{
		switch(m_injections[inject_num].m_used)
		{
			case 0:
				m_skips[inject_num]->SetCheck(1);
			break;
			case 1:
				m_inject1s[inject_num]->SetCheck(1);
			break;
			case 2:
				m_inject2s[inject_num]->SetCheck(1);
			break;
			default:
				m_skips[inject_num]->SetCheck(1);
			break;
		}
	}

	CButton* pInject;
	switch(m_skoptions.m_num_injectors)
	{
		case 0:
			pInject = (CButton*)GetDlgItem(IDC_RADIO_NOINJECT);
			pInject->SetCheck(1);
		break;
		case 1:
			pInject = (CButton*)GetDlgItem(IDC_RADIO_ONEINJECT);
			pInject->SetCheck(1);
		break;
		case 2:
			pInject = (CButton*)GetDlgItem(IDC_RADIO_TWOINJECT);
			pInject->SetCheck(1);
		break;
		default:
			pInject = (CButton*)GetDlgItem(IDC_RADIO_NOINJECT);
			pInject->SetCheck(1);
		break;
	}

	OnCheckInjector();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInjectorOptions::InitTimes()
{

	UINT max_time = (m_skpps.m_intervaltime * m_skpps.m_numsamples) + m_skpps.m_delaytime;
	UINT max_minutes = max_time / 600;

	int inject_num;
	for (inject_num = 0; inject_num < CSKPPS::MAX_INJECTIONS; inject_num++)
	{
		m_minute_spinners[inject_num]->SetRange(0, max_minutes);
		m_minute_spinners[inject_num]->SetPos(m_injections[inject_num].m_time / 600);
		m_minute_spinners[inject_num]->SetAccel(sizeof(min_accel) / sizeof(UDACCEL), min_accel);

		m_second_spinners[inject_num]->SetRange(0, ((max_time /2) > 299) ? 299 : (max_time / 2));
		m_second_spinners[inject_num]->SetPos((m_injections[inject_num].m_time % 600) / 2);

		m_times[inject_num]->SetWindowText(SCFormatDeciseconds(m_injections[inject_num].m_time));
	}
}


void CInjectorOptions::InitVolumes()
{
	int inject_num;
	CString str;
	for (inject_num = 0; inject_num < CSKPPS::MAX_INJECTIONS; inject_num++)
	{
		m_volume_spinners[inject_num]->SetRange(0,
			(m_injections[inject_num].m_used == 1) ? m_max_vol : m_max_vol2);
		m_volume_spinners[inject_num]->SetPos(m_injections[inject_num].m_volume);
		str.Format("%ld", m_injections[inject_num].m_volume);
		m_volumes[inject_num]->SetWindowText(str);
	}
}



void CInjectorOptions::EnableInjections(int index, BOOL enable)
{
	m_times[index]->EnableWindow(enable);
	m_volumes[index]->EnableWindow(enable);
	m_minute_spinners[index]->EnableWindow(enable);
	m_second_spinners[index]->EnableWindow(enable);
	m_volume_spinners[index]->EnableWindow(enable);

}

void CInjectorOptions::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nControl = pScrollBar->GetDlgCtrlID();
	int index = -1;
	int which_spin = -1;

	switch (nControl)
	{
		case IDC_SPIN_TIME1MIN:
			index = 0;
			which_spin = 0;
		break;
		case IDC_SPIN_TIME2MIN:
			index = 1;
			which_spin = 0;
		break;
		case IDC_SPIN_TIME3MIN:
			index = 2;
			which_spin = 0;
		break;
		case IDC_SPIN_TIME4MIN:
			index = 3;
			which_spin = 0;
		break;
		case IDC_SPIN_TIME5MIN:
			index = 4;
			which_spin = 0;
		break;

		case IDC_SPIN_TIME1SEC:
			index = 0;
			which_spin = 1;
		break;
		case IDC_SPIN_TIME2SEC:
			index = 1;
			which_spin = 1;
		break;
		case IDC_SPIN_TIME3SEC:
			index = 2;
			which_spin = 1;
		break;
		case IDC_SPIN_TIME4SEC:
			index = 3;
			which_spin = 1;
		break;
		case IDC_SPIN_TIME5SEC:
			index = 4;
			which_spin = 1;
		break;

		case IDC_SPIN_VOL1:
			index = 0;
			which_spin = 2;
		break;
		case IDC_SPIN_VOL2:
			index = 1;
			which_spin = 2;
		break;
		case IDC_SPIN_VOL3:
			index = 2;
			which_spin = 2;
		break;
		case IDC_SPIN_VOL4:
			index = 3;
			which_spin = 2;
		break;
		case IDC_SPIN_VOL5:
			index = 4;
			which_spin = 2;
		break;

		default:
		break;
	}

	if ((index >= 0) && (which_spin >= 0))
	{
		switch(which_spin)
		{
			case 0:  // Minute spinner
			case 1:	 // Second spinner
			{
				UINT max_time = (m_skpps.m_intervaltime * m_skpps.m_numsamples) + m_skpps.m_delaytime;
				m_injections[index].m_time = (m_minute_spinners[index]->GetPos() & 0x0000ffff) * 600;
				m_injections[index].m_time += (m_second_spinners[index]->GetPos() & 0x0000ffff) * 2;
				if (m_injections[index].m_time < 2)
				{
					m_injections[index].m_time = 2;
					m_minute_spinners[index]->SetPos(m_injections[index].m_time / 600);
					m_second_spinners[index]->SetPos((m_injections[index].m_time % 600) / 2);
				}
				else if (m_injections[index].m_time > max_time)
				{
					m_injections[index].m_time = max_time;
					m_minute_spinners[index]->SetPos(m_injections[index].m_time / 600);
					m_second_spinners[index]->SetPos((m_injections[index].m_time % 600) / 2);
				}
				m_times[index]->SetWindowText(SCFormatDeciseconds(m_injections[index].m_time));
			}
			break;

			case 2:
			{
				CString str;
				m_injections[index].m_volume = (m_volume_spinners[index]->GetPos() & 0x0000ffff);
				str.Format("%ld", m_injections[index].m_volume);
				m_volumes[index]->SetWindowText(str);
			}
			break;
			default:
			break;
		}
	}
	CProtocolDlg::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CInjectorOptions::OnOK() 
{
	// TODO: Add extra validation here
	for (int i=0; i < CSKPPS::MAX_INJECTIONS; i++)
	{
		m_skpps.m_injections[i] = m_injections[i];
		SetVolume(i);
	}
	m_skpps.SortInjections();

	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	ASSERT(pIPort != NULL);
	m_skoptions.m_injectport = pIPort->GetCurSel() + 1;

	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	ASSERT(pVolume != NULL);
	switch(pVolume->GetCurSel())
	{
	case 0:
		m_skoptions.m_volume = 50;
		break;

	case 1:
		m_skoptions.m_volume = 100;
		break;

	case 2:
		m_skoptions.m_volume = 250;
		break;

	case 3:
		m_skoptions.m_volume = 500;
		break;

	case 4:
		m_skoptions.m_volume = 1000;
		break;

	case 5:
	default:
		m_skoptions.m_volume = 2500;
		break;
	}

	pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME2);
	ASSERT(pVolume != NULL);
	switch(pVolume->GetCurSel())
	{
	case 0:
		m_skoptions.m_volume2 = 50;
		break;

	case 1:
		m_skoptions.m_volume2 = 100;
		break;

	case 2:
		m_skoptions.m_volume2 = 250;
		break;

	case 3:
		m_skoptions.m_volume2 = 500;
		break;

	case 4:
		m_skoptions.m_volume2 = 1000;
		break;

	case 5:
	default:
		m_skoptions.m_volume2 = 2500;
		break;
	}

	CComboBox* pSpeed = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED);
	ASSERT(pSpeed != NULL);
	m_skoptions.m_speed = pSpeed->GetCurSel() + 1;

	pSpeed = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED2);
	ASSERT(pSpeed != NULL);
	m_skoptions.m_speed2 = pSpeed->GetCurSel() + 1;

	if (IsDlgButtonChecked(IDC_RADIO_NOINJECT))
		m_skoptions.m_num_injectors = 0;
	else if (IsDlgButtonChecked(IDC_RADIO_ONEINJECT))
		m_skoptions.m_num_injectors = 1;
	else
		m_skoptions.m_num_injectors = 2;

	CProtocolDlg::OnOK();
}


void CInjectorOptions::SetVolume(int index)
{
	CString vol_str;
	m_volumes[index]->GetWindowText(vol_str);
	long vol = atol(LPCTSTR(vol_str));
	vol = (vol < 0) ? 0 : vol;
	if (m_injections[index].m_used == 1)
		vol = (vol > m_max_vol) ? m_max_vol : vol;
	else
		vol = (vol > m_max_vol2) ? m_max_vol2 : vol;
	m_injections[index].m_volume = vol;
	vol_str.Format("%ld", vol);
	m_volumes[index]->SetWindowText(vol_str);
}

void CInjectorOptions::OnKillfocusEditVol1() 
{
	// TODO: Add your control notification handler code here
	SetVolume(0);
	
}

void CInjectorOptions::OnKillfocusEditVol2() 
{
	// TODO: Add your control notification handler code here
	SetVolume(1);
	
}

void CInjectorOptions::OnKillfocusEditVol3() 
{
	// TODO: Add your control notification handler code here
	SetVolume(2);	
	
}

void CInjectorOptions::OnKillfocusEditVol4() 
{
	// TODO: Add your control notification handler code here
	SetVolume(3);	
	
}

void CInjectorOptions::OnKillfocusEditVol5() 
{
	// TODO: Add your control notification handler code here
	SetVolume(4);	
	
}

void CInjectorOptions::OnCheckInjector() 
{
	// TODO: Add your control notification handler code here
	CButton* pInject = (CButton*)GetDlgItem(IDC_RADIO_NOINJECT);
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	CComboBox* pSpeed = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED);
	CComboBox* pVolume2 = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME2);
	CComboBox* pSpeed2 = (CComboBox*)GetDlgItem(IDC_COMBO_SPEED2);
	CStatic* pIParams = (CStatic *)GetDlgItem(IDC_GROUP_INJECTOR);
	CStatic* pSIPort = (CStatic *)GetDlgItem(IDC_STATIC_IPORT);
	CStatic* pSVolume = (CStatic *)GetDlgItem(IDC_STATIC_VOLUME);
	CStatic* pSSpeed = (CStatic *)GetDlgItem(IDC_STATIC_SPEED);
	CStatic* pSVolume2 = (CStatic *)GetDlgItem(IDC_STATIC_VOLUME2);
	CStatic* pSSpeed2 = (CStatic *)GetDlgItem(IDC_STATIC_SPEED2);

	int num_injectors = 0;
	if (IsDlgButtonChecked(IDC_RADIO_NOINJECT))
		num_injectors = 0;
	else if (IsDlgButtonChecked(IDC_RADIO_ONEINJECT))
		num_injectors = 1;
	else
		num_injectors = 2;

	InitVolumes();

	pIPort->EnableWindow((num_injectors == 0) ? FALSE : TRUE);
	pVolume->EnableWindow((num_injectors >= 1) ? TRUE : FALSE);
	pSpeed->EnableWindow((num_injectors >= 1) ? TRUE : FALSE);
	pVolume2->EnableWindow((num_injectors == 2) ? TRUE : FALSE);
	pSpeed2->EnableWindow((num_injectors == 2) ? TRUE : FALSE);
	pIParams->EnableWindow((num_injectors == 0) ? FALSE : TRUE);
	pSIPort->EnableWindow((num_injectors == 0) ? FALSE : TRUE);
	pSVolume->EnableWindow((num_injectors >= 1) ? TRUE : FALSE);	
	pSSpeed->EnableWindow((num_injectors >= 1) ? TRUE : FALSE);	
	pSVolume2->EnableWindow((num_injectors == 2) ? TRUE : FALSE);	
	pSSpeed2->EnableWindow((num_injectors == 2) ? TRUE : FALSE);	

	int inject_num;
	for (inject_num = 0; inject_num < CSKPPS::MAX_INJECTIONS; inject_num++)
	{
		m_skips[inject_num]->EnableWindow((num_injectors == 0) ? FALSE : TRUE);
		m_inject1s[inject_num]->EnableWindow((num_injectors >= 1) ? TRUE : FALSE);
		m_inject2s[inject_num]->EnableWindow((num_injectors == 2) ? TRUE : FALSE);
		if (m_inject2s[inject_num]->GetCheck() == 1)
		{
			if (num_injectors < 2)
			{
				m_inject2s[inject_num]->SetCheck(0);
				m_skips[inject_num]->SetCheck(1);
				m_injections[inject_num].m_used = 0;
			}
			else
			{
				m_injections[inject_num].m_used = 2;
			}
		}
		else if (m_inject1s[inject_num]->GetCheck() == 1)
		{
			if (num_injectors == 0)
			{
				m_inject1s[inject_num]->SetCheck(0);
				m_skips[inject_num]->SetCheck(1);
				m_injections[inject_num].m_used = 0;
			}
			else
			{
				m_injections[inject_num].m_used = 1;
			}
		}
		else	// Skip it
		{
			m_injections[inject_num].m_used = 0;
		}


		if (num_injectors > 0)
		{
			EnableInjections(inject_num,
				(m_skips[inject_num]->GetCheck() == 1) ? FALSE : TRUE);
			SetVolume(inject_num);
		}
		else
		{
			EnableInjections(inject_num, FALSE);
		}
	}
}

void CInjectorOptions::OnChangeVolume() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	ASSERT(pVolume != NULL);
	switch(pVolume->GetCurSel())
	{
	case 0:
		m_max_vol = 50;
		break;

	case 1:
		m_max_vol = 100;
		break;

	case 2:
		m_max_vol = 250;
		break;

	case 3:
		m_max_vol = 500;
		break;

	case 4:
		m_max_vol = 1000;
		break;

	case 5:
	default:
		m_max_vol = 2500;
		break;
	}

	pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME2);
	ASSERT(pVolume != NULL);
	switch(pVolume->GetCurSel())
	{
	case 0:
		m_max_vol2 = 50;
		break;

	case 1:
		m_max_vol2 = 100;
		break;

	case 2:
		m_max_vol2 = 250;
		break;

	case 3:
		m_max_vol2 = 500;
		break;

	case 4:
		m_max_vol2 = 1000;
		break;

	case 5:
	default:
		m_max_vol2 = 2500;
		break;
	}

	InitVolumes();

	for (int inject_num = 0; inject_num < CSKPPS::MAX_INJECTIONS; inject_num++)
		SetVolume(inject_num);

	
}

