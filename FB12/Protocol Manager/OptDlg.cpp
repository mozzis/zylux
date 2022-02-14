// OptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol Manager.h"
#include "OptDlg.h"
#include "General.h"

#include <dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptDlg dialog

COptDlg::COptDlg(COptions &options, CWnd* pParent /*=NULL*/)
	: CDialog(COptDlg::IDD, pParent), m_options(options)
{
	//{{AFX_DATA_INIT(COptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptDlg, CDialog)
	//{{AFX_MSG_MAP(COptDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_WORKDIR, OnButtonWorkdir)
	ON_BN_CLICKED(IDC_CHECK_INJECTOR, OnCheckInjector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptDlg message handlers

BOOL COptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox* pPort = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	ASSERT(pPort != NULL);
	switch(m_options.m_lumiport)
	{
	case 1:
		pPort->SetCurSel(0);
		break;

	case 2:
	default:
		pPort->SetCurSel(1);
		break;
	}
	
	CComboBox* pBaud = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
	ASSERT(pBaud != NULL);
	switch(m_options.m_lumibaud)
	{
	case 2400:
		pBaud->SetCurSel(0);
		break;

	case 4800:
		pBaud->SetCurSel(1);
		break;

	case 9600:
	default:
		pBaud->SetCurSel(2);
		break;
	}

	/*
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	ASSERT(pIPort != NULL);
	switch(m_options.m_injectport)
	{
	case 1:
		pIPort->SetCurSel(0);
		break;

	case 2:
	default:
		pIPort->SetCurSel(1);
		break;
	}

	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	ASSERT(pVolume != NULL);
	switch(m_options.m_volume)
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
*/
	SetDlgItemText(IDC_EDIT_WORKDIR, m_options.m_workdir);



	CButton* pBeep = (CButton*)GetDlgItem(IDC_CHECK_BEEP);
	ASSERT(pBeep != NULL);
	pBeep->SetCheck(m_options.m_beep ? 1 : 0);

	/*
	CButton* pInject = (CButton*)GetDlgItem(IDC_CHECK_INJECTOR);
	CStatic* pIParams = (CStatic *)GetDlgItem(IDC_GROUP_INJECTOR);
	CStatic* pSIPort = (CStatic *)GetDlgItem(IDC_STATIC_IPORT);
	CStatic* pSVolume = (CStatic *)GetDlgItem(IDC_STATIC_VOLUME);
	ASSERT((pInject != NULL) && (pIPort != NULL) && (pVolume != NULL) &&
			(pIParams != NULL) && (pSIPort != NULL) && (pSVolume != NULL));

	BOOL bEnabled = (m_options.m_injector) ? TRUE : FALSE;
	pInject->SetCheck(m_options.m_injector ? 1 : 0);
	pIPort->EnableWindow(bEnabled);
	pVolume->EnableWindow(bEnabled);
	pIParams->EnableWindow(bEnabled);
	pSIPort->EnableWindow(bEnabled);
	pSVolume->EnableWindow(bEnabled);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CComboBox* pPort = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	ASSERT(pPort != NULL);
	switch(pPort->GetCurSel())
	{
	case 0:
		m_options.m_lumiport = 1;
		break;

	case 1:
	default:
		m_options.m_lumiport = 2;
		break;
	}

	CComboBox* pBaud = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
	ASSERT(pBaud != NULL);
	switch(pBaud->GetCurSel())
	{
	case 0:
		m_options.m_lumibaud = 2400;
		break;

	case 1:
		m_options.m_lumibaud = 4800;
		break;

	case 2:
	default:
		m_options.m_lumibaud = 9600;
		break;
	}

	/*
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	ASSERT(pIPort != NULL);
	switch(pIPort->GetCurSel())
	{
	case 0:
		m_options.m_injectport = 1;
		break;

	case 1:
	default:
		m_options.m_injectport = 2;
		break;
	}

	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	ASSERT(pVolume != NULL);
	switch(pVolume->GetCurSel())
	{
	case 0:
		m_options.m_volume = 50;
		break;

	case 1:
		m_options.m_volume = 100;
		break;

	case 2:
		m_options.m_volume = 250;
		break;

	case 3:
		m_options.m_volume = 500;
		break;

	case 4:
		m_options.m_volume = 1000;
		break;

	case 5:
	default:
		m_options.m_volume = 2500;
		break;
	}
*/
	CButton* pBeep = (CButton*)GetDlgItem(IDC_CHECK_BEEP);
	ASSERT(pBeep != NULL);
	m_options.m_beep = (pBeep->GetCheck() == 1) ? true : false;

	/*
	CButton* pInject = (CButton*)GetDlgItem(IDC_CHECK_INJECTOR);
	ASSERT(pInject != NULL);
	m_options.m_injector = (pInject->GetCheck() == 1) ? true : false;
	*/
	GetDlgItemText(IDC_EDIT_WORKDIR, m_options.m_workdir);
}

class CWorkDirDlg : public CFileDialog
{
public:
	CWorkDirDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL)
		: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
			dwFlags, lpszFilter, pParentWnd) { }

	virtual void OnInitDone()
	{
		CFileDialog::OnInitDone();

		// Hide the filename
		HideControl(edt1);
		HideControl(stc3);

		// Hide the filetype
		HideControl(cmb1);
		HideControl(stc2);

		// Change the Directory title text
		SetControlText(stc4, _T("Directory:"));

		// Change the Open button text
		SetControlText(IDOK, _T("Select"));
	}
};

void COptDlg::OnButtonWorkdir()
{
	// TODO: Add your control notification handler code here
	// Set to the workdir
	CString curdir = SCSetCurrentDir(m_options.m_workdir);

	CWorkDirDlg dlg(TRUE, NULL, "nofile", //m_options.m_workdir,
		OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_EXPLORER,
		NULL, this);
	dlg.m_ofn.lpstrTitle = _T("Select the working directory:");

	if (dlg.DoModal() == IDOK)
	{
		// Get the user's dir selection
		m_options.m_workdir = SCGetCurrentDir();
		SetDlgItemText(IDC_EDIT_WORKDIR, m_options.m_workdir);
	}

	// Set back to saved current dir
	//SCSetCurrentDir(curdir);
}

void COptDlg::OnCheckInjector() 
{
	// TODO: Add your control notification handler code here
	/*
	CButton* pInject = (CButton*)GetDlgItem(IDC_CHECK_INJECTOR);
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);
	CComboBox* pVolume = (CComboBox*)GetDlgItem(IDC_COMBO_VOLUME);
	CStatic* pIParams = (CStatic *)GetDlgItem(IDC_GROUP_INJECTOR);
	CStatic* pSIPort = (CStatic *)GetDlgItem(IDC_STATIC_IPORT);
	CStatic* pSVolume = (CStatic *)GetDlgItem(IDC_STATIC_VOLUME);

	BOOL bEnabled = (pInject->GetCheck() == 1) ? TRUE : FALSE;

	pIPort->EnableWindow(bEnabled);
	pVolume->EnableWindow(bEnabled);
	pIParams->EnableWindow(bEnabled);
	pSIPort->EnableWindow(bEnabled);
	pSVolume->EnableWindow(bEnabled);
	*/
}

void COptDlg::OnOK() 
{
	// TODO: Add extra validation here
	/*
	CButton* pInject = (CButton*)GetDlgItem(IDC_CHECK_INJECTOR);
	CComboBox* pPort = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	CComboBox* pIPort = (CComboBox*)GetDlgItem(IDC_COMBO_IPORT);

	ASSERT((pPort != NULL) && (pIPort != NULL) && (pInject != NULL));

	if ((pInject->GetCheck() == 1) && 
		(pPort->GetCurSel() == pIPort->GetCurSel()))
	{
		AfxMessageBox("Luminometer and Injector must use different ports.");
	}
	else
	{
	*/
		CDialog::OnOK();
	//}
}
