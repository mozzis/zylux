// EXCELOPTIONS.cpp : implementation file
//

#include "stdafx.h"
#include "SA.h"
#include "ExcelOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelOptions dialog


CExcelOptions::CExcelOptions(CGPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CExcelOptions::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CExcelOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExcelOptions::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcelOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExcelOptions, CProtocolDlg)
	//{{AFX_MSG_MAP(CExcelOptions)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelOptions message handlers

BOOL CExcelOptions::OnInitDialog()
{
	CProtocolDlg::OnInitDialog();

	// TODO: Add extra initialization here
	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_AUTOSEND);
	ASSERT(button != NULL);
	button->SetCheck(m_pps.AutoSendToExcel() ? 1 : 0);

	SetDlgItemText(IDC_EDIT_WORKBOOK, m_pps.m_workbook);
	SetDlgItemText(IDC_EDIT_WORKSHEET, m_pps.m_worksheet);

	CComboBox* combo;
	combo = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	ASSERT(combo != NULL);
	WORD i;
	for (i = 1; i <= 256; i++)
	{
		combo->AddString(SCGetExcelColString(i));
	}
	combo->SetCurSel(m_pps.m_cell_col);

	SetDlgItemInt(IDC_EDIT_ROW, m_pps.m_cell_row + 1);

	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_MACRO);
	ASSERT(edit != NULL);
	edit->SetLimitText(CGPPS::MACRONAME_SIZE - 1);
	edit->SetWindowText(m_pps.m_macroname);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExcelOptions::OnOK()
{
	// TODO: Add extra validation here
	if (VerifyFields())
	{
		ReadFields();
		CProtocolDlg::OnOK();
	}
}

void CExcelOptions::ReadFields()
{
	CButton* button = (CButton*)GetDlgItem(IDC_CHECK_AUTOSEND);
	ASSERT(button != NULL);
	m_pps.SetAutoSendToExcel((button->GetCheck() == 0) ? false : true);

	CEdit* edit;
	edit = (CEdit*)GetDlgItem(IDC_EDIT_WORKBOOK);
	ASSERT(edit != NULL);
	edit->GetWindowText(m_pps.m_workbook);
	m_pps.m_workbook.TrimLeft();
	m_pps.m_workbook.TrimRight();

	edit = (CEdit*)GetDlgItem(IDC_EDIT_WORKSHEET);
	ASSERT(edit != NULL);
	edit->GetWindowText(m_pps.m_worksheet);
	m_pps.m_worksheet.TrimLeft();
	m_pps.m_worksheet.TrimRight();

	CComboBox* combo;
	combo = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	ASSERT(combo != NULL);
	m_pps.m_cell_col = combo->GetCurSel();

	CString num_str;
	GetDlgItemText(IDC_EDIT_ROW, num_str);
	m_pps.m_cell_row = atoi(num_str) - 1;

	edit = (CEdit*)GetDlgItem(IDC_EDIT_MACRO);
	ASSERT(edit != NULL);
	edit->GetWindowText(m_pps.m_macroname);
	m_pps.m_macroname.TrimLeft();
	m_pps.m_macroname.TrimRight();
}


bool CExcelOptions::VerifyFields()
{
	// Add field verification later, as needed.
	CString num_str;
	GetDlgItemText(IDC_EDIT_ROW, num_str);
	int num = atoi(num_str);
	if ((num >= 1) && (num <= 65536))
	{
		return TRUE;
	}
	else
	{
		SCMessageBox("Cell row must be between 1 and 65536.");
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_ROW);
		ASSERT(edit != NULL);
		edit->SetFocus();
		edit->SetSel(0, -1);

		return FALSE;
	}
}

class CSelectFileDialog : public CFileDialog
{
public:
	CSelectFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
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

		// Change the Open button text
		SetControlText(IDOK, _T("Select"));
	}
};

void CExcelOptions::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CString workbook;
	GetDlgItemText(IDC_EDIT_WORKBOOK, workbook);

	CSelectFileDialog dlg(TRUE, ".xls", workbook,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		"Workbook Files (*.xls)|*.xls|All Files (*.*)|*.*||",
		this);
	dlg.m_ofn.lpstrTitle = _T("Select an Excel (TM) workbook:");

	if (dlg.DoModal() == IDOK)
	{
		// Get the user's dir selection
		m_pps.m_workbook = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_WORKBOOK, m_pps.m_workbook);
	}
}
