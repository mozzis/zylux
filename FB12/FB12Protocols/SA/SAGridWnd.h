#if !defined(AFX_SAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SAGridWnd.h : header file
//
#include "ProtocolGridWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSAGridWnd window

class CSAGridWnd : public CProtocolGridWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CSAGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAGridWnd)
	//}}AFX_VIRTUAL
// Implementation
public:

	virtual void OnInitialUpdate();
	virtual ~CSAGridWnd();

	void AddReplicate(UINT last_replicate);
	void AddSample(UINT last_sample, bool use_background);
	virtual void CMCreateMenu(CMenu& menu);

//	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, 
//		GXModifyType mt, int nType);
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, 
		GXModifyType mt, int nType);

// Generated message map functions
protected:
	//{{AFX_MSG(CSAGridWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
