#if !defined(AFX_CHARTOPTVIEW_H__7DB03541_6B0A_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CHARTOPTVIEW_H__7DB03541_6B0A_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChartOptView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartOptView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "RepInfoList.h"

class CChartOptView : public CFormView
{
protected:
	CChartOptView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChartOptView)

// Form Data
public:
	//{{AFX_DATA(CChartOptView)
	enum { IDD = IDD_GRAPHOPTVIEW };
	CRepInfoList	m_list_replicates;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	bool EditsActive();
	void AdjustLog();
	void AdjustMax();
	void AdjustMin();
	void SetManual();
	void SetAutomatic();
	void VerifyMinMax();
	void UpdateReplicate(UINT replicate_num);
	void UpdateAverage();
	RepInfo BuildRepInfo(UINT rep);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartOptView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChartOptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChartOptView)
	afx_msg void OnCheckLog();
	afx_msg void OnCheckSmoothing();
	afx_msg void OnKillfocusEditMax();
	afx_msg void OnKillfocusEditMin();
	afx_msg void OnRadioAutomatic();
	afx_msg void OnRadioManual();
	afx_msg void OnSelchangeListReplicates();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateKineticsZoomout(CCmdUI* pCmdUI);
	afx_msg void OnKineticsZoomout();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnEditCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTOPTVIEW_H__7DB03541_6B0A_11D1_AE1E_0080C80C9F0E__INCLUDED_)
