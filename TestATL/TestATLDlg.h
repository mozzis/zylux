// TestATLDlg.h : header file
//

#if !defined(AFX_TESTATLDLG_H__F56511BE_2165_45E8_B044_6E7114918153__INCLUDED_)
#define AFX_TESTATLDLG_H__F56511BE_2165_45E8_B044_6E7114918153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestATLDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CTestATLDlg dialog

class CTestATLDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestATLDlg);
	friend class CTestATLDlgAutoProxy;

// Construction
public:
	CTestATLDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTestATLDlg();

// Dialog Data
	//{{AFX_DATA(CTestATLDlg)
	enum { IDD = IDD_TESTATL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestATLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTestATLDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CTestATLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTATLDLG_H__F56511BE_2165_45E8_B044_6E7114918153__INCLUDED_)
