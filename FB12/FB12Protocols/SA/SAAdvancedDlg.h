#if !defined(AFX_SAADVANCEDDLG_H__D15F8CE1_1A24_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_SAADVANCEDDLG_H__D15F8CE1_1A24_11D1_87A6_00400516EF5A__INCLUDED_

#include "SAGridWnd.h"	// Added by ClassView
#include "SampGridWnd.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SAAdvancedDlg.h : header file
//
#include "ProtocolDlg.h"
#include "General.h"
/////////////////////////////////////////////////////////////////////////////
// CSAAdvancedDlg dialog

class CSAAdvancedDlg : public CProtocolDlg
{
// Construction
public:
	CSAPPS& m_pps;
	CSampGridWnd m_SampGrid;
	CSAAdvancedDlg(CSAPPS& pps, LPCTSTR filepath, CWnd* pParent = NULL);   // standard constructor

	BOOL VerifyEntries();
	void SetEntries();
// Dialog Data
	//{{AFX_DATA(CSAAdvancedDlg)
	enum { IDD = IDD_SAADVANCED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAAdvancedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSAAdvancedDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnClear();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAADVANCEDDLG_H__D15F8CE1_1A24_11D1_87A6_00400516EF5A__INCLUDED_)
