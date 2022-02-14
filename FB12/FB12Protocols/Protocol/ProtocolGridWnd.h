#if !defined(AFX_PROTOCOLGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProtocolGridWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtocolGridWnd window

class CProtocolGridWnd : public CGXGridWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CProtocolGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolGridWnd)
	//}}AFX_VIRTUAL

	virtual BOOL OnRButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol,
		ROWCOL nDragRow, ROWCOL nDragCol, CPoint point,
		UINT flags, WORD nHitState);

// Implementation
public:
	virtual ~CProtocolGridWnd();

	bool SendToExcel(LPCTSTR macroname = NULL, LPCTSTR workbookname = NULL,
		LPCTSTR worksheetname = NULL, WORD cell_col = 0, WORD cell_row = 0);
		// Send grid contents to Excel 95 or 97
		// cell_col must be between 0 and 255
		// cell_row must be between 0 and 65535

	void HiliteCell(ROWCOL row, ROWCOL col);
	void UnhiliteCell(ROWCOL row, ROWCOL col);

	virtual void CMCreateMenu(CMenu& menu);
	bool CMAddItemNG(CMenu& menu, UINT nIDNewItem, LPCTSTR lpszNewItem);
	bool CMAddItem(CMenu& menu, UINT nIDNewItem, LPCTSTR lpszNewItem);

	ROWCOL m_ctxt_cell_row;		// when a context menu item is selected over
								// a cell, the dispatched function can find
								// that cell's row number in this variable
	ROWCOL m_ctxt_cell_col;		// when a context menu item is selected over
								// a cell, the dispatched function can find
								// that cell's column number in this variable
	CString m_ctxt_cell_str;	// when a context menu item is selected over
								// a cell, the dispatched function can find
								// the cell's string contents in this variable
	double m_ctxt_cell_val;		// when a context menu item is selected over
								// a cell, the dispatched function can find
								// the cell's double contents in this variable
	long m_ctxt_cell_int;		// when a context menu item is selected over
								// a cell, the dispatched function can find
								// the cell's integer contents in this variable

	// Generated message map functions
protected:
	CString SendToExcel97(LPCTSTR macroname = NULL, LPCTSTR workbookname = NULL,
		LPCTSTR worksheetname = NULL, WORD cell_col = 0, WORD cell_row = 0);
		// Send grid contents to Excel 97
	CString SendToExcel95(LPCTSTR macroname = NULL, LPCTSTR workbookname = NULL,
		LPCTSTR worksheetname = NULL, WORD cell_col = 0, WORD cell_row = 0);
		// Send grid contents to Excel 95

	//{{AFX_MSG(CProtocolGridWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLGRIDWND_H__CE385EF7_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
