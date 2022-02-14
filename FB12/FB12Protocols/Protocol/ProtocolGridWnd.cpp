// ProtocolGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolGridWnd.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CProtocolGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CProtocolGridWnd

CProtocolGridWnd::CProtocolGridWnd()
{
}

CProtocolGridWnd::~CProtocolGridWnd()
{
}


BEGIN_MESSAGE_MAP(CProtocolGridWnd, CGXGridWnd)
	//{{AFX_MSG_MAP(CProtocolGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProtocolGridWnd message handlers

// HiliteCell()
//
// Highlights the specified cell (if it's in the grid)
//
// Inputs:
//   row - the row of the cell to highlight
//   col - the column of the cell to highlight

void CProtocolGridWnd::HiliteCell(ROWCOL row, ROWCOL col)
{
	if ((row <= GetRowCount()) && (col <= GetColCount()))
	{
		// Set the border color
		CGXPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		SetStyleRange(CGXRange(row, col), CGXStyle()
			.SetBorders(gxBorderTop, pen)
			.SetBorders(gxBorderBottom, pen)
			.SetBorders(gxBorderLeft, pen)
			.SetBorders(gxBorderRight, pen)
			);
	}
}

// UnhiliteCell()
//
// Unhighlights the specified cell (if it's in the grid)
//
// Inputs:
//   row - the row of the cell to unhighlight
//   col - the column of the cell to unhighlight

void CProtocolGridWnd::UnhiliteCell(ROWCOL row, ROWCOL col)
{
	if ((row <= GetRowCount()) && (col <= GetColCount()))
	{
		// Reset the border color
		SetStyleRange(CGXRange(row, col), CGXStyle()
			.SetIncludeBorders(gxBorderTop, TRUE)
			.SetIncludeBorders(gxBorderBottom, TRUE)
			.SetIncludeBorders(gxBorderLeft, TRUE)
			.SetIncludeBorders(gxBorderRight, TRUE),
			gxExclude);
	}
}

void CProtocolGridWnd::CMCreateMenu(CMenu& menu)
{
	// Add the Copy if we can
	if (CanCopy())
	{
		// Add the copy item
		CMAddItemNG(menu, ID_EDIT_COPY, _T("&Copy"));
	}
}

// CMAddItem()
//
// Context Menu Add Item - add the id and string to the menu
//
// Call this routine to add an item to the end of the menu.
//
// Inputs:
//   menu        - the menu on which to add the new menu item
//   nIDNewItem  - the resource ID for the new menu item
//   lpszNewItem - the text of the new menu item
//
// Output: true if successful, false if unsuccessful

bool CProtocolGridWnd::CMAddItem(CMenu& menu, UINT nIDNewItem, LPCTSTR lpszNewItem)
{
	return menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, nIDNewItem, lpszNewItem)
		? true : false;
}

// CMAddItemNG()
//
// Context Menu Add Item New Group - add a menu separator if needed,
// then adds the id and string to the menu
//
// Call this routine to start a new group at the end of a menu.  This
// function will first append a seperator, then the new menu item to
// the menu.
//
// Inputs:
//   menu        - the menu on which to add the new menu item
//   nIDNewItem  - the resource ID for the new menu item
//   lpszNewItem - the text of the new menu item
//
// Output: true if successful, false if unsuccessful

bool CProtocolGridWnd::CMAddItemNG(CMenu& menu, UINT nIDNewItem, LPCTSTR lpszNewItem)
{
	if (menu.GetMenuItemCount() > 0)
	{
		if (!menu.AppendMenu(MF_SEPARATOR))
		{
			return false;
		}
	}

	return CMAddItem(menu, nIDNewItem, lpszNewItem);
}

BOOL CProtocolGridWnd::OnRButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol,
	ROWCOL nDragRow, ROWCOL nDragCol, CPoint point,
	UINT flags, WORD nHitState)
{
	if (nHitState & GX_HITSTART)
	{
		// Create the context menu
		CMenu menu;
		if (menu.CreatePopupMenu())
		{
			// Get the contents of the cell
			m_ctxt_cell_row = nHitRow;
			m_ctxt_cell_col = nHitCol;
			m_ctxt_cell_str = GetValueRowCol(nHitRow, nHitCol);
			m_ctxt_cell_val = (float)atof(m_ctxt_cell_str);
			m_ctxt_cell_int = (long)SCNearestInt(m_ctxt_cell_val);

			CMCreateMenu(menu);

			// Show the menu only if we have anything to select
			if (menu.GetMenuItemCount() > 0)
			{
				// Convert the click point to screen coordinates
				CPoint scr_point(point);
				ClientToScreen(&scr_point);

				// Present the menu
				menu.TrackPopupMenu(TPM_LEFTALIGN, scr_point.x, scr_point.y, GetParent());

				m_nHitState = 0;
			}
		}
	}

	return TRUE;
}

// SendToExcel()
//
// This function will send the contents of the grid to
// Excel 97 then execute the specified macro in Excel
// if available.
//
// Inputs:
//   macroname - a string containing the name of the
//               to execute in Excel after sending the
//               data
//
// Output: none

bool CProtocolGridWnd::SendToExcel(LPCTSTR macroname, LPCTSTR workbookname,
		LPCTSTR worksheetname, WORD cell_col, WORD cell_row)
{
	bool excel97 = false;
	bool excel95 = false;
	HKEY key;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Office\\8.0\\Excel",
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		excel97 = true;
		RegCloseKey(key);
	}
	if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Excel\\7.0",
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		excel95 = true;
		RegCloseKey(key);
	}

	if (!excel97 && !excel95)
	{
		SCMessageBox("Neither Excel (TM) 97 nor Excel (TM) 95 are\ninstalled on your computer.");
		return false;
	}

	CString error97_str;
	CString error95_str;

	if (excel97)
	{
		error97_str = SendToExcel97(macroname, workbookname, worksheetname, cell_col, cell_row);
		if (error97_str.IsEmpty())
		{
			return true;
		}
	}

	if (excel95 && !excel97)
	{
		error95_str = SendToExcel95(macroname);
		if (error95_str.IsEmpty())
		{
			return true;
		}
	}

	if (!error97_str.IsEmpty())
	{
		SetFocus();
		SCMessageBox(error97_str);
	}
	if (!error95_str.IsEmpty())
	{
		SetFocus();
		SCMessageBox(error95_str);
	}

	return false;
}
