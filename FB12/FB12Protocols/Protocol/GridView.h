// GridView.h : interface of the CGridView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridVIEW_H__A95AC40F_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_GridVIEW_H__A95AC40F_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGridView : public CFormView
{
protected: // create from serialization only
	CGridView();
	CGridView(UINT nIDTemplate);
	DECLARE_DYNCREATE(CGridView)

// Attributes
public:
	CProtocolDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	UINT m_nID;
	//{{AFX_MSG(CGridView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GridView.cpp
inline CProtocolDoc* CGridView::GetDocument()
   { return (CProtocolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GridVIEW_H__A95AC40F_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_)
