// DlgSiteList.cpp : implementation file
// DlgSiteList is a dialog for editing the site list
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgSiteList.cpp $ * 
// 
// *****************  Version 11  *****************
// User: Maynard      Date: 11/09/00   Time: 4:47p
// Updated in $/ZyluxZip
// Add "true" parameter to call to UpgradeDataRowCount so that list
// control will shrink if the number of entries in list is smaller than
// the default
// 
// *****************  Version 10  *****************
// User: Maynard      Date: 9/26/00    Time: 9:03a
// Updated in $/ZyluxZip
// Make function to change row count to a new number if the new count is
// greater than the present count, and call it to size the grids to their
// respective lists' sizes in OnInitDialog
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 3/18/00    Time: 5:31p
 * Updated in $/ZyluxZip
 * Get rid of some extra symbol names; now similar buttons have same
 * symbol name in all dialogs
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:43a
 * Updated in $/ZyluxZip
 * Add saving and loading of the site list
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:27p
 * Updated in $/ZyluxZip
 * Move initialize of m+pColumnDefs to constructor so can eliminate
 * OnInitDialog override
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:52p
 * Updated in $/ZyluxZip
 * Convert to single-row header with two lines of text per header
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/01/00    Time: 12:44p
 * Updated in $/ZyluxZip
 * Derive the class from CZipListDlg, which does most of the work now
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/01/00    Time: 10:38a
 * Updated in $/ZyluxZip
 * Add Edit menu functions copy, cut,paste, select all, ins/del row
 * Real fix for Esc/Enter key handling (use Trl/DispMessage)
 * 
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 2/28/00    Time: 11:35p
 * Updated in $/ZyluxZip
 * Add comments
 * Change pre-translate message action - just calls pre-translate of grid
 * control to hid escape key from dialog
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 2/27/00    Time: 5:12p
 * Updated in $/ZyluxZip
 * Add copyright and Source Safe headers
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZyluxZip.h"
#include "DlgSiteList.h"
#include "sitelist.h"
#include "messages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteList dialog
#define COL_NAME    1
#define COL_THRESLO 2
#define COL_THRESHI 3
#define COL_SCALELO 4
#define COL_SCALEHI 5

// Titles for column headers
/////////////////////////////////////////
static ZIPCOLDEF tColDefs[] = 
  {
    { 0, COL_NAME,    _T("Site\n\rName") },
    { 0, COL_THRESLO, _T("Threshold\n\rLow") },
    { 0, COL_THRESHI, _T("Threshold\n\rHigh") },
    { 0, COL_SCALELO, _T("Scale\n\rLow")     },
    { 0, COL_SCALEHI, _T("Scale\n\rHigh")     },
    EndOfCols,
  };

// Constructor and destructor
//////////////////////////////////////////////////
CDlgSiteList::CDlgSiteList(CWnd* pParent /*=NULL*/)
	: CDlgZipList(CDlgSiteList::IDD, pParent)
{
  m_pColumnDefs = tColDefs;
	//{{AFX_DATA_INIT(CDlgSiteList)
	//}}AFX_DATA_INIT
  Create(IDD, pParent);
}

CDlgSiteList::~CDlgSiteList()
{
}

void CDlgSiteList::DoDataExchange(CDataExchange* pDX)
{
	CDlgZipList::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSiteList)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSiteList, CDlgZipList)
	//{{AFX_MSG_MAP(CDlgSiteList)
	ON_BN_CLICKED(IDC_LIST_SAVE, OnSiteSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteList message handlers

// Does the actual action of saving data to the site list file
/////////////////////////////////////////////////////////////////////////////
bool CDlgSiteList::SaveSiteList()
{
  CSiteList siteList;
  for (int i = m_Grid.GetFixedRowCount(); i < m_Grid.GetRowCount() - 1; i++)
    {
    CString csTemp;
    csTemp = m_Grid.GetItemText(i, COL_NAME);
    if (!csTemp.IsEmpty())
      {
      LPTSTR pDummy;
      CSite tSite;
      tSite.m_csName = csTemp;
      tSite.m_ThresholdLow =  _tcstod(m_Grid.GetItemText(i, COL_THRESLO), &pDummy);
      tSite.m_ThresholdHigh = _tcstod(m_Grid.GetItemText(i, COL_THRESHI), &pDummy);
      tSite.m_ScaleLow =      _tcstod(m_Grid.GetItemText(i, COL_SCALELO), &pDummy);
      tSite.m_ScaleHigh =     _tcstod(m_Grid.GetItemText(i, COL_SCALEHI), &pDummy);
      siteList.Add(tSite);
      }
    }
  if (siteList.Save())
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
void CDlgSiteList::OnSiteSave() 
{
  SaveSiteList();
}

// Makes sure that changes are saved before allowing dialog to close
/////////////////////////////////////////////////////////////////////////////
bool CDlgSiteList::OkToClose()
{
	if (m_Grid.GetModified())
    {
    int nRes = 
      AfxMessageBox("Site List has changed! Save changes?", MB_YESNOCANCEL);
    if (IDCANCEL == nRes)
      return false;
    if (IDYES == nRes)
      return SaveSiteList();
    }
  return true;
}

BOOL CDlgSiteList::OnInitDialog() 
{
	BOOL bRet = CDlgZipList::OnInitDialog();
  CSiteList siteList;
	
	siteList.Load();
  UpgradeDataRowCount(siteList.GetSize(), true);

  for (int i = 0; i < siteList.GetSize(); i++)
    {
    int j = m_Grid.GetFixedRowCount();
    CSite tSite = siteList[i];
    m_Grid.SetItemText( i+j,COL_NAME,    tSite.m_csName);
    m_Grid.SetItemFloat(i+j,COL_THRESLO, tSite.m_ThresholdLow);
    m_Grid.SetItemFloat(i+j,COL_THRESHI, tSite.m_ThresholdHigh);
    m_Grid.SetItemFloat(i+j,COL_SCALELO, tSite.m_ScaleLow);
    m_Grid.SetItemFloat(i+j,COL_SCALEHI, tSite.m_ScaleHigh);
    }
  m_Grid.SetModified(FALSE);
	return bRet;
}
