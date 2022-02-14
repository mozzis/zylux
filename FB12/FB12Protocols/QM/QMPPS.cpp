// QMPPS.cpp: implementation of the CQMPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QMPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQMPPS::CQMPPS() : m_delaytime(10), m_meastime(10), m_qmversion(1)
{
	SetBase(true);
	SetSaveable(true);
	SetRunable(true);
	strcpy(m_protocolexe, "QM.exe");
	strcpy(m_protocolname, "Quick Measurement");
	strcpy(m_comment, "Quick Measurement is a fast and simple protocol to take measurements with the FB12.");
}

CQMPPS::CQMPPS(const CQMPPS& pps)
{
	*this = pps;
}

CQMPPS::~CQMPPS()
{

}

bool CQMPPS::Write(CFile& cfile)
{
	try
	{
		if (!CPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_qmversion, sizeof(m_qmversion));
		cfile.Write(&m_delaytime, sizeof(m_delaytime));
		cfile.Write(&m_meastime, sizeof(m_meastime));
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}

bool CQMPPS::Read(CFile& cfile)
{
	try
	{
		if ((CPPS::Read(cfile)) &&
			(cfile.Read(&m_qmversion, sizeof(m_qmversion)) == sizeof(m_qmversion)) &&
			(m_qmversion == 1) &&
			(cfile.Read(&m_delaytime, sizeof(m_delaytime)) == sizeof(m_delaytime)) &&
			(cfile.Read(&m_meastime, sizeof(m_meastime)) == sizeof(m_meastime)))
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

CQMPPS& CQMPPS::operator=(const CQMPPS& pps)
{
	if (this != &pps)
	{
		CPPS::operator=(pps);
		m_qmversion = pps.m_qmversion;
		m_delaytime = pps.m_delaytime;
		m_meastime = pps.m_meastime;
	}

	return *this;
}
