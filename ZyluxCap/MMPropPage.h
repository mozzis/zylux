// MMPropPage.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMPropPage.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:14a
 * Updated in $/ZyluxCap/1.2
 * Add i nclude ot tty.h (moved from stdafx.h)
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_MMPROPPAGE_H__32161E69_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_MMPROPPAGE_H__32161E69_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mminfo.h"
#include "tty.h"

/////////////////////////////////////////////////////////////////////////////
// CMMPropPage dialog

class CMMPropPage : public CPropertyPage, public CMMInfo<CTTYInfo>
{
	DECLARE_DYNAMIC(CMMPropPage)

// Construction
public:
  CMMPropPage(UINT uID) : CPropertyPage(uID) { }
  CMMPropPage(UINT uID, CTTYInfo *pI) : CPropertyPage(uID) { SetInfo(pI); }
  ~CMMPropPage() { }

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMMPropPage)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMMPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  VOID CheckDlgButton(UINT uIDCtrl, BOOL bCheck);
  BOOL IsDlgButtonChecked(UINT uIDCtrl);
  VOID FillComboBox(UINT uIDCombo, int nIDString, const DWORD *pTable, WORD wTableLen,
                       DWORD dwCurrentSetting);
  DWORD GetComboItemSel(UINT uIDCombo);
  DWORD GetComboItemData(UINT uIDCombo, int nIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMPROPPAGE_H__32161E69_E84A_11D2_88A4_444553540000__INCLUDED_)
