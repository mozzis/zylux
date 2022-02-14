#if !defined(AFX_QMEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_QMEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QMEditDlg.h : header file
//

#include "ProtocolDlg.h"
#include "QMPPS.h"

/////////////////////////////////////////////////////////////////////////////
// CQMEditDlg dialog

class CQMEditDlg : public CProtocolDlg
{
// Construction
public:
	CQMEditDlg(CQMPPS& pps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor

	CQMPPS& m_pps;

	void SetMeasText();
	void SetDelayText();

// Dialog Data
	//{{AFX_DATA(CQMEditDlg)
	enum { IDD = IDD_QMEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQMEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQMEditDlg)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QMEDITDLG_H__68788BA1_1817_11D1_AE1E_0080C80C9F0E__INCLUDED_)
