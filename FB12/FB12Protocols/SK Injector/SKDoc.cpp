// SKDoc.cpp : implementation of the CSKDoc class
//

#include "stdafx.h"
#include "SK.h"
#include "MainFrm.h"
#include "General.h"
#include "SKHint.h"
#include <mmsystem.h>
#include "SKView.h"

#include "SKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static LPCTSTR restart_msg = "\nPlease exit this protocol and re-start it from the Protocol Manager.";
/////////////////////////////////////////////////////////////////////////////
// CSKDoc

IMPLEMENT_DYNCREATE(CSKDoc, CProtocolDoc)

BEGIN_MESSAGE_MAP(CSKDoc, CProtocolDoc)
	//{{AFX_MSG_MAP(CSKDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_TEXT, OnUpdateFileSaveAsText)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_MEASURE_START, OnMeasureStart)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_START, OnUpdateMeasureStart)
	ON_COMMAND(ID_MEASURE_STOP, OnMeasureStop)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_STOP, OnUpdateMeasureStop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DOWN, OnUpdateButtonDown)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_UP, OnUpdateButtonUp)
	ON_COMMAND(ID_MEASURE_KINETICS, OnMeasureKinetics)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_KINETICS, OnUpdateMeasureKinetics)
	ON_COMMAND(ID_MEASURE_GRID, OnMeasureGrid)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_GRID, OnUpdateMeasureGrid)
	ON_COMMAND(ID_BUTTON_LEFT, OnButtonLeft)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_LEFT, OnUpdateButtonLeft)
	ON_COMMAND(ID_BUTTON_RIGHT, OnButtonRight)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RIGHT, OnUpdateButtonRight)
	ON_COMMAND(ID_BUTTON_UP, OnButtonUp)
	ON_COMMAND(ID_BUTTON_INIT, OnButtonInit)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_INIT, OnUpdateButtonInit)
	ON_COMMAND(ID_BUTTON_DOWN, OnButtonDown)
	ON_COMMAND(ID_BUTTON_INJECTOR1, OnButtonInjector1)
	ON_COMMAND(ID_BUTTON_INJECTOR2, OnButtonInjector2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_INJECTOR1, OnUpdateButtonInjector1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_INJECTOR2, OnUpdateButtonInjector2)
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateMode)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKDoc construction/destruction


CSKDoc::CSKDoc() : m_injector_control(this, SKGetApp()->m_skoptions.m_injectport, SKGetApp()->m_skoptions.m_volume),
	m_meascount(0), m_delaycount(0), m_pps(SKGetApp()->m_pps), m_timer_id(0), m_injectpos1(0),
	m_injectpos2(0), m_injectdirection1(1), m_injectstate1(ISTATE_NIL), m_injectstate2(ISTATE_NIL),
	m_currentamount1(0), m_currentamount2(0), m_nextinjection(-1), m_injectdirection2(1),
	m_kinetics(SKGetApp()->m_pps.m_meastime / 2), m_inject_num(1)
{
	// TODO: add one-time construction code here
	// Get the current date and time
	time_t sys_time;
	time(&sys_time);
	CTime now(sys_time);
	m_datetime = now;

	// Graph view inits
	m_graph_cy = 50;
	m_graph_scroll_pt = CPoint(0, 0);
	m_graph_showaverage = true;
	m_graph_smoothing = false;
	m_graph_manual = false;
	m_graph_log = false;
	m_graph_RLU_min = 0;
	m_graph_RLU_max = 1000;
	// m_graph_replicates is in DeleteContents()

	// Connect to the injector
	if ((SKGetApp()->m_mode == CSKApp::APPMODE_RUN) &&
		  (SKGetApp()->m_skoptions.m_num_injectors > 0))
	{
		m_injector_control.Start();
	
		// Init the total amount to be injected for this protocol
		m_totalamount1 = SKGetApp()->m_pps.GetTotalInjectVolume(1);
		if (SKGetApp()->m_skoptions.m_num_injectors == 2)
			m_totalamount2 = SKGetApp()->m_pps.GetTotalInjectVolume(2);
		else
			m_totalamount2 = 0;

		m_anyinjections = ((m_totalamount2 == 0) && (m_totalamount1 == 0)) ? false : true;
	}
	else
	{
		m_anyinjections = false;
	}

	// Load some stuff from the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	m_graph_cy = SCGetAppProfileInt(appname, "Settings", "GraphOptsSize", m_graph_cy);
	SCGetAppProfileBinary(appname, "Settings", "GraphOptsPos",
		(BYTE*)&m_graph_scroll_pt, sizeof(m_graph_scroll_pt));
/*
	HKEY key;
	CString key_str;
	key_str.Format("Software\\Softstep\\%s\\Settings", AfxGetApp()->m_pszAppName);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T(key_str),
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		DWORD type;
		DWORD size;
		int graph_cy;
		CPoint graph_scroll_pt;

		// Load the size of the graph opts view
		type = REG_BINARY;
		size = sizeof(graph_cy);
		if (RegQueryValueEx(key, _T("GraphOptsSize"), NULL, &type, (BYTE*)&graph_cy, &size)
			== ERROR_SUCCESS)
		{
			m_graph_cy = graph_cy;
		}

		// Load the pos of the graph opts view scroller
		type = REG_BINARY;
		size = sizeof(graph_scroll_pt);
		if (RegQueryValueEx(key, _T("GraphOptsPos"), NULL, &type, (BYTE*)&graph_scroll_pt, &size)
			== ERROR_SUCCESS)
		{
			m_graph_scroll_pt = graph_scroll_pt;
		}

		RegCloseKey(key);
	}
*/
}

CSKDoc::~CSKDoc()
{
	if (m_timer_id != 0)
	{
		timeKillEvent(m_timer_id);
		m_timer_id = 0;
	}

	// Save some stuff in the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	SCWriteAppProfileInt(appname, "Settings", "GraphOptsSize", m_graph_cy);
	SCWriteAppProfileBinary(appname, "Settings", "GraphOptsPos",
		(BYTE*)&m_graph_scroll_pt, sizeof(m_graph_scroll_pt));
/*
	HKEY key;
	CString key_str;
	key_str.Format("Software\\Softstep\\%s\\Settings", AfxGetApp()->m_pszAppName);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T(key_str),
		0, KEY_WRITE|KEY_READ, &key) == ERROR_SUCCESS)
	{
		// Save the size of the graph opts view
		RegSetValueEx(key, _T("GraphOptsSize"), NULL, REG_BINARY,
			(BYTE*)&m_graph_cy, sizeof(m_graph_cy));

		// Save the pos of the graph opts view scroller
		RegSetValueEx(key, _T("GraphOptsPos"), NULL, REG_BINARY,
			(BYTE*)&m_graph_scroll_pt, sizeof(m_graph_scroll_pt));

		RegCloseKey(key);
	}
*/
	m_injector_control.Stop();
}


/////////////////////////////////////////////////////////////////////////////
// CSKDoc serialization

void CSKDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSKDoc diagnostics

#ifdef _DEBUG
void CSKDoc::AssertValid() const
{
	CProtocolDoc::AssertValid();
}

void CSKDoc::Dump(CDumpContext& dc) const
{
	CProtocolDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSKDoc commands

void CSKDoc::FB12NewRLU(long new_RLU)
{
	//new_RLU /= 10;

	if (GetMode() == MODE_MEASURING)
	{
		// Check to see if we should inject
		if (m_anyinjections)
		{
			if ((m_pps.IsLumiTimeBase()) || (m_pps.m_meastime == m_pps.m_intervaltime))
			{
				CheckInjection(true);
			}
		}
		if (m_mode2 == MODE_SAMPLING)
		{
			if (m_delaycount == 0)
			{
				if (m_meascount > 0)
				{
					// Add this RLU event to the kinetics info
					bool door_open =
						(SKGetApp()->m_pFB12Device->get_dooropen() == VARIANT_TRUE) ? true : false;
					m_kinetics.Add(door_open ? 0 : new_RLU);
					m_meascount--;
					if (m_meascount == 0)
					{
						m_samples[m_sample_num].SetReplicate(m_replicate_num, m_kinetics.GetMean());
						SetModifiedFlag(TRUE);

						SampleEnd();
					}
				}
				// else ignore until the door is opened then closed again
			}
			else
			{
				m_delaycount--;
				if (m_delaycount == 0)
				{
					// Set the statusbar text
					SKGetApp()->m_pMainFrame->SetMessageText(IDS_MEASUREMESSAGE);
				}
			}
		}
		else
		{
			if (m_pps.IsLumiTimeBase())
			{
				m_intervalcount--;
				if (m_intervalcount == 0)
				{
					// Interval is over, start back up
					SampleStart();
				}
			}
		}
	}
}

void CSKDoc::FB12DoorChange(VARIANT_BOOL is_open)
{
	if (GetMode() == MODE_STOPPED)
	{
		// We're stopped
		if (!is_open)
		{
			if (!m_pps.UseStartButton())
			{
				// User wants us to start measuring 
				// Don't let them if there are injections, but the injector
				// has not been initialized
				if ((m_anyinjections) && 
					((SKGetApp()->m_skoptions.m_num_injectors == 1) && (m_injectstate1 == ISTATE_INITIALIZED)) ||
					((SKGetApp()->m_skoptions.m_num_injectors == 2) && (m_injectstate1 == ISTATE_INITIALIZED) &&
					 (m_injectstate2 == ISTATE_INITIALIZED)))
				{
					MeasureStart(true);	// start measuring with delay
				}
				else if (!m_anyinjections)
				{
					MeasureStart(true);	// start measuring with delay
				}
			}
			//else
			//{
			//	// This is okay, user will click start button soon
			//}
		}
		//else
		//{
		//	// This is okay, user just opened door to change a tube
		//}
	}
}

void CSKDoc::FB12OperatingChange(VARIANT_BOOL is_operating)
{

}

void CSKDoc::FB12ErrorChange(long new_error)
{
	if (GetMode() == MODE_MEASURING)
	{
		switch (new_error)
		{
		case 1:		// initialization error
			MeasureEnd();
			SCMessageBox(IDS_FB12_ERROR_INIT);
			break;

		case 2:		// general serial error
			MeasureEnd();
			SCMessageBox(IDS_FB12_ERROR_GENERAL);
			break;

		case 3:		// checksum error
			MeasureEnd();
			SCMessageBox(IDS_FB12_ERROR_CHECKSUM);
			break;
		}
	}
}

void CSKDoc::FB12CommunicatingChange(VARIANT_BOOL is_communicating)
{
	if (!is_communicating && (GetMode() == MODE_MEASURING))
	{
		MeasureEnd();
		SCMessageBox(IDS_FB12_TIMEOUT);
	}
}

void CSKDoc::SetMode(int mode)
{
	m_mode = mode;
}

int CSKDoc::GetMode() const
{
	return m_mode;
}

int CSKDoc::GetMode2() const
{
	return m_mode2;
}

void CSKDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	// since document is going away, inhibit FB12 from talking to it
	SKGetApp()->FB12Inhibit();

	// Call base class
	CProtocolDoc::OnCloseDocument();

	// We are quitting the program
	AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CSKDoc::SampleStart(bool delay)
{
	if (m_sample_num < m_numsamples)
	{
		// The delay and measurement counts are initialized
		m_delaycount = delay ? (m_pps.m_delaytime / (10 / SAMPLES_PER_SEC)) : 0;
		m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);

		if (!m_pps.IsLumiTimeBase())
		{
			// Set the time when we stop
			m_time_end += m_pps.m_intervaltime * 100;
			m_time_wait = true;
		}

		// Start a new set of kinetics
		m_kinetics.Reset();

		// Set the statusbar text
		CString status_str;
		if (m_delaycount == 0)
		{
			status_str.Format("Taking %s...",
				(LPCTSTR)GetReplicateString(m_sample_num, m_replicate_num));
		}
		else
		{
			status_str.LoadString(IDS_DELAYMESSAGE);
		}
		SKGetApp()->m_pMainFrame->SetMessageText(status_str);

		// Set the secondary mode
		m_mode2 = MODE_SAMPLING;
	}
}

void CSKDoc::SampleEnd()
{
	if (m_sample_num == (m_numsamples - 1))
	{
		// We're at the end of a run
		MeasureEnd();
	}
	else
	{
		// Determine if we wait for a while, or start right back up
		bool wait = true;
		if (((m_sample_num == 0) && m_pps.UseBackground()) ||
			(m_pps.m_meastime == m_pps.m_intervaltime))
		{
			wait = false;
		}

		// Increment to the next sample to be measured, then update the screen
		UINT current_sample = m_sample_num;
		UINT current_replicate = m_replicate_num;
		Increment();
		m_updatecount--;
		if (m_updatecount == 0)
		{
			m_updatecount = m_update_every_n_samples;
			CSKHint hint(m_next_update_sample, current_sample + 1, current_replicate);
			UpdateAllViews(NULL, 0, &hint);
			m_next_update_sample = current_sample + 1;
		}
		else
		{
			UpdateAllViews(NULL, -1);
		}

		if (wait)
		{
			// We're waiting for some amount of time
			m_mode2 = MODE_WAITINTERVAL;
			SKGetApp()->m_pMainFrame->SetMessageText("Waiting for interval time to expire...");
			if (m_pps.IsLumiTimeBase())
			{
				m_intervalcount = (m_pps.m_intervaltime - m_pps.m_meastime) /
					(10 / SAMPLES_PER_SEC);
			}
			//else
			//{
			//	//TIMECAPS caps;
			//	//timeGetDevCaps(&caps, sizeof(caps));
			//	DWORD ms = (m_pps.m_intervaltime - m_pps.m_meastime) * 100;
			//	m_timer_id = timeSetEvent(ms, 100, TimerCallback, (DWORD)this, TIME_ONESHOT);
			//	m_timems = timeGetTime() + ms;
			//	if (m_timer_id == 0)
			//	{
			//		MeasureEnd();
			//		SCMessageBox("Unable to create timer.");
			//	}
			//}
		}
		else
		{
			// Start right back up, without delay
			SampleStart();
		}
	}
}

void CSKDoc::MeasureStart(bool delay)
{
	if (m_replicate_num < m_pps.m_numreplicates)
	{
		// Init the sample number
		m_sample_num = 0;

		// Which sample are we going to start updating with
		// and how often will we update
		m_next_update_sample = 1;
		m_updatecount = m_update_every_n_samples;

		if (m_anyinjections)
		{
			// Make sure the total amount is correct.
			m_totalamount1 = m_pps.GetTotalInjectVolume(1);

			m_currentamount1 = (SKGetApp()->m_skoptions.m_volume * m_injectpos1) / CXP3KDev::PLUNGER_RESOLUTION;
			CheckVolume(1, m_totalamount1, m_currentamount1, m_injectdirection1, m_totalamount1);
			if (SKGetApp()->m_skoptions.m_num_injectors == 2)
			{
				m_totalamount2 = m_pps.GetTotalInjectVolume(2);
				m_currentamount2 = (SKGetApp()->m_skoptions.m_volume2 * m_injectpos2) / CXP3KDev::PLUNGER_RESOLUTION;
				CheckVolume(2, m_totalamount2, m_currentamount2, m_injectdirection2, m_totalamount2);
			}
			else
			{
				m_totalamount2 = 0;
			}

			UpdateAllViews(NULL);
		}

		// Start measuring the samples - count the RLUs for time
		if (m_pps.IsLumiTimeBase() || (m_pps.m_meastime == m_pps.m_intervaltime))
		{
			// Initialize Injection list
			if (InjectionStart(true))
			{
				// Change the mode
				SetMode(MODE_MEASURING);


				// Start first sample
				SampleStart(delay);
			}
		}
		else
		{
			// Start measuring the samples - use the timer
			m_time_wait = false;
			m_timer_id = timeSetEvent(50, 50, TimerCallback, (DWORD)this, TIME_PERIODIC);
			if (m_timer_id != 0)
			{
				// Get the starting milliseconds
				m_time_end = timeGetTime();
				if ((0xffffffff - m_time_end) < (m_pps.m_intervaltime * 100 * m_numsamples))
				{
					SCMessageBox("The system timer is too high.\nYou must restart your computer or use the\n\"Use luminomter as time base\" option to take a measurement.");
					timeKillEvent(m_timer_id);
				}
				else
				{
					if (InjectionStart(false, m_time_end))
					{

						// Change the mode
						SetMode(MODE_MEASURING);

						// Start first sample
						SampleStart(delay);
					}
					else
					{
						timeKillEvent(m_timer_id);
					}
				}
			}
			else
			{
				SCMessageBox(_T("Unable to allocate timer."));
			}
		}
	}
	else
	{
		SCMessageBox("There are no more replicates to measure.");
	}
}

void CSKDoc::MeasureEnd()
{
	// Do the final grid update
	UINT current_sample = m_sample_num;
	UINT current_replicate = m_replicate_num;
	m_replicate_num++;
	m_sample_num = 0;
	CSKHint hint(m_next_update_sample, current_sample + 1, current_replicate);
	UpdateAllViews(NULL, 0, &hint);
	UpdateAllViews(NULL, -(int)current_replicate - 2);

	if (ProtGetApp()->m_beep)
	{
		MessageBeep(MB_OK);
	}

	// Reset the counters
	if (m_timer_id != 0)
	{
		timeKillEvent(m_timer_id);
		m_timer_id = 0;
	}
	m_delaycount = 0;
	m_meascount = 0;

	// Set the statusbar text
	SetStatus();

	// Change the mode
	SetMode(MODE_STOPPED);

	// Save the log file
	LogDocument();

	if ((current_sample == (m_numsamples - 1)) &&
		(current_replicate == (m_pps.m_numreplicates - 1)) &&
		m_pps.AutoSendToExcel())
	{
		UpdateAllViews(NULL);
		((CSKView*)m_grid_view)->SendToExcel();
	}

	if (m_anyinjections)
	{
		// If this is not the last replicate to be measured, go ahead
		// and get the injector ready for the next replicate.
		if (current_replicate < (m_pps.m_numreplicates - 1))
		{
			m_totalamount1 = m_pps.GetTotalInjectVolume(1);
			CheckVolume(1, m_totalamount1, m_currentamount1, m_injectdirection1, m_totalamount1);

			if (SKGetApp()->m_skoptions.m_num_injectors == 2)
			{
				m_totalamount2 = m_pps.GetTotalInjectVolume(2);
				m_currentamount2 = (SKGetApp()->m_skoptions.m_volume2 * m_injectpos2) / CXP3KDev::PLUNGER_RESOLUTION;
				CheckVolume(2, m_totalamount2, m_currentamount2, m_injectdirection2, m_totalamount2);
			}
			else
			{
				m_totalamount2 = 0;
			}

			if (m_anyinjections)
				m_nextinjection = 0;
			else
				m_nextinjection = -1;
		}
		else
		{
			m_nextinjection = -1;
		}
		UpdateAllViews(NULL);
	}
}

void CSKDoc::InstanceTimerCallback(void)
{
	if ((m_time_wait) && (timeGetTime() >= m_time_end))
	{
		m_time_wait = false;
		SampleStart();
	}
	if ((GetMode() == MODE_MEASURING) && (m_anyinjections))
	{
		CheckInjection(false, timeGetTime());
	}
}

void CALLBACK CSKDoc::TimerCallback(UINT uID, UINT, DWORD dwUser, DWORD, DWORD)
{
	((CSKDoc*)dwUser)->InstanceTimerCallback();
}

void CSKDoc::OnUpdateFileSaveAsText(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}

void CSKDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		if (SaveModified())
		{
			m_pps.Load(ProtGetApp()->m_filetitle);

			if (OnNewDocument())
			{
				if (m_anyinjections)
				{
					m_totalamount1 = m_pps.GetTotalInjectVolume(1);
					CheckVolume(1, m_totalamount1, m_currentamount1, m_injectdirection1, m_totalamount1);
					if (SKGetApp()->m_skoptions.m_num_injectors == 2)
					{
						m_totalamount2 = m_pps.GetTotalInjectVolume(2);
						CheckVolume(2, m_totalamount2, m_currentamount2, m_injectdirection2, m_totalamount2);
					}

					if (m_anyinjections)
						m_nextinjection = 0;
					else
						m_nextinjection = -1;
				}
				UpdateAllViews(NULL);
			}
		}
	}
}

void CSKDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class


	// Init measurement counter to 0
	m_delaycount = 0;
	m_meascount = 0;
	m_intervalcount = 0;
	m_updatecount = 0;
	if (m_timer_id != 0)
	{
		timeKillEvent(m_timer_id);
		m_timer_id = 0;
	}
	m_time_wait = false;
	if (m_pps.m_intervaltime >= 30)
	{
		// for greater than 3 seconds, update every sample
		m_update_every_n_samples = 1;
	}
	else
	{
		// for less than 3 seconds, update after however
		// many sample falls within 3 seconds (rounded to
		// the nearest sample)
		m_update_every_n_samples = 30 / m_pps.m_intervaltime;
	}

	// Reset kinetics
	m_kinetics.Reset();

	// Reset the sample information
	m_samples.RemoveAll();
	m_numsamples = m_pps.m_numsamples + (m_pps.UseBackground() ? 1 : 0);
	m_samples.SetSize(m_numsamples);
	UINT i;
	for (i = 0; i < m_numsamples; i++)
	{
		m_samples[i].m_replicates.SetSize(m_pps.m_numreplicates);
	}

	m_graph_replicates.SetSize(m_pps.m_numreplicates);
	for (i = 0; i < m_pps.m_numreplicates; i++)
	{
		m_graph_replicates[i] = true;
	}

	// Call parent
	CProtocolDoc::DeleteContents();

	// Start out in stopped mode
	SetMode(MODE_STOPPED);

	// Setup the series, sample, and replicate counter
	m_sample_num = 0;
	m_replicate_num = 0;

	SetModifiedFlag(FALSE);

	RemoveLog();

	SetStatus();
}

BOOL CSKDoc::LogDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;
	CFile file;
	if (file.Open(SKGetApp()->m_logpath, CFile::modeCreate | CFile::modeWrite))
	{
		if (SaveMDS(file))
		{
			ok = TRUE;
		}
		file.Close();
	}

	return ok;
}

void CSKDoc::RemoveLog()
{
	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		try
		{
			CFile::Remove(SKGetApp()->m_logpath);
		}
		catch(CFileException* e)
		{
			e->Delete();
		}
	}
}

BOOL CSKDoc::OnSaveDocument(LPCTSTR pathname)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;

	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		UpdateAllViews(NULL);

		CString err_str;
		CFile file;
		if (file.Open(pathname, CFile::modeCreate | CFile::modeWrite))
		{
			if (SaveMDS(file))
			{
				ok = TRUE;
				SetModifiedFlag(FALSE);
				RemoveLog();
			}
			else
			{
				err_str.Format("Error while writing file:\n\n%s", pathname);
				SCMessageBox(err_str);
			}

			file.Close();
		}
		else
		{
			err_str.Format("Unable to open file for saving:\n\n%s", pathname);
			SCMessageBox(err_str);
		}
	}

	return ok;
	//return CProtocolDoc::OnSaveDocument(lpszPathName);
}

BOOL CSKDoc::OnOpenDocument(LPCTSTR pathname)
{
	//if (!CProtocolDoc::OnOpenDocument(lpszPathName))
	//	return FALSE;

	// TODO: Add your specialized creation code here
	BOOL ok = FALSE;
	CString err_str;
	CFile file;
	if (file.Open(pathname, CFile::modeRead))
	{
		if (LoadMDS(file))
		{
			ok = TRUE;
			SetModifiedFlag(FALSE);
		}
		else
		{
			err_str.Format("Error while reading measurement data file:\n\n%s", pathname);
			SCMessageBox(err_str);
		}

		file.Close();
	}
	else
	{
		err_str.Format("Unable to open measurement data file:\n\n%s", pathname);
		SCMessageBox(err_str);
	}

	return ok;
}

BOOL CSKDoc::SaveMDS(CFile& mds_file)
{
	try
	{
		mds_file.SeekToBegin();
		mds_file.SetLength(0);

		// Write the PPS data
		if (!SKGetApp()->m_pps.Write(mds_file))
		{
			return FALSE;
		}

		// Write version number
		WORD version = 1;
		mds_file.Write(&version, sizeof(version));

		// Write the MDS data
		int year = m_datetime.GetYear();
		int month = m_datetime.GetMonth();
		int day = m_datetime.GetDay();
		int hour = m_datetime.GetHour();
		int minute = m_datetime.GetMinute();
		int second = m_datetime.GetSecond();
		mds_file.Write(&year, sizeof(year));
		mds_file.Write(&month, sizeof(month));
		mds_file.Write(&day, sizeof(day));
		mds_file.Write(&hour, sizeof(hour));
		mds_file.Write(&minute, sizeof(minute));
		mds_file.Write(&second, sizeof(second));
		mds_file.Write(&CSample::m_background, sizeof(CSample::m_background));

		UINT i, rep_index;
		for (i = 0; i < m_numsamples; i++)
		{
			for (rep_index = 0; rep_index < m_pps.m_numreplicates; rep_index++)
			{
				mds_file.Write(&m_samples[i].m_replicates[rep_index].m_RLU, sizeof(m_samples[i].m_replicates[rep_index].m_RLU));
				mds_file.Write(&m_samples[i].m_replicates[rep_index].m_used, sizeof(m_samples[i].m_replicates[rep_index].m_used));
			}
		}
	}
	catch (CFileException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}


BOOL CSKDoc::LoadMDS(CFile& mds_file)
{
	try
	{
		// Read the PPS data
		if (!SKGetApp()->m_pps.Read(mds_file))
		{
			return FALSE;
		}

		// Read the version
		WORD version = 0;
		if ((mds_file.Read(&version, sizeof(version)) != sizeof(version)) ||
			(version != 1))
		{
			return FALSE;
		}

		// Read the MDS data
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		if ((mds_file.Read(&year, sizeof(year)) != sizeof(year)) ||
			(mds_file.Read(&month, sizeof(month)) != sizeof(month)) ||
			(mds_file.Read(&day, sizeof(day)) != sizeof(day)) ||
			(mds_file.Read(&hour, sizeof(hour)) != sizeof(hour)) ||
			(mds_file.Read(&minute, sizeof(minute)) != sizeof(minute)) ||
			(mds_file.Read(&second, sizeof(second)) != sizeof(second)) ||
			(mds_file.Read(&CSample::m_background, sizeof(CSample::m_background)) != sizeof(CSample::m_background)))
		{
			return FALSE;
		}
		CTime time(year, month, day, hour, minute, second);
		m_datetime = time;

		// The following call will resize the m_samples[] and
		// m_sample_names[] arrays for me
		DeleteContents();

		UINT i, rep_index;
		CReplicate rep;
		for (i = 0; i < m_numsamples; i++)
		{
			for (rep_index = 0; rep_index < m_pps.m_numreplicates; rep_index++)
			{
				if ((mds_file.Read(&rep.m_RLU, sizeof(rep.m_RLU)) != sizeof(rep.m_RLU)) ||
					(mds_file.Read(&rep.m_used, sizeof(rep.m_used)) != sizeof(rep.m_used)))
				{
					return FALSE;
				}
				m_samples[i].m_replicates[rep_index] = rep;
			}
			m_samples[i].Recalculate();
		}
	}
	catch (CFileException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}

void CSKDoc::OnMeasureStart()
{
	// TODO: Add your command handler code here
	if ((SKGetApp()->m_mode == CSKApp::APPMODE_RUN) &&
		(GetMode() == MODE_STOPPED))
	{
		//if (SKGetApp()->m_pFB12Device->get_dooropen())
		//{
		//	SCMessageBox(_T("The door is open.  Close the door and try again."));
		//}
		//else
		if (!SKGetApp()->m_pFB12Device->get_communicating())
		{
			SCMessageBox(_T("The instrument is not communicating.\nCheck the cabling and serial parameters and try again."));
		}
		else
		{
			MeasureStart(false);  // start measuring with no delay
		}
	}
}

void CSKDoc::OnUpdateMeasureStart(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ((SKGetApp()->m_skoptions.m_num_injectors == 1) && (m_anyinjections))
	{
		pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
		pCmdUI->Enable((m_pps.UseStartButton() && 
			(m_injectstate1 == ISTATE_INITIALIZED) &&
			(m_replicate_num < m_pps.m_numreplicates) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
	else if ((SKGetApp()->m_skoptions.m_num_injectors == 2) && (m_anyinjections))
	{
		pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
		pCmdUI->Enable((m_pps.UseStartButton() && 
			(m_injectstate1 == ISTATE_INITIALIZED) &&
			(m_injectstate2 == ISTATE_INITIALIZED) &&
			(m_replicate_num < m_pps.m_numreplicates) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
	else
	{
		pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
		pCmdUI->Enable((m_pps.UseStartButton() &&
			(m_replicate_num < m_pps.m_numreplicates) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
}

void CSKDoc::OnMeasureStop()
{
	// TODO: Add your command handler code here
	if ((SKGetApp()->m_mode == CSKApp::APPMODE_RUN) &&
		(GetMode() == MODE_MEASURING))
	{
		// Oops, user stopped the measurement
		MeasureEnd();
		SCMessageBox("You stopped the measurement in progess.\n\nMeasurement aborted.");
	}
}

void CSKDoc::OnUpdateMeasureStop(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 1 : 0);
	pCmdUI->Enable(((m_replicate_num < m_pps.m_numreplicates) &&
		(GetMode() != MODE_STOPPED)) ? TRUE : FALSE);
}

void CSKDoc::OnButtonUp() 
{
	if ((m_inject_num == 1) && (m_injectpos1 > 0))
			ManualInject(1, 120);
	else if ((m_inject_num == 2) &&(m_injectpos2 > 0))
			ManualInject(1, 120);
}

void CSKDoc::OnButtonDown() 
{
	// TODO: Add your command handler code here
	if ((m_inject_num == 1) && (m_injectpos1 < CXP3KDev::PLUNGER_RESOLUTION))
		ManualInject(0, 120);	
	else if ((m_inject_num == 2) && (m_injectpos2 < CXP3KDev::PLUNGER_RESOLUTION))
		ManualInject(0, 120);	

}

void CSKDoc::OnUpdateButtonDown(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
	//(m_replicate_num < m_pps.m_numreplicates) &&
	if (m_inject_num == 1)
	{
		pCmdUI->Enable(((m_injectstate1 == ISTATE_INITIALIZED) && 
						(m_injectpos1 < CXP3KDev::PLUNGER_RESOLUTION) &&
						(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
						(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
	else 
	{
		pCmdUI->Enable(((m_injectstate2 == ISTATE_INITIALIZED) &&
						(m_injectpos2 < CXP3KDev::PLUNGER_RESOLUTION) &&
						(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
						(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
		
}

void CSKDoc::OnUpdateButtonUp(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
	//(m_replicate_num < m_pps.m_numreplicates) &&
	if (m_inject_num == 1)
	{
		pCmdUI->Enable(((m_injectstate1 == ISTATE_INITIALIZED) && (m_injectpos1 > 0) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
	else 
	{
		pCmdUI->Enable(((m_injectstate2 == ISTATE_INITIALIZED) && 
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(m_injectpos2 > 0) && (GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
}

void CSKDoc::OnButtonInit() 
{
	// TODO: Add your command handler code here
	if (SCMessageBox("Please verify that \n- there is an empty tube in the chamber, and \n- the FB12 door is closed. \nPress OK to continue Injector initialization, or Cancel to abort.",
		MB_OKCANCEL) == IDOK)
	{
		if ((SKGetApp()->m_skoptions.m_num_injectors == 1) && (m_injectstate1 != ISTATE_ERROR))
		{
			m_injectstate1 = ISTATE_STARTED;
			m_injector_control.Init(1);
		}
		else if ((SKGetApp()->m_skoptions.m_num_injectors == 2) && 
				(m_injectstate1 != ISTATE_ERROR) && (m_injectstate2 != ISTATE_ERROR))
		{
			m_injectstate1 = ISTATE_STARTED;
			m_injector_control.Init(1);
			m_injectstate2 = ISTATE_STARTED;
			m_injector_control.Init(2);
		}
	}
}

void CSKDoc::OnUpdateButtonInit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (SKGetApp()->m_skoptions.m_num_injectors == 1) 
	{
		pCmdUI->Enable((((m_injectstate1 == ISTATE_STARTED) || 
			(m_injectstate1 == ISTATE_INITIALIZED)) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
	else if (SKGetApp()->m_skoptions.m_num_injectors == 2) 
	{
		pCmdUI->Enable((((m_injectstate1 == ISTATE_STARTED) || 
			(m_injectstate1 == ISTATE_INITIALIZED)) &&
			((m_injectstate2 == ISTATE_STARTED) || 
			(m_injectstate2 == ISTATE_INITIALIZED)) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
	}
}

void CSKDoc::OnButtonInjector1() 
{
	// TODO: Add your command handler code here
	m_inject_num = 1;
	
}

void CSKDoc::OnButtonInjector2() 
{
	// TODO: Add your command handler code here
	m_inject_num = 2;
}

void CSKDoc::OnUpdateButtonInjector1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_inject_num == 1)? 1 : 0);
	pCmdUI->Enable((SKGetApp()->m_skoptions.m_num_injectors > 0) ? TRUE : FALSE);
}

void CSKDoc::OnUpdateButtonInjector2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_inject_num == 2)? 1 : 0);
	pCmdUI->Enable((SKGetApp()->m_skoptions.m_num_injectors == 2) ? TRUE : FALSE);	
}

void CSKDoc::OnButtonLeft() 
{
	// TODO: Add your command handler code here
	m_injector_control.SetValve(m_inject_num, 0);
	if (m_inject_num == 1)
		m_injectdirection1 = 0;
	else
		m_injectdirection2 = 0;
}

void CSKDoc::OnUpdateButtonLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_inject_num == 1)
	{
		pCmdUI->SetCheck((m_injectdirection1 == 0) ? 1 : 0);
		pCmdUI->Enable(((m_injectstate1 == ISTATE_INITIALIZED) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->SetCheck((m_injectdirection2 == 0) ? 1 : 0);
		pCmdUI->Enable(((m_injectstate2 == ISTATE_INITIALIZED) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);	
	}
}

void CSKDoc::OnButtonRight() 
{
	// TODO: Add your command handler code here
	m_injector_control.SetValve(m_inject_num, 1);
	if (m_inject_num == 1)
		m_injectdirection1 = 1;
	else
		m_injectdirection2 = 1;
}

void CSKDoc::OnUpdateButtonRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_inject_num == 1)
	{
		pCmdUI->SetCheck((m_injectdirection1 == 1) ? 1 : 0);
		pCmdUI->Enable(((m_injectstate1 == ISTATE_INITIALIZED) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->SetCheck((m_injectdirection2 == 1) ? 1 : 0);
		pCmdUI->Enable(((m_injectstate2 == ISTATE_INITIALIZED) &&
			(SKGetApp()->m_pFB12Device->get_dooropen() != VARIANT_TRUE) &&
			(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);	
	}
}

void CSKDoc::OnMeasureKinetics()
{
	// TODO: Add your command handler code here
	ToggleKinetics();
}

void CSKDoc::OnUpdateMeasureKinetics(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_graph_view == NULL) ? 0 : 1);
}

void CSKDoc::OnUpdateMode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}

void CSKDoc::Increment()
{
	if (m_sample_num == (m_numsamples - 1))
	{
		m_replicate_num++;
		m_sample_num = 0;
	}
	else
	{
		m_sample_num++;
	}
}

void CSKDoc::SetStatus()
{
	// Change the status message
	CString status_str;

	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		if (m_replicate_num < m_pps.m_numreplicates)
		{
			if (m_anyinjections)
			{
				if ((SKGetApp()->m_skoptions.m_num_injectors == 1) &&
					(m_injectstate1 != ISTATE_INITIALIZED) &&
					(m_injectstate1 != ISTATE_ERROR))
				{
					status_str = "Press the Injector Initialization button.";
				}
				else if ((SKGetApp()->m_skoptions.m_num_injectors == 2) &&
					(m_injectstate2 != ISTATE_INITIALIZED) && (m_injectstate2 != ISTATE_INITIALIZED) &&
					(m_injectstate1 != ISTATE_ERROR) && (m_injectstate2 != ISTATE_ERROR))
				{
					status_str = "Press the Injector Initialization button.";
				}
			}
			else if (m_pps.UseStartButton())
			{
				status_str.Format("Press start button or space bar or enter key to measure replicate %ld.",
					m_replicate_num + 1);
			}
			else
			{
				status_str.Format("Close luminometer door to measure replicate %ld.",
					m_replicate_num + 1);
			}
		}
		else
		{
			status_str = "No more replicates to measure.";
		}
	}
	else
	{
		status_str = "View and export data.";
	}

	if (SKGetApp()->m_pMainFrame)
	{
		SKGetApp()->m_pMainFrame->SetMessageText(status_str);
	}
}

CString CSKDoc::GetReplicateString(UINT sample, UINT replicate)
{
	CString rep_str;

	if (sample < m_numsamples)
	{
		if ((sample == 0) && m_pps.UseBackground())
		{
			rep_str.Format("background for replicate %ld", replicate + 1);
		}
		else
		{
			rep_str.Format("measurement %ld for replicate %ld",
				sample + (m_pps.UseBackground() ? 0 : 1), replicate + 1);
		}
	}
	else
	{
		rep_str = "none";
	}

	return rep_str;
}

void CSKDoc::SetModifiedFlag(BOOL bModified)
{
	CProtocolDoc::SetModifiedFlag(
		(SKGetApp()->m_mode == CSKApp::APPMODE_VIEW) ? FALSE : bModified);
}

CString CSKDoc::GetTimerText()
{
	CString txt;
	if (m_mode2 == MODE_WAITINTERVAL)
	{
		if (m_pps.IsLumiTimeBase())
		{
			if (m_intervalcount > 0)
			{
				txt.Format("I %s", (LPCTSTR)SCFormatDeciseconds(m_intervalcount * (10 / SAMPLES_PER_SEC)));
			}
		}
		else
		{
			long diff_time = m_time_end - timeGetTime();
			if (diff_time > 0)
			{
				diff_time = (diff_time + 50) / 100;
				txt.Format("I %s", SCFormatDeciseconds(diff_time));
			}
		}
	}
	else if (m_delaycount > 0)
	{
		txt.Format("D %s", (LPCTSTR)SCFormatDeciseconds(m_delaycount * (10 / SAMPLES_PER_SEC)));
	}
	else if (m_meascount > 0)
	{
		txt.Format("M %s", (LPCTSTR)SCFormatDeciseconds(m_meascount * (10 / SAMPLES_PER_SEC)));
	}
	return txt;
}

void CSKDoc::OnMeasureGrid() 
{
	// TODO: Add your command handler code here
	ToggleGrid();
}

void CSKDoc::OnUpdateMeasureGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_grid_view == NULL) ? 0 : 1);
}


void CSKDoc::XP3KStartResponse(BYTE result)
{
	if (result == CXP3KDev::ERROR_NONE)
	{
		//m_injectstate = ISTATE_STARTED;
		// If we are started, try moving the plunger 0 steps to
		// see if the pump is initialized or not.
		m_injector_control.MoveToRelative(1, 0, 0);
		if (SKGetApp()->m_skoptions.m_num_injectors == 2) 
			m_injector_control.MoveToRelative(2, 0, 0);
	}
	else
	{
		// Error message - could not connect to inject.
		CString err_msg;
		err_msg = "Could not connect to Cavro Injector(s).\nVerify no other applications are using the COM port.";
		err_msg += restart_msg;
		SCMessageBox(err_msg);
		m_injectstate1 = ISTATE_ERROR;
		m_injectstate2 = ISTATE_ERROR;
	}
}

	
void CSKDoc::XP3KMoveToRelativeResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if (result == CXP3KDev::ERROR_NONE)
	{
		if (status == CXP3KDev::ERR_NONE)
		{
			if (dev_num == 1)
			{
				if (m_injectstate1 == ISTATE_INITIALIZED)
				{
					m_injector_control.GetPosition(1);
				}
				else if (m_injectstate1 == ISTATE_NIL)
				{
					// No error on first try to move 0 steps, sometimes
					// (most times) it takes two tries.
					m_injectstate1 = ISTATE_CHECK;
					m_injector_control.MoveToRelative(1, 0, 0);
				}
				else if (m_injectstate1 == ISTATE_CHECK)
				{
					// No error after two tries -> Pump is already initialized
					// Now, do the last step of the initialiazation process where
					// the volume is checked.
					m_injectstate1 = ISTATE_INIT_RIGHT;
					m_injector_control.GetPosition(1);
				}
			}
			else 
			{
				if (m_injectstate2 == ISTATE_INITIALIZED)
				{
					m_injector_control.GetPosition(2);
				}
				else if (m_injectstate2 == ISTATE_NIL)
				{
					// No error on first try to move 0 steps, sometimes
					// (most times) it takes two tries.
					m_injectstate2 = ISTATE_CHECK;
					m_injector_control.MoveToRelative(2, 0, 0);
				}
				else if (m_injectstate2 == ISTATE_CHECK)
				{
					// No error after two tries -> Pump is already initialized
					// Now, do the last step of the initialiazation process where
					// the volume is checked.
					m_injectstate2 = ISTATE_INIT_RIGHT;
					m_injector_control.GetPosition(2);
				}
			}
		}
		else if (status == CXP3KDev:: ERR_NOINIT)
		{
			if ((dev_num == 1) && ((m_injectstate1 == ISTATE_NIL) || (m_injectstate1 == ISTATE_CHECK)))
			{
				// Checking to see if pump is initialized shows that it is not.
				// Put state back to started.
				m_injectstate1 = ISTATE_STARTED;
			}
			else if ((dev_num == 2) && ((m_injectstate2 == ISTATE_NIL) || (m_injectstate2 == ISTATE_CHECK)))
			{
				m_injectstate2 = ISTATE_STARTED;
			}
			else
			{
				if (GetMode() == MODE_MEASURING)
					MeasureEnd();
				SCMessageBox("Please initialize the injector(s) to continue.");
				if (dev_num == 1) 
					m_injectstate1 = ISTATE_STARTED;
				else
					m_injectstate2 = ISTATE_STARTED;
			}
		}
		else if (status != CXP3KDev:: ERR_OPERAND) 
		{
			if (dev_num == 1)
				m_injectstate1 = ISTATE_ERROR;
			else
				m_injectstate2 = ISTATE_ERROR;
			if (GetMode() == MODE_MEASURING)
				MeasureEnd();
			SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
		}
	}
	else
	{
		// handle error
		if (dev_num == 1)
			m_injectstate1 = ISTATE_ERROR;
		else
			m_injectstate2 = ISTATE_ERROR;
		if (GetMode() == MODE_MEASURING)
			MeasureEnd();

		SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
	}
}


void CSKDoc::XP3KGetPositionResponse(BYTE dev_num, BYTE result, BYTE status, int pos)
{
	if ((result == CXP3KDev::ERROR_NONE) && (status == CXP3KDev::ERR_NONE))
	{
		if (dev_num == 1)
		{
			m_injectpos1 = pos;
			if (m_injectstate1 == ISTATE_INIT_RIGHT)
			{
				m_injector_control.SetSpeed(1, SKGetApp()->m_skoptions.m_speed);
				m_injectstate1 = ISTATE_INIT_SETSPEED;
			}
			else if (m_injectstate1 == ISTATE_INIT_CKVOLUME) 
			{
				m_injectstate1 = ISTATE_INITIALIZED;
				SetStatus();
			}
		}
		else
		{
			m_injectpos2 = pos;
			if (m_injectstate2 == ISTATE_INIT_RIGHT)
			{
				m_injector_control.SetSpeed(2, SKGetApp()->m_skoptions.m_speed2);
				m_injectstate2 = ISTATE_INIT_SETSPEED;
			}
			else if (m_injectstate2 == ISTATE_INIT_CKVOLUME) 
			{
				m_injectstate2 = ISTATE_INITIALIZED;
				SetStatus();
			}
		}
	}
	else
	{
		// handle  error
		if (status != CXP3KDev:: ERR_OPERAND)
		{
			if (dev_num == 1)
				m_injectstate1 = ISTATE_ERROR;
			else
				m_injectstate2 = ISTATE_ERROR;

			if (GetMode() == MODE_MEASURING)
				MeasureEnd();
			SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
		}

	}
}

void CSKDoc::XP3KDrawResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if ((result == CXP3KDev::ERROR_NONE) && (status == CXP3KDev::ERR_NONE))
	{
			m_injector_control.GetPosition(dev_num);
	}
	else
	{
		// handle error
		if (status != CXP3KDev:: ERR_OPERAND)
		{
			if (dev_num == 1)
				m_injectstate1 = ISTATE_ERROR;
			else
				m_injectstate2 = ISTATE_ERROR;

			if (GetMode() == MODE_MEASURING)
				MeasureEnd();

			SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
		}
	}
}

void CSKDoc::XP3KInjectResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if ((result == CXP3KDev::ERROR_NONE) && (status == CXP3KDev::ERR_NONE))
	{
		if ((dev_num == 1) && (m_injectstate1 == ISTATE_INITIALIZED))
			m_injector_control.GetPosition(1);
		else if ((dev_num == 2) && (m_injectstate2 == ISTATE_INITIALIZED))
			m_injector_control.GetPosition(2);
	}
	else
	{
		// handle error
		if (status != CXP3KDev:: ERR_OPERAND)
		{
			if (dev_num == 1)
				m_injectstate1 = ISTATE_ERROR;
			else
				m_injectstate2 = ISTATE_ERROR;

			if (GetMode() == MODE_MEASURING)
				MeasureEnd();

			SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
		}
	}
}


void CSKDoc::XP3KSetSpeedResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if (result == CXP3KDev::ERROR_NONE)
	{
		if ((dev_num == 1) && (m_injectstate1 == ISTATE_INIT_SETSPEED))
		{
			m_injectstate1 = ISTATE_INIT_CKVOLUME;
			m_currentamount1 = (SKGetApp()->m_skoptions.m_volume * m_injectpos1) / CXP3KDev::PLUNGER_RESOLUTION;
			CheckVolume(1, m_totalamount1, m_currentamount1, m_injectdirection1, m_totalamount1);
			if (m_anyinjections)
				m_nextinjection = 0;
			else
				m_nextinjection = -1;
		}
		else if ((dev_num == 2) && (m_injectstate2 == ISTATE_INIT_SETSPEED))
		{
			m_injectstate2 = ISTATE_INIT_CKVOLUME;
			m_currentamount2 = (SKGetApp()->m_skoptions.m_volume2 * m_injectpos2) / CXP3KDev::PLUNGER_RESOLUTION;
			CheckVolume(2, m_totalamount2, m_currentamount2, m_injectdirection2, m_totalamount2);
			if (m_anyinjections)
				m_nextinjection = 0;
			else
				m_nextinjection = -1;
		}
	}
	else
	{
		if (dev_num == 1)
			m_injectstate1 = ISTATE_ERROR;
		else
			m_injectstate2 = ISTATE_ERROR;
		// Error message
		SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
	}
}

void CSKDoc::XP3KSetValveResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if ((result == CXP3KDev::ERROR_NONE) && (status == CXP3KDev::ERR_NONE))
	{
		// Valve moved successfully
	}
	else
	{
		// Handle error
		if (dev_num == 1)
			m_injectstate1 = ISTATE_ERROR;
		else
			m_injectstate2 = ISTATE_ERROR;

		if (GetMode() == MODE_MEASURING)
			MeasureEnd();

		SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
	}	
}

void CSKDoc::XP3KInitResponse(BYTE dev_num, BYTE result, BYTE status)
{
	if ((result == CXP3KDev::ERROR_NONE) && (status == CXP3KDev::ERR_NONE))
	{
		if (dev_num == 1)
		{
			if (m_injectstate1 == ISTATE_STARTED)
			{
				m_injector_control.Init(1);
				m_injectstate1 = ISTATE_INIT_LEFT;
			}
			else if (m_injectstate1 == ISTATE_INIT_LEFT)
			{
				m_injector_control.GetPosition(1);
				m_injectstate1 = ISTATE_INIT_RIGHT;
			}
		}
		else
		{
			if (m_injectstate2 == ISTATE_STARTED)
			{
				m_injector_control.Init(2);
				m_injectstate2 = ISTATE_INIT_LEFT;
			}
			else if (m_injectstate2 == ISTATE_INIT_LEFT)
			{
				m_injector_control.GetPosition(2);
				m_injectstate2 = ISTATE_INIT_RIGHT;
			}
		}
	}
	else
	{
		// Handle error
		if (dev_num == 1)
			m_injectstate1 = ISTATE_ERROR;
		else
			m_injectstate2 = ISTATE_ERROR;
		if (GetMode() == MODE_MEASURING)
			MeasureEnd();

		SCMessageBox(m_injector_control.GetErrString(dev_num, result, status)+restart_msg);
	}
}

// Called by the Injector toolbar to move the plunger
// on the injector.  direction is the direction to move the
// plunger (0 => down, 1 => up).  Steps is the number of
// steps to move the plunger (0..3000)
void CSKDoc::ManualInject(BYTE direction, int steps)
{
	if ((m_inject_num == 1) && (m_injectstate1 == ISTATE_INITIALIZED))
	{
		m_injector_control.MoveToRelative(1, direction, steps);
	}
	else if ((m_inject_num == 2) && (m_injectstate2 == ISTATE_INITIALIZED))
	{
		m_injector_control.MoveToRelative(2, direction, steps);
	}

}


void CSKDoc::CheckVolume(BYTE dev_num, int& total, int& current, short& direction, int requested_volume)
{
	int inject_volume; // = m_totalamount - m_currentamount;
	int syringe_volume; 

	if (dev_num == 1)
		syringe_volume = SKGetApp()->m_skoptions.m_volume;
	else
		syringe_volume = SKGetApp()->m_skoptions.m_volume2;

	if (((dev_num == 1) && (m_injectstate1 != ISTATE_ERROR)) ||
		((dev_num == 2) && (m_injectstate2 != ISTATE_ERROR)))
	{
		if (requested_volume > current)
		{
			// if we have to draw in some liquid anyway, why not draw
			// in enough for however much we have left to measure (i.e. m_totalamount)
			if (total > syringe_volume)
			{
				// Measurement total amount to inject is greater
				// than syringe can hold
				inject_volume = syringe_volume - current;
			}
			else
			{
				inject_volume = total - current;
			}
			m_injector_control.Draw(dev_num, inject_volume);
			direction = 0;
			current += inject_volume;
		}
		else
		{
			m_injector_control.GetPosition(dev_num);
		}
	}
}

BOOL CSKDoc::InjectionStart(bool use_count, DWORD start_time)
{
	//m_totalamount = m_pps.GetTotalInjectVolume();

	if (((m_totalamount1 > 0) && (m_injectstate1 == ISTATE_INITIALIZED)) ||
		((m_totalamount2 > 0) && (m_injectstate2 == ISTATE_INITIALIZED)))
	{
		int idx;
		for (idx=0; idx < CSKPPS::MAX_INJECTIONS; idx++)
		{
			if (m_pps.m_injections[idx].m_used > 0)
			{
				if (use_count)
				{
					m_injectionlist[idx] = (int)(m_pps.m_injections[idx].m_time / (10 / SAMPLES_PER_SEC));
				}
				else
				{
					if ((start_time + (m_pps.m_injections[idx].m_time * 100)) > 0xffffffff)
					{
						SCMessageBox("The system timer is too high.\nYou must restart your computer or use the\n\"Use luminomter as time base\" option to take a measurement.");
						return FALSE;
					}
					else 
					{
						m_injectionlist[idx] = start_time + (m_pps.m_injections[idx].m_time * 100);
					}
				}
			}
			else
			{
				// Not used
				m_injectionlist[idx] = 0;
			}
		}
	}
	return TRUE;
}

void CSKDoc::CheckInjection(bool use_count, DWORD time_now)
{

	if ((m_anyinjections) && (m_totalamount1 + m_totalamount2 > 0))
	{
		int idx;
		for (idx=0; idx < CSKPPS::MAX_INJECTIONS; idx++)
		{
			if (m_pps.m_injections[idx].m_used > 0)
			{
				if (use_count)
				{
					m_injectionlist[idx]--;
					if (m_injectionlist[idx] == 0)
					{
						if ((m_pps.m_injections[idx].m_used == 1) && 
							(m_injectstate1 == ISTATE_INITIALIZED))
						{
							DoInjection(1, idx, m_totalamount1, m_currentamount1, m_injectdirection1);
						}
						else if ((m_pps.m_injections[idx].m_used == 2) && 
							(m_injectstate2 == ISTATE_INITIALIZED))
						{
							DoInjection(2, idx, m_totalamount2, m_currentamount2, m_injectdirection2);
						}
					}
				}
				else
				{
					if(time_now >= m_injectionlist[idx])
					{
						if ((m_pps.m_injections[idx].m_used == 1) && 
							(m_injectstate1 == ISTATE_INITIALIZED))
						{
							DoInjection(1, idx, m_totalamount1, m_currentamount1, m_injectdirection1);
						}
						else if ((m_pps.m_injections[idx].m_used == 2) && 
							(m_injectstate2 == ISTATE_INITIALIZED))
						{
							DoInjection(2, idx, m_totalamount2, m_currentamount2, m_injectdirection2);
						}
						m_injectionlist[idx] = 0xffffffff;
					}
				}
			}
		}
	}
}



void CSKDoc::DoInjection(BYTE dev_num, int inject_idx, int& total, int& current, short& direction)
{
	if (SKGetApp()->m_pFB12Device->get_dooropen() == VARIANT_TRUE) 
	{
		CString status_str;
		status_str = "Injection skipped because FB12 door is open.";
		SKGetApp()->m_pMainFrame->SetMessageText(status_str);
	}
	else
	{
		m_injector_control.Inject(dev_num, m_pps.m_injections[inject_idx].m_volume);
		total -= m_pps.m_injections[inject_idx].m_volume;
		current -= m_pps.m_injections[inject_idx].m_volume;
		direction = 1;
	}
	if ((inject_idx < (CSKPPS::MAX_INJECTIONS - 1)) && (m_pps.m_injections[inject_idx+1].m_used > 0))
	{
		m_nextinjection = inject_idx+1;
		int i, vol = 0;
		// Find dev 1's next injection volume
		for (i = inject_idx+1; i < CSKPPS::MAX_INJECTIONS; i++)
		{
			if (m_pps.m_injections[i].m_used == 0)
				break;  // There are no more injections
			else if (m_pps.m_injections[i].m_used == dev_num)
			{
				// This is the next injection volume for dev 1
				vol = m_pps.m_injections[i].m_volume;
				break;
			}
		}

		CheckVolume(dev_num, total, current, direction, vol);
	}
	else 
	{
		m_nextinjection = -1;
	}
}