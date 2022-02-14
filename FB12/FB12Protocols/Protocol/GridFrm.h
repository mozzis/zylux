// GridFrm.h : interface of the CGridFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_GridFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGridFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGridFrame)
public:
	CGridFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGridFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GridFRM_H__CE385EEB_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
