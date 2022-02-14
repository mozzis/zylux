#if !defined(AFX_WORKDIRDLG_H__D1D742A1_2611_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_WORKDIRDLG_H__D1D742A1_2611_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WorkDirDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkDirDlg dialog

class CWorkDirDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CWorkDirDlg)

public:
	CWorkDirDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CWorkDirDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKDIRDLG_H__D1D742A1_2611_11D1_AE1E_0080C80C9F0E__INCLUDED_)
