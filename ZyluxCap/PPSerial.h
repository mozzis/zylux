// PPSerial.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPSerial.h $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_PPSERIAL_H__32161E64_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PPSERIAL_H__32161E64_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmproppage.h"

/////////////////////////////////////////////////////////////////////////////
// CPPSerial dialog

class CPPSerial : public CMMPropPage
{
	DECLARE_DYNCREATE(CPPSerial)

// Construction
public:
	CPPSerial();   // standard constructor
  CPPSerial(CTTYInfo *);
  void CommonConstruct();
  ~CPPSerial();

// Dialog Data
	//{{AFX_DATA(CPPSerial)
	enum { IDD = IDD_PP_SERIAL };
		// NOTE - ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPSerial)
	protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPPSerial)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPSERIAL_H__32161E64_E84A_11D2_88A4_444553540000__INCLUDED_)
