// DAKineticsView.cpp : implementation file
//

#include "stdafx.h"
#include "da.h"
#include "DAKineticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAKineticsView

IMPLEMENT_DYNCREATE(CDAKineticsView, CKineticsView)

CDAKineticsView::CDAKineticsView()
{
}

CDAKineticsView::~CDAKineticsView()
{
}


BEGIN_MESSAGE_MAP(CDAKineticsView, CKineticsView)
	//{{AFX_MSG_MAP(CDAKineticsView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_KINETICS_ZOOMOUT, CKineticsView::OnKineticsZoomout)
	ON_UPDATE_COMMAND_UI(ID_KINETICS_ZOOMOUT, CKineticsView::OnUpdateKineticsZoomout)
	ON_COMMAND(ID_EDIT_COPY, CKineticsView::OnEditCopy)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAKineticsView diagnostics

#ifdef _DEBUG
void CDAKineticsView::AssertValid() const
{
	CKineticsView::AssertValid();
}

void CDAKineticsView::Dump(CDumpContext& dc) const
{
	CKineticsView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDAKineticsView message handlers

BOOL CDAKineticsView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		bool post;
		UINT message;

		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			post = true;
			message = ID_MEASURE_START;
			break;

		case VK_DELETE:
			post = true;
			message = ID_MEASURE_DELETE;
			break;

		default:
			post = false;
			break;
		}

		if (post)
		{
			PostMessage(WM_COMMAND, message, 0);
			return TRUE;
		}
	}
	
	return CKineticsView::PreTranslateMessage(pMsg);
}
