#if !defined(AFX_DLGZIPLIST_H__D0FF46D5_F40F_4C0C_85C3_DAF1BBD0DEA3__INCLUDED_)
#define AFX_DLGZIPLIST_H__D0FF46D5_F40F_4C0C_85C3_DAF1BBD0DEA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// DlgZipList.h : header file
// CDlgZipList is a dialog containing a Zip List control
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgZipList.h $ * 
// 
// *****************  Version 8  *****************
// User: Maynard      Date: 11/28/00   Time: 12:25p
// Updated in $/ZyluxZip
// Add right-click (context-menu) handler
// 
// *****************  Version 7  *****************
// User: Maynard      Date: 11/09/00   Time: 4:52p
// Updated in $/ZyluxZip
// Add "true" parameter to call to UpgradeDataRowCount so that list
// control will shrink if the number of entries in list is smaller than
// the default
// Add handlers for OnInsertRow and OnDeleteRow notifications
// 
// *****************  Version 6  *****************
// User: Maynard      Date: 9/26/00    Time: 9:03a
// Updated in $/ZyluxZip
// Make function to change row count to a new number if the new count is
// greater than the present count, and call it to size the grids to their
// respective lists' sizes in OnInitDialog
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/15/00    Time: 1:57p
 * Updated in $/ZyluxZip
 * Save the base dialog title text in a member variable so it can be used
 * with filenames in derived classes
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:31p
 * Updated in $/ZyluxZip
 * Created RenumberRows helper function with common code for renumbering
 * the rows on insert and delete
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:56p
 * Updated in $/ZyluxZip
 * Add UpdateUI for EditInsertRow and EditDeleteRow
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/01/00    Time: 12:45p
 * Updated in $/ZyluxZip
 * Create a base class to use for all the grid editor dialogs
 * 
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INCLUDES()
#include "label.h"
//}}AFX_INCLUDES

#include "GridZip.h"

typedef struct ZIPCOLDEF {
  int nRow;
  int nCol;
  LPCTSTR Title;
} ZIPCOLDEF;

#define EndOfCols { -1, -1, 0 }

class CDlgZipList : public CDialog
{
// Construction
public:
	CDlgZipList(UINT uID, CWnd* pParent = NULL);   // standard constructor
  virtual ~CDlgZipList();

// Dialog Data
	//{{AFX_DATA(CDlgZipList)
	CLabel	m_Title;
  CGridZip m_Grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZipList)
	protected:
  public:
  virtual BOOL DestroyWindow();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
  int m_nInitColCount;
  int m_nInitRowCount;
  ZIPCOLDEF *m_pColumnDefs;
  int m_nLastInsertedRow;

  CString m_csBasicTitle;

  virtual bool OkToClose();
  void RenumberRows(int nRow);
  void UpgradeDataRowCount(int nDataRows, bool GrowOnly = false);

	// Generated message map functions
	//{{AFX_MSG(CDlgZipList)
  virtual BOOL OnInitDialog();
  afx_msg void OnPrint();
  virtual void OnCancel();
  afx_msg void OnClose();
  afx_msg void OnEditCopy();
  afx_msg void OnEditCut();
  afx_msg void OnEditPaste();
  afx_msg void OnEditSelectall();
  afx_msg void OnEditInsRow();
  afx_msg void OnInsertRow(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDeleteRow(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnEditDelRow();
  afx_msg void OnUpdateEditCopyOrCut(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditInsRow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelRow(CCmdUI* pCmdUI);
  void OnNotifyRClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZIPLIST_H__D0FF46D5_F40F_4C0C_85C3_DAF1BBD0DEA3__INCLUDED_)
