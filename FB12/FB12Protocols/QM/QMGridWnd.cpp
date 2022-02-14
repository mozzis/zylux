// QMGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "QM.h"
#include "QMGridWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_REGISTER(CQMGridWnd, CS_DBLCLKS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// CQMGridWnd

CQMGridWnd::CQMGridWnd()
{
}

CQMGridWnd::~CQMGridWnd()
{
}


BEGIN_MESSAGE_MAP(CQMGridWnd, CProtocolGridWnd)
	//{{AFX_MSG_MAP(CQMGridWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CQMGridWnd message handlers

void CQMGridWnd::OnInitialUpdate()
{
	CProtocolGridWnd::OnInitialUpdate();

	//EnableOleDataSource(GX_DNDTEXT | GX_DNDSTYLES |
	//	GX_DNDCOMPOSE | GX_DNDDIFFRANGEDLG | GX_DNDCOLHEADER);
	EnableOleDataSource(GX_DNDTEXT | GX_DNDROWHEADER);

	CGXGridParam *param = GetParam();
	param->EnableUndo(FALSE);
	param->EnableMoveRows(FALSE);
	param->EnableMoveCols(FALSE);

	SetRowCount(1);
	SetColCount(1);

	SetStyleRange(CGXRange(0, 1), CGXStyle().SetValue("RLU/s"));

	ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_STATIC));

	SetReadOnly(TRUE);

	EnableGridToolTips();
	param->GetStylesMap()->AddUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));

	//GetParam()->EnableUndo(TRUE);
}
/*
void CQMGridWnd::CMCreateMenu(CMenu& menu)
{
	if (CanCopy())
	{
		CMAddItemNG(menu, ID_EDIT_COPY, "&Copy");
	}
}
*/
