// SKDoc.h : interface of the CSKDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_

#include "Kinetics.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SK.h"
#include "ProtocolDoc.h"
#include "Sample.h"
#include "XP3KControl.h"	// Added by ClassView
#include "XP3KTarget.h"

class CSKDoc : public CProtocolDoc, public CXP3KTarget
{
protected: // create from serialization only
	CSKDoc();
	DECLARE_DYNCREATE(CSKDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKDoc)
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
	virtual ~CSKDoc();

	void MeasureStart(bool delay);
	void MeasureEnd();
	void SampleStart(bool delay = false);
	void SampleEnd();

	void SetMode(int mode);
	int GetMode() const;
	int GetMode2() const;

	CString GetReplicateString(UINT sample, UINT replicate);
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

	// Injector Responses
	virtual void XP3KStartResponse(BYTE result);
	//virtual void XP3KMoveToAbsResponse(BYTE result, BYTE status);
	virtual void XP3KMoveToRelativeResponse(BYTE dev_num, BYTE result, BYTE status);
	//virtual void XP3KGetStatusResponse(BYTE result, BYTE status);
	virtual void XP3KGetPositionResponse(BYTE dev_num, BYTE result, BYTE status, int pos);
	virtual void XP3KDrawResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KInjectResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KSetSpeedResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KSetValveResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KInitResponse(BYTE dev_num, BYTE result, BYTE status);

	void CheckInjection(bool use_count, DWORD time_now = 0);
	BOOL InjectionStart(bool use_count, DWORD start_time = 0);
	void CheckVolume(BYTE dev_num, int& total, int& current, short& direction, int requested_volume);
	void ManualInject(BYTE direction, int steps);
	void DoInjection(BYTE dev_num, int inject_idx, int& total, int& current, short& direction);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Cavro Injector variables
	CXP3KControl m_injector_control;			// Interface to the Cavro Pump
	int m_injectpos1;							// Injector 1 position
	int m_injectpos2;							// Injector 2 position
	short m_injectdirection1;					// Injector 1 valve direction
												// 1 => Left To Right, 0 => Right to Left
	short m_injectdirection2;					// Injector 2 valve direction
												// 1 => Left To Right, 0 => Right to Left
	int m_currentamount1;						// Current amount in injector 1 (micro liters)
	int m_currentamount2;						// Current amount in injector 2 (micro liters)
	int m_totalamount1;							// Total amount to inject for replicate with injector 1
	int m_totalamount2;							// Total amount to inject for replicate with injector 2
	short m_injectstate1;						// State of injector 1
	short m_injectstate2;						// State of injector 2
	int m_nextinjection;
	bool m_anyinjections;
	DWORD m_injectionlist[CSKPPS::MAX_INJECTIONS];  // Times/Counts to make injections.
	BYTE m_inject_num;							// Currently selected injector


	// Injector States
	enum
	{
		ISTATE_NIL,						// No state - nothing started
		ISTATE_STARTED,					// Connected to the injector
		ISTATE_CHECK,					// Check to see if Pump is Initialized
		ISTATE_INIT_LEFT,				// First step of initializing the injector
		ISTATE_INIT_RIGHT,				// Second step of initializing the injector
		ISTATE_INIT_SETSPEED,			// Third step of initializing the injector
		ISTATE_INIT_CKVOLUME,			// Fourth step of initializing the injector
		ISTATE_INITIALIZED,				// injector successfully initialized.
		ISTATE_ERROR,					// Unrecoverable injector error

		ISTATE_MAX
	};


	CArray<CSample, CSample&> m_samples;		// the samples [0 might be background]

	UINT m_numsamples;		// m_pps.m_numsamples [+ 1 maybe if background]
	UINT m_sample_num;		// 0 to m_numsamples - 1
	UINT m_replicate_num;	// 0 to m_pps.m_numreplicates - 1

	UINT m_next_update_sample;	// for view updating, the starting sample to update
								// the current m_sample_num is the last sample to update

	UINT m_timer_id;		// for the timer in non-lumi time based 
	DWORD m_time_end;		// the time when the current sample ends
	bool m_time_wait;		// tells whether we're waiting for m_time_end or not

	DWORD m_intervalcount;	// countdown for time interval in lumi-time base
	DWORD m_delaycount;		// countdown for the delay time
	DWORD m_meascount;		// countdown for the measurement time
	DWORD m_updatecount;	// counter to know when to refresh the display
	DWORD m_update_every_n_samples;	// what to reset the m_updatecount to when it reaches 0
	void InstanceTimerCallback(void);
	static void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	CKinetics m_kinetics;

	// graph variables
	bool m_graph_smoothing;		// true for graph smoothing (3 point ave)
	bool m_graph_showaverage;	// true for showing average in graph
	int m_graph_cy;				// size of graph opts frame
	CPoint m_graph_scroll_pt;	// graph opts scroll position
	bool m_graph_manual;		// true for manual RLU range
	bool m_graph_log;			// true for showing log scale
	long m_graph_RLU_min;		// min manual RLU range value
	long m_graph_RLU_max;		// max manual RLU range value
	CArray<bool, bool> m_graph_replicates;	// whether replicates are shown
											// in the graph or not

	CSKPPS& m_pps;
	CTime m_datetime;

	enum
	{
		MODE_STOPPED,
		MODE_MEASURING,
	};
	enum
	{
		MODE_SAMPLING,
		MODE_WAITINTERVAL,
	};

// Generated message map functions
protected:
	int m_mode;
	int m_mode2;

	//{{AFX_MSG(CSKDoc)
	afx_msg void OnUpdateFileSaveAsText(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnMeasureStart();
	afx_msg void OnUpdateMeasureStart(CCmdUI* pCmdUI);
	afx_msg void OnMeasureStop();
	afx_msg void OnUpdateMeasureStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonDown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonUp(CCmdUI* pCmdUI);
	afx_msg void OnMeasureKinetics();
	afx_msg void OnUpdateMeasureKinetics(CCmdUI* pCmdUI);
	afx_msg void OnMeasureGrid();
	afx_msg void OnUpdateMeasureGrid(CCmdUI* pCmdUI);
	afx_msg void OnButtonLeft();
	afx_msg void OnUpdateButtonLeft(CCmdUI* pCmdUI);
	afx_msg void OnButtonRight();
	afx_msg void OnUpdateButtonRight(CCmdUI* pCmdUI);
	afx_msg void OnButtonUp();
	afx_msg void OnButtonInit();
	afx_msg void OnUpdateButtonInit(CCmdUI* pCmdUI);
	afx_msg void OnButtonDown();
	afx_msg void OnButtonInjector1();
	afx_msg void OnButtonInjector2();
	afx_msg void OnUpdateButtonInjector1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonInjector2(CCmdUI* pCmdUI);
	//}}AFX_MSG

	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

#define SKGetDoc() ((CSKDoc*)SKGetApp()->m_pDoc)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKDOC_H__CE385EED_0D84_11D1_AE1E_0080C80C9F0E__INCLUDED_)
