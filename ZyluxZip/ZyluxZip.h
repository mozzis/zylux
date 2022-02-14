// ZyluxZip.h : main header file for the ZYLUXZIP application
// CZyluxZipApp is a program to manage data for the Zylux FB14
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: ZyluxZip.h $ * 
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:58p
 * Updated in $/ZyluxZip
 * Move Set/GetInt/StringSetting to app module so they can be reused
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:21p
 * Updated in $/ZyluxZip
 * Add ATL support to make using the notify interface easier
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/15/00    Time: 2:01p
 * Updated in $/ZyluxZip
 * Add public method to access recent file list
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZYLUXZIP_H__01E5EB2A_8248_43AB_B69F_DE21F8916082__INCLUDED_)
#define AFX_ZYLUXZIP_H__01E5EB2A_8248_43AB_B69F_DE21F8916082__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxadv.h> // recent file list support
#include "ZyluxZip_i.h"

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipApp:
// See ZyluxZip.cpp for the implementation of this class
//

class CZyluxZipApp : public CWinApp
{
public:
	CZyluxZipApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxZipApp)
	public:
	virtual BOOL InitInstance();
  CRecentFileList *GetRecentFileList() { return m_pRecentFileList; }
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

  // Helpers for reading and writing registry settings
  int GetIntSetting(UINT uIDSet, int nDefault);
  int SetIntSetting(UINT uIDSet, int nSetVal);
  CString GetStringSetting(UINT uIDSet, LPCTSTR sDefault = 0);
  int SetStringSetting(UINT uIDSet, LPCTSTR sSetVal);

// Implementation

	//{{AFX_MSG(CZyluxZipApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZYLUXZIP_H__01E5EB2A_8248_43AB_B69F_DE21F8916082__INCLUDED_)
