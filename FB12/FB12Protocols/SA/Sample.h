// Sample.h: interface for the CSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLE_H__7EBBDE81_34C8_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_SAMPLE_H__7EBBDE81_34C8_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Replicate.h"
#include <afxtempl.h>

class CSample  
{
public:
	CSample();
	virtual ~CSample();

	CArray<CReplicate, CReplicate&> m_replicates;
	double m_average;
	double m_precision;
	double m_net;
	double m_precision_net;
	bool   m_precision_overflow;
	bool   m_netprecision_overflow;
	//double m_99Conf;
	//double m_95Conf;
	static long m_background;

	void SetReplicate(int rep_num, long value);
	void ClearReplicate(int rep_num);
	void Recalculate();
	int NumReplicatesUsed();


};
#endif // !defined(AFX_SAMPLE_H__7EBBDE81_34C8_11D1_8C08_00400516EF5A__INCLUDED_)
