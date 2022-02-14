#if !defined(AFX_QMVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_QMVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QMView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQMView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "QMDoc.h"
#include "QMGridWnd.h"
#include "GridView.h"

class CQMView : public CGridView
{
protected:
	CQMView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQMView)

// Form Data
public:
	//{{AFX_DATA(CQMView)
	enum { IDD = IDD_QMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CQMDoc *GetDocument();
	CQMGridWnd m_grid;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQMView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void MyGridResize();
	virtual ~CQMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CQMView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSaveAsText();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnExcel();
	afx_msg void OnUpdateExcel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in QMView.cpp
inline CQMDoc* CQMView::GetDocument()
   { return (CQMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QMVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
