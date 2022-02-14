; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ZyluxCap.h"
LastPage=0

ClassCount=20
Class1=CZyluxFormAutoProxy
Class2=CDlgSettings
Class3=CZyluxCapApp
Class4=CMMStatusBar
Class5=CZyluxCapDlg
Class6=CWndData
Class7=CWndTTY
Class8=CEditData
Class9=CEdtData
Class10=CMainFrame

ResourceCount=13
Resource1=IDD_PP_APP
Resource2=TTYACCEL
Resource3=IDD_PP_DATAWIN
Resource4=IDD_DATAWIN
Resource5=IDD_SERIAL
Resource6=IDD_PP_SERIAL
Class11=CZyluxForm
Resource7=IDD_PP_XFER
Resource8=IDD_ABOUTBOX (_ZYLUX_NORMAL)
Resource9=IDD_XFER
Class12=CPPApp
Class13=CPPDataWin
Class14=CPPXfer
Resource10=TTYMENU
Resource11=IDD_ABOUTBOX (_ZYLUX_BRITISH)
Class15=CPPSerial
Class16=CPSSettings
Class17=CMMPropPage
Class18=MMPropSheet
Class19=CEdtCol
Class20=CEdtRow
Resource12=IDD_ZYLUXCAP_DIALOG
Resource13=IDR_MAINFRAME

[CLS:CDlgSettings]
Type=0
BaseClass=CDialog
HeaderFile=DlgSettings.h
ImplementationFile=DlgSettings.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgSettings

[CLS:CZyluxCapApp]
Type=0
BaseClass=CWinApp
HeaderFile=ZyluxCap.h
ImplementationFile=ZyluxCap.cpp
LastObject=CZyluxCapApp
Filter=N

[CLS:CZyluxCapDlg]
Type=0
BaseClass=CDialog
HeaderFile=ZyluxCapDlg.h
ImplementationFile=ZyluxCapDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHK_CONNECT

[CLS:CWndData]
Type=0
BaseClass=CDialog
HeaderFile=WndData.h
ImplementationFile=WndData.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LOADFILE

[CLS:CWndTTY]
Type=0
BaseClass=CWnd
HeaderFile=WndTTY.h
ImplementationFile=WndTTY.cpp
LastObject=CWndTTY

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrame.h
ImplementationFile=MainFrame.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[DLG:IDD_ZYLUXCAP_DIALOG]
Type=1
Class=CZyluxCapDlg
ControlCount=1
Control1=IDC_CHK_CONNECT,button,1342242822

[DLG:IDD_DATAWIN]
Type=1
Class=CWndData
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_TTYDATA,edit,1353781444
Control3=IDC_PUSH,button,1342242817
Control4=IDC_LOADFILE,button,1342242817

[ACL:TTYACCEL]
Type=1
Class=?
Command1=IDM_SENDBLOCK
Command2=IDM_DISCONNECT
Command3=IDM_CONNECT
CommandCount=3

[MNU:TTYMENU]
Type=1
Class=?
Command1=IDM_CONNECT
Command2=IDM_DISCONNECT
Command3=IDM_EXIT
Command4=IDM_SETTINGS
Command5=IDM_ABOUTBOX
CommandCount=5

[CLS:CEditData]
Type=0
HeaderFile=EditData.h
ImplementationFile=EditData.cpp
BaseClass=CEdit
Filter=W
LastObject=CEditData
VirtualFilter=WC

[CLS:CEdtData]
Type=0
HeaderFile=EdtData.h
ImplementationFile=EdtData.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CEdtData

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_CONNECT
Command2=IDM_DISCONNECT
Command3=IDM_EXIT
Command4=IDM_SETTINGS
Command5=IDM_ABOUTBOX
CommandCount=5

[CLS:CMMStatusBar]
Type=0
HeaderFile=MMStatusBar.h
ImplementationFile=MMStatusBar.cpp
BaseClass=CStatusBar
Filter=W
LastObject=CMMStatusBar

[CLS:CZyluxForm]
Type=0
HeaderFile=ZyluxForm.h
ImplementationFile=ZyluxForm.cpp
BaseClass=CFormView
Filter=D
LastObject=CZyluxForm
VirtualFilter=VWC

[DLG:IDD_PP_SERIAL]
Type=1
Class=CPPSerial
ControlCount=14
Control1=IDC_STATIC,static,1342308354
Control2=IDD_PORTCB,combobox,1344340483
Control3=IDC_STATIC,static,1342177282
Control4=IDD_BAUDCB,combobox,1344340483
Control5=IDC_STATIC,static,1342177282
Control6=IDD_DATABITSCB,combobox,1344340483
Control7=IDC_STATIC,static,1342177282
Control8=IDD_PARITYCB,combobox,1344340483
Control9=IDC_STATIC,static,1342177282
Control10=IDD_STOPBITSCB,combobox,1344340483
Control11=IDD_DTRDSR,button,1342242819
Control12=IDD_RTSCTS,button,1342177283
Control13=IDD_XONXOFF,button,1342177283
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_PP_DATAWIN]
Type=1
Class=CPPDataWin
ControlCount=5
Control1=IDD_AUTOWRAP,button,1342242819
Control2=IDD_NEWLINE,button,1342177283
Control3=IDD_LOCALECHO,button,1342177283
Control4=IDD_DISPLAYERRORS,button,1342177283
Control5=IDD_FONT,button,1342373888

[DLG:IDD_PP_XFER]
Type=1
Class=CPPXfer
ControlCount=14
Control1=IDC_CHK_FILE,button,1342242819
Control2=IDC_EDT_FILE,edit,1350631552
Control3=IDC_CHK_REPFILE,button,1342242819
Control4=IDC_CHK_SHEET,button,1342242819
Control5=IDC_EDT_SHEET,edit,1350631552
Control6=IDC_CHK_RANGE,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDT_RANGECOL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDT_RANGEROW,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SLDDELAY,msctls_trackbar32,1342242821
Control13=IDC_DELTIME,static,1342308352
Control14=IDC_ERRMSG,static,1342308352

[DLG:IDD_PP_APP]
Type=1
Class=CPPApp
ControlCount=2
Control1=IDD_AUTOCONNECT,button,1342177283
Control2=IDD_AUTOQUIT,button,1342177283

[CLS:CPPApp]
Type=0
HeaderFile=PPApp.h
ImplementationFile=PPApp.cpp
BaseClass=CMMPropPage
Filter=D
LastObject=CPPApp

[CLS:CPPDataWin]
Type=0
HeaderFile=PPDataWin.h
ImplementationFile=PPDataWin.cpp
BaseClass=CMMPropPage
Filter=D
LastObject=CPPDataWin

[CLS:CPPXfer]
Type=0
HeaderFile=PPXfer.h
ImplementationFile=PPXfer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDT_RANGEROW
VirtualFilter=dWC

[DLG:IDD_XFER]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SLDDELAY,msctls_trackbar32,1342242821
Control3=IDC_DELTIME,static,1342308352
Control4=IDC_EDT_RANGE,edit,1350631552
Control5=IDC_EDT_RANGE2,edit,1350631552
Control6=IDC_CHK_RANGE,button,1342242819
Control7=IDC_CHK_FILE,button,1342242819

[DLG:IDD_SERIAL]
Type=1
Class=?
ControlCount=29
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308354
Control3=IDD_PORTCB,combobox,1344340483
Control4=IDC_STATIC,static,1342177282
Control5=IDD_BAUDCB,combobox,1344340483
Control6=IDC_STATIC,static,1342177282
Control7=IDD_DATABITSCB,combobox,1344340483
Control8=IDC_STATIC,static,1342177282
Control9=IDD_PARITYCB,combobox,1344340483
Control10=IDC_STATIC,static,1342177282
Control11=IDD_STOPBITSCB,combobox,1344340483
Control12=IDC_STATIC,static,1342177282
Control13=IDD_DTRDSR,button,1342242819
Control14=IDD_RTSCTS,button,1342177283
Control15=IDD_XONXOFF,button,1342177283
Control16=IDC_STATIC,button,1342308359
Control17=IDD_AUTOWRAP,button,1342242819
Control18=IDD_NEWLINE,button,1342177283
Control19=IDD_LOCALECHO,button,1342177283
Control20=IDD_DISPLAYERRORS,button,1342177283
Control21=IDD_FONT,button,1342373888
Control22=IDC_STATIC,static,1342308352
Control23=IDC_SLDDELAY,msctls_trackbar32,1342242821
Control24=IDC_DELTIME,static,1342308352
Control25=IDC_STATIC,button,1342177287
Control26=IDD_AUTOCONNECT,button,1342177283
Control27=IDD_AUTOQUIT,button,1342177283
Control28=IDOK,button,1342242817
Control29=IDCANCEL,button,1342242816

[CLS:CPPSerial]
Type=0
HeaderFile=PPSerial.h
ImplementationFile=PPSerial.cpp
BaseClass=CDialog
Filter=D
LastObject=CPPSerial

[CLS:CPSSettings]
Type=0
HeaderFile=PSSettings.h
ImplementationFile=PSSettings.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC

[CLS:CMMPropPage]
Type=0
HeaderFile=MMPropPage.h
ImplementationFile=MMPropPage.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:MMPropSheet]
Type=0
HeaderFile=MMPropSheet.h
ImplementationFile=MMPropSheet.cpp
BaseClass=CPropertySheet
Filter=W

[CLS:CEdtCol]
Type=0
HeaderFile=EdtCol.h
ImplementationFile=EdtCol.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CEdtCol

[CLS:CEdtRow]
Type=0
HeaderFile=EdtRow.h
ImplementationFile=EdtRow.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[DLG:IDD_ABOUTBOX (_ZYLUX_NORMAL)]
Type=1
Class=CMMPropPage
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_APPNAME,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_VERINFO,static,1342308480

[DLG:IDD_ABOUTBOX (_ZYLUX_BRITISH)]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_APPNAME,static,1342308480
Control4=IDC_VERINFO,static,1342308480

[CLS:CZyluxFormAutoProxy]
Type=0
HeaderFile=dlgproxy.h
ImplementationFile=dlgproxy.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C
LastObject=CZyluxFormAutoProxy

