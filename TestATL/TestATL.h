// TestATL.h : main header file for the TESTATL application
//

#if !defined(AFX_TESTATL_H__24D93878_09EB_462B_BF72_9291A6983E62__INCLUDED_)
#define AFX_TESTATL_H__24D93878_09EB_462B_BF72_9291A6983E62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "TestATL_i.h"

/////////////////////////////////////////////////////////////////////////////
// CTestATLApp:
// See TestATL.cpp for the implementation of this class
//

class CTestATLApp : public CWinApp
{
public:
	CTestATLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestATLApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestATLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTATL_H__24D93878_09EB_462B_BF72_9291A6983E62__INCLUDED_)
