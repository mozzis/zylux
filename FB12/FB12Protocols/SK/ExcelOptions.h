#if !defined(AFX_EXCELOPTIONS_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_EXCELOPTIONS_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ExcelOptions.h : header file
//
#include "ProtocolDlg.h"
#include "General.h"
#include "GPPS.h"
/////////////////////////////////////////////////////////////////////////////
// CExcelOptions dialog

class CExcelOptions : public CProtocolDlg
{
// Construction
public:
	CGPPS& m_pps;
	CExcelOptions(CGPPS& pps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor

	bool VerifyFields();
	void ReadFields();

// Dialog Data
	//{{AFX_DATA(CExcelOptions)
	enum { IDD = IDD_EXCELOPTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExcelOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELOPTIONS_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
