// DlgProxy.cpp : implementation file
// DlgProxy is the automation-createable proxy for the main window
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: DlgProxy.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:11p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "DlgProxy.h"
#include "ZyluxZipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlgAutoProxy

IMPLEMENT_DYNCREATE(CZyluxZipDlgAutoProxy, CCmdTarget)

CZyluxZipDlgAutoProxy::CZyluxZipDlgAutoProxy()
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
	ASSERT_KINDOF(CZyluxZipDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CZyluxZipDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CZyluxZipDlgAutoProxy::~CZyluxZipDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CZyluxZipDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CZyluxZipDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CZyluxZipDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CZyluxZipDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CZyluxZipDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IZyluxZip to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {AB3992C6-C2A0-4617-902B-B9A7007A0728}
static const IID IID_IZyluxZip =
{ 0xab3992c6, 0xc2a0, 0x4617, { 0x90, 0x2b, 0xb9, 0xa7, 0x0, 0x7a, 0x7, 0x28 } };

BEGIN_INTERFACE_MAP(CZyluxZipDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CZyluxZipDlgAutoProxy, IID_IZyluxZip, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {B0FBB7DF-CC6F-4D82-89DB-9008D0AE6BED}
IMPLEMENT_OLECREATE2(CZyluxZipDlgAutoProxy, "ZyluxZip.Application", 0xb0fbb7df, 0xcc6f, 0x4d82, 0x89, 0xdb, 0x90, 0x8, 0xd0, 0xae, 0x6b, 0xed)

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlgAutoProxy message handlers
