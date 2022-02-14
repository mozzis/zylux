// GPPS.cpp: implementation of the CGPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GPPS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPPS::CGPPS(): m_gversion(2), m_gflags(0), m_cell_col(0), m_cell_row(0)
{
}

CGPPS::CGPPS(const CGPPS& pps) //: CPPS(pps)
{
	*this = pps;
}

CGPPS::~CGPPS()
{

}


CGPPS& CGPPS::operator=(const CGPPS& pps)
{
	if (this != &pps)
	{
		CPPS::operator=(pps);
		m_gversion = pps.m_gversion;
		m_gflags = pps.m_gflags;
		m_macroname = pps.m_macroname;
		m_workbook = pps.m_workbook;
		m_worksheet = pps.m_worksheet;
		m_cell_col = pps.m_cell_col;
		m_cell_row = pps.m_cell_row;
	}
	return *this;
}


bool CGPPS::Write(CFile& cfile)
{
	try
	{
		if (!CPPS::Write(cfile))
		{
			return false;
		}
		cfile.Write(&m_gversion, sizeof(m_gversion));
		cfile.Write(&m_gflags, sizeof(m_gflags));
		cfile.Write((LPCTSTR)m_macroname, m_macroname.GetLength() + 1);
		cfile.Write((LPCTSTR)m_workbook, m_workbook.GetLength() + 1);
		cfile.Write((LPCTSTR)m_worksheet, m_worksheet.GetLength() + 1);
		cfile.Write(&m_cell_col, sizeof(m_cell_col));
		cfile.Write(&m_cell_row, sizeof(m_cell_row));
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}

bool CGPPS::Read(CFile& cfile)
{
	try
	{
		if ((CPPS::Read(cfile)) &&
			(cfile.Read(&m_gversion, sizeof(m_gversion)) == sizeof(m_gversion)) &&
			(cfile.Read(&m_gflags, sizeof(m_gflags)) == sizeof(m_gflags)))
		{
			if (m_gversion == 1)
			{
				// Convert version 1 to version 2
				m_gversion = 2;
				TCHAR m_macro[MACRONAME_SIZE];
				if (cfile.Read(m_macro, sizeof(m_macro)) == sizeof(m_macro))
				{
					m_macroname = m_macro;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if ((m_gversion == 2) &&
				ReadCString(cfile, m_macroname) &&
				ReadCString(cfile, m_workbook) &&
				ReadCString(cfile, m_worksheet) &&
				(cfile.Read(&m_cell_col, sizeof(m_cell_col)) == sizeof(m_cell_col)) &&
				(cfile.Read(&m_cell_row, sizeof(m_cell_row)) == sizeof(m_cell_row)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}

bool CGPPS::UseStartButton() const
{
	return (m_gflags & FLAG_USESTARTBUTTON) ? true : false;
}

bool CGPPS::UseBackground() const
{
	return (m_gflags & FLAG_USEBACKGROUND) ? true : false;
}

bool CGPPS::UseTimestamps() const
{
	return (m_gflags & FLAG_USETIMESTAMPS) ? true : false;
}

bool CGPPS::AutoSendToExcel() const
{
	return (m_gflags & FLAG_AUTOSENDTOEXCEL) ? true : false;
}

void CGPPS::SetUseStartButton(bool use_startbutton)
{
	if (use_startbutton)
	{
		m_gflags |= FLAG_USESTARTBUTTON;
	}
	else
	{
		m_gflags &= ~FLAG_USESTARTBUTTON;
	}
}

void CGPPS::SetUseBackground(bool use_background)
{
	if (use_background)
	{
		m_gflags |= FLAG_USEBACKGROUND;
	}
	else
	{
		m_gflags &= ~FLAG_USEBACKGROUND;
	}

}

void CGPPS::SetUseTimestamps(bool use_timestamps)
{
	if (use_timestamps)
	{
		m_gflags |= FLAG_USETIMESTAMPS;
	}
	else
	{
		m_gflags &= ~FLAG_USETIMESTAMPS;
	}

}

void CGPPS::SetAutoSendToExcel(bool autosend)
{
	if (autosend)
	{
		m_gflags |= FLAG_AUTOSENDTOEXCEL;
	}
	else
	{
		m_gflags &= ~FLAG_AUTOSENDTOEXCEL;
	}

}

bool CGPPS::ReadCString(CFile& cfile, CString& str)
{
	TCHAR ch;

	const CHUNK_SIZE = 64;
	TCHAR *tmp_str = new TCHAR[CHUNK_SIZE + 1];
	tmp_str[CHUNK_SIZE] = 0;

	str.Empty();
	do
	{
		int index = 0;
		do
		{
			try
			{
				if (cfile.Read(&ch, sizeof(ch)) != sizeof(ch))
				{
					delete [] tmp_str;
					return false;
				}
				tmp_str[index++] = ch;
			}
			catch(CFileException *e)
			{
				e->Delete();
				delete [] tmp_str;
				return false;
			}
		} while ((index < CHUNK_SIZE) && (ch != 0));
		str += tmp_str;
	} while (ch != 0);

	delete [] tmp_str;
	return true;
}
