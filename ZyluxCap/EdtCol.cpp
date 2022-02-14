/////////////////////////////////////////////////////////////////////////////
// EdtCol.cpp : implementation file
// CEdtCol is an edit control which will only allow entries from "AA" to "ZZ""
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: EdtCol.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/22/99    Time: 12:04p
 * Updated in $/ZyluxCap/2.0
 * Allow user to highlight contents of edit box and type to replace them,
 * even if the box already has two characters in it.
 * Convert all alpha characters to uppercase
 * Specifically limit to alpha characters
 * Send warning message to parent if there is a problem
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:06a
 * Created in $/ZyluxCap
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "EdtCol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdtCol

CEdtCol::CEdtCol()
{
}

CEdtCol::~CEdtCol()
{
}


BEGIN_MESSAGE_MAP(CEdtCol, CEdit)
	//{{AFX_MSG_MAP(CEdtCol)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdtCol message handlers

void CEdtCol::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  TCHAR tcBuff[4];
  int nChars = GetLine(0, tcBuff, 4);
  bool bDoNewChar = true;
  switch (nChar)
    {
    case VK_BACK:   // backspace
    case VK_DELETE: // delete
      break;   // ok to process
    default:
      {
      int nStart, nEnd;
      GetSel(nStart, nEnd);
      if (!_istalpha(nChar)) // if not an alpha char
        bDoNewChar = false;  // reject it
      else if (nChars > 1 && // if at limit already
               nStart == nEnd)    // and no chars are highlighted
        bDoNewChar = false;  // don't process
      else
        {
        // CAUTION - casting const to non-cnst here!
        MSG *pMsg = (MSG *)GetCurrentMessage();
        nChar = towupper(nChar); // process as CAP char only
        pMsg->wParam = nChar; // force value for default handler
        }
      }
    }
	if (bDoNewChar) // if OK
    {
    CEdit::OnChar(nChar, nRepCnt, nFlags); // process it
    GetParent()->SendMessage(WM_BADCOLCHAR, 0, 0); // clear error
    }
  else // not OK
    GetParent()->SendMessage(WM_BADCOLCHAR, // warn user
      (WPARAM)(nChars > 1 ? eTooMany : eNotAlpha), 0);
}
