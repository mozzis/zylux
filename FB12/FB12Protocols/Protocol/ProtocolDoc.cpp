// ProtocolDoc.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolDoc.h"
#include "Protocol.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtocolDoc

IMPLEMENT_DYNCREATE(CProtocolDoc, CDocument)

CProtocolDoc::CProtocolDoc() : m_grid_view(NULL), m_grid_frame(NULL),
	m_graph_view(NULL), m_graph_frame(NULL), m_options(ProtGetApp()->m_options)
{
	memset(&m_grid_placement, 0, sizeof(m_grid_placement));
	memset(&m_graph_placement, 0, sizeof(m_graph_placement));

	// Load some stuff from the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	SCGetAppProfileBinary(appname, "Settings", "GridFrame",
		(BYTE*)&m_grid_placement, sizeof(m_grid_placement));
	SCGetAppProfileBinary(appname, "Settings", "GraphFrame",
		(BYTE*)&m_graph_placement, sizeof(m_graph_placement));

	ProtGetApp()->m_pDoc = this;
}

CProtocolDoc::~CProtocolDoc()
{
	// Save some stuff in the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	SCWriteAppProfileBinary(appname, "Settings", "GridFrame",
		(BYTE*)&m_grid_placement, sizeof(m_grid_placement));
	SCWriteAppProfileBinary(appname, "Settings", "GraphFrame",
		(BYTE*)&m_graph_placement, sizeof(m_graph_placement));

	ProtGetApp()->m_pDoc = NULL;
}


BEGIN_MESSAGE_MAP(CProtocolDoc, CDocument)
	//{{AFX_MSG_MAP(CProtocolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolDoc diagnostics

#ifdef _DEBUG
void CProtocolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProtocolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProtocolDoc commands

void CProtocolDoc::ToggleKinetics()
{
	CProtocolApp* pApp = ProtGetApp();
	if (pApp->m_graph_template != NULL)
	{
		if (m_graph_view == NULL)
		{
			m_graph_frame = pApp->m_graph_template->CreateNewFrame(this, NULL);
			if (m_graph_frame != NULL)
			{
				bool first_time = (m_graph_placement.length == 0) ? true : false;
				if (!first_time)
				{
					m_graph_frame->SetWindowPlacement(&m_graph_placement);
				}
				pApp->m_graph_template->InitialUpdateFrame(m_graph_frame, this);
				if (first_time)
				{
					((CMDIFrameWnd*)pApp->m_pMainWnd)->MDITile(MDITILE_HORIZONTAL);
				}
			}
		}
		else
		{
			m_graph_frame->PostMessage(WM_CLOSE);
		}
	}
}

void CProtocolDoc::ToggleGrid()
{
	CProtocolApp* pApp = ProtGetApp();
	if (pApp->m_grid_template != NULL)
	{
		if (m_grid_view == NULL)
		{
			pApp->m_grid_template->CreateNewFrame(this, NULL);
			if (m_grid_frame != NULL)
			{
				bool first_time = (m_grid_placement.length == 0) ? true : false;
				if (!first_time)
				{
					m_grid_frame->SetWindowPlacement(&m_grid_placement);
				}
				pApp->m_grid_template->InitialUpdateFrame(m_grid_frame, this);
				if (first_time)
				{
					((CMDIFrameWnd*)pApp->m_pMainWnd)->MDITile(MDITILE_HORIZONTAL);
				}
			}
		}
		else
		{
			m_grid_frame->PostMessage(WM_CLOSE);
		}
	}
}
