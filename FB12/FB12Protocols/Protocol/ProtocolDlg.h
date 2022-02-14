#if !defined(AFX_PROTOCOLDLG_H__312E27E1_1ED9_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLDLG_H__312E27E1_1ED9_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProtocolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg dialog

class CProtocolDlg : public CDialog
{
// Construction
public:
	CProtocolDlg(LPCTSTR protocolname, UINT nIDTemplate, CWnd* pParentWnd = NULL);

	LPCTSTR m_protocolname;

// Dialog Data
	//{{AFX_DATA(CProtocolDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolDlg)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProtocolDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLDLG_H__312E27E1_1ED9_11D1_AE1E_0080C80C9F0E__INCLUDED_)
