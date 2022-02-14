// SerialDialog.cpp : implementation file
//

#include "stdafx.h"
#include "protocol manager.h"
#include "SerialDialog.h"
#include "SCSerialNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialDialog dialog


CSerialDialog::CSerialDialog(bool is_missing, CWnd* pParent /*=NULL*/)
	: CDialog(CSerialDialog::IDD, pParent), m_missing(is_missing)
{
	//{{AFX_DATA_INIT(CSerialDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSerialDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSerialDialog, CDialog)
	//{{AFX_MSG_MAP(CSerialDialog)
	ON_EN_CHANGE(IDC_EDIT_SER1, OnChangeEditSer1)
	ON_EN_CHANGE(IDC_EDIT_SER2, OnChangeEditSer2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialDialog message handlers

void CSerialDialog::OnChangeEditSer1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	CEdit* pSer1 = (CEdit*)GetDlgItem(IDC_EDIT_SER1);
	CEdit* pSer2 = (CEdit*)GetDlgItem(IDC_EDIT_SER2);
	CString ser1;
	CString ser2;
	DWORD sel = pSer1->GetSel();
	pSer1->GetWindowText(ser1);
	pSer2->GetWindowText(ser2);
	m_serial_string = ser1 + ser2;
	if ((sel & 0x0000FFFF) == 5)
	{
		pSer2->SetFocus();
	}
	else
	{
		pSer1->SetSel(sel);
	}
	GetDlgItem(IDOK)->EnableWindow(
		(CSCSerialNumber::ExtractSerialNumber(m_serial_string) >= 2) ? TRUE : FALSE);
}

void CSerialDialog::OnChangeEditSer2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	CEdit* pSer1 = (CEdit*)GetDlgItem(IDC_EDIT_SER1);
	CEdit* pSer2 = (CEdit*)GetDlgItem(IDC_EDIT_SER2);
	CString ser1;
	CString ser2;
	DWORD sel = pSer2->GetSel();
	pSer1->GetWindowText(ser1);
	pSer2->GetWindowText(ser2);
	m_serial_string = ser1 + ser2;
	if ((sel & 0x0000FFFF) == 0)
	{
		pSer1->SetFocus();
	}
	else
	{
		pSer2->SetSel(sel);
	}
	//pSer2->SetSel(sel);
	GetDlgItem(IDOK)->EnableWindow(
		(CSCSerialNumber::ExtractSerialNumber(m_serial_string) >= 2) ? TRUE : FALSE);
}

void CSerialDialog::OnOK() 
{
	// TODO: Add extra validation here
	CEdit* pSer1 = (CEdit*)GetDlgItem(IDC_EDIT_SER1);
	CEdit* pSer2 = (CEdit*)GetDlgItem(IDC_EDIT_SER2);
	CString ser1;
	CString ser2;
	pSer1->GetWindowText(ser1);
	pSer2->GetWindowText(ser2);
	m_serial_string = ser1 + ser2;
	int serial_number = CSCSerialNumber::ExtractSerialNumber(m_serial_string);
	GetDlgItem(IDOK)->EnableWindow(
		(serial_number > 0) ? TRUE : FALSE);

	if (serial_number > 0)
	{
		CDialog::OnOK();
	}
}

BOOL CSerialDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_SERMSG, m_missing ?
		"No serial number found." :
		"Serial number is invalid.");

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	((CEdit*)GetDlgItem(IDC_EDIT_SER1))->LimitText(5);
	((CEdit*)GetDlgItem(IDC_EDIT_SER2))->LimitText(5);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
