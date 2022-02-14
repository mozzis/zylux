/////////////////////////////////////////////////////////////////////////////
// MMSlide.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMSlide.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:22a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#include "stdafx.h"
#include "MMSlide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMSlide

CMMSlide::CMMSlide()
{
}

CMMSlide::~CMMSlide()
{
}

BEGIN_MESSAGE_MAP(CMMSlide, CSliderCtrl)
	//{{AFX_MSG_MAP(CMMSlide)
	ON_WM_HSCROLL_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMSlide message handlers

void CMMSlide::HScroll(UINT /*nSBCode*/, UINT /*nPos*/) 
{
  TRACE("Got the HScroll message!\n");
}

void CMMSlide::VScroll(UINT nSBCode, UINT nPos) 
{
  HScroll(nSBCode, nPos);
}

/////////////////////////////////////////////////////////////////////////////
// CDelaySlide

CDelaySlide::CDelaySlide(UINT nID, CWnd *pParent, double *pValue)
  : CSliderCtrl()
{
  SubclassDlgItem(nID, pParent);
  m_nID = nID;
  m_pValue = pValue;
  SetRange(0, 100);
  SetLineSize(1);
  SetPageSize(2);
  SetTicFreq(5);
  int pos = (int)*pValue;
  if (pParent->GetDlgItem(nID)->GetStyle() & TBS_VERT)
    pos = 100 - pos;
  SetPos(pos);
}

CDelaySlide::~CDelaySlide()
{
}

BEGIN_MESSAGE_MAP(CDelaySlide, CSliderCtrl)
	//{{AFX_MSG_MAP(CDelaySlide)
	ON_WM_HSCROLL_REFLECT()
	ON_WM_VSCROLL_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelaySlide message handlers

void CDelaySlide::HScroll(UINT /*nSBCode*/, UINT /*nPos*/) 
{
  if (m_pValue)
    *m_pValue = (double)GetPos();
  GetParent()->SendMessage(WM_COMMAND, m_nID);
}

void CDelaySlide::VScroll(UINT nSBCode, UINT nPos) 
{
  if (m_pValue)
    *m_pValue = 100 - (double)GetPos();
  GetParent()->SendMessage(WM_COMMAND, m_nID);
}


BOOL CDelaySlide::DestroyWindow() 
{
  UnsubclassWindow();
	return CSliderCtrl::DestroyWindow();
}
