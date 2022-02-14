// CAPPS.cpp: implementation of the CCAPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CA.h"
#include "CAPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCAPPS::CCAPPS() : m_caversion(1), m_delaytime(10), m_meastime(10), m_numreps(1), 
				   m_numsamps(1), m_numnegreps(1), m_numposreps(1), m_lowoffset(0),
				   m_highoffset(0), m_lowfactor(1.0), m_highfactor(0.0), m_low_lposfactor(0.0),
				   m_high_lposfactor(1.0)
{
	SetBase(true);
	SetSaveAsable(true);
	SetUseStartButton(false);
	strcpy(m_protocolexe, "CA.exe");
	strcpy(m_protocolname, "Cut-off Assay");
	strcpy(m_comment, "Cut-off Assay protocol categorizes multiple samples and replicates by qualitative ranges.");
	m_samplelist.SetSize(m_numsamps);
	m_negresult = "NEG";
	m_posresult = "POS";
	m_equivresult = "+/-";
}


CCAPPS::CCAPPS(const CCAPPS& pps) : CGPPS(pps)
{
	*this = pps;
}


CCAPPS::~CCAPPS()
{

}


CCAPPS& CCAPPS::operator=(const CCAPPS& pps)
{

	if (this != &pps)
	{
		CGPPS::operator=(pps);
		m_caversion = pps.m_caversion;
		//m_caflags = pps.m_caflags;
		m_delaytime = pps.m_delaytime;
		m_meastime = pps.m_meastime;
		m_numnegreps = pps.m_numnegreps;
		m_numposreps = pps.m_numposreps;
		m_numreps = pps.m_numreps;
		m_numsamps = pps.m_numsamps;
		m_lowoffset = pps.m_lowoffset;
		m_highoffset = pps.m_highoffset;
		m_lowfactor = pps.m_lowfactor;
		m_highfactor = pps.m_highfactor;
		m_low_lposfactor = pps.m_low_lposfactor;
		m_high_lposfactor = pps.m_high_lposfactor;
		m_negresult = pps.m_negresult;
		m_posresult = pps.m_posresult;
		m_equivresult = pps.m_equivresult;
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(pps.m_numsamps);
		m_samplelist.Copy(pps.m_samplelist);
	}
	return *this;
}


bool CCAPPS::Write(CFile& cfile)
{
	try
	{
		if (!CGPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_caversion, sizeof(m_caversion));
		//cfile.Write(&m_caflags, sizeof(m_caflags));
		cfile.Write(&m_delaytime, sizeof(m_delaytime));
		cfile.Write(&m_meastime, sizeof(m_meastime));

		cfile.Write(&m_numnegreps, sizeof(m_numnegreps));
		cfile.Write(&m_numposreps, sizeof(m_numposreps));
		cfile.Write(&m_numreps, sizeof(m_numreps));
		cfile.Write(&m_numsamps, sizeof(m_numsamps));

		cfile.Write(&m_lowoffset, sizeof(m_lowoffset));
		cfile.Write(&m_highoffset, sizeof(m_highoffset));
		cfile.Write(&m_lowfactor, sizeof(m_lowfactor));
		cfile.Write(&m_highfactor, sizeof(m_highfactor));
		cfile.Write(&m_low_lposfactor, sizeof(m_low_lposfactor));
		cfile.Write(&m_high_lposfactor, sizeof(m_high_lposfactor));

		cfile.Write((LPCTSTR)m_negresult, m_negresult.GetLength() + 1);
		cfile.Write((LPCTSTR)m_posresult, m_posresult.GetLength() + 1);
		cfile.Write((LPCTSTR)m_equivresult, m_equivresult.GetLength() + 1);


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


bool CCAPPS::Read(CFile& cfile)
{
	try
	{
		if (!CGPPS::Read(cfile))
		{
			return false;
		}
		if (cfile.Read(&m_caversion, sizeof(m_caversion)) != sizeof(m_caversion))
		{
			return false;
		}
		if (m_caversion != 1)
		{
			return false;
		}

		// (cfile.Read(&m_caflags, sizeof(m_caflags)) == sizeof(m_caflags))
		if (!((cfile.Read(&m_delaytime, sizeof(m_delaytime)) == sizeof(m_delaytime)) &&
		      (cfile.Read(&m_meastime, sizeof(m_meastime)) == sizeof(m_meastime)) &&
		      (cfile.Read(&m_numnegreps, sizeof(m_numnegreps)) == sizeof(m_numnegreps)) &&
		      (cfile.Read(&m_numposreps, sizeof(m_numposreps)) == sizeof(m_numposreps)) &&
		      (cfile.Read(&m_numreps, sizeof(m_numreps)) == sizeof(m_numreps)) &&
		      (cfile.Read(&m_numsamps, sizeof(m_numsamps)) == sizeof(m_numsamps)) &&
		      (cfile.Read(&m_lowoffset, sizeof(m_lowoffset)) == sizeof(m_lowoffset)) &&
		      (cfile.Read(&m_highoffset, sizeof(m_highoffset)) == sizeof(m_highoffset)) &&
		      (cfile.Read(&m_lowfactor, sizeof(m_lowfactor)) == sizeof(m_lowfactor)) &&
		      (cfile.Read(&m_highfactor, sizeof(m_highfactor)) == sizeof(m_highfactor)) &&
		      (cfile.Read(&m_low_lposfactor, sizeof(m_low_lposfactor)) == sizeof(m_low_lposfactor)) &&
		      (cfile.Read(&m_high_lposfactor, sizeof(m_high_lposfactor)) == sizeof(m_high_lposfactor)))) 
		{
			return false;
		}

		if (!Read_CString(cfile, m_negresult, RESULTSTEXT_SIZE))
		{
			return false;
		}
		if (!Read_CString(cfile, m_posresult, RESULTSTEXT_SIZE))
		{
			return false;
		}

		if (!Read_CString(cfile, m_equivresult, RESULTSTEXT_SIZE))
		{
			return false;
		}


		int i;
		CString s;
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(m_numsamps);

		for(i=0; i < (int)m_numsamps; i++)
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



void CCAPPS::SetNumSamps(UINT num_samps)
{
	if (num_samps > 0)
	{
		m_numsamps = num_samps;
		m_samplelist.SetSize(num_samps);
	}
}

void CCAPPS::SetNumReps(UINT num_reps)
{
	if (num_reps > 0)
		m_numreps = num_reps;
}

void CCAPPS::SetNegReps(UINT num_negreps)
{
	//if (num_negreps > 0)
		m_numnegreps = num_negreps;
}

void CCAPPS::SetPosReps(UINT num_posreps)
{
	//if (num_posreps > 0)
		m_numposreps = num_posreps;
}

void CCAPPS::AddSample(LPCTSTR sample, int pos)
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


void CCAPPS::ResetSampList()
{
	m_samplelist.RemoveAll();
	m_numsamps = 1;
	m_samplelist.SetSize(1);
}


bool CCAPPS::Read_CString(CFile & cfile, CString & str, int size)
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

void CCAPPS::FillEmptySamples()
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
