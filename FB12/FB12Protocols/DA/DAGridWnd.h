#if !defined(AFX_DAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAGridWnd.h : header file
//

#include "ProtocolGridWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDAGridWnd window

class CDAGridWnd : public CProtocolGridWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CDAGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAGridWnd)
	//}}AFX_VIRTUAL
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol,
		const CGXStyle* pStyle, GXModifyType mt = gxOverride,
		int nType = 0);

// Implementation
public:
	virtual ~CDAGridWnd();

	virtual void OnInitialUpdate();

	virtual void CMCreateMenu(CMenu& menu);

	static char* m_xform_net_str[];		// Net transform strings
	static char* m_xform_norm_str[];	// Norm transform strings

	// Generated message map functions
protected:
	//{{AFX_MSG(CDAGridWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
