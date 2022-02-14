// InjectorParams.h: interface for the CInjectorParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INJECTORPARAMS_H__90873B41_D9D8_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_INJECTORPARAMS_H__90873B41_D9D8_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CInjectorParams  
{
public:
	CInjectorParams();
	CInjectorParams(const CInjectorParams &ip);
	virtual ~CInjectorParams();

	CInjectorParams & operator=(const CInjectorParams& ip);
	bool Write(CFile &cfile);
	bool Read(CFile &cfile);
	BYTE m_used;
	long m_volume;
	DWORD m_time;

};

#endif // !defined(AFX_INJECTORPARAMS_H__90873B41_D9D8_11D1_8C08_00400516EF5A__INCLUDED_)
