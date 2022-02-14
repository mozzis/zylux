// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "TestATL.h"
#include "DlgProxy.h"
#include "TestATLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestATLDlgAutoProxy

IMPLEMENT_DYNCREATE(CTestATLDlgAutoProxy, CCmdTarget)

CTestATLDlgAutoProxy::CTestATLDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CTestATLDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CTestATLDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CTestATLDlgAutoProxy::~CTestATLDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CTestATLDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CTestATLDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CTestATLDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTestATLDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTestATLDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ITestATL to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {DC7B1C4A-0C45-480D-A53E-96F7AFED7404}
static const IID IID_ITestATL =
{ 0xdc7b1c4a, 0xc45, 0x480d, { 0xa5, 0x3e, 0x96, 0xf7, 0xaf, 0xed, 0x74, 0x4 } };

BEGIN_INTERFACE_MAP(CTestATLDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CTestATLDlgAutoProxy, IID_ITestATL, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {664565D7-CE94-4369-A177-6AC3784DD52E}
IMPLEMENT_OLECREATE2(CTestATLDlgAutoProxy, "TestATL.Application", 0x664565d7, 0xce94, 0x4369, 0xa1, 0x77, 0x6a, 0xc3, 0x78, 0x4d, 0xd5, 0x2e)

/////////////////////////////////////////////////////////////////////////////
// CTestATLDlgAutoProxy message handlers
