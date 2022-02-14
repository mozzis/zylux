/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__F0CB602C_7876_11D2_88A4_00104BF194E2__INCLUDED_)
#define AFX_DLGPROXY_H__F0CB602C_7876_11D2_88A4_00104BF194E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CZyluxForm;

/////////////////////////////////////////////////////////////////////////////
// CZyluxFormAutoProxy command target

class CZyluxFormAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CZyluxFormAutoProxy)

	CZyluxFormAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CZyluxForm* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxFormAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CZyluxFormAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CZyluxFormAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CZyluxFormAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CZyluxFormAutoProxy)
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
	afx_msg void Quit();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__F0CB602C_7876_11D2_88A4_00104BF194E2__INCLUDED_)
