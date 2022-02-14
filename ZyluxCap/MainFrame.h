/////////////////////////////////////////////////////////////////////////////
// Mainframe.h
// Mainframe is the main window for this application
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MainFrame.h $ * 
// 
// *****************  Version 6  *****************
// User: Maynard      Date: 5/15/00    Time: 10:41a
// Updated in $/ZyluxCap/2.0
// Add m_bAutomated to track whether frame was lauched by another program
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:12p
 * Updated in $/ZyluxCap/2.0
 * Add OnClose handler to call dialog's notifier
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:08a
 * Updated in $/ZyluxCap/2.0
 * Add a GetDialog function so autoproxy can get pointer to child dialog
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 6/29/99    Time: 6:57p
 * Updated in $/ZyluxCap/1.1
 * Add OnCommand handler for IDM_ABOUTBOX so menu Exit item works
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:22a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#if !defined(AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainFrame.h : header file
//

#include "mmstatusbar.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame frame

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();           // protected constructor used by dynamic creation

// Attributes
public:
  bool m_bAutomated; // flag if program being controlled
// Operations
public:
  class CZyluxForm *GetDialog() { return m_pDlg; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
  virtual void GetMessageString(UINT, CString&) const;
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainFrame();

  CMMStatusBar m_wndStatusBar;
  class CZyluxForm *m_pDlg;

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
  afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnAboutBox();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_)
