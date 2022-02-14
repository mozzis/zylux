// MKPPS.h: interface for the CMKPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_MKPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GPPS.h"


class CMKPPS : public CGPPS  
{
public:
	WORD m_mkversion;
	enum
	{
		FLAG_LUMITIMEBASE		= 0x00000001,	// Use luminometer instead of
												// computer as time basis.
		FLAG_ALLOWNONNOMINAL	= 0x00000010,	// Allow measurements at times
												// other than nominal times.
	};

	WORD m_mkflags;

	DWORD m_delaytime;
	DWORD m_meastime;
	DWORD m_intervaltime;
	//DWORD m_durationtime;

	UINT m_nummeasurements;

	UINT m_numreps;
	UINT m_numsamps;



	// Constructors and Destructors
	CMKPPS();
	CMKPPS(const CMKPPS& pps);
	virtual ~CMKPPS();

	// Operators
	CMKPPS	&operator=(const CMKPPS& pps);

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);

	bool AllowNonNominalTimes() const;
	bool IsLumiTimeBase() const;

	// Mutators
	void SetNumSamps(UINT num_samps);
	void SetNumReps(UINT num_reps);
	void SetNonNominalTimes(bool use_nonnominal);
	void SetLumiTimeBase(bool is_lumitimebase);

};

#endif // !defined(AFX_MKPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
