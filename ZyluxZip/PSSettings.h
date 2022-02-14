// PSSettings.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
*/

#if !defined(AFX_PSSETTINGS_H__32161E65_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PSSETTINGS_H__32161E65_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTTYInfo;
class CWndData;

typedef struct PSSettingsInfo
{
  CTTYInfo *pTTY;
  CWndData *pData;
} PSSettingsInfo;

/////////////////////////////////////////////////////////////////////////////
// CPSSettings

class CPSSettings : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSSettings)

// Construction
public:
	CPSSettings(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, PSSettingsInfo *pInfo = 0);
	CPSSettings(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, PSSettingsInfo *pInfo = 0);
  void CommonConstruct(PSSettingsInfo *pInfo);
// Attributes
public:

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
  class CTTYInfo   *m_pTTYInfo;
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
