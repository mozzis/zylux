#if !defined(AFX_OPTDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_OPTDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Options.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptDlg dialog

class COptDlg : public CDialog
{
// Construction
public:
	COptions m_options;
	COptDlg(COptions &options, CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(COptDlg)
	enum { IDD = IDD_OPTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonWorkdir();
	afx_msg void OnCheckInjector();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
