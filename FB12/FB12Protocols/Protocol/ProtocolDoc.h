#if !defined(AFX_PROTOCOLDOC_H__2B98A3C1_1D83_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_PROTOCOLDOC_H__2B98A3C1_1D83_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProtocolDoc.h : header file
//

#include <wtypes.h>
#include "KineticsView.h"
#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// CProtocolDoc document

class CProtocolDoc : public CDocument
{
protected:
	CProtocolDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProtocolDoc)

// Attributes
public:
	CView* m_graph_view;
	CFrameWnd* m_graph_frame;
	WINDOWPLACEMENT m_graph_placement;
	CView* m_grid_view;
	CFrameWnd* m_grid_frame;
	WINDOWPLACEMENT m_grid_placement;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolDoc)
	//}}AFX_VIRTUAL

// Implementation
public:
	COptions& m_options;
	void ToggleGrid();
	void ToggleKinetics();
	virtual void FB12CommunicatingChange(VARIANT_BOOL is_communicating) { };
	virtual void FB12OperatingChange(VARIANT_BOOL is_operating) { };
	virtual void FB12DoorChange(VARIANT_BOOL is_open) { };
	virtual void FB12ErrorChange(long new_error) { };
	virtual void FB12NewRLU(long new_RLU) { };
	virtual ~CProtocolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CProtocolDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLDOC_H__2B98A3C1_1D83_11D1_AE1E_0080C80C9F0E__INCLUDED_)
