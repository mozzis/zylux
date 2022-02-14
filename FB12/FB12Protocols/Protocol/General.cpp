// General function

#include "StdAfx.h"
#include "General.h"
#include "Protocol.h"

// SCMessageBox()
//
// This function is a duplicate for AfxMessageBox() in MFC
// except that it will inhibit the FB12 serial thread from
// processing events received from the serial port so that
// messages do not get backlogged.
//
// Input:
//   lpszText - the string to display
//   nType    - the message box type
//   nIDHelp  - the help ID for the message box
//
// Output:
//   the response from the dialog (the ID pressed)

int SCMessageBox(LPCTSTR lpszText, UINT nType, UINT nIDHelp)
{
	ProtGetApp()->FB12Inhibit();
	int result = AfxMessageBox(lpszText, nType, nIDHelp);
	ProtGetApp()->FB12Uninhibit();
	return result;
}

// SCMessageBox()
//
// This function is a duplicate for AfxMessageBox() in MFC
// except that it will inhibit the FB12 serial thread from
// processing events received from the serial port so that
// messages do not get backlogged.
//
// Input:
//   nIDPrompt - the resource of the string to display
//   nType     - the message box type
//   nIDHelp   - the help ID for the message box
//
// Output:
//   the response from the dialog (the ID pressed)

int SCMessageBox(UINT nIDPrompt, UINT nType, UINT nIDHelp)
{
	ProtGetApp()->FB12Inhibit();
	int result = AfxMessageBox(nIDPrompt, nType, nIDHelp);
	ProtGetApp()->FB12Uninhibit();
	return result;
}

// SCSafeMessageBox()
//
// This function displays a string in a dialog box with
// the application name as the title and an OK button.
// It is safe to use this function in MFC from a thread
// other than the main thread for a CWnd.  This function
// will inhibit the FB12 serial thread from processing
// events received from the serial port so that messages
// do not get backlogged.
//
// Input:
//   lpszText - the string to display
//
// Output:
//   the response from the message box (IDOK)

int SCSafeMessageBox(LPCTSTR lpszText)
{
	ProtGetApp()->FB12Inhibit();
	int result = ::MessageBox(NULL, lpszText, AfxGetApp()->m_pszAppName,
		MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
	ProtGetApp()->FB12Uninhibit();
	return result;
}

// SCSafeMessageBox()
//
// This function displays a string from a resource ID in
// a dialog box with the application name as the title and
// an OK button.  It is safe to use this function in MFC
// from a thread other than the main thread for a CWnd.
// This function will inhibit the FB12 serial thread from
// processing events received from the serial port so that
// messages do not get backlogged.
//
// Input:
//   nIDPrompt - the resouce ID for a string to display
//
// Output:
//   the response from the message box (IDOK)

int SCSafeMessageBox(UINT nIDPrompt)
{
	ProtGetApp()->FB12Inhibit();
	CString text;
	text.LoadString(nIDPrompt);
	int result = ::MessageBox(NULL, text, AfxGetApp()->m_pszAppName,
		MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
	ProtGetApp()->FB12Uninhibit();
	return result;
}

// SCGetFileName()
//
// This function takes a pathname and returns just the
// filename at the end.
//
// Input:
//   filepath - the pathname from which to extact the
//              filename
//
// Output:
//   the filename extracted from the pathname

CString SCGetFileName(const CString& filepath)
{
	CString filename;
	LPCTSTR fp = filepath;
	LPTSTR bp = strrchr(filepath, '\\');
	if (bp == NULL)
	{
		filename = filepath;
	}
	else
	{
		filename.Format("%s", &bp[1]);
	}
	return filename;
}

// SCGetFileTitle()
//
// This function takes a filename (not whole path) and
// returns the filename less its extension, if any.
//
// Input:
//   filename - the filename from which to creat the
//              file title
//
// Output:
//   the filename minus its extension (if any)

CString SCGetFileTitle(const CString& filename)
{
	CString filetitle;
	LPCTSTR fn = filename;
	LPTSTR pp = strrchr(filename, '.');
	if (pp == NULL)
	{
		filetitle = filename;
	}
	else
	{
		filetitle = CString(fn, pp - fn);
	}
	return filetitle;
}

// SCGetCurrentDir()
//
// This function returns the current directory in a
// CString object.
//
// Input: none
//
// Output:
//   the string containing the path of the current
//   directory

CString SCGetCurrentDir()
{
	CString dir;
	DWORD size = GetCurrentDirectory(0, NULL);
	LPTSTR curdir = new char[size];
	if (curdir)
	{
		if (GetCurrentDirectory(size, curdir) == (size - 1))
		{
			dir = curdir;
		}
		delete [] curdir;
	}

	return dir;
}

// SCSetCurrentDir()
//
// This function takes a new path to set as the current
// directory and returns the old current directory.
//
// Input:
//   path - the path string of the new directory to
//          make the current directory
//
// Output:
//   the old path string for the current directory

CString SCSetCurrentDir(LPCTSTR path)
{
	CString curdir = SCGetCurrentDir();
	SetCurrentDirectory(path);
	return curdir;
}

// SCRound()
//
// Rounds a double to the nearest 100ths place.
//
// Input:
//   value - the double value to round
//
// Output: the rounded result

double SCRound(double value)
{
	return ((double)SCNearestInt(value * 100.0)) / 100.0;
}

// SCNearestInt()
//
// Finds the nearest integer of a double value.
//
// Input:
//   value - the double value convert to the nearest integer value
//
// Ouput: the nearest integer of the input

__int64 SCNearestInt(double value)
{
	if (value > 0)
	{
		return (__int64)(value + 0.5);
	}
	else
	{
		return (__int64)(value - 0.5);
	}
}

// SCHasFocus()
//
// This function will take a control ID and tell you
// if it is the active control.
//
// Inputs:
//   id - the control ID to check
//
// Output: true if the control with the passed ID is
//   active; false if it is not active

bool SCHasFocus(int id)
{
	CWnd* focus_wnd = CWnd::GetFocus();
	if (focus_wnd)
	{
		if (focus_wnd->GetDlgCtrlID() == id)
		{
			return true;
		}
	}

	return false;
}

// SCFormatDecisecondsCh()
//
// This function will take a deciseconds value and
// format it into a string of the form "Xm Y.Zs"
// where X is the number of minutes, and Y.Z is the
// number of seconds.
//
// Inputs:
//   decisecs - the deciseconds number to format
//   out_str  - output buffer (at least 20 bytes)
//
// Output: the formatted string

void SCFormatDecisecondsCh(UINT decisecs, LPTSTR out_str)
{
	if (out_str)
	{
		UINT days = decisecs / 864000;
		decisecs %= 864000;
		UINT hrs = decisecs / 36000;
		decisecs %= 36000;
		UINT mins = decisecs / 600;
		decisecs %= 600;
		UINT secs = decisecs / 10;
		decisecs %= 10;

		TCHAR tmp_str[32];
		out_str[0] = 0;
		bool other = false;
		if (days > 0)
		{
			sprintf(tmp_str, "%ldd ", days);
			strcat(out_str, tmp_str);
			other = true;
		}
		if (hrs > 0)
		{
			sprintf(tmp_str, "%ldh ", hrs);
			strcat(out_str, tmp_str);
			other = true;
		}
		if (mins > 0)
		{
			sprintf(tmp_str, "%ldm ", mins);
			strcat(out_str, tmp_str);
			other = true;
		}
		if (!(other && (secs == 0) && (decisecs == 0)))
		{
			sprintf(tmp_str, "%ld.%lds", secs, decisecs);
			strcat(out_str, tmp_str);
		}
	}
}

// SCFormatDeciseconds()
//
// This function will take a deciseconds value and
// format it into a string of the form "Xm Y.Zs"
// where X is the number of minutes, and Y.Z is the
// number of seconds.
//
// Inputs:
//   decisecs - the deciseconds number to format
//
// Output: the formatted string

CString SCFormatDeciseconds(UINT decisecs)
{
	UINT days = decisecs / 864000;
	decisecs %= 864000;
	UINT hrs = decisecs / 36000;
	decisecs %= 36000;
	UINT mins = decisecs / 600;
	decisecs %= 600;
	UINT secs = decisecs / 10;
	decisecs %= 10;

	CString out_str;
	CString tmp_str;
	if (days > 0)
	{
		tmp_str.Format("%ldd ", days);
		out_str += tmp_str;
	}
	if (hrs > 0)
	{
		tmp_str.Format("%ldh ", hrs);
		out_str += tmp_str;
	}
	if (mins > 0)
	{
		tmp_str.Format("%ldm ", mins);
		out_str += tmp_str;
	}
	tmp_str.Format("%ld.%lds", secs, decisecs);
	out_str += tmp_str;

	return out_str;
}

CString SCGetExcelColString(WORD col_num)
{
	CString col_str;

	if (col_num <= 256)
	{
		while (col_num > 0)
		{
			col_num--;
			TCHAR letter = 'A' + (col_num % 26);
			col_str = letter + col_str;
			col_num /= 26;
		}
	}

	return col_str;
}

int SCGetAppProfileInt(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	int result = nDefault;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key_str,
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		DWORD value;
		DWORD type = REG_DWORD;
		DWORD size = 4;
		if (RegQueryValueEx(key, lpszEntry, NULL, &type, (LPBYTE)&value, &size) == ERROR_SUCCESS)
		{
			result = value;
		}
		RegCloseKey(key);
	}

	return result;
}

CString SCGetAppProfileString(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR nDefault)
{
	CString result = nDefault;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key_str,
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		DWORD type = REG_SZ;
		DWORD size;
		if (RegQueryValueEx(key, lpszEntry, NULL, &type, NULL, &size) == ERROR_SUCCESS)
		{
			LPTSTR value = new TCHAR[size];
			if (RegQueryValueEx(key, lpszEntry, NULL, &type, (LPBYTE)value, &size) == ERROR_SUCCESS)
			{
				result = value;
			}
			delete [] value;
		}
		RegCloseKey(key);
	}

	return result;
}

BOOL SCGetAppProfileBinary(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry,
						   BYTE *lpData, DWORD cbData)
{
	BOOL result = FALSE;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key_str,
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		DWORD type = REG_BINARY;
		DWORD size = cbData;
		if (RegQueryValueEx(key, lpszEntry, NULL, &type, lpData, &size) == ERROR_SUCCESS)
		{
			result = TRUE;
		}
		RegCloseKey(key);
	}

	return result;
}

BOOL SCWriteAppProfileInt(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	BOOL result = FALSE;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	DWORD disposition;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, key_str, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disposition) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(key, lpszEntry, NULL, REG_DWORD, (LPBYTE)&nValue, 4) == ERROR_SUCCESS)
		{
			result = TRUE;
		}
		RegCloseKey(key);
	}

	return result;
}

BOOL SCWriteAppProfileString(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR nValue)
{
	BOOL result = FALSE;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	DWORD disposition;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, key_str, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disposition) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(key, lpszEntry, NULL, REG_SZ, (LPBYTE)nValue, strlen(nValue)) == ERROR_SUCCESS)
		{
			result = TRUE;
		}
		RegCloseKey(key);
	}

	return result;
}

BOOL SCWriteAppProfileBinary(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry,
							 CONST BYTE *lpData, DWORD cbData)
{
	BOOL result = FALSE;

	CString key_str = "Software\\Softstep\\";
	key_str += lpszApp;
	key_str += "\\";
	key_str += lpszSection;
	HKEY key;
	DWORD disposition;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, key_str, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disposition) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(key, lpszEntry, NULL, REG_BINARY, lpData, cbData) == ERROR_SUCCESS)
		{
			result = TRUE;
		}
		RegCloseKey(key);
	}

	return result;
}
