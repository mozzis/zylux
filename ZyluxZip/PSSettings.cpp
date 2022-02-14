// PSSettings.cpp : implementation file
// CPSSettings property sheet is for all settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PSSettings.cpp $ * 
// 
// *****************  Version 4  *****************
// User: Maynard      Date: 7/21/00    Time: 3:13p
// Updated in $/ZyluxZip
// Remove Program settings prop page - nothing there yet
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:56p
 * Updated in $/ZyluxZip
 * Link to local TTY info and data window info structs
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:42p
 * Updated in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 11:35a
 * Created in $/ZyluxZip
*/

#include "stdafx.h"
#include "resource.h"
#include "ZyluxZip.h"
#include "PSSettings.h"
#include "ppapp.h"
#include "ppdatawin.h"
#include "ppserial.h"
#include "winplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSSettings

IMPLEMENT_DYNAMIC(CPSSettings, CPropertySheet)

void CPSSettings::CommonConstruct(PSSettingsInfo *pInfo)
{
  m_pTTYInfo = pInfo->pTTY;
  m_psh.dwFlags |= PSH_NOAPPLYNOW; // Zap 'Apply' button
//  m_pPPApp = new CPPApp();
  m_pPPDataWin = new CPPDataWin(pInfo->pData);
  m_pPPSerial = new CPPSerial(pInfo->pTTY);
//  AddPage(m_pPPApp);
  AddPage(m_pPPSerial);
  AddPage(m_pPPDataWin);
}

CPSSettings::CPSSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, PSSettingsInfo *pInfo)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
  CommonConstruct(pInfo);
}

CPSSettings::CPSSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage, PSSettingsInfo *pInfo)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
  CommonConstruct(pInfo);
}

CPSSettings::~CPSSettings()
{
//  delete m_pPPApp;
  delete m_pPPSerial;
  delete m_pPPDataWin;
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
  CWindowPlacement().Restore(IDR_ENT_SETTINGPS, this, TRUE, FALSE);
	return bResult;
}

void CPSSettings::OnDestroy() 
{
  CWindowPlacement().Save(IDR_ENT_SETTINGPS, this);
	CPropertySheet::OnDestroy();
}
