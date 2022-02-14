// QM.h : main header file for the QM application
//

#if !defined(AFX_QM_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_QM_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MainFrm.h"
#include "QMPPS.h"
#include "Protocol.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CQMApp:
// See QM.cpp for the implementation of this class
//

class CQMApp : public CProtocolApp
{
public:
	CQMApp();
	~CQMApp();

	virtual BOOL ModeEdit();
	virtual BOOL ModeRunView();
	virtual BOOL ModeView();
	virtual BOOL ModeRun();
	virtual BOOL ModeGen();

	CQMPPS m_pps;
	CMainFrame* m_pMainFrame;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQMApp)
	public:
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
#define QMGetApp() ((CQMApp*)AfxGetApp())

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QM_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
