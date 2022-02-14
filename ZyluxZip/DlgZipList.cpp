// DlgZipList.cpp : implementation file
// DlgSiteList is a dialog which contains a Zip List control
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgZipList.cpp $ * 
// 
// *****************  Version 12  *****************
// User: Maynard      Date: 11/28/00   Time: 12:25p
// Updated in $/ZyluxZip
// Add right-click (context-menu) handler
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 11/09/00   Time: 4:52p
// Updated in $/ZyluxZip
// Add "true" parameter to call to UpgradeDataRowCount so that list
// control will shrink if the number of entries in list is smaller than
// the default
// Other fixes to UpgradeDataRowCount and RenumberRows - fix row number
// calcs, do auto-insert row stuff in RenumberRow and not in
// UpgradeDataRowCount
// Add handlers for OnInsertRow and OnDeleteRow notifications
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 9/26/00    Time: 9:03a
// Updated in $/ZyluxZip
// Make function to change row count to a new number if the new count is
// greater than the present count, and call it to size the grids to their
// respective lists' sizes in OnInitDialog
// 
// *****************  Version 9  *****************
// User: Maynard      Date: 7/21/00    Time: 3:52p
// Updated in $/ZyluxZip
// Make Edit...Delete Row delete all selected rows, except for the bottom
// grid row (the "auto-insert" row)
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/18/00    Time: 5:31p
 * Updated in $/ZyluxZip
 * Get rid of some extra symbol names; now similar buttons have same
 * symbol name in all dialogs
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/17/00    Time: 12:47a
 * Updated in $/ZyluxZip
 * Get real status bar height instead of guessing
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/15/00    Time: 1:57p
 * Updated in $/ZyluxZip
 * Save the base dialog title text in a member variable so it can be used
 * with filenames in derived classes
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:30p
 * Updated in $/ZyluxZip
 * Changes to reflect bug fixing related to row insertion; removed a lot
 * of now-uneccessary code from OnInitDialog. Created RenumberRows helper
 * function with common code for renumbering the rows on insert and delete
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/02/00    Time: 8:36p
 * Updated in $/ZyluxZip
 * Moved column autosizing around again
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:56p
 * Updated in $/ZyluxZip
 * Do more work to avoid bug in row and column sizing when inserting rows
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/01/00    Time: 12:45p
 * Updated in $/ZyluxZip
 * Create a base class to use for all the grid editor dialogs
*/
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ZyluxZip.h"
#include "DlgZipList.h"
#include "messages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgZipList::CDlgZipList(UINT uID, CWnd* pParent /*=NULL*/)
  : CDialog(uID, pParent)
{
  m_nInitColCount = 6;
  m_nInitRowCount = 15;
  m_pColumnDefs = 0;
  m_nLastInsertedRow = -1;
  m_Grid.SetFixedRowCount(1); // title rows
  //{{AFX_DATA_INIT(CDlgZipList)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

CDlgZipList::~CDlgZipList()
{

}

void CDlgZipList::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgZipList)
  DDX_Control(pDX, IDC_DLG_TITLE, m_Title);
  DDX_GridControl(pDX, IDC_SITELIST, m_Grid);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZipList, CDialog)
  //{{AFX_MSG_MAP(CDlgZipList)
  ON_BN_CLICKED(IDC_LIST_PRINT, OnPrint)
  ON_WM_CLOSE()
  ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
  ON_COMMAND(ID_EDIT_CUT, OnEditCut)
  ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
  ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
  ON_COMMAND(ID_EDIT_INS_ROW, OnEditInsRow)
  ON_NOTIFY(GVN_INSERTITEM, IDC_SITELIST, OnInsertRow)
  ON_NOTIFY(GVN_DELETEITEM, IDC_SITELIST, OnDeleteRow)
  ON_NOTIFY(NM_RCLICK, IDC_SITELIST, OnNotifyRClick)

  ON_COMMAND(ID_EDIT_DEL_ROW, OnEditDelRow)
  ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyOrCut)
  ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INS_ROW, OnUpdateEditInsRow)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DEL_ROW, OnUpdateEditDelRow)
  ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyOrCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZipList message handlers

BOOL CDlgZipList::OnInitDialog() 
{
  CDialog::OnInitDialog();
  m_Title.GetWindowText(m_csBasicTitle);
  m_Title.SetFontBold(TRUE);  // Make the title big, bold, and blue
  m_Title.SetFontSize(10);
  m_Title.SetTextColor(RGB(0,0,0xFF));
  // Now set up columns and rows in grid
  m_Grid.SetListMode(FALSE);   // no sorting on column header clicks
  m_Grid.SetColumnCount(m_nInitColCount);
  m_Grid.SetRowCount(m_nInitRowCount);
  m_Grid.SetFixedColumnCount(1); // row numbers in leftmost column
  // Put titles in column headers
  if (m_pColumnDefs) // derived class must set up column defs
    {
    ZIPCOLDEF *pColDef = m_pColumnDefs;
    while (pColDef->nRow != -1 && pColDef->nCol != -1 && pColDef->Title != 0)
      {
      m_Grid.SetItemText(pColDef->nRow, pColDef->nCol, pColDef->Title);
      m_Grid.SetItemFormat(pColDef->nRow, pColDef->nCol, DT_WORDBREAK|DT_CENTER);
      pColDef++;
      }
    }
  else
    TRACE0("You didn't provide titles for the columns!\n");

  // last row is special - mark it with "*" to denote auto-insert row
  m_Grid.SetItemText(m_nInitRowCount - 1, 0, GRID_AUTOINSERT_STRING);

  // Fit this dialog into the parent window's client so it seems to replace it
  CFrameWnd *pParent = GetParentFrame();
  CWnd *pBar = pParent->GetMessageBar();

  CRect cRectBar(0, 0, 0, 18), cRectPar, cRectCli;
  if (pBar)
    pBar->GetWindowRect(&cRectBar);

  pParent->GetClientRect(&cRectPar);
  // Must adjust size to account for status bar in parent
  cRectPar.bottom -= cRectBar.Height();
  // make sure height is integral number of rows
  int nHeight = m_Grid.GetRowHeight(m_Grid.GetFixedRowCount());
  int nRem = cRectPar.Height() % nHeight;
  cRectPar.bottom -= nRem;
  MoveWindow(&cRectPar);      // set dialog size to fit into parent client
  m_Grid.GetWindowRect(&cRectCli); // set grid size to fit into dialog client
  ScreenToClient(&cRectCli);
  cRectCli.bottom = cRectPar.bottom;
  m_Grid.MoveWindow(&cRectCli);

  m_Grid.ExpandToFit();        // Expand grid to fit its window space
  m_Grid.AutoSizeColumn(0);    // Make first column narrower
  m_Grid.ExpandColumnsToFit(); // Expand columns again
  m_Grid.SetModified(FALSE);   // mark as "unmodified" - no editing done yet
  m_Grid.SetFocus();
  m_Grid.SetFocusCell(1,1); // top-left cell (but not column or row header)

  return FALSE;  // return TRUE unless you set the focus to a control
}

// Runs when the user clicks the Print button
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::OnPrint() 
{
  m_Grid.Print();
}

// Makes sure that changes are saved before allowing dialog to close
/////////////////////////////////////////////////////////////////////////////
bool CDlgZipList::OkToClose()
{
  if (m_Grid.GetModified())
    {
    int nRes = 
      AfxMessageBox("Data has changed! Save changes?", MB_YESNOCANCEL);
    if (IDCANCEL == nRes)
      return false;
    if (IDYES == nRes)
      return true; // SaveSiteList();
    }
  return true;
}

// This runs if the Cancel button is clicked or window gets IDCANCEL command
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::OnCancel() 
{
  if (!OkToClose())
    return;
  CDialog::OnCancel();
  DestroyWindow();
}

// This is absolutely the last thing that runs while there is still an hWnd
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::PostNcDestroy() 
{
  delete this;
}

// This runs in order to destroy and clean up window
/////////////////////////////////////////////////////////////////////////////
BOOL CDlgZipList::DestroyWindow() 
{
  GetParent()->SendMessage(WM_DLGCLOSED, 0, 0);
  return CDialog::DestroyWindow();
}

// This runs if user clicks close box or window otherwise receives WM_CLOSE
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::OnClose() 
{
  if (!OkToClose())
    return;
  DestroyWindow();
}

// Don't let CDialog see escape key! It invokes the Cancel function
// Don't let CDialog see enter key! It invokes the OK function
// Always send escape and enter down to grid, which may ignore them
// If in-place edit in progress, escape will restore previous cell contents
// Enter moves cursor to next cell
/////////////////////////////////////////////////////////////////////////////
BOOL CDlgZipList::PreTranslateMessage(MSG* pMsg) 
{
  if(WM_KEYDOWN == pMsg->message)
    {
    if(VK_RETURN == pMsg->wParam ||
       VK_ESCAPE == pMsg->wParam ||
       VK_INSERT == pMsg->wParam)
      {
      ::TranslateMessage(pMsg);
      ::DispatchMessage(pMsg);
      return TRUE;                    // DO NOT process further
      }
    }
  return CDialog::PreTranslateMessage(pMsg);
}

void CDlgZipList::UpgradeDataRowCount(int nDataRows, bool bGrowOnly /* = false */) 
{
  int nRows = m_Grid.GetRowCount();
  int nFixRows = m_Grid.GetFixedRowCount();
  int nNeedRows = nDataRows + nFixRows + 1; // allow for auto-insert row
  if (!bGrowOnly || (nRows < nNeedRows))
    {
    m_Grid.SetRowCount(nNeedRows);
    RenumberRows(min(nRows-1, nNeedRows));
    }
}

void CDlgZipList::RenumberRows(int nRow) 
{
  int nRows = m_Grid.GetRowCount(),
      nFixedRows = m_Grid.GetFixedRowCount();
  for (int i = max(1,nRow); i < nRows; i++)
    {
    CString csTemp;
    csTemp.Format("%d", i - nFixedRows + 1);
    m_Grid.SetItemText(i,0, csTemp);
    m_Grid.SetModified(FALSE, i, 0); // doesn't count as a mod
    }
  if (i > nFixedRows+1)
    {
    // Mark last row as auto-insert
    m_Grid.SetItemText(i-1, 0, GRID_AUTOINSERT_STRING);
    m_Grid.SetModified(FALSE, i-1, 0); // doesn't count as a mod
    }
}

// called when user uses CTRL_INS to insert a row
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::OnInsertRow(NMHDR*, LRESULT*)
{
  OnEditInsRow();
}

// called when user uses CTRL_DEL to delete a row
/////////////////////////////////////////////////////////////////////////////
void CDlgZipList::OnDeleteRow(NMHDR*, LRESULT*)
{
  OnEditDelRow();
}

void CDlgZipList::OnEditInsRow() 
{
  CCellID cell = m_Grid.GetFocusCell(); 
  int nRow = cell.row;
  if (nRow >= 0)
    {
    m_Grid.SetRedraw(FALSE);
    m_nLastInsertedRow = m_Grid.InsertRow(GRID_AUTOINSERT_STRING, nRow); 
    RenumberRows(nRow);
    if (cell.IsValid())
      m_Grid.SetFocusCell(cell);
    m_Grid.SetRedraw(TRUE, TRUE);
    }
}

void CDlgZipList::OnEditDelRow() 
{
  int nRow;
  CCellRange cRange = m_Grid.GetSelectedCellRange();
  if (cRange.Count() < 1 && 0 <= (nRow = m_Grid.GetFocusCell().row))
    {
    m_Grid.SetRedraw(FALSE);
    m_Grid.DeleteRow(nRow); 
    RenumberRows(nRow);
    m_Grid.SetRedraw(TRUE, TRUE);
    m_Grid.Invalidate();
    }
  else if (cRange.Count())
    {
    m_Grid.SetRedraw(FALSE);
    if (cRange.GetMaxRow() >= m_Grid.GetRowCount() - 1)
      cRange.SetMaxRow(m_Grid.GetRowCount() - 2);
    for (int i = cRange.GetMaxRow(); i >= cRange.GetMinRow() &&
                                     m_Grid.GetRowCount() > 2; i--)
      {
      m_Grid.DeleteRow(i); 
      RenumberRows(i);
      }
    m_Grid.SetRedraw(TRUE, TRUE);
    m_Grid.Invalidate();
    }
}

void CDlgZipList::OnEditCopy() 
{
  m_Grid.OnEditCopy();  
}

void CDlgZipList::OnEditCut() 
{
  m_Grid.OnEditCut(); 
}

void CDlgZipList::OnEditPaste() 
{
  m_Grid.OnEditPaste(); 
}

void CDlgZipList::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_Grid.GetSelectedCount() > 0);
}

void CDlgZipList::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
  // Attach a COleDataObject to the clipboard see if there is any data
  COleDataObject obj;
  pCmdUI->Enable(obj.AttachClipboard() && obj.IsDataAvailable(CF_TEXT)); 
}

void CDlgZipList::OnEditSelectall() 
{
  m_Grid.OnEditSelectAll();
}

void CDlgZipList::OnUpdateEditInsRow(CCmdUI* pCmdUI) 
{
  int nRow = m_Grid.GetFocusCell().row;
  pCmdUI->Enable(nRow >= 0);
}

void CDlgZipList::OnUpdateEditDelRow(CCmdUI* pCmdUI) 
{
  int nRow = m_Grid.GetFocusCell().row;
  pCmdUI->Enable(nRow >= 0);
}

void CDlgZipList::OnNotifyRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_GRIDVIEW *pNMGRID = (NM_GRIDVIEW *)pNMHDR;
  CPoint start;
  CRect rect;
  if (!m_Grid.GetCellRect(pNMGRID->iRow, pNMGRID->iColumn, &rect))
    return;
  start = rect.BottomRight();
  // make sure window is active
  GetParentFrame()->ActivateFrame();
  ClientToScreen(&start);
  CMenu menu;
  if (menu.LoadMenu (IDR_MENU_CONTEXT))
    {
    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
      start.x, start.y,
      AfxGetMainWnd()); // use main window for cmds
    }
  OnRButtonDown(pNMGRID->nFlags, start);
}
