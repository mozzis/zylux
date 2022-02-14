// InjectorToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "SK.h"
#include "SKDoc.h"
#include "InjectorToolBar.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInjectorToolBar

CInjectorToolBar::CInjectorToolBar() : is_working(false), m_timerid(0), m_direction(0)
{
}

CInjectorToolBar::~CInjectorToolBar()
{
	// Revoke timer
	if (m_timerid != 0)
	{
		timeKillEvent(m_timerid);
	}
}


//BEGIN_MESSAGE_MAP(CInjectorToolBar, CToolBarCtrl)
BEGIN_MESSAGE_MAP(CInjectorToolBar, CToolBar)
	//{{AFX_MSG_MAP(CInjectorToolBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectorToolBar message handlers

void CInjectorToolBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int i = 0;
	RECT draw_rect, inject_rect;
	GetItemRect(CommandToIndex(ID_BUTTON_DOWN), &draw_rect);
	GetItemRect(CommandToIndex(ID_BUTTON_UP), &inject_rect);
	if ((point.x >= draw_rect.left) && (point.x <= draw_rect.right) &&
		(point.y >= draw_rect.top) && (point.y <= draw_rect.bottom) &&
		(GetToolBarCtrl().GetState(ID_BUTTON_DOWN) & TBSTATE_ENABLED))
	{
		//SetCapture();
		if (!is_working)
		{
			is_working = true;
			m_direction = 0;
			//AfxMessageBox("Hello");
		}
	}
	else if ((point.x >= inject_rect.left) && (point.x <= inject_rect.right) &&
		(point.y >= inject_rect.top) && (point.y <= inject_rect.bottom) &&
		(GetToolBarCtrl().GetState(ID_BUTTON_UP) & TBSTATE_ENABLED))
	{

		if (!is_working)
		{
			is_working = true;
			m_direction = 1;
			//AfxMessageBox("Hello");
		}
	}
	
	if (is_working)
	{
		TIMECAPS time_caps;
		timeGetDevCaps(&time_caps, sizeof(time_caps));
		UINT move_times = 500;  // every half second.
		if (move_times < time_caps.wPeriodMin)
		{
			move_times = time_caps.wPeriodMin;
		}
		if (move_times > time_caps.wPeriodMax)
		{
			move_times = time_caps.wPeriodMax;
		}
		m_timerid = timeSetEvent(move_times, 100, ManualTimer, (DWORD)this, TIME_PERIODIC);
	}
	CToolBar::OnLButtonDown(nFlags, point);
}

void CInjectorToolBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (is_working)
	{
		// Revoke timer
		if (m_timerid != 0)
		{
			timeKillEvent(m_timerid);
			m_timerid = 0;
		}

		is_working = false;
	}

	CToolBar::OnLButtonUp(nFlags, point);
}

void CALLBACK CInjectorToolBar::ManualTimer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	((CInjectorToolBar *)dwUser)->InstanceTimer();
}

void CInjectorToolBar::InstanceTimer(void)
{
	CSKDoc * pDoc = (CSKDoc *)SKGetApp()->m_pDoc;
	if (((m_direction == 0) && !(GetToolBarCtrl().GetState(ID_BUTTON_DOWN) & TBSTATE_ENABLED))  ||
		((m_direction == 1) && !(GetToolBarCtrl().GetState(ID_BUTTON_UP) & TBSTATE_ENABLED)) )
	{
		// The button is being pushed but it is disabled now (by SKDoc)
		// Revoke the timer and stop working
		timeKillEvent(m_timerid);
		m_timerid = 0;
		is_working = false;
	}
		
	if ((is_working) && (pDoc != NULL))
	{
		// Manually inject by 120 steps -- works well for all syringe volumes ;-}
		pDoc->ManualInject(m_direction, 120);	
	}
}

