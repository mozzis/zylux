// SampGridWnd.h: interface for the CSampGridWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPGRIDWND_H__0D7594C2_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_SAMPGRIDWND_H__0D7594C2_5CE9_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSampGridWnd : public CGXGridWnd  
{
	DECLARE_REGISTER()

// Construction
public:
	CSampGridWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampGridWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_initialized;
	virtual void OnInitialUpdate();
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);

	virtual ~CSampGridWnd();

	void SetGridValues(CDAPPS& pps);
	void GetGridValues(CDAPPS& pps);
	void ClearSelRows();
	void DeleteSelRows();
	void AppendSamplesFromBuffer(LPTSTR buffer, DWORD size);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampGridWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()};

#endif // !defined(AFX_SAMPGRIDWND_H__0D7594C2_5CE9_11D1_8C08_00400516EF5A__INCLUDED_)
