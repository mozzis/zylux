// PMActWatch.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol Manager.h"
#include "PMActWatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPMActivationWatcher

IMPLEMENT_DYNCREATE(CPMActivationWatcher, CWinThread)

CPMActivationWatcher::CPMActivationWatcher()
{
}

CPMActivationWatcher::~CPMActivationWatcher()
{
}

BOOL CPMActivationWatcher::InitInstance()
{
	CPMApp* pApp = (CPMApp*) AfxGetApp();

	CSyncObject* pEvents[2];
	pEvents[1] = pApp->m_pInstanceEvent;
	pEvents[0] = pApp->m_pShutdownEvent;

	DWORD dwSignalled;
	CMultiLock Locker(pEvents, 2);

	while (1)
	{
		dwSignalled = Locker.Lock(INFINITE, FALSE);
		TRACE(_T("dwSignalled is %d\n"), dwSignalled);

		// is it Shutdown?
		if ((dwSignalled-WAIT_OBJECT_0) == 0)
			break;

		// is it Instance?
		if ((dwSignalled-WAIT_OBJECT_0) == 1)
		{
			CWnd MainWindow;
			if (MainWindow.Attach(pApp->m_pMainWnd->m_hWnd))
			{
				CWnd* pWnd = MainWindow.GetLastActivePopup();
				pWnd->SetForegroundWindow();
				MainWindow.Detach();
				OnIdle(0);
			}
			else
				::MessageBeep(0);
		}
	}

	// never do ExitInstance() or Run()
	return FALSE;
}

BEGIN_MESSAGE_MAP(CPMActivationWatcher, CWinThread)
	//{{AFX_MSG_MAP(CPMActivationWatcher)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPMActivationWatcher message handlers
