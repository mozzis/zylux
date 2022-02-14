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
	void RecalculateB();
	void RecalculateA();
	void RecalculateTransform();
	void Recalculate();
	int GetNumReplicates(int series);
	void SetReplicate(int series, int replicate, long RLU);
	void ClearReplicate(int series, int replicate);
	CSample();
	virtual ~CSample();

	enum
	{
		SERIES_A,
		SERIES_B,
	};

	// Series A
	CArray<CReplicate, CReplicate&> m_replicates_a;
	double m_average_a;
	double m_precision_a;
	bool m_precision_a_overflow;
	double m_net_a;
	double m_precision_net_a;
	bool m_precision_net_a_overflow;

	// Series B
	CArray<CReplicate, CReplicate&> m_replicates_b;
	double m_average_b;
	double m_precision_b;
	bool m_precision_b_overflow;
	double m_net_b;
	double m_precision_net_b;
	bool m_precision_net_b_overflow;

	// Transform
	double m_xnet_a;
	bool m_xnet_a_overflow;
	double m_xnet_b;
	double m_xform;
	bool m_xform_overflow;
	double m_precision_xform;
	bool m_precision_xform_overflow;
	bool m_precision_xform_na;

	static long m_background_a;
	static long m_background_b;
	static bool m_normalize;
	static double m_normalize_value;
};

#endif // !defined(AFX_SAMPLE_H__2D9C9F01_3359_11D1_AE1E_0080C80C9F0E__INCLUDED_)
