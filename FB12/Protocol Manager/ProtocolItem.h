// ProtocolItem.h: interface for the CProtocolItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTOCOLITEM_H__032CD357_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLITEM_H__032CD357_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PPS.h"

class CProtocolItem  
{
public:
	CProtocolItem();
	CProtocolItem(CString& name, CPPS& pps);
	virtual ~CProtocolItem();

	CString m_name;
	CPPS m_pps;
};
bool operator<(const CProtocolItem& item1, const CProtocolItem& item2);

#endif // !defined(AFX_PROTOCOLITEM_H__032CD357_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
