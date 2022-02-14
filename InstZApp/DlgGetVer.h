#if !defined(AFX_DLGBETVER_H__5529E0E5_47B4_4CF0_ACD5_C0417C3162AF__INCLUDED_)
#define AFX_DLGBETVER_H__5529E0E5_47B4_4CF0_ACD5_C0417C3162AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetVer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetVer dialog

class CDlgGetVer : public CDialog
{
// Construction
public:
	CDlgGetVer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetVer)
	enum { IDD = IDD_GETCAPVER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  enum E_CHOICES { UPGRADE_US = 0, UPGRADE_UK, UPGRADE_NO };
  E_CHOICES GetUserChoice(void);
  void SetVersion(LPCTSTR szVer) { m_csVersion = szVer; }
  void SetPrevVerPresent(bool bSet) { m_bPrevVerPresent = bSet; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetVer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  E_CHOICES m_eChoice;
  CString m_csVersion;
  bool m_bPrevVerPresent;

	// Generated message map functions
	//{{AFX_MSG(CDlgGetVer)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBETVER_H__5529E0E5_47B4_4CF0_ACD5_C0417C3162AF__INCLUDED_)
