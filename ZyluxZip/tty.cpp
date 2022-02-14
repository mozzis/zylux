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
// *****************  Version 5  *****************
// User: Maynard      Date: 11/09/00   Time: 4:53p
// Updated in $/ZyluxZip
// Chage default baud rate to 4800 as per Zylux request since no
// handshaking
// 
// *****************  Version 4  *****************
// User: Maynard      Date: 9/26/00    Time: 9:11a
// Updated in $/ZyluxZip
// Remove data "push" thread and procedure from Capture program
// Check to see if there is room before copying sent data into the display
// buffer
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:17p
 * Updated in $/ZyluxZip
 * Remove local echo and show error flags, let data window decide what to
 * display
 * Add ShowTTYError function to pass flags to data window
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:58p
 * Updated in $/ZyluxZip
 * Move Set/GetInt/StringSetting to app module so they can be reused
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 11:44a
 * Created in $/ZyluxZip
*/

#include "stdafx.h"
#include <afxpriv.h>
#include <memory>
#include "zyluxzip.h"
#include "tty.h"
#include "resource.h"

// helpers for reading/writing settings

//////////////////////////////////////////////////////////////////////////
CTTYInfo::CTTYInfo()
{
  // initialize TTY info structure
  fConnected = FALSE;
  // get settings from registry/ini file
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  idComDev = 0;
  bPort      = pApp->GetIntSetting(IDS_PORTNO, 1);
  dwBaudRate = pApp->GetIntSetting(IDS_BAUDRATE, CBR_4800);
  bByteSize  = pApp->GetIntSetting(IDS_BYTESIZE, 8);
  bFlowCtrl  = pApp->GetIntSetting(IDS_FLOWCTRL, FC_XONXOFF);
  bParity    = pApp->GetIntSetting(IDS_PARITY, NOPARITY);
  bStopBits  = pApp->GetIntSetting(IDS_STOPBIT, ONESTOPBIT);

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

  m_cbBufSize = MAXCOLS * MAXROWS;
  m_pabData = (BYTE *)malloc(m_cbBufSize);
  m_bReadingData = false;
  m_hWndTerm = 0;
}

//////////////////////////////////////////////////////////////////////////
CTTYInfo::~CTTYInfo()
{
  if (fConnected)
    CloseConnection();

  // clean up event objects
  CloseHandle(osRead.hEvent);
  CloseHandle(osWrite.hEvent);

  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  // save settings to registry/ini file
  pApp->SetIntSetting(IDS_PORTNO,    bPort);
  pApp->SetIntSetting(IDS_BAUDRATE,  dwBaudRate);
  pApp->SetIntSetting(IDS_BYTESIZE,  bByteSize);
  pApp->SetIntSetting(IDS_FLOWCTRL,  bFlowCtrl);
  pApp->SetIntSetting(IDS_PARITY,    bParity);
  pApp->SetIntSetting(IDS_STOPBIT,   bStopBits);
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
  wsprintf(szPort, "%s%d", _T("COM"), bPort);

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

   // block until thread has been halted
   while(m_dwThreadID != 0)
     continue;

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


void CTTYInfo::ShowTTYBlock(LPCSTR buf, int nLen, bool bLocal /* = FALSE */)
{
  if (!m_hWndTerm) return;
  m_ShowTTYInfo.nLength = nLen;
  m_ShowTTYInfo.pData = buf;
  m_ShowTTYInfo.pTTYInfo = this;
  m_ShowTTYInfo.bLocal = bLocal;
  m_ShowTTYInfo.bError = false;
  SendMessage(m_hWndTerm, WM_SHOWTTY, 0, (LPARAM)&m_ShowTTYInfo);
}

void CTTYInfo::ShowTTYError(LPCTSTR pszError)
{
  if (!m_hWndTerm) return;
  m_ShowTTYInfo.nLength = lstrlen(pszError);
  m_ShowTTYInfo.pData = pszError;
  m_ShowTTYInfo.pTTYInfo = this;
  m_ShowTTYInfo.bLocal = false;
  m_ShowTTYInfo.bError = true;
  SendMessage(m_hWndTerm, WM_SHOWTTY, 0, (LPARAM)&m_ShowTTYInfo);
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
  DWORD dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);

  if (m_cbBufSize < m_cbInCount + (int)dwLength)
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
            ShowTTYError(szError);
            ClearCommError(idComDev, &dwErrorFlags, &ComStat);
            if (dwErrorFlags > 0)
              {
	            wsprintf(szError, "<CE-%u>", dwErrorFlags);
	            ShowTTYError(szError);
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
        if ((dwErrorFlags > 0))
          {
	        wsprintf(szError, "<CE-%u>", dwErrorFlags);
	        ShowTTYError(szError);
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
//
//     BYTE *pByte
//        pointer to data to write to port
//     DWORD dwBytesToWrite
//        32-bit number of bytes to send
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
           ShowTTYError(szError);
           ClearCommError(idComDev, &dwErrorFlags, &ComStat);
           if (dwErrorFlags > 0)
             {
             wsprintf(szError, "<CE-%u>", dwErrorFlags);
             ShowTTYError(szError);
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
      if (m_cbBufSize < m_cbInCount + (int)dwBytesSent)
        _tcsncpy((LPTSTR)&m_pabData[m_cbInCount], lpByte, dwBytesSent);
      m_cbInCount += dwBytesSent;
      }
    else
      {
      // some other error occurred
      ClearCommError(idComDev, &dwErrorFlags, &ComStat);
      if (dwErrorFlags > 0)
        {
        wsprintf(szError, "<CE-%u>", dwErrorFlags);
        ShowTTYError(szError);
        }
      return (FALSE);
      }
    ShowTTYBlock(lpByte, dwBytesSent, true);
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
      AfxGetApp()->PostThreadMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
      }
    }

  CloseHandle(os.hEvent); // get rid of event handle

  // clear information in structure (kind of a "we're done flag")
  pInfo->m_dwThreadID = 0;
  pInfo->hWatchThread = NULL;
  return(TRUE);
} // end of CommWatchProc()


