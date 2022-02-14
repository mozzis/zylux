// ProtocolItem.cpp: implementation of the CProtocolItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protocol Manager.h"
#include "ProtocolItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocolItem::CProtocolItem()
{

}

CProtocolItem::CProtocolItem(CString& name, CPPS& pps)
	: m_name(name), m_pps(pps)
{

}

CProtocolItem::~CProtocolItem()
{

}

bool operator<(const CProtocolItem& item1, const CProtocolItem& item2)
{
	if (item1.m_pps.IsBase() && !item2.m_pps.IsBase())
	{
		return true;
	}
	else if (!item1.m_pps.IsBase() && item2.m_pps.IsBase())
	{
		return false;
	}
	else
	{
		if (item1.m_name < item2.m_name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
