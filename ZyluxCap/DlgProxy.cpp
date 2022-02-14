/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "ZyluxCap.h"
#include "DlgProxy.h"
#include "ZyluxForm.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZyluxFormAutoProxy

IMPLEMENT_DYNCREATE(CZyluxFormAutoProxy, CCmdTarget)

CZyluxFormAutoProxy::CZyluxFormAutoProxy()
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
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
	ASSERT_KINDOF(CMainFrame, AfxGetApp()->m_pMainWnd);
	m_pDialog = ((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetDialog();
	m_pDialog->m_pAutoProxy = this;
}

CZyluxFormAutoProxy::~CZyluxFormAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CZyluxFormAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CZyluxFormAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CZyluxFormAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CZyluxFormAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CZyluxFormAutoProxy)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "Baud", GetBaud, SetBaud, VT_I4)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "Port", GetPort, SetPort, VT_I2)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "FlowCtrl", GetFlowCtrl, SetFlowCtrl, VT_I2)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "DBits", GetDBits, SetDBits, VT_I2)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "Parity", GetParity, SetParity, VT_I2)
	DISP_PROPERTY_EX(CZyluxFormAutoProxy, "StopBits", GetStopBits, SetStopBits, VT_I2)
	DISP_FUNCTION(CZyluxFormAutoProxy, "Advise", Advise, VT_ERROR, VTS_UNKNOWN)
	DISP_FUNCTION(CZyluxFormAutoProxy, "UnAdvise", UnAdvise, VT_ERROR, VTS_UNKNOWN)
	DISP_FUNCTION(CZyluxFormAutoProxy, "SetWindowPos", OleSetWindowPos, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CZyluxFormAutoProxy, "CenterOnRect", CenterOnRect, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CZyluxFormAutoProxy, "Quit", Quit, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ZULUXCAP to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F0CB6025-7876-11D2-88A4-00104BF194E2}
static const IID IID_IZYLUXCAP =
{ 0xf0cb6025, 0x7876, 0x11d2, { 0x88, 0xa4, 0x0, 0x10, 0x4b, 0xf1, 0x94, 0xe2 } };

BEGIN_INTERFACE_MAP(CZyluxFormAutoProxy, CCmdTarget)
	INTERFACE_PART(CZyluxFormAutoProxy, IID_IZYLUXCAP, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {F0CB6023-7876-11D2-88A4-00104BF194E2}
IMPLEMENT_OLECREATE2(CZyluxFormAutoProxy, "ZyluxCap.Application", 0xf0cb6023, 0x7876, 0x11d2, 0x88, 0xa4, 0x0, 0x10, 0x4b, 0xf1, 0x94, 0xe2)

/////////////////////////////////////////////////////////////////////////////
// CZyluxFormAutoProxy message handlers

SCODE CZyluxFormAutoProxy::Advise(LPUNKNOWN pNotifier) 
{
  return m_pDialog->Advise(pNotifier);
}

SCODE CZyluxFormAutoProxy::UnAdvise(LPUNKNOWN pNotifier) 
{
  return m_pDialog->UnAdvise(pNotifier);
}

void CZyluxFormAutoProxy::OleSetWindowPos(long left, long top, long right, long bottom) 
{
  m_pDialog->OleSetWindowPos(left, top, right, bottom);
}

void CZyluxFormAutoProxy::CenterOnRect(long left, long top, long right, long bottom) 
{
  m_pDialog->CenterOnRect(left, top, right, bottom);
}

long CZyluxFormAutoProxy::GetBaud() 
{
	return m_pDialog->GetBaud();
}

void CZyluxFormAutoProxy::SetBaud(long nNewValue) 
{
	m_pDialog->SetBaud(nNewValue);
}

short CZyluxFormAutoProxy::GetPort() 
{
	return m_pDialog->GetPort();
}

void CZyluxFormAutoProxy::SetPort(short nNewValue) 
{
	m_pDialog->SetPort(nNewValue);
}

short CZyluxFormAutoProxy::GetFlowCtrl() 
{
	return m_pDialog->GetFlowCtrl();
}

void CZyluxFormAutoProxy::SetFlowCtrl(short nNewValue) 
{
	m_pDialog->SetFlowCtrl(nNewValue);
}

short CZyluxFormAutoProxy::GetDBits() 
{
	return m_pDialog->GetDBits();
}

void CZyluxFormAutoProxy::SetDBits(short nNewValue) 
{
	m_pDialog->SetDBits(nNewValue);
}

short CZyluxFormAutoProxy::GetParity() 
{
	return m_pDialog->GetParity();
}

void CZyluxFormAutoProxy::SetParity(short nNewValue) 
{
	m_pDialog->SetParity(nNewValue);
}

short CZyluxFormAutoProxy::GetStopBits() 
{
	return m_pDialog->GetStopBits();
}

void CZyluxFormAutoProxy::SetStopBits(short nNewValue) 
{
	m_pDialog->SetStopBits(nNewValue);
}

void CZyluxFormAutoProxy::Quit() 
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  PostQuitMessage(0);
}
