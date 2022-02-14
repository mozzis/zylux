/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: EdtData.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:20a
 * Updated in $/ZyluxCap/2.0
 * Add source safe header keyword
*/

#if !defined(AFX_EDTDATA_H__E338A604_9911_11D2_88A4_444553540000__INCLUDED_)
#define AFX_EDTDATA_H__E338A604_9911_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdtData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdtData window

class CEdtData : public CEdit
{
// Construction
public:
	CEdtData();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdtData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEdtData();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEdtData)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDTDATA_H__E338A604_9911_11D2_88A4_444553540000__INCLUDED_)
