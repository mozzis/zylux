// FB12Device.cpp: implementation of the FB12Device class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <mmsystem.h>
#include "FB12Device.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef FB12_DEBUG
char FB12Device::m_cr = 0x0d;
char *FB12Device::state_names[FB12Device::STATE_MAX] =
{
		"STATE_START",
		"STATE_RX_BANG",

		// RLU value
		"STATE_RX_E",
		"STATE_RX_Esp",
		"STATE_RX_EspRn",
		"STATE_RX_EspR8",
		"STATE_RX_EspR8sp",
		"STATE_RX_EspR8spc1",

		// Door closed
		"STATE_RX_C",
		"STATE_RX_Csp",
		"STATE_RX_Csp8",

		// Door open
		"STATE_RX_O",
		"STATE_RX_Osp",
		"STATE_RX_Osp9",
};
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FB12Device::FB12Device(UINT msg, bool inhibit) : m_msg(msg),
m_operating(VARIANT_FALSE), m_inhibit(inhibit ? 1 : 0),
	m_port(1), m_baud(9600), m_dooropen(VARIANT_FALSE), m_RLU(0),
	m_error(ERROR_NONE), m_communicating(VARIANT_FALSE)
{
	// Get the main thread id
	m_mainthreadid = GetCurrentThreadId();

#ifdef FB12_SIMULATE
	// Create the timer to generate fake RLUs
	m_timerid = timeSetEvent(200, 100, SerialTimer, (DWORD)this, TIME_PERIODIC);
	//m_timerid = timeSetEvent(20, 10, SerialTimer, (DWORD)this, TIME_PERIODIC);
#else
	// Init that thread is not active
	m_threadactive = false;

	// Create the async IO listening event
	m_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
#endif
}

FB12Device::~FB12Device()
{
	// Make sure the serial IO and thread is stopped
	Stop();

#ifdef FB12_SIMULATE
	// Revoke timer
	if (m_timerid != 0)
	{
		timeKillEvent(m_timerid);
		m_timerid = 0;
	}
#else
	// Clean up the event
	CloseHandle(m_overlapped.hEvent);
#endif
}

VARIANT_BOOL FB12Device::Start(short port, long baud)
{
#ifdef FB12_TIMELIMIT
	// Test for time limit
	SYSTEMTIME now;
	GetLocalTime(&now);
	if ((now.wYear >= 1998)
		&& (now.wMonth >= 1)
		&& (now.wDay >= 1))
	{
		char oot_str[] = "This is an evaluation copy which has expired.\n\nPlease contact Softstep Corporation to purchase this software.\n\n7801 N. Lamar, Suite A-139\nAustin, TX  78752\nwww.softstep.com\n512-323-2760";
		::MessageBox(NULL, oot_str, "FB12",
			MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_TASKMODAL);
		SetError(ERROR_INIT);
		return VARIANT_FALSE;
	}
#endif

	VARIANT_BOOL success = VARIANT_FALSE;

	// Only allow client to start if we are 1) not
	// already operating, 2) the port is valid, and
	// 3) the baud is valid
	if (!m_operating && ((port == 1) || (port == 2)) &&
		((baud == 2400) || (baud == 4800) || (baud == 9600)))
	{
#ifdef FB12_SIMULATE
		SetOperating(VARIANT_TRUE);
		SetCommunicating(VARIANT_TRUE);
		// Indicate success
		success = VARIANT_TRUE;
		SetError(ERROR_NONE);
#else
		// Open the COM port
		char com_str[5];
		//strcpy(com_str, (port == 1) ? "COM1" : "COM2");
		sprintf(com_str, "COM%d", port);
		m_hcom = CreateFile(com_str, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		// Check to see if the COM port opened successfully
		if (m_hcom != INVALID_HANDLE_VALUE)
		{
			// We are now "operating"
			SetOperating(VARIANT_TRUE);

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
					// Init the state machine
					m_state = STATE_START;

					// Create the serial thread
					m_hthread = CreateThread(NULL, 0, SerialThread, this, 0, &m_threadid);
					m_threadactive = (m_hthread == INVALID_HANDLE_VALUE) ? false : true;
					if (m_threadactive)
					{
#ifdef FB12_DEBUG
						m_hdebug = CreateFile("debug.txt", GENERIC_WRITE, FILE_SHARE_READ, 
							NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
						DWORD num;
						WriteFile(m_hdebug, state_names[m_state], strlen(state_names[m_state]), &num, NULL);
						WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
						// Set port and baud properties
						m_port = port;
						m_baud = baud;

						// Indicate success
						success = VARIANT_TRUE;
						SetError(ERROR_NONE);
					}
					else
					{
						// Unable to create thread
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
			SetError(ERROR_INIT);
		}
#endif // FB12_SIMULATE
	}
	else
	{
		SetError(ERROR_INIT);
	}

	return success;
}

void FB12Device::Stop(void)
{
	if (m_operating)
	{
#ifdef FB12_DEBUG
		CloseHandle(m_hdebug);
#endif

#ifndef FB12_SIMULATE
		if (m_threadactive)
		{
			// Stop the serial thread
			PostThreadMessage(m_threadid, WM_QUIT, 0, 0);

			// Wait for thread to exit (max 5 seconds)
			WaitForSingleObject(m_hthread, 5000);

			// Close the handle to the thread
			CloseHandle(m_hthread);

			// Indicate inactivity
			m_threadactive = false;
		}

		// Cancel any pending IO
		//CancelIo(m_hcom);		// No CancelIo() in Windows 95

		// Close down the COM port file handle
		CloseHandle(m_hcom);
#endif

		// Let clients know we're stopped
		SetOperating(VARIANT_FALSE);
		SetCommunicating(VARIANT_FALSE);
	}
}

#ifndef FB12_SIMULATE
void FB12Device::HandleByte(BYTE byte)
{
#ifdef FB12_DEBUG
	char hex_str[17] = "0123456789ABCDEF";
	DWORD num;
	WriteFile(m_hdebug, "0x", 2, &num, NULL);
	WriteFile(m_hdebug, &hex_str[(byte >> 4) & 0x0f], 1, &num, NULL);
	WriteFile(m_hdebug, &hex_str[byte & 0x0f], 1, &num, NULL);
	if ((byte >= 0x20) && (byte <= 0x7e))
	{
		WriteFile(m_hdebug, "  ", 2, &num, NULL);
		WriteFile(m_hdebug, &byte, 1, &num, NULL);
	}
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	switch (m_state)
	{
	case STATE_START:
		if (byte == '!')
		{
			m_checksum = byte;
			m_state = STATE_RX_BANG;
		}
		break;

	case STATE_RX_BANG:
		m_checksum += byte;
		switch (byte)
		{
		case 'E':
			m_state = STATE_RX_E;
			break;

		case 'C':
			m_state = STATE_RX_C;
			break;

		case 'O':
			m_state = STATE_RX_O;
			break;

		default:
			m_state = STATE_START;
		}
		break;

	// RLU
	case STATE_RX_E:
		if (byte == ' ')
		{
			m_checksum += byte;
			m_state = STATE_RX_Esp;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_Esp:
		if (byte == ' ')
		{
			// We've received the first byte of the new RLU
			m_checksum += byte;
			m_digitcount = 1;
			m_newRLU = 0;
			m_state = STATE_RX_EspRn;
		}
		else if ((byte >= '0') && (byte <= '9'))
		{
			// We've received the first byte of the new RLU
			m_checksum += byte;
			m_digitcount = 1;
			m_newRLU = byte - '0';
			m_state = STATE_RX_EspRn;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_EspRn:
		if (byte == ' ')
		{
			// We've received another byte of the new RLU
			m_checksum += byte;
			m_digitcount++;
			m_newRLU = m_newRLU * 10;
			if (m_digitcount == 8)
			{
				m_state = STATE_RX_EspR8;
			}
		}
		else if ((byte >= '0') && (byte <= '9'))
		{
			// We've received another byte of the new RLU
			m_checksum += byte;
			m_digitcount++;
			m_newRLU = (m_newRLU * 10) + (byte - '0');
			if (m_digitcount == 8)
			{
				m_state = STATE_RX_EspR8;
			}
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_EspR8:
		if (byte == ' ')
		{
			m_checksum += byte;
			m_checksum = m_checksum % 256;
			m_state = STATE_RX_EspR8sp;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_EspR8sp:
		if ((byte >= '0') && (byte <= '9'))
		{
			m_checksumrx = (byte - '0') << 4;
			m_state = STATE_RX_EspR8spc1;
		}
		else if ((byte >= 'A') && (byte <= 'F'))
		{
			m_checksumrx = (byte - 'A' + 10) << 4;
			m_state = STATE_RX_EspR8spc1;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_EspR8spc1:
		if ((byte >= '0') && (byte <= '9'))
		{
			m_checksumrx += byte - '0';
			if (m_checksum == m_checksumrx)
			{
				// New RLU is valid
				SetRLU(m_newRLU);
			}
			else
			{
				// Checksum error
				SetError(ERROR_CHECKSUM);
			}
			m_state = STATE_START;
		}
		else if ((byte >= 'A') && (byte <= 'F'))
		{
			m_checksumrx += byte - 'A' + 10;
			if (m_checksum == m_checksumrx)
			{
				// New RLU is valid
				SetRLU(m_newRLU);
			}
			else
			{
				// Checksum error
				SetError(ERROR_CHECKSUM);
			}
		}
		m_state = STATE_START;
		break;

	// Door closed
	case STATE_RX_C:
		if (byte == ' ')
		{
			m_checksum += byte;
			m_checksum = m_checksum % 256;
			m_state = STATE_RX_Csp;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_Csp:
		if (byte == '8')
		{
			m_state = STATE_RX_Csp8;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_Csp8:
		if (byte == '4')
		{
			if (m_checksum == 0x84)
			{
				SetDoorOpen(VARIANT_FALSE);
			}
			else
			{
				// Checksum error
				SetError(ERROR_CHECKSUM);
			}
		}
		m_state = STATE_START;
		break;

	// Door open
	case STATE_RX_O:
		if (byte == ' ')
		{
			m_checksum += byte;
			m_checksum = m_checksum % 256;
			m_state = STATE_RX_Osp;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_Osp:
		if (byte == '9')
		{
			m_state = STATE_RX_Osp9;
		}
		else
		{
			m_state = STATE_START;
		}
		break;

	case STATE_RX_Osp9:
		if (byte == '0')
		{
			if (m_checksum == 0x90)
			{
				SetDoorOpen(VARIANT_TRUE);
			}
			else
			{
				// Checksum error
				SetError(ERROR_CHECKSUM);
			}
		}
		m_state = STATE_START;
		break;
	}
#ifdef FB12_DEBUG
	WriteFile(m_hdebug, state_names[m_state], strlen(state_names[m_state]), &num, NULL);
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
}
#endif

VARIANT_BOOL FB12Device::get_operating(void) const
{
	return m_operating;
}

VARIANT_BOOL FB12Device::get_communicating(void) const
{
	return m_communicating;
}

long FB12Device::get_error(void) const
{
	return m_error;
}

long FB12Device::get_baud(void) const
{
	return m_baud;
}

short FB12Device::get_port(void) const
{
	return m_port;
}

VARIANT_BOOL FB12Device::get_dooropen(void) const
{
	return m_dooropen;
}

long FB12Device::get_RLU(void) const
{
	return m_RLU;
}

void FB12Device::SetDoorOpen(VARIANT_BOOL new_dooropen)
{
#ifdef FB12_DEBUG
	DWORD num;
	if (new_dooropen)
	{
		WriteFile(m_hdebug, "<<Door Open>>", 13, &num, NULL);
	}
	else
	{
		WriteFile(m_hdebug, "<<Door Closed>>", 15, &num, NULL);
	}
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	// Always notify on this property
	m_dooropen = new_dooropen;
	if (m_inhibit == 0)
	{
		PostThreadMessage(m_mainthreadid, m_msg, FB12_MSG_DOORCHANGE, m_dooropen);
	}
	// We received something from luminometer, so we are communicating
	SetCommunicating(VARIANT_TRUE);
}

void FB12Device::SetRLU(long new_RLU)
{
#ifdef FB12_DEBUG
	char rlu_str[24] = "<<New RLU ";
	char num_str[11];
	int i = 0;
	long rlu = new_RLU;
	while (rlu > 0)
	{
		num_str[i] = "0123456789"[rlu % 10];
		rlu = rlu / 10;
		i++;
	}
	num_str[i] = 0;
	int j = strlen(rlu_str);
	while (i > 0)
	{
		i--;
		rlu_str[j] = num_str[i];
		j++;
	}
	rlu_str[j] = '>';
	j++;
	rlu_str[j] = '>';
	j++;
	rlu_str[j] = 0;

	DWORD num;
	WriteFile(m_hdebug, rlu_str, strlen(rlu_str), &num, NULL);
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	// Always notify on this property
	m_RLU = new_RLU;
	if (m_inhibit == 0)
	{
		PostThreadMessage(m_mainthreadid, m_msg, FB12_MSG_NEWRLU, m_RLU);
	}
	// We received something from luminometer, so we are communicating
	SetCommunicating(VARIANT_TRUE);
}

void FB12Device::SetOperating(VARIANT_BOOL new_operating)
{
#ifdef FB12_DEBUG
	DWORD num;
	if (new_dooropen)
	{
		WriteFile(m_hdebug, "<<Is Operating>>", 16, &num, NULL);
	}
	else
	{
		WriteFile(m_hdebug, "<<Is Not Operating>>", 20, &num, NULL);
	}
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	if (new_operating != m_operating)
	{
		// Only notify if there is a change in this property
		m_operating = new_operating;
		if (m_inhibit == 0)
		{
			PostThreadMessage(m_mainthreadid, m_msg, FB12_MSG_OPERATINGCHANGE, m_operating);
		}
	}
}

void FB12Device::SetCommunicating(VARIANT_BOOL communicating)
{
#ifdef FB12_DEBUG
	DWORD num;
	if (communicating)
	{
		WriteFile(m_hdebug, "<<Is Communicating>>", 20, &num, NULL);
	}
	else
	{
		WriteFile(m_hdebug, "<<Is Not Communicating>>", 24, &num, NULL);
	}
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	if (communicating != m_communicating)
	{
		// Only notify if there is a change in this property
		m_communicating = communicating;
		if (m_inhibit == 0)
		{
			PostThreadMessage(m_mainthreadid, m_msg, FB12_MSG_COMMUNICATINGCHANGE, m_communicating);
		}
	}
}

void FB12Device::SetError(long new_error)
{
#ifdef FB12_DEBUG
	char err_str[32] = "<<New error ";
	char num_str[11];
	int i = 0;
	long error = new_error;
	while (error > 0)
	{
		num_str[i] = "0123456789"[error % 10];
		error = error / 10;
		i++;
	}
	num_str[i] = 0;
	int j = strlen(err_str);
	while (i > 0)
	{
		i--;
		err_str[j] = num_str[i];
		j++;
	}
	err_str[j] = '>';
	j++;
	err_str[j] = '>';
	j++;
	err_str[j] = 0;

	DWORD num;
	WriteFile(m_hdebug, err_str, strlen(err_str), &num, NULL);
	WriteFile(m_hdebug, &m_cr, 1, &num, NULL);
#endif
	// Always notify on this property
	m_error = new_error;
	if (m_inhibit == 0)
	{
		PostThreadMessage(m_mainthreadid, m_msg, FB12_MSG_ERRORCHANGE, m_error);
	}
}

#ifdef FB12_SIMULATE
void CALLBACK FB12Device::SerialTimer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	((FB12Device *)dwUser)->InstanceTimer();
}

void FB12Device::InstanceTimer(void)
{
	if (m_operating && m_communicating)
	{
		SetRLU(rand() % 1000);
	}
}

#else

DWORD WINAPI FB12Device::SerialThread(void * parameter)
{
	return ((FB12Device *)parameter)->InstanceThread();
}

DWORD FB12Device::InstanceThread(void)
{
	bool pending = false;

	// Start the first read operation
	m_overlapped.Internal = 0;
	m_overlapped.InternalHigh = 0;
	m_overlapped.Offset = 0;
	m_overlapped.OffsetHigh = 0;

	bool exit = false;
	MSG msg;
	while (!exit)
	{
		// Handle any messages
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, 0, 0, 0))
			{
				exit = true;
			}
			DispatchMessage(&msg);
		}

		// Handle starting a read operation if needed
		if (!pending)
		{
			// Reset error
			SetError(ERROR_NONE);

			// Start the read operation of 1 byte
			if (ReadFile(m_hcom, &m_readch, 1, &m_bytesread, &m_overlapped))
			{
				// Read completed before ReadFile() returned;
				// The event loop will process the result
				pending = true;
			}
			else
			{
				// There was an error in reading
				DWORD error = GetLastError();
				if (error == ERROR_IO_PENDING)
				{
					// Oh, it was just an error that the read
					// hasn't completed
					pending = true;
				}
				else
				{
					// Some other serial error
					SetError(ERROR_SERIAL);
				}
			}
		}

		// Handle checking on read operation if needed
		if (pending)
		{
			// Wait at max 5000ms (5s) for the next char to be received
			if (WaitForSingleObject(m_overlapped.hEvent, 5000) == WAIT_TIMEOUT)
			{
				// Timeout occurred
				SetCommunicating(VARIANT_FALSE);
			}
			else
			{
				if (GetOverlappedResult(m_hcom, &m_overlapped, &m_bytesread, FALSE))
				{
					pending = false;
					if (m_bytesread == 1)
					{
						HandleByte(m_readch);
					}
					else
					{
						// Oops, number of bytes read was not 1!
						pending = false;
						SetError(ERROR_SERIAL);
					}
				}
				else
				{
					DWORD error = GetLastError();
					if (error != ERROR_IO_INCOMPLETE)
					{
						// a real error
						pending = false;
						SetError(ERROR_SERIAL);
					}
				}
			}
		}
	}

	return 0;
}
#endif

void FB12Device::InhibitMsg()
{
	m_inhibit++;
}

void FB12Device::UninhibitMsg()
{
	m_inhibit--;
}

bool FB12Device::IsInhibitMsg() const
{
	return (m_inhibit == 0) ? false : true;
}
