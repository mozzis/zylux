#if !defined(AFX_KINETICSVIEW_H__A95AC432_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_KINETICSVIEW_H__A95AC432_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KineticsView.h : header file
//

#include "Kinetics.h"

/////////////////////////////////////////////////////////////////////////////
// CKineticsView view

class CKineticsView : public CView
{
public:

protected:
	void OnEditCopy();
	CKineticsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CKineticsView)

	CKinetics* m_kinetics;

// Attributes
public:

// Operations
public:
	void OnKineticsZoomout();
	void OnUpdateKineticsZoomout(CCmdUI* pCmdUI);
	UINT m_sample_end;
	UINT m_sample_start;
	CPoint m_selection_end;
	CPoint m_selection_start;
	bool m_zoomed;
	bool m_selecting;
	void DrawSelection();
	void SetSampleRange();
	int m_maxkinetics;
	SRGCompoundDisplay* m_compound_display;
	CDocument* GetDocument();
	SRGraph m_graph;
	void SetKinetics(CKinetics& kinetics, int max_kinetics);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKineticsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CKineticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	virtual SRGraph* GetGraph();
	//{{AFX_MSG(CKineticsView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DAView.cpp
inline CDocument* CKineticsView::GetDocument()
   { return m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KINETICSVIEW_H__A95AC432_41E1_11D1_AE1E_0080C80C9F0E__INCLUDED_)
