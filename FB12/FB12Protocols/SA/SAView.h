#if !defined(AFX_SAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SAView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSAView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "SADoc.h"
#include "SAGridWnd.h"
#include "GridView.h"

class CSAView : public CGridView
{
protected:
	CSAView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSAView)

// Form Data
public:
	//{{AFX_DATA(CSAView)
	enum { IDD = IDD_SAVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CSADoc *GetDocument();
	CSAGridWnd m_grid;
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
	//{{AFX_VIRTUAL(CSAView)
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
	virtual ~CSAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSAView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSaveAsText();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnExcel();
	afx_msg void OnAddRep();
	afx_msg void OnAddSamp();
	afx_msg void OnKillfocusEditBackground();
	afx_msg void OnContextBackground();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SAView.cpp
inline CSADoc* CSAView::GetDocument()
   { return (CSADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVIEW_H__CE385EF8_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
