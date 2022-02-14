/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// ZyluxCap.h : main header file for the ZYLUXCAP application
//
/////////////////////////////////////////////////////////////////////////////
/*
* $History: ZyluxCap.h $ * 
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 4/14/00    Time: 10:05a
 * Updated in $/ZyluxCap/2.0
 * Add handler for custom quit message
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:19a
 * Updated in $/ZyluxCap/2.0
 * Remove custom code to register interface, just use CComModule instead
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 10:15a
 * Updated in $/ZyluxCap/2.0
 * Add code to register typelib and notifier interface
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:06a
 * Updated in $/ZyluxCap/1.2
 * Add handler to pass WM_SETMESSAGESTRING from other thread along to
 * mainframe
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:30a
 * Updated in $/ZyluxCap/2.0
 * Add OnAppAbout handler here
 * Add source safe header keyword
*/
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZYLUXCAP_H__F0CB6028_7876_11D2_88A4_00104BF194E2__INCLUDED_)
#define AFX_ZYLUXCAP_H__F0CB6028_7876_11D2_88A4_00104BF194E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZyluxCapApp:
// See ZyluxCap.cpp for the implementation of this class
//

class CZyluxCapApp : public CWinApp
{
public:
	CZyluxCapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxCapApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZyluxCapApp)
	afx_msg void OnAppAbout();
  afx_msg void OnMessageString(UINT wParam, LONG lParam);
  afx_msg void OnAppQuit(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZYLUXCAP_H__F0CB6028_7876_11D2_88A4_00104BF194E2__INCLUDED_)
