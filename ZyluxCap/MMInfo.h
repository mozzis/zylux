// MMInfo.h: interface for the CMMInfo class.
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: MMInfo.h $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:13a
 * Created in $/ZyluxCap/2.0
*/

#if !defined(AFX_MMINFO_H__32161E6C_E84A_11D2_88A4_444553540000__INCLUDED_)
#define AFX_MMINFO_H__32161E6C_E84A_11D2_88A4_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class Info> class CMMInfo  
{
public:
  CMMInfo() { m_pInfo = 0; }
  virtual ~CMMInfo() { m_pInfo = 0; }
  Info *m_pInfo;
  void SetInfo(Info *pInfo) { m_pInfo = pInfo; }
  Info *GetInfo() { return m_pInfo; }
};

#endif // !defined(AFX_MMINFO_H__32161E6C_E84A_11D2_88A4_444553540000__INCLUDED_)
