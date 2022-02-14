// MMStatusBar.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMStatusBar.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:22a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "MMStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMStatusBar

struct AFX_STATUSPANE
{
	UINT    nID;        // IDC of indicator: 0 => normal text area
	int     cxText;     // width of string area in pixels
						//   on both sides there is a 3 pixel gap and
						//   a one pixel border, making a pane 6 pixels wider
	UINT    nStyle;     // style flags (SBPS_*)
	UINT    nFlags;     // state flags (SBPF_*)
	CString strText;    // text in the pane
};

#define CX_PANE_BORDER 6    // 3 pixels on each side of each pane

inline AFX_STATUSPANE* CStatusBar::_GetPanePtr(int nIndex) const
{
	ASSERT((nIndex >= 0 && nIndex < m_nCount) || m_nCount == 0);
	return ((AFX_STATUSPANE*)m_pData) + nIndex;
}

CMMStatusBar::CMMStatusBar()
{
}

CMMStatusBar::~CMMStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMMStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CMMStatusBar)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMStatusBar message handlers

void CMMStatusBar::OnSize(UINT nType, int cx, int cy) 
{
  int nIndex = CommandToIndex(0);
  if (nIndex >= 0)
    {
    AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
    if (pSBP)
      {
      CClientDC dc(this);
      CSize csText = dc.GetTextExtent(pSBP->strText);
      pSBP->cxText = csText.cx;
      }
    }
	CStatusBar::OnSize(nType, cx, cy);
}
