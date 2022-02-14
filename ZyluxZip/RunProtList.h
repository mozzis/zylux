// RunProtList.h: interface for the CRunProtList class.
// CRunProtList is a self-loading string array for the RunProtocolList
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: RunProtList.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:55a
 * Updated in $/ZyluxZip
 * Add Save, Load, and initialization
*/
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNPROTLIST_H__461910FD_A6BE_4C4B_BFAE_2E2128A95953__INCLUDED_)
#define AFX_RUNPROTLIST_H__461910FD_A6BE_4C4B_BFAE_2E2128A95953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sitelist.h"

class CRunProtItem : public CSite
{
public:
  CRunProtItem() : m_bSelected(false) {}
  virtual ~CRunProtItem() {}
  bool m_bSelected;
};

class CRunProtList : public CArray<CRunProtItem, CRunProtItem> 
{
public:
	CRunProtList();
	virtual ~CRunProtList();

  bool Load(LPCTSTR szFileName);
	bool Save();
	bool SaveAs(LPCTSTR szFileName);
  CString RunProtocolName() { return m_csRunProtocolName; }
  CString RunName() { return m_csRunName; }
  void RunProtocolName(LPCTSTR szNew ) { m_csRunProtocolName = szNew; }
  void RunName(LPCTSTR szNew) { m_csRunName = szNew; }
protected:
  CString m_csRunProtocolName;
  CString m_csRunName;
  CString m_csFileName;
};

#endif // !defined(AFX_RUNPROTLIST_H__461910FD_A6BE_4C4B_BFAE_2E2128A95953__INCLUDED_)
