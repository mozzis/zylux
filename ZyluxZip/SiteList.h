// SiteList.h: interface for the CSiteList class.
// CSiteList is a self-loading string array for the SiteList
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: SiteList.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:55a
 * Updated in $/ZyluxZip
 * Add Save, Load, and initialization
*/
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SITELIST_H__7D98492F_81A1_44F7_8A9A_23316F9A186D__INCLUDED_)
#define AFX_SITELIST_H__7D98492F_81A1_44F7_8A9A_23316F9A186D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSite
{
public:
  CSite();
	virtual ~CSite();

  CString m_csName;
  CString m_csDescription;
  double m_ThresholdLow;
  double m_ThresholdHigh;
  double m_ScaleLow;
  double m_ScaleHigh;
};

class CSiteList : public CArray<CSite, CSite> 
{
public:
	CSiteList();
	virtual ~CSiteList();

  bool Load();
	bool Save();

protected:
  CString m_csFileName;
};

#endif // !defined(AFX_SITELIST_H__7D98492F_81A1_44F7_8A9A_23316F9A186D__INCLUDED_)
