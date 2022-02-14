// CA.h : main header file for the CA application
//

#if !defined(AFX_CA_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CA_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MainFrm.h"
#include "CADoc.h"
#include "CAPPS.h"
#include "Protocol.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCAApp:
// See CA.cpp for the implementation of this class
//

class CCAApp : public CProtocolApp
{
public:
	CCAApp();
	~CCAApp();

	virtual BOOL ModeEdit();
	virtual BOOL ModeRunView();
	virtual BOOL ModeView();
	virtual BOOL ModeRun();
	virtual BOOL ModeGen();

	CCAPPS m_pps;
	CMainFrame* m_pMainFrame;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAApp)
	public:
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCAApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#define CAGetApp() ((CCAApp*)AfxGetApp())

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CA_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
