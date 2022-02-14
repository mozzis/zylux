// SKHint.h: interface for the CSKHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_)
#define AFX_SKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSKHint : public CObject  
{
public:
	UINT m_last;
	UINT m_first;
	UINT m_replicate;
	CSKHint(UINT first_sample, UINT last_sample, UINT replicate);
	virtual ~CSKHint();

};

#endif // !defined(AFX_SKHINT_H__228FF7E1_456C_11D1_AE1E_0080C80C9F0E__INCLUDED_)
