#if !defined(AFX_INJECTORTOOLBAR_H__E2EF0821_D5E8_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_INJECTORTOOLBAR_H__E2EF0821_D5E8_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InjectorToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInjectorToolBar window

class CInjectorToolBar : public CToolBar //public CToolBarCtrl
{
// Construction
public:
	CInjectorToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectorToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	BYTE m_direction;
	bool is_working;
	virtual ~CInjectorToolBar();

	// Generated message map functions
protected:
	UINT m_timerid;

	static void CALLBACK ManualTimer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void InstanceTimer(void);

	//{{AFX_MSG(CInjectorToolBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTORTOOLBAR_H__E2EF0821_D5E8_11D1_8C08_00400516EF5A__INCLUDED_)
