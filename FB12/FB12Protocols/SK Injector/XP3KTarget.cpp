// XP3KTarget.cpp: implementation of the CXP3KTarget class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XP3KTarget.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXP3KTarget::CXP3KTarget()
{

}

CXP3KTarget::~CXP3KTarget()
{

}

void CXP3KTarget::XP3KStartResponse(BYTE result)
{
}

void CXP3KTarget::XP3KMoveToAbsResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KMoveToRelativeResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KGetStatusResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KGetPositionResponse(BYTE dev_num, BYTE result, BYTE status, int pos)
{
}

void CXP3KTarget::XP3KDrawResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KInjectResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KSetSpeedResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KSetValveResponse(BYTE dev_num, BYTE result, BYTE status)
{
}

void CXP3KTarget::XP3KInitResponse(BYTE dev_num, BYTE result, BYTE status)
{
}