// MKDoc.cpp : implementation of the CMKDoc class
//

#include "stdafx.h"
#include "MK.h"
#include "MainFrm.h"
#include "General.h"
#include "MKHint.h"
#include <mmsystem.h>
#include "MKView.h"

#include "MKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKDoc

IMPLEMENT_DYNCREATE(CMKDoc, CProtocolDoc)

BEGIN_MESSAGE_MAP(CMKDoc, CProtocolDoc)
	//{{AFX_MSG_MAP(CMKDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_TEXT, OnUpdateFileSaveAsText)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_MEASURE_STOP, OnMeasureStop)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_STOP, OnUpdateMeasureStop)
	ON_COMMAND(ID_MEASURE_KINETICS, OnMeasureKinetics)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_KINETICS, OnUpdateMeasureKinetics)
	ON_COMMAND(ID_MEASURE_GRID, OnMeasureGrid)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_GRID, OnUpdateMeasureGrid)
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
// CMKDoc construction/destruction

CMKDoc::CMKDoc() : m_meascount(0), m_delaycount(0),
	m_pps(MKGetApp()->m_pps), m_timer_id(0),
	m_kinetics(MKGetApp()->m_pps.m_meastime / 2)
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
	m_graph_smoothing = false;
	m_graph_nominal = true;
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

CMKDoc::~CMKDoc()
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
}


/////////////////////////////////////////////////////////////////////////////
// CMKDoc serialization

void CMKDoc::Serialize(CArchive& ar)
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
// CMKDoc diagnostics

#ifdef _DEBUG
void CMKDoc::AssertValid() const
{
	CProtocolDoc::AssertValid();
}

void CMKDoc::Dump(CDumpContext& dc) const
{
	CProtocolDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMKDoc commands

void CMKDoc::FB12NewRLU(long new_RLU)
{
	if ((GetMode() == MODE_MEASURING) &&
		(GetMode2() == MODE_SAMP) &&
		!m_door_wait)
	{
		// See if we need to record the time
		if ((m_rep_num == 0) && (m_kinetics.m_num_kinetics == 0))
		{
			// we record the time at the beginning of each sample
			m_samples[m_samp_num].m_measurements[m_meas_num].SetTime(
				((timeGetTime() - m_time_start) + 50) / 100);
			m_graph_hightime = m_samples[m_samp_num].m_measurements[m_meas_num].m_time;
		}

		if (m_delaycount == 0)
		{
			if (m_meascount > 0)
			{
				// Add this RLU event to the kinetics info
				m_kinetics.Add(new_RLU);
				m_meascount--;
				if (m_meascount == 0)
				{
					m_samples[m_samp_num].m_measurements[m_meas_num].SetReplicate(m_rep_num, m_kinetics.GetMean());
					SetModifiedFlag(TRUE);

					MeasurementEnd();
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
				MKGetApp()->m_pMainFrame->SetMessageText(IDS_MEASUREMESSAGE);
			}
		}
	}
}

void CMKDoc::FB12DoorChange(VARIANT_BOOL is_open)
{
	if (GetMode() == MODE_STOPPED)
	{
		// We're stopped
		if (!is_open)
		{
			// User wants us to start measuring
			MeasureStart();
		}
	}
	else if ((GetMode() == MODE_MEASURING) && (GetMode2() == MODE_SAMP))
	{
		if (!is_open && m_door_wait)
		{
			m_door_wait = false;
		}
		else if (is_open && !m_door_wait)
		{
			// Oops, door was opened during a measurement!
			m_delaycount = m_pps.m_delaytime / (10 / SAMPLES_PER_SEC);
			m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);
			m_door_wait = true;
			m_kinetics.Reset();
			if (SCMessageBox("The door was opened during a measurement.\n\nWould you like to skip this measurement?",
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				MeasurementEnd();
				UpdateAllViews(NULL);
			}
		}
	}
}

void CMKDoc::FB12OperatingChange(VARIANT_BOOL is_operating)
{

}

void CMKDoc::FB12ErrorChange(long new_error)
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

void CMKDoc::FB12CommunicatingChange(VARIANT_BOOL is_communicating)
{
	if (!is_communicating && (GetMode() == MODE_MEASURING))
	{
		MeasureEnd();
		SCMessageBox(IDS_FB12_TIMEOUT);
	}
}

void CMKDoc::SetMode(int mode)
{
	m_mode = mode;
}

int CMKDoc::GetMode() const
{
	return m_mode;
}

void CMKDoc::SetMode2(int mode)
{
	m_mode2 = mode;
}

int CMKDoc::GetMode2() const
{
	return m_mode2;
}

void CMKDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	// since document is going away, inhibit FB12 from talking to it
	MKGetApp()->FB12Inhibit();

	// Call base class
	CProtocolDoc::OnCloseDocument();

	// We are quitting the program
	AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CMKDoc::MeasurementStart()
{
	// Set the time when the next measurement should start
	m_time_end += m_pps.m_intervaltime * 100;

	// The delay and measurement counts are initialized
	m_delaycount = m_pps.m_delaytime / (10 / SAMPLES_PER_SEC);
	m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);

	m_samp_num = 0;
	m_rep_num = 0;

	// Reset the kinetics data
	m_kinetics.Reset();

	// Start the measurement (all samples and replicates)
	SetMode2(MODE_SAMP);
	m_door_wait = true;
	SetStatus();

	if (ProtGetApp()->m_beep)
	{
		MessageBeep(MB_OK);
	}
}

void CMKDoc::MeasurementEnd()
{
	if ((m_meas_num == (m_nummeas - 1)) &&
		(m_samp_num == (m_numsamps - 1)) &&
		(m_rep_num == (m_numreps - 1)))
	{
		// We're at the end of 
		MeasureEnd();
	}
	else
	{
		// Increment to the next sample to be measured, then update the screen
		UINT current_meas = m_meas_num;
		UINT current_samp = m_samp_num;
		UINT current_rep = m_rep_num;

		// Increment counters
		if (m_samp_num == (m_numsamps - 1))
		{
			if (m_rep_num == (m_numreps - 1))
			{
				m_meas_num++;
				m_rep_num = 0;
				m_samp_num = 0;
				SetMode2(MODE_WAIT);
			}
			else
			{
				m_rep_num++;
			}
		}
		else
		{
			if (m_rep_num == (m_numreps - 1))
			{
				m_samp_num++;
				m_rep_num = 0;
			}
			else
			{
				m_rep_num++;
			}
		}

		// Reset delaycount & meascount
		m_delaycount = m_pps.m_delaytime / (10 / SAMPLES_PER_SEC);
		m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);
		m_door_wait = true;
		m_kinetics.Reset();
		SetStatus();

		// Update the views
		CMKHint hint(current_meas, current_samp, current_rep);
		UpdateAllViews(NULL, 0, &hint);
		//UpdateAllViews(NULL, current_meas + 1);
	}
}

void CMKDoc::MeasureStart()
{
	m_timer_id = timeSetEvent(50, 50, TimerCallback, (DWORD)this, TIME_PERIODIC);
	if (m_timer_id != 0)
	{
		// Get the starting milliseconds
		m_time_start = m_time_end = timeGetTime();
		if ((0xffffffff - m_time_end) < (m_pps.m_intervaltime * 100))
		{
			SCMessageBox("The system timer is too high.\nYou must restart your computer or use the\n\"Use luminomter as time base\" option to take a measurement.");
		}
		else
		{
			m_time_end += m_pps.m_intervaltime * 100;

			// The delay and measurement counts are initialized
			m_delaycount = m_pps.m_delaytime / (10 / SAMPLES_PER_SEC);
			m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);

			m_samp_num = 0;
			m_rep_num = 0;

			// Reset the kinetics data
			m_kinetics.Reset();

			// Start the measurement (all samples and replicates)
			SetMode2(MODE_SAMP);

			// No wait for door on first sample
			m_door_wait = false;

			// Change the mode to start the measuring
			SetMode(MODE_MEASURING);

			SetStatus();
		}
	}
	else
	{
		SCMessageBox(_T("Unable to allocate timer."));
	}
}

void CMKDoc::MeasureEnd()
{
	// Change the mode
	SetMode(MODE_FINISHED);

	// Do the final grid update
	CMKHint hint(m_meas_num, m_samp_num, m_rep_num);
	UpdateAllViews(NULL, 0, &hint);
	//UpdateAllViews(NULL, m_meas_num + 1);
	//UpdateAllViews(NULL, -(int)current_replicate - 2);

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

	// Save the log file
	LogDocument();

	if ((m_meas_num == (m_nummeas - 1)) &&
		(m_samp_num == (m_numsamps - 1)) &&
		(m_rep_num == (m_numreps - 1)) &&
		m_pps.AutoSendToExcel())
	{
		((CMKView*)m_grid_view)->SendToExcel();
	}
}

void CMKDoc::InstanceTimerCallback(void)
{
	if ((GetMode() == MODE_MEASURING) &&
		(GetMode2() == MODE_WAIT) &&
		(timeGetTime() >= m_time_end))
	{
		MeasurementStart();
	}
}

void CALLBACK CMKDoc::TimerCallback(UINT uID, UINT, DWORD dwUser, DWORD, DWORD)
{
	((CMKDoc*)dwUser)->InstanceTimerCallback();
}

void CMKDoc::OnUpdateFileSaveAsText(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() != MODE_MEASURING) ? TRUE : FALSE);
}

void CMKDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	if (MKGetApp()->m_mode == CMKApp::APPMODE_RUN)
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

void CMKDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	// Init measurement counter to 0
	m_delaycount = 0;
	m_meascount = 0;
	if (m_timer_id != 0)
	{
		timeKillEvent(m_timer_id);
		m_timer_id = 0;
	}

	// Reset kinetics
	m_kinetics.Reset();

	// Reset the sample information
	m_samples.RemoveAll();
	m_numsamps = m_pps.m_numsamps;
	m_nummeas = m_pps.m_nummeasurements;
	m_numreps = m_pps.m_numreps;
	m_samples.SetSize(m_numsamps);
	UINT i, j;
	for (i = 0; i < m_numsamps; i++)
	{
		m_samples[i].m_measurements.SetSize(m_pps.m_nummeasurements);
		for (j = 0; j < m_nummeas; j++)
		{
			m_samples[i].m_measurements[j].m_replicates.SetSize(m_pps.m_numreps);
		}
	}

	m_graph_replicates.SetSize((m_pps.m_numreps + 1) * m_pps.m_numsamps);
	for (i = 0; i < ((m_pps.m_numreps + 1) * m_pps.m_numsamps); i++)
	{
		m_graph_replicates[i] = true;
	}

	// Call parent
	CProtocolDoc::DeleteContents();

	// Start out in stopped mode
	SetMode(MODE_STOPPED);

	// Setup the measurement, sample, and replicate counters
	m_samp_num = 0;
	m_meas_num = 0;
	m_rep_num = 0;

	// Gotta let the graph know there's no time
	m_graph_hightime = 0;

	SetModifiedFlag(FALSE);

	RemoveLog();

	SetStatus();
}

BOOL CMKDoc::LogDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;
	CFile file;
	if (file.Open(MKGetApp()->m_logpath, CFile::modeCreate | CFile::modeWrite))
	{
		if (SaveMDS(file))
		{
			ok = TRUE;
		}
		file.Close();
	}

	return ok;
}

void CMKDoc::RemoveLog()
{
	if (MKGetApp()->m_mode == CMKApp::APPMODE_RUN)
	{
		try
		{
			CFile::Remove(MKGetApp()->m_logpath);
		}
		catch(CFileException* e)
		{
			e->Delete();
		}
	}
}

BOOL CMKDoc::OnSaveDocument(LPCTSTR pathname)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;

	if (MKGetApp()->m_mode == CMKApp::APPMODE_RUN)
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

BOOL CMKDoc::OnOpenDocument(LPCTSTR pathname)
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

BOOL CMKDoc::SaveMDS(CFile& mds_file)
{
	try
	{
		mds_file.SeekToBegin();
		mds_file.SetLength(0);

		// Write the PPS data
		if (!MKGetApp()->m_pps.Write(mds_file))
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

		UINT meas, samp, rep;
		for (meas = 0; meas < m_nummeas; meas++)
		{
			for (samp = 0; samp < m_numsamps; samp++)
			{
				mds_file.Write(&m_samples[samp].m_measurements[meas].m_time,
					sizeof(m_samples[samp].m_measurements[meas].m_time));
				mds_file.Write(&m_samples[samp].m_measurements[meas].m_time_valid,
					sizeof(m_samples[samp].m_measurements[meas].m_time_valid));
				for (rep = 0; rep < m_numreps; rep++)
				{
					mds_file.Write(&m_samples[samp].m_measurements[meas]
						.m_replicates[rep].m_RLU, sizeof(m_samples[samp].m_measurements[meas]
						.m_replicates[rep].m_RLU));
					mds_file.Write(&m_samples[samp].m_measurements[meas]
						.m_replicates[rep].m_used, sizeof(m_samples[samp].m_measurements[meas]
						.m_replicates[rep].m_used));
				}
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


BOOL CMKDoc::LoadMDS(CFile& mds_file)
{
	try
	{
		// Read the PPS data
		if (!MKGetApp()->m_pps.Read(mds_file))
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

		UINT meas, samp, rep;
		CReplicate repl;
		for (meas = 0; meas < m_nummeas; meas++)
		{
			for (samp = 0; samp < m_numsamps; samp++)
			{
				DWORD time;
				bool time_valid;
				if ((mds_file.Read(&time, sizeof(time)) != sizeof(time)) ||
					(mds_file.Read(&time_valid, sizeof(time_valid)) != sizeof(time_valid)))
				{
					return FALSE;
				}
				m_samples[samp].m_measurements[meas].m_time = time;
				m_samples[samp].m_measurements[meas].m_time_valid = time_valid;
				if (time_valid)
				{
					m_graph_hightime = time;
				}
				for (rep = 0; rep < m_numreps; rep++)
				{
					if ((mds_file.Read(&repl.m_RLU, sizeof(repl.m_RLU)) != sizeof(repl.m_RLU)) ||
						(mds_file.Read(&repl.m_used, sizeof(repl.m_used)) != sizeof(repl.m_used)))
					{
						return FALSE;
					}
					m_samples[samp].m_measurements[meas].m_replicates[rep] = repl;
				}
				m_samples[samp].m_measurements[meas].Recalculate();
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

void CMKDoc::OnMeasureStop()
{
	// TODO: Add your command handler code here
	if ((MKGetApp()->m_mode == CMKApp::APPMODE_RUN) &&
		(GetMode() == MODE_MEASURING))
	{
		// User wants to stop...ask them if they really wanna
		if (SCMessageBox("Are you sure you would like to stop measuring?",
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			// Oops, user stopped the measurement
			MeasureEnd();
			//SCMessageBox("You stopped the measurement in progess.\n\nMeasurement aborted.");
		}
	}
}

void CMKDoc::OnUpdateMeasureStop(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_MEASURING) ? 0 : 1);
	pCmdUI->Enable((GetMode() == MODE_MEASURING) ? TRUE : FALSE);
}

void CMKDoc::OnMeasureKinetics()
{
	// TODO: Add your command handler code here
	ToggleKinetics();
}

void CMKDoc::OnUpdateMeasureKinetics(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_graph_view == NULL) ? 0 : 1);
}

void CMKDoc::OnUpdateMode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() != MODE_MEASURING) ? TRUE : FALSE);
}

void CMKDoc::SetStatus()
{
	// Change the status message
	CString status_str;

	if (MKGetApp()->m_mode == CMKApp::APPMODE_RUN)
	{
		if (GetMode() == MODE_STOPPED)
		{
			status_str.Format("Close luminometer door to begin measuring replicate 1 of sample 1.");
		}
		else if (GetMode() == MODE_FINISHED)
		{
			status_str = "No more measurements to be made.";
		}
		else
		{
			if (GetMode2() == MODE_WAIT)
			{
				status_str.Format("Waiting for interval time to expire to start new cycle.");
			}
			else
			{
				if (m_door_wait)
				{
					status_str.Format("Close luminometer door to measure replicate %ld of sample %ld.",
						m_rep_num + 1, m_samp_num + 1);
				}
				else
				{
					status_str.Format("Measuring...");
				}
			}
		}
	}
	else
	{
		status_str = "View and export data.";
	}

	MKGetApp()->m_pMainFrame->SetMessageText(status_str);
}

CString CMKDoc::GetReplicateString(UINT sample, UINT replicate)
{
	CString rep_str;

	if (sample < m_numsamps)
	{
		rep_str.Format("measurement %ld for replicate %ld",
			sample, replicate + 1);
	}
	else
	{
		rep_str = "none";
	}

	return rep_str;
}

void CMKDoc::SetModifiedFlag(BOOL bModified)
{
	CProtocolDoc::SetModifiedFlag(
		(MKGetApp()->m_mode == CMKApp::APPMODE_VIEW) ? FALSE : bModified);
}

CString CMKDoc::GetTimerText()
{
	CString txt;

	if (GetMode() == MODE_MEASURING)
	{
		if (GetMode2() == MODE_WAIT)
		{
			long diff_time = m_time_end - timeGetTime();
			if (diff_time > 0)
			{
				diff_time = (diff_time + 50) / 100;
				txt.Format("I %s", SCFormatDeciseconds(diff_time));
			}
		}
		else
		{
			if (m_door_wait)
			{
				txt.Format("Door Wait");
			}
			else if (m_delaycount > 0)
			{
				txt.Format("D %s", (LPCTSTR)SCFormatDeciseconds(m_delaycount * (10 / SAMPLES_PER_SEC)));
			}
			else if (m_meascount > 0)
			{
				txt.Format("M %s", (LPCTSTR)SCFormatDeciseconds(m_meascount * (10 / SAMPLES_PER_SEC)));
			}
		}
	}

	return txt;
}

CString CMKDoc::GetCounterText()
{
	CString txt;

	if (GetMode() == MODE_MEASURING)
	{
		txt.Format("%s", (LPCTSTR)SCFormatDeciseconds(
			((timeGetTime() - m_time_start) + 50) / 100));
	}

	return txt;
}

void CMKDoc::OnMeasureGrid()
{
	// TODO: Add your command handler code here
	ToggleGrid();
}

void CMKDoc::OnUpdateMeasureGrid(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_grid_view == NULL) ? 0 : 1);
}
