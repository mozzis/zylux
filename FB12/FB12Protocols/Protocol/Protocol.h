// Protocol.h : main header file for the Protocol application class
//

#if !defined(AFX_PROTOCOL_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOL_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <afxmt.h>
#include "ProtocolDoc.h"
#include "FB12Device.h"
#include "Options.h"	// Added by ClassView

class CActivationWatcher;

/////////////////////////////////////////////////////////////////////////////
// CProtocolApp:
// See Protocol.cpp for the implementation of this class
//

class CProtocolApp : public CWinApp
{
public:
	COptions m_options;
	CProtocolApp(UINT main_icon_id, UINT doc_icon_id, UINT graph_icon_id);
	~CProtocolApp();

	virtual BOOL ModeEdit();
	virtual BOOL ModeRunView();
	virtual BOOL ModeView();
	virtual BOOL ModeRun();
	virtual BOOL ModeGen();

	void FB12Inhibit();
	void FB12Uninhibit();
	bool FB12IsInibited() const;

	CMultiDocTemplate* m_grid_template;
	CMultiDocTemplate* m_graph_template;

	// FB12Device message
	enum
	{
		WM_FB12 = WM_APP,
	};
	// m_mode enums
	enum
	{
		APPMODE_NONE,
		APPMODE_EDIT,	// edit .pps file
		APPMODE_RUN,	// run .pps file
		APPMODE_VIEW,	// view .mds file
		APPMODE_GEN,	// generate a base .pps file

		APPMODE_MAX
	};
	int m_mode;
	long m_baud;
	short m_port;
	bool m_beep;

	FB12Device* m_pFB12Device;
	CProtocolDoc* m_pDoc;

	CString m_filepath;		// path and filename of cmd line file (relative to m_maindir)
	CString m_filename;		// filename of cmd line file
	CString m_filetitle;	// filename less extension of cmd line file

	CString m_maindir;		// the path of Protocol Manager
	CString m_protocoldir;	// the path of the protocols
	CString m_workdir;		// the path the user chose for saving data
	CString m_logpath;		// the path and filename of the logfile

	UINT m_main_icon_id;
	UINT m_doc_icon_id;
	UINT m_graph_icon_id;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProtocolApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg LRESULT OnFB12Event(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CEvent* m_pInstanceEvent;
	CEvent* m_pShutdownEvent;
	CActivationWatcher* m_pActivationWatch;
	friend CActivationWatcher;
};
#define ProtGetApp() ((CProtocolApp*)AfxGetApp())

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOL_H__CE385EE5_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
