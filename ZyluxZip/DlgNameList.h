#if !defined(AFX_DLGNAMELIST_H__966894EF_4F57_4342_992D_9A10E45A5141__INCLUDED_)
#define AFX_DLGNAMELIST_H__966894EF_4F57_4342_992D_9A10E45A5141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNameList.h : header file
// DlgNameList is a dialog for editing the name list
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgNameList.h $ * 
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:42a
 * Updated in $/ZyluxZip
 * Add saving and loading of the name list
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:25p
 * Updated in $/ZyluxZip
 * Move initialize of m_pColumnDefs to constructor so can eliminate
 * OnInitDialog override
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:50p
 * Updated in $/ZyluxZip
 * Add dialog to edit name list
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INCLUDES()
#include "dlgziplist.h"
//}}AFX_INCLUDES

class CDlgNameList : public CDlgZipList
{
// Construction
public:
	CDlgNameList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNameList)
	enum { IDD = IDD_NAMELIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNameList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  virtual bool OkToClose();
  bool SaveNameList();

	// Generated message map functions
	//{{AFX_MSG(CDlgNameList)
  afx_msg void OnNamesSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNAMELIST_H__966894EF_4F57_4342_992D_9A10E45A5141__INCLUDED_)
