#if !defined(AFX_CAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CAGridWnd.h : header file
//
#include "ProtocolGridWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CCAGridWnd window

class CCAGridWnd : public CProtocolGridWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CCAGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAGridWnd)
	//}}AFX_VIRTUAL
// Implementation
public:

	virtual void OnInitialUpdate();
	virtual ~CCAGridWnd();

	virtual void CMCreateMenu(CMenu& menu);

	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, 
		GXModifyType mt, int nType);

// Generated message map functions
protected:
	//{{AFX_MSG(CCAGridWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
