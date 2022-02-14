// SiteList.cpp: implementation of the CSiteList class.
// CSiteList is a self-loading string array for the SiteList
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: SiteList.cpp $ * 
// 
// *****************  Version 4  *****************
// User: Maynard      Date: 7/21/00    Time: 3:53p
// Updated in $/ZyluxZip
// Warn when attempting to save empty site list or run name list, but
// allow the operation if the user confirms it
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:35p
 * Updated in $/ZyluxZip
 * Don't abort Load operation if threshold or scale fields of site list
 * entry are empty
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:55a
 * Updated in $/ZyluxZip
 * Add Save, Load, and initialization
*/
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zyluxzip.h"
#include "SiteList.h"
#include "mystrtok.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ZYLUXSITEKEY _T("ZYLUX ZIP Site List version ")
#define ZYLUXSITEVER _T("1.0\n")
const TCHAR ZYLUXSITEHDR[] = ZYLUXSITEKEY ZYLUXSITEVER;

CSite::CSite()
{
  m_ThresholdLow = m_ThresholdHigh = m_ScaleLow = m_ScaleHigh = 0;
}

CSite::~CSite()
{

}

//////////////////////////////////////////////////////////////////////
CSiteList::CSiteList()
{
  TCHAR szPath[_MAX_PATH];
  GetWindowsDirectory(szPath, sizeof(szPath));
  m_csFileName = szPath;
  m_csFileName += _T("\\");
  m_csFileName += _T("SiteList.ZDB");
}

CSiteList::~CSiteList()
{

}

bool CSiteList::Save()
{
  UINT uMode = CFile::modeCreate | CFile::modeWrite| CFile::shareDenyWrite | CFile::typeText; 
  bool bRetVal = true;
  CString csLinePut;
  CStdioFile cFile;
  if (!GetSize())
    {
    CString csMsg = _T("The site list is empty! Do you really want to save it?");
    if (IDYES != AfxMessageBox(csMsg, MB_YESNO | MB_ICONSTOP))
      return false;
    }

  if (cFile.Open(m_csFileName, uMode))
    {
    try 
      {
      cFile.WriteString(ZYLUXSITEHDR);
      for (int i = 0; i < GetSize(); i++)
        {
        csLinePut.Format("%s\t%s\t%g\t%g\t%g\t%g\n", 
                          operator[](i).m_csName,
                          operator[](i).m_csDescription,
                          operator[](i).m_ThresholdLow,
                          operator[](i).m_ThresholdHigh,
                          operator[](i).m_ScaleLow,
                          operator[](i).m_ScaleHigh);
        cFile.WriteString(csLinePut);
        }
      cFile.Close();
      }
    catch (CFileException *pE) // catch exceptions locally (for debugging)
      {
      pE->ReportError();
      return false;
      }
    }
  return bRetVal;
}

bool CSiteList::Load()
{
  UINT uMode = CFile::modeRead | CFile::shareDenyWrite | CFile::typeText; 
  bool bRetVal = true;
  CString csLineGet;
  CStdioFile cFile;
  LPCTSTR szDelims = _T(TABSTR "," EOLSTR);

  RemoveAll();
  try
    {
    // See if file exists already
    if (cFile.Open(m_csFileName, uMode))
      {
      // File exists, make sure it's the right kind
      cFile.ReadString(csLineGet);
      // Look for app-specific header
      if (!_tcsnicmp(ZYLUXSITEKEY, csLineGet, sizeof(ZYLUXSITEKEY)))
        {
        CString csMsg;
        csMsg.Format(_T("%s is not a Zylux Zip Site List!"), 
                     m_csFileName);
        AfxMessageBox(csMsg, MB_OK | MB_ICONSTOP);
        return false;
        } // header check
      float dVers;
      LPTSTR szDummy;
      // header present, check for version
      if (!_stscanf(csLineGet, ZYLUXSITEKEY "%f", &dVers) || 
          dVers > _tcstod(ZYLUXSITEVER, &szDummy))
        {
        CString csMsg;
        csMsg.Format(_T("%s was created by a more recent version of Zylux Zip.\r\n"
                    "Abort?"), m_csFileName);
        if (IDYES == AfxMessageBox(csMsg, MB_YESNO))
          return false; // user said to abort the operation
        }
      while(cFile.ReadString(csLineGet))
        {
        CSite cSite;
        csLineGet += _T('\n');
        LPTSTR pBuf = csLineGet.GetBuffer(csLineGet.GetLength()),
               pDummy;
        pBuf = mystrtok(pBuf, szDelims); // Get 1st column
        if (pBuf &&  (cSite.m_csName = pBuf))
          {
          bool bFields = 
            (pBuf = mystrtok(0, szDelims)) &&
            (cSite.m_csDescription = pBuf) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cSite.m_ThresholdLow = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cSite.m_ThresholdHigh = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cSite.m_ScaleLow = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cSite.m_ScaleHigh = _tcstod(pBuf, &pDummy));
          Add(cSite);
          }
        else
          {
          AfxMessageBox(_T("Error! Site List Entry has no name!"));
          bRetVal = false;
          break;
          }
        }
      cFile.Close(); // close input file (happens anyway on function exit)
      }
    } // end of operation
  catch (CFileException *pE) // catch exceptions locally (for debugging)
    {
    pE->ReportError();
    return false;
    }
  return bRetVal;
}
