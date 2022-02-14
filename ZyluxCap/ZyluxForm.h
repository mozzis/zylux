// ZyluxForm.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: ZyluxForm.h $ * 
// 
// *****************  Version 5  *****************
// User: Maynard      Date: 5/15/00    Time: 10:45a
// Updated in $/ZyluxCap/2.0
// Add serial port property settings accesible via COM
// Add m_bAutomated flag to know if app is controlled by another program
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:15p
 * Updated in $/ZyluxCap/2.0
 * Add SetWindowPosition and CenterOnRect methods for form
 * Use referencing technique from ZyluxZip to know when to delete
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:21a
 * Updated in $/ZyluxCap/2.0
 * Add autoproxy link, notifier routines, Advise and UnAdvise
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:29a
 * Updated in $/ZyluxCap/2.0
 * Change settings dialog to propery sheet and pages
*/

#if !defined(AFX_ZYLUXFORM_H__454CE92A_C31A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_ZYLUXFORM_H__454CE92A_C31A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZyluxForm form view

#ifndef __AFXEXT_H__
#endif

class CZyluxForm : public CFormView
{
	DECLARE_DYNCREATE(CZyluxForm)
public:
	CZyluxForm();   // constructor used by dynamic creation
  virtual ~CZyluxForm();

  void SetRef(CWnd **ppRef) 
    { m_ppRef = ppRef; if (ppRef) *ppRef = this; } 

// Form Data
public:
	//{{AFX_DATA(CZyluxForm)
	enum { IDD = IDD_ZYLUXCAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
  class CZyluxFormAutoProxy *m_pAutoProxy;
  bool m_bAutomated;
// Operations
public:
  bool DoNotify(long lCategory, long lReason);
  bool IsConnected();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxForm)
	public:
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	virtual BOOL DestroyWindow();
  virtual void OnInitMenu(CMenu* pMenu);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
  class CTTYInfo *m_pTTYInfo;
  class CWndData *m_pWndData;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
  class CDlgSettings *m_pSettingsDlg;
  class CPSSettings *m_pSettings;
  CTypedPtrList<CPtrList, interface IZyluxNotify *> m_NotifyList;
  CWnd **m_ppRef;

  BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CZyluxForm)
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnSettings();
	afx_msg void OnShowData();
	afx_msg void OnUpdateChkConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowData(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSettings(CCmdUI* pCmdUI);
  afx_msg void OnChkConnect();
	afx_msg void OnExit();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
  // Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CZyluxForm)
	afx_msg long GetBaud();
	afx_msg void SetBaud(long nNewValue);
	afx_msg short GetPort();
	afx_msg void SetPort(short nNewValue);
	afx_msg short GetFlowCtrl();
	afx_msg void SetFlowCtrl(short nNewValue);
	afx_msg short GetDBits();
	afx_msg void SetDBits(short nNewValue);
	afx_msg short GetParity();
	afx_msg void SetParity(short nNewValue);
	afx_msg short GetStopBits();
	afx_msg void SetStopBits(short nNewValue);
	afx_msg SCODE Advise(LPUNKNOWN pNotifier);
	afx_msg SCODE UnAdvise(LPUNKNOWN pNotifier);
	afx_msg void OleSetWindowPos(long left, long top, long right, long bottom);
	afx_msg void CenterOnRect(long left, long top, long right, long bottom);
	//}}AFX_DISPATCH
protected:
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZYLUXFORM_H__454CE92A_C31A_11D2_88A4_444553540000__INCLUDED_)
