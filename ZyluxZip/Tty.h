/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// Definition of the CTTYInfo class
/////////////////////////////////////////////////////////////////////////////
/*
* $History: Tty.h $ * 
// 
// *****************  Version 3  *****************
// User: Maynard      Date: 9/26/00    Time: 9:11a
// Updated in $/ZyluxZip
// Remove data "push" thread and procedure from Capture program
// Check to see if there is room before copying sent data into the display
// buffer
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:21p
 * Updated in $/ZyluxZip
 * Remove local echo and show error flags, moved to showinfo structure to
 * pass local and show error flags to data window
 * Remove reference list and function, don't need to track references
 * since this is a single global object
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 11:44a
 * Created in $/ZyluxZip
*/

// constant definitions

// hard coded maximum number of ports for device under Win32
#ifndef TTYINFO_DEFINED
#define TTYINFO_DEFINED

#define MAXPORTS        4

// terminal size

#define MAXROWS         800
#define MAXCOLS         80

// Flow control flags
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// Xon/Xoff definitions
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define WM_SHOWTTY (WM_APP + 1)

// data structures
typedef struct SHOWTTYINFO 
{
  class CTTYInfo *pTTYInfo;
  LPCSTR pData;
  int nLength;
  bool bLocal;
  bool bError;
} SHOWTTYINFO;

class CTTYInfo
{
public:
  CTTYInfo();
  ~CTTYInfo();

  int ReadCommBlock(int);
  BOOL WriteCommBlock(LPCTSTR, DWORD);
  BOOL OpenConnection();
  BOOL SetupConnection();
  BOOL CloseConnection();

  SHOWTTYINFO m_ShowTTYInfo;
  bool m_bReadingData;

  HANDLE  idComDev; // Com port device handle
  volatile HANDLE m_hEventWait; // handle of event for timeout wait thread
  BYTE    bPort, *m_pabData;
  int m_cbInCount; // number of bytes received so far into abData
  int m_cbBufSize; // size of buffer allocated so far
  BOOL    fConnected, fUseCNReceive;
  BYTE    bByteSize, bFlowCtrl, bParity, bStopBits;
  DWORD   dwBaudRate, m_dwTimeout, m_dwTimeoutCount;
  HANDLE  hPostEvent, hWatchThread, hWatchEvent;
  HWND    m_hWndTerm; // used to send cross-thread message to data window
  volatile DWORD   m_dwThreadID;
  OVERLAPPED osWrite, osRead;

protected:
  // shows data in window if available
  void ShowTTYBlock(LPCSTR buf, int nLen, bool bLocal = false);
  void ShowTTYError(LPCTSTR pszError);
};

DWORD FAR PASCAL CommWatchProc(CTTYInfo *);

#endif TTYINFO_DEFINED

//---------------------------------------------------------------------------
//  End of File: tty.h
//---------------------------------------------------------------------------
