// GPPS.h: interface for the CGPPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPPS_H__5D1B6921_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_GPPS_H__5D1B6921_1A48_11D1_87A6_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PPS.h"

class CGPPS : public CPPS
{
public:
	bool ReadCString(CFile& cfile, CString& str);
	WORD m_gversion;

	enum
	{
		// bits for m_gflags
		FLAG_USESTARTBUTTON	 = 0x0001,
		FLAG_USEBACKGROUND	 = 0x0002,
		FLAG_USETIMESTAMPS	 = 0x0004,
		FLAG_AUTOSENDTOEXCEL = 0x0008,

		// string sizes
		MACRONAME_SIZE		= 64,
		SAMPLENAME_SIZE     = 32,
	};

	WORD m_gflags;
	CString m_macroname;	// Excel macro name
	CString m_workbook;		// path to Excel workbook
	CString m_worksheet;	// Excel worksheet name
	WORD m_cell_col;		// Excel cell column 0 - 255 -> A - IV
	WORD m_cell_row;		// Excel cell row 0 - 65535 -> 1 - 65536

	// Constructors and Destructors
	CGPPS();
	CGPPS(const CGPPS& pps);
	virtual ~CGPPS();

	CGPPS& operator=(const CGPPS& pps);
	virtual bool Write(CFile& cfile);
	virtual bool Read(CFile& cfile);
	bool UseStartButton() const;
	bool UseBackground() const;
	bool UseTimestamps() const;
	bool AutoSendToExcel() const;
	void SetUseStartButton(bool use_startbutton);
	void SetUseBackground(bool use_background);
	void SetUseTimestamps(bool use_timestamps);
	void SetAutoSendToExcel(bool autosend);
};

#endif // !defined(AFX_GPPS_H__5D1B6921_1A48_11D1_87A6_00400516EF5A__INCLUDED_)
