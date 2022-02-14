// General functions
// Copyright Softstep Corporation

#pragma once

int SCMessageBox(LPCTSTR lpszText, UINT nType = MB_OK, UINT nIDHelp = 0);
int SCMessageBox(UINT nIDPrompt, UINT nType = MB_OK, UINT nIDHelp = 1);
int SCSafeMessageBox(LPCTSTR lpszText);
int SCSafeMessageBox(UINT nIDPrompt);
CString SCGetFileName(const CString& filepath);
CString SCGetFileTitle(const CString& filename);
CString SCGetCurrentDir();
CString SCSetCurrentDir(LPCTSTR path);
double SCRound(double value);
__int64 SCNearestInt(double value);
bool SCHasFocus(int id);
void SCFormatDecisecondsCh(UINT decisecs, LPTSTR out_str);
CString SCFormatDeciseconds(UINT decisecs);
CString SCGetExcelColString(WORD col_num);	// col_num must be between 1 and 256
int SCGetAppProfileInt(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
CString SCGetAppProfileString(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR nDefault);
BOOL SCGetAppProfileBinary(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry,
						   BYTE *lpData, DWORD cbData);
BOOL SCWriteAppProfileInt(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
BOOL SCWriteAppProfileString(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR nValue);
BOOL SCWriteAppProfileBinary(LPCTSTR lpszApp, LPCTSTR lpszSection, LPCTSTR lpszEntry,
							 CONST BYTE *lpData, DWORD cbData);
