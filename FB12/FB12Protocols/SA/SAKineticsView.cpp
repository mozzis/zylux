// SAKineticsView.cpp : implementation file
//

#include "stdafx.h"
#include "sa.h"
#include "SAKineticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSAKineticsView

IMPLEMENT_DYNCREATE(CSAKineticsView, CKineticsView)

CSAKineticsView::CSAKineticsView()
{
}

CSAKineticsView::~CSAKineticsView()
{
}


BEGIN_MESSAGE_MAP(CSAKineticsView, CKineticsView)
	//{{AFX_MSG_MAP(CSAKineticsView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_COPY, CKineticsView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_KINETICS_ZOOMOUT, CKineticsView::OnUpdateKineticsZoomout)
	ON_COMMAND(ID_KINETICS_ZOOMOUT, CKineticsView::OnKineticsZoomout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAKineticsView diagnostics

#ifdef _DEBUG
void CSAKineticsView::AssertValid() const
{
	CKineticsView::AssertValid();
}

void CSAKineticsView::Dump(CDumpContext& dc) const
{
	CKineticsView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSAKineticsView message handlers

BOOL CSAKineticsView::PreTranslateMessage(MSG* pMsg)
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
