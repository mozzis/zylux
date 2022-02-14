#if !defined(AFX_SERIALDIALOG_H__67CF5021_6FF7_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SERIALDIALOG_H__67CF5021_6FF7_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SerialDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerialDialog dialog

class CSerialDialog : public CDialog
{
// Construction
public:
	bool m_missing;
	CString m_serial_string;
	CSerialDialog(bool is_missing, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialDialog)
	enum { IDD = IDD_SERIAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSerialDialog)
	afx_msg void OnChangeEditSer1();
	afx_msg void OnChangeEditSer2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALDIALOG_H__67CF5021_6FF7_11D1_AE1E_0080C80C9F0E__INCLUDED_)
