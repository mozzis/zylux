// PPApp.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPApp.h $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/
#if !defined(AFX_PPAPP_H__32161E61_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PPAPP_H__32161E61_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmproppage.h"

/////////////////////////////////////////////////////////////////////////////
// CPPApp dialog

class CPPApp : public CMMPropPage
{
	DECLARE_DYNCREATE(CPPApp)

// Construction
public:
	CPPApp();
  CPPApp(CTTYInfo *pI);
  void CommmonConstruct();
	~CPPApp();

// Dialog Data
	//{{AFX_DATA(CPPApp)
	enum { IDD = IDD_PP_APP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPApp)
	protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAPP_H__32161E61_E84A_11D2_88A4_444553540000__INCLUDED_)
