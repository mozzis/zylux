// PPDataWin.cpp : implementation file
// CPPDataWin property page is for data window settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPDataWin.cpp $ * 
// 
// *****************  Version 5  *****************
// User: Maynard      Date: 5/15/00    Time: 11:36a
// Updated in $/ZyluxZip
// Use font specified in Settings, allow to change
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:15p
 * Updated in $/ZyluxZip
 * Change font handling so it takes effect on the data window if already
 * open
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:55p
 * Updated in $/ZyluxZip
 * Set up data window to save/restore registry settings
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:41p
 * Updated in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 12:05p
 * Created in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "resource.h"
#include "tty.h"
#include "PPDataWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPDataWin property page

IMPLEMENT_DYNCREATE(CPPDataWin, CMMPropPage)

CPPDataWin::CPPDataWin(CWndData *pWnd) : CMMPropPage(CPPDataWin::IDD)
{
	//{{AFX_DATA_INIT(CPPDataWin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  ReadRegistry();
  m_pDataWnd = pWnd;
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
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPDataWin message handlers

BOOL CPPDataWin::OnInitDialog() 
{
	BOOL bRet = CMMPropPage::OnInitDialog();
  CheckDlgButton(IDC_DISPLAYERRORS, m_bDisplayErrors);
  CheckDlgButton(IDC_AUTOWRAP, m_bAutoWrap);
  CheckDlgButton(IDC_NEWLINE, m_bNewLine);
  CheckDlgButton(IDC_LOCALECHO, m_bLocalEcho);

  if (m_pDataWnd)  // get current data window's font
    m_pDataWnd->GetInfo(this);
  else // use dialog's font
    {
    CFont *pFont = GetFont();
    pFont->GetLogFont(&m_lfFont);
    pFont->Detach();
    }

  return bRet;
}

void CPPDataWin::OnOK() 
{
  m_bDisplayErrors = 0 != IsDlgButtonChecked(IDC_DISPLAYERRORS);
  m_bAutoWrap = 0 != IsDlgButtonChecked(IDC_AUTOWRAP);
  m_bNewLine = 0 != IsDlgButtonChecked(IDC_NEWLINE);
  m_bLocalEcho = 0 != IsDlgButtonChecked(IDC_LOCALECHO);
  if (m_pDataWnd) 
    m_pDataWnd->SetInfo(this);
  WriteRegistry();
  CMMPropPage::OnOK();
}

void CPPDataWin::OnFont() 
{
  CHOOSEFONT  cfTTYFont;
  ZeroMemory(&cfTTYFont, sizeof(cfTTYFont));
  cfTTYFont.lStructSize    = sizeof(cfTTYFont);
  cfTTYFont.hwndOwner      = GetSafeHwnd();
  cfTTYFont.hDC            = NULL;
  cfTTYFont.rgbColors      = m_rgbFGColor;
  cfTTYFont.lpLogFont      = &m_lfFont;
  cfTTYFont.Flags          = CF_SCREENFONTS | CF_FIXEDPITCHONLY |
                             CF_EFFECTS | CF_INITTOLOGFONTSTRUCT ;
  cfTTYFont.lCustData      = 0 ;
  cfTTYFont.lpfnHook       = NULL ;
  cfTTYFont.lpTemplateName = NULL ;
  cfTTYFont.hInstance      = AfxGetInstanceHandle();

  if (ChooseFont(&cfTTYFont))
    {
    m_rgbFGColor = cfTTYFont.rgbColors;
    if (m_pDataWnd)
      {
      CFont cFont;
      if (cFont.CreateFontIndirect(cfTTYFont.lpLogFont))
        {
        m_pDataWnd->OnSetFont(&cFont);
        }
      }
    }
}

