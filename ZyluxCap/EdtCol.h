// EdtCol.h
// CEdtCol is an edit control which will only allow entries from "AA" to "ZZ""
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: EdtCol.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/22/99    Time: 12:05p
 * Updated in $/ZyluxCap/2.0
 * Add constants to use in sending warning message to parent
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_EDTCOL_H__636D9F66_EE62_11D2_88A4_444553540000__INCLUDED_)
#define AFX_EDTCOL_H__636D9F66_EE62_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdtCol.h : header file
//
#define WM_BADCOLCHAR (WM_APP + 12)

/////////////////////////////////////////////////////////////////////////////
// CEdtCol window

class CEdtCol : public CEdit
{
// Construction
public:
	CEdtCol();

// Attributes
public:
  enum { eTooMany = 1, eNotAlpha = 2 };
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdtCol)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEdtCol();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEdtCol)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDTCOL_H__636D9F66_EE62_11D2_88A4_444553540000__INCLUDED_)
