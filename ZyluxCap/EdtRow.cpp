/////////////////////////////////////////////////////////////////////////////
// EdtRow.cpp : implementation file
// CEdtRow is an edit control which will only numeric entries > 0
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: EdtRow.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/22/99    Time: 12:12p
 * Updated in $/ZyluxCap/2.0
 * Limit chars to digits in OnChar instead of via style bits in resource -
 * less error-prone and also provides for warning messages
 * 
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "EdtRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdtRow

CEdtRow::CEdtRow()
{
}

CEdtRow::~CEdtRow()
{
}


BEGIN_MESSAGE_MAP(CEdtRow, CEdit)
	//{{AFX_MSG_MAP(CEdtRow)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdtRow message handlers

void CEdtRow::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  TCHAR tcBuff[4];
  if ((nChar == _T('0')) &&      // char is a zero
      GetLine(0, tcBuff, 4) < 1) // it's the only char
    // warn user; value can't start with or be zero
    GetParent()->SendMessage(WM_BADROWCHAR, (WPARAM)eNoZero, 0);
  else if (!_istdigit(nChar)) // must be a digit (0-9)
    GetParent()->SendMessage(WM_BADROWCHAR, (WPARAM)eNotDigit, 0);
  else // char is OK, process it
    {
    CEdit::OnChar(nChar, nRepCnt, nFlags);
    GetParent()->SendMessage(WM_BADROWCHAR, 0, 0); // clear error message
    }
}
