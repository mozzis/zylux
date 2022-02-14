// PSSettings.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PSSettings.h $ * 
// 
// *****************  Version 3  *****************
// User: Maynard      Date: 5/15/00    Time: 10:48a
// Updated in $/ZyluxCap/2.0
// Add m_bAutomated flag, set by parent, and used to know if the serial
// settings dialog should be included in the settings prop sheet
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_PSSETTINGS_H__32161E65_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PSSETTINGS_H__32161E65_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mminfo.h"
#include "tty.h"

/////////////////////////////////////////////////////////////////////////////
// CPSSettings

class CPSSettings : public CPropertySheet, public CMMInfo<CTTYInfo>
{
	DECLARE_DYNAMIC(CPSSettings)

// Construction
public:
	CPSSettings(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, CTTYInfo *pInfo = 0, bool bAutomated = false);
	CPSSettings(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, CTTYInfo *pInfo = 0, bool bAutomated = false);
  CommonConstruct(CTTYInfo *pI, bool bAutomated);
// Attributes
public:
  bool m_bAutomated;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSSettings)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSSettings();
protected:
  class CPPApp     *m_pPPApp;
  class CPPDataWin *m_pPPDataWin;
  class CPPSerial  *m_pPPSerial;
  class CPPXfer    *m_pPPXfer;
  class CZyluxForm *m_pParent;

	// Generated message map functions
protected:
	//{{AFX_MSG(CPSSettings)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSSETTINGS_H__32161E65_E84A_11D2_88A4_444553540000__INCLUDED_)
