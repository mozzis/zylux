// XP3KControl.cpp : implementation file
//

#include "stdafx.h"
#include "XP3KControl.h"
#include <queue>
using namespace std ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XP3K_STATUS_WAIT 1000
//#define XP3K_TIMELIMIT

/////////////////////////////////////////////////////////////////////////////
// CXP3KControl

CXP3KControl::CXP3KControl(CXP3KTarget * pTarget, int port, long volume1, long volume2)
	: m_threadactive(FALSE), m_outstanding(0), m_connected(FALSE),
	m_port(port), m_baud(9600), m_volume1(volume1), m_volume2(volume2), m_checktime1(0),
	m_checktime2(0)
{
	// Get the main thread id
	m_mainthreadid = GetCurrentThreadId();
	VERIFY(CreateEx(0, AfxRegisterWndClass(0, NULL, NULL, NULL),
		"Invisible Pump Man", WS_POPUP, 0,  0,  10,  10, NULL, 0));
	ASSERT(m_hWnd != NULL);
	ASSERT(pTarget != NULL);
	m_pTarget = pTarget;
}

CXP3KControl::~CXP3KControl()
{
	Stop();
}


BEGIN_MESSAGE_MAP(CXP3KControl, CWnd)
	//{{AFX_MSG_MAP(CXP3KControl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(XP3K_MSG, OnXP3KEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Creates the serial thread and sends a start message
// to it.  If no errors occur, returns TRUE, FALSE otherwise.
BOOL CXP3KControl::Start()
{
	BOOL success = FALSE;
	
#ifdef XP3K_TIMELIMIT
	// Test for time limit
	SYSTEMTIME now;
	GetLocalTime(&now);
	if (((now.wYear + 3) >= (1998 + 3))
		&& ((now.wMonth + 5) >= (6 + 5))
		&& ((now.wDay + 7) >= (1 + 7)))
	{
		char oot_str[] = "This is an evaluation copy which has expired.\n\nPlease contact Softstep Corporation to purchase this software.\n\n7801 N. Lamar, Suite A-139\nAustin, TX  78752\nwww.softstep.com\n512-323-2760";
		::MessageBox(NULL, oot_str, "XP3K - QM",
			MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_TASKMODAL);
		//SetError(ERROR_INIT);
		return FALSE;
	}
#endif

	m_connected = TRUE;
	// Create the synchronous thread
	m_hthread = CreateThread(NULL, 0, SyncThread, this, 0, &m_threadid);
	m_threadactive = (m_hthread == INVALID_HANDLE_VALUE) ? FALSE : TRUE;

	if (m_threadactive)
	{
		while ( ! PostThreadMessage(m_threadid, XP3K_MSG, MSG_START, 0));
		success = TRUE;
	}
	return success;
}


// Sends a Quit message to the serial thread and waits 
// a maximum of 5 seconds for it to exit.  Cleans up thread
// handle.
void CXP3KControl::Stop()
{
	if (m_threadactive)
	{
		// Stop the serial thread
		PostThreadMessage(m_threadid, WM_QUIT, 0, 0);

		// Wait for thread to exit (max 5 seconds)
		WaitForSingleObject(m_hthread, 5000);

		// Close the handle to the thread
		CloseHandle(m_hthread);

		// Indicate inactivity
		m_threadactive = FALSE;

	}
	m_outstanding = 0;
}


// Sends the MSG_MOVE_ABS message to the serial thread with the
// MoveTo parameters (device number and position to move).  If
// sending the message fails, cleans up parameters and returns
// FALSE.  Returns TRUE otherwise.
BOOL CXP3KControl::MoveToAbs(BYTE dev_num, int pos)
{
	// Create the MoveTo message parameter.
	CXP3KParamMoveTo * lp = new CXP3KParamMoveTo(dev_num, pos);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_MOVE_ABS, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

// Sends the MSG_MOVE_REL message to the serial thread along with
// the MoveTo parameters (device number and position and direction relative to current).
//  If sending the message fails, cleans up parameters and returns
// FALSE.  Returns TRUE otherwise.
BOOL CXP3KControl::MoveToRelative(BYTE dev_num, BYTE direction, int relative_pos)
{

	// Create the MoveTo message parameter.
	CXP3KParamMoveTo * lp = new CXP3KParamMoveTo(dev_num, relative_pos, direction);

	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_MOVE_REL, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

// Sends the MSG_DRAW message to the serial thread along with the
// Syringe command parameters (device number and amount to draw).  If
// sending the message fails, cleans up parameters and returns
// FALSE.  Returns TRUE otherwise.
BOOL CXP3KControl::Draw(BYTE dev_num, long amount)
{
	CXP3KParamSyringe * lp = new CXP3KParamSyringe(dev_num, amount);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_DRAW, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

// Sends the MSG_INJECT message to the serial thread along with the
// Syringe command parameters (device number and amount to inject).  If
// sending the message fails, cleans up parameters and returns
// FALSE.  Returns TRUE otherwise.
BOOL CXP3KControl::Inject(BYTE dev_num, long amount)
{
	CXP3KParamSyringe * lp = new CXP3KParamSyringe(dev_num, amount);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_INJECT, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::GetPosition(BYTE dev_num)
{
	CXP3KParam * lp = new CXP3KParam(dev_num);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_GET_POSITION, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::SetSpeed(BYTE dev_num, int speed_index)
{	
	// Just use 16 bits for speed_index
	//LPARAM lp = speed_index & 0x0000FFFF;
	CXP3KParamSpeed * lp = new CXP3KParamSpeed(dev_num, speed_index);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_SET_SPEED, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::GetStatus(BYTE dev_num)
{
	CXP3KParam * lp = new CXP3KParam(dev_num);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_GET_STATUS, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::SetValve(BYTE dev_num, BYTE state)
{
	CXP3KParamValve * lp = new CXP3KParamValve(dev_num, state);
	//LPARAM lp = 0x00000000;
	//lp = lp | state;
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_SET_VALVE, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::Init(BYTE dev_num, BYTE output_side /* = 0 */)
{
	//LPARAM lp = 0x00000000;
	//lp = lp | output_side;
	CXP3KParamValve * lp = new CXP3KParamValve(dev_num, output_side);
	if (PostThreadMessage(m_threadid, XP3K_MSG, MSG_INIT, (LPARAM)lp))
	{
		m_outstanding++;
		return TRUE;
	}
	else
	{
		delete lp;
		return FALSE;
	}
}

BOOL CXP3KControl::IsWaiting(void)
{
	return ((m_outstanding == 0) ? FALSE : TRUE);
}


DWORD WINAPI CXP3KControl::SyncThread(void * parameter)
{
	return ((CXP3KControl *)parameter)->InstanceThread();
}

DWORD CXP3KControl::InstanceThread(void)
{
	MSG msg;
	BYTE status1, status2, result1, result2;
	int dev1_wait = MSG_NONE;
	int dev2_wait = MSG_NONE;
	bool new_msg;

	queue<MSG> dev1_Q;
	queue<MSG> dev2_Q;
	CXP3KDev pump;


	pump.SetVolume(1, m_volume1);
	pump.SetVolume(2, m_volume2);


	bool exit = false;
	while (!exit)
	{
		new_msg = false;
		if ((dev1_wait == MSG_NONE) && (dev2_wait == MSG_NONE))	// Just wait for a msg
		{
			if (!GetMessage(&msg, 0, 0, 0))
				exit = true;
			else
				new_msg = true;
		}
		else 
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				new_msg = true;
				if (msg.message == WM_QUIT)
					exit = true;
			}
		}

		// Put the new message on the queue
		if (new_msg && msg.message == XP3K_MSG)
		{
			// If it is the Start message, process immediately
			if (msg.wParam == MSG_START)
			{
				ProcessMsg(msg, pump);
			}
			else
			{
				if (((CXP3KParam *)msg.lParam)->m_dev_num == 1)
					dev1_Q.push(msg);
				if (((CXP3KParam *)msg.lParam)->m_dev_num == 2)
					dev2_Q.push(msg);
			}
		}
		if (new_msg)
			DispatchMessage(&msg);
		
		// First Check on Dev1
		if (dev1_wait != MSG_NONE)	// Check the status of the last dev1 command
		{
			status1 = 0x00;
			result1 = 0x00;
			
			if (timeGetTime() > m_checktime1)
			{
				//Sleep(500);
				if (pump.GetStatus(1, status1))
				{
					result1 = pump.ERROR_NONE;
					if (!pump.IsBusy(status1))	// If pump is not busy, send result
					{
						SendMsg(1, dev1_wait, result1, status1);
						dev1_wait = MSG_NONE;
					}
				}
				else	// An error occurred getting the status of the pump
				{
					result1 = pump.GetError();
					status1 = 0x00;
					SendMsg(1, dev1_wait, result1, status1);
					dev1_wait = MSG_NONE;
				}
			}
		}


		if ((dev1_wait == MSG_NONE) && (!dev1_Q.empty()))
		{
			// Process the next message.
			msg = dev1_Q.front();
			dev1_Q.pop();
			dev1_wait = ProcessMsg(msg, pump);
			while((dev1_wait == MSG_GET_POSITION) ||
				  (dev1_wait == MSG_GET_STATUS))
			{
				if (!dev1_Q.empty())
				{
					msg = dev1_Q.front();
					dev1_Q.pop();
					dev1_wait = ProcessMsg(msg, pump);
				}
				else
					dev1_wait = MSG_NONE;
			}
		}

		// Check on Dev2
		if (dev2_wait != MSG_NONE)	// Check the status of the last dev2 command
		{
			status2 = 0x00;
			result2 = 0x00;
			
			//Sleep(500);
			if (timeGetTime() > m_checktime2)
			{
				if (pump.GetStatus(2, status2))
				{
					result2 = pump.ERROR_NONE;
					if (!pump.IsBusy(status2))	// If pump is not busy, send result
					{
						SendMsg(2, dev2_wait, result2, status2);
						dev2_wait = MSG_NONE;
					}
				}
				else	// An error occurred getting the status of the pump
				{
					result2 = pump.GetError();
					status2 = 0x00;
					SendMsg(2, dev2_wait, result2, status2);
					dev2_wait = MSG_NONE;
				}
			}

		}

		if ((dev2_wait == MSG_NONE) && (!dev2_Q.empty()))
		{
			// Process the next message.
			msg = dev2_Q.front();
			dev2_Q.pop();
			dev2_wait = ProcessMsg(msg, pump);
			while((dev2_wait == MSG_GET_POSITION) ||
				  (dev2_wait == MSG_GET_STATUS))
			{
				if (!dev2_Q.empty())
				{
					msg = dev2_Q.front();
					dev2_Q.pop();
					dev2_wait = ProcessMsg(msg, pump);
				}
				else
					dev2_wait = MSG_NONE;
			}
		}	



	
	}
	pump.Stop();

	return 0;
}

void CXP3KControl::SendMsg(BYTE dev_num, int msg, BYTE result, BYTE status)
{
	status = status & 0x0F; // Mask off unused bits
	CXP3KResponse *lp = new CXP3KResponse(dev_num, result, status);

	::SendNotifyMessage(m_hWnd, XP3K_MSG, (WPARAM)msg, (LPARAM)lp);
}

int CXP3KControl::ProcessMsg(MSG &msg, CXP3KDev &pump)
{
	LPARAM send_back = 0x00000000;
	BYTE dev_num, status, result;
	if (msg.wParam == MSG_GET_POSITION)
	{
		CXP3KParam *pParam = ((CXP3KParam *)msg.lParam);
		dev_num = pParam->m_dev_num;
		delete pParam;	// Clean up allocated message parameter

		int step = pump.GetPositionStep(dev_num, status);
		status = status & 0x0F; // Mask off unused bits

		result = (step >= 0)? pump.ERROR_NONE : pump.GetError();
		CXP3KResponsePosition *lp = new CXP3KResponsePosition(dev_num, result, status, step);

		::SendNotifyMessage(m_hWnd, XP3K_MSG, msg.wParam, (LPARAM)lp);
	}
	else if (msg.wParam == MSG_GET_STATUS)
	{
		CXP3KParam *pParam = ((CXP3KParam *)msg.lParam);
		dev_num = pParam->m_dev_num;
		delete pParam;

		result = (pump.GetStatus(dev_num, status))? pump.ERROR_NONE : pump.GetError();
		//status = status & 0x0F; // Mask off unused bits
		SendMsg(dev_num, msg.wParam, result, status);
		//::SendNotifyMessage(m_hWnd, XP3K_MSG, msg.wParam, send_back);
	}
	if (msg.wParam == MSG_START)
	{
		// Start message has no parameter, and only sends back a result.
		result = (pump.Start(m_port, m_baud)) ? pump.ERROR_NONE : pump.GetError();
		send_back = (send_back | result) << 24;
		::SendNotifyMessage(m_hWnd, XP3K_MSG, msg.wParam, send_back);
		msg.wParam = MSG_NONE;
	}
	else // a non-query message
	{
		dev_num = ((CXP3KParam *)msg.lParam)->m_dev_num;

		// SendCommand writes the command to the port, and cleans
		// up the parameter memory.
		result = SendCommand(msg, pump);
		if (result != pump.ERROR_NONE)	// Write error
		{
			status = 0x00;
			SendMsg(dev_num, msg.message, result, status);
		}
	}
	
	return (msg.wParam);
}

// Handles the non-query commands
BYTE CXP3KControl::SendCommand(MSG & msg, CXP3KDev &pump)
{
	BYTE result, dev_num;
	switch(msg.wParam)
	{
	
		case MSG_MOVE_ABS:
		{
			CXP3KParamMoveTo * pParam = (CXP3KParamMoveTo *)msg.lParam;
			dev_num = pParam->m_dev_num;
			int pos = pParam->m_position;
			delete pParam;
			result = (pump.SendMoveToStepCmd(dev_num, pos))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;
		}
		break;

		case MSG_MOVE_REL:
		{
			CXP3KParamMoveTo * pParam = (CXP3KParamMoveTo *)msg.lParam;
			dev_num = pParam->m_dev_num;
			int pos = pParam->m_position;
			BYTE direction = pParam->m_direction;
			delete pParam;

			result = (pump.SendMoveRelativeCmd(dev_num, direction, pos))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		case MSG_DRAW:
		{
			CXP3KParamSyringe *pParam = (CXP3KParamSyringe *)msg.lParam;
			dev_num = pParam->m_dev_num;
			long amt = pParam->m_amount;
			delete pParam;

			result = (pump.SendDrawCmd(dev_num, amt)? pump.ERROR_NONE : pump.GetError());
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		case MSG_INJECT:
		{
			CXP3KParamSyringe *pParam = (CXP3KParamSyringe *)msg.lParam;
			dev_num = pParam->m_dev_num;
			long amt = pParam->m_amount;
			delete pParam;

			result = (pump.SendInjectCmd(dev_num, amt))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		case MSG_SET_SPEED:
		{
			CXP3KParamSpeed *pParam = (CXP3KParamSpeed *)msg.lParam;
			dev_num = pParam->m_dev_num;
			int speed = pParam->m_speed_index;
			delete pParam;

			result = (pump.SendSetSpeedCmd(dev_num, speed))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		case MSG_SET_VALVE:
		{
			CXP3KParamValve *pParam = (CXP3KParamValve *)msg.lParam;
			dev_num = pParam->m_dev_num;
			BYTE state = pParam->m_state;
			delete pParam;

			result = (pump.SendSetValveCmd(dev_num, state))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		case MSG_INIT:
		{
			CXP3KParamValve *pParam = (CXP3KParamValve *)msg.lParam;
			dev_num = pParam->m_dev_num;
			BYTE output_side = pParam->m_state;
			delete pParam;

			result = (pump.SendInitCmd(dev_num, output_side))? pump.ERROR_NONE : pump.GetError();
			if (dev_num == 1)
				m_checktime1 = timeGetTime() + XP3K_STATUS_WAIT;
			else
				m_checktime2 = timeGetTime() + XP3K_STATUS_WAIT;

		}
		break;

		default:
		break;
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CXP3KControl message handlers
LRESULT CXP3KControl::OnXP3KEvent(WPARAM wParam, LPARAM lParam)
{
	BYTE result, status, dev_num;
	int pos;
	
	if (wParam == MSG_START)
	{
		result = (lParam >> 24) & 0x000000FF;
	}
	else 
	{
		if (wParam == MSG_GET_POSITION)
		{
			CXP3KResponsePosition *pResponse = (CXP3KResponsePosition *)lParam;
			dev_num = pResponse->m_dev_num;
			result = pResponse->m_result;
			status = pResponse->m_status;
			pos = pResponse->m_position;
			delete pResponse;
		}
		else
		{
			CXP3KResponse *pResponse = (CXP3KResponse *)lParam;
			dev_num = pResponse->m_dev_num;
			result = pResponse->m_result;
			status = pResponse->m_status;
			delete pResponse;
		}
	}
	if (m_outstanding > 0)
	{
		m_outstanding--;
	}

	switch (wParam) 
	{
	case MSG_START:
		m_pTarget->XP3KStartResponse(result);
	break;

	case MSG_MOVE_ABS:
		m_pTarget->XP3KMoveToAbsResponse(dev_num, result, status);
	break;

	case MSG_MOVE_REL:
		m_pTarget->XP3KMoveToRelativeResponse(dev_num, result, status);
	break;

	case MSG_DRAW:
		m_pTarget->XP3KDrawResponse(dev_num, result, status);
	break;

	case MSG_INJECT:
		m_pTarget->XP3KInjectResponse(dev_num, result, status);
	break;

	case MSG_GET_POSITION:
		m_pTarget->XP3KGetPositionResponse(dev_num, result, status, pos);
	break;

	case MSG_SET_SPEED:
		m_pTarget->XP3KSetSpeedResponse(dev_num, result, status);
	break;

	case MSG_GET_STATUS:
		m_pTarget->XP3KGetStatusResponse(dev_num, result, status);
	break;

	case MSG_SET_VALVE:
		m_pTarget->XP3KSetValveResponse(dev_num, result, status);
	break;

	case MSG_INIT:
		m_pTarget->XP3KInitResponse(dev_num, result, status);
	break;

	default:
		break;
	}

	return TRUE;
}


CString CXP3KControl::GetErrString(BYTE dev_num, BYTE result, BYTE status)
{
	CString msg = "No Error";

	// First check for communication errors
	if (result != CXP3KDev::ERROR_NONE)
	{
		switch (result)
		{
			case CXP3KDev::ERROR_INIT:
				msg.Format("%s %d.", "Error connecting to injector", dev_num);
			break;
			case CXP3KDev::ERROR_WRITE:
				msg.Format("%s %d.", "Error while writing commands to injector", dev_num);
			break;
			case CXP3KDev::ERROR_READ:
				msg.Format("%s %d.", "Error while reading replies from injector", dev_num);
			break;
			case CXP3KDev::ERROR_TIMEDOUT:
				msg.Format("%s %d %s.", "Timeout waiting for injector to respond.\nVerify that injector", 
					dev_num, "is connected to the PC.");
			break;
			case CXP3KDev::ERROR_NOCOMM:
			case CXP3KDev::ERROR_OTHER:
			default:
				msg = "Unknown serial error occurred.";
			break;
		}
	}
	else if (status != CXP3KDev::ERR_NONE)
	{
		// Now check for device errors.
		switch (status)
		{
			case CXP3KDev::ERR_INIT:
				msg.Format("%s %d.", "Cavro XP3000 initialization error. \nPlease restart injector", dev_num);
			break;
			case CXP3KDev::ERR_COMMAND:
				msg.Format("%s %d.", "Cavro XP3000 invalid command error for injector", dev_num);
			break;
			case CXP3KDev::ERR_OPERAND:
				msg.Format("%s %d.", "Cavro XP3000 invalid operand error for injector", dev_num);
			break;
			case CXP3KDev::ERR_SEQUENCE:
				msg.Format("%s %d.", "Cavro XP3000 invalid command sequence error.\nPlease restart injector", dev_num);
			break;
			case CXP3KDev::ERR_EPROM:
				msg.Format("%s %d.", "Cavro XP3000 EPROM failure.\nPlease restart injector", dev_num);
			break;
			case CXP3KDev::ERR_NOINIT:
				msg.Format("%s %d.", "Cavro XP3000 not initialized for injector", dev_num);
			break;
			case CXP3KDev::ERR_PLUNGER:
				msg.Format("%s %d.", "Cavro XP3000 plunger overload error.\nPlease restart injector", dev_num);
			break;
			case CXP3KDev::ERR_VALVE:
				msg.Format("%s %d.", "Cavro XP3000 valve overload error.\nPlease restart injector", dev_num);
			break;
			case CXP3KDev::ERR_NOMOVE:
				msg.Format("%s %d.", "Cavro XP3000 plunger move not allowed for injector", dev_num);
			break;
			case CXP3KDev::ERR_CMD_OVERFLOW:
				msg.Format("%s %d.", "Cavro XP3000 command overflow error.\nPlease restart injector", dev_num);
			break;
			default:
				msg.Format("%s %d.", "Unknown injector error occurred for injector", dev_num);
			break;
		}
	}

	return msg;
}


