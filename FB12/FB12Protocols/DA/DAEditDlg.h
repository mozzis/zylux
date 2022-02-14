#if !defined(AFX_DAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAEditDlg.h : header file
//

#include "ProtocolDlg.h"
#include "DAPPS.h"

/////////////////////////////////////////////////////////////////////////////
// CDAEditDlg dialog

class CDAEditDlg : public CProtocolDlg
{
// Construction
public:
	CDAEditDlg(CDAPPS& pps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor

	CDAPPS& m_pps;

	void SetMeasAText();
	void SetDelayAText();
	void SetMeasBText();
	void SetDelayBText();

	void ReadFields();
	bool VerifyFields();

// Dialog Data
	//{{AFX_DATA(CDAEditDlg)
	enum { IDD = IDD_DAEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDAEditDlg)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAdvanced();
	afx_msg void OnRadioDoorclose();
	afx_msg void OnRadioStartbutton();
	afx_msg void OnExcel();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
