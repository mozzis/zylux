// RunNameList.h: interface for the RunNameList class.
// CRunNameList is a self-loading string array for RunNames
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: RunNameList.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:54a
 * Updated in $/ZyluxZip
 * Add Save, Load, and initialization
*/
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNNAMELIST_H__72C2ABEF_0BB0_472E_B9FE_21025C3E812A__INCLUDED_)
#define AFX_RUNNAMELIST_H__72C2ABEF_0BB0_472E_B9FE_21025C3E812A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRunName
{
public:
  CRunName();
	virtual ~CRunName();

  CString m_csName;
  CString m_csDescription;
};

class CRunNameList : public CArray<CRunName, CRunName> 
{
public:
	CRunNameList();
	virtual ~CRunNameList();

  bool Load();
	bool Save();

protected:
  CString m_csFileName;
};

#endif // !defined(AFX_RUNNAMELIST_H__72C2ABEF_0BB0_472E_B9FE_21025C3E812A__INCLUDED_)
