// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CE385EE9_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MAINFRM_H__CE385EE9_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ProtocolFrame.h"

class CMainFrame : public CProtocolFrame
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndFB12Bar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG

	afx_msg void OnUpdateDoorStatus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTimer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRX(CCmdUI* pCmdUI);

#ifdef FB12_SIMULATE
	afx_msg void OnToggleDoor();
	afx_msg void OnUpdateDoor(CCmdUI* pCmdUI);
#endif

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CE385EE9_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
