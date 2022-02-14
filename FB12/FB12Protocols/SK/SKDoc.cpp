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
	ON_COMMAND(ID_MEASURE_KINETICS, OnMeasureKinetics)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_KINETICS, OnUpdateMeasureKinetics)
	ON_COMMAND(ID_MEASURE_GRID, OnMeasureGrid)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_GRID, OnUpdateMeasureGrid)
	ON_COMMAND(ID_SAMPLESTART, OnSamplestart)
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FB12_DOORSTATUS, OnUpdateDoorStatus)
	ON_UPDATE_COMMAND_UI(ID_FB12_TIMER, OnUpdateTimer)
	ON_UPDATE_COMMAND_UI(ID_FB12_RX, OnUpdateRX)
	ON_UPDATE_COMMAND_UI(ID_TIMER_COUNT, OnUpdateTimerCount)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKDoc construction/destruction

CSKDoc::CSKDoc() : m_meascount(0), m_delaycount(0),
	m_pps(SKGetApp()->m_pps), m_timer_id(0),
	m_kinetics(SKGetApp()->m_pps.m_meastime / (10 / SAMPLES_PER_SEC)),
	m_counter(0)
{
	// TODO: add one-time construction code here
	// Get the current date and time
	time_t sys_time;
	time(&sys_time);
	CTime now(sys_time);
	m_datetime = now;

	// Graph view inits
	m_graph_cy = 75;
	m_graph_scroll_pt = CPoint(0, 0);
	m_graph_showaverage = true;
	m_graph_smoothing = false;
	m_graph_manual = false;
	m_graph_log = false;
	m_graph_RLU_min = 0;
	m_graph_RLU_max = 1000;
	// m_graph_replicates is in DeleteContents()

	// Load some stuff from the registry
	CString appname = "STLS\\";
	appname += AfxGetApp()->m_pszAppName;
	m_graph_cy = SCGetAppProfileInt(appname, "Settings", "GraphOptsSize", m_graph_cy);
	SCGetAppProfileBinary(appname, "Settings", "GraphOptsPos",
		(BYTE*)&m_graph_scroll_pt, sizeof(m_graph_scroll_pt));
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
//#ifdef _DEBUG
//	CMemoryState oldMemState, newMemState, diffMemState;
//    oldMemState.Checkpoint();
//#endif
		
	m_counter++;

	if (GetMode() == MODE_MEASURING)
	{
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

	m_counter--;

//#ifdef _DEBUG
//	newMemState.Checkpoint();
//    if (diffMemState.Difference(oldMemState, newMemState))
//	{
//        TRACE("Memory leaked!\n");
//	}
//#endif
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
				MeasureStart(true);	// start measuring with delay
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
		TCHAR status_str[64];
		if (m_delaycount == 0)
		{
			TCHAR rep_str[48];
			GetReplicateString(m_sample_num, m_replicate_num, rep_str);
			sprintf(status_str, "Taking %s...", rep_str);
		}
		else
		{
			strcpy(status_str, "Waiting for delay time to pass...");
			//status_str.LoadString(IDS_DELAYMESSAGE);
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

		if (m_pps.IsLumiTimeBase() || (m_pps.m_meastime == m_pps.m_intervaltime))
		{
			// Change the mode
			SetMode(MODE_MEASURING);

			// Start first sample
			SampleStart(delay);
		}
		else
		{
			m_time_wait = false;
			m_timer_id = timeSetEvent(50, 50, TimerCallback, (DWORD)this, TIME_PERIODIC);
			if (m_timer_id != 0)
			{
				// Get the starting milliseconds
				m_time_end = timeGetTime();
				if ((0xffffffff - m_time_end) < (m_pps.m_intervaltime * 100 * m_numsamples))
				{
					SCMessageBox("The system timer is too high.\nYou must restart your computer or use the\n\"Use luminomter as time base\" option to take a measurement.");
				}
				else
				{
					// Change the mode
					SetMode(MODE_MEASURING);

					// Start first sample
					SampleStart(delay);
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
}

void CSKDoc::InstanceTimerCallback(void)
{
	if ((m_time_wait) && (timeGetTime() >= m_time_end))
	{
		m_time_wait = false;
		//SampleStart();
		AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, ID_SAMPLESTART, 0);
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
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
	pCmdUI->Enable((m_pps.UseStartButton() &&
		(m_replicate_num < m_pps.m_numreplicates) &&
		(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
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
	TCHAR status_str[128];
	status_str[0] = 0;

	if (SKGetApp()->m_mode == CSKApp::APPMODE_RUN)
	{
		if (m_replicate_num < m_pps.m_numreplicates)
		{
			if (m_pps.UseStartButton())
			{
				sprintf(status_str,
					"Press start button or space bar or enter key to measure replicate %ld.",
					m_replicate_num + 1);
			}
			else
			{
				sprintf(status_str,
					"Close luminometer door to measure replicate %ld.",
					m_replicate_num + 1);
			}
		}
		else
		{
			strcpy(status_str, "No more replicates to measure.");
		}
	}
	else
	{
		strcpy(status_str, "View and export data.");
	}

	if (SKGetApp()->m_pMainFrame)
	{
		SKGetApp()->m_pMainFrame->SetMessageText(status_str);
	}
}

// buffer for rep_str should be at least 48 bytes

void CSKDoc::GetReplicateString(UINT sample, UINT replicate, TCHAR *rep_str)
{
	if (sample < m_numsamples)
	{
		if ((sample == 0) && m_pps.UseBackground())
		{
			sprintf(rep_str, "background for replicate %ld", replicate + 1);
		}
		else
		{
			sprintf(rep_str, "measurement %ld for replicate %ld",
				sample + (m_pps.UseBackground() ? 0 : 1), replicate + 1);
		}
	}
	else
	{
		strcpy(rep_str, "none");
	}
}

void CSKDoc::SetModifiedFlag(BOOL bModified)
{
	CProtocolDoc::SetModifiedFlag(
		(SKGetApp()->m_mode == CSKApp::APPMODE_VIEW) ? FALSE : bModified);
}

void CSKDoc::OnUpdateDoorStatus(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	LPCTSTR txt;
	CSKApp* pApp = SKGetApp();
	if (pApp->m_pFB12Device)
	{
		if (pApp->m_pFB12Device->get_dooropen())
		{
			txt = "Door Open";
		}
		else
		{
			txt = "Door Closed";
		}
	}
	else
	{
		txt = "Door ?";
	}

	pCmdUI->SetText(txt);
}

void CSKDoc::OnUpdateTimer(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	TCHAR txt[32];
	TCHAR dsec_str[32];
	txt[0] = 0;
	if (GetMode() == MODE_MEASURING)
	{
		if (GetMode2() == MODE_WAITINTERVAL)
		{
			if (m_pps.IsLumiTimeBase())
			{
				if (m_intervalcount > 0)
				{
					SCFormatDecisecondsCh(m_intervalcount * (10 / SAMPLES_PER_SEC), dsec_str);
					sprintf(txt, "I %s", dsec_str);
				}
			}
			else
			{
				long diff_time = m_time_end - timeGetTime();
				if (diff_time > 0)
				{
					diff_time = (diff_time + 50) / 100;
					SCFormatDecisecondsCh(diff_time, dsec_str);
					sprintf(txt, "I %s", dsec_str);
				}
			}
		}
		else if (m_delaycount > 0)
		{
			SCFormatDecisecondsCh(m_delaycount * (10 / SAMPLES_PER_SEC), dsec_str);
			sprintf(txt, "D %s", dsec_str);
		}
		else if (m_meascount > 0)
		{
			SCFormatDecisecondsCh(m_meascount * (10 / SAMPLES_PER_SEC), dsec_str);
			sprintf(txt, "M %s", dsec_str);
		}
	}

	pCmdUI->SetText(txt);
}

void CSKDoc::OnUpdateRX(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CSKApp* pApp = SKGetApp();
	pCmdUI->Enable(pApp->m_pFB12Device && pApp->m_pFB12Device->get_communicating());
}

void CSKDoc::OnUpdateTimerCount(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	TCHAR num_str[16];
	sprintf(num_str, "%d", m_counter);
	pCmdUI->SetText(num_str);
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

void CSKDoc::OnSamplestart() 
{
	// TODO: Add your command handler code here
	SampleStart();
}
