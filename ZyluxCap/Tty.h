/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
// Definition of the CTTYInfo class
/////////////////////////////////////////////////////////////////////////////
/*
* $History: Tty.h $ * 
// 
// *****************  Version 8  *****************
// User: Maynard      Date: 5/26/00    Time: 2:33a
// Updated in $/ZyluxCap/2.0
// Add a ReleaseReference to correspond to the existing AddReference, and
// make sure that the PushTimeoutProcedure calls it before exiting; else
// the destructor tried to write to unallocated memory/stack
// 
// *****************  Version 7  *****************
// User: Maynard      Date: 5/15/00    Time: 11:09a
// Updated in $/ZyluxCap/2.0
// Add m_bAutomated flag
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 12/08/99   Time: 12:09a
 * Updated in $/ZyluxCap/1.2
 * Make ascii data buffer dynamically allocated
 * Change initial size from 255X80 to 800X80
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 6/29/99    Time: 6:57p
 * Updated in $/ZyluxCap/1.1
 * Increase MAXROWS constant to 255 from 25 so buffer is larger
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:25a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
 * Save/Restore file, sheet and range specifier data
*/

// constant definitions

// hard coded maximum number of ports for device under Win32
#ifndef TTYINFO_DEFINED
#define TTYINFO_DEFINED

#include <afxtempl.h>

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
  void AddReference(class CTTYInfo **pInfo) { m_RefList.AddTail(pInfo); }
  void ReleaseReference(class CTTYInfo **pInfo);

  SHOWTTYINFO m_ShowTTYInfo;
  bool m_bReadingData, m_bPushingData;
  bool m_bAutomated; // flag if program is being controlled

  HANDLE  idComDev; // Com port device handle
  volatile HANDLE m_hEventWait; // handle of event for timeout wait thread
  BYTE    bPort, *m_pabData;
  int m_cbInCount; // number of bytes received so far into abData
  int m_cbBufSize; // size of buffer allocated so far
  BOOL    fConnected, fLocalEcho, fNewLine, fAutoWrap,
          fUseCNReceive, fDisplayErrors;
  BYTE    bByteSize, bFlowCtrl, bParity, bStopBits;
  DWORD   dwBaudRate;
  HFONT   hTTYFont;
  LOGFONT lfTTYFont;
  DWORD   rgbFGColor;
  HANDLE  hPostEvent, hWatchThread, hWatchEvent;
  HWND    hWndTerm; // used to send cross-thread message to data window
  volatile DWORD   m_dwThreadID;
  OVERLAPPED osWrite, osRead;

  // Program Options
  BOOL m_bAutoConnect; // if true, connect to serial port on startup
  BOOL m_bAutoQuit;    // if true, quit program after successful push
  DWORD m_dwTimeout;   // milliseconds to wait for data after last byte
                       // received before initiating "push"
  DWORD m_dwTimeoutCount; // counter of timeout period left
   
  CString m_sFile;     // name of file for specific file output
  CString m_sSheet;    // name of sheet for specific sheet output
  CString m_sRangeCol; // name of start column for specified range
  CString m_sRangeRow; // name of end column for specified range

  BOOL m_bSpecFile;  // if true, output to specified file
  BOOL m_bSpecSheet; // if true, output to specified sheet
  BOOL m_bSpecRange; // if true, output to specified range
  BOOL m_bRepFile;   // replace output file if it exists

  void ShowTTYBlock(LPCSTR buf, int nLen); // shows data in window if available
protected:
  CTypedPtrList<CPtrList, class CTTYInfo **> m_RefList;
};

DWORD FAR PASCAL CommWatchProc(CTTYInfo *);
DWORD FAR PASCAL PushTimeoutProc(CTTYInfo *);

#endif TTYINFO_DEFINED

//---------------------------------------------------------------------------
//  End of File: tty.h
//---------------------------------------------------------------------------
