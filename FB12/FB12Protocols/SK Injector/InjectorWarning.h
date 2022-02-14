#if !defined(AFX_INJECTORWARNING_H__A3045601_4728_11D2_8C08_00400516EF5A__INCLUDED_)
#define AFX_INJECTORWARNING_H__A3045601_4728_11D2_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InjectorWarning.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInjectorWarning dialog

class CInjectorWarning : public CDialog
{
// Construction
public:
	bool m_warnflag;
	CInjectorWarning(bool show, CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CInjectorWarning)
	enum { IDD = IDD_INJECTWARN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectorWarning)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInjectorWarning)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTORWARNING_H__A3045601_4728_11D2_8C08_00400516EF5A__INCLUDED_)
