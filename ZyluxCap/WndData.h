// WndData.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: WndData.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:26a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/
#if !defined(AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_)
#define AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
#include "edtdata.h"

/////////////////////////////////////////////////////////////////////////////
// CWndData dialog

class CWndData : public CDialog
{
// Construction
public:
	CWndData(CWnd* pParent = NULL);   // standard constructor
  CWndData(CWnd *, CWndData **, class CTTYInfo *);
  void CommonConstruct();
// Dialog Data
  int m_nGapLeft;
  int m_nGapRight;
  int m_nGapTop;
  int m_nGapBottom;

	//{{AFX_DATA(CWndData)
	enum { IDD = IDD_DATAWIN };
	CEdtData	m_EdtData;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndData)
	public:
	virtual void OnSetFont(CFont* pFont);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
  ~CWndData();
  void SendTTYData(LPCTSTR pData, int nBytes);
  bool GetLocalEcho(void);
protected:
  CWndData **m_ppRef;
  class CTTYInfo *m_pTTYInfo;
  void ShowTTYBlock(class CTTYInfo *pInfo, LPCSTR lpBlock, int nLength);

	// Generated message map functions
	//{{AFX_MSG(CWndData)
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void HandleShowMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPush();
	afx_msg void OnLoadfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_)
