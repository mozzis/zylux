// PPSerial.cpp : implementation file
// CPPSerial property page is for serial port settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPSerial.cpp $ * 
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 4/13/99    Time: 2:12a
 * Created in $/ZyluxCap/2.0
*/

#include "stdafx.h"
#include "ZyluxCap.h"
#include "PPSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const DWORD BaudTable[] =
{
  CBR_110,   CBR_300,    CBR_600,   CBR_1200,  CBR_2400,
  CBR_4800,  CBR_9600,   CBR_14400, CBR_19200, CBR_38400,
  CBR_56000, CBR_128000, CBR_256000
};

static const DWORD ParityTable[] =
{
  NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY
};

static const DWORD StopBitsTable[] =
{
  ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS
};


/////////////////////////////////////////////////////////////////////////////
// CPPSerial property page

IMPLEMENT_DYNCREATE(CPPSerial, CMMPropPage)

void CPPSerial::CommonConstruct()
{
  //{{AFX_DATA_INIT(CPPSerial)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPSerial::CPPSerial() : CMMPropPage(CPPSerial::IDD)
{
}

CPPSerial::CPPSerial(CTTYInfo *pI) : CMMPropPage(CPPSerial::IDD, pI)
{
}

CPPSerial::~CPPSerial()
{
}

void CPPSerial::DoDataExchange(CDataExchange* pDX)
{
	CMMPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPSerial)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPSerial, CMMPropPage)
	//{{AFX_MSG_MAP(CPPSerial)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPSerial message handlers

//////////////////////////////////////////////////////////////////////////
BOOL CPPSerial::OnInitDialog() 
{
  CMMPropPage::OnInitDialog();
  CString csBuffer, csTemp;
  CTTYInfo *pInfo = GetInfo();
  WORD wCount, wMaxCOM = MAXPORTS, wPosition;

  // load the COM prefix from resources
  csTemp.LoadString(IDS_COMPREFIX);
  CComboBox *pCombo = (CComboBox *)GetDlgItem(IDD_PORTCB);
  ASSERT(pCombo);
  // fill port combo box and make initial selection
  for (wCount = 0; wCount < wMaxCOM; wCount++)
    {
    csBuffer.Format("%s%d", csTemp, wCount + 1);
    pCombo->AddString(csBuffer);
    }

  pCombo->SetCurSel(pInfo->bPort - 1);
  // disable COM port combo box if connection has already been
  // established (e.g. OpenComm() already successful)
  pCombo->EnableWindow(!pInfo->fConnected);
  // fill baud combo box and make initial selection
  FillComboBox(IDD_BAUDCB, IDS_BAUD110, BaudTable, countof(BaudTable),
               pInfo->dwBaudRate);
  pCombo = (CComboBox *)GetDlgItem(IDD_DATABITSCB);
  // fill data bits combo box and make initial selection
  for (wCount = 5; wCount < 9; wCount++)
    {
    csBuffer.Format("%d", wCount);
    wPosition = pCombo->AddString(csBuffer);
    // if current selection, tell the combo box
    if (wCount == pInfo->bByteSize)
      pCombo->SetCurSel(wPosition);
    }
  // fill parity combo box and make initial selection
  FillComboBox(IDD_PARITYCB, IDS_PARITYNONE, ParityTable,
               countof(ParityTable), pInfo->bParity);
  // fill stop bits combo box and make initial selection
  FillComboBox(IDD_STOPBITSCB, IDS_ONESTOPBIT, StopBitsTable,
                countof(StopBitsTable), pInfo->bStopBits);
  // initalize the flow control settings
  CheckDlgButton(IDD_DTRDSR, (pInfo->bFlowCtrl & FC_DTRDSR) > 0);
  CheckDlgButton(IDD_RTSCTS, (pInfo->bFlowCtrl & FC_RTSCTS) > 0);
  CheckDlgButton(IDD_XONXOFF,(pInfo->bFlowCtrl & FC_XONXOFF) > 0);
  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Handle OK button 
//////////////////////////////////////////////////////////////////////////
void CPPSerial::OnOK() 
{
  CTTYInfo *pInfo = GetInfo();
  pInfo->bPort = (BYTE)GetComboItemSel(IDD_PORTCB) + 1;
  // get baud rate selection
  DWORD wSelection = GetComboItemSel(IDD_BAUDCB);
  pInfo->dwBaudRate = GetComboItemData(IDD_BAUDCB, wSelection);
  // get data bits selection
  pInfo->bByteSize = (BYTE)GetComboItemSel(IDD_DATABITSCB) + 5;
  // get parity selection
  wSelection = GetComboItemSel(IDD_PARITYCB);
  pInfo->bParity = (BYTE)GetComboItemData(IDD_PARITYCB, wSelection);
  // get stop bits selection
  wSelection = GetComboItemSel(IDD_STOPBITSCB);
  pInfo->bStopBits = (BYTE)GetComboItemData(IDD_STOPBITSCB, wSelection);
  // get flow control settings
  pInfo->bFlowCtrl = 0;

  if (IsDlgButtonChecked(IDD_DTRDSR))
    pInfo->bFlowCtrl |= FC_DTRDSR;
  if (IsDlgButtonChecked(IDD_RTSCTS))
    pInfo->bFlowCtrl |= FC_RTSCTS;
  if (IsDlgButtonChecked(IDD_XONXOFF))
    pInfo->bFlowCtrl |= FC_XONXOFF;

	CMMPropPage::OnOK();
}
