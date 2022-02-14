// XP3KTarget.h: interface for the CXP3KTarget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XP3KTARGET_H__6B4160A1_B28B_11D1_8C08_00400516EF5A__INCLUDED_)
#define AFX_XP3KTARGET_H__6B4160A1_B28B_11D1_8C08_00400516EF5A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CXP3KTarget  
{
public:
	CXP3KTarget();
	virtual ~CXP3KTarget();
	virtual void XP3KStartResponse(BYTE result);
	virtual void XP3KMoveToAbsResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KMoveToRelativeResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KGetStatusResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KGetPositionResponse(BYTE dev_num, BYTE result, BYTE status, int pos);
	virtual void XP3KDrawResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KInjectResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KSetSpeedResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KSetValveResponse(BYTE dev_num, BYTE result, BYTE status);
	virtual void XP3KInitResponse(BYTE dev_num, BYTE result, BYTE status);
};

#endif // !defined(AFX_XP3KTARGET_H__6B4160A1_B28B_11D1_8C08_00400516EF5A__INCLUDED_)
