// CAPPS.h: interface for the CCAPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_CAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GPPS.h"


class CCAPPS : public CGPPS  
{
public:
	void FillEmptySamples();
	WORD m_caversion;
	enum
	{

		RESULTSTEXT_SIZE	= 16
	};

	// WORD m_caflags;

	DWORD m_delaytime;
	DWORD m_meastime;

	// Positive and negative controls
	UINT m_numnegreps;
	UINT m_numposreps;

	// Analytes
	UINT m_numreps;
	UINT m_numsamps;

	// Calculation paramaters
	long	m_lowoffset;
	long	m_highoffset;
	double	m_lowfactor;
	double	m_highfactor;
	double	m_low_lposfactor;
	double	m_high_lposfactor;

	// Results Output Text
	CString m_negresult;
	CString m_posresult;
	CString m_equivresult;

	// The list of sample names
	CArray<CString, CString&> m_samplelist;


	// Constructors and Destructors
	CCAPPS();
	CCAPPS(const CCAPPS& pps);
	virtual ~CCAPPS();

	// Operators
	CCAPPS	&operator=(const CCAPPS& pps);

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);
	bool Read_CString(CFile& cfile, CString & str, int size);


	// Mutators
	void SetNumSamps(UINT num_samps);
	void SetNumReps(UINT num_reps);
	void SetPosReps(UINT num_posreps);
	void SetNegReps(UINT num_negreps);
	void AddSample(LPCTSTR sample, int pos);
	void ResetSampList();
};

#endif // !defined(AFX_CAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
