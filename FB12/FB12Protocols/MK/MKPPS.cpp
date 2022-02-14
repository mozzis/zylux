// MKPPS.cpp: implementation of the CMKPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MK.h"
#include "MKPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMKPPS::CMKPPS() : m_mkversion(1), m_delaytime(10), m_meastime(10), m_numreps(1), 
				   m_numsamps(1), m_intervaltime(100), m_mkflags(FLAG_LUMITIMEBASE),
				   m_nummeasurements(1)
{
	SetBase(true);
	SetSaveAsable(true);
	SetUseStartButton(false);
	strcpy(m_protocolexe, "MK.exe");
	strcpy(m_protocolname, "Multiple Kinetics");
	strcpy(m_comment, "Multiple Kinetics is intended for the parallel, \
interlocked measurement of the kinetics of several samples with replicates.");
}


CMKPPS::CMKPPS(const CMKPPS& pps) : CGPPS(pps)
{
	*this = pps;
}


CMKPPS::~CMKPPS()
{

}


CMKPPS& CMKPPS::operator=(const CMKPPS& pps)
{

	if (this != &pps)
	{
		CGPPS::operator=(pps);
		m_mkversion = pps.m_mkversion;
		m_mkflags = pps.m_mkflags;
		m_delaytime = pps.m_delaytime;
		m_meastime = pps.m_meastime;
		m_intervaltime = pps.m_intervaltime;
		m_numreps = pps.m_numreps;
		m_numsamps = pps.m_numsamps;
		m_nummeasurements = pps.m_nummeasurements;
	}
	return *this;
}


bool CMKPPS::Write(CFile& cfile)
{
	try
	{
		if (!CGPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_mkversion, sizeof(m_mkversion));
		cfile.Write(&m_mkflags, sizeof(m_mkflags));
		cfile.Write(&m_delaytime, sizeof(m_delaytime));
		cfile.Write(&m_meastime, sizeof(m_meastime));
		cfile.Write(&m_intervaltime, sizeof(m_intervaltime));

		cfile.Write(&m_numreps, sizeof(m_numreps));
		cfile.Write(&m_numsamps, sizeof(m_numsamps));
		cfile.Write(&m_nummeasurements, sizeof(m_nummeasurements));


		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}


bool CMKPPS::Read(CFile& cfile)
{
	try
	{
		if (!CGPPS::Read(cfile))
		{
			return false;
		}
		if (cfile.Read(&m_mkversion, sizeof(m_mkversion)) != sizeof(m_mkversion))
		{
			return false;
		}
		if (m_mkversion != 1)
		{
			return false;
		}

		// (cfile.Read(&m_caflags, sizeof(m_caflags)) == sizeof(m_caflags))
		if (!((cfile.Read(&m_mkflags, sizeof(m_mkflags)) == sizeof(m_mkflags)) &&
			  (cfile.Read(&m_delaytime, sizeof(m_delaytime)) == sizeof(m_delaytime)) &&
		      (cfile.Read(&m_meastime, sizeof(m_meastime)) == sizeof(m_meastime)) &&
		      (cfile.Read(&m_intervaltime, sizeof(m_intervaltime)) == sizeof(m_intervaltime)) &&
		      (cfile.Read(&m_numreps, sizeof(m_numreps)) == sizeof(m_numreps)) &&
		      (cfile.Read(&m_numsamps, sizeof(m_numsamps)) == sizeof(m_numsamps)) &&
			  (cfile.Read(&m_nummeasurements, sizeof(m_nummeasurements)) == sizeof(m_nummeasurements)))) 
		{
			return false;
		}


		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}


bool CMKPPS::AllowNonNominalTimes() const
{
	return (m_mkflags & FLAG_ALLOWNONNOMINAL) ? true : false;
}


void CMKPPS::SetNonNominalTimes(bool use_nonnominal)
{
	if (use_nonnominal)
	{
		m_mkflags |= FLAG_ALLOWNONNOMINAL;
	}
	else
	{
		m_mkflags &= ~FLAG_ALLOWNONNOMINAL;
	}
}

bool CMKPPS::IsLumiTimeBase() const
{
	return (m_mkflags & FLAG_LUMITIMEBASE) ? true : false;
}

void CMKPPS::SetLumiTimeBase(bool is_lumitimebase)
{
	if (is_lumitimebase)
	{
		m_mkflags |= FLAG_LUMITIMEBASE;
	}
	else
	{
		m_mkflags &= ~FLAG_LUMITIMEBASE;
	}
}


void CMKPPS::SetNumSamps(UINT num_samps)
{
	if (num_samps > 0)
	{
		m_numsamps = num_samps;
	}
}

void CMKPPS::SetNumReps(UINT num_reps)
{
	if (num_reps > 0)
		m_numreps = num_reps;
}

