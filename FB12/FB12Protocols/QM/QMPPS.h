// QMPPS.h: interface for the CQMPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QMPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_QMPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PPS.h"

class CQMPPS : public CPPS  
{
public:
	// Constructors and destructor
	CQMPPS();
	CQMPPS(const CQMPPS& pps);
	virtual ~CQMPPS();

	// Serializers
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);

	// Operators
	CQMPPS& operator=(const CQMPPS& pps);

	// Member variables
	WORD m_qmversion;	// the Quick Measure version
	DWORD m_delaytime;	// in deciseconds
	DWORD m_meastime;	// in deciseconds
};

#endif // !defined(AFX_QMPPS_H__1B400442_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
