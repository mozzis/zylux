#include "stdafx.h"
#include <stdio.h>

static int LoadFile(LPCTSTR FileName, CString& csData)
{
  FILE *pFile = fopen(FileName, "r");

  if (!pFile)
    return 0;

  int nLines = 0;
  TCHAR cBuf[80], *pCh = 0;
  do {
    pCh = _fgetts(cBuf, 80, pFile);
    csData += cBuf;
    nLines++;
    } while (pCh);
  return nLines;
}