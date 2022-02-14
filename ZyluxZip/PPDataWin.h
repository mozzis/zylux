// PPDataWin.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPDataWin.h $ * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/27/00    Time: 2:55p
 * Updated in $/ZyluxZip
 * Set up data window to save/restore registry settings
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:41p
 * Updated in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 12:40p
 * Created in $/ZyluxZip
*/
#if !defined(AFX_PPDATAWIN_H__32161E62_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_PPDATAWIN_H__32161E62_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmproppage.h"
#include "wnddata.h"

/////////////////////////////////////////////////////////////////////////////
// CPPDataWin dialog

class CPPDataWin : public CMMPropPage, public WndDataInfo
{
	DECLARE_DYNCREATE(CPPDataWin)

// Construction
public:
	CPPDataWin(class CWndData *p = 0);
	~CPPDataWin();

  void SetInfo(WndDataInfo *pInfo);
  void GetInfo(WndDataInfo *pInfo);

// Dialog Data
	//{{AFX_DATA(CPPDataWin)
	enum { IDD = IDD_PP_DATAWIN };
		// NOTE - ClassWizard will add data members here.
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPDataWin)
	protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  class CWndData *m_pDataWnd;
	// Generated message map functions
	//{{AFX_MSG(CPPDataWin)
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPDATAWIN_H__32161E62_E84A_11D2_88A4_444553540000__INCLUDED_)
