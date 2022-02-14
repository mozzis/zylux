// SKHint.cpp: implementation of the CSKHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sk.h"
#include "SKHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSKHint::CSKHint(UINT first_sample, UINT last_sample, UINT replicate)
	: m_first(first_sample), m_last(last_sample), m_replicate(replicate)
{

}

CSKHint::~CSKHint()
{

}
