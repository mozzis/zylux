#if !defined(AFX_SAVEASDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SAVEASDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SaveAsDlg.h : header file
//

#include "resource.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CSaveAsDlg dialog

class CSaveAsDlg : public CDialog
{
// Construction
public:
	CSaveAsDlg(LPCTSTR default_name, bool allow_base_overwrite,
		CWnd* pParent = NULL);   // standard constructor

	CArray<CString, CString&> m_protocols;
	CString m_protocolname;
	bool m_allow_base_overwrite;

// Dialog Data
	//{{AFX_DATA(CSaveAsDlg)
	enum { IDD = IDD_PPSDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveAsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveAsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListProtocols();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEASDLG_H__032CD355_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
