// DAAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "da.h"
#include "DAAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAAdvanced dialog


CDAAdvanced::CDAAdvanced(CDAPPS& pps, LPCTSTR protocolname, CWnd* pParent)
	: CProtocolDlg(protocolname, CDAAdvanced::IDD, pParent), m_pps(pps)
{
	//{{AFX_DATA_INIT(CDAAdvanced)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDAAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CProtocolDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDAAdvanced)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDAAdvanced, CProtocolDlg)
	//{{AFX_MSG_MAP(CDAAdvanced)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAAdvanced message handlers

BOOL CDAAdvanced::OnInitDialog() 
{
	CProtocolDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SampGrid.SubclassDlgItem(IDC_EDGRID, this);
	m_SampGrid.Initialize();
	m_SampGrid.m_initialized = true;
	m_SampGrid.SetGridValues(m_pps);

	//CEdit* pMacro = (CEdit*)GetDlgItem(IDC_EDIT_MACRO);
	//ASSERT(pMacro != NULL);
	//pMacro->SetLimitText(CGPPS::MACRONAME_SIZE - 1);
	//pMacro->SetWindowText(m_pps.m_macroname);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAAdvanced::OnOK() 
{
	// TODO: Add extra validation here
	if (VerifyEntries()) 
	{
		SetEntries();
		CProtocolDlg::OnOK();
	}	
}

void CDAAdvanced::SetEntries()
{
	CString entry;
	CEdit* pMacroName = (CEdit*) GetDlgItem(IDC_EDIT_MACRO);

	//entry.Empty();
	//pMacroName->GetWindowText(entry);
	//entry.TrimLeft();
	//entry.TrimRight();
	//if (entry.IsEmpty())
	//	memset(m_pps.m_macroname, 0, sizeof(m_pps.m_macroname));
	//else
	//	strcpy(m_pps.m_macroname, LPCTSTR(entry));

	m_pps.ResetSampList();
	m_SampGrid.GetGridValues(m_pps);
}


BOOL CDAAdvanced::VerifyEntries()
{
	// Add field verification later, as needed.
	return TRUE;
}

void CDAAdvanced::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.ClearSelRows();	
}

void CDAAdvanced::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_SampGrid.DeleteSelRows();
	
}

void CDAAdvanced::OnImport() 
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
