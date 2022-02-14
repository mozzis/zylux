#if !defined(AFX_INJECTOROPTIONS_H__ACDFA901_D913_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_INJECTOROPTIONS_H__ACDFA901_D913_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ProtocolDlg.h"
#include "SKOptions.h"
// InjectorOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInjectorOptions dialog

class CInjectorOptions : public CProtocolDlg
{
// Construction
public:
	void SetVolume(int index);
	void InitVolumes();
	void InitTimes();
	CInjectorOptions(CSKPPS &skpps, LPCTSTR protocolname, CWnd* pParent = NULL);   // standard constructor
	CSKPPS & m_skpps;
	CSKOptions& m_skoptions;

	CInjectorParams m_injections[CSKPPS::MAX_INJECTIONS];
	CButton* m_skips[CSKPPS::MAX_INJECTIONS];
	CButton* m_inject1s[CSKPPS::MAX_INJECTIONS];
	CButton* m_inject2s[CSKPPS::MAX_INJECTIONS];

	CSpinButtonCtrl* m_minute_spinners[CSKPPS::MAX_INJECTIONS];
	CSpinButtonCtrl* m_second_spinners[CSKPPS::MAX_INJECTIONS];
	CSpinButtonCtrl* m_volume_spinners[CSKPPS::MAX_INJECTIONS];
	CEdit* m_times[CSKPPS::MAX_INJECTIONS];
	CEdit* m_volumes[CSKPPS::MAX_INJECTIONS];

	long m_max_vol, m_max_vol2;
// Dialog Data
	//{{AFX_DATA(CInjectorOptions)
	enum { IDD = IDD_INJECTOROPTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectorOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableInjections(int index, BOOL enable);

	// Generated message map functions
	//{{AFX_MSG(CInjectorOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnKillfocusEditVol1();
	afx_msg void OnKillfocusEditVol2();
	afx_msg void OnKillfocusEditVol3();
	afx_msg void OnKillfocusEditVol4();
	afx_msg void OnKillfocusEditVol5();
	afx_msg void OnCheckInjector();
	afx_msg void OnChangeVolume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTOROPTIONS_H__ACDFA901_D913_11D1_8C08_00400516EF5A__INCLUDED_)
