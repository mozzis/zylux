// SKOptions.cpp: implementation of the CSKOptions class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SKOptions.h"
#include "General.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSKOptions::CSKOptions() : m_num_injectors(0), m_injectport(2), m_volume(500),
	m_speed(11), m_volume2(500), m_speed2(11), m_showwarning(1)
{
	Read();
}

CSKOptions::~CSKOptions()
{

}

void CSKOptions::Write()
{
	LPCTSTR app = "STLS\\Single Kinetics Injector";
	LPCTSTR opts = "Options";

	SCWriteAppProfileInt(app, opts, "NumInjectors", m_num_injectors);
	SCWriteAppProfileInt(app, opts, "InjectPort", m_injectport);
	SCWriteAppProfileInt(app, opts, "Volume", m_volume);
	SCWriteAppProfileInt(app, opts, "Speed", m_speed);
	SCWriteAppProfileInt(app, opts, "Volume2", m_volume2);
	SCWriteAppProfileInt(app, opts, "Speed2", m_speed2);
	SCWriteAppProfileInt(app, opts, "Warning", m_showwarning);

}

void CSKOptions::Read()
{
	LPCTSTR app = "STLS\\Single Kinetics Injector";
	LPCTSTR opts = "Options";

	m_num_injectors = SCGetAppProfileInt(app, opts, "NumInjectors", m_num_injectors);
	m_injectport = SCGetAppProfileInt(app, opts, "InjectPort", m_injectport);
	m_volume = SCGetAppProfileInt(app, opts, "Volume", m_volume);
	m_speed = SCGetAppProfileInt(app, opts, "Speed", m_speed);
	m_volume2 = SCGetAppProfileInt(app, opts, "Volume2", m_volume2);
	m_speed2 = SCGetAppProfileInt(app, opts, "Speed2", m_speed2);
	m_showwarning = SCGetAppProfileInt(app, opts, "Warning", m_showwarning);
}
