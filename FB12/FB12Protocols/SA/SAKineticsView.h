#if !defined(AFX_SAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SAKineticsView.h : header file
//

#include "KineticsView.h"

/////////////////////////////////////////////////////////////////////////////
// CSAKineticsView view

class CSAKineticsView : public CKineticsView
{
protected:
	CSAKineticsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSAKineticsView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAKineticsView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSAKineticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSAKineticsView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAKINETICSVIEW_H__5C8A2981_4C78_11D1_AE1E_0080C80C9F0E__INCLUDED_)
