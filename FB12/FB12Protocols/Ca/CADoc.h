// CADoc.h : interface of the CCADoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_CADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Kinetics.h"	// Added by ClassView
#include "CAPPS.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CA.h"
#include "ProtocolDoc.h"
#include "Sample.h"

class CCADoc : public CProtocolDoc
{
protected: // create from serialization only
	CCADoc();
	DECLARE_DYNCREATE(CCADoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCADoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RecalcCutoffs();
	BOOL MoreToMeasure();
	virtual ~CCADoc();
	
	BOOL GetNext(UINT& rep, UINT& samp);
	void MeasureEnd();
	void MeasureStart(bool delay);
	void SetMode(int mode);
	int GetMode() const;
	CString GetReplicateString(UINT sample, UINT replicate);
	void SetStatus();
	
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

	CArray<CSample, CSample&> m_samples;

	bool m_any_deleted;		
	bool m_validassay;		// true if (lowcutoff <= highcutoff), false otherwise
	UINT m_sample_num;		// 1 to m_pps.m_numsamples;
	UINT m_replicate_num;	// 1 to m_pps.m_numreplicates;	
	UINT m_last_sample;		// 1 to m_pps.m_numsamples;
	UINT m_last_replicate;	// 1 to m_pps.m_numreplicates;	
	UINT m_numsamples;
	UINT m_negsample;		// either 1 or 2 depending if background row used
	UINT m_possample;		// either 2 or 3 depending if background row used
	UINT m_maxreps;			// max replicate - sample, pos, or neg

	DWORD m_meascount;
	DWORD m_delaycount;

	CKinetics m_kinetics;

	CCAPPS& m_pps;


	CTime m_datetime;

	enum
	{
		MODE_STOPPED,
		MODE_MEASURING,
	};

protected:
	int m_mode;

// Generated message map functions
protected:
	//{{AFX_MSG(CCADoc)
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
	afx_msg void OnUpdateFileSaveAsText(CCmdUI* pCmdUI);
	afx_msg void OnMeasureGrid();
	afx_msg void OnUpdateMeasureGrid(CCmdUI* pCmdUI);
	//}}AFX_MSG

	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};


#define CAGetDoc() ((CCADoc*)CAGetApp()->m_pDoc)


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
