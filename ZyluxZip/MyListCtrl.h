// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLISTCTRL_H__D55926E2_6511_11D2_9EB9_006097BA9496__INCLUDED_)
#define AFX_MYLISTCTRL_H__D55926E2_6511_11D2_9EB9_006097BA9496__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:
	enum EHighlight {HIGHLIGHT_NORMAL, HIGHLIGHT_ALLCOLUMNS, HIGHLIGHT_ROW};
protected:
	int  m_nHighlight;		// Indicate type of selection highlighting

// Operations
public:
  int HitTestEx(CPoint &point, int *col) const;
  CEdit* EditSubLabel( int nItem, int nCol );
  int CMyListCtrl::SetHighlightType(EHighlight hilite);
  BOOL SortTextItems( int nCol, BOOL bAscending, int low = 0, int high = -1);
  int GetColumnCount(void);
  void AutoSizeColumns(int col = -1);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();
protected:
  void RepaintSelectedItems();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__D55926E2_6511_11D2_9EB9_006097BA9496__INCLUDED_)
