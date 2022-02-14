// Options.cpp: implementation of the COptions class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Options.h"
#include "General.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptions::COptions() : m_lumibaud(9600), m_lumiport(1), m_beep(true),
	m_injector(false), m_injectport(2), m_volume(500), m_version("1.1a")
{
	Read();
}

COptions::~COptions()
{

}

void COptions::Write()
{
	LPCTSTR app = "STLS";
	LPCTSTR opts = "Options";

	SCWriteAppProfileInt(app, opts, "LumiBaud", m_lumibaud);
	SCWriteAppProfileInt(app, opts, "LumiPort", m_lumiport);
	SCWriteAppProfileInt(app, opts, "Beep", m_beep ? 1 : 0);
	SCWriteAppProfileInt(app, opts, "Injector", m_injector ? 1 : 0);
	SCWriteAppProfileInt(app, opts, "InjectPort", m_injectport);
	SCWriteAppProfileInt(app, opts, "Volume", m_volume);
	SCWriteAppProfileString(app, opts, "MainDir", m_maindir);
	SCWriteAppProfileString(app, opts, "WorkDir", m_workdir);
	SCWriteAppProfileString(app, opts, "Version", m_version);
}

void COptions::Read()
{
	LPCTSTR app = "STLS";
	LPCTSTR opts = "Options";

	m_lumibaud = SCGetAppProfileInt(app, opts, "LumiBaud", m_lumibaud);
	m_lumiport = SCGetAppProfileInt(app, opts, "LumiPort", m_lumiport);
	m_beep = (SCGetAppProfileInt(app, opts, "Beep", m_beep) == 0) ? false : true;
	m_injector = (SCGetAppProfileInt(app, opts, "Injector", m_injector) == 0) ? false : true;
	m_injectport = SCGetAppProfileInt(app, opts, "InjectPort", m_injectport);
	m_volume = SCGetAppProfileInt(app, opts, "Volume", m_volume);
	m_maindir = SCGetAppProfileString(app, opts, "MainDir", m_maindir);
	m_workdir = SCGetAppProfileString(app, opts, "WorkDir", m_workdir);
	m_version = SCGetAppProfileString(app, opts, "Version", m_version);
}
