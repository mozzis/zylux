// Sample.cpp: implementation of the CSample class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CA.h"
#include "Sample.h"
#include "General.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CSample::m_background = 0;
long CSample::m_lowcutoff = 0;
long CSample::m_highcutoff = 0;

CSample::CSample() : m_precision_overflow(false), m_netprecision_overflow(false),
					 m_average(0.0), m_net(0.0), m_precision(0.0), m_precision_net(0.0),
					 m_result(RESULT_NONE)
{
}

CSample::~CSample()
{

}



void CSample::SetReplicate(int rep_num, long value)
{
	
	if (rep_num < m_replicates.GetSize())
	{
		m_replicates[rep_num].m_RLU = value;
		m_replicates[rep_num].m_used = true;
		//if (NumReplicatesUsed() > 0)
		Recalculate();
	}

}


void CSample::ClearReplicate(int rep_num)
{
	if (rep_num < m_replicates.GetSize())
	{
		m_replicates[rep_num].m_RLU = 0;
		m_replicates[rep_num].m_used = false;
		Recalculate();
	}
}

void CSample::Recalculate()
{
	int num_used = 0;
	double sum =0.0;
	int i;
	for (i = 0; i < m_replicates.GetSize(); i++)
	{
		if (m_replicates[i].m_used)
		{
			num_used++;
			sum+= m_replicates[i].m_RLU;
		}
	}

	if (num_used > 0)
	{

		m_average = SCRound(sum / num_used);
		m_net = m_average - m_background;
		sum = 0.0;

		for (i = 0; i < m_replicates.GetSize(); i++)
		{
			if (m_replicates[i].m_used)
			{
				sum += pow((m_average - m_replicates[i].m_RLU), 2);
			}
		}

		double std_dev = sqrt(sum/num_used);

		if (m_average != 0)
		{
			m_precision = SCRound(std_dev / m_average * 100.0);
			m_precision_overflow = false;
		}
		else
		{
			m_precision = 0.0;
			m_precision_overflow = true;
		}

		if (m_net != 0)
		{
			m_precision_net = SCRound(std_dev / m_net * 100.0);
			m_netprecision_overflow = false;
		}
		else
		{
			m_precision_net = 0.0;
			m_netprecision_overflow = true;
		}

		// Calculate Result
		if ((m_result != RESULT_BKGD) && (m_result != RESULT_NEGSTD) &&
			(m_result != RESULT_POSCTRL))
		{
			if (m_net < m_lowcutoff)
				m_result = RESULT_NEG;
			else if (m_net > m_highcutoff)
				m_result = RESULT_POS;
			else
				m_result = RESULT_EQUIV;
		}
	}
}


UINT CSample::NumReplicatesUsed()
{
	int count = 0;
	int num_replicates = m_replicates.GetSize();

	for (int i=0; i < num_replicates; i++)
	{
		if (m_replicates[i].m_used)
			count++;
	}

	return count;
}


