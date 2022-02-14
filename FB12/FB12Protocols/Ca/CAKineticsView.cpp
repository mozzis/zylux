// CAKineticsView.cpp : implementation file
//

#include "stdafx.h"
#include "CA.h"
#include "CAKineticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAKineticsView

IMPLEMENT_DYNCREATE(CCAKineticsView, CKineticsView)

CCAKineticsView::CCAKineticsView()
{
}

CCAKineticsView::~CCAKineticsView()
{
}


BEGIN_MESSAGE_MAP(CCAKineticsView, CKineticsView)
	//{{AFX_MSG_MAP(CCAKineticsView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_COPY, CKineticsView::OnEditCopy)
	ON_COMMAND(ID_KINETICS_ZOOMOUT, CKineticsView::OnKineticsZoomout)
	ON_UPDATE_COMMAND_UI(ID_KINETICS_ZOOMOUT, CKineticsView::OnUpdateKineticsZoomout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAKineticsView diagnostics

#ifdef _DEBUG
void CCAKineticsView::AssertValid() const
{
	CKineticsView::AssertValid();
}

void CCAKineticsView::Dump(CDumpContext& dc) const
{
	CKineticsView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCAKineticsView message handlers

BOOL CCAKineticsView::PreTranslateMessage(MSG* pMsg)
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
