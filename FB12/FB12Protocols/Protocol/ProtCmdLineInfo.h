// ProtCmdLineInfo.h: interface for the CProtCmdLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ProtCmdLineInfo_H__085BB941_0F34_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_ProtCmdLineInfo_H__085BB941_0F34_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CProtCmdLineInfo : public CCommandLineInfo  
{
public:
	//long m_baud;
	//short m_port;
	int m_mode;
	//CString m_workdir;
	//bool m_beep;

	CProtCmdLineInfo();
	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

#endif // !defined(AFX_ProtCmdLineInfo_H__085BB941_0F34_11D1_AE1E_0080C80C9F0E__INCLUDED_)
