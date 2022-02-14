#if !defined(AFX_MKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MKEditDlg.h : header file
//

#include "ProtocolDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CMKEditDlg dialog

class CMKEditDlg : public CProtocolDlg
{
// Construction
public:
	UINT m_duration;
	CMKPPS& m_pps;

	void SetMeasText();
	void SetDelayText();
	void SetIntervalText();
	void SetDurationText();
	BOOL VerifyEntries();
	void SetEntries();

	CMKEditDlg(CMKPPS& ed_pps, LPCTSTR protocol_name,  CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMKEditDlg)
	enum { IDD = IDD_MKEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMKEditDlg)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnExcel();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
