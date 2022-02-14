// DAPPS.cpp: implementation of the CDAPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DAPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDAPPS::CDAPPS() : m_DAversion(1), m_delaytime_a(10), m_meastime_a(10),
	m_delaytime_b(10), m_meastime_b(10), m_numsamples(1),
	m_numreplicates(1), m_order(ORDER_ABAB), m_transform(XFORM_AMINUSB)
{
	SetBase(true);
	SetSaveAsable(true);
	SetUseStartButton(false);
	strcpy(m_protocolexe, "DA.exe");
	strcpy(m_protocolname, "Dual Assay");
	strcpy(m_comment, "Dual Assay computes the transform of net values from each sample, which has two series of replicates.");
	m_samplelist.SetSize(m_numsamples);
}


CDAPPS::CDAPPS(const CDAPPS& pps)
{
	*this = pps;
}

CDAPPS::~CDAPPS()
{

}

bool CDAPPS::Write(CFile& cfile)
{
	try
	{
		if (!CGPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_DAversion, sizeof(m_DAversion));
		cfile.Write(&m_delaytime_a, sizeof(m_delaytime_a));
		cfile.Write(&m_meastime_a, sizeof(m_meastime_a));
		cfile.Write(&m_delaytime_b, sizeof(m_delaytime_b));
		cfile.Write(&m_meastime_b, sizeof(m_meastime_b));
		cfile.Write(&m_numsamples, sizeof(m_numsamples));
		cfile.Write(&m_numreplicates, sizeof(m_numreplicates));
		cfile.Write(&m_order, sizeof(m_order));
		cfile.Write(&m_transform, sizeof(m_transform));

		UINT i;
		for(i = 0; i < m_numsamples; i++)
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

bool CDAPPS::Read(CFile& cfile)
{
	try
	{
		if (!((CGPPS::Read(cfile)) &&
			(cfile.Read(&m_DAversion, sizeof(m_DAversion)) == sizeof(m_DAversion)) &&
			(m_DAversion == 1) &&
			(cfile.Read(&m_delaytime_a, sizeof(m_delaytime_a)) == sizeof(m_delaytime_a)) &&
			(cfile.Read(&m_meastime_a, sizeof(m_meastime_a)) == sizeof(m_meastime_a)) &&
			(cfile.Read(&m_delaytime_b, sizeof(m_delaytime_b)) == sizeof(m_delaytime_b)) &&
			(cfile.Read(&m_meastime_b, sizeof(m_meastime_b)) == sizeof(m_meastime_b)) &&
			(cfile.Read(&m_numsamples, sizeof(m_numsamples)) == sizeof(m_numsamples)) &&
			(cfile.Read(&m_numreplicates, sizeof(m_numreplicates)) == sizeof(m_numreplicates)) &&
			(cfile.Read(&m_order, sizeof(m_order)) == sizeof(m_order)) &&
			(cfile.Read(&m_transform, sizeof(m_transform)) == sizeof(m_transform))))
		{
			return false;
		}

		UINT i;
		CString s;
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(m_numsamples);

		for(i = 0; i < m_numsamples; i++)
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


CDAPPS& CDAPPS::operator=(const CDAPPS& pps)
{
	if (this != &pps)
	{
		CGPPS::operator=(pps);
		m_DAversion = pps.m_DAversion;
		m_delaytime_a = pps.m_delaytime_a;
		m_meastime_a = pps.m_meastime_a;
		m_delaytime_b = pps.m_delaytime_b;
		m_meastime_b = pps.m_meastime_b;
		m_numsamples = pps.m_numsamples;
		m_numreplicates = pps.m_numreplicates;
		m_order = pps.m_order;
		m_transform = pps.m_transform;
		m_samplelist.RemoveAll();
		m_samplelist.SetSize(pps.m_numsamples);
		m_samplelist.Copy(pps.m_samplelist);
	}

	return *this;
}


void CDAPPS::SetNumSamps(UINT num_samps)
{
	if (num_samps > 0)
	{
		m_numsamples = num_samps;
		m_samplelist.SetSize(num_samps);
	}
}

void CDAPPS::SetNumReps(UINT num_reps)
{
	if (num_reps > 0)
		m_numreplicates = num_reps;
}

void CDAPPS::AddSample(LPCTSTR sample, int pos)
{
	if ((sample != NULL) && (pos > 0))
	{
		CString s;
		s = sample;
	
		m_samplelist.SetAt(pos-1, s);
	}
}


void CDAPPS::ResetSampList()
{
	m_samplelist.RemoveAll();
	m_numsamples = 1;
	m_samplelist.SetSize(1);
}


bool CDAPPS::Read_CString(CFile & cfile, CString & str, int size)
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

void CDAPPS::FillEmptySamples()
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
