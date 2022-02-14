// PPApp.cpp : implementation file
// CPPApp is a property page for application-wide settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPApp.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:41p
 * Updated in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 12:52p
 * Created in $/ZyluxZip
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "PPApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPApp property page

IMPLEMENT_DYNCREATE(CPPApp, CMMPropPage)

CPPApp::CPPApp() : CMMPropPage(CPPApp::IDD)
{
	//{{AFX_DATA_INIT(CPPApp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
  return bRet;
}

void CPPApp::OnOK() 
{
 CMMPropPage::OnOK();
}