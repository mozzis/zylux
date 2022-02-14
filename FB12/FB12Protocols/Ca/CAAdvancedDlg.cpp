// CAAdvancedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CA.h"
#include "CAAdvancedDlg.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAAdvancedDlg dialog


CCAAdvancedDlg::CCAAdvancedDlg(CCAPPS& pps, LPCTSTR filepath, CWnd* pParent /*=NULL*/)
	: CProtocolDlg(filepath, CCAAdvancedDlg::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CCAAdvancedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCAAdvancedDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAAdvancedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCAAdvancedDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CCAAdvancedDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAAdvancedDlg message handlers

BOOL CCAAdvancedDlg::OnInitDialog() 
{
	CProtocolDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SampGrid.SubclassDlgItem(IDC_EDGRID, this);
	m_SampGrid.Initialize();
	m_SampGrid.m_initialized = true;
	m_SampGrid.SetGridValues(m_pps);

	//CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACNAME);
	CEdit* pNegResult = (CEdit*) GetDlgItem(IDC_EDIT_NEGRESULT);
	CEdit* pPosResult = (CEdit*) GetDlgItem(IDC_EDIT_POSRESULT);
	CEdit* pEquivResult = (CEdit*) GetDlgItem(IDC_EDIT_EQUIVRESULT);


	//pMacroName->LimitText(m_pps.MACRONAME_SIZE - 1);
	//pMacroName->SetWindowText(m_pps.m_macroname);

	pNegResult->LimitText(m_pps.RESULTSTEXT_SIZE - 1);
	pNegResult->SetWindowText(m_pps.m_negresult);

	pPosResult->LimitText(m_pps.RESULTSTEXT_SIZE - 1);
	pPosResult->SetWindowText(m_pps.m_posresult);

	pEquivResult->LimitText(m_pps.RESULTSTEXT_SIZE - 1);
	pEquivResult->SetWindowText(m_pps.m_equivresult);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCAAdvancedDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (VerifyEntries()) 
	{
		SetEntries();
		CProtocolDlg::OnOK();
	}
}


BOOL CCAAdvancedDlg::VerifyEntries()
{
	CString entry;
	CEdit* pNegResult = (CEdit*) GetDlgItem(IDC_EDIT_NEGRESULT);
	CEdit* pPosResult = (CEdit*) GetDlgItem(IDC_EDIT_POSRESULT);
	CEdit* pEquivResult = (CEdit*) GetDlgItem(IDC_EDIT_EQUIVRESULT);

	entry.Empty();
	pNegResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	if (entry.IsEmpty())
	{
		SCMessageBox("Please enter a string for the Negative Result.");
		return FALSE;
	}

	entry.Empty();
	pPosResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	if (entry.IsEmpty())
	{
		SCMessageBox("Please enter a string for the Positive Result.");
		return FALSE;
	}
	
	entry.Empty();
	pEquivResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	if (entry.IsEmpty())
	{
		SCMessageBox("Please enter a string for the Equivocal Result.");
		return FALSE;
	}

	return TRUE;
}

void CCAAdvancedDlg::SetEntries()
{
	CString entry;
	//CButton* p95ConfCol = (CButton*) GetDlgItem(IDC_CB_95CONFCOL);
	//CButton* p99ConfCol = (CButton*) GetDlgItem(IDC_CB_99CONFCOL);
	//CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACNAME);
	CEdit* pNegResult = (CEdit*) GetDlgItem(IDC_EDIT_NEGRESULT);
	CEdit* pPosResult = (CEdit*) GetDlgItem(IDC_EDIT_POSRESULT);
	CEdit* pEquivResult = (CEdit*) GetDlgItem(IDC_EDIT_EQUIVRESULT);

	//if (p95ConfCol->GetCheck())
	//	m_pps.SetUse95ConfCol(true);
	//else
	//	m_pps.SetUse95ConfCol(false);

	//if (p99ConfCol->GetCheck())
	//	m_pps.SetUse99ConfCol(true);
	//else
	//	m_pps.SetUse99ConfCol(false);


	//entry.Empty();
	//pMacroName->GetWindowText(entry);
	//entry.TrimLeft();
	//entry.TrimRight();
	//if (entry.IsEmpty())
	//	memset(m_pps.m_macroname, 0, sizeof(m_pps.m_macroname));
	//else
	//	strcpy(m_pps.m_macroname, LPCTSTR(entry));

	entry.Empty();
	pEquivResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	m_pps.m_equivresult = entry;

	entry.Empty();
	pNegResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	m_pps.m_negresult = entry;

	entry.Empty();
	pPosResult->GetWindowText(entry);
	entry.TrimLeft();
	entry.TrimRight();
	m_pps.m_posresult = entry;

	m_pps.ResetSampList();
	m_SampGrid.GetGridValues(m_pps);
}

void CCAAdvancedDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.DeleteSelRows();
}

void CCAAdvancedDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.ClearSelRows();
}

void CCAAdvancedDlg::OnImport() 
{
	// TODO: Add your control notification handler code here
// pop-up file-open dlg to ask for location
	CFileDialog dlgFile(
		TRUE,
		_T(".txt"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));

	dlgFile.m_ofn.lpstrTitle = "Import Sample Names from File";

	if (dlgFile.DoModal( ) == IDCANCEL)
		return;

	CStdioFile textFile;
	CString txt_line, buffer;

	if (!textFile.Open(dlgFile.GetFileName( ), CFile::modeRead))
	{
		txt_line.Format("File %s could not be opened!", dlgFile.GetFileName());
		SCMessageBox(txt_line);
		return;
	}

	int i;
	buffer.Empty();

	while (textFile.ReadString(txt_line) == TRUE)
	{
		txt_line.TrimLeft();
		i = txt_line.Find('\t');
		if (i >= 0) 
		{
			txt_line = txt_line.Left(i);
		}
		txt_line.TrimRight();
		buffer += (buffer.IsEmpty()) ? txt_line : ("\n" + txt_line);
	}

	m_SampGrid.AppendSamplesFromBuffer(buffer.GetBuffer(buffer.GetLength()), buffer.GetLength());
	m_SampGrid.Redraw();

	textFile.Close( );

	
}
