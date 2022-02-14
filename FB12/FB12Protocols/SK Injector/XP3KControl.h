#if !defined(AFX_XP3KCONTROL_H__170F4621_B1BC_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_XP3KCONTROL_H__170F4621_B1BC_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// XP3KControl.h : header file
//
#include "XP3KTarget.h"
#include "XP3KDev.h"
#include <mmsystem.h>

// Response class 
class CXP3KResponse
{
public:
	CXP3KResponse(BYTE pump_num, BYTE result, BYTE status) : m_dev_num(pump_num),
		m_status(status), m_result(result) { }
	BYTE m_dev_num;
	BYTE m_status;
	BYTE m_result;
};

// Used for GetPosition response
class CXP3KResponsePosition : public CXP3KResponse
{
public:
	CXP3KResponsePosition(BYTE pump_num, BYTE result, BYTE status, int pos) : 
		CXP3KResponse(pump_num, status, result), m_position(pos) { }
	int m_position;	
};

// Command Parameter class.
class CXP3KParam
{
public:
	CXP3KParam(BYTE pump_num) : m_dev_num(pump_num) { }
	BYTE m_dev_num;
};

// Used for MoveToAbs and MoveToRelative
class CXP3KParamMoveTo : public CXP3KParam
{
public:
	CXP3KParamMoveTo(BYTE pump_num, int pos, BYTE dir = 0) : CXP3KParam(pump_num),
		m_direction(dir), m_position(pos) {}
	BYTE m_direction;
	int m_position;
};

// Used for Draw and Inject
class CXP3KParamSyringe : public CXP3KParam
{
public:
	CXP3KParamSyringe(BYTE pump_num, int amt) : CXP3KParam(pump_num), m_amount(amt) {}
	long m_amount;
};

// Used for SetSpeed
class CXP3KParamSpeed : public CXP3KParam
{
public:
	CXP3KParamSpeed(BYTE pump_num, int spd) : CXP3KParam(pump_num), m_speed_index(spd) {}
	int m_speed_index;
};

// Used for SetValve and Init
class CXP3KParamValve : public CXP3KParam
{
public:
	CXP3KParamValve(BYTE pump_num, BYTE st) : CXP3KParam(pump_num), m_state(st) {}
	BYTE m_state;
};

/////////////////////////////////////////////////////////////////////////////
// CXP3KControl window

class CXP3KControl : public CWnd
{
// Construction
public:
	CXP3KControl(CXP3KTarget* pTarget, int port = 1, long volume1 = 500, long volume2 = 500);

// Attributes
	//messages 
	enum {
		MSG_MOVE_ABS,				
		MSG_MOVE_REL,
		MSG_DRAW,
		MSG_INJECT,
		MSG_GET_POSITION,
		MSG_SET_SPEED,
		MSG_GET_STATUS,
		MSG_SET_VALVE,
		MSG_INIT,
		MSG_START,
		MSG_NONE,
		MSG_MAX
	};


	// Specific Message
	enum {
		XP3K_MSG = WM_USER + 2
	};

public:

// Operations

	// Start serial port thread
	BOOL Start();
	// Stop serial port thread
	void Stop();
	// Move the plunger on device dev_num to the absolute position pos - if valid
	BOOL MoveToAbs(BYTE dev_num, int pos);
	// Move the plunger on device dev_num to a position (relative_pos) relative
	// to the current position of the plunger.  Direction specifies up (1) or down (0)
	BOOL MoveToRelative(BYTE dev_num, BYTE direction, int relative_pos);
	// Draw amount microliters in device dev_num
	BOOL Draw(BYTE dev_num, long amount);
	// Inject amount microliters from device dev_num
	BOOL Inject(BYTE dev_num, long amount);
	// Get the position (0 - 3000) of device dev_num
	BOOL GetPosition(BYTE dev_num);
	// Set the speed index (1 fastest - 40 slowest) for device dev_num's plunger
	BOOL SetSpeed(BYTE dev_num, int speed_index);
	// Get the current status of device dev_num
	BOOL GetStatus(BYTE dev_num);
	// Set the valve to the left (state == 0) or right (state == 1) of device dev_num
	BOOL SetValve(BYTE dev_num, BYTE state);
	// Initialize device dev_num as pumping left-to-right(output_side == 0) or
	// right-to-left (output_side == 1)
	BOOL Init(BYTE dev_num, BYTE output_side=0);

	// Returns true if either pump has an outstanding message, false otherwise
	BOOL IsWaiting(void);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXP3KControl)
	//}}AFX_VIRTUAL

// IXP3Kementation
public:
	CString GetErrString(BYTE dev_num, BYTE result, BYTE status);
	virtual ~CXP3KControl();

	// Generated message map functions
protected:
	int m_port;			// Communications port pump(s) connected.
	long m_baud;		// Baud rate (9600 or 38400) at which to connect to pump(s)
	long m_volume1;		// Volume of the pump 1 syringe
	long m_volume2;		// Volume of the pump 2 syringe

	CXP3KTarget *m_pTarget;		// Target for Pump reply messages

	int m_outstanding;	// Keeps track of the number of outstanding commands (both pumps)
	BOOL m_threadactive; // True if serial port thread is active, false otherwise
	HANDLE m_hthread;	// Handle to the serial port thread
	DWORD m_threadid;	// Serial port thread ID
	DWORD m_mainthreadid;	// Main thread ID
	BOOL m_connected;	// True if serial thread is connected to the serial port, false
						// otherwise

	DWORD m_checktime1;	// Used to determine how often to send a get status command
	DWORD m_checktime2;
	
	DWORD InstanceThread(void);		// Serial port thread function
	// Process any messaged from the main thread
	int ProcessMsg(MSG &msg, CXP3KDev &pump);
	// Write the command to the pump
	BYTE SendCommand(MSG &msg, CXP3KDev &pump);
	// Send messages with command results back to the main thread
	void SendMsg(BYTE dev_num, int msg, BYTE result, BYTE status);

	// Calls InstanceThread
	static DWORD WINAPI SyncThread(LPVOID parameter);

	//{{AFX_MSG(CXP3KControl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	// Message handling function for main thread
	afx_msg LRESULT OnXP3KEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XP3KCONTROL_H__170F4621_B1BC_11D1_8C08_00400516EF5A__INCLUDED_)
