// DADoc.cpp : implementation of the CDADoc class
//

#include "stdafx.h"
#include "DA.h"
#include "MainFrm.h"
#include "General.h"
#include "DAView.h"

#include "DADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDADoc

IMPLEMENT_DYNCREATE(CDADoc, CProtocolDoc)

BEGIN_MESSAGE_MAP(CDADoc, CProtocolDoc)
	//{{AFX_MSG_MAP(CDADoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_TEXT, OnUpdateFileSaveAsText)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_MEASURE_DELETE, OnMeasureDelete)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_DELETE, OnUpdateMeasureDelete)
	ON_COMMAND(ID_MEASURE_START, OnMeasureStart)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_START, OnUpdateMeasureStart)
	ON_COMMAND(ID_MEASURE_STOP, OnMeasureStop)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_STOP, OnUpdateMeasureStop)
	ON_COMMAND(ID_MEASURE_KINETICS, OnMeasureKinetics)
	ON_UPDATE_COMMAND_UI(ID_MEASURE_KINETICS, OnUpdateMeasureKinetics)
	ON_COMMAND(ID_FILE_SAVE_KINETICS_AS_TEXT, OnFileSaveKineticsAsText)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_KINETICS_AS_TEXT, OnUpdateFileSaveKineticsAsText)
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
// CDADoc construction/destruction

CDADoc::CDADoc() : m_meascount(0), m_delaycount(0),
	m_pps(DAGetApp()->m_pps),
	m_kinetics((DAGetApp()->m_pps.m_meastime_a > DAGetApp()->m_pps.m_meastime_b) ?
		DAGetApp()->m_pps.m_meastime_a / 2 :
		DAGetApp()->m_pps.m_meastime_b / 2)
{
	// TODO: add one-time construction code here
	// Get the current date and time
	time_t sys_time;
	time(&sys_time);
	CTime now(sys_time);
	m_datetime = now;
}

CDADoc::~CDADoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CDADoc serialization

void CDADoc::Serialize(CArchive& ar)
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
// CDADoc diagnostics

#ifdef _DEBUG
void CDADoc::AssertValid() const
{
	CProtocolDoc::AssertValid();
}

void CDADoc::Dump(CDumpContext& dc) const
{
	CProtocolDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDADoc commands

void CDADoc::FB12NewRLU(long new_RLU)
{
	if (GetMode() == MODE_MEASURING)
	{
		// Add this RLU event to the kinetics info
		if (m_delaycount == 0)
		{
			if (m_meascount > 0)
			{
				m_kinetics.Add(new_RLU);
				UpdateAllViews(NULL, -1);
				m_meascount--;
				if (m_meascount == 0)
				{
					m_samples[m_sample_num].SetReplicate(m_series, m_replicate_num, m_kinetics.GetMean());
					SetModifiedFlag(TRUE);
					MeasureEnd();
					if (ProtGetApp())
					{
						MessageBeep(MB_OK);
					}

					m_sample_num_prev = m_sample_num;
					m_replicate_num_prev = m_replicate_num;
					m_series_prev = m_series;
					m_has_deleted = false;

					// Store this sample for the update below
					int update_sample = m_sample_num;

					// Increment to the next replicate to be measured
					Increment();

					UpdateAllViews(NULL, update_sample + 1);
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
				DAGetApp()->m_pMainFrame->SetMessageText(IDS_MEASUREMESSAGE);
			}
		}
	}
}

void CDADoc::FB12DoorChange(VARIANT_BOOL is_open)
{
	if (GetMode() == MODE_MEASURING)
	{
		// We're measuring a replicate
		if (is_open)
		{
			// Oops, door was opened during a measurement!
			MeasureEnd();
			if (SCMessageBox("The door was opened during a measurement.\n\nWould you like to skip this measurement?",
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				Increment();
				UpdateAllViews(NULL);
			}
		}
		//else
		//{
		//	// Hmmm, door closed during measurement; weird
		//}
	}
	else
	{
		// We're stopped
		if (!is_open)
		{
			if (m_pps.UseStartButton())
			{
				// This is okay, user will click start button soon
			}
			else
			{
				// User wants us to start measuring
				MeasureStart(true);	// start measuring with delay
			}
		}
		//else
		//{
		//	// This is okay, user just opened door to change a tube
		//}
	}
}

void CDADoc::FB12OperatingChange(VARIANT_BOOL is_operating)
{

}

void CDADoc::FB12ErrorChange(long new_error)
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

void CDADoc::FB12CommunicatingChange(VARIANT_BOOL is_communicating)
{
	if (!is_communicating && (GetMode() == MODE_MEASURING))
	{
		MeasureEnd();
		SCMessageBox(IDS_FB12_TIMEOUT);
	}
}

void CDADoc::SetMode(int mode)
{
	m_mode = mode;
}

int CDADoc::GetMode() const
{
	return m_mode;
}

void CDADoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	// since document is going away, inhibit FB12 from talking to it
	DAGetApp()->FB12Inhibit();

	// Call base class
	CProtocolDoc::OnCloseDocument();

	// We are quitting the program
	AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CDADoc::MeasureStart(bool delay)
{
	if (m_sample_num < m_numsamples)
	{
		// The delay and measurement counts are initialized
		if (m_series == CSample::SERIES_A)
		{
			m_delaycount = delay ? (m_pps.m_delaytime_a / (10 / SAMPLES_PER_SEC)) : 0;
			m_meascount = m_pps.m_meastime_a / (10 / SAMPLES_PER_SEC);
		}
		else
		{
			m_delaycount = delay ? (m_pps.m_delaytime_b / (10 / SAMPLES_PER_SEC)) : 0;
			m_meascount = m_pps.m_meastime_b / (10 / SAMPLES_PER_SEC);
		}

		// Start a new set of kinetics
		m_kinetics.Reset();

		// Set the statusbar text
		DAGetApp()->m_pMainFrame->SetMessageText(
			(m_delaycount == 0) ? IDS_MEASUREMESSAGE : IDS_DELAYMESSAGE);

		// Change the mode
		SetMode(MODE_MEASURING);
	}
	else
	{
		SCMessageBox("There are no more samples to measure.");
	}
}

void CDADoc::MeasureEnd()
{
	// Reset the counters
	m_delaycount = 0;
	m_meascount = 0;

	// Set the statusbar text
	SetStatus();

	// Change the mode
	SetMode(MODE_STOPPED);

	// Save the log file
	LogDocument();

	if ((m_series == CSample::SERIES_B) &&
		(m_sample_num == (m_numsamples - 1)) &&
		(m_replicate_num == (m_pps.m_numreplicates - 1)) &&
		m_pps.AutoSendToExcel())
	{
		UpdateAllViews(NULL);
		((CDAView*)m_grid_view)->SendToExcel();
	}
}

void CDADoc::OnUpdateFileSaveAsText(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable((GetMode() == MODE_STOPPED) && IsModified());
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}

void CDADoc::OnFileNew()
{
	// TODO: Add your command handler code here
	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
 		// Ensure that each views current cell is stored
 		CGXGridHint hint(gxHintTransferCurrentCell);
 		hint.lParam = TRUE;

 		UpdateAllViews(NULL, 0, &hint);
		if (SaveModified())
		{
			if (OnNewDocument())
			{
				m_pps.Load(DAGetApp()->m_filetitle);

				// Set the empty sample names to "Sample N"
				m_pps.FillEmptySamples();

				UpdateAllViews(NULL);
			}
		}
}
}

void CDADoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	// Init measurement counter to 0
	m_delaycount = 0;
	m_meascount = 0;

	// Reset kinetics
	m_kinetics.Reset();

	// Reset the sample information
	m_samples.RemoveAll();
	m_numsamples = m_pps.m_numsamples + (m_pps.UseBackground() ? 1 : 0);
	m_samples.SetSize(m_numsamples);
	UINT i;
	for (i = 0; i < m_numsamples; i++)
	{
		m_samples[i].m_replicates_a.SetSize(m_pps.m_numreplicates);
		m_samples[i].m_replicates_b.SetSize(m_pps.m_numreplicates);
	}

	// Default to not allowing a "delete last measurement"
	m_has_deleted = true;

	// Call parent
	CProtocolDoc::DeleteContents();

	// Start out in stopped mode
	SetMode(MODE_STOPPED);

	// Setup the series, sample, and replicate counter
	m_series = CSample::SERIES_A;
	m_sample_num = 0;
	m_replicate_num = 0;

	SetModifiedFlag(FALSE);

	RemoveLog();

	SetStatus();
}

BOOL CDADoc::LogDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;
	CFile file;
	if (file.Open(DAGetApp()->m_logpath, CFile::modeCreate | CFile::modeWrite))
	{
		if (SaveMDS(file))
		{
			ok = TRUE;
		}
		file.Close();
	}

	return ok;
}

void CDADoc::RemoveLog()
{
	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		try
		{
			CFile::Remove(DAGetApp()->m_logpath);
		}
		catch(CFileException* e)
		{
			e->Delete();
		}
	}
}

BOOL CDADoc::OnSaveDocument(LPCTSTR pathname)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;

	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		// Ensures that any cell currently being edited is stored
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

BOOL CDADoc::OnOpenDocument(LPCTSTR pathname)
{
	//if (!CProtocolDoc::OnOpenDocument(lpszPathName))
	//	return FALSE;

	//CString curdir = SCGetCurrentDir();

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

	//return TRUE;
}

BOOL CDADoc::SaveMDS(CFile& mds_file)
{
	try
	{
		mds_file.SeekToBegin();
		mds_file.SetLength(0);

		// Write the PPS data
		if (!DAGetApp()->m_pps.Write(mds_file))
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
		mds_file.Write(&CSample::m_normalize_value, sizeof(CSample::m_normalize_value));
		mds_file.Write(&CSample::m_background_a, sizeof(CSample::m_background_a));
		mds_file.Write(&CSample::m_background_b, sizeof(CSample::m_background_b));

		UINT i, rep;
		for (i = 0; i < m_numsamples; i++)
		{
			for (rep = 0; rep < m_pps.m_numreplicates; rep++)
			{
				// Series A
				mds_file.Write(&m_samples[i].m_replicates_a[rep].m_RLU, sizeof(m_samples[i].m_replicates_a[rep].m_RLU));
				mds_file.Write(&m_samples[i].m_replicates_a[rep].m_used, sizeof(m_samples[i].m_replicates_a[rep].m_used));

				// Series B
				mds_file.Write(&m_samples[i].m_replicates_b[rep].m_RLU, sizeof(m_samples[i].m_replicates_b[rep].m_RLU));
				mds_file.Write(&m_samples[i].m_replicates_b[rep].m_used, sizeof(m_samples[i].m_replicates_b[rep].m_used));
			}
		}

		//LPTSTR sample_name[CDAPPS::SAMPLENAME_SIZE];
		/*
		for (i = 0; i < m_pps.m_numsamples; i++)
		{
			//strcpy(sample_name, m_sample_names[i]);
			//mds_file.Write(sample_name, strlen(sample_name) + 1);
			mds_file.Write((LPCTSTR)m_sample_names[i],
				m_sample_names[i].GetLength() + 1);
		}
		*/
	}
	catch (CFileException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}


BOOL CDADoc::LoadMDS(CFile& mds_file)
{
	try
	{
		// Read the PPS data
		if (!DAGetApp()->m_pps.Read(mds_file))
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
			(mds_file.Read(&CSample::m_normalize_value, sizeof(CSample::m_normalize_value)) != sizeof(CSample::m_normalize_value)) ||
			(mds_file.Read(&CSample::m_background_a, sizeof(CSample::m_background_a)) != sizeof(CSample::m_background_a)) ||
			(mds_file.Read(&CSample::m_background_b, sizeof(CSample::m_background_b)) != sizeof(CSample::m_background_b)))
		{
			return FALSE;
		}
		CTime time(year, month, day, hour, minute, second);
		m_datetime = time;

		// The following call will resize the m_samples[] and
		// m_sample_names[] arrays for me
		DeleteContents();

		UINT i, rep;
		CReplicate rep_a, rep_b;
		for (i = 0; i < m_numsamples; i++)
		{
			for (rep = 0; rep < m_pps.m_numreplicates; rep++)
			{
				if ((mds_file.Read(&rep_a.m_RLU, sizeof(rep_a.m_RLU)) != sizeof(rep_a.m_RLU)) ||
					(mds_file.Read(&rep_a.m_used, sizeof(rep_a.m_used)) != sizeof(rep_a.m_used)) ||
					(mds_file.Read(&rep_b.m_RLU, sizeof(rep_b.m_RLU)) != sizeof(rep_b.m_RLU)) ||
					(mds_file.Read(&rep_b.m_used, sizeof(rep_b.m_used)) != sizeof(rep_b.m_used)))
				{
					return FALSE;
				}
				m_samples[i].m_replicates_a[rep] = rep_a;
				m_samples[i].m_replicates_b[rep] = rep_b;
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

void CDADoc::OnMeasureDelete()
{
	// TODO: Add your command handler code here
	if ((DAGetApp()->m_mode == CDAApp::APPMODE_RUN) && (!m_has_deleted))
	{
		CString rep_str;
		rep_str = GetReplicateString(m_series_prev, m_sample_num_prev, m_replicate_num_prev);
		CString msg_str;
		msg_str.Format(
			"Are you sure you want to delete the last\nmeasurement (%s)?",
			rep_str);
		if (SCMessageBox(msg_str, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_samples[m_sample_num_prev].ClearReplicate(m_series_prev, m_replicate_num_prev);
			m_has_deleted = true;
			UpdateAllViews(NULL, m_sample_num_prev + 1);

			msg_str.Format(
				"Last measurement deleted.\n\nWould you like to re-measure %s?",
				rep_str);
			if (SCMessageBox(msg_str, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				m_sample_num = m_sample_num_prev;
				m_replicate_num = m_replicate_num_prev;
				m_series = m_series_prev;
				SetStatus();
				UpdateAllViews(NULL, m_sample_num_prev + 1);
			}
		}
	}
}

void CDADoc::OnUpdateMeasureDelete(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((GetMode() == MODE_STOPPED) && !m_has_deleted) ? TRUE : FALSE);
}

void CDADoc::OnMeasureStart()
{
	// TODO: Add your command handler code here
	if ((DAGetApp()->m_mode == CDAApp::APPMODE_RUN) &&
		(GetMode() == MODE_STOPPED))
	{
		if (DAGetApp()->m_pFB12Device->get_dooropen())
		{
			SCMessageBox(_T("The door is open.  Close the door and try again."));
		}
		else if (!DAGetApp()->m_pFB12Device->get_communicating())
		{
			SCMessageBox(_T("The instrument is not communicating.\nCheck the cabling and serial parameters and try again."));
		}
		else
		{
			MeasureStart(false);  // start measuring with no delay
		}
	}
}

void CDADoc::OnUpdateMeasureStart(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
	pCmdUI->Enable((m_pps.UseStartButton() && (m_sample_num < m_numsamples) &&
		(GetMode() == MODE_STOPPED)) ? TRUE : FALSE);
}

void CDADoc::OnMeasureStop()
{
	// TODO: Add your command handler code here
	if ((DAGetApp()->m_mode == CDAApp::APPMODE_RUN) &&
		(GetMode() == MODE_MEASURING))
	{
		// Oops, user stopped the measurement
		MeasureEnd();
		if (SCMessageBox("You stopped the measurement in progess!\n\nWould you like to skip this measurement?",
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Increment();
			UpdateAllViews(NULL);
		}
	}
}

void CDADoc::OnUpdateMeasureStop(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 1 : 0);
	pCmdUI->Enable(((m_sample_num < m_numsamples) &&
		(GetMode() != MODE_STOPPED)) ? TRUE : FALSE);
}

void CDADoc::OnMeasureGrid()
{
	// TODO: Add your command handler code here
	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		ToggleGrid();
	}
}

void CDADoc::OnUpdateMeasureGrid(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_grid_view == NULL) ? 0 : 1);
}

void CDADoc::OnMeasureKinetics()
{
	// TODO: Add your command handler code here
	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		ToggleKinetics();
		if (m_graph_view)
		{
			((CKineticsView*)m_graph_view)->SetKinetics(m_kinetics,
				((m_pps.m_meastime_a > m_pps.m_meastime_b) ?
				m_pps.m_meastime_a : m_pps.m_meastime_b) /
				(10 / SAMPLES_PER_SEC));
		}
	}
}

void CDADoc::OnUpdateMeasureKinetics(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_graph_view == NULL) ? 0 : 1);
}

void CDADoc::OnUpdateMode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}

void CDADoc::Increment()
{
	if (m_pps.m_order == CDAPPS::ORDER_ABAB)
	{
		if (m_series == CSample::SERIES_B)
		{
			m_series = CSample::SERIES_A;
			if (m_replicate_num == (m_pps.m_numreplicates - 1))
			{
				m_sample_num++;
				m_replicate_num = 0;
			}
			else
			{
				m_replicate_num++;
			}
		}
		else
		{
			m_series = CSample::SERIES_B;
		}
	}
	else
	{
		if (m_series == CSample::SERIES_B)
		{
			if (m_replicate_num == (m_pps.m_numreplicates - 1))
			{
				m_replicate_num = 0;
				m_sample_num++;
			}
			else
			{
				m_replicate_num++;
			}
		}
		else
		{
			if (m_replicate_num == (m_pps.m_numreplicates - 1))
			{
				m_replicate_num = 0;
				if (m_sample_num == (m_numsamples - 1))
				{
					m_series = CSample::SERIES_B;
					m_sample_num = 0;
				}
				else
				{
					m_sample_num++;
				}
			}
			else
			{
				m_replicate_num++;
			}
		}
	}

	SetStatus();
}

void CDADoc::SetStatus()
{
	// Change the status message
	CString status_str;

	if (DAGetApp()->m_mode == CDAApp::APPMODE_RUN)
	{
		if (m_sample_num < m_numsamples)
		{
			CString rep_str = GetReplicateString(m_series, m_sample_num, m_replicate_num);
			if (m_pps.UseStartButton())
			{
				status_str.Format("Press start button or space bar or enter key to measure %s.", rep_str);
			}
			else
			{
				status_str.Format("Close luminometer door to measure %s.", rep_str);
			}
		}
		else
		{
			status_str = "No more samples to measure.";
		}
	}
	else
	{
		status_str = "View or export data.";
	}

	DAGetApp()->m_pMainFrame->SetMessageText(status_str);
}

CString CDADoc::GetReplicateString(int series, UINT sample, UINT replicate)
{
	CString rep_str;

	if (sample < m_numsamples)
	{
		if ((sample == 0) && m_pps.UseBackground())
		{
			rep_str.Format("replicate %d of background, series %c",
				replicate + 1, (series == CSample::SERIES_A) ? 'A' : 'B');
		}
		else
		{
			rep_str.Format("replicate %d for sample \"%s\", series %c",
				replicate + 1, m_pps.m_samplelist[sample -
				(m_pps.UseBackground() ? 1 : 0)],
				(series == CSample::SERIES_A) ? 'A' : 'B');
		}
	}
	else
	{
		rep_str = "none";
	}

	return rep_str;
}

void CDADoc::SetModifiedFlag(BOOL bModified)
{
	CProtocolDoc::SetModifiedFlag(
		(DAGetApp()->m_mode == CDAApp::APPMODE_VIEW) ? FALSE : bModified);
}

void CDADoc::OnFileSaveKineticsAsText()
{
	// TODO: Add your command handler code here
	m_kinetics.SaveAsText();
}

void CDADoc::OnUpdateFileSaveKineticsAsText(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_kinetics.m_num_kinetics == 0) ? FALSE : TRUE);
}
