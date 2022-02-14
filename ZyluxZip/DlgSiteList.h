#if !defined(AFX_DLGSITELIST_H__E167A345_D2BD_4E54_A2F4_88E0CD90A9FB__INCLUDED_)
#define AFX_DLGSITELIST_H__E167A345_D2BD_4E54_A2F4_88E0CD90A9FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSiteList.h : header file
// CDlgSiteList is a dialog for editing the site list
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgSiteList.h $ * 
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:43a
 * Updated in $/ZyluxZip
 * Add saving and loading of the site list
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:27p
 * Updated in $/ZyluxZip
 * Move initialize of m+pColumnDefs to constructor so can eliminate
 * OnInitDialog override
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:52p
 * Updated in $/ZyluxZip
 * Convert to single-row header with two lines of text per header
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/01/00    Time: 12:44p
 * Updated in $/ZyluxZip
 * Derive the class from CZipListDlg, which does most of the work now
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/01/00    Time: 10:39a
 * Updated in $/ZyluxZip
 * Add Edit menu functions copy, cut,paste, select all, ins/del row
 * 
 * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INCLUDES()
#include "dlgziplist.h"
//}}AFX_INCLUDES

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteList dialog

class CDlgSiteList : public CDlgZipList
{
// Construction
public:
  CDlgSiteList(CWnd* pParent = NULL);   // standard constructor
  virtual ~CDlgSiteList();

// Dialog Data
  //{{AFX_DATA(CDlgSiteList)
	enum { IDD = IDD_SITELIST };
	//}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgSiteList)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual bool OkToClose();
  bool SaveSiteList();

  // Generated message map functions
  //{{AFX_MSG(CDlgSiteList)
  afx_msg void OnSiteSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSITELIST_H__E167A345_D2BD_4E54_A2F4_88E0CD90A9FB__INCLUDED_)
