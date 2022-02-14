////////////////////////////////////////////////////////////////
// CWindowPlacement Copyright 1996 Microsoft Systems Journal.
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: WinPlace.h $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:26a
 * Updated in $/ZyluxCap/2.0
 * Add Souce Safe header keyword
*/

#ifndef _WINPLACE_DEFINED
#define _WINPLACE_DEFINED

////////////////
// CWindowPlacement reads and writes WINDOWPLACEMENT 
// from/to application profile and CArchive.
//
struct CWindowPlacement : public tagWINDOWPLACEMENT {
	CWindowPlacement();
	~CWindowPlacement();
	
	// Read/write to app profile
	BOOL GetProfileWP(LPCTSTR lpszKey, LPCTSTR lpszVal);
	BOOL WriteProfileWP(LPCTSTR lpszKey, LPCTSTR lpszVal);

	// Save/restore window pos (from app profile)
	void Save(UINT nEntry, CWnd* pWnd);
	// bDialog == TRUE means restore size but not position
	BOOL Restore(UINT nEntry, CWnd* pWnd, BOOL bDialog = TRUE, BOOL bMaxDefault = FALSE);

	// Save/restore from archive
	friend CArchive& operator<<(CArchive& ar, const CWindowPlacement& wp);
	friend CArchive& operator>>(CArchive& ar, CWindowPlacement& wp);
};

#endif // _WINPLACE_DEFINED
