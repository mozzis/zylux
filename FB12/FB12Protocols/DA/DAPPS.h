// DAPPS.h: interface for the CDAPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DAPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GPPS.h"

class CDAPPS : public CGPPS
{
public:
	void FillEmptySamples();
	// Constructors and destructor
	CDAPPS();
	CDAPPS(const CDAPPS& pps);
	virtual ~CDAPPS();

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);
	bool Read_CString(CFile& cfile, CString & str, int size);

	// Operators
	CDAPPS& operator=(const CDAPPS& pps);

	//Mutators
	void SetNumSamps(UINT num_samps);
	void SetNumReps(UINT num_reps);
	void AddSample(LPCTSTR sample, int pos);
	void ResetSampList();

	// Member variables
	WORD m_DAversion;		// the Dual Assay version
	DWORD m_delaytime_a;	// in deciseconds
	DWORD m_meastime_a;		// in deciseconds
	DWORD m_delaytime_b;	// in deciseconds
	DWORD m_meastime_b;		// in deciseconds
	UINT m_numsamples;		// max 65535
	UINT m_numreplicates;	// max 65535
	// The list of sample names
	CArray<CString, CString&> m_samplelist;

	enum
	{
		XFORM_AMINUSB,
		XFORM_BMINUSA,
		XFORM_ADIVB,
		XFORM_BDIVA,
		XFORM_ADIV_BMINUSA,

		XFORM_MAX
	};
	BYTE m_transform;
	enum
	{
		ORDER_ABAB,
		ORDER_AABB,

		ORDER_MAX
	};
	BYTE m_order;
};

#endif // !defined(AFX_DAPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
