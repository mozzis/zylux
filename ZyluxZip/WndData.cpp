/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// WndData.cpp : implementation file
// WndData is a mini-terminal window to send/receive chars with a COM port
/////////////////////////////////////////////////////////////////////////////
/*
* $History: WndData.cpp $ * 
// 
// *****************  Version 5  *****************
// User: Maynard      Date: 5/15/00    Time: 11:38a
// Updated in $/ZyluxZip
// Use font settings from registry
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:23p
 * Updated in $/ZyluxZip
 * Add hex mode and font management
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/27/00    Time: 3:00p
 * Updated in $/ZyluxZip
 * Set up to read/write registry settings on create/destroy
 * Add SetInfo and GetInfo methods to communicate with Settings dialog
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:43p
 * Updated in $/ZyluxZip
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "resource.h"
#include "WndData.h"
#include "tty.h"
#include "winplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndData dialog

WndDataInfo::WndDataInfo() :
    m_bLocalEcho(false),
    m_bDisplayErrors(false),
    m_bAutoWrap(false),
    m_bNewLine(false),
    m_rgbFGColor(0),
    m_hFont(0)
{
}

void WndDataInfo::ReadRegistry()
{
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  m_bLocalEcho      = 0 != pApp->GetIntSetting(IDS_LOCALECHO, FALSE);
  m_bAutoWrap       = 0 != pApp->GetIntSetting(IDS_AUTOWRAP, TRUE);
  m_bDisplayErrors  = 0 != pApp->GetIntSetting(IDS_DISPERRS, TRUE);
  m_bNewLine        = 0 != pApp->GetIntSetting(IDS_NEWLINE, TRUE);
  m_rgbFGColor      = 0 != pApp->GetIntSetting(IDS_TEXTCOLOR, 0);
  m_bHexMode        = 0 != pApp->GetIntSetting(IDS_HEXMODE, FALSE);

  m_lfFont.lfItalic =  0 != pApp->GetIntSetting(IDS_FONTITALIC, 0);
  m_lfFont.lfHeight =  pApp->GetIntSetting(IDS_FONTHEIGHT, -9);
  m_lfFont.lfWidth  =  pApp->GetIntSetting(IDS_FONTWIDTH, 10);
  m_lfFont.lfWeight =  pApp->GetIntSetting(IDS_FONTWEIGHT, FW_NORMAL);
  m_lfFont.lfPitchAndFamily = pApp->GetIntSetting(IDS_FONTPITCH, FIXED_PITCH | FF_MODERN);
  CString csName = pApp->GetStringSetting(IDS_FONTNAME, _T("FixedSys"));
  _tcsncpy(m_lfFont.lfFaceName, (LPCTSTR)csName, LF_FACESIZE);
  m_lfFont.lfFaceName[LF_FACESIZE-1] = 0;
}

void WndDataInfo::WriteRegistry()
{
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  pApp->SetIntSetting(IDS_LOCALECHO, m_bLocalEcho    );
  pApp->SetIntSetting(IDS_AUTOWRAP,  m_bAutoWrap     );
  pApp->SetIntSetting(IDS_DISPERRS,  m_bDisplayErrors);
  pApp->SetIntSetting(IDS_NEWLINE,   m_bNewLine      );
  pApp->SetIntSetting(IDS_TEXTCOLOR, m_rgbFGColor    );
  pApp->SetIntSetting(IDS_HEXMODE,   m_bHexMode      );

  pApp->SetIntSetting(IDS_FONTITALIC, m_lfFont.lfItalic);
  pApp->SetIntSetting(IDS_FONTHEIGHT, m_lfFont.lfHeight);
  pApp->SetIntSetting(IDS_FONTWIDTH,  m_lfFont.lfWidth);
  pApp->SetIntSetting(IDS_FONTWEIGHT, m_lfFont.lfWeight);
  pApp->SetIntSetting(IDS_FONTPITCH,  m_lfFont.lfPitchAndFamily);
  pApp->SetStringSetting(IDS_FONTNAME, m_lfFont.lfFaceName);
}

//////////////////////////////////////////////////////////////////////////
void CWndData::CommonConstruct()
{
	//{{AFX_DATA_INIT(CWndData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_bHexMode = false;
  // setup default font information
  m_lfFont.lfEscapement =     0;
  m_lfFont.lfOrientation =    0;
  m_lfFont.lfUnderline =      0;
  m_lfFont.lfStrikeOut =      0;
  m_lfFont.lfCharSet =        ANSI_CHARSET;
  m_lfFont.lfOutPrecision =   OUT_DEFAULT_PRECIS;
  m_lfFont.lfClipPrecision =  CLIP_DEFAULT_PRECIS;
  m_lfFont.lfQuality =        DEFAULT_QUALITY;
  ReadRegistry();
  m_hFont = CreateFontIndirect(&m_lfFont);
}

//////////////////////////////////////////////////////////////////////////
CWndData::CWndData(CWnd* pParent /*=NULL*/)
	: CDialog(CWndData::IDD, pParent)
{
  m_ppRef = 0;
  m_pTTYInfo = 0;
  CommonConstruct();
}

//////////////////////////////////////////////////////////////////////////
CWndData::CWndData(CWnd* pParent /*=NULL*/, CWndData **ppRef, CTTYInfo *pInfo)
	: CDialog(CWndData::IDD, pParent)
{
  m_ppRef = ppRef;
  m_pTTYInfo = pInfo;
  CommonConstruct();
}

//////////////////////////////////////////////////////////////////////////
CWndData::~CWndData()
{
  if (m_ppRef)
    *m_ppRef = 0; // let parent know window is gone
  WriteRegistry();
}

BOOL CWndData::SetInfo(const WndDataInfo *pInfo)
{
  m_bLocalEcho     = pInfo->m_bLocalEcho;
  m_bDisplayErrors = pInfo->m_bDisplayErrors;
  m_bAutoWrap      = pInfo->m_bAutoWrap;
  m_bNewLine       = pInfo->m_bNewLine;
  m_rgbFGColor     = pInfo->m_rgbFGColor;
//  m_hFont          = pInfo->m_hFont;
}

BOOL CWndData::GetInfo(WndDataInfo *pInfo) const
{
  pInfo->m_bLocalEcho     = m_bLocalEcho;
  pInfo->m_bDisplayErrors = m_bDisplayErrors;
  pInfo->m_bAutoWrap      = m_bAutoWrap;
  pInfo->m_bNewLine       = m_bNewLine;
  pInfo->m_rgbFGColor     = m_rgbFGColor;
  pInfo->m_lfFont         = m_lfFont;
//  pInfo->m_hFont          = m_hFont;
}

//////////////////////////////////////////////////////////////////////////
void CWndData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWndData)
	DDX_Control(pDX, IDC_TTYDATA, m_EdtData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWndData, CDialog)
	//{{AFX_MSG_MAP(CWndData)
	ON_WM_CLOSE()
	ON_WM_SIZE()
  ON_MESSAGE(WM_SHOWTTY, HandleShowMsg)
	ON_BN_CLICKED(IDC_HEXMODE, OnHexMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWndData message handlers

// handle modeless deletion
//////////////////////////////////////////////////////////////////////////
void CWndData::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
}

//////////////////////////////////////////////////////////////////////////
void CWndData::OnClose() 
{
  DestroyWindow();	
}

//////////////////////////////////////////////////////////////////////////
void CWndData::OnOK() 
{
  OnClose();
}

//////////////////////////////////////////////////////////////////////////
BOOL CWndData::OnInitDialog() 
{
	CDialog::OnInitDialog();
  CRect rectWnd, rectThis;
  CWnd *pWnd = GetDlgItem(IDC_TTYDATA);
  if (pWnd)
    {
    // save the original gaps around the edit control
    // when window is resized, the edit will also be
    // resized to maintain the same gaps
    pWnd->GetWindowRect(&rectWnd);
    GetWindowRect(&rectThis);
    m_nGapLeft = rectWnd.left - rectThis.left;
    m_nGapRight = rectThis.right - rectWnd.right;
    m_nGapTop = rectWnd.top - rectThis.top;
    m_nGapBottom = rectThis.bottom - rectWnd.bottom;

    if (m_hFont)
      {
      CFont mFont;
      mFont.Attach(m_hFont);
      pWnd->SetFont(&mFont, FALSE);
      mFont.Detach();
      }
    }
  CButton *pBtn = (CButton *)GetDlgItem(IDC_HEXMODE);
  if (pBtn)
    pBtn->SetCheck(m_bHexMode);

  if (m_pTTYInfo && !m_pTTYInfo->fConnected)
    m_pTTYInfo->OpenConnection();
  CWindowPlacement().Restore(IDR_ENT_DATA, this, FALSE, FALSE);
  GetDlgItem(IDC_TTYDATA)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
}

// When dialog is resized, move the edit control and the "Push" button
// so that they stay in the proper positions relative to the dialog
//////////////////////////////////////////////////////////////////////////
void CWndData::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
  CRect rectWnd, rectThis;
  CWnd *pWnd = GetDlgItem(IDC_TTYDATA);
  if (!pWnd)
    return;
  pWnd->GetWindowRect(&rectWnd);
  ScreenToClient(&rectWnd);
  GetWindowRect(&rectThis);
  ScreenToClient(&rectThis);
  // calc new rect using saved gaps around sides
  rectWnd.left = rectThis.left + m_nGapLeft;
  rectWnd.right = rectThis.right - m_nGapRight;
  rectWnd.top = rectThis.top + m_nGapTop;
  rectWnd.bottom = rectThis.bottom - m_nGapBottom;
  pWnd->MoveWindow(&rectWnd);
  pWnd = GetDlgItem(IDC_HEXMODE);
  if (!pWnd)
    return;
  pWnd->GetWindowRect(&rectWnd);
  ScreenToClient(&rectWnd);
  rectWnd.OffsetRect((rectThis.right - rectWnd.right) - m_nGapRight, 0);
  pWnd->MoveWindow(&rectWnd);
}

//---------------------------------------------------------------------------
//  Description:
//     Writes character block to this window
//---------------------------------------------------------------------------
void CWndData::ShowTTYBlock(CTTYInfo *pInfo, LPCSTR lpBlock, int nLength)
{
  // if this is local echo data, don't show it if "local echo" is not on
  if (pInfo->m_ShowTTYInfo.bLocal && !m_bLocalEcho)
    return;
  // if this is a tty error message, don't show it if "show errors" in not on
  if (pInfo->m_ShowTTYInfo.bError && !m_bDisplayErrors)
    return;
  CString csData, csOut;
  // appends new text to existing text
  _tcsncpy(csData.GetBuffer(nLength), lpBlock, nLength);
  csData.ReleaseBuffer(nLength);
  for (int i = 0; i < nLength; i++)
    {
    unsigned char nCh = csData[i];
    if (m_bHexMode)
      {
      CString csAsc;
      csAsc.Format(_T("%2.2x"), nCh);
      csOut += csAsc;
      if (i < nLength - 1)
        csOut += _T(' ');
      }
    else
      csOut += nCh;
    }
  if (m_bNewLine)
    csOut += _T('\n');
  m_EdtData.SetSel(-1, -1, TRUE);
  m_EdtData.ReplaceSel(csOut);
  return;
}

// Gets message from the TTY watch thread, writes data to window
//////////////////////////////////////////////////////////////////////////
long CWndData::HandleShowMsg(WPARAM wParam, LPARAM lParam)
{
  SHOWTTYINFO *pShowInfo = (SHOWTTYINFO *)lParam;
  CTTYInfo *pInfo = pShowInfo->pTTYInfo;
  LPCSTR lpBlock = pShowInfo->pData;
  int nLength = pShowInfo->nLength;
  ShowTTYBlock(pInfo, lpBlock, nLength);
  return 0;
}

// Called when the user changes the font using the Settings dialog
//////////////////////////////////////////////////////////////////////////
void CWndData::OnSetFont(CFont* pFont) 
{
  pFont->GetLogFont(&m_lfFont);
  m_hFont = (HFONT)pFont->GetSafeHandle();
  if (GetSafeHwnd())
    {
    CWnd *pWnd = GetDlgItem(IDC_TTYDATA);
    if (pWnd)
      pWnd->SetFont(pFont);
	  CDialog::OnSetFont(pFont);
    }
}

BOOL CWndData::DestroyWindow() 
{
  if (m_pTTYInfo && m_pTTYInfo->fConnected)
    m_pTTYInfo->CloseConnection();

  CWindowPlacement().Save(IDR_ENT_DATA, this);
	return CDialog::DestroyWindow();
}

void CWndData::SendTTYData(LPCTSTR pData, int nBytes)
{
  if (m_pTTYInfo && m_pTTYInfo->fConnected)
    m_pTTYInfo->WriteCommBlock(pData, nBytes);
}

bool CWndData::GetLocalEcho(void)
{
  return (m_bLocalEcho);
}

static BOOL Pump()
{
  MSG msg;
  // Retrieve and dispatch any waiting messages.
  while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) 
    {                              
    if (!AfxGetApp()->PumpMessage()) 
      {
      ::PostQuitMessage (0);
      return FALSE;
      }
    else if (WM_CLOSE == msg.message)
      return FALSE;
    }
  // Simulate the framework's idle processing mechanism.
  LONG lIdle = 0;
  while (AfxGetApp ()->OnIdle (lIdle++))
    continue;

  return TRUE;
}

void CWndData::OnHexMode() 
{
  CButton *pBtn = (CButton *)GetDlgItem(IDC_HEXMODE);
  if (pBtn)
    m_bHexMode = pBtn->GetCheck() != 0;
}
