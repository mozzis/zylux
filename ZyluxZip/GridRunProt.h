// GridRunProt.h: interface for the CGridRunProt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDRUNPROT_H__A507CFB1_12B0_4814_AC89_3CAD1A77999E__INCLUDED_)
#define AFX_GRIDRUNPROT_H__A507CFB1_12B0_4814_AC89_3CAD1A77999E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridZip.h"

class CGridRunProt : public CGridZip  
{
  DECLARE_DYNCREATE(CGridRunProt)
public:
	CGridRunProt();
	virtual ~CGridRunProt();
  virtual int InsertRow(LPCTSTR strHeading, int nRow /* = -1 */);

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CGridRunProt)
  //}}AFX_VIRTUAL

protected:
  // Generated message map functions
  //{{AFX_MSG(CGridRunProt)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GRIDRUNPROT_H__A507CFB1_12B0_4814_AC89_3CAD1A77999E__INCLUDED_)
