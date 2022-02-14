// MKHint.cpp: implementation of the CMKHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MK.h"
#include "MKHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMKHint::CMKHint(UINT meas, UINT samp, UINT rep)
	: m_meas(meas), m_samp(samp), m_rep(rep)
{

}

CMKHint::~CMKHint()
{

}
