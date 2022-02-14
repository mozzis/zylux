// GridRunProt.cpp: implementation of the CGridRunProt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zyluxzip.h"
#include "GridRunProt.h"
#include "inplacecheck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGridRunProt, CGridZip)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridRunProt::CGridRunProt()
{

}

CGridRunProt::~CGridRunProt()
{

}


BEGIN_MESSAGE_MAP(CGridRunProt, CGridZip)
  //{{AFX_MSG_MAP(CGridRunProt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CGridRunProt::InsertRow(LPCTSTR strHeading, int nRow /* = -1 */)
{
  if (0 <= (nRow = CGridCtrl::InsertRow(strHeading, nRow)))
    SetCellType(nRow,1,RUNTIME_CLASS(CInPlaceCheck));

  return nRow;
}
