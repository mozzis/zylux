// GridZip.h: interface for the CGridZip class.
// CGridZip is a derivative of CGridCtrl to redirect certain characters
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: GridZip.h $ * 
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
 * Remove InsertRow and GetCell overrides
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/04/00    Time: 11:57a
 * Created in $/ZyluxZip
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

#if !defined(AFX_ZIPGRID_H__ADFFE2EA_4E53_4160_896E_8242D7378469__INCLUDED_)
#define AFX_ZIPGRID_H__ADFFE2EA_4E53_4160_896E_8242D7378469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GRID\GridCtrl.h"

class CGridZip : public CGridCtrl  
{
  DECLARE_DYNCREATE(CGridZip)
public:
	CGridZip();
// Implementation
	virtual ~CGridZip();
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CGridZip)
protected:
  virtual CGridCell *CreateCell(int nRow, int nCol);
public:
  virtual BOOL SetItemFormat(int nRow, int nCol, UINT nFormat);
  BOOL SetItemFloat(int nRow, int nCol, double dData);
  //}}AFX_VIRTUAL

protected:
  // Generated message map functions
  //{{AFX_MSG(CGridZip)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_ZIPGRID_H__ADFFE2EA_4E53_4160_896E_8242D7378469__INCLUDED_)
