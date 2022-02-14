#if !defined(AFX_DAADVANCED_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_DAADVANCED_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_

#include "DAGridWnd.h"	// Added by ClassView
#include "SampGridWnd.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAAdvanced.h : header file
//
#include "ProtocolDlg.h"
#include "General.h"
/////////////////////////////////////////////////////////////////////////////
// CDAAdvanced dialog

class CDAAdvanced : public CProtocolDlg
{
// Construction
public:
	CDAPPS& m_pps;
	CSampGridWnd m_SampGrid;
	CDAAdvanced(CDAPPS& pps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor

	BOOL VerifyEntries();
	void SetEntries();

// Dialog Data
	//{{AFX_DATA(CDAAdvanced)
	enum { IDD = IDD_DAADVANCED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDAAdvanced)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClear();
	afx_msg void OnDelete();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAADVANCED_H__0D7594C1_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
