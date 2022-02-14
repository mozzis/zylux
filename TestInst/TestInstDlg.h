// TestInstDlg.h : header file
//

#if !defined(AFX_TESTINSTDLG_H__C9FAC7BB_241F_4A72_803E_9B383EDE6183__INCLUDED_)
#define AFX_TESTINSTDLG_H__C9FAC7BB_241F_4A72_803E_9B383EDE6183__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestInstDlg dialog

class CTestInstDlg : public CDialog
{
// Construction
public:
	CTestInstDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestInstDlg)
	enum { IDD = IDD_TESTINST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestInstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestInstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTINSTDLG_H__C9FAC7BB_241F_4A72_803E_9B383EDE6183__INCLUDED_)
