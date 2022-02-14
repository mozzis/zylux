// WorkDirDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol Manager.h"
#include "WorkDirDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkDirDlg

IMPLEMENT_DYNAMIC(CWorkDirDlg, CFileDialog)

CWorkDirDlg::CWorkDirDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CWorkDirDlg, CFileDialog)
	//{{AFX_MSG_MAP(CWorkDirDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

