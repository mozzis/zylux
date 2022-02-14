// SCSerialNumber.h: interface for the CSCSerialNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCSERIALNUMBER_H__64AC7B41_6F05_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SCSERIALNUMBER_H__64AC7B41_6F05_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSCSerialNumber  
{
public:
	enum
	{
		SERIALNUM_MIN = 1,
		SERIALNUM_MAX = 100000,
		c1 = 95,			// constant multiplier
		c2 = 78,			// constant multiplier
		cx1 = 0x00246DC5,	// constant xor-er
		cx2 = 0x009F362B	// constant xor-er
	};

	static void MakeSerialFile(LPCTSTR serial_filename = NULL, bool use_dialog = true);
	//static bool RequestSerialString();
	static CString MakeSerialString(int serial_number);
	static int ExtractSerialNumber(CString serial_string);
	CSCSerialNumber();
	virtual ~CSCSerialNumber();

};

#endif // !defined(AFX_SCSERIALNUMBER_H__64AC7B41_6F05_11D1_AE1E_0080C80C9F0E__INCLUDED_)
