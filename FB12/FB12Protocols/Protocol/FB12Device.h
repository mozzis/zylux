// FB12Device.h: interface for the FB12Device class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FB12DEVICE_H__5065AA21_E734_11D0_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_FB12DEVICE_H__5065AA21_E734_11D0_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wtypes.h>

//#define FB12_DEBUG
//#define FB12_SIMULATE
//#define FB12_TIMELIMIT

class FB12Device  
{
public:
	bool IsInhibitMsg() const;
	void InhibitMsg();
	void UninhibitMsg();
	// wParam
	enum
	{
		FB12_MSG_DOORCHANGE,			// lParam is VARIANT_BOOL is_open
		FB12_MSG_NEWRLU,				// lParam is long new_RLU
		FB12_MSG_ERRORCHANGE,			// lParam is long new_error
		FB12_MSG_OPERATINGCHANGE,		// lParam is VARIANT_BOOL is_operating
		FB12_MSG_COMMUNICATINGCHANGE,	// lParam is VARIANT_BOOL is_communicating
	};
	void SetOperating(VARIANT_BOOL new_operating);
	void SetCommunicating(VARIANT_BOOL communicating);
	void SetRLU(long new_RLU);
	void SetDoorOpen(VARIANT_BOOL new_dooropen);
	void SetError(long new_error);
	long get_RLU(void) const;
	VARIANT_BOOL get_dooropen(void) const;
	short get_port(void) const;
	long get_baud(void) const;
	VARIANT_BOOL get_operating(void) const;
	VARIANT_BOOL get_communicating(void) const;
	long get_error(void) const;
	void Stop(void);
	VARIANT_BOOL Start(short port, long baud);
	FB12Device(UINT msg, bool inhibit);
	virtual ~FB12Device();

protected:
	//long m_timercount;
#ifdef FB12_SIMULATE
	UINT m_timerid;
	void InstanceTimer(void);
	static void CALLBACK SerialTimer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
#else
	DWORD InstanceThread(void);
	static DWORD WINAPI SerialThread(LPVOID parameter);
	void HandleByte(BYTE byte);

	bool m_threadactive;
	HANDLE m_hthread;
	DWORD m_threadid;

	// m_state states
	enum
	{
		STATE_START,
		STATE_RX_BANG,

		// RLU value
		STATE_RX_E,
		STATE_RX_Esp,
		STATE_RX_EspRn,
		STATE_RX_EspR8,
		STATE_RX_EspR8sp,
		STATE_RX_EspR8spc1,

		// Door closed
		STATE_RX_C,
		STATE_RX_Csp,
		STATE_RX_Csp8,

		// Door open
		STATE_RX_O,
		STATE_RX_Osp,
		STATE_RX_Osp9,

		STATE_MAX
	};

	long m_newRLU;
	int m_state;
	int m_checksumrx;
	int m_checksum;
	int m_digitcount;
	DWORD m_bytesread;
	BYTE m_readch;
	OVERLAPPED m_overlapped;
	HANDLE m_hcom;
#endif

	UINT m_msg;
	DWORD m_mainthreadid;
	long m_inhibit;

	long m_RLU;
	short m_port;
	long m_baud;
	long m_error;
	VARIANT_BOOL m_operating;
	VARIANT_BOOL m_dooropen;
	VARIANT_BOOL m_communicating;

	enum
	{
		ERROR_NONE,
		ERROR_INIT,
		ERROR_SERIAL,
		ERROR_CHECKSUM,
		
		ERROR_MAX
	};
#ifdef FB12_DEBUG
	HANDLE m_hdebug;
	static char m_cr;
	static char *state_names[STATE_MAX];
#endif
};

#endif // !defined(AFX_FB12DEVICE_H__5065AA21_E734_11D0_AE1E_0080C80C9F0E__INCLUDED_)
