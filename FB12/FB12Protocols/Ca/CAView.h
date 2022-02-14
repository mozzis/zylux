#if !defined(AFX_CAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CAView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCAView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "CADoc.h"
#include "CAGridWnd.h"
#include "GridView.h"

class CCAView : public CGridView
{
protected:
	CCAView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCAView)

// Form Data
public:
	//{{AFX_DATA(CCAView)
	enum { IDD = IDD_CAVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CCADoc *GetDocument();
	CCAGridWnd m_grid;
    ROWCOL hilite_row;
    ROWCOL hilite_col;

// Operations
public:
	void SendToExcel();
	bool EditsActive();
	void HiliteCell(UINT current_row);

	void UpdateSample(UINT sample_num);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
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
	virtual ~CCAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCAView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSaveAsText();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnExcel();
	afx_msg void OnKillfocusEditBackground();
	afx_msg void OnContextBackground();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CAView.cpp
inline CCADoc* CCAView::GetDocument()
   { return (CCADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
