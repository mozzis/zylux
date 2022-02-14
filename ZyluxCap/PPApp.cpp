// PPApp.cpp : implementation file
// CPPApp is a property page for application-wide settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPApp.cpp $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "PPApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPApp property page

IMPLEMENT_DYNCREATE(CPPApp, CMMPropPage)

void CPPApp::CommmonConstruct()
{
	//{{AFX_DATA_INIT(CPPApp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPApp::CPPApp() : CMMPropPage(CPPApp::IDD)
{
}

CPPApp::CPPApp(CTTYInfo *pI) : CMMPropPage(CPPApp::IDD, pI)
{
}

CPPApp::~CPPApp()
{
}

void CPPApp::DoDataExchange(CDataExchange* pDX)
{
	CMMPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPApp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPApp, CMMPropPage)
	//{{AFX_MSG_MAP(CPPApp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPApp message handlers

//////////////////////////////////////////////////////////////////////////

BOOL CPPApp::OnInitDialog() 
{
	BOOL bRet = CMMPropPage::OnInitDialog();
  CheckDlgButton(IDD_AUTOCONNECT, m_pInfo->m_bAutoConnect);
  CheckDlgButton(IDD_AUTOQUIT, m_pInfo->m_bAutoQuit);
  return bRet;
}

void CPPApp::OnOK() 
{
  m_pInfo->m_bAutoConnect = IsDlgButtonChecked(IDD_AUTOCONNECT);
  m_pInfo->m_bAutoQuit = IsDlgButtonChecked(IDD_AUTOQUIT);
 CMMPropPage::OnOK();
}