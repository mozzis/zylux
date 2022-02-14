// SKPPS.cpp: implementation of the CSKPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SKPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSKPPS::CSKPPS() : m_SKversion(1), m_SKflags(FLAG_LUMITIMEBASE),
	m_delaytime(10), m_meastime(10), m_intervaltime(50),
	m_numsamples(1), m_numreplicates(1)
{
	SetBase(true);
	SetSaveAsable(true);
	strcpy(m_protocolexe, "SK.exe");
	strcpy(m_protocolname, "Single Kinetics");
	strcpy(m_comment, "Single Kinetics measures a sample many times over a period of time at specified intervals.");
}

CSKPPS::CSKPPS(const CSKPPS& pps)
{
	*this = pps;
}

CSKPPS::~CSKPPS()
{

}

bool CSKPPS::Write(CFile& cfile)
{
	try
	{
		if (!CGPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_SKversion, sizeof(m_SKversion));
		cfile.Write(&m_SKflags, sizeof(m_SKflags));
		cfile.Write(&m_delaytime, sizeof(m_delaytime));
		cfile.Write(&m_meastime, sizeof(m_meastime));
		cfile.Write(&m_intervaltime, sizeof(m_intervaltime));
		cfile.Write(&m_numsamples, sizeof(m_numsamples));
		cfile.Write(&m_numreplicates, sizeof(m_numreplicates));
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}

bool CSKPPS::Read(CFile& cfile)
{
	try
	{
		if ((CGPPS::Read(cfile)) &&
			(cfile.Read(&m_SKversion, sizeof(m_SKversion)) == sizeof(m_SKversion)) &&
			(m_SKversion == 1) &&
			(cfile.Read(&m_SKflags, sizeof(m_SKflags)) == sizeof(m_SKflags)) &&
			(cfile.Read(&m_delaytime, sizeof(m_delaytime)) == sizeof(m_delaytime)) &&
			(cfile.Read(&m_meastime, sizeof(m_meastime)) == sizeof(m_meastime)) &&
			(cfile.Read(&m_intervaltime, sizeof(m_intervaltime)) == sizeof(m_intervaltime)) &&
			(cfile.Read(&m_numsamples, sizeof(m_numsamples)) == sizeof(m_numsamples)) &&
			(cfile.Read(&m_numreplicates, sizeof(m_numreplicates)) == sizeof(m_numreplicates)))
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

CSKPPS& CSKPPS::operator=(const CSKPPS& pps)
{
	if (this != &pps)
	{
		CGPPS::operator=(pps);
		m_SKversion = pps.m_SKversion;
		m_SKflags = pps.m_SKflags;
		m_delaytime = pps.m_delaytime;
		m_meastime = pps.m_meastime;
		m_intervaltime = pps.m_intervaltime;
		m_numsamples = pps.m_numsamples;
		m_numreplicates = pps.m_numreplicates;
	}

	return *this;
}

bool CSKPPS::IsLumiTimeBase() const
{
	return (m_SKflags & FLAG_LUMITIMEBASE) ? true : false;
}

void CSKPPS::SetLumiTimeBase(bool is_lumitimebase)
{
	if (is_lumitimebase)
	{
		m_SKflags |= FLAG_LUMITIMEBASE;
	}
	else
	{
		m_SKflags &= ~FLAG_LUMITIMEBASE;
	}
}
