/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// PushData.cpp
/////////////////////////////////////////////////////////////////////////////
/* 
* $Header: /ZyluxCap/2.0/pushdata.cpp 10    6/08/00 7:40a Maynard $
*
* $Log: /ZyluxCap/2.0/pushdata.cpp $
// 
// 10    6/08/00 7:40a Maynard
// Shouldn't specify version of Excel.Application; fails if prev version
// was never installed.
// 
// 9     5/15/00 11:07a Maynard
// Add more comments
// Remove initial '-1' value from CBreak array; not needed anymore as
// placeholder
 * 
 * 8     5/03/00 10:41p Maynard
 * Fix position of run-name field start - was off by one due to incorrect
 * documentation (ref: Dave's EMail 19 Nov 1998)
 * Use string representation of Excel class name - seems to work OK now
 * (didn't before? maybe with Office 95?)
 * Do a better job of looking for an existing open document in Excel - do
 * one-at-a-time compare of filename with and without default extension
 * Set sheet to visible at end of push - just in case Excel settings are
 * wierd
 * 
 * 7     12/08/99 12:12a Maynard
 * Fix error in counting number of lines in British version
*
*/

#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include "pushdata.h"
#include "tty.h"

// #import <mso97.dll> no_namespace rename("DocumentProperties", "DocumentPropertiesXL")   
// #import <vbeext1.olb> no_namespace   
// #import <excel8.olb> rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces

#include "mso97.tlh"
#include "vbeext1.tlh"
#include "excel8.tlh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nLineLength = 59;

// Format: Dave's original message had a table which listed the positions of
// each data field. This table had the site name and run name as each as ten-
// ten-character fields; the run name started at 19 and the site name at 30.
// I created a parsing routine which simply inserted a NUL at each end of field
// position; then I could treat them as regular C strings. This meant that the 
// last character of the Run Name might get zapped if it were the max length.
// Then a British version of the device came out with (slightly?) different
// firmware. Apparently, in this device fields were not of fixed length but
// were delimited with a space character. I made a different parsing routine
// which replaced space characters regardless of position
// Subsequently it was reported as a bug that the first character of the run
// name was being zapped in the _Non-British_ version of the software. This 
// time I looked and found that the default run name in the FB14 (generated
// by choosing the "Reset" function in the Run Name entry function) always
// started with at Space charachter. This is why Dave's table showed two
// blanks between the minutes field and the Run name.
// I changed the field position of the run name from 20 to 19. However, if I
// don't *also* change the position of the Site Name field from 30 to 29, then
// the Run Name field will be 11 characters long, UNLESS position 19 is always
// supposed to contain a space character. Note that in the original scheme, 
// the Run Name and the Site Name were the only fields which were not separ-
// ated by a space. So this is the interpretation I am going with - that both
// name fields were supposed to be 10 characters long (since that is all that
// the instrument will allow you to enter)
//
int cBreaks[] = // these are the positions of the ENDS of each field
//                     1                   2                   3                   4                   5                    6
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 |9 0
// Num   B Day . Mon . Yr  B Hr  : Min B |------Run Name---|B|-----Site Name---| B RHU/s B LoThr B HiThr B F B ChClCRLF| 
  {      3,                12,         18,                  29,                  40,     44,     48,     52, 54,  };

static const int g_nFields = countof(cBreaks)+1;
static const char SPC = ' ';

#ifdef _ZYLUX_BRITISH
#define FilterBuffer FilterBufferSpaces
// replaces 'blanks' (spaces) at specified locations with nulls
// so Excel will see separate strings
//////////////////////////////////////////////////////////////////////////
static int FilterBufferSpaces(CString &csData)
{
  int nLines = 0,
      nLength = csData.GetLength();
  LPTSTR pData = csData.GetBuffer(nLength), pEnd = &pData[nLength];
  while (SPC == *pData && ++pData < pEnd)
    continue; // skip leading blanks

  do
    {
    while ((pData < pEnd) && (SPC == *pData || 0 == *pData))
      *(pData++) = 0; // replace leading blanks with NULs
    while ((pData < pEnd) && (SPC != *pData && 0 != *pData))
      {               // look for next space or NUL
      if ('\n' == *pData) // count CR as EOL
        nLines++;
      if ('\n' == *pData || '\r' == *pData)
        *pData = 0;       // Zap CR/LF, so last field ends at line end
      pData++; // skip non-spaces
      }
    }
  while (pData < pEnd);

  csData.ReleaseBuffer(nLength);
  return nLines;
}

#else // for normal unit

#define FilterBuffer FilterBufferFixedField

static int FilterBufferFixedField(CString &csData)
{
  int nLines = 0,
      nLength = csData.GetLength();
  LPTSTR pData = csData.GetBuffer(nLength);
  for (int i = 0; i < nLength; i+= nLineLength)
    {
    for (int j = 0; j < g_nFields-1;j++)
      if (i + cBreaks[j] < nLength)
        pData[i + cBreaks[j]] = 0;
    if ((i+(nLineLength - 2)) < nLength) 
      pData[i+(nLineLength - 2)] = 0;
    if ((i+(nLineLength - 1)) < nLength) 
      pData[i+(nLineLength - 1)] = 0;
    nLines++;
    }
  csData.ReleaseBuffer(nLength);
  return nLines;
}

#endif // British or normal unit

// handles exceptions from COM (OLE) system calls
void dump_com_error(_com_error &e)
{
  _bstr_t bstrSource(e.Source());
  _bstr_t bstrDescription(e.Description());
  CString csMsg;
  csMsg.Format(_T("Error in OLE automation:\n"
                  "\tCode = %08lx\n"
                  "\tCode meaning = %s\n"
                  "\tSource = %s\n"
                  "\tDescription = %s\n"),
  e.Error(), e.ErrorMessage(), (LPCTSTR) bstrSource, (LPCTSTR) bstrDescription);
  AfxMessageBox(csMsg, MB_ICONEXCLAMATION);
}

HRESULT AllocData(_variant_t &tVar, int nLines)
{
  SAFEARRAY *pNewSA = 0;
  SAFEARRAYBOUND Dims[2] = { { g_nFields, 0 }, { nLines, 0 } };
  V_VT(&tVar) = (VARTYPE)(VT_VARIANT | VT_ARRAY); // make it an array
  if (0 == (pNewSA = SafeArrayCreate(VT_VARIANT, 2, Dims))) // new 2-D array
    return E_OUTOFMEMORY;
  tVar.parray = pNewSA;
  return S_OK;
}

// for unsuccessful system calls. get the error string from Windows
// and display it
/////////////////////////////////////////////////////////////////////////////
DWORD ReportLastError(LPCTSTR caption /* = NULL */)
{
  LPTSTR pMsg;
  DWORD dwErr = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,   // pointer to  message source 
    dwErr,  // requested message identifier 
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR)&pMsg, 0, NULL);
    // Display the string.
    AfxGetMainWnd()->MessageBox(pMsg, caption, MB_OK|MB_ICONINFORMATION);
  LocalFree(pMsg);
  return dwErr;
}

// Given a starting column address, calc a string for the given column
/////////////////////////////////////////////////////////////////////////////
CString GetColStr(const CString& csCol, long nCol)
{
  CString csRet;
  int nLen = csCol.GetLength();
  // Have to handle case of column wrapping, e.g. from "AZ" to "BA"
  if (csCol[nLen-1] + nCol > 'Z') // will incrementing last char wrap it?
    {
    if (nLen < 2) // yes, check for only one char (e.g. "A")
      csRet = "A"; // make two char address starting with "A"
    else          // already two chars
      csRet = (TCHAR)(csCol[nLen-2] + 1); // increment first char
    // now calc value of second char
    csRet += (TCHAR)('A' + (nCol - ('Z' - csCol[nLen-1]) - 1));
    }
  else if (nLen < 2) // room to just increment character
    csRet = (TCHAR)(csCol[0] + nCol); // increment single character
  else // increment double char address
    {
    csRet = csCol.Left(1); // take left char as-is
    csRet += (TCHAR)(csCol[nLen-1] + nCol); // add incremented right char
    }
  return(csRet);
}

// Given a starting row address, calc a string for the given row
/////////////////////////////////////////////////////////////////////////////
CString GetRowStr(const CString& csRow, long nRow)
{
  CString csRet;

  int nRowStart = _ttoi(csRow);
  csRet.Format("%d", nRowStart + nRow);
  return(csRet);
}

//////////////////////////////////////////////////////////////////////////
BOOL StuffTTYData(LPCTSTR pData, int nLength, CTTYInfo *pInfo)
{
  BOOL bRet = TRUE;
  // make a copy of data in csData (necessary?)
  CString csData;
  LPTSTR pCS = csData.GetBufferSetLength(nLength);
  memcpy(pCS, pData, nLength);
  csData.ReleaseBuffer(nLength);
  // Now insert NUL chars at ends of fields
  int nLines = FilterBuffer(csData);
  try // allow local handling of COM (OLE) errors
    {
    Excel::_ApplicationPtr pXL; 
    // See if Excel is already running
    // look for "Microsoft Excel Application"
    pXL.GetActiveObject(L"Excel.Application");
    if (0 == pXL) // if not running yet
      pXL.CreateInstance(L"Excel.Application"); // start it up!
    if (0 /* still! */ == pXL)
      throw _com_error(CO_E_CREATEPROCESS_FAILURE); // couldn't start Excel

    Excel::WorkbooksPtr pBooks = pXL->Workbooks;
    Excel::_WorkbookPtr pBook = 0;
    Excel::_WorksheetPtr pSheet = 0;

    if (pInfo->m_bSpecFile && 
        !pInfo->m_sFile.IsEmpty()) // if user specified file
      {
      // want to check for file open in excel
      // excel doesn't include path in workbook name, so must
      // isolate filename (with extension) and check for that,
      // then see if the paths are the same
      CString csDir, csFile, csPath, csExt;
      _splitpath(pInfo->m_sFile, csDir.GetBuffer(_MAX_DRIVE),
                                 csPath.GetBuffer(_MAX_PATH), 
                                 csFile.GetBuffer(_MAX_FNAME), 
                                 csExt.GetBuffer(_MAX_EXT));
      csDir.ReleaseBuffer();
      csFile.ReleaseBuffer();
      csPath.ReleaseBuffer();
      csExt.ReleaseBuffer();
      csFile += csExt;
      csDir += csPath;
      try // See if the file with the given name is already open
        {
        // Workbook indices are 1-based!
        for (long i = 1; i < pBooks->Count + 1; i++)
          {
          CString csName = (LPCTSTR)pBooks->Item[i]->Name;
          if (!csName.CompareNoCase(csFile) || !csName.CompareNoCase(csFile + _T(".xls")))
            {
            pBook = pBooks->Item[i]; // name part matched, at least
            break;
            }
          }
        if (pBook)
          {
          CString csExPath = (LPCTSTR)pBook->Path;
          csFile = (LPCTSTR)pXL->DefaultFilePath; // get path from Excel

          if (csDir.Right(1) == '\\' && csExPath.Right(1) != '\\')
            csExPath += '\\';
          if (csDir.IsEmpty()) // no dir specified
            {
            if (csExPath.CompareNoCase(csFile)) // compare file's dir with default
              throw _com_error(DISP_E_BADINDEX); // right name, wrong path
            }
          else if(csDir.CompareNoCase(csExPath))
            throw _com_error(DISP_E_BADINDEX); // right name, wrong path
          }
        else
          throw _com_error(DISP_E_BADINDEX); // name not found
        }
      catch (_com_error &e) // if thrown by Excel or by above "throw" lines
        {
        if (DISP_E_BADINDEX == e.Error()) // if couldn't find existfind existing open file
          {
          // look for non-open existing file (on disk)
          // if user included path in spec, use as-is; else, use default data file path
          if (!csPath.IsEmpty()) // user supplied some path
            csFile = pInfo->m_sFile; // use it unchanged
          else
            {
            csFile = (LPCTSTR)pXL->DefaultFilePath; // get path from Excel
            if (csFile.Right(1) != '\\')   // append delimiter as needed
              csFile += '\\';
            csFile += pInfo->m_sFile;      // add supplied file name
            }
          // make sure the file ends with an Excel extension
          if (csFile.Right(4).CompareNoCase(_T(".xls")) &&
              csFile.Right(4).CompareNoCase(_T(".xlw")))
            csFile += _T(".xls");
          if (-1 != _taccess(csFile, 0)) // see if found on disk
            {
            if (pInfo->m_bRepFile) // yes, if user wants to replace existing file
              {
              if (-1 == _tremove(csFile)) // delete it first
                {
                ReportLastError("Can't delete old file!");
                bRet = FALSE;
                }
create_new: //////label, sorry!!///////////////////////////////////////////////
              if (bRet) // if file removed or didn't exist
                {
                _variant_t vNul(vtMissing);
                pBook = pBooks->Add((long)Excel::xlWBATWorksheet); // create with 1 sheet
                pBook->SaveAs (csFile.AllocSysString(),    // give name on disk
                               vNul, vNul, vNul, vNul, vNul, Excel::xlNoChange);
                }
              }
            else // file found and user wants to re-use existing file
              pBook = pBooks->Open(pInfo->m_sFile.AllocSysString()); // open existing
            }
          else // file not found on disk
            goto create_new;
          }   
        else // if com error not due to open file not found
          throw e; // pass up to next level
        } // end catch
      }
    else // user didn't specify file; any file will do
      {
      pBook = pXL->Application->ActiveWorkbook;
      if (0 == pBook)
        pBook = pBooks->Add((long)Excel::xlWBATWorksheet); // create file with 1 sheet
      }

    if (pBook) // if any of the above succeeded
      pBook->Activate(); // make it the active workbook so sheet can be located

    if (pInfo->m_bSpecSheet && 
        !pInfo->m_sSheet.IsEmpty()) // if user specified output sheet
      {
      try
        {
        pSheet = // see if an existing sheet has the desired name
          pXL->ActiveWorkbook->Worksheets->Item[(LPCTSTR)pInfo->m_sSheet];
        }
      catch(_com_error &e) // if GetItem didn't succeed
        {
        if (DISP_E_BADINDEX == e.Error()) // couldn't find a sheet with that name
          {
          pSheet = pXL->Worksheets->Add();  // add a new worksheet
          pSheet->Name = pInfo->m_sSheet.AllocSysString(); // name as desired
          }
        else // com error not due to named sheet not found
          throw e; // pass up to next level
        } // end catch
      }
    else // if any sheet will do
      {
//      pSheet = pXL->ActiveSheet; // see if there's an active one
//      if (NULL == pSheet.GetInterfacePtr())
        pSheet = pXL->Worksheets->Add();  // add new worksheet
      }

    pSheet->Activate();

    // now send array to Excel
    // need to generate range spec of form AB:XY where AB = column and XY = row
    CString csRange;
    CString csCol, csRow;
    if (pInfo->m_bSpecRange &&            // if user specfied output cell
        !pInfo->m_sRangeCol.IsEmpty() &&  
        !pInfo->m_sRangeRow.IsEmpty())
      {
      // generate end cell reference based on start cell
      CString csColStart = pInfo->m_sRangeCol, csColEnd = csColStart, 
              csRowStart = pInfo->m_sRangeRow, csRowEnd;
      int nColChars = csColStart.GetLength();
      // make sure there is room for the data - must have at least
      // <nFields> columns after start
      if (toupper(csColStart[nColChars-1]) > 'Z' - g_nFields &&
          toupper(csColStart[nColChars-2]) > 'Y')
        bRet = FALSE; // no good
      else // room enough, set end column and row characters
        {
        if (csColStart[nColChars-1] + g_nFields-1 <= 'Z') // if no wrap (AP or less)
          csColEnd.SetAt(nColChars-1, csColStart[nColChars-1] + g_nFields-1);
        else // wrap; e.g. AX1:BG1
          {
          csColEnd.SetAt(nColChars-2, csColStart[nColChars-2] + 1);
          csColEnd.SetAt(nColChars-1, 'A' + ('Z'-csColStart[nColChars-1]) + g_nFields-1);
          }
        csCol = csColStart;
        csRow = csRowStart;
        }
      }
    else // no starting cell specified
      {
      csCol = 'A';
      csRow = '1';
      }

    if (bRet) // all right so far, push the data to Excel
      {
      // with Excel ready to receive data, move data into array of variants
      TCHAR *pC = csData.GetBuffer(nLength);
      for (long i = 0; i < nLines; i++) // Load each line into the array
        {
        for (long j = 0; j < g_nFields;j++) // move each field into a variant
          {
          _variant_t vVar(pC); // point to NUL-terminated string
          csRange.Format("%s%s", GetColStr(csCol, j), GetRowStr(csRow, i));
          Excel::RangePtr pRange = pSheet->Range[(LPCTSTR)csRange];
          pRange->Value = &vVar;
          pC = &pC[_tcslen(pC)];
          while (!*pC)
            pC++; // skip up to next field
          }
        }
      pXL->Visible = VARIANT_TRUE;
      pSheet->Visible = Excel::xlSheetVisible;
      }
    }
  catch (_com_error &e) // here if there was an OLE exception
    {
    dump_com_error(e); // display the error
    bRet = FALSE;      // signal problem
    }
  return bRet;
}
