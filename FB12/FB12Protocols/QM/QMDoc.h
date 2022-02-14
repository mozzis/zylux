// QMDoc.h : interface of the CQMDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QMDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_QMDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Kinetics.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ProtocolDoc.h"

class CQMDoc : public CProtocolDoc
{
protected: // create from serialization only
	CQMDoc();
	DECLARE_DYNCREATE(CQMDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQMDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQMDoc();

	enum
	{
		MODE_STOPPED,
		MODE_MEASURING,
	};

	void MeasureEnd();
	void MeasureStart();

	void SetMode(int mode);
	int GetMode() const;

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

	CArray<long,long> m_RLUs;
	DWORD m_meascount;
	DWORD m_delaycount;
	DWORD m_delaytime;
	DWORD m_meastime;
	CTime m_datetime;
	CKinetics m_kinetics;
protected:
	int m_mode;

// Generated message map functions
protected:
	//{{AFX_MSG(CQMDoc)
	afx_msg void OnUpdateFileSaveAsText(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	//}}AFX_MSG

	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QMDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
