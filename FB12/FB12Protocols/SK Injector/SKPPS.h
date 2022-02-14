// SKPPS.h: interface for the CSKPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SKPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GPPS.h"
#include "InjectorParams.h"	// Added by ClassView

class CSKPPS : public CGPPS
{
public:
	void SortInjections();
	int GetTotalInjectVolume(BYTE dev_num = 1);
	// Constructors and destructor
	CSKPPS();
	CSKPPS(const CSKPPS& pps);
	virtual ~CSKPPS();

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);

	// Operators
	CSKPPS& operator=(const CSKPPS& pps);

	// Member variables
	WORD m_SKversion;		// the Single Kinetics version

	enum
	{
		MAX_INJECTIONS = 5,
	};

	enum
	{
		FLAG_LUMITIMEBASE = 1,	// use luminometer instead of
								// computer as time basis
	};
	WORD m_SKflags;
	DWORD m_delaytime;		// in deciseconds
	DWORD m_meastime;		// in deciseconds
	DWORD m_intervaltime;	// in deciseconds
	UINT m_numsamples;		// max 0x7fff (32767)
	UINT m_numreplicates;	// max 0x7fff (32767)

	CInjectorParams m_injections[MAX_INJECTIONS];


	bool IsLumiTimeBase() const;
	void SetLumiTimeBase(bool is_lumitimebase);
};

#endif // !defined(AFX_SKPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
