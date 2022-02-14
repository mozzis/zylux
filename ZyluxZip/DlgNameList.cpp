// DlgNameList.cpp : implementation file
// DlgNameList is a dialog for editing the name list
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgNameList.cpp $ * 
// 
// *****************  Version 7  *****************
// User: Maynard      Date: 11/09/00   Time: 4:43p
// Updated in $/ZyluxZip
// Add "true" parameter to call to UpgradeDataRowCount so that list
// control will shrink if the number of entries in list is smaller than
// the default
// 
// *****************  Version 6  *****************
// User: Maynard      Date: 9/26/00    Time: 9:03a
// Updated in $/ZyluxZip
// Make function to change row count to a new number if the new count is
// greater than the present count, and call it to size the grids to their
// respective lists' sizes in OnInitDialog
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/18/00    Time: 5:31p
 * Updated in $/ZyluxZip
 * Get rid of some extra symbol names; now similar buttons have same
 * symbol name in all dialogs
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:41a
 * Updated in $/ZyluxZip
 * Add saving and loading of the name list
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:25p
 * Updated in $/ZyluxZip
 * Move initialize of m_pColumnDefs to constructor so can eliminate
 * OnInitDialog override
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:50p
 * Updated in $/ZyluxZip
 * Add dialog to edit name list
 * 
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZyluxZip.h"
#include "RunNameList.h"
#include "DlgNameList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNameList dialog

#define COL_NAME 1
#define COL_DESC 2

// Titles for column headers
/////////////////////////////////////////
static ZIPCOLDEF tColDefs[] = 
  {
    { 0, COL_NAME, _T("Run Name") },
    { 0, COL_DESC, _T("Description") },
    EndOfCols,
  };

CDlgNameList::CDlgNameList(CWnd* pParent /*=NULL*/)
  : CDlgZipList(CDlgNameList::IDD, pParent)
{
  m_nInitColCount = 3;
  m_pColumnDefs = tColDefs;
  //{{AFX_DATA_INIT(CDlgNameList)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  Create(IDD, pParent);
}


void CDlgNameList::DoDataExchange(CDataExchange* pDX)
{
  CDlgZipList::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgNameList)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgNameList, CDlgZipList)
  //{{AFX_MSG_MAP(CDlgNameList)
	ON_BN_CLICKED(IDC_LIST_SAVE, OnNamesSave)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNameList message handlers

// Does the actual action of saving data to the site list file
/////////////////////////////////////////////////////////////////////////////
bool CDlgNameList::SaveNameList()
{
  CRunNameList nameList;
  for (int i = m_Grid.GetFixedRowCount(); i < m_Grid.GetRowCount() - 1; i++)
    {
    CString csTemp;
    csTemp = m_Grid.GetItemText(i, COL_NAME);
    if (!csTemp.IsEmpty())
      {
      CRunName tName;
      tName.m_csName = csTemp;
      tName.m_csDescription = m_Grid.GetItemText(i,COL_DESC);
      nameList.Add(tName);
      }
    }
  if (nameList.Save())
    {
    m_Grid.SetModified(FALSE);
    SetDlgItemText(IDCANCEL, _T("&Close"));
    return true;
    }
  else
    return false;
}

// Runs when Save button is clicked
/////////////////////////////////////////////////////////////////////////////
void CDlgNameList::OnNamesSave() 
{
  SaveNameList();
}

// Makes sure that changes are saved before allowing dialog to close
/////////////////////////////////////////////////////////////////////////////
bool CDlgNameList::OkToClose()
{
	if (m_Grid.GetModified())
    {
    int nRes = 
      AfxMessageBox("Name List has changed! Save changes?", MB_YESNOCANCEL);
    if (IDCANCEL == nRes)
      return false;
    if (IDYES == nRes)
      return SaveNameList();
    }
  return true;
}

BOOL CDlgNameList::OnInitDialog() 
{
	BOOL bRet = CDlgZipList::OnInitDialog();
  CRunNameList nameList;
	
	nameList.Load();
  UpgradeDataRowCount(nameList.GetSize(), true);
  for (int i = 0; i < nameList.GetSize(); i++)
    {
    int j = m_Grid.GetFixedRowCount();
    CRunName tName = nameList[i];
    m_Grid.SetItemText(i+j, COL_NAME, tName.m_csName);
    m_Grid.SetItemText(i+j, COL_DESC, tName.m_csDescription);
    }
  m_Grid.SetModified(FALSE);
	return bRet;
}
