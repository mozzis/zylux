// WndData.h : header file
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: WndData.h $ * 
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:23p
 * Updated in $/ZyluxZip
 * Add hex mode and font management
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/27/00    Time: 3:00p
 * Updated in $/ZyluxZip
 * Set up to read/write registry settings on create/destroy
 * Add SetInfo and GetInfo methods to communicate with Settings dialog
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:43p
 * Updated in $/ZyluxZip
*/
#if !defined(AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_)
#define AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
#include "edtdata.h"

typedef struct WndDataInfo
{
  WndDataInfo(); 
  void ReadRegistry();
  void WriteRegistry();

  HFONT m_hFont;
  LOGFONT m_lfFont;
  bool m_bLocalEcho;
  bool m_bDisplayErrors;
  bool m_bAutoWrap;
  bool m_bNewLine;
  bool m_bHexMode;
  COLORREF m_rgbFGColor;
} WndDataInfo;

/////////////////////////////////////////////////////////////////////////////
// CWndData dialog

class CWndData : public CDialog, public WndDataInfo
{
// Construction
public:
	CWndData(CWnd* pParent = NULL);   // standard constructor
  CWndData(CWnd *, CWndData **ppD =0, class CTTYInfo *pI =0);
  void CommonConstruct();

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
  SetInfo(const WndDataInfo *pInfo);
  GetInfo(WndDataInfo *pInfo) const;

protected:
// Dialog Data
  int m_nGapLeft;
  int m_nGapRight;
  int m_nGapTop;
  int m_nGapBottom;
  CWndData **m_ppRef;
  class CTTYInfo *m_pTTYInfo;
  void ShowTTYBlock(class CTTYInfo *pInfo, LPCSTR lpBlock, int nLength);

	// Generated message map functions
	//{{AFX_MSG(CWndData)
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg long HandleShowMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnHexMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDDATA_H__071F0743_7F9E_11D2_88A4_444553540000__INCLUDED_)
