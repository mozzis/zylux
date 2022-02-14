// GridCombo.h: interface for the CGridCombo class.
// CGridCombo is a CGridCell which presents a combo box at edit time
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: GridCombo.h $ * 
// 
// *****************  Version 2  *****************
// User: Maynard      Date: 11/14/00   Time: 1:08p
// Updated in $/ZyluxZip/Grid
// Change include to reflect relocation of GridCombo to the Grid directory
// 
// *****************  Version 1  *****************
// User: Maynard      Date: 11/14/00   Time: 12:37p
// Created in $/ZyluxZip/Grid
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:52a
 * Updated in $/ZyluxZip
 * Add code to produce the combo box for editing and to add and delete
 * items
*/
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCOMBO_H__3FF259D7_A714_42C7_89E1_D34382CB61AB__INCLUDED_)
#define AFX_GRIDCOMBO_H__3FF259D7_A714_42C7_89E1_D34382CB61AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class CGridCombo : public CGridCell  
{
    DECLARE_DYNCREATE(CGridCombo)
public:
	CGridCombo();
	virtual ~CGridCombo();
  virtual BOOL Edit(int nRow, int nCol, CRect rect, UINT nID, UINT nChar);
  static void AddItem(LPCSTR szItem);
  static void DelItem(LPCSTR szItem);
  static void RemoveAll();
protected:
  static CStringArray m_Items;
};

#endif // !defined(AFX_GRIDCOMBO_H__3FF259D7_A714_42C7_89E1_D34382CB61AB__INCLUDED_)
