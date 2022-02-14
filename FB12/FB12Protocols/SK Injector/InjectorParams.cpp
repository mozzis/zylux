// InjectorParams.cpp: implementation of the CInjectorParams class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sk.h"
#include "InjectorParams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInjectorParams::CInjectorParams() : m_time(2), m_volume(0), m_used(0)
{

}

CInjectorParams::CInjectorParams(const CInjectorParams& ip)
{
	*this = ip;
}

CInjectorParams::~CInjectorParams()
{

}

bool CInjectorParams::Read(CFile & cfile)
{
	try 
	{
		if ((cfile.Read(&m_time, sizeof(m_time)) == sizeof(m_time)) &&
			(cfile.Read(&m_volume, sizeof(m_volume)) == sizeof(m_volume)) &&
			(cfile.Read(&m_used, sizeof(m_used)) == sizeof(m_used)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}

}

bool CInjectorParams::Write(CFile & cfile)
{
	try
	{
		cfile.Write(&m_time, sizeof(m_time));
		cfile.Write(&m_volume, sizeof(m_volume));
		cfile.Write(&m_used, sizeof(m_used));
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}


CInjectorParams & CInjectorParams::operator =(const CInjectorParams & ip)
{
	if (this != &ip)
	{
		m_time = ip.m_time;
		m_volume = ip.m_volume;
		m_used = ip.m_used;
	}

	return *this;
}
