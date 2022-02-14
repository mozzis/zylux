// MMPropPage.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "MMPropPage.h"
#include "tty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMPropPage property page

IMPLEMENT_DYNAMIC(CMMPropPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CMMPropPage, CPropertyPage)
	  //{{AFX_MSG_MAP(CMMPropPage)
		  // NOTE: the ClassWizard will add message map macros here
	  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMPropPage message handlers

/////////////////////////////////////////////////////////////////////////////
// CMMPropPage extensions - Helper routines

// Helpers to set/get control states
//////////////////////////////////////////////////////////////////////////
VOID CMMPropPage::CheckDlgButton(UINT uIDCtrl, BOOL bCheck)
{
  CButton *pBtn = (CButton *)GetDlgItem(uIDCtrl);
  if (pBtn)
    pBtn->SetCheck(bCheck);
}

//////////////////////////////////////////////////////////////////////////
BOOL CMMPropPage::IsDlgButtonChecked(UINT uIDCtrl)
{
  CButton *pBtn = (CButton *)GetDlgItem(uIDCtrl);
  if (pBtn)
    return pBtn->GetCheck();
  else
    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
VOID CMMPropPage::FillComboBox(UINT uIDCombo, int nIDString,
                       const DWORD *pTable, WORD wTableLen,
                       DWORD dwCurrentSetting)
{
  CString csBuffer;
  WORD  wCount, wPosition;

  CComboBox *pCombo = (CComboBox *)GetDlgItem(uIDCombo);
  if (!pCombo)
    return;
  for (wCount = 0; wCount < wTableLen; wCount++)
    {
    // load the string from the string resources and
    // add it to the combo box
    csBuffer.LoadString(nIDString + wCount);
    wPosition = pCombo->AddString(csBuffer);
    // use item data to store the actual table value
    pCombo->SetItemData(wPosition, pTable[wCount]);
    // if this is our current setting, select it
    if (pTable[wCount] == dwCurrentSetting)
      pCombo->SetCurSel(wPosition);
    }
} // end of FillComboBox()

//////////////////////////////////////////////////////////////////////////
DWORD CMMPropPage::GetComboItemSel(UINT uIDCombo)
{
  CComboBox *pCombo = (CComboBox *)GetDlgItem(uIDCombo);
  ASSERT(pCombo);
  return pCombo->GetCurSel();
}

//////////////////////////////////////////////////////////////////////////
DWORD CMMPropPage::GetComboItemData(UINT uIDCombo, int nIndex)
{
  CComboBox *pCombo = (CComboBox *)GetDlgItem(uIDCombo);
  ASSERT(pCombo);
  return pCombo->GetItemData(nIndex);
}
  
