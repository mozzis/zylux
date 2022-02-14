// XP3KDev.cpp: implementation of the CXP3KDev class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <mmsystem.h>
#include "XP3KDev.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#define XP3K_LOG

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXP3KDev::CXP3KDev() : m_port(1), m_baud(9600),m_error(ERROR_NONE), 
						m_communicating(FALSE), m_volume1(500), m_volume2(500)
{
}

CXP3KDev::~CXP3KDev()
{
	// Make sure the COM port is closed.
	Stop();
}

BOOL CXP3KDev::Start(short port, long baud)
{	
	// Serial logging stuff.
#ifdef XP3K_LOG
	m_hlog = CreateFile("C:\\TMP\\XP3K.LOG", GENERIC_WRITE,
			0, NULL, OPEN_ALWAYS, 0, NULL);
		
	if (m_hlog == INVALID_HANDLE_VALUE)
		return FALSE;
	else
#endif
		return (OpenPort(port, baud));
}


BOOL CXP3KDev::OpenPort(short port, long baud)
{
	BOOL success = FALSE;
	SetError(ERROR_NONE);
	// Only open port if 1) it's not
	// already open, 2) the port is valid, and
	// 3) the baud is valid
	if (!m_communicating &&
		((port >= 1) && (port <= 8)) &&
		((baud == 38400) || (baud == 9600)))
	{
		// Open the COM port
		CString com_str;
		com_str.Format("COM%d", port);
		m_hcom = CreateFile(LPCSTR(com_str), GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		// Check to see if the COM port opened successfully
		if (m_hcom != INVALID_HANDLE_VALUE)
		{
			// Get the current COM state information
			DCB dcb;
			if (GetCommState(m_hcom, &dcb))
			{
				// Change the COM state information
				dcb.BaudRate = baud;
				dcb.fBinary = TRUE;
				dcb.fParity = FALSE;
				dcb.fOutxCtsFlow = FALSE;
				dcb.fOutxDsrFlow = FALSE;
				dcb.fDtrControl = DTR_CONTROL_ENABLE;
				dcb.fDsrSensitivity = FALSE;
				dcb.fTXContinueOnXoff = FALSE;
				dcb.fOutX = FALSE;
				dcb.fInX = FALSE;
				dcb.fErrorChar = FALSE;
				dcb.fNull = FALSE;
				dcb.fRtsControl = RTS_CONTROL_ENABLE;
				dcb.fAbortOnError = TRUE;
				dcb.ByteSize = 8;
				dcb.Parity = NOPARITY;
				dcb.StopBits = ONESTOPBIT;
				// Set the COM state information
				if (SetCommState(m_hcom, &dcb))
				{
					COMMTIMEOUTS CommTimeouts;
					if (GetCommTimeouts(m_hcom,  &CommTimeouts))
					{
						CommTimeouts.ReadIntervalTimeout = 0;
						CommTimeouts.ReadTotalTimeoutMultiplier = 0;
						CommTimeouts.ReadTotalTimeoutConstant = POLL_TIME * 8;
						CommTimeouts.WriteTotalTimeoutMultiplier = 0;
						CommTimeouts.WriteTotalTimeoutConstant = 0;
						
						if (SetCommTimeouts(m_hcom, &CommTimeouts))
						{

							// Set port and baud properties
							m_port = port;
							m_baud = baud;

							// Indicate success
							success = TRUE;
							SetError(ERROR_NONE);
							m_communicating = TRUE;
						}
						else
						{
							// We were unable to set the COM timeout
							// information, so just shut down
							Stop();
							SetError(ERROR_INIT);
						}
					}
					else
					{
						// We were unable to get the COM timeout
						// information, so just shut down
						Stop();
						SetError(ERROR_INIT);
					}
				}
				else
				{
					// We were unable to set the COM sate
					// information, so just shut down
					Stop();
					SetError(ERROR_INIT);
				}
			}
			else
			{
				// We couldn't get the COM state information
				// so just shut everything down
				Stop();
				SetError(ERROR_INIT);
			}



		}
		else
		{
			// CreateFile failed
			SetError(ERROR_INIT);
		}
	}
	else
	{
		// bad baud or port
		SetError(ERROR_INIT);
	}

	return success;
}


void CXP3KDev::Stop(void)
{
#ifdef XP3K_LOG
	CloseHandle(m_hlog);
#endif 

	CloseHandle(m_hcom);
	m_communicating = FALSE;
}


BYTE CXP3KDev::GetError(void) const
{
	return m_error;
}

long CXP3KDev::GetBaud(void) const
{
	return m_baud;
}

short CXP3KDev::GetPort(void) const
{
	return m_port;
}

// GetVolume()
//
// Returns the appropriate syringe volume

long CXP3KDev::GetVolume(BYTE dev_num) const
{
	if (dev_num == 1)
		return m_volume1;
	else
		return m_volume2;
}

// SetVolume()
//
// Set the volume of the given syringe 

void CXP3KDev::SetVolume(BYTE dev_num, long vol)
{
	if (vol >= 0)
		if (dev_num == 1)
			m_volume1 = vol;
		else
			m_volume2 = vol;
}




void CXP3KDev::SetError(BYTE error)
{
	m_error = error;
}



// GetPositionStep()
//
// Send the Get Absolute position command and wait for result

int CXP3KDev::GetPositionStep(BYTE dev_num, BYTE &status)
{
	int step = -1;
	CString cmd;

	cmd.Format("%d%c", dev_num, CMD_GET_POSITION);
	if (WriteCmdReadResult(status, cmd))
	{
		status = status & 0x0F;  // Mask off unused bits
		if (status == ERR_NONE)
		{
			char num_str[5];
			int idx = 0;
			while ((idx < 4) && (m_readbuf[idx+3] != 0x03))
			{
				num_str[idx] = (char)m_readbuf[idx+3];
				idx++;
			}
			num_str[idx] = 0x00;
			step = atoi((char *)num_str);
		}
	}
	
	return (step);
}


// GetStatus()
//
// Send Query status command wait for result.

BOOL CXP3KDev::GetStatus(BYTE dev_num, BYTE &status)
{
	CString cmd;

	cmd.Format("%d%c", dev_num, CMD_GET_STATUS);
	BOOL success = WriteCmdReadResult(status, cmd);
	//status = status & 0x0F; // Mask off unused bits
	return (success);
}



// SendInitCmd()
//
// Send command to initialize the pump

BOOL CXP3KDev::SendInitCmd(BYTE dev_num, BYTE output_side /* = 0 */)
{
	CString cmd;
	int force_val = 0;

	long vol = (dev_num == 1) ? m_volume1 : m_volume2;

	if ((vol > 100) && (vol < 1000))
	{
		force_val = 1;
	}
	else if (vol <= 100)
	{
		force_val = 2;
	}
	if (output_side == 0)
	{
		cmd.Format("%d%c%d%c", dev_num, CMD_INIT_RIGHT, force_val, CMD_RUN_CMD);
	}
	else
	{
		cmd.Format("%d%c%d%c", dev_num, CMD_INIT_LEFT, force_val, CMD_RUN_CMD);
	}
	return (WriteCmd(cmd));
}

// SendMoveRelativeCmd()
//
// Send command to Move the plunger to a position relative to the current position.

BOOL CXP3KDev::SendMoveRelativeCmd(BYTE dev_num, BYTE direction, int relative_step)
{
	CString cmd;
	SetError(ERROR_NONE);
	if ((relative_step >= 0) && (relative_step <= PLUNGER_RESOLUTION))
	{
		if (direction == 0)
		{
			cmd.Format("%d%c%d%c", dev_num, CMD_DRAW_REL, relative_step, CMD_RUN_CMD);
		}
		else
		{
			cmd.Format("%d%c%d%c", dev_num, CMD_INJECT_REL, relative_step, CMD_RUN_CMD);
		}
		return (WriteCmd(cmd));
	}
	else
	{
		SetError(ERROR_OTHER);
		return FALSE;
	}
}

// SendMoveToStepCmd()
//
// Send command to move the plunger to an absolute position.

BOOL CXP3KDev::SendMoveToStepCmd(BYTE dev_num, int step)
{
	CString cmd;
	SetError(ERROR_NONE);
	if ((step >= 0) && (step <= PLUNGER_RESOLUTION))
	{
		cmd.Format("%d%c%d%c", dev_num, CMD_MOVE_ABS, step, CMD_RUN_CMD);
		return (WriteCmd(cmd));
	}
	else
	{
		SetError(ERROR_OTHER);
		return FALSE;
	}
}

// SendSetSpeedCmd()
//
// Send command to set the Speed index for the pump.

BOOL CXP3KDev::SendSetSpeedCmd(BYTE dev_num, int speed_index)
{
	CString cmd;
	SetError(ERROR_NONE);
	if ((speed_index >= 1) && (speed_index <= 40))
	{
		cmd.Format("%d%c%d%c", dev_num, CMD_SET_SPEED, speed_index,  CMD_RUN_CMD);
		return (WriteCmd(cmd));
	}
	else
	{
		SetError(ERROR_OTHER);
		return FALSE;
	}
}

// SendSetValveCmd()
//
// Send command to change the valve for input or output.

BOOL CXP3KDev::SendSetValveCmd(BYTE dev_num, BYTE state)
{
	CString cmd;
	if (state == 0)
	{
		cmd.Format("%d%c%c", dev_num, CMD_INPUT_VALVE, CMD_RUN_CMD);
	}
	else
	{
		cmd.Format("%d%c%c", dev_num, CMD_OUTPUT_VALVE, CMD_RUN_CMD);
	}
	return (WriteCmd(cmd));
}

// Returns true if the Device is busy, false otherwise
bool CXP3KDev::IsBusy(BYTE status) const
{
	return ((status & READY_BIT) == 0);
}

BOOL CXP3KDev::WriteCmdPollResult(BYTE & status, LPCSTR cmd)
{	
	BOOL success = FALSE;
	SetError(ERROR_NONE);
	BYTE tmp_stat;
	if (WriteCmdReadResult(tmp_stat, cmd))
	{
		int num_tries = 0;
		CString poll_cmd;

		poll_cmd.Format("%c", CMD_GET_STATUS);
		while (((tmp_stat & READY_BIT) == 0) && (num_tries < TIMEOUT_VAL))
		{
			Sleep(POLL_TIME);
			if (!WriteCmdReadResult(tmp_stat, LPCSTR(poll_cmd)))
				break;
			num_tries++;
		}

		if (((tmp_stat & READY_BIT) == 0) && (num_tries >= TIMEOUT_VAL))
		{
			SetError(ERROR_TIMEDOUT);
		}
		else if (GetError() == ERROR_NONE)
		{
			success = TRUE;
			status = tmp_stat & 0x0F;
		}
	}

	return success;
}


BOOL CXP3KDev::WriteCmdReadResult(BYTE & status, LPCSTR cmd)
{
	BOOL success = FALSE;
	SetError(ERROR_NONE);
#ifdef XP3K_LOG
	m_logbuf[1] = '\0';
	DWORD log_bytes = 0;
	DWORD log_to_write = 0;
	CString log_buf;
#endif

	if (m_communicating)
	{
		DWORD num_to_write = 0;
		DWORD total_bytes = 0;
		CString write_buf;
		bool write_again = true;

		write_buf.Format("%c%s%c", CMD_START, cmd, CMD_END);
		num_to_write = write_buf.GetLength();

		while (write_again)
		{
			if (!WriteFile(m_hcom, (LPCVOID)LPCSTR(write_buf), num_to_write, &total_bytes, NULL))
			{
				SetError(ERROR_WRITE);
			}
			else
			{
			#ifdef XP3K_LOG
				log_buf.Format("Sending: %c%s%c\n", CMD_START, cmd, CMD_END);
				log_to_write = log_buf.GetLength();
				WriteFile(m_hlog, (LPCVOID)LPCSTR(log_buf), log_to_write, &log_bytes, NULL);
				log_buf = "Reading:";
				log_to_write = log_buf.GetLength();
				WriteFile(m_hlog, (LPCVOID)LPCSTR(log_buf), log_to_write, &log_bytes, NULL);
			#endif

				int idx = 0;
				bool eoc = false;
				BYTE readch;
				while(!eoc)
				{
					if(!ReadFile(m_hcom, &readch, 1, &total_bytes, NULL))
					{
						SetError(ERROR_READ);
						write_again = false;
						break;
					}
					else 
					{
					#ifdef XP3K_LOG
						log_buf.Format("%X", readch);
						log_to_write = log_buf.GetLength();
						WriteFile(m_hlog, (LPCVOID)LPCSTR(log_buf), log_to_write, &log_bytes, NULL);
					#endif
						// Only timeout if we do not get any kind of response with the
						// time out time.
						if ((idx == 0) && (total_bytes < 1)) 
						{
							SetError(ERROR_TIMEDOUT);
							write_again = false;
						#ifdef XP3K_LOG
							log_buf = "Time Out!\n";
							log_to_write = log_buf.GetLength();
							WriteFile(m_hlog, (LPCVOID)LPCSTR(log_buf), log_to_write, &log_bytes, NULL);
						#endif
							break;
						}
						else
						{
							if (readch != RESP_END)
							{
								if ((idx == 0) && (readch != CMD_START))
								{
									// Gettting a bad response, throw away
									// the rest, and write the command again.
									if (readch != 0xFF)
									{
										Flush();
										break;
									}
								}
								else
									m_readbuf[idx++] = readch;
							}
							else
							{
								eoc = true;
								if (idx > 0)
									write_again = false;
							#ifdef XP3K_LOG
								m_logbuf[0] = '\n';
								WriteFile(m_hlog, (LPCVOID)m_logbuf, 1, &log_bytes, NULL);
							#endif
							}
						}
					}
				}
				if (eoc)
				{
					success = TRUE;
					status = m_readbuf[2];
				}
			}
		}
	}
	else
	{
		SetError(ERROR_NOCOMM);
	}

	return success;
}

BOOL CXP3KDev::WriteCmd(LPCSTR cmd)
{
	BOOL success = FALSE;
	SetError(ERROR_NONE);
#ifdef XP3K_LOG
	DWORD log_bytes = 0;
	DWORD log_to_write = 0;
	CString log_buf;
#endif

	if (m_communicating)
	{
		DWORD num_to_write = 0;
		DWORD total_bytes = 0;
		CString write_buf;

		write_buf.Format("%c%s%c", CMD_START, cmd, CMD_END);
		num_to_write = write_buf.GetLength();

#ifdef XP3K_LOG
		log_buf.Format("Sending: %c%s%c\n", CMD_START, cmd, CMD_END);
		log_to_write = log_buf.GetLength();
		WriteFile(m_hlog, (LPCVOID)LPCSTR(log_buf), log_to_write, &log_bytes, NULL);
#endif

		if (!WriteFile(m_hcom, (LPCVOID)LPCSTR(write_buf), num_to_write, &total_bytes, NULL))
		{
			SetError(ERROR_WRITE);
		}
		else
		{
			success = TRUE;
		}
	}
	else
	{
		SetError(ERROR_NOCOMM);
	}

	return success;
}

void CXP3KDev::Flush()
{

#ifdef XP3K_LOG
	DWORD log_to_write = 0;
	DWORD log_bytes = 0;
	m_logbuf[1] = '\0';

	CString write_buf;
	write_buf = "Flushing: ";
	log_to_write = write_buf.GetLength();
	WriteFile(m_hlog, (LPCVOID)LPCSTR(write_buf), log_to_write, &log_bytes, NULL);
#endif

	COMMTIMEOUTS CommTimeouts;
	DWORD old_to;
	if (GetCommTimeouts(m_hcom,  &CommTimeouts))
	{
		old_to = CommTimeouts.ReadTotalTimeoutConstant;
		CommTimeouts.ReadIntervalTimeout = 0;
		CommTimeouts.ReadTotalTimeoutMultiplier = 0;
		CommTimeouts.ReadTotalTimeoutConstant = POLL_TIME;
		CommTimeouts.WriteTotalTimeoutMultiplier = 0;
		CommTimeouts.WriteTotalTimeoutConstant = 0;
		
		SetCommTimeouts(m_hcom, &CommTimeouts);


		DWORD total_bytes = 0;
		int idx = 0;
		bool done = false;
		BYTE readch;
		while(!done)
		{
			if(!ReadFile(m_hcom, &readch, 1, &total_bytes, NULL))
			{
				//SetError(ERROR_READ);
				//break;bResult = ReadFile(hFile, &inBuffer, nBytesToRead, &nBytesRead, NULL)
				done = true;
			}
			else 
			{
				if (total_bytes < 1)
				{
					//SetError(ERROR_TIMEDOUT);
					done = true;
	#ifdef XP3K_LOG
					m_logbuf[0] = '\n';
					WriteFile(m_hlog, (LPCVOID)m_logbuf, 1, &log_bytes, NULL);
	#endif
					break;
				}
				else
				{
					// do nothing
	#ifdef XP3K_LOG
				write_buf.Format("%X", readch);
				log_to_write = write_buf.GetLength();
				WriteFile(m_hlog, (LPCVOID)LPCSTR(write_buf), log_to_write, &log_bytes, NULL);
	#endif

				}
			}
		}
		CommTimeouts.ReadIntervalTimeout = 0;
		CommTimeouts.ReadTotalTimeoutMultiplier = 0;
		CommTimeouts.ReadTotalTimeoutConstant = old_to;
		CommTimeouts.WriteTotalTimeoutMultiplier = 0;
		CommTimeouts.WriteTotalTimeoutConstant = 0;
		
		SetCommTimeouts(m_hcom, &CommTimeouts);
	}
}


BOOL CXP3KDev::SendDrawCmd(BYTE dev_num, long amount)
{
	long vol = (dev_num == 1) ? m_volume1 : m_volume2;
	if (vol == 0)
		vol = 1;
	int num_steps = (PLUNGER_RESOLUTION * amount) / vol;
	// Set Valve for input and draw relative to current position
	CString cmd;

	if ((amount >= 0) && (amount <= vol))
	{
		// if there is plunger movement, combine valve and plunger commands
		if (num_steps > 0)
			cmd.Format("%d%c%c%d%c", dev_num, CMD_INPUT_VALVE, CMD_DRAW_REL, num_steps, CMD_RUN_CMD);
		else	// otherwise, just move the valve
			cmd.Format("%d%c%c", dev_num, CMD_INPUT_VALVE, CMD_RUN_CMD);
	}

	return (WriteCmd(cmd));
}


BOOL CXP3KDev::SendInjectCmd(BYTE dev_num, long amount)
{
	long vol = (dev_num == 1) ? m_volume1 : m_volume2;
	if (vol == 0)
		vol = 1;
	int num_steps = (PLUNGER_RESOLUTION * amount) / vol;
	// Set Valve for input and draw relative to current position
	CString cmd;
	if ((amount >= 0) && (amount <= vol))
	{

		// if there is plunger movement, combine valve and plunger commands
		if (num_steps > 0)
			cmd.Format("%d%c%c%d%c", dev_num, CMD_OUTPUT_VALVE, CMD_INJECT_REL, num_steps, CMD_RUN_CMD);
		else	// otherwise, just move the valve
			cmd.Format("%d%c%c", dev_num, CMD_OUTPUT_VALVE, CMD_RUN_CMD);
	}

	return (WriteCmd(cmd));

}



