// Options.h: interface for the COptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_)
#define AFX_OPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COptions  
{
public:
	CString m_version;
	CString m_workdir;
	CString m_maindir;
	void Read();
	void Write();
	long m_volume;
	bool m_injector;
	bool m_beep;
	short m_injectport;
	short m_lumiport;
	long m_lumibaud;
	COptions();
	virtual ~COptions();

};

#endif // !defined(AFX_OPTIONS_H__86D2A821_D544_11D1_AE23_0080C80C9F0E__INCLUDED_)
