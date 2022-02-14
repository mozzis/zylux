// DADoc.h : interface of the CDADoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_DADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Kinetics.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DA.h"
#include "Kinetics.h"
#include "ProtocolDoc.h"
#include "Sample.h"
#include "KineticsView.h"

class CDADoc : public CProtocolDoc
{
protected: // create from serialization only
	CDADoc();
	DECLARE_DYNCREATE(CDADoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDADoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDADoc();

	void MeasureEnd();
	void MeasureStart(bool delay);

	void SetMode(int mode);
	int GetMode() const;

	CString GetReplicateString(int series, UINT sample, UINT replicate);
	void SetStatus();
	void Increment();

	void SetModifiedFlag(BOOL bModified = TRUE);
	BOOL SaveMDS(CFile& mds_file);
	BOOL LoadMDS(CFile& mds_file);

	BOOL LogDocument();
	void RemoveLog();

	virtual void FB12CommunicatingChange(VARIANT_BOOL is_communicating);
	virtual void FB12OperatingChange(VARIANT_BOOL is_operating);
	virtual void FB12ErrorChange(long new_error);
	virtual void FB12DoorChange(VARIANT_BOOL is_open);
	virtual void FB12NewRLU(long new_RLU);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	CArray<CString, CString&> m_sample_names;	// the sample names
	CArray<CSample, CSample&> m_samples;		// the samples [0 might be background]

	UINT m_numsamples;		// m_pps.m_numsamples [+ 1 maybe if background]
	UINT m_sample_num;		// 0 to m_numsamples - 1
	UINT m_replicate_num;	// 0 to m_pps.m_numreplicates - 1
	int m_series;			// CSample::SERIES_A or CSample::SERIES_B

	bool m_has_deleted;			// true if user has deleted last sample since measuring
	UINT m_sample_num_prev;		// what to go back to when last sample deleted
	UINT m_replicate_num_prev;	// what to go back to when last sample deleted
	int m_series_prev;			// what to go back to when last sample deleted

	DWORD m_delaycount;
	DWORD m_meascount;

	CKinetics m_kinetics;

	CDAPPS& m_pps;
	CTime m_datetime;

	enum
	{
		MODE_STOPPED,
		MODE_MEASURING,
	};

// Generated message map functions
protected:
	int m_mode;

	//{{AFX_MSG(CDADoc)
	afx_msg void OnUpdateFileSaveAsText(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnMeasureDelete();
	afx_msg void OnUpdateMeasureDelete(CCmdUI* pCmdUI);
	afx_msg void OnMeasureStart();
	afx_msg void OnUpdateMeasureStart(CCmdUI* pCmdUI);
	afx_msg void OnMeasureStop();
	afx_msg void OnUpdateMeasureStop(CCmdUI* pCmdUI);
	afx_msg void OnMeasureKinetics();
	afx_msg void OnUpdateMeasureKinetics(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveKineticsAsText();
	afx_msg void OnUpdateFileSaveKineticsAsText(CCmdUI* pCmdUI);
	afx_msg void OnMeasureGrid();
	afx_msg void OnUpdateMeasureGrid(CCmdUI* pCmdUI);
	//}}AFX_MSG

	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

#define DAGetDoc() ((CDADoc*)DAGetApp()->m_pDoc)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
