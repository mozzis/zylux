// XP3KDev.h: interface for the CXP3KDev class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XP3KDEV_H__5F87EC21_A86D_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_XP3KDEV_H__5F87EC21_A86D_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wtypes.h>

class CXP3KDev  
{
public:
	bool IsBusy(BYTE status) const;
	CXP3KDev();
	virtual ~CXP3KDev();

	short GetPort(void) const;				// returns the port
	long GetBaud(void) const;				// returns the baud rate
	BYTE GetError(void) const;				// returns the error code
	void Stop(void);						// Closes the COM port
	BOOL Start(short port, long baud);		// Opens and inits the COM port
											// Returns TRUE on success, on failure
											// returns false and sets error code
	void SetVolume(BYTE dev_num, long vol);
	long GetVolume(BYTE dev_num) const;

	// Commands to the instrument.  Return TRUE on success, FALSE on failure.
	// The value of status is unknown on failure.
	// If these functions return FALSE, use get_error to determine error

	// Draw liquid from resevoir into syringe
	// amount is in microliters.
	BOOL SendDrawCmd(BYTE dev_num, long amount);

	// Inject liquid from syringe into luminometer
	// amount is in microliters.
	BOOL SendInjectCmd(BYTE dev_num, long amount);

	// Intialize pump
	// ouput_side == 0 => pump input on left, pump output on right (default)
	// output_side != 0 => pump input on right, pump output on left
	BOOL SendInitCmd(BYTE dev_num, BYTE output_side = 0);

	// Move plunger to absolute step position
	// 0 <= step <= 3000,  step = 0 and step = 3000 are the same physical position
	BOOL SendMoveToStepCmd(BYTE dev_num, int step);


	// Move the plunger to a position relative to the current position
	// direction == 0 => Move the plunger down (draw)
	// direction != 0 => Move the plunger up (inject)
	// relative step [0..3000] position relative to the current position
	BOOL SendMoveRelativeCmd(BYTE dev_num, BYTE direction, int relative_step);

	// Sets the valve to input or output
	// state == 0 => valve set for input (draw)
	// state != 0 => valve set for output (inject)
	BOOL SendSetValveCmd(BYTE dev_num, BYTE state);

	// Set the speeds of the pump (start speed, top speed, and cutoff speed)
	// according to an index.  The XP3000 has a built-in table of common speed
	// configurations.  speed_index [1..40] indexes an entry in that table.
	BOOL SendSetSpeedCmd(BYTE dev_num, int speed_index);
	// In the future, we should implement the other speed commands.
	// For now, we will only use SetSpeed

	// Get the current device status
	// status will be one of the Device Error codes listed below.
	BOOL GetStatus(BYTE dev_num, BYTE &status);

	// Get the plunger absolute step position
	// returns an integer [0..3000] on success, a negative integer on error
	int GetPositionStep(BYTE dev_num, BYTE &status);

	// Device Error Codes
	enum
	{
		ERR_NONE = 0x00,			// No error
		ERR_INIT = 0x01,			// Initialization error
		ERR_COMMAND = 0x02,			// Invalid command
		ERR_OPERAND = 0x03,			// Invalid operand
		ERR_SEQUENCE = 0x04,		// Invalid command sequence
		ERR_EPROM = 0x06,			// EPROM failure
		ERR_NOINIT = 0x07,			// Device not Initialized
		ERR_PLUNGER = 0x09,			// Plunger Overload
		ERR_VALVE = 0x0A,			// Valve Overload
		ERR_NOMOVE = 0x0B,			// Plunger Move not Allowed
		ERR_CMD_OVERFLOW = 0x0F,	// Command Overflow

		ERR_MAX = 0xFF				
	};

	// Error codes
	enum
	{
		ERROR_NONE,					// No error
		ERROR_INIT,					// Error intializing port
		ERROR_WRITE,				// Error writing
		ERROR_READ,					// Error reading
		ERROR_TIMEDOUT,				// Read timed out
		ERROR_NOCOMM,				// Error - not connected to device
		ERROR_OTHER,				// None of the above Errors
		
		ERROR_MAX
	};

	// Misc. Public constants
	enum
	{
		PLUNGER_RESOLUTION = 3000
	};

protected:
	void Flush();
	HANDLE m_hcom;						// COM port handle
	HANDLE m_hlog;

	short m_port;						// Port number (1..4)
	long m_baud;						// Baud rate (9600 or 38400)
	BYTE m_error;						// Last error that occurred

	BOOL m_communicating;				// TRUE if COM port is open

	long m_volume1;						// Volume of pump 1 syringe (in microliters)
	long m_volume2;						// Volume of pump 2 syringe (in microliters)

	BYTE m_readbuf[16];
	BYTE m_logbuf[16];
	// Device Commands
	enum
	{
		CMD_INIT_RIGHT = 'Z',		// Initialize pump, output to the right
		CMD_INIT_LEFT = 'Y',		// Initialize pump, output to the left
		CMD_MOVE_ABS = 'A',			// Move plunger to absolute position
		CMD_DRAW_REL = 'P',			// Draw plunger to a step relative to current pos.
		CMD_INJECT_REL = 'D',		// Inject plunger to a step relative to current pos.
		CMD_INPUT_VALVE = 'I',		// Place valve in input position
		CMD_OUTPUT_VALVE = 'O',		// Place valve in output position
		CMD_SET_SPEED = 'S',		// Set the speed (start, max, and cutoff) by index
		CMD_RUN_CMD = 'R',			// Run the command string 
		CMD_GET_STATUS = 'Q',		// Get the status byte (see Device Error Codes)
		CMD_GET_POSITION = '?',		// Get the absolute position of the plunger
		CMD_GET_FIRMWARE = '&',		// Get the firmware string (probably won't be used)
		CMD_START = '/',			// Start Commands with this
		CMD_END = '\r',				// End commands with CR
		RESP_END = '\n',			// Responses end with LF

		CMD_NULL = ' '
	};

	// Misc. constants
	enum { 
		TIMEOUT_VAL = 1500,			// Number of polls for giving up on the instrument completing a movement
		POLL_TIME = 500,			// Poll interval (and read timeout) in milliseconds
		READY_BIT = 0x20
	};		

	void SetError(BYTE error);			// Set the error code
	
	BOOL OpenPort(short port, long baud);	// Open the COM port
	BOOL WriteCmd(LPCSTR cmd);
	BOOL WriteCmdPollResult(BYTE & status, LPCSTR cmd);
	BOOL WriteCmdReadResult(BYTE & status, LPCSTR cmd);
};

#endif // !defined(AFX_XP3KDEV_H__5F87EC21_A86D_11D1_8C08_00400516EF5A__INCLUDED_)
