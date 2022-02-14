#if !defined(AFX_SAMPGRIDWND_H__80F1AAA1_1A37_11D1_87A6_00400516EF5A__INCLUDED_)
#define AFX_SAMPGRIDWND_H__80F1AAA1_1A37_11D1_87A6_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SampGridWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampGridWnd window

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

	void SetGridValues(CSAPPS& pps);
	void GetGridValues(CSAPPS& pps);
	void ClearSelRows();
	void DeleteSelRows();
	void AppendSamplesFromBuffer(LPTSTR buffer, DWORD size);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampGridWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPGRIDWND_H__80F1AAA1_1A37_11D1_87A6_00400516EF5A__INCLUDED_)
