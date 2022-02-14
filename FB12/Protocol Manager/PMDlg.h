// PMDlg.h : header file
//

#if !defined(AFX_PMDLG_H__032CD347_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PMDLG_H__032CD347_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "ProtocolItem.h"
#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// CPMDlg dialog

class CPMDlg : public CDialog
{
// Construction
public:
	CPMDlg(CString filename, CWnd* pParent = NULL);	// standard constructor
	~CPMDlg();

	void MySize();

	bool BuildProtocolArray();
	void InsertProtocol(CString& filename, CPPS& pps);
	void InsertProtocolType(CString& filename, CPPS& pps);

	bool StartProtocolAndWait(LPTSTR cmdline, bool rebuild = false);
	PROCESS_INFORMATION m_pi;
	//bool m_waiting;

	static UINT ProtocolThreadFunction(LPVOID pParam);

	//void InstanceTimerCallback(void);
	//static void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	//UINT m_timer_id;

	HRESULT ResolveLink(HWND hwnd, LPSTR link_path);

	CString m_filename;
	COptions m_options;

	bool m_rebuild;
	CArray<CProtocolItem, CProtocolItem&> m_protocols;
	CArray<CProtocolItem, CProtocolItem&> m_protocol_types;

// Dialog Data
	//{{AFX_DATA(CPMDlg)
	enum { IDD = IDD_PROTOCOLMANAGER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPMDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	afx_msg void OnDropFiles(HDROP hDropInfo);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOptions();
	afx_msg void OnSelchangeListProtocols();
	afx_msg void OnProtocolRun();
	afx_msg void OnProtocolEdit();
	afx_msg void OnRetrieve();
	afx_msg void OnProtocolDelete();
	afx_msg void OnAppAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeListProtocoltypes();
	afx_msg void OnProtocolCreate();
	afx_msg void OnViewfile();
	afx_msg void OnProtocoldone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PMDLG_H__032CD347_1A20_11D1_AE1E_0080C80C9F0E__INCLUDED_)
