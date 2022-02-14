// PSSettings.cpp : implementation file
// CPSSettings property sheet is for all settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PSSettings.cpp $ * 
// 
// *****************  Version 2  *****************
// User: Maynard      Date: 5/15/00    Time: 10:48a
// Updated in $/ZyluxCap/2.0
// Add m_bAutomated flag, set by parent, and used to know if the serial
// settings dialog should be included in the settings prop sheet
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "PSSettings.h"
#include "ppapp.h"
#include "ppdatawin.h"
#include "ppserial.h"
#include "ppxfer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSSettings

IMPLEMENT_DYNAMIC(CPSSettings, CPropertySheet)

CPSSettings::CommonConstruct(CTTYInfo *pInfo, bool bAutomated)
{
  m_bAutomated = bAutomated;
  SetInfo(pInfo);
  m_psh.dwFlags |= PSH_NOAPPLYNOW; // Zap 'Apply' button
  m_pPPApp = new CPPApp(GetInfo());
  m_pPPDataWin = new CPPDataWin(GetInfo());
  if (!m_bAutomated)
    m_pPPSerial = new CPPSerial(GetInfo());
  else
    m_pPPSerial = 0;
  m_pPPXfer = new CPPXfer(GetInfo());
  AddPage(m_pPPApp);
  AddPage(m_pPPDataWin);
  if (!m_bAutomated)
    AddPage(m_pPPSerial);
  AddPage(m_pPPXfer);
}

CPSSettings::CPSSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, CTTYInfo *pI, bool bAutomated)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
  CommonConstruct(pI, bAutomated);
}

CPSSettings::CPSSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage, CTTYInfo *pI, bool bAutomated)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
  CommonConstruct(pI, bAutomated);
}

CPSSettings::~CPSSettings()
{
  delete m_pPPApp;
  delete m_pPPDataWin;
  delete m_pPPSerial;
  delete m_pPPXfer;
}

BEGIN_MESSAGE_MAP(CPSSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CPSSettings)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSSettings message handlers

BOOL CPSSettings::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
  CWindowPlacement().Restore(IDR_ENT_SETTINGS, this, TRUE, FALSE);
	return bResult;
}

void CPSSettings::OnDestroy() 
{
  CWindowPlacement().Save(IDR_ENT_SETTINGS, this);
	CPropertySheet::OnDestroy();
}
