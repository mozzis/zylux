// TestInst.h : main header file for the TESTINST application
//

#if !defined(AFX_TESTINST_H__A0360977_8701_4F4A_8E5A_F7EB965657F0__INCLUDED_)
#define AFX_TESTINST_H__A0360977_8701_4F4A_8E5A_F7EB965657F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestInstApp:
// See TestInst.cpp for the implementation of this class
//

class CTestInstApp : public CWinApp
{
public:
	CTestInstApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestInstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestInstApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTINST_H__A0360977_8701_4F4A_8E5A_F7EB965657F0__INCLUDED_)
