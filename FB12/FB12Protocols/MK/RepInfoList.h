#if !defined(AFX_REPINFOLIST_H__1B4E0A21_6C14_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_REPINFOLIST_H__1B4E0A21_6C14_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RepInfoList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRepInfoList window

class RepInfo
{
public:
	RepInfo() : m_integral(-1), m_peak(-1), m_peaktime(-1),
		m_halfrise(-1), m_halfdecay(-1) { }
	RepInfo(long integral, long peak, int peak_time,
		int half_rise, int half_decay)
		: m_integral(integral), m_peak(peak), m_peaktime(peak_time),
		m_halfrise(half_rise), m_halfdecay(half_decay) { }
	long m_integral;	// for all of these,
	long m_peak;		// -1 means don't show
	int m_peaktime;		// -2 means "N/A"
	int m_halfrise;		// >= 0 is normal
	int m_halfdecay;
};

class CRepInfoList : public CCheckListBox
{
// Construction
public:
	CRepInfoList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepInfoList)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_adjustedcols;
	void AdjustSize();
	CArray<RepInfo, RepInfo&> m_info;
	void SetInfo(int rep, RepInfo& rep_info);
	void SetInfo(int rep, long integral, long peak, int peak_time, int half_rise, int half_decay);
	RepInfo& GetInfo(int rep);
	virtual ~CRepInfoList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRepInfoList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPINFOLIST_H__1B4E0A21_6C14_11D1_AE1E_0080C80C9F0E__INCLUDED_)
