// PPS.h: interface for the CPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPS_H__1B400441_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PPS_H__1B400441_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

class CPPS  
{
public:
	WORD m_version;
	DWORD m_checksum;
	enum
	{
		// bits for m_flags
		FLAG_SAVEASABLE	= 0x00000001,
		FLAG_SAVEABLE	= 0x00000002,
		FLAG_RUNABLE	= 0x00000004,
		FLAG_DELETEABLE	= 0x00000008,
		FLAG_BASE		= 0x00000010,	// is a base protocol

		// string limits
		PROTOCOLEXE_SIZE = 32,
		PROTOCOLNAME_SIZE = 32,
		COMMENT_SIZE = 256,
	};
	WORD m_flags;
	char m_protocolexe[PROTOCOLEXE_SIZE];
	char m_protocolname[PROTOCOLNAME_SIZE];
	char m_comment[COMMENT_SIZE];

	// Constructors and destructor
	CPPS();
	CPPS(const CPPS& pps);	
	virtual ~CPPS();

	// Serializers
	virtual bool Write(CFile& cfile);	// low level
	virtual bool Read(CFile& cfile);	// low level
	bool Save(LPCTSTR filename);		// high level
	bool SaveAs(LPCTSTR filename,
		bool allow_base_overwrite);		// high level
	bool Load(LPCTSTR filename);		// high level

	// Accessors
	bool IsBase() const;
	bool IsDeleteable() const;
	bool IsRunable() const;
	bool IsSaveAsable() const;
	bool IsSaveable() const;

	// Mutators
	void SetBase(bool is_base);
	void SetDeleteable(bool is_deleteable);
	void SetRunable(bool is_runable);
	void SetSaveable(bool is_saveable);
	void SetSaveAsable(bool is_saveasable);

	// Operators
	CPPS& operator=(const CPPS& pps);

	// Helpers
	static bool IsFileBase(LPCTSTR protocol_name);
	static int BuildProtocolArray(CArray<CString, CString&>& protocols,
		bool extensions = false);
};

#endif // !defined(AFX_PPS_H__1B400441_17FD_11D1_AE1E_0080C80C9F0E__INCLUDED_)
