// CADoc.cpp : implementation of the CCADoc class
//

#include "stdafx.h"
#include "CA.h"
#include "MainFrm.h"
#include "CAView.h"

#include "General.h"
#include "CADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCADoc

IMPLEMENT_DYNCREATE(CCADoc, CProtocolDoc)

BEGIN_MESSAGE_MAP(CCADoc, CProtocolDoc)
	//{{AFX_MSG_MAP(CCADoc)
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
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_TEXT, OnUpdateFileSaveAsText)
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
// CCADoc construction/destruction

CCADoc::CCADoc() : m_meascount(0), m_delaycount(0),
	m_pps(CAGetApp()->m_pps), m_validassay(true),
	m_kinetics(CAGetApp()->m_pps.m_meastime / 2)
{
}

CCADoc::~CCADoc()
{

}




/////////////////////////////////////////////////////////////////////////////
// CCADoc serialization

void CCADoc::Serialize(CArchive& ar)
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
// CCADoc diagnostics

#ifdef _DEBUG
void CCADoc::AssertValid() const
{
	CProtocolDoc::AssertValid();
}

void CCADoc::Dump(CDumpContext& dc) const
{
	CProtocolDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCADoc commands

void CCADoc::FB12NewRLU(long new_RLU)
{
	if (GetMode() == MODE_MEASURING)
	{
		if (!CAGetApp()->m_pFB12Device->get_dooropen())
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
						m_samples[m_sample_num - 1].SetReplicate(m_replicate_num - 1, m_kinetics.GetMean());
						if (((m_negsample > 0) && (m_sample_num == m_negsample)) || 
							((m_possample > 0) && (m_sample_num == m_possample)))
							RecalcCutoffs();
						SetModifiedFlag(TRUE);
						m_last_sample = m_sample_num;
						m_last_replicate = m_replicate_num;
						m_any_deleted = false;
						MeasureEnd();
						if (ProtGetApp()->m_beep)
						{
							MessageBeep(MB_OK);
						}
						GetNext(m_replicate_num, m_sample_num);
						SetStatus();

						UpdateAllViews(NULL, m_last_sample);

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
					CAGetApp()->m_pMainFrame->SetMessageText(IDS_MEASUREMESSAGE);
				}
			}
		}
	}
}

void CCADoc::FB12DoorChange(VARIANT_BOOL is_open)
{
	if ((GetMode() == MODE_MEASURING) && (is_open))
	{
		if ((m_delaycount > 0) || (m_meascount > 0))
		{
			MeasureEnd();
			SCMessageBox(IDS_FB12_DOOROPENED);
		}
	}
	else if (GetMode() == MODE_STOPPED)
	{
		// Stopped
		if ((!is_open) && (!m_pps.UseStartButton()))
		{
			// The door was closed

			if (!MoreToMeasure())
			{
				SCMessageBox("There are no more measurements to be made.");
			}
			else
			{
				MeasureStart(true);	// measure with delay
			}
		}


	}

}

void CCADoc::FB12OperatingChange(VARIANT_BOOL is_operating)
{

}

void CCADoc::FB12ErrorChange(long new_error)
{
	if (GetMode() == MODE_MEASURING)
	{

		if ((m_delaycount > 0) || (m_meascount > 0))
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

}

void CCADoc::FB12CommunicatingChange(VARIANT_BOOL is_communicating)
{
	if (!is_communicating && (GetMode() == MODE_MEASURING))
	{
		MeasureEnd();
		SCMessageBox(IDS_FB12_TIMEOUT);
	}
}

void CCADoc::SetMode(int mode)
{
	m_mode = mode;
}


int CCADoc::GetMode() const
{
	return m_mode;
}


void CCADoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class

	// since document is going away, inhibit FB12 from talking to it
	CAGetApp()->FB12Inhibit();

	// Call base class
	CProtocolDoc::OnCloseDocument();

	// We are quitting the program
	AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CCADoc::MeasureStart(bool delay)
{
	// The delay and measurement counts are initialized
	m_delaycount = (delay) ? (m_pps.m_delaytime / (10 / SAMPLES_PER_SEC)) : 0;
	m_meascount = m_pps.m_meastime / (10 / SAMPLES_PER_SEC);
			

	// Start a new set of kinetics
	m_kinetics.Reset();

	// Set the statusbar text
	CAGetApp()->m_pMainFrame->SetMessageText(
		(m_delaycount == 0) ? IDS_MEASUREMESSAGE : IDS_DELAYMESSAGE);

	SetMode(MODE_MEASURING);

}

void CCADoc::MeasureEnd()
{
	// Reset the counters
	m_delaycount = 0;
	m_meascount = 0;

	// Set the statusbar text
	SetStatus();

	//Save the log file
	LogDocument();
	
	SetMode(MODE_STOPPED);
	UpdateAllViews(NULL);

	if ((m_sample_num == m_numsamples) &&
		(m_replicate_num == m_pps.m_numreps) &&
		m_pps.AutoSendToExcel())
	{
		((CCAView*)m_grid_view)->SendToExcel();
	}
}



void CCADoc::OnFileNew() 
{
 	// Ensure that each views current cell is stored
	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
 		CGXGridHint hint(gxHintTransferCurrentCell);
 		hint.lParam = TRUE;
 
 		UpdateAllViews(NULL, 0, &hint);

		// TODO: Add your command handler code here
		if (SaveModified())
		{
			m_pps.Load(CAGetApp()->m_filetitle);

			// Set the empty sample names to "Sample N"
			m_pps.FillEmptySamples();

			if (OnNewDocument())
			{
				UpdateAllViews(NULL);
			}
		}
	}
}


void CCADoc::DeleteContents()
{
	//TODO: Add your specialized code here and/or call the base class
	m_delaycount = 0;
	m_meascount = 0;

	time_t sys_time;
	time(&sys_time);
	CTime now(sys_time);
	m_datetime = now;

	CSample::m_lowcutoff = 0;
	CSample::m_highcutoff = 0;

	//m_RLUs.RemoveAll();
	m_kinetics.Reset();

	// Reset the sample information
	m_samples.RemoveAll();


	m_numsamples = m_pps.m_numsamps;
	if (m_pps.UseBackground())
	{
		m_numsamples++; // Add 1 for the background
		if (m_pps.m_numnegreps == 0)  // No negative control
		{
			m_negsample = 0;  
			m_possample = 2;  // Pos. control row is 2
		}
		else  // There is a negative control
		{
			m_negsample = 2;  // Bkgrd row 1, neg. cntrl 2, pos. control 3
			m_possample = 3;
			m_numsamples++;  // Add 1 for the neg. cntrl
		}
		if (m_pps.m_numposreps == 0)  // No positive control
		{
			m_possample = 0;
		}
		else
		{
			m_numsamples++;  // Add 1 for the pos. cntrl
		}
	}
	else
	{
		if (m_pps.m_numnegreps == 0)   // No negative control
		{
			m_negsample = 0;
			m_possample = 1;
		}
		else  // There is a negative control
		{
			m_negsample = 1;
			m_possample = 2;
			m_numsamples++; // add 1 for neg. cntrl
		}
		if (m_pps.m_numposreps == 0)  // No positive control
		{
			m_possample = 0;
		}
		else  // There is a positive control
		{
			m_numsamples++; // Add 1 for pos. cntrl.
		}

	}

	m_maxreps = m_pps.m_numreps;
	if (m_pps.m_numposreps > m_maxreps)
		m_maxreps = m_pps.m_numposreps;
	if (m_pps.m_numnegreps > m_maxreps)
		m_maxreps = m_pps.m_numnegreps;

	m_samples.SetSize(m_numsamples);

	for (UINT i = 0; i < m_numsamples; i++)
	{
		if ((m_negsample > 0) && (i == (m_negsample-1)))
		{
			m_samples[i].m_replicates.SetSize(m_pps.m_numnegreps);
			m_samples[i].m_result = CSample::RESULT_NEGSTD;
		}
		else if ((m_possample > 0) && (i == (m_possample-1)))
		{
			m_samples[i].m_replicates.SetSize(m_pps.m_numposreps);
			m_samples[i].m_result = CSample::RESULT_POSCTRL;
		}
		else
		{
			m_samples[i].m_replicates.SetSize(m_pps.m_numreps);
			if ((i == 0) && (m_pps.UseBackground()))
				m_samples[i].m_result = CSample::RESULT_BKGD;
		}
	}

	if ((m_negsample == 0) && (m_possample == 0))
		RecalcCutoffs();

	m_sample_num = 1;
	m_replicate_num = 1;
	m_last_sample = 0;
	m_last_replicate = 0;

	CProtocolDoc::DeleteContents();

	// Start out in stopped mode
	SetMode(MODE_STOPPED);

	SetModifiedFlag(FALSE);

	RemoveLog();
	SetStatus();
}

BOOL CCADoc::LogDocument()
{
	// TODO:  Add your specialized code here and/or call the base class
	BOOL ok = FALSE;
	CFile file;
	if(file.Open(CAGetApp()->m_logpath, CFile::modeCreate | 
		CFile::modeWrite))
	{
		if (SaveMDS(file))
		{
			ok = TRUE;
		}
		file.Close();
	}

	return ok;
}


void CCADoc::RemoveLog()
{
	try
	{
		CFile::Remove(CAGetApp()->m_logpath);
	}
	catch (CFileException* e)
	{
		e->Delete();
	}
}

BOOL CCADoc::OnSaveDocument(LPCTSTR pathname)
{
	// TODO:  Add your specialized code here and/or call the base class
	BOOL ok = FALSE;

	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
 		// Ensure that each views current cell is stored
 		CGXGridHint hint(gxHintTransferCurrentCell);
 		hint.lParam = TRUE;
 
 		UpdateAllViews(NULL, 0, &hint);

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
}

BOOL CCADoc::OnOpenDocument(LPCTSTR pathname) 
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
	
	//return TRUE;
}

BOOL CCADoc::SaveMDS(CFile& mds_file) 
{
	try
	{
		mds_file.SeekToBegin();
		mds_file.SetLength(0);

		// Write the PPS data
		if (!CAGetApp()->m_pps.Write(mds_file))
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

		UINT i, rep, num_reps;
		for (i = 0; i < m_numsamples; i++)
		{
			if ((m_negsample > 0) && (i == (m_negsample - 1)))
				num_reps = m_pps.m_numnegreps;
			else if ((m_possample > 0) && (i == (m_possample - 1)))
				num_reps = m_pps.m_numposreps;
			else
				num_reps = m_pps.m_numreps;
			for (rep = 0; rep < num_reps; rep++)
			{
				mds_file.Write(&m_samples[i].m_replicates[rep].m_RLU, sizeof(m_samples[i].m_replicates[rep].m_RLU));
				mds_file.Write(&m_samples[i].m_replicates[rep].m_used, sizeof(m_samples[i].m_replicates[rep].m_used));
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


BOOL CCADoc::LoadMDS(CFile& mds_file) 
{
	try
	{
		// Read the PPS data
		if (!CAGetApp()->m_pps.Read(mds_file))
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
		// m_sample_names[] arrays for me.  Also, if there are
		// no positive nor negative controls, this will Calculate
		// the cut-off values.
		DeleteContents();

		CReplicate replicate;
		UINT i, rep, num_reps;


		for (i = 0; i < m_numsamples; i++)
		{
			if ((m_negsample > 0) && (i == (m_negsample - 1)))
				num_reps = m_pps.m_numnegreps;
			else if ((m_possample > 0) && (i == (m_possample - 1)))
				num_reps = m_pps.m_numposreps;
			else
				num_reps = m_pps.m_numreps;

			for (rep = 0; rep < num_reps; rep++)			
			{
				if ((mds_file.Read(&replicate.m_RLU, sizeof(replicate.m_RLU)) != sizeof(replicate.m_RLU)) ||
					(mds_file.Read(&replicate.m_used, sizeof(replicate.m_used)) != sizeof(replicate.m_used)))
				{
					return FALSE;
				}
				m_samples[i].m_replicates[rep] = replicate;
			}
			m_samples[i].Recalculate();
			// After Neg and Pos controls calculated, calculate cut-offs for the
			// the analyte samples.
			if (m_possample > 0)        // There is a positive control
			{
				if (i == (m_possample - 1))
					RecalcCutoffs();
			}
			else if (m_negsample > 0)   // No positive control, but there is a neg. cntrl
			{
				if (i == (m_negsample - 1))
					RecalcCutoffs();
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


BOOL  CCADoc::GetNext(UINT& rep, UINT& samp)
{
	UINT num_reps;

	if ((m_negsample > 0) && (samp == m_negsample))
		num_reps = m_pps.m_numnegreps;
	else if ((m_possample > 0) && (samp == m_possample))
		num_reps = m_pps.m_numposreps;
	else
		num_reps = m_pps.m_numreps;

	if (rep == num_reps)
	{
		rep = 1;
		samp++;
	}
	else 
	{
		rep++;
	}
	return TRUE;
}


void CCADoc::OnMeasureDelete() 
{
	// TODO: Add your command handler code here
	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
		if ((m_last_sample == 0) || (m_last_replicate == 0)) 
		{
			SCMessageBox("No previous measurement to delete.");
		}
		else
		{
			CString msg, rep_str;
			rep_str = GetReplicateString(m_last_sample, m_last_replicate);
			msg.Format(
				"Are you sure you want to delete the last\nmeasurement (%s)?", 
				rep_str);
			if (SCMessageBox(msg, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				m_samples[m_last_sample - 1].ClearReplicate(m_last_replicate-1);
				if (((m_negsample > 0) && (m_last_sample == m_negsample)) || 
					((m_possample > 0) && (m_last_sample == m_possample)))
					RecalcCutoffs();
				m_any_deleted = true;
				UpdateAllViews(NULL, m_last_sample);

				msg.Format(
					"Last measurement deleted.\n\nWould you like to re-measure %s?",
					rep_str);

				if (SCMessageBox(msg, MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					m_sample_num = m_last_sample;
					m_replicate_num = m_last_replicate;
					SetStatus();
					UpdateAllViews(NULL, m_last_sample);
				}
			}
		}
	}
}


void CCADoc::OnUpdateMeasureDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((GetMode() == MODE_STOPPED) && !m_any_deleted) ? TRUE : FALSE);
}


void CCADoc::OnMeasureStart()
{
	// Start measuring inits
	if ((CAGetApp()->m_mode == CCAApp::APPMODE_RUN) &&
		(GetMode() == MODE_STOPPED))
	{
		MeasureStart(false);	//  measure with no delay
	}	
}

void CCADoc::OnUpdateMeasureStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 0 : 1);
	pCmdUI->Enable((m_pps.UseStartButton()) && (GetMode() == MODE_STOPPED) &&
			(MoreToMeasure()) ? TRUE : FALSE);
}

void CCADoc::OnMeasureStop()
{
	if ((CAGetApp()->m_mode == CCAApp::APPMODE_RUN) &&
		(GetMode() == MODE_MEASURING))
	{
		MeasureEnd();
		if (SCMessageBox("Measurement Stopped.\n\nWould you like to skip this measurement?", 
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			GetNext(m_replicate_num, m_sample_num);
			SetStatus();
			UpdateAllViews(NULL);
		}
	}
	// If MODE_STOPPED, then this function should not be called	
}

void CCADoc::OnUpdateMeasureStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((GetMode() == MODE_STOPPED) ? 1 : 0);
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? FALSE : TRUE);

}

void CCADoc::OnMeasureKinetics() 
{
	// TODO: Add your command handler code here
	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
		ToggleKinetics();
		if (m_graph_view)
		{
			HICON hIcon = AfxGetApp()->LoadIcon(IDR_KINETICSFRAME);
			m_graph_frame->SetIcon(hIcon, TRUE);
			m_graph_frame->SetIcon(hIcon, FALSE);
			((CKineticsView *)m_graph_view)->SetKinetics(m_kinetics,
				m_pps.m_meastime / (10 / SAMPLES_PER_SEC));
		}
	}
}

void CCADoc::OnUpdateMeasureKinetics(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_graph_view == NULL) ? 0 : 1);
}

void CCADoc::OnUpdateMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}


void CCADoc::SetStatus()
{
	// Change the status message
	CString status_str;

	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
		if (MoreToMeasure())
		{
			CString rep_str = GetReplicateString(m_sample_num, m_replicate_num);
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
			status_str = "No more measures to be made.";
		}
	}
	else
	{
		status_str = "View and export data.";
	}

	CAGetApp()->m_pMainFrame->SetMessageText(status_str);
}


CString CCADoc::GetReplicateString(UINT sample, UINT replicate)
{
	CString rep_str;

	if (sample <= m_numsamples)
	{
		if ((sample == 1) && m_pps.UseBackground())
		{
			rep_str.Format("replicate %d of background", replicate);
		}
		else if ((m_negsample > 0) && (sample == m_negsample))
		{
			rep_str.Format("replicate %d of the negative control", replicate);
		}
		else if ((m_possample > 0) && (sample == m_possample))
		{
			rep_str.Format("replicate %d of the positive control", replicate);
		}
		else
		{
			UINT offset = 1;
			if (m_pps.UseBackground())
				offset++;
			if (m_negsample > 0)
				offset++;
			if (m_possample > 0)
				offset++;
			UINT samp_num = sample - offset;
			//if (strlen(	m_pps.m_samplelist[samp_num].sampname) == 0)
			if (m_pps.m_samplelist[samp_num].IsEmpty())
			{
				rep_str.Format("replicate %d for sample %d", replicate, samp_num+1);
			}
			else
			{
				rep_str.Format("replicate %d for sample \"%s\"",replicate, 
					LPCTSTR(m_pps.m_samplelist[samp_num]));
			}
		}
	}
	else
	{
		rep_str = "none";
	}

	return rep_str;
}


void CCADoc::SetModifiedFlag(BOOL bModified)
{
	CProtocolDoc::SetModifiedFlag(
		(CAGetApp()->m_mode == CCAApp::APPMODE_VIEW) ? FALSE : bModified);
}

BOOL CCADoc::MoreToMeasure()
{
	BOOL ret = TRUE;

	if ((m_sample_num > m_numsamples) && (m_replicate_num == 1))
	{
		ret = FALSE;
	}

	return ret;
}

void CCADoc::RecalcCutoffs()
{
//	if ((m_samples[m_negsample-1].NumReplicatesUsed() > 0) &&
//		(m_samples[m_possample-1].NumReplicatesUsed() > 0))
//	{
		// All Controls measured, calculate the cutoffs
		long low_cutoff, high_cutoff;

		if ((m_negsample == 0) && (m_possample == 0))  // There are no controls
		{
			low_cutoff = m_pps.m_lowoffset;
			high_cutoff = m_pps.m_highoffset;
		}
		else if (m_negsample == 0)  // There are pos. controls, but no neg. controls
		{
			low_cutoff = m_pps.m_lowoffset + 
				((long)SCNearestInt(m_pps.m_low_lposfactor * m_samples[m_possample-1].m_net));
			high_cutoff = m_pps.m_highoffset + 
				((long)SCNearestInt(m_pps.m_high_lposfactor * m_samples[m_possample-1].m_net));
		}
		else if (m_possample == 0)  // There are neg. controls, but no pos. controls
		{
			low_cutoff = m_pps.m_lowoffset + 
				((long)SCNearestInt(m_pps.m_lowfactor * m_samples[m_negsample-1].m_net));
			high_cutoff = m_pps.m_highoffset + 
				((long)SCNearestInt(m_pps.m_highfactor * m_samples[m_negsample-1].m_net));
		}
		else  // There are both kinds of controls
		{
			low_cutoff = m_pps.m_lowoffset + 
				((long)SCNearestInt(m_pps.m_lowfactor * m_samples[m_negsample-1].m_net)) +
				((long)SCNearestInt(m_pps.m_low_lposfactor * m_samples[m_possample-1].m_net));

			high_cutoff = m_pps.m_highoffset + 
				((long)SCNearestInt(m_pps.m_highfactor * m_samples[m_negsample-1].m_net)) +
				((long)SCNearestInt(m_pps.m_high_lposfactor * m_samples[m_possample-1].m_net));
		}

		if (CSample::m_lowcutoff != low_cutoff)
			CSample::m_lowcutoff = low_cutoff;

		if (CSample::m_highcutoff != high_cutoff)
			CSample::m_highcutoff = high_cutoff;
		
		if (low_cutoff > high_cutoff)
			m_validassay = false;
		else
			m_validassay = true;

//	}
}


void CCADoc::OnFileSaveKineticsAsText() 
{
	// TODO: Add your command handler code here
	m_kinetics.SaveAsText();
}

void CCADoc::OnUpdateFileSaveKineticsAsText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_kinetics.m_num_kinetics == 0) ? FALSE : TRUE);
}

void CCADoc::OnUpdateFileSaveAsText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);	
}

void CCADoc::OnMeasureGrid() 
{
	// TODO: Add your command handler code here
	if (CAGetApp()->m_mode == CCAApp::APPMODE_RUN)
	{
		ToggleGrid();
	}
}

void CCADoc::OnUpdateMeasureGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_grid_view == NULL) ? 0 : 1);
}
