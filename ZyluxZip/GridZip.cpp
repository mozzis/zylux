// GridZip.cpp: implementation of the CGridZip class.
// GridZip is a dreivative of CGridCtrl to redirect certain characters
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: GridZip.cpp $ * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:52a
 * Updated in $/ZyluxZip
 * Add SetItemFloat method for putting text representation of numbers into
 * cells
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:33p
 * Updated in $/ZyluxZip
 * Override CreateCell to put numbers into new cells in first column
 * Override SetItemFormat to adust cell height if item format changes
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/04/00    Time: 11:57a
 * Created in $/ZyluxZip
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/01/00    Time: 10:42a
 * Updated in $/ZyluxZip
 * Disable row resizing, enable drag-drop (in constructor)
 * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:38p
 * Updated in $/ZyluxZip
 * Remove un-needed override of OnKeyDown
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZyluxZip.h"
#include "GridZip.h"
#include "inplacecheck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGridZip, CGridCtrl)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridZip::CGridZip()
{
  SetRowResize(FALSE);
  m_bAllowDragAndDrop = TRUE;
  SetTextBkColor(0xFFFFFF);
  m_bDoubleBuffer      = FALSE;     // Use double buffering to avoid flicker?
}

CGridZip::~CGridZip()
{

}

BEGIN_MESSAGE_MAP(CGridZip, CGridCtrl)
  //{{AFX_MSG_MAP(CGridZip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Creates a new grid cell and performs any necessary initialisation
/*virtual*/ CGridCell* CGridZip::CreateCell(int nRow, int nCol)
{
  CGridCell *pCell = CGridCtrl::CreateCell(nRow, nCol);
  if (!pCell)
    return NULL;

  if (0 == nCol && nRow >= m_nFixedRows)
    {
    CString cs;
    cs.Format("%d", nRow - m_nFixedRows + 1);
    pCell->SetText(cs);
    }
  return pCell;
}

BOOL CGridZip::SetItemFormat(int nRow, int nCol, UINT nFormat)
{
  if (CGridCtrl::SetItemFormat(nRow, nCol, nFormat))
    {
    CDC *pDC = GetDC();
    CGridCell *pCell = GetCell(0,1);
    CSize cSz = pCell->GetCellExtent(pDC);
    if (cSz.cy > 0)
      SetRowHeight(nRow, cSz.cy);
    return TRUE;
    }
  return FALSE;
}

BOOL CGridZip::SetItemFloat(int nRow, int nCol, double dData)
{
  CString csData;
  csData.Format("%g", dData);
  return CGridCtrl::SetItemText(nRow, nCol, csData);
}
