// RunNameList.cpp: implementation of the CRunNameList class.
// CRunNameList is a self-loading string array for RunNames
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: RunNameList.cpp $ * 
// 
// *****************  Version 4  *****************
// User: Maynard      Date: 7/21/00    Time: 3:53p
// Updated in $/ZyluxZip
// Warn when attempting to save empty site list or run name list, but
// allow the operation if the user confirms it
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:34p
 * Updated in $/ZyluxZip
 * Don't abort if Description field of name list is empty
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:54a
 * Updated in $/ZyluxZip
 * Add Save, Load, and initialization
*/
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zyluxzip.h"
#include "RunNameList.h"
#include "mystrtok.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ZYLUXNAMESKEY _T("ZYLUX ZIP Name List version ")
#define ZYLUXNAMESVER _T("1.0\n")
const TCHAR ZYLUXNAMESHDR[] = ZYLUXNAMESKEY ZYLUXNAMESVER;

CRunName::CRunName()
{
 
}

CRunName::~CRunName()
{

}

//////////////////////////////////////////////////////////////////////

CRunNameList::CRunNameList()
{
  TCHAR szPath[_MAX_PATH];
  GetWindowsDirectory(szPath, sizeof(szPath));
  m_csFileName = szPath;
  m_csFileName += _T("\\");
  m_csFileName += _T("NameList.ZDB");
}

CRunNameList::~CRunNameList()
{

}

bool CRunNameList::Save()
{
  UINT uMode = CFile::modeCreate | CFile::modeWrite| CFile::shareDenyWrite | CFile::typeText; 
  bool bRetVal = true;
  CString csLinePut;
  CStdioFile cFile;
  if (!GetSize())
    {
    CString csMsg = _T("The Run Name list is empty! Do you really want to save it?");
    if (IDYES != AfxMessageBox(csMsg, MB_YESNO | MB_ICONSTOP))
      return false;
    }

  if (cFile.Open(m_csFileName, uMode))
    {
    try 
      {
      cFile.WriteString(ZYLUXNAMESHDR);
      for (int i = 0; i < GetSize(); i++)
        {
        csLinePut.Format("%s\t%s\t%g\t%g\t%g\t%g\n", 
                          operator[](i).m_csName,
                          operator[](i).m_csDescription);
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

bool CRunNameList::Load()
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
      if (!_tcsnicmp(ZYLUXNAMESKEY, csLineGet, sizeof(ZYLUXNAMESKEY)))
        {
        CString csMsg;
        csMsg.Format(_T("%s is not a Zylux Zip Run Name List!"), 
                     m_csFileName);
        AfxMessageBox(csMsg, MB_OK | MB_ICONSTOP);
        return false;
        } // header check
      float dVers;
      LPTSTR szDummy;
      // header present, check for version
      if (!_stscanf(csLineGet, ZYLUXNAMESKEY "%f", &dVers) || 
          dVers > _tcstod(ZYLUXNAMESVER, &szDummy))
        {
        CString csMsg;
        csMsg.Format(_T("%s was created by a more recent version of Zylux Zip.\r\n"
                    "Abort?"), m_csFileName);
        if (IDYES == AfxMessageBox(csMsg, MB_YESNO))
          return false; // user said to abort the operation
        }
      while(cFile.ReadString(csLineGet))
        {
        CRunName cRunName;
        csLineGet += _T('\n');
        LPTSTR pBuf = csLineGet.GetBuffer(csLineGet.GetLength());
        pBuf = mystrtok(pBuf, szDelims); // Get 1st column
        if (pBuf && (cRunName.m_csName = pBuf))
          {
          bool bFields = 
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunName.m_csDescription = pBuf);
          Add(cRunName);
          }
        else
          {
          AfxMessageBox(_T("Error! Run Name List Entry has no name!"));
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
