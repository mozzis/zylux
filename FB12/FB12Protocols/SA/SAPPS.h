// SAPPS.h: interface for the CSAPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_SAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GPPS.h"


class CSAPPS : public CGPPS  
{
public:
	void FillEmptySamples();
	WORD m_saversion;
	enum
	{
		// bits for m_saflags
		FLAG_USE95CONFCOL	= 0x00000001,
		FLAG_USE99CONFCOL	= 0x00000002,
		FLAG_FLEXNUMREPS	= 0x00000004,
		FLAG_FLEXNUMSAMPS	= 0x00000008,
		FLAG_ISROWORDER		= 0x00000010,
	};

	WORD m_saflags;
	DWORD m_delaytime;
	DWORD m_meastime;
	UINT m_numreps;
	UINT m_numsamps;
	CArray<CString, CString&> m_samplelist;

	// Constructors and Destructors
	CSAPPS();
	CSAPPS(const CSAPPS& pps);
	virtual ~CSAPPS();

	// Operators
	CSAPPS	&operator=(const CSAPPS& pps);

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);

	// Accessors
	bool Use95ConfCol() const;
	bool Use99ConfCol() const;
	bool UseRowOrder() const;
	bool IsFlexibleNumReps() const;
	bool IsFlexibleNumSamps() const;

	// Mutators
	void SetUse95ConfCol(bool use_95confcol);
	void SetUse99ConfCol(bool use_99confcol);
	void SetUseRowOrder(bool use_roworder);
	void SetFlexibleNumReps(bool is_flexiblenumreps);
	void SetFlexibleNumSamps(bool is_flexiblenumsamps);
	void SetNumSamps(UINT num_samps);
	void SetNumReps(UINT num_reps);
	void AddSample(LPCTSTR sample, UINT pos);
	void ResetSampList();
	bool Read_CString(CFile & cfile, CString & str, int size);

};

#endif // !defined(AFX_SAPPS_H__5D1B6922_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
