// PPSerial.cpp : implementation file
// CPPSerial property page is for serial port settings
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
/*
* $History: PPSerial.cpp $ * 
 * 
 * *****************  Version 2  *****************
 * User: Maynard      Date: 3/23/00    Time: 1:42p
 * Updated in $/ZyluxZip
 * 
 * *****************  Version 1  *****************
 * User: Maynard      Date: 3/23/00    Time: 11:45a
 * Created in $/ZyluxZip
*/

#include "stdafx.h"
#include "ZyluxZip.h"
#include "resource.h"
#include "tty.h"
#include "PPSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))

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
  m_pTTYInfo = 0;
}

CPPSerial::CPPSerial(class CTTYInfo *pInfo) : CMMPropPage(CPPSerial::IDD)
{
  m_pTTYInfo = pInfo;
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
  WORD wCount, wMaxCOM = MAXPORTS, wPosition;

  // load the COM prefix from resources
  csTemp.LoadString(IDS_COMPREFIX);
  CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_PORTCB);
  ASSERT(pCombo);
  // fill port combo box and make initial selection
  for (wCount = 0; wCount < wMaxCOM; wCount++)
    {
    csBuffer.Format("%s%d", csTemp, wCount + 1);
    pCombo->AddString(csBuffer);
    }

  pCombo->SetCurSel(m_pTTYInfo->bPort - 1);
  // disable COM port combo box if connection has already been
  // established (e.g. OpenComm() already successful)
  pCombo->EnableWindow(!m_pTTYInfo->fConnected);
  // fill baud combo box and make initial selection
  FillComboBox(IDC_BAUDCB, IDS_BAUD110, BaudTable, _countof(BaudTable),
               m_pTTYInfo->dwBaudRate);
  pCombo = (CComboBox *)GetDlgItem(IDC_DATABITSCB);
  // fill data bits combo box and make initial selection
  for (wCount = 5; wCount < 9; wCount++)
    {
    csBuffer.Format("%d", wCount);
    wPosition = pCombo->AddString(csBuffer);
    // if current selection, tell the combo box
    if (wCount == m_pTTYInfo->bByteSize)
      pCombo->SetCurSel(wPosition);
    }
  // fill parity combo box and make initial selection
  FillComboBox(IDC_PARITYCB, IDS_PARITYNONE, ParityTable,
               _countof(ParityTable), m_pTTYInfo->bParity);
  // fill stop bits combo box and make initial selection
  FillComboBox(IDC_STOPBITSCB, IDS_ONESTOPBIT, StopBitsTable,
                _countof(StopBitsTable), m_pTTYInfo->bStopBits);
  // initalize the flow control settings
  CheckDlgButton(IDC_DTRDSR, (m_pTTYInfo->bFlowCtrl & FC_DTRDSR) > 0);
  CheckDlgButton(IDC_RTSCTS, (m_pTTYInfo->bFlowCtrl & FC_RTSCTS) > 0);
  CheckDlgButton(IDC_XONXOFF,(m_pTTYInfo->bFlowCtrl & FC_XONXOFF) > 0);
  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Handle OK button 
//////////////////////////////////////////////////////////////////////////
void CPPSerial::OnOK() 
{
  m_pTTYInfo->bPort = (BYTE)GetComboItemSel(IDC_PORTCB) + 1;
  // get baud rate selection
  DWORD wSelection = GetComboItemSel(IDC_BAUDCB);
  m_pTTYInfo->dwBaudRate = GetComboItemData(IDC_BAUDCB, wSelection);
  // get data bits selection
  m_pTTYInfo->bByteSize = (BYTE)GetComboItemSel(IDC_DATABITSCB) + 5;
  // get parity selection
  wSelection = GetComboItemSel(IDC_PARITYCB);
  m_pTTYInfo->bParity = (BYTE)GetComboItemData(IDC_PARITYCB, wSelection);
  // get stop bits selection
  wSelection = GetComboItemSel(IDC_STOPBITSCB);
  m_pTTYInfo->bStopBits = (BYTE)GetComboItemData(IDC_STOPBITSCB, wSelection);
  // get flow control settings
  m_pTTYInfo->bFlowCtrl = 0;

  if (IsDlgButtonChecked(IDC_DTRDSR))
    m_pTTYInfo->bFlowCtrl |= FC_DTRDSR;
  if (IsDlgButtonChecked(IDC_RTSCTS))
    m_pTTYInfo->bFlowCtrl |= FC_RTSCTS;
  if (IsDlgButtonChecked(IDC_XONXOFF))
    m_pTTYInfo->bFlowCtrl |= FC_XONXOFF;

	CMMPropPage::OnOK();
}
