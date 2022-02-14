// Sample.cpp: implementation of the CSample class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sample.h"
#include "MK.h"
#include "General.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CSample::m_background = 0;

CMeasurement::CMeasurement() :
	m_average(0.0), m_net(0.0), m_precision(0.0), m_precision_net(0.0),
	m_precision_overflow(false), m_precision_net_overflow(false),
	m_time_valid(false), m_time(0)
{
}

CMeasurement::~CMeasurement()
{

}

// SetReplicate()
//
// Sets the value of a specific replicate.
//
// Inputs:
//   replicate - the replicate: 0 - (numreplicates - 1)
//   RLU       - the RLU value
//
// Output: none

void CMeasurement::SetReplicate(int replicate, long RLU)
{
	if (replicate < m_replicates.GetSize())
	{
		m_replicates[replicate].m_used = true;
		m_replicates[replicate].m_RLU = RLU;
		Recalculate();
	}
}

void CMeasurement::SetTime(DWORD time)
{
	m_time = time;
	m_time_valid = true;
}

void CMeasurement::ClearReplicate(int replicate)
{
	if (replicate < m_replicates.GetSize())
	{
		m_replicates[replicate].m_used = false;
		m_replicates[replicate].m_RLU = 0;
		Recalculate();
	}
}

int CMeasurement::GetNumReplicates()
{
	int i;
	int num = 0;

	for (i = 0; i < m_replicates.GetSize(); i++)
	{
		if (m_replicates[i].m_used)
		{
			num++;
		}
	}

	return num;
}

void CMeasurement::Recalculate()
{
	int i;

	// calculate the average
	double ave = 0.0;
	int num = 0;
	for (i = 0; i < m_replicates.GetSize(); i++)
	{
		if (m_replicates[i].m_used)
		{
			num++;
			ave += m_replicates[i].m_RLU;
		}
	}

	if (num > 0)
	{
		ave = SCRound(ave / num);

		m_average = ave;						// Set the average
		m_net = ave - CSample::m_background;	// Set the net

		// calculate the standard deviation
		double sd = 0.0;
		double d;
		for (i = 0; i < m_replicates.GetSize(); i++)
		{
			if (m_replicates[i].m_used)
			{
				d = ave - m_replicates[i].m_RLU;
				sd += d * d;
			}
		}
		sd = sqrt(sd / num);

		// calculate the precision
		if (ave == 0.0)
		{
			m_precision = 0.0;
			m_precision_overflow = true;
		}
		else
		{
			// Set the precision
			m_precision = SCRound(sd / ave * 100.0);
			m_precision_overflow = false;
		}

		// calculate the precision of net
		if (m_net == 0.0)
		{
			m_precision_net = 0.0;
			m_precision_net_overflow = true;
		}
		else
		{
			// Set the net of precision for
			m_precision_net = SCRound(sd / m_net * 100.0);
			m_precision_net_overflow = false;
		}
	}
}
