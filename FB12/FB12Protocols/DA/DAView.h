#if !defined(AFX_DAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "DADoc.h"
#include "DAGridWnd.h"
#include "GridView.h"

class CDAView : public CGridView
{
protected:
	CDAView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDAView)

// Form Data
public:
	//{{AFX_DATA(CDAView)
	enum { IDD = IDD_DAVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CDADoc *GetDocument();
	CDAGridWnd m_grid;

// Operations
public:
	void SendToExcel();
	bool EditsActive();
	ROWCOL hilite_col;
	ROWCOL hilite_row;
	void UpdateSample(UINT sample_num);
	void HiliteCell();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAView)
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
	virtual ~CDAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDAView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSaveAsText();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnExcel();
	afx_msg void OnCheckNormalize();
	afx_msg void OnKillfocusEditBackgroundA();
	afx_msg void OnKillfocusEditBackgroundB();
	afx_msg void OnKillfocusEditNormalize();
	afx_msg void OnContextBackgroundA();
	afx_msg void OnContextBackgroundB();
	afx_msg void OnContextNormalize();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DAView.cpp
inline CDADoc* CDAView::GetDocument()
   { return (CDADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
