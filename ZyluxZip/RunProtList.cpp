// RunProtList.cpp: implementation of the CRunProtList class.
// CRunProtList is a self-loading string array for the RunProtocolList
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: RunProtList.cpp $ * 
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:34p
 * Updated in $/ZyluxZip
 * Don't abort if threshold and scale fields of protocol list are empty on
 * Open operation
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/15/00    Time: 2:00p
 * Updated in $/ZyluxZip
 * Check for file exists in SaveAs
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
#include "mystrtok.h"
#include "RunProtList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ZYLUXPROTKEY _T("ZYLUX ZIP Protocol List version ")
#define ZYLUXPROTVER _T("1.0\n")
const TCHAR ZYLUXPROTHDR[] = ZYLUXPROTKEY ZYLUXPROTVER;

CRunProtList::CRunProtList()
{

}

CRunProtList::~CRunProtList()
{

}

bool CRunProtList::Save()
{
  UINT uMode = CFile::modeCreate | CFile::modeWrite| CFile::shareDenyWrite | CFile::typeText; 
  bool bRetVal = true;
  CString csLinePut;
  CStdioFile cFile;
  if (!GetSize())
    return false;

  if (cFile.Open(m_csFileName, uMode))
    {
    try 
      {
      cFile.WriteString(ZYLUXPROTHDR);
      cFile.WriteString(m_csRunProtocolName + "\n");
      cFile.WriteString(m_csRunName + "\n");
      for (int i = 0; i < GetSize(); i++)
        {
        CRunProtItem cRunProtItem = operator[](i);
        if (cRunProtItem.m_bSelected)
          {
          csLinePut.Format("%s\t%s\t%g\t%g\t%g\t%g\n", 
                            cRunProtItem.m_csName,
                            cRunProtItem.m_csDescription,
                            cRunProtItem.m_ThresholdLow,
                            cRunProtItem.m_ThresholdHigh,
                            cRunProtItem.m_ScaleLow,
                            cRunProtItem.m_ScaleHigh);
          cFile.WriteString(csLinePut);
          }
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

bool CRunProtList::SaveAs(LPCTSTR szFileName)
{
  CFileStatus cStatus;
  if (CFile::GetStatus(szFileName, cStatus))
    {
    CString csMsg;
    csMsg.Format(_T("File %s exists!\nReplace?"), szFileName);
    if (IDYES != AfxMessageBox(csMsg, MB_YESNO|MB_ICONEXCLAMATION))
      return false;
    }
  m_csFileName = szFileName;
  return Save();
}

bool CRunProtList::Load(LPCTSTR szFileName)
{
  UINT uMode = CFile::modeRead | CFile::shareDenyWrite | CFile::typeText; 
  bool bRetVal = false;
  CString csLineGet;
  CStdioFile cFile;
  LPCTSTR szDelims = _T(TABSTR "," EOLSTR);

  RemoveAll();
  try
    {
    // See if file exists already
    m_csFileName = szFileName;
    if (cFile.Open(m_csFileName, uMode))
      {
      // File exists, make sure it's the right kind
      cFile.ReadString(csLineGet);
      // Look for app-specific header
      if (!_tcsnicmp(ZYLUXPROTKEY, csLineGet, sizeof(ZYLUXPROTKEY)))
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
      if (!_stscanf(csLineGet, ZYLUXPROTKEY "%f", &dVers) || 
          dVers > _tcstod(ZYLUXPROTVER, &szDummy))
        {
        CString csMsg;
        csMsg.Format(_T("%s was created by a more recent version of Zylux Zip.\r\n"
                    "Abort?"), m_csFileName);
        if (IDYES == AfxMessageBox(csMsg, MB_YESNO))
          return false; // user said to abort the operation
        }
      if (cFile.ReadString(csLineGet))
        m_csRunProtocolName = csLineGet;
      if (cFile.ReadString(csLineGet))
        m_csRunName = csLineGet;
      while(cFile.ReadString(csLineGet))
        {
        CRunProtItem cRunProtItem;
        csLineGet += _T('\n');
        LPTSTR pBuf = csLineGet.GetBuffer(csLineGet.GetLength()),
               pDummy;
        pBuf = mystrtok(pBuf, szDelims); // Get 1st column
        if (pBuf && (cRunProtItem.m_csName = pBuf))
          {
          bool bFields =
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunProtItem.m_csDescription = pBuf) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunProtItem.m_ThresholdLow = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunProtItem.m_ThresholdHigh = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunProtItem.m_ScaleLow = _tcstod(pBuf, &pDummy)) &&
            (pBuf = mystrtok(0, szDelims)) &&
            (cRunProtItem.m_ScaleHigh = _tcstod(pBuf, &pDummy));
          cRunProtItem.m_bSelected = true;
          Add(cRunProtItem);
          }
        else
          {
          AfxMessageBox(_T("Error! Run Protocol List Entry has no Site Name!"));
          bRetVal = false;
          break;
          }
        }
      bRetVal = true; // success!
      cFile.Close();  // close input file (happens anyway on function exit)
      }
    } // end of operation
  catch (CFileException *pE) // catch exceptions locally (for debugging)
    {
    pE->ReportError();
    return false;
    }
  return bRetVal;
}
