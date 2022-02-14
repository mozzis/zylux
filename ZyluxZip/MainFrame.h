/////////////////////////////////////////////////////////////////////////////
// Mainframe.h
// Mainframe is the main window for this application
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MainFrame.h $ * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:40p
 * Updated in $/ZyluxZip
 * Put back special system menu handling (defers to child form)
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:37p
 * Updated in $/ZyluxZip
 * Remove un-needed overrides of OnDestroy, OnMenuSelect and OnSysCommand
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 2/27/00    Time: 4:42p
 * Created in $/ZyluxZip
 * 
*/

#if !defined(AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMStatusBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame frame

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

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
  class CZyluxZipDlg *m_pDlg;

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAboutBox();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__454CE920_C31A_11D2_88A4_444553540000__INCLUDED_)
