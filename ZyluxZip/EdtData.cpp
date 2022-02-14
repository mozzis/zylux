// EdtData.cpp : implementation file
// EdtData is a custom edit control which echoes keystrokes to a COM port
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: EdtData.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:39p
 * Updated in $/ZyluxZip
*/

#include "stdafx.h"
#include "resource.h"
#include "EdtData.h"
#include "wnddata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdtData

CEdtData::CEdtData()
{
}

CEdtData::~CEdtData()
{
}


BEGIN_MESSAGE_MAP(CEdtData, CEdit)
	//{{AFX_MSG_MAP(CEdtData)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdtData message handlers

// echoes characters typed to TTY port and optionally to screen
void CEdtData::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  CWndData *pData = (CWndData *)GetParent();
  pData->SendTTYData((LPCTSTR)&nChar, 1); // send to COM port
  if (pData->GetLocalEcho())
    CEdit::OnChar(nChar, nRepCnt, nFlags); // send to screen
}
