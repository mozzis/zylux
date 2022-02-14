// Sample.h: interface for the CSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLE_H__2D9C9F01_3359_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SAMPLE_H__2D9C9F01_3359_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Replicate.h"
#include <afxtempl.h>

class CSample  
{
public:
	void Recalculate();
	int GetNumReplicates();
	void SetReplicate(int replicate, long RLU);
	void ClearReplicate(int replicate);
	CSample();
	virtual ~CSample();

	CArray<CReplicate, CReplicate&> m_replicates;
	double m_average;
	double m_precision;
	bool m_precision_overflow;
	double m_net;
	double m_precision_net;
	bool m_precision_net_overflow;

	static long m_background;
};

#endif // !defined(AFX_SAMPLE_H__2D9C9F01_3359_11D1_AE1E_0080C80C9F0E__INCLUDED_)
