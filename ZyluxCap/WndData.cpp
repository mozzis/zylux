/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// WndData.cpp : implementation file
// WndData is a mini-terminal window to send/receive chars with a COM port
/////////////////////////////////////////////////////////////////////////////
/*
* $History: WndData.cpp $ * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:08a
 * Updated in $/ZyluxCap/1.2
 * Set flag in TTYInfo when busy reading data
 * Add Pump procedure so long read could be aborted - not working yet
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:26a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#include "stdafx.h"
#include <afxpriv.h>
#include "ZyluxCap.h"
#include "WndData.h"
#include "tty.h"
#include "pushdata.h"
#include "winplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndData dialog

//////////////////////////////////////////////////////////////////////////
void CWndData::CommonConstruct()
{
	//{{AFX_DATA_INIT(CWndData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//////////////////////////////////////////////////////////////////////////
CWndData::CWndData(CWnd* pParent /*=NULL*/)
	: CDialog(CWndData::IDD, pParent)
{
}

//////////////////////////////////////////////////////////////////////////
CWndData::CWndData(CWnd* pParent /*=NULL*/, CWndData **ppRef, CTTYInfo *pInfo)
	: CDialog(CWndData::IDD, pParent)
{
  m_ppRef = ppRef;
  m_pTTYInfo = pInfo;
}

//////////////////////////////////////////////////////////////////////////
CWndData::~CWndData()
{
  *m_ppRef = 0; // let parent know window is gone
  m_pTTYInfo = 0;
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
	ON_BN_CLICKED(IDC_PUSH, OnPush)
	ON_BN_CLICKED(IDC_LOADFILE, OnLoadfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWndData message handlers

// handle modeless deletion
//////////////////////////////////////////////////////////////////////////
void CWndData::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
  delete this; // must do here; parent can't
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
    if (m_pTTYInfo->hTTYFont)
      {
      CFont mFont;
      mFont.Attach(m_pTTYInfo->hTTYFont);
      pWnd->SetFont(&mFont, FALSE);
      mFont.Detach();
      }
    }
  CWindowPlacement().Restore(IDR_ENT_DATA, this, FALSE, FALSE);
  GetDlgItem(IDC_TTYDATA)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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
  pWnd = GetDlgItem(IDC_PUSH);
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
  CString csData;
  // appends new text to existing text
  _tcsncpy(csData.GetBuffer(nLength), lpBlock, nLength);
  csData.ReleaseBuffer(nLength);
  m_EdtData.SetSel(-1, -1, TRUE);
  m_EdtData.ReplaceSel(csData);
  return;
}

// Gets message from the TTY watch thread, writes data to window
//////////////////////////////////////////////////////////////////////////
void CWndData::HandleShowMsg(WPARAM wParam, LPARAM lParam)
{
  SHOWTTYINFO *pShowInfo = (SHOWTTYINFO *)lParam;
  CTTYInfo *pInfo = pShowInfo->pTTYInfo;
  LPCSTR lpBlock = pShowInfo->pData;
  int nLength = pShowInfo->nLength;
  ShowTTYBlock(pInfo, lpBlock, nLength);
}

// Called when the "Push" button is clicked
// Sends the text in the window to Excel
//////////////////////////////////////////////////////////////////////////
void CWndData::OnPush() 
{
  CString csData;
  GetDlgItemText(IDC_TTYDATA, csData);
  int nLenCurr = csData.GetLength();
  ::StuffTTYData(csData, nLenCurr, m_pTTYInfo);
}

// Called when the user changes the font using the Settings dialog
//////////////////////////////////////////////////////////////////////////
void CWndData::OnSetFont(CFont* pFont) 
{
  CWnd *pWnd = GetDlgItem(IDC_TTYDATA);
  if (pWnd)
    pWnd->SetFont(pFont);
	CDialog::OnSetFont(pFont);
}

BOOL CWndData::DestroyWindow() 
{
  CWindowPlacement().Save(IDR_ENT_DATA, this);
	return CDialog::DestroyWindow();
}

void CWndData::SendTTYData(LPCTSTR pData, int nBytes)
{
  if (m_pTTYInfo->fConnected)
    m_pTTYInfo->WriteCommBlock(pData, nBytes);
}

bool CWndData::GetLocalEcho(void)
{
  return (false != m_pTTYInfo->fLocalEcho);
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

static int LoadFile(LPCTSTR FileName, CString& csData)
{
  FILE *pFile = fopen(FileName, "rb");

  if (!pFile)
    return 0;

  int nLines = 0;
  TCHAR tCh = 0;
  csData.Empty();
  do {
    if (EOF != (tCh = _fgettc(pFile)))
      csData += tCh;
    if (tCh == '\n')
      {
      nLines++;
      }
    } while (EOF != tCh);
  fclose(pFile);
  return nLines;
}

// for debugging purposes: load up a file to push
void CWndData::OnLoadfile() 
{
  CString csData;
  m_pTTYInfo->m_bReadingData = true;
  AfxGetMainWnd()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
  if (LoadFile("data.txt", csData))
    {
    SetDlgItemText(IDC_TTYDATA, csData);
    _tcscpy((LPTSTR)m_pTTYInfo->m_pabData, csData);
    // this will trigger a "push" if auto-push is enabled
    m_pTTYInfo->m_cbInCount = csData.GetLength();
    }
  if (m_pTTYInfo)
    {
    m_pTTYInfo->m_bReadingData = false;
    AfxGetMainWnd()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
    }
}
