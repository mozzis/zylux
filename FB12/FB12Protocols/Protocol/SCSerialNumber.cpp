// SCSerialNumber.cpp: implementation of the CSCSerialNumber class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SCSerialNumber.h"
#include "General.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSCSerialNumber::CSCSerialNumber()
{

}

CSCSerialNumber::~CSCSerialNumber()
{

}

CString CSCSerialNumber::MakeSerialString(int serial_number)
{
	CString serial_string;
	LPTSTR hex_str = "0123456789BCDEFGHIJLNOPQSTUVWXYZ";

	if ((serial_number >= SERIALNUM_MIN) && (serial_number <= SERIALNUM_MAX))
	{
		__int64 n1 = (serial_number * c1) ^ cx1;
		__int64 n2 = (serial_number * c2) ^ cx2;
		__int64 n =
			(((n1 >> 20) & 0x0F) << 44) +	// 1
			(((n2 >>  0) & 0x0F) << 40) +	// 2
			(((n1 >> 12) & 0x0F) << 36) +	// 3
			(((n2 >>  8) & 0x0F) << 32) +	// 4
			(((n1 >>  4) & 0x0F) << 28) +	// 5
			(((n2 >> 16) & 0x0F) << 24) +	// 6
			(((n1 >>  0) & 0x0F) << 20) +	// A
			(((n2 >> 20) & 0x0F) << 16) +	// B
			(((n1 >>  8) & 0x0F) << 12) +	// C
			(((n2 >> 12) & 0x0F) <<  8) +	// D
			(((n1 >> 16) & 0x0F) <<  4) +	// E
			(((n2 >>  4) & 0x0F) <<  0);	// F
		serial_string += hex_str[(n >> 45) & 0x1F];	// 1
		serial_string += hex_str[(n >> 40) & 0x1F];	// 2
		serial_string += hex_str[(n >> 35) & 0x1F];	// 3
		serial_string += hex_str[(n >> 30) & 0x1F];	// 4
		serial_string += hex_str[(n >> 25) & 0x1F];	// 5
		serial_string += hex_str[(n >> 20) & 0x1F];	// 6
		serial_string += hex_str[(n >> 15) & 0x1F];	// 7
		serial_string += hex_str[(n >> 10) & 0x1F];	// 8
		serial_string += hex_str[(n >>  5) & 0x1F];	// 9
		serial_string += hex_str[(n >>  0) & 0x1F];	// 10
	}

	return serial_string;
}

int CSCSerialNumber::ExtractSerialNumber(CString serial_string)
{
	int serial_number = 0;

	serial_string.MakeUpper();
	if ((serial_string.GetLength() == 10) &&
		(serial_string.FindOneOf("MARK") == -1))
	{
		CString hex_str = "0123456789BCDEFGHIJLNOPQSTUVWXYZ";
		__int64 x =
			((__int64)hex_str.Find(serial_string[ 0]) << 45) +
			((__int64)hex_str.Find(serial_string[ 1]) << 40) +
			((__int64)hex_str.Find(serial_string[ 2]) << 35) +
			((__int64)hex_str.Find(serial_string[ 3]) << 30) +
			((__int64)hex_str.Find(serial_string[ 4]) << 25) +
			((__int64)hex_str.Find(serial_string[ 5]) << 20) +
			((__int64)hex_str.Find(serial_string[ 6]) << 15) +
			((__int64)hex_str.Find(serial_string[ 7]) << 10) +
			((__int64)hex_str.Find(serial_string[ 8]) <<  5) +
			((__int64)hex_str.Find(serial_string[ 9]) <<  0);
		int x1 = ((
			(((int)(x >> 44) & 0x0F) << 20) +
			(((int)(x >>  4) & 0x0F) << 16) +
			(((int)(x >> 36) & 0x0F) << 12) +
			(((int)(x >> 12) & 0x0F) <<  8) +
			(((int)(x >> 28) & 0x0F) <<  4) +
			(((int)(x >> 20) & 0x0F) <<  0)) ^ cx1) / c1;
		int x2 = ((
			(((int)(x >> 16) & 0x0F) << 20) +
			(((int)(x >> 24) & 0x0F) << 16) +
			(((int)(x >>  8) & 0x0F) << 12) +
			(((int)(x >> 32) & 0x0F) <<  8) +
			(((int)(x >>  0) & 0x0F) <<  4) +
			(((int)(x >> 40) & 0x0F) <<  0)) ^ cx2) / c2;
		if ((x1 == x2) && (x1 >= SERIALNUM_MIN) && (x1 <= SERIALNUM_MAX))
		{
			return (int)x1;
		}
	}

	return serial_number;
}

//bool CSCSerialNumber::RequestSerialString()
//{
//	return false;
//}

void CSCSerialNumber::MakeSerialFile(LPCTSTR serial_filename, bool use_dialog)
{
	CString filename;
	if (serial_filename)
	{
		filename = serial_filename;
	}
	else
	{
		filename = "serialnum.txt";
	}

	if (use_dialog)
	{
		CFileDialog file_dlg(
			FALSE,
			_T(".txt"),
			filename,
			OFN_HIDEREADONLY,
			_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));

		if (file_dlg.DoModal() == IDOK)
		{
			filename = file_dlg.GetPathName();
		}
		else
		{
			return;
		}
	}

	CFile serial_file;
	if (serial_file.Open(filename, CFile::modeCreate | CFile::modeWrite))
	{
		try
		{
			CWaitCursor wait_cursor;
			CString serial_string;
			int serial_number;
			for (serial_number = SERIALNUM_MIN;
				serial_number <= SERIALNUM_MAX;
				serial_number++)
			{
				CString line_str;
				serial_string = MakeSerialString(serial_number);
				line_str.Format("%ld\t%s\n", serial_number, serial_string);
				serial_file.Write((LPCTSTR)line_str, line_str.GetLength());
			}
		}
		catch(CFileException *e)
		{
			e->Delete();
			SCMessageBox(_T("Error writing to file."));
		}
		serial_file.Close();
	}
}
