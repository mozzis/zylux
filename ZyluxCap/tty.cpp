/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// Implementation of the CTTYInfo class
// Also contains the COM port watch thread and processing
/////////////////////////////////////////////////////////////////////////////
/*
* $History: tty.cpp $ * 
// 
// *****************  Version 16  *****************
// User: Maynard      Date: 11/14/00   Time: 11:39a
// Updated in $/ZyluxCap/2.0
// Should use m_bAutomated flag to deterimine whether to save only the
// serial port settings; others saved always
// 
// *****************  Version 15  *****************
// User: Maynard      Date: 9/25/00    Time: 2:26p
// Updated in $/ZyluxCap/2.0
// Eliminate an unused string in OpenConnection
// 
// *****************  Version 14  *****************
// User: Maynard      Date: 7/22/00    Time: 2:08p
// Updated in $/ZyluxCap/2.0
// 
// *****************  Version 13  *****************
// User: Maynard      Date: 7/22/00    Time: 2:07p
// Updated in $/ZyluxCap/2.0
// 
// *****************  Version 12  *****************
// User: Maynard      Date: 7/21/00    Time: 5:58p
// Updated in $/ZyluxCap/2.0
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 6/08/00    Time: 7:14a
// Updated in $/ZyluxCap/2.0
// Move CloseConnection in destructor to be after the reference list is
// released; CloseConnection kills off the threads which may be holding
// the reference pointers.
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 5/26/00    Time: 2:33a
// Updated in $/ZyluxCap/2.0
// Add a ReleaseReference to correspond to the existing AddReference, and
// make sure that the PushTimeoutProcedure calls it before exiting; else
// the destructor tried to write to unallocated memory/stack
// 
// *****************  Version 9  *****************
// User: Maynard      Date: 5/15/00    Time: 11:09a
// Updated in $/ZyluxCap/2.0
// Use m_bAutomated flag to tell whether to save settings in destructor
// Don't use OR operator when getting flow control settings
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 5/03/00    Time: 10:42p
 * Updated in $/ZyluxCap/2.0
 * Add a comment
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 4/14/00    Time: 4:26p
 * Updated in $/ZyluxCap/2.0
 * Check pointer before use in destructor
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 4/14/00    Time: 10:01a
 * Updated in $/ZyluxCap/2.0
 * Post custom quit message instead of WM_QUIT in PushTimeoutProcedure;
 * WM_QUIT was never seen by the CWinApp derived class, so main window was
 * not closed properly
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:11a
 * Updated in $/ZyluxCap/1.2
 * Make ascii data buffer dynamically allocated
 * Re-alloc buffer if more data than initial size received
 * Send message to parent thread to change status message when reading or
 * pushing data
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:25a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
 * Save/Restore file, sheet and range specifier data
*/

#include "stdafx.h"
#include <afxpriv.h>
#include <memory>
#include "tty.h"
#include "resource.h"
#include "pushdata.h"
#include "messages.h"

// helpers for reading/writing settings

static int GetIntSetting(CWinApp *pApp, UINT uIDSet, int nDefault)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return pApp->GetProfileInt(csSect, csEnt, nDefault);
}

static int SetIntSetting(CWinApp *pApp, UINT uIDSet, int nSetVal)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return pApp->WriteProfileInt(csSect, csEnt, nSetVal);
}

static CString GetStringSetting(CWinApp *pApp, UINT uIDSet, LPCTSTR sDefault = 0)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return pApp->GetProfileString(csSect, csEnt, sDefault);
}

static int SetStringSetting(CWinApp *pApp, UINT uIDSet, LPCTSTR sSetVal)
{
  CString csSect, csEnt;
  csSect.LoadString(IDS_SETTINGS);
  csEnt.LoadString(uIDSet);
  return pApp->WriteProfileString(csSect, csEnt, sSetVal);
}

//////////////////////////////////////////////////////////////////////////
CTTYInfo::CTTYInfo()
{
  // initialize TTY info structure
  fConnected = FALSE;
  m_bAutomated = false;
  // get settings from registry/ini file
  CWinApp *pApp = AfxGetApp();
  idComDev   = 0;
  fLocalEcho = GetIntSetting(pApp, IDS_LOCALECHO, FALSE);
  fAutoWrap  = GetIntSetting(pApp, IDS_AUTOWRAP, TRUE);
  bPort      = GetIntSetting(pApp, IDS_PORTNO, 1);
  dwBaudRate = GetIntSetting(pApp, IDS_BAUDRATE, CBR_9600);
  bByteSize  = GetIntSetting(pApp, IDS_BYTESIZE, 8);
  bFlowCtrl  = GetIntSetting(pApp, IDS_FLOWCTRL, FC_XONXOFF);
  bParity    = GetIntSetting(pApp, IDS_PARITY, NOPARITY);
  bStopBits =  GetIntSetting(pApp, IDS_STOPBIT, ONESTOPBIT);
  // Program Options
  fDisplayErrors = GetIntSetting(pApp, IDS_DISPERRS, TRUE);
  m_dwTimeout = GetIntSetting(pApp, IDS_TIMEOUT, 3000);
  m_dwTimeoutCount = 0;
  m_bAutoConnect = GetIntSetting(pApp, IDS_AUTOCONNECT, TRUE);
  m_bAutoQuit = GetIntSetting(pApp, IDS_AUTOQUIT, TRUE);

  m_bSpecFile =  GetIntSetting(pApp, IDS_SPECFILE,  FALSE);
  m_bSpecSheet = GetIntSetting(pApp, IDS_SPECSHEET, FALSE);
  m_bSpecRange = GetIntSetting(pApp, IDS_SPECRANGE, FALSE);
  m_bRepFile   = GetIntSetting(pApp, IDS_REPFILE, FALSE);

  m_sFile  = GetStringSetting(pApp, IDS_NAMEFILE);
  m_sSheet = GetStringSetting(pApp, IDS_NAMESHEET);
  m_sRangeRow = GetStringSetting(pApp, IDS_NAMERANGEROW);
  m_sRangeCol = GetStringSetting(pApp, IDS_NAMERANGECOL);

  m_RefList.RemoveAll();

  hTTYFont = NULL;
  rgbFGColor = RGB(0, 0, 0);

  osWrite.Offset = 0;
  osWrite.OffsetHigh = 0;
  osRead.Offset = 0;
  osRead.OffsetHigh = 0;

  // create I/O event used for overlapped reads / writes
  osRead.hEvent = CreateEvent(NULL,   // no security
                              TRUE,   // explicit reset req
                              FALSE,  // initial event reset
                              NULL);  // no name
  if (osRead.hEvent == NULL)
    {
    throw;
    }
  osWrite.hEvent = CreateEvent(NULL,  // no security
                               TRUE,  // explicit reset req
                               FALSE, // initial event reset
                               NULL); // no name
  if (NULL == osWrite.hEvent)
    {
    CloseHandle(osRead.hEvent);
    throw;
    }

  // setup default font information
  lfTTYFont.lfHeight =         -9;
  lfTTYFont.lfWidth =          10;
  lfTTYFont.lfEscapement =     0;
  lfTTYFont.lfOrientation =    0;
  lfTTYFont.lfWeight =         FW_NORMAL;
  lfTTYFont.lfItalic =         0;
  lfTTYFont.lfUnderline =      0;
  lfTTYFont.lfStrikeOut =      0;
  lfTTYFont.lfCharSet =        ANSI_CHARSET;
  lfTTYFont.lfOutPrecision =   OUT_DEFAULT_PRECIS;
  lfTTYFont.lfClipPrecision =  CLIP_DEFAULT_PRECIS;
  lfTTYFont.lfQuality =        DEFAULT_QUALITY;
  lfTTYFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
  _tcscpy(lfTTYFont.lfFaceName, _T("FixedSys"));
  hTTYFont = CreateFontIndirect(&lfTTYFont);
  m_cbBufSize = MAXCOLS * MAXROWS;
  m_pabData = (BYTE *)malloc(m_cbBufSize);
  m_bReadingData = m_bPushingData = false;

}

void CTTYInfo::ReleaseReference(class CTTYInfo **pInfo)
{
  POSITION pos = m_RefList.Find(pInfo);
  if (pos)
    {
    m_RefList.RemoveAt(pos);
    }
}

//////////////////////////////////////////////////////////////////////////
CTTYInfo::~CTTYInfo()
{
  if (m_RefList.GetCount())
    {
    while (m_RefList.GetHeadPosition())
      {
      CTTYInfo **ppInfo = m_RefList.RemoveTail();
      if (ppInfo)
        *ppInfo = 0;
      }
    }


  if (fConnected)
    CloseConnection();

  // clean up event objects
  CloseHandle(osRead.hEvent);
  CloseHandle(osWrite.hEvent);

  DeleteObject(hTTYFont);
  CWinApp *pApp = AfxGetApp();
  if (!m_bAutomated)
    {
    // save settings to registry/ini file
    SetIntSetting(pApp, IDS_LOCALECHO, fLocalEcho);
    SetIntSetting(pApp, IDS_AUTOWRAP,  fAutoWrap);
    SetIntSetting(pApp, IDS_PORTNO,    bPort);
    SetIntSetting(pApp, IDS_BAUDRATE,  dwBaudRate);
    SetIntSetting(pApp, IDS_BYTESIZE,  bByteSize);
    SetIntSetting(pApp, IDS_FLOWCTRL,  bFlowCtrl);
    SetIntSetting(pApp, IDS_PARITY,    bParity);
    SetIntSetting(pApp, IDS_STOPBIT,   bStopBits);
    SetIntSetting(pApp, IDS_DISPERRS,  fDisplayErrors);
    }
  // these aren't really serial port settings, and so they 
  // should be saved by some other object.
  SetIntSetting(pApp, IDS_TIMEOUT,   m_dwTimeout);
  SetIntSetting(pApp, IDS_AUTOCONNECT, m_bAutoConnect);
  SetIntSetting(pApp, IDS_AUTOQUIT,    m_bAutoQuit);
  SetIntSetting(pApp, IDS_SPECFILE,  m_bSpecFile);
  SetIntSetting(pApp, IDS_SPECSHEET, m_bSpecSheet);
  SetIntSetting(pApp, IDS_SPECRANGE, m_bSpecRange);
  SetIntSetting(pApp, IDS_REPFILE, m_bRepFile);
  SetStringSetting(pApp, IDS_NAMEFILE,  m_sFile);
  SetStringSetting(pApp, IDS_NAMESHEET, m_sSheet);
  SetStringSetting(pApp, IDS_NAMERANGEROW, m_sRangeRow);
  SetStringSetting(pApp, IDS_NAMERANGECOL, m_sRangeCol);

  free(m_pabData);
}

//---------------------------------------------------------------------------
//  BOOL NEAR OpenConnection()
//
//  Description:
//     Opens communication port specified in the CTTYInfo struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the CTTYInfo struct.
//
//  Parameters: none
//
//  Win-32 Porting Issues:
//     - OpenComm() is not supported under Win-32.  Use CreateFile()
//       and setup for OVERLAPPED_IO.
//     - Win-32 has specific communication timeout parameters.
//     - Created the secondary thread for event notification.
//
//---------------------------------------------------------------------------
BOOL NEAR CTTYInfo::OpenConnection()
{
  TCHAR szPort[15];
  BOOL    fRetVal;

  HANDLE       hCommWatchThread;
  DWORD        dwThreadID;
  COMMTIMEOUTS CommTimeOuts;

  // show the hourglass cursor
  HCURSOR hWaitCursor = LoadCursor(NULL, IDC_WAIT),
          hOldCursor = SetCursor(hWaitCursor);

  // load the COM prefix string and append port number
  wsprintf(szPort, "%s%d", "COM", bPort);

  // open COMM device
  if ((idComDev =
     CreateFile(szPort, GENERIC_READ | GENERIC_WRITE,
                 0,                    // exclusive access
                 NULL,                 // no security attrs
                 OPEN_EXISTING,
                 FILE_ATTRIBUTE_NORMAL |
                 FILE_FLAG_OVERLAPPED, // overlapped I/O
                 NULL)) == (HANDLE) -1)
     return (FALSE);
  else
    {
    // get any early notifications
    SetCommMask(idComDev, EV_RXCHAR);

    // setup device buffers
    SetupComm(idComDev, 4096, 4096);

    // purge any information in the buffer
    PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    // set up for overlapped I/O
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = 1000;
    // CBR_9600 is approximately 1byte/ms. For our purposes, allow
    // double the expected time per character for a fudge factor.
    CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/dwBaudRate;
    CommTimeOuts.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(idComDev, &CommTimeOuts);
    }

  fRetVal = SetupConnection();

  if (fRetVal)
    {
    fConnected = TRUE;
    // clear input buffer
    memset(m_pabData, 0, m_cbBufSize);
    m_cbInCount = 0;

    // Create a secondary thread to watch for an event.
    if (NULL == (hCommWatchThread =
                    CreateThread((LPSECURITY_ATTRIBUTES) NULL,
                                  0,
                                  (LPTHREAD_START_ROUTINE) CommWatchProc,
                                  (LPVOID) this,
                                  0, &dwThreadID)))
      {
      fConnected = FALSE;
      CloseHandle(idComDev);
      fRetVal = FALSE;
      }
    else
      {
      m_dwThreadID = dwThreadID;
      hWatchThread = hCommWatchThread;

      // assert DTR
      EscapeCommFunction(idComDev, SETDTR);
      }
    CWinThread *pTh = 
      AfxBeginThread((AFX_THREADPROC)PushTimeoutProc, this, 
                     THREAD_PRIORITY_NORMAL, 0 , CREATE_SUSPENDED);
    pTh->m_bAutoDelete = TRUE;
    pTh->ResumeThread();
    }
  else
    {
    fConnected = FALSE;
    CloseHandle(idComDev);
    }

  // restore cursor
  SetCursor(hOldCursor);
  return (fRetVal);
} // end of OpenConnection()

//////////////////////////////////////////////////////////////////////////
BOOL NEAR CTTYInfo::CloseConnection()
{
   // set connected flag to FALSE
   fConnected = FALSE;

   // disable event notification and wait for thread to halt
   SetCommMask(idComDev, 0);
   SetEvent(m_hEventWait); // release timeout thread

   // block until thread has been halted
   while(m_dwThreadID != 0 && m_hEventWait != 0);

   // drop DTR
   EscapeCommFunction(idComDev, CLRDTR);

   // purge any outstanding reads/writes and close device handle
   PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT |
                                   PURGE_TXCLEAR | PURGE_RXCLEAR);
   CloseHandle(idComDev);
   return (TRUE);
} // end of CloseConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR SetupConnection()
//
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//
//  Parameters:
//
//  Win-32 Porting Issues:
//     - Win-32 requires a slightly different processing of the DCB.
//       Changes were made for configuration of the hardware handshaking
//       lines.
//
//---------------------------------------------------------------------------
BOOL CTTYInfo::SetupConnection()
{
  BOOL       fRetVal;
  BYTE       bSet;
  DCB        dcb;
  dcb.DCBlength = sizeof(DCB);

  GetCommState(idComDev, &dcb);

  dcb.BaudRate = dwBaudRate;
  dcb.ByteSize = bByteSize;
  dcb.Parity = bParity;
  dcb.StopBits = bParity;
  // setup hardware flow control
  bSet = (BYTE) ((bFlowCtrl & FC_DTRDSR) != 0);
  dcb.fOutxDsrFlow = bSet;
  if (bSet)
     dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
  else
     dcb.fDtrControl = DTR_CONTROL_ENABLE;

  bSet = (BYTE) ((bFlowCtrl & FC_RTSCTS) != 0);
  dcb.fOutxCtsFlow = bSet;
  if (bSet)
     dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
  else
     dcb.fRtsControl = RTS_CONTROL_ENABLE;

  // setup software flow control
  bSet = (BYTE) ((bFlowCtrl & FC_XONXOFF) != 0);

  dcb.fInX = dcb.fOutX = bSet;
  dcb.XonChar = ASCII_XON;
  dcb.XoffChar = ASCII_XOFF;
  dcb.XonLim = 100;
  dcb.XoffLim = 100;

  // other various settings
  dcb.fBinary = TRUE;
  dcb.fParity = TRUE;

  fRetVal = SetCommState(idComDev, &dcb);

  return (fRetVal);
} // end of SetupConnection()


void CTTYInfo::ShowTTYBlock(LPCSTR buf, int nLen)
{
  if (!hWndTerm) return;
  m_ShowTTYInfo.nLength = nLen;
  m_ShowTTYInfo.pData = buf;
  m_ShowTTYInfo.pTTYInfo = this;
  SendMessage(this->hWndTerm, WM_SHOWTTY, 0, (LPARAM)&m_ShowTTYInfo);
}

//---------------------------------------------------------------------------
//  int ReadCommBlock(LPSTR lpszBlock, int nMaxLength)
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided buffer.
//
//  Parameters:
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------
int CTTYInfo::ReadCommBlock(int nMaxLength)
{
  COMSTAT ComStat;
  DWORD   dwErrorFlags;
  // only try to read number of bytes in queue
  ClearCommError(idComDev, &dwErrorFlags, &ComStat);
  DWORD dwLength = min((DWORD) nMaxLength, ComStat.cbInQue);

  if (m_cbBufSize < m_cbInCount + dwLength)
    {
    m_pabData = (BYTE *)realloc(m_pabData, m_cbInCount + dwLength);
    memset(&m_pabData[m_cbInCount], 0, (m_cbInCount + dwLength) - m_cbBufSize);
    m_cbBufSize = m_cbInCount + dwLength;
    }
  BYTE *lpszBlock = &m_pabData[m_cbInCount]; 
  if (dwLength > 0)
    {
    DWORD dwError;
    TCHAR szError[10];
    BOOL  fReadStat = ReadFile(idComDev, lpszBlock,
		                   dwLength, &dwLength, &osRead);
    SetEvent(m_hEventWait); // release timeout thread
    if (!fReadStat)
      {
      if (GetLastError() == ERROR_IO_PENDING)
        {
        OutputDebugString("\n\rIO Pending");
        // We have to wait for read to complete.
        // This function will timeout according to the
        // CommTimeOuts.ReadTotalTimeoutConstant variable
        // Every time it times out, check for port errors
        while(!GetOverlappedResult(idComDev,
           &osRead, &dwLength, TRUE))
          {
          dwError = GetLastError();
          if(dwError == ERROR_IO_INCOMPLETE)
            // normal result if not finished
            continue;
          else
            {
            // an error occurred, try to recover
            wsprintf(szError, "<CE-%u>", dwError);
            ShowTTYBlock(szError, lstrlen(szError));
            ClearCommError(idComDev, &dwErrorFlags, &ComStat);
            if ((dwErrorFlags > 0) && fDisplayErrors)
              {
	            wsprintf(szError, "<CE-%u>", dwErrorFlags);
	            ShowTTYBlock(szError, lstrlen(szError));
              }
            break;
            }
          }
        }
      else
        {
        // some other error occurred
        dwLength = 0;
        ClearCommError(idComDev, &dwErrorFlags, &ComStat);
        if ((dwErrorFlags > 0) && fDisplayErrors)
          {
	        wsprintf(szError, "<CE-%u>", dwErrorFlags);
	        ShowTTYBlock(szError, lstrlen(szError));
          }
        }
      }
    }
  if (dwLength)
    {
    ShowTTYBlock((LPCTSTR)lpszBlock, dwLength);
    m_cbInCount += dwLength;
    }

  return (dwLength);
} // end of ReadCommBlock()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteCommBlock(HWND hWnd, BYTE *pByte)
//
//  Description:
//     Writes a block of data to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE *pByte
//        pointer to data to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------
BOOL NEAR CTTYInfo::WriteCommBlock(LPCTSTR lpByte, DWORD dwBytesToWrite)
{
  BOOL    fWriteStat;
  DWORD   dwBytesWritten;
  DWORD   dwErrorFlags;
  DWORD   dwError;
  DWORD   dwBytesSent=0;
  COMSTAT ComStat;
  char    szError[ 128 ];

  fWriteStat = WriteFile(idComDev, lpByte, dwBytesToWrite,
                          &dwBytesWritten, &osWrite);
  SetEvent(m_hEventWait); // release timeout thread

  // Note that normally the code will not execute the following
  // because the driver caches write operations. Small I/O requests
  // (up to several thousand bytes) will normally be accepted
  // immediately and WriteFile will return true even though an
  // overlapped operation was specified

  if (!fWriteStat)
    {
    if(GetLastError() == ERROR_IO_PENDING)
      {
      // We should wait for the completion of the write operation
      // so we know if it worked or not

      // This is only one way to do this. It might be beneficial to
      // place the write operation in a separate thread
      // so that blocking on completion will not negatively
      // affect the responsiveness of the UI

      // If the write takes too long to complete, this
      // function will timeout according to the
      // CommTimeOuts.WriteTotalTimeoutMultiplier variable.
      // This code logs the timeout but does not retry
      // the write.
      while(!GetOverlappedResult(idComDev, &osWrite, &dwBytesWritten, TRUE))
        {
        dwError = GetLastError();
        if(dwError == ERROR_IO_INCOMPLETE)
          {
          // normal result if not finished
          dwBytesSent += dwBytesWritten;
          continue;
          }
        else
          {
           // an error occurred, try to recover
           wsprintf(szError, "<CE-%u>", dwError);
           ShowTTYBlock(szError, lstrlen(szError));
           ClearCommError(idComDev, &dwErrorFlags, &ComStat);
           if ((dwErrorFlags > 0) && fDisplayErrors)
             {
             wsprintf(szError, "<CE-%u>", dwErrorFlags);
             ShowTTYBlock(szError, lstrlen(szError));
             }
          break;
          }
        }
      dwBytesSent += dwBytesWritten;
#ifdef _DEBUG
      if(dwBytesSent != dwBytesToWrite)
        wsprintf(szError,"\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
      else
        wsprintf(szError,"%ld bytes written\n", dwBytesSent);
      OutputDebugString(szError);
#endif
      _tcsncpy((LPTSTR)&m_pabData[m_cbInCount], lpByte, dwBytesSent);
      m_cbInCount += dwBytesSent;
      }
    else
      {
      // some other error occurred
      ClearCommError(idComDev, &dwErrorFlags, &ComStat);
      if ((dwErrorFlags > 0) && fDisplayErrors)
        {
        wsprintf(szError, "<CE-%u>", dwErrorFlags);
        ShowTTYBlock(szError, lstrlen(szError));
        }
      return (FALSE);
      }
    }
  return (TRUE);
} // end of WriteCommBlock()

//************************************************************************
//  DWORD FAR PASCAL CommWatchProc(CTTYInfo *pInfo)
//
//  Description:
//     A secondary thread that will watch for COMM events.
//
//  Parameters:
//     LPSTR lpData
//        32-bit pointer argument
//
//  Win-32 Porting Issues:
//     - Added this thread to watch the communications device and
//       post notifications to the associated window.
//
//************************************************************************
DWORD FAR PASCAL CommWatchProc(CTTYInfo *pInfo)
{
  DWORD dwEvtMask;
  OVERLAPPED  os;
	int nLength;

  memset(&os, 0, sizeof(OVERLAPPED));
  // create I/O event used for overlapped read
  os.hEvent = CreateEvent(NULL,    // no security
                          TRUE,    // explicit reset req
                          FALSE,   // initial event reset
                          NULL);   // no name
  if (os.hEvent == NULL)
    {
    MessageBox(NULL, "Failed to create event for thread!", "TTY Error!",
               MB_ICONEXCLAMATION | MB_OK);
    return (FALSE);
    }

  if (!SetCommMask(pInfo->idComDev, EV_RXCHAR))
    return (FALSE);

  while (pInfo->fConnected)
    {
    dwEvtMask = 0;
    WaitCommEvent(pInfo->idComDev, &dwEvtMask, NULL);
    if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
      pInfo->m_bReadingData = true;
      AfxGetApp()->PostThreadMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
      do
        nLength = pInfo->ReadCommBlock(MAXCOLS);
      while (nLength > 0);
      pInfo->m_bReadingData = false;
      pInfo->m_bPushingData = true; // an assumption
      AfxGetApp()->PostThreadMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
      }
    }

  CloseHandle(os.hEvent); // get rid of event handle

  // clear information in structure (kind of a "we're done flag")
  pInfo->m_dwThreadID = 0;
  pInfo->hWatchThread = NULL;
  return(TRUE);
} // end of CommWatchProc()


//************************************************************************
//  DWORD FAR PASCAL PushTimeoutProc(CTTYInfo *pInfo)
//
//  Description:
//     A secondary thread that will push data to Excel.
//
//************************************************************************
DWORD FAR PASCAL PushTimeoutProc(CTTYInfo *pInfo)
{
  pInfo->m_hEventWait = 
    CreateEvent(0,
    FALSE, // flag for manual-reset event
    FALSE, // flag for initial state
    0);    // pointer to event-object name
  DWORD dwResult;
  CTTYInfo *localpInfo = pInfo;
  pInfo->AddReference(&localpInfo);
  CoInitialize(NULL);
  do
    {
    // if auto-timeout not set, wait for at least three seconds
    DWORD dwTimeout = pInfo->m_dwTimeout ? pInfo->m_dwTimeout : 3000;
    pInfo->m_dwTimeoutCount = dwTimeout;
    dwResult = WaitForSingleObject(pInfo->m_hEventWait, dwTimeout);
    if (!pInfo || !pInfo->m_hEventWait)
      break; // quit do loop if event closed (program end)
    // pInfo still alive from here on in do/while
    switch(dwResult)
      {
      case WAIT_OBJECT_0: // char received before timeout
      break;
      case WAIT_TIMEOUT: // no more data expected, do push
        if (pInfo && pInfo->m_dwTimeout)
          {
          if (pInfo->m_cbInCount > 8) // arbitrary minimum
            {
            pInfo->m_bPushingData = true;
            // change status bar message
            AfxGetApp()->PostThreadMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
            if (StuffTTYData((LPCTSTR)pInfo->m_pabData, pInfo->m_cbInCount, pInfo) &&
                pInfo->m_bAutoQuit)
              AfxGetApp()->PostThreadMessage(WM_APPQUIT, 0, 0);
            pInfo->m_bPushingData = false;
            AfxGetApp()->PostThreadMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
            }
          pInfo->m_cbInCount = 0; // "clear" buffer of "noise"
          }
      break;
      case WAIT_ABANDONED: // time to end app
      break;
      }
    }
  while (pInfo->fConnected && dwResult == WAIT_OBJECT_0 || dwResult == WAIT_TIMEOUT);
  if (localpInfo && pInfo && pInfo->m_hEventWait)
    {
    CloseHandle(pInfo->m_hEventWait);
    pInfo->m_hEventWait = 0; // signal thread done
    }
  CoUninitialize();
  pInfo->ReleaseReference(&localpInfo);
  return 0;
}