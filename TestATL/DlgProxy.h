// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__A34B6012_2E93_4F48_9055_B4A309C5109E__INCLUDED_)
#define AFX_DLGPROXY_H__A34B6012_2E93_4F48_9055_B4A309C5109E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestATLDlg;

/////////////////////////////////////////////////////////////////////////////
// CTestATLDlgAutoProxy command target

class CTestATLDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CTestATLDlgAutoProxy)

	CTestATLDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CTestATLDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestATLDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestATLDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CTestATLDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTestATLDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTestATLDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__A34B6012_2E93_4F48_9055_B4A309C5109E__INCLUDED_)
