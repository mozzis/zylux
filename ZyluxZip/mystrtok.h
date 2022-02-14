// mystrtok.h: declares a function for tokenizing strings
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: mystrtok.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 12:00p
 * Updated in $/ZyluxZip
 * Separate mystrtok into separate file so can re-use
*/
//
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const TCHAR EOL = _T('\n');
const TCHAR TAB = _T('\t');
#define TABSTR _T("\t")
#define EOLSTR _T("\n")
#define VALID_FILE(x) (x != 0 && (x != CFile::hFileNull))

LPTSTR mystrtok(LPTSTR szStr, LPCTSTR szDelims);
