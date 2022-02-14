#if !defined(AFX_DLGRUNPROTOCOL_H__62D9C415_B5AF_4BE2_A98E_F293F0B1A162__INCLUDED_)
#define AFX_DLGRUNPROTOCOL_H__62D9C415_B5AF_4BE2_A98E_F293F0B1A162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRunProtocol.h : header file
// DlgRunProtocol is a dialog for editing run protocol lists
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgRunProtocol.h $ * 
// 
// *****************  Version 13  *****************
// User: Maynard      Date: 11/15/00   Time: 8:29a
// Updated in $/ZyluxZip
// Add list box to select which run to upload to, and use it in upload
// proc.
// 
// *****************  Version 12  *****************
// User: Maynard      Date: 11/09/00   Time: 4:53p
// Updated in $/ZyluxZip
// Add OnInsertRowHandler declaration
 * 
 * *****************  Version 11  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:26p
 * Updated in $/ZyluxZip
 * Add first pass of sending data to FB14
 * 
 * *****************  Version 10  *****************
 * User: Maynard      Date: 3/22/00    Time: 1:48p
 * Updated in $/ZyluxZip
 * Finish Edit button function
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 3/18/00    Time: 5:28p
 * Updated in $/ZyluxZip
 * Add handler for edit button push
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/17/00    Time: 1:01p
 * Updated in $/ZyluxZip
 * Implement a prompt (via a CLabel) to warn the user to provide a Run
 * Name and an Assembly name before saving the protocol
 * Abort Save operation if names are not provided
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/17/00    Time: 10:04a
 * Updated in $/ZyluxZip
 * Make check-box cells read-only so single-click always toggles their
 * state
 * Add helper routine to set up combos and check boxes
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:53p
 * Updated in $/ZyluxZip
 * Add function to initialize new run protocol with site list
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/15/00    Time: 1:55p
 * Updated in $/ZyluxZip
 * Set the modified flag if the run protocol or run names change
 * Always bring up SaveAs dialog box even if previously saved
 * Add filename to dialog title
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:43a
 * Updated in $/ZyluxZip
 * Add saving and loading of the run protocol list
 * Hook up the protocol name and run name controls
 * Update the site list selected count control when needed
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:26p
 * Updated in $/ZyluxZip
 * Add OnEditInsRow and OnAutoInsertRow handlers to add checkboxes to
 * first column when new rows are added
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:51p
 * Updated in $/ZyluxZip
 * Add dialog to edit protocol list
*/
/////////////////////////////////////////////////////////////////////////////

#include "dlgziplist.h"
#include "sitelist.h"
#include "runnamelist.h"
class CTTYInfo;
class CRunProtList;

/////////////////////////////////////////////////////////////////////////////
// CDlgRunProtocol dialog

class CDlgRunProtocol : public CDlgZipList
{
// Construction
public:
	CDlgRunProtocol(CWnd* pParent = NULL,
                  CTTYInfo *pI = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRunProtocol)
	enum { IDD = IDD_RUN_PROTOCOL };
	CButton	m_btnEdit;
	CComboBox	m_NameListCombo;
	CString	m_RunProtNameEdit;
	UINT	m_uSiteCount;
  CLabel m_lblNeedNames;
	//}}AFX_DATA

  bool Open(LPCTSTR szFileName);
  bool New();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRunProtocol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  CString m_csLocalFileName;
  CSiteList m_SiteList;
  CRunNameList m_NameList;
  CTTYInfo *m_pTTYInfo;

  virtual bool OkToClose();
  bool SaveRunProtList();
  void UpdateTitle(LPCTSTR szTitle);
  void SetupCheckAndCombo(int nRow); // put controls in 1st 2 cols
  void ShowOrHideWarning(); // show or hide the "need names" label
  void DoClickEdit(bool bEnable); 
  int LoadRunProtList(CRunProtList &runProtList);

	// Generated message map functions
	//{{AFX_MSG(CDlgRunProtocol)
	virtual BOOL OnInitDialog();
  afx_msg void OnInsertRow(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnEditInsRow();
  afx_msg void OnAutoInsertRow(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnEndComboEdit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnRunProtSave();
	afx_msg void OnChangeRunAssembly();
	afx_msg void OnEditchangeRunName();
	afx_msg void OnSelChangeRunName();
	afx_msg void OnClickEdit();
	afx_msg void OnListSend();
	afx_msg void OnChangeRunSlot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRUNPROTOCOL_H__62D9C415_B5AF_4BE2_A98E_F293F0B1A162__INCLUDED_)
