// ZyluxZipDlg.h : header file
// CZyluxZipDlg is the main dialog window for this program
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: ZyluxZipDlg.h $ * 
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 9/04/00    Time: 12:59p
// Updated in $/ZyluxZip
// Make separate menu item update handler for Capture
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 6/08/00    Time: 7:24a
// Updated in $/ZyluxZip
// Move the ZyluxCapApp COM object coclass def to the .cpp file from this
// header - much cleaner interface
// 
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:43p
 * Updated in $/ZyluxZip
 * Add settings dialog and data window
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:22p
 * Updated in $/ZyluxZip
 * Add OnCapture handler with Notifier to handle launching the ZyluxCap
 * program and detecting when it goes away
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:39p
 * Updated in $/ZyluxZip
 * Add routine to disable MRU items if Run Protocol editor is already open
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/15/00    Time: 2:02p
 * Updated in $/ZyluxZip
 * Add routine to respond to selection from MRU list in Run Protocol menu
 * item
 * Separate RunProtocol open code into DoOpenRunProtocol called by both
 * regular and MRU versions of menu open
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/02/00    Time: 8:39p
 * Updated in $/ZyluxZip
 * Add NameList and RunProtocol dialogs
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/01/00    Time: 10:48a
 * Updated in $/ZyluxZip
 * Add override of OnCmdMsg to chain message map to child dialogs
 * Add a pointer to modeless dialog member variable
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:43p
 * Updated in $/ZyluxZip
 * Add RunProtocolOpen handler
 * Remove OnInitMenu handler
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////
//

#if !defined(AFX_ZYLUXZIPDLG_H__B159E59B_1E4D_4172_A9A4_B2F5735E827D__INCLUDED_)
#define AFX_ZYLUXZIPDLG_H__B159E59B_1E4D_4172_A9A4_B2F5735E827D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZyluxZipDlg dialog

class CZyluxZipDlg : public CFormView
{
	DECLARE_DYNCREATE(CZyluxZipDlg);
	friend class CZyluxZipDlgAutoProxy;

// Construction
public:
	CZyluxZipDlg(CWnd **ppRef = NULL);	// standard constructor
	virtual ~CZyluxZipDlg();

  void SetRef(CWnd **ppRef) 
    { m_ppRef = ppRef; if (ppRef) *ppRef = this; } 

// Dialog Data
	//{{AFX_DATA(CZyluxZipDlg)
	enum { IDD = IDD_ZYLUXZIP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyluxZipDlg)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
  virtual void OnInitMenu(CMenu* pMenu);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CZyluxZipDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;
  UINT m_uIdDlg; // flag if a dialog is up
  CWnd *m_pDlg; // pointer to modeless dialog if any
  CWnd **m_ppRef;
  class CWndData *m_pWndData;
  class CTTYInfo *m_pTTYInfo;
  virtual LRESULT OnDialogClosed(WPARAM, LPARAM);
  virtual LRESULT OnDialogOpened(WPARAM, LPARAM);
  BOOL DoRunProtocolOpen(LPCTSTR szFileName);
	BOOL CanExit();
  static void OnNotify(LONG lCat, LONG lCode, IUnknown * pUnk);

  // Generated message map functions
	//{{AFX_MSG(CZyluxZipDlg)
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnSiteList();
	afx_msg void OnUpdateMRUItem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuItem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCapture(CCmdUI* pCmdUI);
	afx_msg void OnSettings();
	afx_msg void OnRunProtocolOpen();
	afx_msg void OnRunNames();
	afx_msg void OnRunProtocolNew();
  afx_msg BOOL OnOpenRecentProtList(UINT nID);
	afx_msg void OnCapture();
	afx_msg void OnShowData();
  afx_msg void OnUpdateShowData(CCmdUI* pCmdUI) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT

#endif // !defined(AFX_ZYLUXZIPDLG_H__B159E59B_1E4D_4172_A9A4_B2F5735E827D__INCLUDED_)
