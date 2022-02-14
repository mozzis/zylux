// PPXfer.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPXfer.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/22/99    Time: 12:14p
 * Updated in $/ZyluxCap/2.0
 * Add member for custom row edit control
 * Add OnKillActive to validate row and column etnries on exit
 * Add warning message display when invalid chars are entered for row and
 * column addresses
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_PPXFER_H__32161E63_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PPXFER_H__32161E63_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmproppage.h"
#include "edtcol.h"
#include "edtrow.h"

/////////////////////////////////////////////////////////////////////////////
// CPPXfer dialog

class CPPXfer : public CMMPropPage
{
	DECLARE_DYNCREATE(CPPXfer)

// Construction
public:
	CPPXfer();   // standard constructor
  CPPXfer(CTTYInfo *);
  void CommonConstruct();
	~CPPXfer();  // destructor

// Dialog Data
	//{{AFX_DATA(CPPXfer)
	enum { IDD = IDD_PP_XFER };
	CEdtRow m_EdtRow;
	CEdtCol m_EdtCol;
	//}}AFX_DATA

protected:
  class CDelaySlide *m_pSldDelay;
  double m_DelayDbl;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPXfer)
	protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnKillActive(); // return zero if OK to exit
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPXfer)
	afx_msg void OnDelay();
	afx_msg void OnChkFile();
	afx_msg void OnChkSheet();
	afx_msg void OnChkRange();
	afx_msg void OnChkRepFile();
  afx_msg long OnBadRowChar(WPARAM, LPARAM);
  afx_msg long OnBadColChar(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPXFER_H__32161E63_E84A_11D2_88A4_444553540000__INCLUDED_)
