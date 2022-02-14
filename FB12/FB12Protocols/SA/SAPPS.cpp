// SAPPS.cpp: implementation of the CSAPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SA.h"
#include "SAPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSAPPS::CSAPPS() : m_saversion(1), m_delaytime(10), m_meastime(10), m_numreps(1), 
				   m_numsamps(1), m_saflags(0)
{
	SetBase(true);
	SetSaveAsable(true);
	SetUseRowOrder(true);
	SetUseStartButton(false);
	strcpy(m_protocolexe, "SA.exe");
	strcpy(m_protocolname, "Single Assay");
	strcpy(m_comment, "Single Assay protocol measures multiple samples and replicates.");
	m_samplelist.SetSize(m_numsamps);
}


CSAPPS::CSAPPS(const CSAPPS& pps) : CGPPS(pps)
{
	
	m_saversion = pps.m_saversion;
	m_saflags = pps.m_saflags;
	m_delaytime = pps.m_delaytime;
	m_meastime = pps.m_meastime;
	m_numreps = pps.m_numreps;
	m_numsamps = pps.m_numsamps;
	m_samplelist.SetSize(pps.m_numsamps);
	m_samplelist.Copy(pps.m_samplelist);
}


CSAPPS::~CSAPPS()
{

}


CSAPPS& CSAPPS::operator=(const CSAPPS& pps)
{

	if (this != &pps)
	{
		CGPPS::operator=(pps);
		m_saversion = pps.m_saversion;
		m_saflags = pps.m_saflags;
		m_delaytime = pps.m_delaytime;
		m_meastime = pps.m_meastime;
		m_numreps = pps.m_numreps;
		m_numsamps = pps.m_numsamps;
		//memcpy(&m_defaultname, &(pps.m_defaultname), sizeof(m_defaultname));
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(pps.m_numsamps);
		m_samplelist.Copy(pps.m_samplelist);
	}
	return *this;
}


bool CSAPPS::Write(CFile& cfile)
{
	try
	{
		if (!CGPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_saversion, sizeof(m_saversion));
		cfile.Write(&m_saflags, sizeof(m_saflags));
		cfile.Write(&m_delaytime, sizeof(m_delaytime));
		cfile.Write(&m_meastime, sizeof(m_meastime));
		cfile.Write(&m_numreps, sizeof(m_numreps));
		cfile.Write(&m_numsamps, sizeof(m_numsamps));
		//cfile.Write(&m_defaultname, sizeof(m_defaultname));
		UINT i;
		for(i=0; i < m_numsamps; i++)
		{
			cfile.Write((LPCTSTR)m_samplelist[i], m_samplelist[i].GetLength() + 1);
		}
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}


bool CSAPPS::Read(CFile& cfile)
{
	try
	{
		if (!CGPPS::Read(cfile))
		{
			return false;
		}
		if (cfile.Read(&m_saversion, sizeof(m_saversion)) != sizeof(m_saversion))
		{
			return false;
		}
		if (m_saversion != 1)
		{
			return false;
		}
		if (!((cfile.Read(&m_saflags, sizeof(m_saflags)) == sizeof(m_saflags)) &&
			  (cfile.Read(&m_delaytime, sizeof(m_delaytime)) == sizeof(m_delaytime)) &&
		      (cfile.Read(&m_meastime, sizeof(m_meastime)) == sizeof(m_meastime)) &&
		      (cfile.Read(&m_numreps, sizeof(m_numreps)) == sizeof(m_numreps)) &&
		      (cfile.Read(&m_numsamps, sizeof(m_numsamps)) == sizeof(m_numsamps)))) 
		{
			return false;
		}
		//cfile.Read(&m_defaultname, sizeof(m_defaultname));
		UINT i;
		CString s;
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(m_numsamps);

		for(i=0; i < m_numsamps; i++)
		{
			if(!Read_CString(cfile, s, SAMPLENAME_SIZE))
			{
				return false;
			}
			m_samplelist.SetAt(i, s);
		}

		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}


bool CSAPPS::Use95ConfCol() const
{
	return (m_saflags & FLAG_USE95CONFCOL) ? true : false;
}

bool CSAPPS::Use99ConfCol() const
{
	return (m_saflags & FLAG_USE99CONFCOL) ? true : false;
}

bool CSAPPS::UseRowOrder() const
{
	return (m_saflags & FLAG_ISROWORDER) ? true : false;
}

bool CSAPPS::IsFlexibleNumReps() const
{
	return (m_saflags & FLAG_FLEXNUMREPS) ? true : false;
}

bool CSAPPS::IsFlexibleNumSamps() const
{
	return (m_saflags & FLAG_FLEXNUMSAMPS) ? true : false;
}


void CSAPPS::SetUse95ConfCol(bool use_95confcol)
{
	if (use_95confcol)
	{
		m_saflags |= FLAG_USE95CONFCOL;
	}
	else
	{
		m_saflags &= ~FLAG_USE95CONFCOL;
	}
}

void CSAPPS::SetUse99ConfCol(bool use_99confcol)
{
	if (use_99confcol)
	{
		m_saflags |= FLAG_USE99CONFCOL;
	}
	else
	{
		m_saflags &= ~FLAG_USE99CONFCOL;
	}
}

void CSAPPS::SetUseRowOrder(bool use_roworder)
{
	if (use_roworder)
	{
		m_saflags |= FLAG_ISROWORDER;
	}
	else
	{
		m_saflags &= ~FLAG_ISROWORDER;
	}
}

void CSAPPS::SetFlexibleNumReps(bool is_flexiblenumreps)
{
	if (is_flexiblenumreps)
	{
		m_saflags |= FLAG_FLEXNUMREPS;
	}
	else
	{
		m_saflags &= ~FLAG_FLEXNUMREPS;
	}
}

void CSAPPS::SetFlexibleNumSamps(bool is_flexiblenumsamps)
{
	if (is_flexiblenumsamps)
	{
		m_saflags |= FLAG_FLEXNUMSAMPS;
	}
	else
	{
		m_saflags &= ~FLAG_FLEXNUMSAMPS;
	}
}

void CSAPPS::SetNumSamps(UINT num_samps)
{
	if (num_samps > 0)
	{
		m_numsamps = num_samps;
		m_samplelist.SetSize(num_samps);
	}
}

void CSAPPS::SetNumReps(UINT num_reps)
{
	if (num_reps > 0)
		m_numreps = num_reps;
}


void CSAPPS::AddSample(LPCTSTR sample, UINT pos)
{
	if ((sample != NULL) && (pos > 0))
	{
		CString s;
		s = sample;
		// strncpy(s.sampname, sample, SAMPLENAME_SIZE - 1 );
		//s.sampname[SAMPLENAME_SIZE - 1] = '\0';
	
		m_samplelist.SetAt(pos-1, s);
		//m_numsamps++;
		//m_samplelist.SetSize(m_numsamps);

		//m_samplelist.Add(s);
	}
}


void CSAPPS::ResetSampList()
{
	m_samplelist.RemoveAll();
	m_numsamps = 1;
	m_samplelist.SetSize(1);
}

bool CSAPPS::Read_CString(CFile & cfile, CString & str, int size)
{
	//TCHAR tmp_str[size];
	TCHAR ch;

	TCHAR *tmp_str = new TCHAR[size];

	int index = 0;
	do
	{
		if (cfile.Read(&ch, sizeof(ch)) != sizeof(ch))
		{
			delete [] tmp_str;
			return false;
		}
		tmp_str[index++] = ch;
	} while (ch != 0);

	str = tmp_str;
	delete [] tmp_str;
	return true;
}

void CSAPPS::FillEmptySamples()
{
	int i;
	for (i = 0; i < m_samplelist.GetSize(); i++)
	{
		if (m_samplelist[i].IsEmpty())
		{
			m_samplelist[i].Format("Sample %ld", i + 1);
		}
	}
}
