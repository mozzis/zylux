/////////////////////////////////////////////////////////////////////////////
// EdtRow.h
// CEdtRow is an edit box which only accepts numbers
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
//
// $History: EdtRow.h $ 
// 
// *****************  Version 4  *****************
// User: Maynard      Date: 5/15/00    Time: 10:40a
// Updated in $/ZyluxCap/2.0
// Add Source Safe header
//
#if !defined(AFX_EDTROW_H__983105C4_F899_11D2_88A4_00104BF194E2__INCLUDED_)
#define AFX_EDTROW_H__983105C4_F899_11D2_88A4_00104BF194E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEdtRow window
#define WM_BADROWCHAR (WM_APP + 11)

class CEdtRow : public CEdit
{
// Construction
public:
	CEdtRow();

  enum { eNoZero = 1, eNotDigit = 2 };
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdtRow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEdtRow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEdtRow)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDTROW_H__983105C4_F899_11D2_88A4_00104BF194E2__INCLUDED_)
