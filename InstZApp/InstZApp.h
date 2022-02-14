// InstZApp.h : main header file for the INSTZAPP DLL
//

#if !defined(AFX_INSTZAPP_H__29232AAD_33CB_411B_AA8B_5A188D6963E3__INCLUDED_)
#define AFX_INSTZAPP_H__29232AAD_33CB_411B_AA8B_5A188D6963E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifdef INSTZAPP_EXPORTS
#define INSTZAPP_API __declspec(dllexport)
#else
#define INSTZAPP_API __declspec(dllimport)
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInstZAppApp
// See InstZApp.cpp for the implementation of this class
//

class CInstZAppApp : public CWinApp
{
public:
	CInstZAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstZAppApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CInstZAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

INSTZAPP_API CHAR WINAPI fnInstZApp(HWND, LPSTR, LPSTR, LPSTR, LPSTR);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTZAPP_H__29232AAD_33CB_411B_AA8B_5A188D6963E3__INCLUDED_)
