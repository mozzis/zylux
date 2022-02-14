#if !defined(AFX_CAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CAEditDlg.h : header file
//

#include "ProtocolDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CCAEditDlg dialog

class CCAEditDlg : public CProtocolDlg
{
// Construction
public:
	CCAPPS& m_pps;

	void SetMeasText();
	void SetDelayText();
	void SetCalculationsText();
	BOOL VerifyEntries();
	void SetEntries();

	CCAEditDlg(CCAPPS& ed_pps, LPCTSTR protocol_name,  CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCAEditDlg)
	enum { IDD = IDD_CAEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCAEditDlg)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAdvanced();
	afx_msg void OnRbStartbutton();
	afx_msg void OnRbDoorclose();
	afx_msg void OnExcel();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
