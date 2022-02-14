// SAAdvancedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SA.h"
#include "SAAdvancedDlg.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSAAdvancedDlg dialog


CSAAdvancedDlg::CSAAdvancedDlg(CSAPPS& pps, LPCTSTR filepath, CWnd* pParent /*=NULL*/)
	: CProtocolDlg(filepath, CSAAdvancedDlg::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CSAAdvancedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSAAdvancedDlg::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAAdvancedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSAAdvancedDlg, CProtocolDlg)
	//{{AFX_MSG_MAP(CSAAdvancedDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAAdvancedDlg message handlers

BOOL CSAAdvancedDlg::OnInitDialog() 
{
	CProtocolDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SampGrid.SubclassDlgItem(IDC_EDGRID, this);
	m_SampGrid.Initialize();
	m_SampGrid.m_initialized = true;
	m_SampGrid.SetGridValues(m_pps);

	//CButton* p95ConfCol = (CButton*) GetDlgItem(IDC_CB_95CONFCOL);
	//CButton* p99ConfCol = (CButton*) GetDlgItem(IDC_CB_99CONFCOL);
	CButton* pFlexReps = (CButton*) GetDlgItem(IDC_CB_FLEXREPS);
	CButton* pFlexSamps = (CButton*) GetDlgItem(IDC_CB_FLEXSAMPS);
	CButton* pRowOrder = (CButton*) GetDlgItem(IDC_RB_ROWORDER);
	CButton* pColOrder = (CButton*) GetDlgItem(IDC_RB_COLORDER);
	//CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACNAME);
	//CEdit* pDefaultSamp = (CEdit*) GetDlgItem(IDC_EDIT_DEFAULTSAMP);

	//if (m_pps.Use95ConfCol())
	//	p95ConfCol->SetCheck(1);
	//else
	//	p95ConfCol->SetCheck(0);

	//if (m_pps.Use99ConfCol())
	//	p99ConfCol->SetCheck(1);
	//else
	//	p99ConfCol->SetCheck(0);

	if (m_pps.IsFlexibleNumReps())
		pFlexReps->SetCheck(1);
	else
		pFlexReps->SetCheck(0);

	if (m_pps.IsFlexibleNumSamps())
		pFlexSamps->SetCheck(1);
	else
		pFlexSamps->SetCheck(0);

	if (m_pps.UseRowOrder())
		pRowOrder->SetCheck(1);
	else
		pColOrder->SetCheck(1);

	//pMacroName->LimitText(m_pps.MACRONAME_SIZE - 1);
	//pDefaultSamp->LimitText(m_pps.SAMPLENAME_SIZE - 1);
	//pMacroName->SetWindowText(m_pps.m_macroname);
	//pDefaultSamp->SetWindowText(m_pps.m_defaultname.sampname);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSAAdvancedDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (VerifyEntries()) 
	{
		SetEntries();
		CProtocolDlg::OnOK();
	}
}


BOOL CSAAdvancedDlg::VerifyEntries()
{
	return TRUE;
}

void CSAAdvancedDlg::SetEntries()
{
	//CString entry;
	//CButton* p95ConfCol = (CButton*) GetDlgItem(IDC_CB_95CONFCOL);
	//CButton* p99ConfCol = (CButton*) GetDlgItem(IDC_CB_99CONFCOL);
	CButton* pFlexReps = (CButton*) GetDlgItem(IDC_CB_FLEXREPS);
	CButton* pFlexSamps = (CButton*) GetDlgItem(IDC_CB_FLEXSAMPS);
	CButton* pRowOrder = (CButton*) GetDlgItem(IDC_RB_ROWORDER);
	CButton* pColOrder = (CButton*) GetDlgItem(IDC_RB_COLORDER);
	//CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACNAME);
	//CEdit* pDefaultSamp = (CEdit*) GetDlgItem(IDC_EDIT_DEFAULTSAMP);

	//if (p95ConfCol->GetCheck())
	//	m_pps.SetUse95ConfCol(true);
	//else
	//	m_pps.SetUse95ConfCol(false);

	//if (p99ConfCol->GetCheck())
	//	m_pps.SetUse99ConfCol(true);
	//else
	//	m_pps.SetUse99ConfCol(false);

	if (pFlexReps->GetCheck())
		m_pps.SetFlexibleNumReps(true);
	else
		m_pps.SetFlexibleNumReps(false);

	if (pFlexSamps->GetCheck())
		m_pps.SetFlexibleNumSamps(true);
	else
		m_pps.SetFlexibleNumSamps(false);


	if (pRowOrder->GetCheck())
		m_pps.SetUseRowOrder(true);
	else
		m_pps.SetUseRowOrder(false);

	//pDefaultSamp->GetWindowText(entry);
	//entry.TrimLeft();
	//entry.TrimRight();
	//strcpy(m_pps.m_defaultname.sampname, LPCTSTR(entry));

	//m_pps.m_macroname.Empty();
	//pMacroName->GetWindowText(m_pps.m_macroname);
	//m_pps.m_macroname.TrimLeft();
	//m_pps.m_macroname.TrimRight();
	
	m_pps.ResetSampList();
	m_SampGrid.GetGridValues(m_pps);
}

void CSAAdvancedDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.DeleteSelRows();
}

void CSAAdvancedDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.ClearSelRows();
}

void CSAAdvancedDlg::OnImport() 
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
