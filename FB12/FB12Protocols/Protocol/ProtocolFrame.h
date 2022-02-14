#if !defined(AFX_PROTOCOLFRAME_H__8889C0C1_1F57_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLFRAME_H__8889C0C1_1F57_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProtocolFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtocolFrame frame

class CProtocolFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CProtocolFrame)
public:
	CProtocolFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CString m_status_str;

// Operations
public:
	bool m_placement_loaded;
	void DockControlBarRightOf(CToolBar* Bar,CToolBar* RightOf);
	UINT GetLastStatusID() const;
	void SetMessageText(LPCTSTR lpszText);
	void SetMessageText(UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProtocolFrame();

	// Generated message map functions
	//{{AFX_MSG(CProtocolFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLFRAME_H__8889C0C1_1F57_11D1_AE1E_0080C80C9F0E__INCLUDED_)
