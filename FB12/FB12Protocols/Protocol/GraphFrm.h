// GraphFrm.h : interface of the CGraphFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GraphFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_GraphFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGraphFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGraphFrame)
public:
	CGraphFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GraphFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
