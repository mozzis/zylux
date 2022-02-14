// QMDoc.cpp : implementation of the CQMDoc class
//

#include "stdafx.h"
#include "QM.h"
#include "MainFrm.h"
#include "General.h"

#include "QMDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQMDoc

IMPLEMENT_DYNCREATE(CQMDoc, CProtocolDoc)

BEGIN_MESSAGE_MAP(CQMDoc, CProtocolDoc)
	//{{AFX_MSG_MAP(CQMDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_TEXT, OnUpdateFileSaveAsText)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateMode)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQMDoc construction/destruction

CQMDoc::CQMDoc() : m_meascount(0), m_delaycount(0),
	m_kinetics(QMGetApp()->m_pps.m_meastime / 2)
{
	// TODO: add one-time construction code here
	// Set the time to the current time
	time_t sys_time;
	time(&sys_time);
	CTime now(sys_time);
	m_datetime = now;
}

CQMDoc::~CQMDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CQMDoc serialization

void CQMDoc::Serialize(CArchive& ar)
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
// CQMDoc diagnostics

#ifdef _DEBUG
void CQMDoc::AssertValid() const
{
	CProtocolDoc::AssertValid();
}

void CQMDoc::Dump(CDumpContext& dc) const
{
	CProtocolDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQMDoc commands

void CQMDoc::FB12NewRLU(long new_RLU)
{
	if (GetMode() == MODE_MEASURING)
	{
		if (!QMGetApp()->m_pFB12Device->get_dooropen())
		{
			// Add this RLU event to the kinetics info
			if (m_delaycount == 0)
			{
				if (m_meascount > 0)
				{
					m_kinetics.Add(new_RLU);
					m_meascount--;
					if (m_meascount == 0)
					{
						m_RLUs.Add(m_kinetics.GetMean());
						SetModifiedFlag(TRUE);
						UpdateAllViews(NULL, m_RLUs.GetSize());
						MeasureEnd();
						if (ProtGetApp()->m_beep)
						{
							MessageBeep(MB_OK);
						}
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
					QMGetApp()->m_pMainFrame->SetMessageText(IDS_MEASUREMESSAGE);
				}
			}
		}
	}
}

void CQMDoc::FB12DoorChange(VARIANT_BOOL is_open)
{
	if (is_open)
	{
		// door was openend
		if (GetMode() == MODE_MEASURING)
		{
			// during measuring!!!
			MeasureEnd();
			SCMessageBox(IDS_FB12_DOOROPENED);
		}
	}
	else
	{
		// The door was closed
		MeasureStart();
	}
}

void CQMDoc::FB12OperatingChange(VARIANT_BOOL is_operating)
{

}

void CQMDoc::FB12ErrorChange(long new_error)
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

void CQMDoc::FB12CommunicatingChange(VARIANT_BOOL is_communicating)
{
	if (!is_communicating &&
		((m_delaycount > 0) || (m_meascount > 0)))
	{
		MeasureEnd();
		SCMessageBox(IDS_FB12_TIMEOUT);
	}
}

void CQMDoc::SetMode(int mode)
{
	m_mode = mode;
}

int CQMDoc::GetMode() const
{
	return m_mode;
}

void CQMDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	// since document is going away, inhibit FB12 from talking to it
	QMGetApp()->FB12Inhibit();

	// Call base class
	CProtocolDoc::OnCloseDocument();

	// We are quitting the program
	AfxGetApp()->m_pMainWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CQMDoc::MeasureStart()
{
	// The delay and measurement counts are initialized
	m_delaycount = m_delaytime / (10 / SAMPLES_PER_SEC);
	m_meascount = m_meastime / (10 / SAMPLES_PER_SEC);

	// Start a new set of kinetics
	m_kinetics.Reset();

	// Set the statusbar text
	QMGetApp()->m_pMainFrame->SetMessageText(
		(m_delaycount == 0) ? IDS_MEASUREMESSAGE : IDS_DELAYMESSAGE);

	SetMode(MODE_MEASURING);
}

void CQMDoc::MeasureEnd()
{
	SetMode(MODE_STOPPED);

	// Reset the counters
	m_delaycount = 0;
	m_meascount = 0;

	// Set the statusbar text
	QMGetApp()->m_pMainFrame->SetMessageText(AFX_IDS_IDLEMESSAGE);

	// Save the log file
	LogDocument();
}

void CQMDoc::OnUpdateFileSaveAsText(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((QMGetApp()->m_mode == CQMApp::APPMODE_VIEW) ||
		((GetMode() == MODE_STOPPED) && IsModified())) ? TRUE : FALSE );
}

void CQMDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	if (QMGetApp()->m_mode == CQMApp::APPMODE_RUN)
	{
		if (SaveModified())
		{
			if (OnNewDocument())
			{
				UpdateAllViews(NULL);
			}
		}
	}
}

void CQMDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	m_delaycount = 0;
	m_meascount = 0;

	m_RLUs.RemoveAll();
	m_kinetics.Reset();

	CProtocolDoc::DeleteContents();

	m_delaytime = QMGetApp()->m_pps.m_delaytime;
	m_meastime = QMGetApp()->m_pps.m_meastime;

	// Start out in stopped mode
	SetMode(MODE_STOPPED);

	SetModifiedFlag(FALSE);

	RemoveLog();

	if (QMGetApp()->m_mode == CQMApp::APPMODE_RUN)
	{
		QMGetApp()->m_pMainFrame->SetMessageText(AFX_IDS_IDLEMESSAGE);
	}
	else
	{
		QMGetApp()->m_pMainFrame->SetMessageText(IDS_VIEW_IDLEMESSAGE);
	}
}

BOOL CQMDoc::LogDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;
	CFile file;
	if (file.Open(QMGetApp()->m_logpath, CFile::modeCreate | CFile::modeWrite))
	{
		if (SaveMDS(file))
		{
			ok = TRUE;
		}
		file.Close();
	}

	return ok;
}

void CQMDoc::RemoveLog()
{
	if (QMGetApp()->m_mode == CQMApp::APPMODE_RUN)
	{
		try
		{
			CFile::Remove(QMGetApp()->m_logpath);
		}
		catch(CFileException* e)
		{
			e->Delete();
		}
	}
}

BOOL CQMDoc::OnSaveDocument(LPCTSTR pathname)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ok = FALSE;

	if (QMGetApp()->m_mode == CQMApp::APPMODE_RUN)
	{
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

BOOL CQMDoc::OnOpenDocument(LPCTSTR pathname)
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

BOOL CQMDoc::SaveMDS(CFile& mds_file)
{
	try
	{
		mds_file.SeekToBegin();
		mds_file.SetLength(0);

		// Write the PPS data
		if (!QMGetApp()->m_pps.Write(mds_file))
		{
			return FALSE;
		}

		// Write the MDS data
		int year = m_datetime.GetYear();
		int month = m_datetime.GetMonth();
		int day = m_datetime.GetDay();
		int hour = m_datetime.GetHour();
		int minute = m_datetime.GetMinute();
		int second = m_datetime.GetSecond();
		int num_samples = m_RLUs.GetSize();
		mds_file.Write(&year, sizeof(year));
		mds_file.Write(&month, sizeof(month));
		mds_file.Write(&day, sizeof(day));
		mds_file.Write(&hour, sizeof(hour));
		mds_file.Write(&minute, sizeof(minute));
		mds_file.Write(&second, sizeof(second));
		mds_file.Write(&num_samples, sizeof(num_samples));

		for (int i = 0; i < num_samples; i++)
		{
			mds_file.Write(&m_RLUs[i], sizeof(long));
		}
	}
	catch (CFileException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}


BOOL CQMDoc::LoadMDS(CFile& mds_file)
{
	try
	{
		// Read the PPS data
		if (!QMGetApp()->m_pps.Read(mds_file))
		{
			return FALSE;
		}

		// Resets stuff according to PPS structures
		DeleteContents();

		// Read the MDS data
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		int num_samples;
		if ((mds_file.Read(&year, sizeof(year)) != sizeof(year)) ||
			(mds_file.Read(&month, sizeof(month)) != sizeof(month)) ||
			(mds_file.Read(&day, sizeof(day)) != sizeof(day)) ||
			(mds_file.Read(&hour, sizeof(hour)) != sizeof(hour)) ||
			(mds_file.Read(&minute, sizeof(minute)) != sizeof(minute)) ||
			(mds_file.Read(&second, sizeof(second)) != sizeof(second)) ||
			(mds_file.Read(&num_samples, sizeof(num_samples)) != sizeof(num_samples)))
		{
			return FALSE;
		}
		CTime time(year, month, day, hour, minute, second);
		m_datetime = time;

		long rlu;
		for (int i = 0; i < num_samples; i++)
		{
			if (mds_file.Read(&rlu, sizeof(long)) != sizeof(long))
			{
				return FALSE;
			}
			m_RLUs.Add(rlu);
		}
	}
	catch (CFileException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}

void CQMDoc::OnUpdateMode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((GetMode() == MODE_STOPPED) ? TRUE : FALSE);
}
