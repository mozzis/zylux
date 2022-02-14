#if !defined(AFX_DAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAKineticsView.h : header file
//

#include "KineticsView.h"

/////////////////////////////////////////////////////////////////////////////
// CDAKineticsView view

class CDAKineticsView : public CKineticsView
{
protected:
	CDAKineticsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDAKineticsView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAKineticsView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDAKineticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDAKineticsView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
