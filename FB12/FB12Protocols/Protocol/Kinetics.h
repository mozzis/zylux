// Kinetics.h: interface for the CKinetics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KINETICS_H__9C9059E1_1312_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_KINETICS_H__9C9059E1_1312_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

class CKinetics  
{
public:
	long m_num_kinetics;
	long m_max_kinetics;
	CKinetics(long max_kinetics);
	virtual ~CKinetics();

	void Add(long rlu);
	void Reset();

	long GetMin() const;
	long GetMax() const;
	long GetMean() const;
	CString GetMeanString() const;

	bool SaveAsText();

	CArray<long,long> m_RLUs;
	long m_min;
	long m_max;
	__int64 m_RLU_sum;
};

#endif // !defined(AFX_KINETICS_H__9C9059E1_1312_11D1_AE1E_0080C80C9F0E__INCLUDED_)
