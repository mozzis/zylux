#if !defined(AFX_SKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SKEditDlg.h : header file
//

#include "ProtocolDlg.h"
#include "SKPPS.h"

/////////////////////////////////////////////////////////////////////////////
// CSKEditDlg dialog

class CSKEditDlg : public CProtocolDlg
{
// Construction
public:
	CSKEditDlg(CSKPPS& pps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor

	CSKPPS& m_pps;
	UINT m_duration;

	void SetMeasText();
	void SetDelayText();
	void SetIntervalText();
	void SetDurationText();

	void ReadFields();
	bool VerifyFields();

// Dialog Data
	//{{AFX_DATA(CSKEditDlg)
	enum { IDD = IDD_SKEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSKEditDlg)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditNumsamp();
	afx_msg void OnRadioStartbutton();
	afx_msg void OnRadioDoorclose();
	afx_msg void OnAdvanced();
	afx_msg void OnExcel();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
