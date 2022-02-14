// GridView.cpp : implementation of the CGridView class
//

#include "stdafx.h"

#include "Protocol.h"
#include "ProtocolDoc.h"
#include "GridView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridView

IMPLEMENT_DYNCREATE(CGridView, CFormView)

BEGIN_MESSAGE_MAP(CGridView, CFormView)
	//{{AFX_MSG_MAP(CGridView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridView construction/destruction

CGridView::CGridView()
	: CFormView(m_nID)
{
	// TODO: add construction code here

}

CGridView::CGridView(UINT nIDTemplate)
	: CFormView(nIDTemplate), m_nID(nIDTemplate)
{
	// TODO: add construction code here

}

CGridView::~CGridView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGridView diagnostics

#ifdef _DEBUG
void CGridView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CProtocolDoc* CGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProtocolDoc)));
	return (CProtocolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridView message handlers

int CGridView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// Update the view pointer in the document
	((CProtocolDoc*)GetDocument())->m_grid_view = this;
	
	return 0;
}

void CGridView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	// Update the view pointer
	ProtGetApp()->m_pDoc->m_grid_view = NULL;
}
