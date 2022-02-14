// SKOPTIONS.h: interface for the CSKOptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKOPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_)
#define AFX_SKOPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSKOptions
{
public:
	int m_showwarning;
	void Read();
	void Write();
	int m_speed;
	int m_speed2;
	long m_volume;
	long m_volume2;
	BYTE m_num_injectors;
	short m_injectport;
	CSKOptions();
	virtual ~CSKOptions();

};

#endif // !defined(AFX_SKOPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_)
