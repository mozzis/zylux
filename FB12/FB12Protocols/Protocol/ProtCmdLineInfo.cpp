// ProtCmdLineInfo.cpp: implementation of the CProtCmdLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protocol.h"
#include "ProtCmdLineInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtCmdLineInfo::CProtCmdLineInfo() : m_mode(CProtocolApp::APPMODE_NONE)
	//m_port(1), m_baud(9600)
{
}

void CProtCmdLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
	bool parsed = false;

	if (lpszParam && bFlag)
	{
		if (strlen(lpszParam) == 1)
		{
			switch (*lpszParam)
			{
			case 'e':
				parsed = true;
				m_mode = CProtocolApp::APPMODE_EDIT;
				break;

			case 'r':
				parsed = true;
				m_mode = CProtocolApp::APPMODE_RUN;
				break;

			case 'v':
				parsed = true;
				m_mode = CProtocolApp::APPMODE_VIEW;
				break;

			case 'g':
				parsed = true;
				m_mode = CProtocolApp::APPMODE_GEN;
				break;
			}
		}
/*
		else if (strlen(lpszParam) > 1)
		{
			switch (*lpszParam)
			{
			case 'p':
				// Snag the COM port
				parsed = true;
				m_port = atoi(&lpszParam[1]);
				break;

			case 'b':
				// Snag the baud
				parsed = true;
				m_baud = atol(&lpszParam[1]);
				break;

			case 'f':
				// Snag the beep flag
				parsed = true;
				m_beep = (atol(&lpszParam[1]) == 1) ? true : false;
				break;

			case 'w':
				// Snag the work directory
				parsed = true;
				m_workdir = &lpszParam[1];
				break;
			}
		}
*/
	}

	if (!parsed)
	{
		CCommandLineInfo::ParseParam(lpszParam, bFlag, bLast);
	}
}
