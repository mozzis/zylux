// PPDataWin.cpp : implementation file
// CPPDataWin property page is for data window settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPDataWin.cpp $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "PPDataWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPDataWin property page

IMPLEMENT_DYNCREATE(CPPDataWin, CMMPropPage)

void CPPDataWin::CommonConstruct()
{
	//{{AFX_DATA_INIT(CPPDataWin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPDataWin::CPPDataWin() : CMMPropPage(CPPDataWin::IDD)
{
}

CPPDataWin::CPPDataWin(CTTYInfo *pI) : CMMPropPage(CPPDataWin::IDD, pI)
{
}

CPPDataWin::~CPPDataWin()
{
}

void CPPDataWin::DoDataExchange(CDataExchange* pDX)
{
	CMMPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPDataWin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPDataWin, CMMPropPage)
	//{{AFX_MSG_MAP(CPPDataWin)
	ON_BN_CLICKED(IDD_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPDataWin message handlers

BOOL CPPDataWin::OnInitDialog() 
{
	BOOL bRet = CMMPropPage::OnInitDialog();
  CheckDlgButton(IDD_DISPLAYERRORS, m_pInfo->fDisplayErrors);
  CheckDlgButton(IDD_AUTOWRAP, m_pInfo->fAutoWrap);
  CheckDlgButton(IDD_NEWLINE, m_pInfo->fNewLine);
  CheckDlgButton(IDD_LOCALECHO, m_pInfo->fLocalEcho);
  return bRet;
}

void CPPDataWin::OnOK() 
{
  m_pInfo->fDisplayErrors = IsDlgButtonChecked(IDD_DISPLAYERRORS);
  m_pInfo->fAutoWrap = IsDlgButtonChecked(IDD_AUTOWRAP);
  m_pInfo->fNewLine = IsDlgButtonChecked(IDD_NEWLINE);
  m_pInfo->fLocalEcho = IsDlgButtonChecked(IDD_LOCALECHO);
  CMMPropPage::OnOK();
}

void CPPDataWin::OnFont() 
{
  CHOOSEFONT  cfTTYFont ;
  CTTYInfo *pInfo = GetInfo();

  cfTTYFont.lStructSize    = sizeof(CHOOSEFONT);
  cfTTYFont.hwndOwner      = GetSafeHwnd();
  cfTTYFont.hDC            = NULL;
  cfTTYFont.rgbColors      = pInfo->rgbFGColor;
  cfTTYFont.lpLogFont      = &pInfo->lfTTYFont;
  cfTTYFont.Flags          = CF_SCREENFONTS | CF_FIXEDPITCHONLY |
                             CF_EFFECTS | CF_INITTOLOGFONTSTRUCT ;
  cfTTYFont.lCustData      = 0 ;
  cfTTYFont.lpfnHook       = NULL ;
  cfTTYFont.lpTemplateName = NULL ;
  cfTTYFont.hInstance      = AfxGetInstanceHandle();

  if (ChooseFont(&cfTTYFont))
      pInfo->rgbFGColor = cfTTYFont.rgbColors ;
}
