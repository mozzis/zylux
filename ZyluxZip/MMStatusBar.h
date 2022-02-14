// MMStatusBar.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMStatusBar.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 2/27/00    Time: 4:42p
 * Created in $/ZyluxZip
 * 
*/

#if !defined(AFX_MMSTATUSBAR_H__454CE924_C31A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_MMSTATUSBAR_H__454CE924_C31A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMMStatusBar window

class CMMStatusBar : public CStatusBar
{
// Construction
public:
	CMMStatusBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMMStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMStatusBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMSTATUSBAR_H__454CE924_C31A_11D2_88A4_444553540000__INCLUDED_)
