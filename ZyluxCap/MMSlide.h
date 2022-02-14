/////////////////////////////////////////////////////////////////////////////
// MMSlide.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMSlide.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:22a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#pragma once

class CMMSlide : public CSliderCtrl
{
// Construction
public:
	CMMSlide();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMSlide)
public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMMSlide();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMSlide)
	afx_msg void HScroll(UINT nSBCode, UINT nPos);
	afx_msg void VScroll(UINT nSBCode, UINT nPos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
class CDelaySlide : public CSliderCtrl
{
// Construction
public:
	CDelaySlide(UINT nID, CWnd* pParent, double *pValue = 0);

// Attributes
protected:
  double * m_pValue;
  UINT m_nID;
// Operations
public:

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelaySlide)
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDelaySlide();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDelaySlide)
	afx_msg void HScroll(UINT nSBCode, UINT nPos);
	afx_msg void VScroll(UINT nSBCode, UINT nPos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
