// MKHint.h: interface for the CMKHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_MKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMKHint : public CObject
{
public:
	UINT m_meas;
	UINT m_samp;
	UINT m_rep;
	CMKHint(UINT meas, UINT samp, UINT rep);
	virtual ~CMKHint();

};

#endif // !defined(AFX_MKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_)
