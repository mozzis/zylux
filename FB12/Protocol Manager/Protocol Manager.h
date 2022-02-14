// Protocol Manager.h : main header file for the PROTOCOL MANAGER application
//

#if !defined(AFX_PROTOCOLMANAGER_H__032CD345_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLMANAGER_H__032CD345_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxmt.h>

class CPMActivationWatcher;

/////////////////////////////////////////////////////////////////////////////
// CPMApp:
// See Protocol Manager.cpp for the implementation of this class
//

class CPMApp : public CWinApp
{
public:
	CPMApp();
	~CPMApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPMApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CEvent* m_pInstanceEvent;
	CEvent* m_pShutdownEvent;
	CPMActivationWatcher* m_pActivationWatch;
	friend CPMActivationWatcher;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLMANAGER_H__032CD345_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
