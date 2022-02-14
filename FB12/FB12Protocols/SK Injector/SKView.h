#if !defined(AFX_SKVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SKVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SKView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSKView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "SKDoc.h"
#include "SKGridWnd.h"
#include "GridView.h"

class CSKView : public CGridView
{
protected:
	CSKView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSKView)

// Form Data
public:
	//{{AFX_DATA(CSKView)
	enum { IDD = IDD_SKVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CSKDoc *GetDocument();
	CSKGridWnd m_grid;
	bool m_showinject;

// Operations
public:
	void InitInjectList(CListBox *pList);
	void SendToExcel();
	bool EditsActive();
	ROWCOL hilite_col;
	ROWCOL hilite_row;
	void UpdateSample(UINT sample_num);
	void HiliteCell();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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
	virtual ~CSKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSKView)
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

#ifndef _DEBUG  // debug version in SKView.cpp
inline CSKDoc* CSKView::GetDocument()
   { return (CSKDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
