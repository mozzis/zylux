// PPXfer.cpp : implementation file
// PPDataXfer property page is for data transfer settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPXfer.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/22/99    Time: 12:14p
 * Updated in $/ZyluxCap/2.0
 * Add member for custom row edit control
 * Add OnKillActive to validate row and column etnries on exit
 * Add warning message display when invalid chars are entered for row and
 * column addresses
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "PPXfer.h"
#include "mmslide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPXfer property page

IMPLEMENT_DYNCREATE(CPPXfer, CMMPropPage)

void CPPXfer::CommonConstruct()
{
	//{{AFX_DATA_INIT(CPPXfer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pSldDelay = 0;
}

CPPXfer::CPPXfer() : CMMPropPage(CPPXfer::IDD)
{
  CommonConstruct();
}

CPPXfer::CPPXfer(CTTYInfo *pI) : CMMPropPage(CPPXfer::IDD, pI)
{
  CommonConstruct();
}

CPPXfer::~CPPXfer()
{
  delete m_pSldDelay;
  m_pSldDelay = 0;
}

void CPPXfer::DoDataExchange(CDataExchange* pDX)
{
	CMMPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPXfer)
	DDX_Control(pDX, IDC_EDT_RANGEROW, m_EdtRow);
	DDX_Control(pDX, IDC_EDT_RANGECOL, m_EdtCol);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPXfer, CDialog)
	//{{AFX_MSG_MAP(CPPXfer)
  ON_COMMAND(IDC_SLDDELAY, OnDelay)
	ON_BN_CLICKED(IDC_CHK_FILE, OnChkFile)
	ON_BN_CLICKED(IDC_CHK_SHEET, OnChkSheet)
	ON_BN_CLICKED(IDC_CHK_RANGE, OnChkRange)
	ON_BN_CLICKED(IDC_CHK_REPFILE, OnChkRepFile)
  ON_MESSAGE(WM_BADROWCHAR, OnBadRowChar)
  ON_MESSAGE(WM_BADCOLCHAR, OnBadColChar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPXfer message handlers

BOOL CPPXfer::OnInitDialog() 
{
	BOOL bRet = CMMPropPage::OnInitDialog();
  m_DelayDbl = (double)m_pInfo->m_dwTimeout / 50.0;
  if (!m_pSldDelay)
    m_pSldDelay = new CDelaySlide(IDC_SLDDELAY, this, &m_DelayDbl);
  OnDelay();
  CheckDlgButton(IDC_CHK_FILE, m_pInfo->m_bSpecFile);
  CheckDlgButton(IDC_CHK_REPFILE, m_pInfo->m_bRepFile);
  CheckDlgButton(IDC_CHK_SHEET, m_pInfo->m_bSpecSheet);
  CheckDlgButton(IDC_CHK_RANGE, m_pInfo->m_bSpecRange);

  SetDlgItemText(IDC_EDT_FILE,  m_pInfo->m_sFile);
  SetDlgItemText(IDC_EDT_SHEET, m_pInfo->m_sSheet);
  SetDlgItemText(IDC_EDT_RANGEROW, m_pInfo->m_sRangeRow);
  SetDlgItemText(IDC_EDT_RANGECOL, m_pInfo->m_sRangeCol);
  
  GetDlgItem(IDC_EDT_FILE)->EnableWindow(IsDlgButtonChecked(IDC_CHK_FILE));
  GetDlgItem(IDC_CHK_REPFILE)->EnableWindow(IsDlgButtonChecked(IDC_CHK_FILE));
  GetDlgItem(IDC_EDT_SHEET)->EnableWindow(IsDlgButtonChecked(IDC_CHK_SHEET));
  GetDlgItem(IDC_EDT_RANGEROW)->EnableWindow(IsDlgButtonChecked(IDC_CHK_RANGE));
  GetDlgItem(IDC_EDT_RANGECOL)->EnableWindow(IsDlgButtonChecked(IDC_CHK_RANGE));
  return bRet;
}


BOOL CPPXfer::OnKillActive()
{
  CString sRangeRow, sRangeCol;
  bool bRowOK = true, bColOK = true;
  GetDlgItemText(IDC_EDT_RANGEROW, sRangeRow);
  GetDlgItemText(IDC_EDT_RANGECOL, sRangeCol);

  if (IsDlgButtonChecked(IDC_CHK_RANGE)) // if range should be valid
    {
    CString sReason;
    if (sRangeRow.IsEmpty())
      {
      sReason = "The row address is empty!";
      bRowOK = false;
      }
    if (sRangeCol.IsEmpty())
      {
      if (sReason.GetLength())
        sReason += "\n\r";
      sReason += "The column address is empty!";
      bColOK = false;
      }
    if (!bRowOK || !bColOK)
      {
      CString sMsg = "The output range is invalid because: \n\r";
      sMsg += sReason;
      AfxMessageBox(sMsg);
      return FALSE;
      }
    }
  return TRUE;
}

void CPPXfer::OnOK() 
{
  GetDlgItemText(IDC_EDT_FILE,  m_pInfo->m_sFile);
  GetDlgItemText(IDC_EDT_SHEET, m_pInfo->m_sSheet);
  GetDlgItemText(IDC_EDT_RANGEROW, m_pInfo->m_sRangeRow);
  GetDlgItemText(IDC_EDT_RANGECOL, m_pInfo->m_sRangeCol);
  m_pInfo->m_bSpecFile  = IsDlgButtonChecked(IDC_CHK_FILE);
  m_pInfo->m_bRepFile  = IsDlgButtonChecked(IDC_CHK_REPFILE);
  m_pInfo->m_bSpecSheet = IsDlgButtonChecked(IDC_CHK_SHEET);
  m_pInfo->m_bSpecRange = IsDlgButtonChecked(IDC_CHK_RANGE);
  CMMPropPage::OnOK();
}

// change the push delay time
/////////////////////////////////////////////////////////////////////////////
void CPPXfer::OnDelay()
{
  CString csVal;
  if (this->m_DelayDbl)
    csVal.Format("%3.2g sec.", m_DelayDbl * .01 * 5.0);
  else
    csVal = "(Disabled)";

  m_pInfo->m_dwTimeout = (DWORD)(m_DelayDbl * .01 * 5000);
  SetDlgItemText(IDC_DELTIME, csVal);
}

void CPPXfer::OnChkFile() 
{
  GetDlgItem(IDC_EDT_FILE)->EnableWindow(IsDlgButtonChecked(IDC_CHK_FILE));
  GetDlgItem(IDC_CHK_REPFILE)->EnableWindow(IsDlgButtonChecked(IDC_CHK_FILE));
}

void CPPXfer::OnChkSheet() 
{
  GetDlgItem(IDC_EDT_SHEET)->EnableWindow(IsDlgButtonChecked(IDC_CHK_SHEET));
}

void CPPXfer::OnChkRange() 
{
  GetDlgItem(IDC_EDT_RANGEROW)->EnableWindow(IsDlgButtonChecked(IDC_CHK_RANGE));
  GetDlgItem(IDC_EDT_RANGECOL)->EnableWindow(IsDlgButtonChecked(IDC_CHK_RANGE));
}


void CPPXfer::OnChkRepFile() 
{
	
}

void ShowCharError(LPCTSTR szMsg, CWnd *pWnd)
{
  CStatic *pMsg = (CStatic *)pWnd->GetDlgItem(IDC_ERRMSG);
  if (pMsg)
    pMsg->SetWindowText(szMsg);
  if (szMsg)
    MessageBeep(MB_ICONASTERISK);
}

LRESULT CPPXfer::OnBadRowChar(WPARAM wReason, LPARAM)
{
  LPCTSTR szMsg = 0;
  if (CEdtRow::eNoZero == wReason)
    szMsg = "First row must be '1' not '0'!";
  else if (CEdtRow::eNotDigit == wReason)
    szMsg = "Only digits allowed in row address!";
  ShowCharError(szMsg, this);
  return 0;
}

LRESULT CPPXfer::OnBadColChar(WPARAM wReason, LPARAM)
{
  LPCTSTR szMsg = 0;
  if (CEdtCol::eTooMany == wReason)
    szMsg = "Max two chars in column address!";
  else if (CEdtCol::eNotAlpha == wReason)
    szMsg = "Alpha chars only in column address!";
  ShowCharError(szMsg, this);
  return 0;
}
