// mystrtok.cpp: defines a function for tokenizing strings
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: mystrtok.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 12:00p
 * Updated in $/ZyluxZip
 * Separate mystrtok into separate file so can re-use
*/
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mystrtok.h"

// version of strtok which returns zero-length string if
// a delimiter was found with no token text; i.e. it doesn't
// skip multiple occurrences of the delimiter as strtok does
/////////////////////////////////////////////////////////////////////////////
LPTSTR mystrtok(LPTSTR szStr, LPCTSTR szDelims)
{
  static LPTSTR pBuf = 0;
  LPTSTR pDelim = 0;
  if (!szStr) // call first time with strbuf address; subsequent with NULL
    szStr = pBuf; // save for next call
  if (szStr && *szStr && 0 != (pDelim = _tcspbrk(szStr, szDelims)))
    { // "token" (including empty string) found!
    *pDelim = 0; // zap the delim
    pBuf = &pDelim[1]; // save for next time
    return szStr; // return found "token"
    }
  pBuf = 0; // reset buffer address
  return 0; // nothing found
}

