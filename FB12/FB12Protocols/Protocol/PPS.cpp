// PPS.cpp: implementation of the CPPS class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PPS.h"
#include "General.h"
#include "Protocol.h"
#include "SaveAsDlg.h"

#include <dlgs.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// CPPS()
//
// This is the default constructor for CPPS class.  It inits
// everything to an empty state.

CPPS::CPPS() : m_version(1), m_checksum(0), m_flags(0)
{
	memset(m_protocolexe, 0, sizeof(m_protocolexe));
	memset(m_protocolname, 0, sizeof(m_protocolname));
	memset(m_comment, 0, sizeof(m_comment));
}

// CPPS()
//
// This in the copy constructor.

CPPS::CPPS(const CPPS& pps)
{
	*this = pps;
}

// operator=()
//
// This is the assignment operator.

CPPS& CPPS::operator=(const CPPS& pps)
{
	if (this != &pps)
	{
		m_version = pps.m_version;
		m_checksum = pps.m_checksum;
		m_flags = pps.m_flags;
		memcpy(m_protocolexe, pps.m_protocolexe, sizeof(m_protocolexe));
		memcpy(m_protocolname, pps.m_protocolname, sizeof(m_protocolname));
		memcpy(m_comment, pps.m_comment, sizeof(m_comment));
	}
	return *this;
}

// ~CPPS()
//
// This is the destructor.

CPPS::~CPPS()
{
}

// Write()
//
// This function writes the pps data to the passed in
// CFile.  This is a virtual function such that the
// most derived class' Write() function will be called
// first.  Any subclasses should call its base class'
// Write() function first, then write its own data to
// the CFile.  Use this function as an outline to write
// any derived class' Write() function.
//
// Input:
//   cfile - the CFile where the data is to be written
//
// Output:
//   true if the write is successful; false if the
//   write is not successful

bool CPPS::Write(CFile& cfile)
{
	try
	{
		cfile.Write(&m_version, sizeof(m_version));
		cfile.Write(&m_checksum, sizeof(m_checksum));
		cfile.Write(&m_flags, sizeof(m_flags));
		cfile.Write(m_protocolexe, sizeof(m_protocolexe));
		cfile.Write(m_protocolname, sizeof(m_protocolname));
		cfile.Write(m_comment, sizeof(m_comment));
		return true;
	}
	catch(CFileException *e)
	{
		e->Delete();
		return false;
	}
}

// Read()
//
// This function reads protocol data from a passed in
// CFile.  This is a virtual function such that the
// most derived class' Read() function will be called
// first.  Any subclasses should call its base class'
// Read() function first, then read its own data to
// the CFile.  Use this function as an outline to write
// any derived class' Read() function.
//
// Input:
//   cfile - the CFile where the data is to be read
//
// Output:
//   true if the read is successful; false if the
//   read is not successful

bool CPPS::Read(CFile& cfile)
{
	try
	{
		if ((cfile.Read(&m_version, sizeof(m_version)) == sizeof(m_version)) &&
			(m_version == 1) &&
			(cfile.Read(&m_checksum, sizeof(m_checksum)) == sizeof(m_checksum)) &&
			(cfile.Read(&m_flags, sizeof(m_flags)) == sizeof(m_flags)) &&
			(cfile.Read(m_protocolexe, sizeof(m_protocolexe)) == sizeof(m_protocolexe)) &&
			(cfile.Read(m_protocolname, sizeof(m_protocolname)) == sizeof(m_protocolname)) &&
			(cfile.Read(m_comment, sizeof(m_comment)) == sizeof(m_comment)))
		{
			return true;
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

// Save()
//
// Saves the protocol under the passed name.
//
// This function will change to the protocols directory
// temporarily to load the data, and then go back to
// the directory it was called from.
//
// ****WARNING****
// This function should only be called from CProtocolApp
// derived programs.
//
// Input:
//   protocol_name - the name of the protocol to save
//                   (without .pps)
//
// Output:
//   true if the save was successful; false if there was
//   an error in saving

bool CPPS::Save(LPCTSTR protocol_name)
{
	CString pps_filename = protocol_name;
	pps_filename += ".pps";

	bool success = false;

	CString curdir = SCSetCurrentDir(ProtGetApp()->m_protocoldir);

	CString err_str;
	CFile pps_file;
	if (pps_file.Open(pps_filename, CFile::modeCreate | CFile::modeWrite))
	{
		if (Write(pps_file))
		{
			success = true;
		}
		else
		{
			err_str.Format("Error saving file %s!", pps_filename);
			SCMessageBox(err_str);
		}

		pps_file.Close();
	}
	else
	{
		err_str.Format("File %s could not be opened!", pps_filename);
		SCMessageBox(err_str);
	}

	SCSetCurrentDir(curdir);

	return success;
}

// SaveAs()
//
// This function will save a protocol under a new name,
// defaulting to the name passed in.
//
// This function will change to the protocols directory
// temporarily to load the data, and then go back to
// the directory it was called from.
//
// ****WARNING****
// This function should only be called from CProtocolApp
// derived programs.
//
// Input:
//   protocol_name        - the default name of the protocol
//                          (without .pps)
//   allow_base_overwrite - set to true if user is allowed to
//                          overwrite a base protocol file; set
//                          to false if the user is not allowed
//                          to overwrite a base protocol file
//
// Output:
//   true if the save was successful; false if the user canceled
//   or there was an error in saving

bool CPPS::SaveAs(LPCTSTR protocol_name, bool allow_base_overwrite)
{
	CSaveAsDlg dlg(protocol_name, allow_base_overwrite);
	if (dlg.DoModal() == IDOK)
	{
		memset(m_protocolname, 0, sizeof(m_protocolname));
		strcpy(m_protocolname, dlg.m_protocolname);
		if (Save(m_protocolname))
		{
			return true;
		}
	}

	return false;
}

// Load()
//
// This function loads the pps data into the pps class
// given the name of a protocol.
//
// This function will change to the protocols directory
// temporarily to load the data, and then go back to
// the directory it was called from.
//
// ****WARNING****
// This function should only be called from CProtocolApp
// derived programs.
//
// Input:
//   protocol_name - the name of the protocol (without .pps)
//
// Output:
//   true if successful, false if not successful

bool CPPS::Load(LPCTSTR protocol_name)
{
	CString pps_filename = protocol_name;
	pps_filename += ".pps";
	bool success = false;

	CString curdir = SCSetCurrentDir(ProtGetApp()->m_protocoldir);

	CString err_str;
	CFile pps_file;
	if (pps_file.Open(pps_filename, CFile::modeRead))
	{
		if (Read(pps_file))
		{
			success = true;
		}
		else
		{
			err_str.Format("Error reading file %s!", pps_filename);
			SCMessageBox(err_str);
		}

		pps_file.Close();
	}
	else
	{
		err_str.Format("File %s could not be opened!", pps_filename);
		SCMessageBox(err_str);
	}

	SCSetCurrentDir(curdir);

	return success;
}

// IsSaveable()
//
// This function test whether the pps object is save-able.
//
// Input: none
//
// Output:
//   true if the pps object is save-able; false if the pps
//   object is not save-able

bool CPPS::IsSaveable() const
{
	return (m_flags & FLAG_SAVEABLE) ? true : false;
}

// IsSaveAsable()
//
// This function test whether the pps object is saveas-able.
//
// Input: none
//
// Output:
//   true if the pps object is saveas-able; false if the pps
//   object is not saveas-able

bool CPPS::IsSaveAsable() const
{
	return (m_flags & FLAG_SAVEASABLE) ? true : false;
}

// IsRunable()
//
// This function test whether the pps object is run-able.
//
// Input: none
//
// Output:
//   true if the pps object is run-able; false if the pps
//   object is not run-able

bool CPPS::IsRunable() const
{
	return (m_flags & FLAG_RUNABLE) ? true : false;
}

// IsDeleteable()
//
// This function test whether the pps object is delete-able.
//
// Input: none
//
// Output:
//   true if the pps object is delete-able; false if the pps
//   object is not delete-able

bool CPPS::IsDeleteable() const
{
	return (m_flags & FLAG_DELETEABLE) ? true : false;
}

// IsBase()
//
// This function test whether the pps object is a base
// protocol type.
//
// Input: none
//
// Output:
//   true if the pps object is a base; false if the pps
//   object is not a base

bool CPPS::IsBase() const
{
	return (m_flags & FLAG_BASE) ? true : false;
}

// SetBase()
//
// This function sets whether the pps object is a base
// object or not.
//
// Input:
//   is_base - pass true to set the object to a base type;
//             pass false to set the object to a non-base type
//
// Output: none

void CPPS::SetBase(bool is_base)
{
	if (is_base)
	{
		m_flags |= FLAG_BASE;
	}
	else
	{
		m_flags &= ~FLAG_BASE;
	}
}

// SetDeleteable()
//
// This function sets whether the pps object is delete-able
// or not.
//
// Input:
//   is_deleteable - pass true to set the object delete-able;
//                   pass false to set the object not delete-able
//
// Output: none

void CPPS::SetDeleteable(bool is_deleteable)
{
	if (is_deleteable)
	{
		m_flags |= FLAG_DELETEABLE;
	}
	else
	{
		m_flags &= ~FLAG_DELETEABLE;
	}
}

// SetRunable()
//
// This function sets whether the pps object is run-able
// or not.
//
// Input:
//   is_runable - pass true to set the object run-able;
//                pass false to set the object not run-able
//
// Output: none

void CPPS::SetRunable(bool is_runable)
{
	if (is_runable)
	{
		m_flags |= FLAG_RUNABLE;
	}
	else
	{
		m_flags &= ~FLAG_RUNABLE;
	}
}

// SetSaveable()
//
// This function sets whether the pps object is save-able
// or not.
//
// Input:
//   is_saveable - pass true to set the object save-able;
//                 pass false to set the object not save-able
//
// Output: none

void CPPS::SetSaveable(bool is_saveable)
{
	if (is_saveable)
	{
		m_flags |= FLAG_SAVEABLE;
	}
	else
	{
		m_flags &= ~FLAG_SAVEABLE;
	}
}

// SetSaveAsable()
//
// This function sets whether the pps object is saveas-able
// or not.
//
// Input:
//   is_saveasable - pass true to set the object saveas-able;
//                   pass false to set the object not saveas-able
//
// Output: none

void CPPS::SetSaveAsable(bool is_saveasable)
{
	if (is_saveasable)
	{
		m_flags |= FLAG_SAVEASABLE;
	}
	else
	{
		m_flags &= ~FLAG_SAVEASABLE;
	}
}

// IsFileBase()
//
// This is a static helper function to determine if
// a protocol on disk is a base protocol.
//
// ****WARNING****
// This function should only be called from CProtocolApp
// derived programs.
//
// Input:
//   protocol_name - the name of the protocol to check
//                   (without .pps)
//
// Output:
//   true if the protocol is a base protocol; false if
//   the protocol is not a base protocol

bool CPPS::IsFileBase(LPCTSTR protocol_name)
{
	CString pps_filename = protocol_name;
	pps_filename += ".pps";
	bool is_base = false;

	CString curdir = SCSetCurrentDir(ProtGetApp()->m_protocoldir);

	CFile pps_file;
	if (pps_file.Open(pps_filename, CFile::modeRead))
	{
		CPPS pps;
		if (pps.Read(pps_file))
		{
			is_base = pps.IsBase();
		}

		pps_file.Close();
	}

	SCSetCurrentDir(curdir);

	return is_base;
}

// BuildProtocolArray()
//
// int /* num_protocols */ BuildProtocolArray(CArray<CString, CString&>& protocols, bool extension);
//
// This is a static helper function that builds an array of
// CStrings for the protocols in the "protocols" directory
// with or without .pps extensions and returns the number found.
//
// *****NOTE*****
// This function assumes you are in the main directory for the
// Protocol Manager.
//
// Input:
//   protocol   - a reference to the array to fill with names
//   extensions - true if you want .pps extensions on the names;
//                or false if you want no extension
//
// Output:
//   the number of protocols found

int CPPS::BuildProtocolArray(CArray<CString, CString&>& protocols, bool extensions)
{
	protocols.SetSize(0);
	int num_names = 0;
	CString name;
	CFileFind finder;
	BOOL bWorking = finder.FindFile("protocols\\*.pps");
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		num_names++;
		name = finder.GetFileName();
		protocols.Add(extensions ? name : name.Left(name.GetLength() - 4));
	}

	return num_names;
}
