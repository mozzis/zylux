// Sample.cpp: implementation of the CSample class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sample.h"
#include "DA.h"
#include "General.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CSample::m_background_a = 0;
long CSample::m_background_b = 0;
bool CSample::m_normalize = false;
double CSample::m_normalize_value = 1.0;

CSample::CSample() :
	m_average_a(0.0), m_net_a(0.0), m_precision_a(0.0), m_precision_net_a(0.0),
	m_average_b(0.0), m_net_b(0.0), m_precision_b(0.0), m_precision_net_b(0.0),
	m_xnet_a(0.0), m_xnet_b(0.0), m_xform(0.0), m_precision_xform(0.0),
	m_precision_a_overflow(false), m_precision_net_a_overflow(false),
	m_precision_b_overflow(false), m_precision_net_b_overflow(false),
	m_xform_overflow(false), m_xnet_a_overflow(false),
	m_precision_xform_overflow(false), m_precision_xform_na(false)
{
}

CSample::~CSample()
{

}

// SetReplicate()
//
// Sets the value of a specific replicate.
//
// Inputs:
//   series    - the series: SERIES_A or SERIES_B
//   replicate - the replicate: 0 - (numreplicates - 1)
//   RLU       - the RLU value
//
// Output: none

void CSample::SetReplicate(int series, int replicate, long RLU)
{
	if (series == SERIES_A)
	{
		if (replicate < m_replicates_a.GetSize())
		{
			m_replicates_a[replicate].m_used = true;
			m_replicates_a[replicate].m_RLU = RLU;
			RecalculateA();
			RecalculateTransform();
		}
	}
	else
	{
		if (replicate < m_replicates_b.GetSize())
		{
			m_replicates_b[replicate].m_used = true;
			m_replicates_b[replicate].m_RLU = RLU;
			RecalculateB();
			RecalculateTransform();
		}
	}
}

void CSample::ClearReplicate(int series, int replicate)
{
	if (series == SERIES_A)
	{
		if (replicate < m_replicates_a.GetSize())
		{
			m_replicates_a[replicate].m_used = false;
			m_replicates_a[replicate].m_RLU = 0;
			RecalculateA();
			RecalculateTransform();
		}
	}
	else
	{
		if (replicate < m_replicates_b.GetSize())
		{
			m_replicates_b[replicate].m_used = false;
			m_replicates_b[replicate].m_RLU = 0;
			RecalculateB();
			RecalculateTransform();
		}
	}
}

int CSample::GetNumReplicates(int series)
{
	int i;
	int num = 0;

	if (series == SERIES_A)
	{
		for (i = 0; i < m_replicates_a.GetSize(); i++)
		{
			if (m_replicates_a[i].m_used)
			{
				num++;
			}
		}
	}
	else
	{
		for (i = 0; i < m_replicates_b.GetSize(); i++)
		{
			if (m_replicates_b[i].m_used)
			{
				num++;
			}
		}
	}

	return num;
}

void CSample::Recalculate()
{
	// Series A
	RecalculateA();

	// Series B
	RecalculateB();

	// Transform
	RecalculateTransform();
}

void CSample::RecalculateA()	// Does not call Normalize()!
{
	int i;
	int num;
	double ave;
	double sd;
	double d;

	// Series A
	// calculate the average of a
	ave = 0.0;
	num = 0;
	for (i = 0; i < m_replicates_a.GetSize(); i++)
	{
		if (m_replicates_a[i].m_used)
		{
			num++;
			ave += m_replicates_a[i].m_RLU;
		}
	}
	if (num > 0)
	{
		ave = SCRound(ave / num);
		m_average_a = ave;					// Set the average for A
		m_net_a = ave - m_background_a;		// Set the net for A

		// calculate the standard deviation of a
		sd = 0.0;
		for (i = 0; i < m_replicates_a.GetSize(); i++)
		{
			if (m_replicates_a[i].m_used)
			{
				d = ave - m_replicates_a[i].m_RLU;
				sd += d * d;
			}
		}
		sd = sqrt(sd / num);

		// calculate the precision of a
		if (ave == 0.0)
		{
			m_precision_a = 0.0;
			m_precision_a_overflow = true;
		}
		else
		{
			// Set the precision for A
			m_precision_a = SCRound(sd / ave * 100.0);
			m_precision_a_overflow = false;
		}

		// calculate the precision of net a
		if (m_net_a == 0.0)
		{
			m_precision_net_a = 0.0;
			m_precision_net_a_overflow = true;
		}
		else
		{
			// Set the net of precision for A
			m_precision_net_a = SCRound(sd / m_net_a * 100.0);
			m_precision_net_a_overflow = false;
		}
	}
}

void CSample::RecalculateB()	// Does not call RecalculateTransform()!
{
	int i;
	int num;
	double ave;
	double sd;
	double d;

	// Series B
	// calculate the average for b
	ave = 0.0;
	num = 0;
	for (i = 0; i < m_replicates_b.GetSize(); i++)
	{
		if (m_replicates_b[i].m_used)
		{
			num++;
			ave += m_replicates_b[i].m_RLU;
		}
	}
	if (num > 0)
	{
		ave = SCRound(ave / num);
		m_average_b = ave;					// Set the average for B
		m_net_b = ave - m_background_b;		// Set the net for B

		// calculate the standard deviation
		sd = 0.0;
		for (i = 0; i < m_replicates_b.GetSize(); i++)
		{
			if (m_replicates_b[i].m_used)
			{
				d = ave - m_replicates_b[i].m_RLU;
				sd += d * d;
			}
		}
		sd = sqrt(sd / num);

		// calculate the precision of b
		if (ave == 0.0)
		{
			m_precision_b = 0.0;
			m_precision_b_overflow = true;
		}
		else
		{
			// Set the precision for B
			m_precision_b = SCRound(sd / ave * 100.0);
			m_precision_b_overflow = false;
		}

		// calculate the precision of net b
		if (m_net_b == 0.0)
		{
			m_precision_net_b = 0.0;
			m_precision_net_b_overflow = true;
		}
		else
		{
			// Set the net of precision for B
			m_precision_net_b = SCRound(sd / m_net_b * 100.0);
			m_precision_net_b_overflow = false;
		}
	}
}

void CSample::RecalculateTransform()
{
	// Calculate xnets
	if (m_net_b == 0.0)
	{
		m_xnet_a = 0.0;
		m_xnet_a_overflow = true;
	}
	else
	{
		m_xnet_a = SCRound(m_net_a * m_normalize_value / m_net_b);
		m_xnet_a_overflow = false;
	}
	m_xnet_b = m_normalize_value;

	// Calculate the transform
	double a = m_normalize ? m_xnet_a : m_net_a;
	double b = m_normalize ? m_xnet_b : m_net_b;

	m_xform = 0.0;				// default 0
	m_xform_overflow = false;	// assume no overflow

	switch (DAGetApp()->m_pps.m_transform)
	{
	case CDAPPS::XFORM_AMINUSB:
		m_xform = a - b;
		break;

	case CDAPPS::XFORM_BMINUSA:
		m_xform = b - a;
		break;

	case CDAPPS::XFORM_ADIVB:
		if (b == 0.0)
		{
			m_xform_overflow = true;
		}
		else
		{
			m_xform = SCRound(a / b);
		}
		break;

	case CDAPPS::XFORM_BDIVA:
		if (a == 0.0)
		{
			m_xform_overflow = true;
		}
		else
		{
			m_xform = SCRound(b / a);
		}
		break;

	case CDAPPS::XFORM_ADIV_BMINUSA:
		if ((b - a) == 0.0)
		{
			m_xform_overflow = true;
		}
		else
		{
			m_xform = SCRound(a / (b - a));
		}
		break;
	}

	// Calculate the precision of transformed replicates
	m_precision_xform = 0.0;			// default 0
	m_precision_xform_overflow = false;	// assume no overflow
	m_precision_xform_na = false;		// assume applicable

	// Build the replicate transform array
	CArray<double, double> repx;
	int i;
	for (i = 0; !m_precision_xform_overflow && 
		(i < m_replicates_a.GetSize()) && (i < m_replicates_b.GetSize());
		i++)
	{
		if ((m_replicates_a[i].m_used) &&
			(m_replicates_b[i].m_used))
		{
			// get the nets
			a = (double)(m_replicates_a[i].m_RLU - m_background_a);
			b = (double)(m_replicates_b[i].m_RLU - m_background_b);

			// make transform
			switch (DAGetApp()->m_pps.m_transform)
			{
			case CDAPPS::XFORM_AMINUSB:
				repx.Add(a - b);
				break;

			case CDAPPS::XFORM_BMINUSA:
				repx.Add(b - a);
				break;

			case CDAPPS::XFORM_ADIVB:
				if (b == 0.0)
				{
					m_precision_xform_overflow = true;
				}
				else
				{
					repx.Add(a / b);
				}
				break;

			case CDAPPS::XFORM_BDIVA:
				if (a == 0.0)
				{
					m_precision_xform_overflow = true;
				}
				else
				{
					repx.Add(b / a);
				}
				break;

			case CDAPPS::XFORM_ADIV_BMINUSA:
				if ((b - a) == 0.0)
				{
					m_precision_xform_overflow = true;
				}
				else
				{
					repx.Add(a / (b - a));
				}
				break;
			}
		}
		else
		{
			break;
		}
	}

	int num = repx.GetSize();
	if (num == 0)
	{
		m_precision_xform_na = true;
	}
	else if (!m_precision_xform_overflow)
	{
		// Find the average
		double ave = 0.0;
		for (i = 0; i < num; i++)
		{
			ave += repx[i];
		}
		ave /= num;

		// Find the standard deviation
		double sd = 0.0;
		double d;
		for (i = 0; i < num; i++)
		{
			d = ave - repx[i];
			sd += d * d;
		}
		sd = sqrt(sd / num);

		m_precision_xform = SCRound(sd / ave * 100.0);
	}
}
