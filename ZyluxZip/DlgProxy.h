// DlgProxy.h : header file
// CZyluxZipDlgAutoProxy is an automation-creatable proxy for the main
// dialog of this application
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgProxy.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGPROXY_H__C814F40B_9E05_4501_A536_E991E9CC86BA__INCLUDED_)
#define AFX_DLGPROXY_H__C814F40B_9E05_4501_A536_E991E9CC86BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CZyluxZipDlg;

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlgAutoProxy command target

class CZyluxZipDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CZyluxZipDlgAutoProxy)

	CZyluxZipDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CZyluxZipDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxZipDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CZyluxZipDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CZyluxZipDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CZyluxZipDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CZyluxZipDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__C814F40B_9E05_4501_A536_E991E9CC86BA__INCLUDED_)
