#if !defined(AFX_MKGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MKGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MKGridWnd.h : header file
//

#include "ProtocolGridWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMKGridWnd window

class CMKGridWnd : public CProtocolGridWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CMKGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKGridWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void AdjustGrid(bool nominal);
	virtual ~CMKGridWnd();

	virtual void OnInitialUpdate();

	virtual void CMCreateMenu(CMenu& menu);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMKGridWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
