// MKDoc.h : interface of the CMKDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Kinetics.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MK.h"
#include "ProtocolDoc.h"
#include "Sample.h"

class CMKDoc : public CProtocolDoc
{
protected: // create from serialization only
	CMKDoc();
	DECLARE_DYNCREATE(CMKDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetTimerText();
	CString GetCounterText();
	virtual ~CMKDoc();

	void MeasureStart();
	void MeasureEnd();
	void MeasurementStart();
	void MeasurementEnd();

	void SetMode(int mode);
	int GetMode() const;
	void SetMode2(int mode);
	int GetMode2() const;

	CString GetReplicateString(UINT sample, UINT replicate);
	void SetStatus();
	//void Increment();

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

	CArray<CSample, CSample&> m_samples;		// the samples [0 might be background]

	UINT m_numsamps;	// m_pps.m_numsamples
	UINT m_nummeas;		// m_pps.m_nummeasurements
	UINT m_numreps;		// m_pps.m_numreplicates
	UINT m_samp_num;	// 0 to m_numsamples - 1
	UINT m_meas_num;	// 0 to m_nummeas - 1
	UINT m_rep_num;		// 0 to m_pps.m_numreplicates - 1

	UINT m_timer_id;		// for the timer in non-lumi time based
	DWORD m_time_start;		// the system time when the measurements began
	DWORD m_time_end;		// the time when the current sample ends

	bool m_door_wait;		// true when waiting for door to close
	DWORD m_delaycount;		// countdown for the delay time
	DWORD m_meascount;		// countdown for the measurement time
	void InstanceTimerCallback(void);
	static void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	CKinetics m_kinetics;

	// graph variables
	bool m_graph_smoothing;		// true for graph smoothing (3 point ave)
	bool m_graph_nominal;		// true for graph shows nominal times, false for actual times
	int m_graph_cy;				// size of graph opts frame
	CPoint m_graph_scroll_pt;	// graph opts scroll position
	bool m_graph_manual;		// true for manual RLU range
	bool m_graph_log;			// true for showing log scale
	long m_graph_RLU_min;		// min manual RLU range value
	long m_graph_RLU_max;		// max manual RLU range value
	DWORD m_graph_hightime;		// holds the time value when the last measurement was taken
	CArray<bool, bool> m_graph_replicates;	// whether replicates are shown
											// in the graph or not
	CArray<bool, bool> m_graph_showaverages;	// whether the average of
												// each replicate is shown or not

	CMKPPS& m_pps;
	CTime m_datetime;

	enum	// mode
	{
		MODE_STOPPED,
		MODE_MEASURING,
		MODE_FINISHED,
	};
	enum	// mode 2, if mode == MODE_MEASURING
	{
		MODE_SAMP,
		MODE_WAIT,
	};

// Generated message map functions
protected:
	int m_mode;
	int m_mode2;

	//{{AFX_MSG(CMKDoc)
	afx_msg void OnUpdateFileSaveAsText(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnMeasureStop();
	afx_msg void OnUpdateMeasureStop(CCmdUI* pCmdUI);
	afx_msg void OnMeasureKinetics();
	afx_msg void OnUpdateMeasureKinetics(CCmdUI* pCmdUI);
	afx_msg void OnMeasureGrid();
	afx_msg void OnUpdateMeasureGrid(CCmdUI* pCmdUI);
	//}}AFX_MSG

	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

#define MKGetDoc() ((CMKDoc*)MKGetApp()->m_pDoc)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
