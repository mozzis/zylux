#if !defined(AFX_CHARTVIEW_H__BDED57B7_59C6_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CHARTVIEW_H__BDED57B7_59C6_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChartView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ChartView.h"

class CChartView : public CView
{
	friend class CChartOptView;

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CChartView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChartView)

// Attributes
public:

// Operations
public:
	UINT m_sample_end;
	UINT m_sample_start;
	CPoint m_selection_end;
	CPoint m_selection_start;
	bool m_zoomed;
	bool m_selecting;
	void DrawSelection();
	SRGCompoundDisplay* m_compound_display;
	SRGraph m_graph;
	void UpdateSample(UINT sample_num, UINT replicate_num);
	void SetSampleRange();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChartView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoomout();
	afx_msg void OnUpdateZoomout(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTVIEW_H__BDED57B7_59C6_11D1_AE1E_0080C80C9F0E__INCLUDED_)
