// Kinetics.cpp: implementation of the CKinetics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Kinetics.h"
#include "Protocol.h"
#include "General.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKinetics::CKinetics(long max_kinetics) : m_max_kinetics(max_kinetics)
{
	m_RLUs.SetSize(m_max_kinetics);
	Reset();
}

CKinetics::~CKinetics()
{
}

void CKinetics::Add(long rlu)
{
	if (m_num_kinetics < m_max_kinetics)
	{
		m_RLUs.SetAt(m_num_kinetics, rlu);
		m_num_kinetics++;
		m_RLU_sum += rlu;
		if (rlu < m_min)
		{
			m_min = rlu;
		}
		if (rlu > m_max)
		{
			m_max = rlu;
		}
	}
}

void CKinetics::Reset()
{
	m_num_kinetics = 0;
	m_RLU_sum = 0;
	m_min = LONG_MAX;
	m_max = LONG_MIN;
}

long CKinetics::GetMin() const
{
	return m_min;
}

long CKinetics::GetMax() const
{
	return m_max;
}

long CKinetics::GetMean() const
{
	if (m_num_kinetics > 0)
	{
		return (long)SCNearestInt((double)m_RLU_sum / (double)m_num_kinetics);
	}
	else
	{
		return 0;
	}
}

CString CKinetics::GetMeanString() const
{
	CString str = "=MEAN(";
	if (m_num_kinetics > 0)
	{
		CString num;
		num.Format("%ld", m_RLUs[0]);
		str += num;
		int i;
		for(i = 1; i < m_num_kinetics; i++)
		{
			num.Format(", %ld", m_RLUs[i]);
			str += num;
		}
	}
	str += ')';
	return str;
}

bool CKinetics::SaveAsText()
{
	bool success = false;
	CString str;

	ProtGetApp()->FB12Inhibit();

	// pop-up file-open dlg to ask for location
	CFileDialog dlgFile(
		FALSE,
		_T(".txt"),
		_T("Kinetics.txt"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));
	dlgFile.m_ofn.lpstrTitle = _T("Save Kinetics As Text");

	if (dlgFile.DoModal() == IDOK)
	{
		CFile textFile;
		if (textFile.Open(dlgFile.GetFileName(),
			CFile::modeCreate | CFile::modeWrite))
		{
			try
			{
				int i;
				for (i = 0; i < m_num_kinetics; i++)
				{
					str.Format("%ld\r\n", m_RLUs[i]);
					textFile.Write(str, str.GetLength());
				}
				success = true;
			}
			catch(CFileException *e)
			{
				str.Format("Error writing kinetics data.\n\n%s", dlgFile.GetFileName());
				SCMessageBox(str);
				e->Delete();
			}

			textFile.Close();
		}
		else
		{
			str.Format("File %s could not be opened!", dlgFile.GetFileName());
			SCMessageBox(str);
		}
	}

	ProtGetApp()->FB12Uninhibit();

	return success;
}
