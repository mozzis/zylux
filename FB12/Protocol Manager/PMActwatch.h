// PMActWatch.h : header file
//

#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPMActivationWatcher thread

class CPMActivationWatcher : public CWinThread
{
	DECLARE_DYNCREATE(CPMActivationWatcher)
protected:
	CPMActivationWatcher();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPMActivationWatcher)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPMActivationWatcher();

	// Generated message map functions
	//{{AFX_MSG(CPMActivationWatcher)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
