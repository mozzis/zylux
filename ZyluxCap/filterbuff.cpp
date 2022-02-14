#include "stdafx.h"

// Format:
//
int cBreaks[] = 
//                    1                   2                   3                   4                   5                    6
//0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 |9 0
//Num   B Day . Mon . Yr  B Hr  : Min B B |----Run Name-----| |-----Site Name---| B RHU/s B LoThr B HiThr B F B ChClCRLF| 
  {     3,               12,           19,                 29,                   40,     44,     48,     52, 54  };

// replaces 'blanks' at specified locations with tabs
//////////////////////////////////////////////////////////////////////////
int FilterBuffer(CString &csData)
{
  int nLines = 0,
      nLength = csData.GetLength();
  LPTSTR pData = csData.GetBuffer(nLength);
  for (int i = 0; i < nLength; i+= 58)
    {
    for (int j = 0; j < sizeof(cBreaks) / sizeof(cBreaks[0]);j++)
      if (i + cBreaks[j] < nLength)
        pData[i + cBreaks[j]] = '\t';
    pData[i+57] = '\n';
    pData[i+58] = 0;
    nLines++;
    }
  csData.ReleaseBuffer();
  return nLines;
}
