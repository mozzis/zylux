#if !defined(AFX_MKGRAPHFRAME_H__43ABEAC1_6AFF_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MKGRAPHFRAME_H__43ABEAC1_6AFF_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MKGraphFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMKGraphFrame frame

#include "GraphFrm.h"

class CMKGraphFrame : public CGraphFrame
{
	DECLARE_DYNCREATE(CMKGraphFrame)
protected:
	CMKGraphFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKGraphFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSplitterWnd m_splitter;
	virtual ~CMKGraphFrame();

	// Generated message map functions
	//{{AFX_MSG(CMKGraphFrame)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKGRAPHFRAME_H__43ABEAC1_6AFF_11D1_AE1E_0080C80C9F0E__INCLUDED_)
