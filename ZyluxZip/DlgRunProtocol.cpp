// DlgRunProtocol.cpp : implementation file
// DlgRunProtocol is a dialog for editing run protocol lists
// Copyright (C) 2000 Mayn Idea Software
// All rights reserved
/*
* $History: DlgRunProtocol.cpp $ * 
// 
// *****************  Version 24  *****************
// User: Maynard      Date: 11/28/00   Time: 12:24p
// Updated in $/ZyluxZip
// Enforce the maximum site count in the upload and in the selection
// routines.
// Reduce initial row count by 1 to compensate for added slot number
// control
// 
// *****************  Version 23  *****************
// User: Maynard      Date: 11/15/00   Time: 8:29a
// Updated in $/ZyluxZip
// Add list box to select which run to upload to, and use it in upload
// proc.
// 
// *****************  Version 22  *****************
// User: Maynard      Date: 11/14/00   Time: 10:41a
// Updated in $/ZyluxZip
// Fix for bug where unselected items transmitted by Send function
// 
// *****************  Version 21  *****************
// User: Maynard      Date: 11/09/00   Time: 4:46p
// Updated in $/ZyluxZip
// Add "true" parameter to call to UpgradeDataRowCount so that list
// control will shrink if the number of entries in list is smaller than
// the default
// Add handler for AutoInsRow, so combo and check box get added
// Add break to OnEndComboEdit
// 
// *****************  Version 20  *****************
// User: Maynard      Date: 9/26/00    Time: 9:08a
// Updated in $/ZyluxZip
// Make the grid grow to hold larger site lists when dialog first created
// Make sure the last grid row is the empty "auto-add" row before
// excluding it
// OnListSend
//   Set status messages
//   Send single-byte checksum (in upper case) instead of 2-byte as in
// docs
//   Wait and check for acknowedge message after sending data
// 
// *****************  Version 19  *****************
// User: Maynard      Date: 7/21/00    Time: 4:43p
// Updated in $/ZyluxZip
// Check for possible illegal value in New() - not seen here, but seen in
// TN!
// 
// *****************  Version 18  *****************
// User: Maynard      Date: 7/21/00    Time: 3:13p
// Updated in $/ZyluxZip
// Add error check at end of protocol upload
// 
// *****************  Version 17  *****************
// User: Maynard      Date: 7/10/00    Time: 7:22p
// Updated in $/ZyluxZip
// Even more comments
// 
// *****************  Version 16  *****************
// User: Maynard      Date: 6/08/00    Time: 7:16a
// Updated in $/ZyluxZip
// Many more comments
 * 
 * *****************  Version 15  *****************
 * User: Maynard      Date: 5/05/00    Time: 2:26p
 * Updated in $/ZyluxZip
 * Add first pass of sending data to FB14
 * 
 * *****************  Version 14  *****************
 * User: Maynard      Date: 3/22/00    Time: 10:41p
 * Updated in $/ZyluxZip
 * Fixed bug in edit function - rows inserted at wrong place
 * 
 * *****************  Version 13  *****************
 * User: Maynard      Date: 3/22/00    Time: 1:48p
 * Updated in $/ZyluxZip
 * Finish Edit button function
 * 
 * *****************  Version 12  *****************
 * User: Maynard      Date: 3/21/00    Time: 5:17p
 * Updated in $/ZyluxZip
 * Store "pressed" state of Edit button in button not static int
 * 
 * *****************  Version 11  *****************
 * User: Maynard      Date: 3/18/00    Time: 5:28p
 * Updated in $/ZyluxZip
 * Add handler for edit button push
 * 
 * *****************  Version 10  *****************
 * User: Maynard      Date: 3/17/00    Time: 1:01p
 * Updated in $/ZyluxZip
 * Implement a prompt (via a CLabel) to warn the user to provide a Run
 * Name and an Assembly name before saving the protocol
 * Abort Save operation if names are not provided
 * 
 * *****************  Version 9  *****************
 * User: Maynard      Date: 3/17/00    Time: 10:04a
 * Updated in $/ZyluxZip
 * Make check-box cells read-only so single-click always toggles their
 * state
 * Add helper routine to set up combos and check boxes
 * 
 * *****************  Version 8  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:53p
 * Updated in $/ZyluxZip
 * Add function to initialize new run protocol with site list
 * 
 * *****************  Version 7  *****************
 * User: Maynard      Date: 3/16/00    Time: 11:33p
 * Updated in $/ZyluxZip
 * Use DocTemplate resource to hold filter for file dialogs
 * Offer Run Protocol name as default for Save operation
 * Make sure filename has correct extension for Save operation
 * Update Name List if run protocol read in with Open has new name
 * 
 * *****************  Version 6  *****************
 * User: Maynard      Date: 3/15/00    Time: 1:55p
 * Updated in $/ZyluxZip
 * Set the modified flag if the run protocol or run names change
 * Always bring up SaveAs dialog box even if previously saved
 * Add filename to dialog title
 * 
 * *****************  Version 5  *****************
 * User: Maynard      Date: 3/15/00    Time: 11:43a
 * Updated in $/ZyluxZip
 * Add saving and loading of the run protocol list
 * Hook up the protocol name and run name controls
 * Update the site list selected count control when needed
 * 
 * *****************  Version 4  *****************
 * User: Maynard      Date: 3/06/00    Time: 12:26p
 * Updated in $/ZyluxZip
 * Add OnEditInsRow and OnAutoInsertRow handlers to add checkboxes to
 * first column when new rows are added
 * 
 * *****************  Version 3  *****************
 * User: Maynard      Date: 3/04/00    Time: 11:39a
 * Updated in $/ZyluxZip
 * Insert a couple of rows in OnInitDialog to help in debugging
 * Set first non-fixed column of every row to checkbox type
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/02/00    Time: 6:51p
 * Updated in $/ZyluxZip
 * Add dialog to edit protocol list
 * 
*/
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <afximpl.h> // AfxGetFileName
#include "zyluxzip.h"
#include "runprotlist.h"
#include "DlgRunProtocol.h"
#include "inplacecheck.h"
#include "grid/gridcombo.h"
#include "tty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_SELECT  1
#define COL_NAME    2
#define COL_THRESLO 3
#define COL_THRESHI 4
#define COL_SCALELO 5
#define COL_SCALEHI 6

const int MAX_SITE_COUNT = 48;

// Titles for column headers
/////////////////////////////////////////
static ZIPCOLDEF tColDefs[] = 
  {
    { 0, COL_SELECT , _T("Select\n\rSite") },
    { 0, COL_NAME   , _T("Site\n\rName") },
    { 0, COL_THRESLO, _T("Threshold\n\rLow") },
    { 0, COL_THRESHI, _T("Threshold\n\rHigh") },
    { 0, COL_SCALELO, _T("Scale\n\rLow")     },
    { 0, COL_SCALEHI, _T("Scale\n\rHigh")     },
    EndOfCols,
  };

/////////////////////////////////////////////////////////////////////////////
CDlgRunProtocol::CDlgRunProtocol(CWnd* pParent /*=NULL*/, CTTYInfo *pInfo)
	: CDlgZipList(CDlgRunProtocol::IDD, pParent)
{
  m_nInitColCount = 7;
  m_nInitRowCount = 12;
  m_Grid.SetFixedRowCount(1); // title rows
	m_pColumnDefs = tColDefs;
  m_pTTYInfo = pInfo;
	//{{AFX_DATA_INIT(CDlgRunProtocol)
	m_RunProtNameEdit = _T("");
	m_uSiteCount = 0;
	//}}AFX_DATA_INIT
  Create(IDD, pParent);
}

void CDlgRunProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDlgZipList::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRunProtocol)
	DDX_Control(pDX, IDC_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_RUN_NAME, m_NameListCombo);
	DDX_Text(pDX, IDC_RUN_ASSEMBLY, m_RunProtNameEdit);
	DDX_Text(pDX, IDC_SITE_COUNT, m_uSiteCount);
	DDX_Control(pDX, IDC_NEEDNAMES, m_lblNeedNames);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgRunProtocol, CDlgZipList)
	//{{AFX_MSG_MAP(CDlgRunProtocol)
  ON_NOTIFY(GVN_INSERTITEM, IDC_SITELIST, OnInsertRow)
  ON_COMMAND(ID_EDIT_INS_ROW, OnEditInsRow)
  ON_NOTIFY(GVN_AUTOINSERTROW, IDC_SITELIST, OnAutoInsertRow)
  ON_NOTIFY(GVN_ENDLABELEDIT,  IDC_SITELIST, OnEndComboEdit)
  ON_NOTIFY(NM_CLICK,   IDC_SITELIST, OnColumnClick)
	ON_BN_CLICKED(IDC_LIST_SAVE, OnRunProtSave)
	ON_EN_CHANGE(IDC_RUN_ASSEMBLY, OnChangeRunAssembly)
	ON_CBN_EDITCHANGE(IDC_RUN_NAME, OnEditchangeRunName)
	ON_CBN_SELCHANGE(IDC_RUN_NAME, OnSelChangeRunName)
	ON_BN_CLICKED(IDC_EDIT, OnClickEdit)
	ON_BN_CLICKED(IDC_LIST_SEND, OnListSend)
	ON_CBN_SELCHANGE(IDC_RUN_SLOT, OnChangeRunSlot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRunProtocol message handlers

// Put the special controls in the first two columns
/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::SetupCheckAndCombo(int nRow)
{
  // Make check box in first (non-fixed) column
  m_Grid.SetCellType(nRow, COL_SELECT, RUNTIME_CLASS(CInPlaceCheck));
  // Check box has to be read-only to respond to mouse clicks correctly
  UINT uState = m_Grid.GetItemState(nRow, COL_SELECT);
  m_Grid.SetItemState(nRow, COL_SELECT, uState|GVIS_READONLY);
  // Make disappearing/re-appearing combo box in second column
  m_Grid.SetCellType(nRow, COL_NAME, RUNTIME_CLASS(CGridCombo));
  CGridCell *pCell = m_Grid.GetCell(nRow, COL_NAME);
  pCell->SetOneClickEdit(true);
}

// Initial dialog setup
/////////////////////////////////////////////////////////////////////////////
BOOL CDlgRunProtocol::OnInitDialog() 
{
  BOOL bRet = CDlgZipList::OnInitDialog();
  m_lblNeedNames.SetTextColor(0x000000FF);

  m_SiteList.Load();
  UpgradeDataRowCount(m_SiteList.GetSize(), true);

  for (int i = m_Grid.GetFixedRowCount(); i < m_Grid.GetRowCount(); i++)
    SetupCheckAndCombo(i);

  CGridCombo::RemoveAll();
  for (i = 0; i < m_SiteList.GetSize(); i ++)
    {
    CString csItem = m_SiteList[i].m_csName;
    CGridCombo::AddItem(csItem);
    }
  m_NameList.Load();
  for (i = 0; i < m_NameList.GetSize(); i ++)
    {
    CString csItem = m_NameList[i].m_csName;
    m_NameListCombo.AddString(csItem);
    }
  CComboBox *pcmbSlot = (CComboBox *)GetDlgItem(IDC_RUN_SLOT);
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  int nCurSlot = pApp->GetIntSetting(IDS_CURRENT_SLOT, 0);
  pcmbSlot->SetCurSel(nCurSlot);

  m_uSiteCount = 0;
  UpdateData(FALSE); // update the dialog
  m_Grid.SetModified(FALSE);
  DoClickEdit(false);
  return bRet;
}

// Called by functions which create a new run protocol
/////////////////////////////////////////////////////////////////////////////
bool CDlgRunProtocol::New() 
{
  int j = max(0, m_Grid.GetFixedRowCount());
  for (int i = 0; i < m_SiteList.GetSize(); i++, j++)
    {
    m_Grid.SetItemText (j, COL_NAME,    m_SiteList[i].m_csName);
    m_Grid.SetItemFloat(j, COL_THRESLO, m_SiteList[i].m_ThresholdLow);
    m_Grid.SetItemFloat(j, COL_THRESHI, m_SiteList[i].m_ThresholdHigh);
    m_Grid.SetItemFloat(j, COL_SCALELO, m_SiteList[i].m_ScaleLow);
    m_Grid.SetItemFloat(j, COL_SCALEHI, m_SiteList[i].m_ScaleHigh);
    m_Grid.RedrawRow(j);
    }
  for (; j < m_Grid.GetRowCount(); j++)
    m_Grid.RedrawRow(j);

  if (i > 1)
    m_Grid.SetModified(FALSE);
  return true;
}

// Called to load a file from disk
/////////////////////////////////////////////////////////////////////////////
bool CDlgRunProtocol::Open(LPCTSTR szFileName) 
{
  CRunProtList cRunProtList;
  if (!cRunProtList.Load(szFileName))
    return false;
  UpdateTitle(szFileName);
  int nOldRowCount = m_Grid.GetRowCount();
  UpgradeDataRowCount(cRunProtList.GetSize(), false);
  m_RunProtNameEdit = cRunProtList.RunProtocolName();
  // if the name in the file is not a part of the current list
  if (CB_ERR == m_NameListCombo.SelectString(-1, cRunProtList.RunName()))
    {
    m_NameListCombo.AddString(cRunProtList.RunName());
    m_NameListCombo.SelectString(-1, cRunProtList.RunName());
    CRunName cName;
    cName.m_csName = cRunProtList.RunName();
    m_NameList.Add(cName);
    m_NameList.Save(); // update database
    }
  int nStartRow = m_Grid.GetFixedRowCount();
  for (int i = nStartRow; i < m_Grid.GetRowCount()-1; i++)
    {
    int j = i - nStartRow;
    if (j > cRunProtList.GetUpperBound())
      break;
    m_uSiteCount = j+1; // index is zero-based

    if (i >= nOldRowCount)
      SetupCheckAndCombo(i);

    CInPlaceCheck *pChk = (CInPlaceCheck *)m_Grid.GetCell(i, COL_SELECT);
    pChk->SetChecked(cRunProtList[j].m_bSelected);
    m_Grid.SetItemText( i, COL_NAME, cRunProtList[j].m_csName);
    m_Grid.SetItemFloat(i, COL_THRESLO, cRunProtList[j].m_ThresholdLow);
    m_Grid.SetItemFloat(i, COL_THRESHI, cRunProtList[j].m_ThresholdHigh);
    m_Grid.SetItemFloat(i, COL_SCALELO, cRunProtList[j].m_ScaleLow);
    m_Grid.SetItemFloat(i, COL_SCALEHI, cRunProtList[j].m_ScaleHigh);
    m_Grid.RedrawRow(i);
    }
  // if rows were added, the auto-insert row still needs a check and combo
  if (i >= nOldRowCount)
    SetupCheckAndCombo(m_Grid.GetRowCount()-1);

  ShowOrHideWarning();
  DoClickEdit(false);
  UpdateData(FALSE); // update the dialog
  m_Grid.SetModified(FALSE);
  return true;
}

// Makes sure that changes are saved before allowing dialog to close
/////////////////////////////////////////////////////////////////////////////
bool CDlgRunProtocol::OkToClose()
{
	if (m_Grid.GetModified())
    {
    int nRes = 
      AfxMessageBox("Site List has changed! Save changes?", MB_YESNOCANCEL);
    if (IDCANCEL == nRes)
      return false;
    if (IDYES == nRes)
      return SaveRunProtList();
    }
  return true;
}

// called when user uses CTRL_INS to insert a row
/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnInsertRow(NMHDR* pNMHDR, LRESULT* pResult)
{
  OnEditInsRow();
}

/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnEditInsRow() 
{
  CDlgZipList::OnEditInsRow();
  if (0 <= m_nLastInsertedRow)
    SetupCheckAndCombo(m_nLastInsertedRow);
}

/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnAutoInsertRow(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_GRIDVIEW *pNMGRID = (NM_GRIDVIEW *)pNMHDR;
  int nRow = pNMGRID->iRow;
  m_nLastInsertedRow = nRow;
  if (0 <= m_nLastInsertedRow)
    SetupCheckAndCombo(m_nLastInsertedRow);
}

/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnEndComboEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_GRIDVIEW *pNMGRID = (NM_GRIDVIEW *)pNMHDR;

  CString csSiteName = m_Grid.GetItemText(pNMGRID->iRow, pNMGRID->iColumn);
  for (int i = 0; i < m_SiteList.GetSize(); i++)
    {
    if (csSiteName == m_SiteList[i].m_csName)
      {
      int nRow = pNMGRID->iRow;
      m_Grid.SetItemFloat(nRow, COL_THRESLO, m_SiteList[i].m_ThresholdLow);
      m_Grid.SetItemFloat(nRow, COL_THRESHI, m_SiteList[i].m_ThresholdHigh);
      m_Grid.SetItemFloat(nRow, COL_SCALELO, m_SiteList[i].m_ScaleLow);
      m_Grid.SetItemFloat(nRow, COL_SCALEHI, m_SiteList[i].m_ScaleHigh);
      break;
      }
    }
}

/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_GRIDVIEW *pNMGRID = (NM_GRIDVIEW *)pNMHDR;

  if (0 == pNMGRID->iRow) // don't do selection when clicking on header
    {
    *pResult = 1; // defaults to 0 (FALSE)
    return;
    }
  if (COL_SELECT == pNMGRID->iColumn) 
    {
    if (m_uSiteCount >= MAX_SITE_COUNT) // enforce max site limit of FB14
      {
      CInPlaceCheck *pCheck = 
        (CInPlaceCheck *)m_Grid.GetCell(pNMGRID->iRow, COL_SELECT);
      if (pCheck->GetChecked()) // cell just got checked
        {
        pCheck->SetChecked(false); // uncheck it
        m_Grid.RedrawCell(pNMGRID->iRow, COL_SELECT); // redisplay
        CString sMsg;
        sMsg.Format(_T("You have chosen the maximum number of sites (%i)"), MAX_SITE_COUNT);
        AfxMessageBox(sMsg);
        *pResult = 1;
        }
      }
    // recount selected sites
    m_uSiteCount = 0;
    for (int i = m_Grid.GetFixedRowCount(); i < m_Grid.GetRowCount(); i++)
      {
      CInPlaceCheck *pCheck = 
        (CInPlaceCheck *)m_Grid.GetCell(i, COL_SELECT);
      m_uSiteCount += pCheck->GetChecked();
      }
    }
  UpdateData(FALSE); // update the dialog
}

/////////////////////////////////////////////////////////////////////////////
static bool GetSaveFileName(CString &csName)
{
  CSingleDocTemplate cTemplate(IDR_ZYLTYPE, 0, 0, 0);
  CString csFilter, csExt;
  cTemplate.GetDocString(csFilter, CDocTemplate::filterName);
  cTemplate.GetDocString(csExt, CDocTemplate::filterExt);
  csFilter = csFilter + _T("|*") + csExt + _T("||");

  CFileDialog mDlgFile(FALSE, 0, 0, OFN_NOTESTFILECREATE|OFN_HIDEREADONLY, csFilter);

  // make sure the prompt has the correct file extension
  if (csName.Right(4).CompareNoCase(csExt))
    csName += csExt;

  int nLen = _tcslen(csName);
  mDlgFile.m_ofn.lpstrTitle = _T("Save Run Protocol As:");
  mDlgFile.m_ofn.lpstrFile = csName.GetBuffer(_MAX_PATH);
  mDlgFile.m_ofn.nMaxFile = _MAX_PATH;
  ZeroMemory(mDlgFile.m_ofn.lpstrFile + nLen, _MAX_PATH-nLen);
  int oldIndex = mDlgFile.m_ofn.nFilterIndex;

  // run the file dialog
  bool bResult = mDlgFile.DoModal() == IDOK ? true : false;
  csName.ReleaseBuffer();
  // make sure the chosen filename has the correct extension
  if (csName.Right(4).CompareNoCase(csExt))
    csName += csExt;
  return bResult;
}

// Does the actual action of saving data to the run protocol file
/////////////////////////////////////////////////////////////////////////////
bool CDlgRunProtocol::SaveRunProtList()
{
  UpdateData(TRUE); // get data from dialog

  CString csName;
  m_NameListCombo.GetWindowText(csName);
  if (m_RunProtNameEdit.IsEmpty() || csName.IsEmpty())
    {
    AfxMessageBox(_T("You must enter a Run Assembly name and a Run Name\n\r"
                     "before saving the Run Protocol."));
    m_lblNeedNames.FlashText(TRUE);
    return false;
    }

  CRunProtList runProtList;
  int nSelected = LoadRunProtList(runProtList);
  if (!nSelected)
    {
    AfxMessageBox(_T("No sites are selected!\n\r"
                     "Select one or more sites before saving the Run Protocol."),
                  MB_OK|MB_ICONSTOP);
    return false;
    }
  if (m_csLocalFileName.IsEmpty()) // if no filename yet
    m_csLocalFileName = m_RunProtNameEdit; // get filename from run protocol name
//  if (!m_csLocalFileName.IsEmpty() || GetSaveFileName(m_csLocalFileName))
  if (GetSaveFileName(m_csLocalFileName)) // get permission and choose filename
    {
    if (runProtList.SaveAs(m_csLocalFileName)) // do the save
      {
      m_Grid.SetModified(FALSE); // if saved, mark not modified
      SetDlgItemText(IDCANCEL, _T("&Close")); // can't cancel now
      UpdateTitle(m_csLocalFileName); // change title
      return true;
      }
    else
      return false;
    }
  return false;
}

// Runs when Save button is clicked
/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnRunProtSave() 
{
  SaveRunProtList();
}

// Called by functions which save or load run protocol files
/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::UpdateTitle(LPCTSTR szFileName)
{
  m_csLocalFileName = szFileName;
  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  CRecentFileList *pList = pApp->GetRecentFileList();
  pList->Add(szFileName);
  TCHAR szTitle[22];
  AfxGetFileName(szFileName, szTitle, sizeof(szTitle));
  m_Title.SetWindowText(m_csBasicTitle + ": " + szTitle);
}

// Series of functions to show a warning if the Protocol doesn't have
// a name or a Run Name
/////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::ShowOrHideWarning() 
{
  CString csName;
  m_NameListCombo.GetWindowText(csName);
  int nLen = m_NameListCombo.GetLBTextLen(m_NameListCombo.GetCurSel());
  int nCmdShow = m_RunProtNameEdit.IsEmpty() || 
                 (0 >= nLen && csName.IsEmpty()) ? SW_SHOW : SW_HIDE;
  m_lblNeedNames.FlashText(FALSE);
  m_lblNeedNames.ShowWindow(nCmdShow);
}

void CDlgRunProtocol::OnChangeRunAssembly() 
{
  UpdateData(TRUE);
  ShowOrHideWarning();
  m_Grid.SetModified(TRUE);	
}

void CDlgRunProtocol::OnEditchangeRunName() 
{
  UpdateData(TRUE);
  CString csName;
  m_NameListCombo.GetWindowText(csName);
  if (csName.IsEmpty())
    m_NameListCombo.SetCurSel(-1);
  ShowOrHideWarning();
  m_Grid.SetModified(TRUE);	
}

void CDlgRunProtocol::OnSelChangeRunName() 
{
  UpdateData(TRUE);
  ShowOrHideWarning();
  m_Grid.SetModified(TRUE);	
}

void CDlgRunProtocol::OnClickEdit() 
{
  int nChecked = m_btnEdit.GetCheck();
  DoClickEdit(nChecked == 0);
}

static SetRowReadOnly(CGridCtrl *pGrid, int nRow, bool bReadOnly)
{
  for (int i = 1; i < _countof(tColDefs)-1; i++)
    {
    int nCol = tColDefs[i].nCol;
    DWORD dwState = pGrid->GetItemState(nRow, nCol);
    if (bReadOnly)
      dwState |= GVIS_READONLY;
    else
      dwState &= ~GVIS_READONLY;
    pGrid->SetItemState(nRow, nCol, dwState);
    }
}

// Set up the grid to allow/disallow editing
//////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::DoClickEdit(bool bEnable) 
{
  m_btnEdit.SetCheck(bEnable);
  // if enabling editing, need to display all of the site list entries,
  // not just those already included in the protocol
  ////////////////////////////////////////////////////////////////////////
  if (bEnable) 
    {
    // use hash table to speed up adding non-existent entries
    CMap<DWORD, DWORD, LPCTSTR, LPCTSTR&> SetMap;
    SetMap.InitHashTable(m_Grid.GetRowCount()*5);
    int j = m_Grid.GetFixedRowCount();
    // load up hash set with existing entries
    for (int i = j; i < m_Grid.GetRowCount(); i++)
      {
      SetRowReadOnly(&m_Grid, i, false);
      CString csName = m_Grid.GetItemText(i, COL_NAME);
      if (!csName.IsEmpty())
        {
        j = i+1; // track row after last non-empty row
        SetMap[HashKey((LPCTSTR)csName)] = csName;
        }
      }
    // Now add entries from site list which don't exist yet
    for (i = 0; i < m_SiteList.GetSize(); i++)
      {
      CString csName = m_SiteList[i].m_csName;
      LPCTSTR pSz = csName;
      if (!SetMap.Lookup(HashKey(pSz), pSz))
        {
        int k = m_Grid.InsertRow(GRID_AUTOINSERT_STRING, j++); 
        RenumberRows(k-1);
        SetupCheckAndCombo(k);
        CSite tSite = m_SiteList[i];
        m_Grid.SetItemText( k, COL_NAME,    tSite.m_csName);
        m_Grid.SetItemFloat(k, COL_THRESLO, tSite.m_ThresholdLow);
        m_Grid.SetItemFloat(k, COL_THRESHI, tSite.m_ThresholdHigh);
        m_Grid.SetItemFloat(k, COL_SCALELO, tSite.m_ScaleLow);
        m_Grid.SetItemFloat(k, COL_SCALEHI, tSite.m_ScaleHigh);
        }
      }
    }
  else // just disable editing
    {
    for (int i = m_Grid.GetFixedRowCount(); i < m_Grid.GetRowCount(); i++)
      {
      SetRowReadOnly(&m_Grid, i, true);
      }
    }
};

// move data from grid into a CRunProtList object
//////////////////////////////////////////////////////////////////////////
int CDlgRunProtocol::LoadRunProtList(CRunProtList &runProtList)
{
  int nSelected = 0;
  CString csTemp;
  runProtList.RemoveAll();
  m_NameListCombo.GetWindowText(csTemp);
  runProtList.RunProtocolName(m_RunProtNameEdit);
  runProtList.RunName(csTemp);
  int nRows = m_Grid.GetRowCount();
  CGridCell *pCell = m_Grid.GetCell(nRows-1, 0);
#ifdef _DEBUG
  LPCTSTR pTxt = pCell->GetText();
#endif
  // if last row is the empty "auto-add" row (which should always be true)
  // exclude it from the list
  if (pCell && pCell->GetText() && '*' == pCell->GetText()[0])
    nRows -= 1;

  for (int i = m_Grid.GetFixedRowCount(); i < nRows; i++)
    {
    csTemp = m_Grid.GetItemText(i, COL_NAME);
    if (!csTemp.IsEmpty())
      {
      LPTSTR pDummy;
      CRunProtItem tProtItem;
      tProtItem.m_csName = csTemp;
      tProtItem.m_ThresholdLow =  _tcstod(m_Grid.GetItemText(i, COL_THRESLO), &pDummy);
      tProtItem.m_ThresholdHigh = _tcstod(m_Grid.GetItemText(i, COL_THRESHI), &pDummy);
      tProtItem.m_ScaleLow =      _tcstod(m_Grid.GetItemText(i, COL_SCALELO), &pDummy);
      tProtItem.m_ScaleHigh =     _tcstod(m_Grid.GetItemText(i, COL_SCALEHI), &pDummy);
      CInPlaceCheck *pCheck = (CInPlaceCheck *)m_Grid.GetCell(i, COL_SELECT);
      tProtItem.m_bSelected = pCheck->GetChecked();
      nSelected += tProtItem.m_bSelected;
      runProtList.Add(tProtItem);
      }
    }
  return nSelected;
}

// wait for given number of milliseconds
//////////////////////////////////////////////////////////////////////////
static void TimePause(int nPeriod)
{
  DWORD       dwStartTime;
  DWORD       dwCurrentTime;

  dwStartTime = GetTickCount();
  do
    {
    dwCurrentTime = GetTickCount();
    } 
  while ((int) (dwCurrentTime - dwStartTime) < nPeriod);
}

/****************************************************************************
Protocol Specification for FB14 RUN-Upload.
-----------------------------------------------------------------------------
!  			start data transmission
R	  		download assembled run to FB14
space  
X			ID of run in FB14 to be replaced (A,B,C,D,E,F,G,H,I,J)
space
rrrrrrrrrr		10 digit new run name  
space
ssssssss01		10 digit site-1 name  
L01			3 digit low threshold for site-1  
H01			3 digit high threshold for site-1  
ssssssss02		10 digit site-2 name
L02			3 digit low threshold for site-2
H02			3 digit high threshold for site-2
...
ssssssss48		10 digit site-48 name
L48			3 digit low threshold for site-48
H48			3 digit high threshold for site-48
space
check sum high byte
check sum low byte
carriage return/line feed

After the FB14 has received a complete string with correct check sum,
it sends an acknowledge:

!	Hex:	21
R				52
space		20
9				39
3				33
carriage return	0D
line feed			  0A
                         this is really at offset
                             16 + 48 * 16 = 784-|
                                                |
          1         2         3         4       V 5
0123456789012345678901234567890123456789012345678901234
!R X 0123456789 0123456789LLLHHH0123456789LLLHHH cHcLRN
                                                ^
****************************************************************************/
const int nLineLength = 10 + 3 + 3; // site name + lo thresh + high thresh
// header to send first
const CHAR cRunID[] = { '!', 'R', ' ', 'A', ' ' }; // always "RUN-A" for now
// checksum as {SPC}XX{CR}{LF}
const CHAR FBTerm[] = { ' ', 'H', 'L', '\r', '\n' };
// ack response from FB14
const CHAR ACK_MSG[] = { '!', 'R',  ' ', '9', '3', '\r', '\n' };
////////////////////////////////////////////////////////////////////////////
void CDlgRunProtocol::OnListSend() 
{
  CWaitCursor Wait;
  if (m_pTTYInfo) // if TTY connector supplied
    {
    BOOL bWasConnected = m_pTTYInfo->fConnected;
    if (!bWasConnected &&              // if not connected already
        !m_pTTYInfo->OpenConnection()) // if couldn't open connection
      {
      AfxMessageBox("Couldn't connect to FB14: Check serial settings.", 
        MB_OK|MB_ICONSTOP);
      return;
      }
    CFrameWnd *pWnd = (CFrameWnd *)AfxGetMainWnd();
    pWnd->SetMessageText("Sending Data");

    int nCurSlot = 0;
      {
      CComboBox *pcmbSlot = (CComboBox *)GetDlgItem(IDC_RUN_SLOT);
      if (pcmbSlot)
        nCurSlot = pcmbSlot->GetCurSel();
      }

    CRunProtList runProtList;
    int nSelected = LoadRunProtList(runProtList); // number of valid entries
    if (nSelected) // if no entries selected, don't download
      {
      // signature + run name + spc after run name + checksum bytes + site data
      int nBufSize = 
        sizeof(cRunID)+10+1+sizeof(FBTerm) + (nLineLength * MAX_SITE_COUNT);
      CHAR *lpBuf = new CHAR[nBufSize+1]; // allow for trailing NUL of sprintf
      ZeroMemory(lpBuf, nBufSize+1);
      // copy upload command and ID or Assembly to overwrite
      LPTSTR pBuf = strcpy(lpBuf, cRunID) + strlen(lpBuf);
      lpBuf[3] = 'A' + nCurSlot;
      // append new assembly name, padded with spaces, plus one
      // extra trailing space--------v
      pBuf += sprintf(pBuf, "%-10.10s ", runProtList.RunName());
      // Add Site Name and thresholds for each site
      CString csLow, csHigh;
      int j = 0;
      for (int i = 0; i < min(MAX_SITE_COUNT, runProtList.GetSize()); i++)
        {
        CRunProtItem cItem = runProtList[i];
        if (!cItem.m_bSelected)
          continue;
        j++;
        csLow.Format ("%g", cItem.m_ThresholdLow);
        csHigh.Format("%g", cItem.m_ThresholdHigh);
        pBuf += 
          sprintf(pBuf, "%-10.10s%-3.3s%-3.3s", cItem.m_csName, csLow, csHigh);
        }
      // fill remaining (unused) entries with space characters
      for (i = j; i < MAX_SITE_COUNT; i++)
        pBuf += sprintf(pBuf, "%-16.16s", " ");

      *pBuf++ = ' '; // add one more space before checksum
      int nChkSum = 0;
      for (LPTSTR pChar = lpBuf; pChar < pBuf; pChar++)
        nChkSum += *pChar; // compute checksum

      // convert checksum to ASCII and store plus final CR/LF
      pBuf += sprintf(pBuf, "%2.2X\r\n", nChkSum & 0xFF);
      // debug runtime check that the counts are right
      ASSERT((pBuf - lpBuf) == nBufSize);
#ifdef _DEBUG // write file for debugging
      CFile fDbgOut("c:\\zdbgout.txt", CFile::modeCreate | CFile::modeWrite);
      fDbgOut.Write(lpBuf, nBufSize);
      fDbgOut.Flush();
      fDbgOut.Close();
#endif
      // Send the Data!!!
      m_pTTYInfo->m_cbInCount = 0; // reset buffer pointer
      if (!m_pTTYInfo->WriteCommBlock(lpBuf, nBufSize))
        {
        AfxMessageBox("Error sending data to FB14.", 
          MB_OK|MB_ICONSTOP);
        }
      else
        {
        pWnd->SetMessageText("Waiting for response");
        TimePause(1000);    // Wait for response to arrive; FB14 is SLOW
        if (m_pTTYInfo->m_cbInCount != (int)(nBufSize + sizeof(ACK_MSG)))
          AfxMessageBox("FB14 did not acknowledge upload", MB_OK|MB_ICONSTOP);
        else
          AfxMessageBox("Upload successful!", MB_OK);
        } // if WriteComBlock sucessful
      delete lpBuf;
      } // if any entries selected
    if (!bWasConnected && m_pTTYInfo->fConnected)
      m_pTTYInfo->CloseConnection();
    pWnd->SetMessageText("Ready");
    }
}

void CDlgRunProtocol::OnChangeRunSlot() 
{
  CComboBox *pcmbSlot = (CComboBox *)GetDlgItem(IDC_RUN_SLOT);
  int nCurSlot = pcmbSlot->GetCurSel();

  CZyluxZipApp *pApp = (CZyluxZipApp *)AfxGetApp();
  pApp->SetIntSetting(IDS_CURRENT_SLOT, nCurSlot);
	
}
