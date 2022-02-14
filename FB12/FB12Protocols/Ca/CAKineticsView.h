#if !defined(AFX_CAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CAKineticsView.h : header file
//

#include "KineticsView.h"

/////////////////////////////////////////////////////////////////////////////
// CCAKineticsView view

class CCAKineticsView : public CKineticsView
{
protected:
	CCAKineticsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCAKineticsView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAKineticsView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCAKineticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCAKineticsView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
