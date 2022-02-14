; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgZipList
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "zyluxzip.h"
LastPage=0

ClassCount=27
Class1=CDlgNameList
Class2=CZyluxZipDlgAutoProxy
Class3=CDlgRunProtocol
Class4=CDlgSiteList
Class5=CDlgZipList
Class6=CEdtData
Class7=CGridCtrl
Class8=CGridDropTarget
Class9=CInPlaceEdit
Class10=CComboEdit
Class11=CInPlaceList
Class12=CTitleTip
Class13=CGridRunProt
Class14=CGridZip
Class15=CLabel
Class16=CAboutDlg
Class17=CMainFrame
Class18=CMMPropPage
Class19=CMMStatusBar
Class20=CMyListCtrl
Class21=CPPApp
Class22=CPPDataWin
Class23=CPPSerial
Class24=CPSSettings
Class25=CWndData
Class26=CZyluxZipApp
Class27=CZyluxZipDlg

ResourceCount=11
Resource1=IDD_SITELIST
Resource2=IDD_ABOUTBOX
Resource3=IDD_PP_DATAWIN
Resource4=IDD_RUN_PROTOCOL
Resource5=IDD_DATAWIN
Resource6=IDD_PP_APP
Resource7=IDD_ZYLUXZIP_DIALOG
Resource8=IDD_NAMELIST
Resource9=IDR_MENU_CONTEXT
Resource10=IDD_PP_SERIAL
Resource11=IDR_MAINFRAME

[CLS:CDlgNameList]
Type=0
BaseClass=CDlgZipList
HeaderFile=DlgNameList.h
ImplementationFile=DlgNameList.cpp

[CLS:CZyluxZipDlgAutoProxy]
Type=0
BaseClass=CCmdTarget
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp

[CLS:CDlgRunProtocol]
Type=0
BaseClass=CDlgZipList
HeaderFile=DlgRunProtocol.h
ImplementationFile=DlgRunProtocol.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_RUN_SLOT

[CLS:CDlgSiteList]
Type=0
BaseClass=CDlgZipList
HeaderFile=DlgSiteList.h
ImplementationFile=DlgSiteList.cpp

[CLS:CDlgZipList]
Type=0
BaseClass=CDialog
HeaderFile=DlgZipList.h
ImplementationFile=DlgZipList.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgZipList

[CLS:CEdtData]
Type=0
BaseClass=CEdit
HeaderFile=EdtData.h
ImplementationFile=EdtData.cpp

[CLS:CGridCtrl]
Type=0
BaseClass=CWnd
HeaderFile=Grid\GridCtrl.h
ImplementationFile=Grid\GridCtrl.cpp

[CLS:CGridDropTarget]
Type=0
BaseClass=COleDropTarget
HeaderFile=Grid\GridDropTarget.h
ImplementationFile=Grid\GridDropTarget.cpp

[CLS:CInPlaceEdit]
Type=0
BaseClass=CEdit
HeaderFile=Grid\InPlaceEdit.h
ImplementationFile=Grid\InPlaceEdit.cpp

[CLS:CComboEdit]
Type=0
BaseClass=CEdit
HeaderFile=Grid\InPlaceList.h
ImplementationFile=Grid\InPlaceList.cpp

[CLS:CInPlaceList]
Type=0
BaseClass=CComboBox
HeaderFile=Grid\InPlaceList.h
ImplementationFile=Grid\InPlaceList.cpp

[CLS:CTitleTip]
Type=0
BaseClass=CWnd
HeaderFile=Grid\TitleTip.h
ImplementationFile=Grid\TitleTip.cpp

[CLS:CGridRunProt]
Type=0
BaseClass=CGridZip
HeaderFile=GridRunProt.h
ImplementationFile=GridRunProt.cpp

[CLS:CGridZip]
Type=0
BaseClass=CGridCtrl
HeaderFile=GridZip.h
ImplementationFile=GridZip.cpp

[CLS:CLabel]
Type=0
BaseClass=CStatic
HeaderFile=Label.h
ImplementationFile=Label.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainFrame.cpp
ImplementationFile=MainFrame.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrame.h
ImplementationFile=MainFrame.cpp

[CLS:CMMPropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MMPropPage.h
ImplementationFile=MMPropPage.cpp

[CLS:CMMStatusBar]
Type=0
BaseClass=CStatusBar
HeaderFile=MMStatusBar.h
ImplementationFile=MMStatusBar.cpp

[CLS:CMyListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp

[CLS:CPPApp]
Type=0
BaseClass=CMMPropPage
HeaderFile=PPApp.h
ImplementationFile=PPApp.cpp

[CLS:CPPDataWin]
Type=0
BaseClass=CMMPropPage
HeaderFile=PPDataWin.h
ImplementationFile=PPDataWin.cpp
LastObject=CPPDataWin

[CLS:CPPSerial]
Type=0
BaseClass=CMMPropPage
HeaderFile=PPSerial.h
ImplementationFile=PPSerial.cpp

[CLS:CPSSettings]
Type=0
BaseClass=CPropertySheet
HeaderFile=PSSettings.h
ImplementationFile=PSSettings.cpp

[CLS:CWndData]
Type=0
BaseClass=CDialog
HeaderFile=WndData.h
ImplementationFile=WndData.cpp
Filter=D
VirtualFilter=dWC
LastObject=CWndData

[CLS:CZyluxZipApp]
Type=0
BaseClass=CWinApp
HeaderFile=ZyluxZip.h
ImplementationFile=ZyluxZip.cpp

[CLS:CZyluxZipDlg]
Type=0
BaseClass=CFormView
HeaderFile=ZyluxZipDlg.h
ImplementationFile=ZyluxZipDlg.cpp

[DLG:IDD_NAMELIST]
Type=1
Class=CDlgNameList
ControlCount=5
Control1=IDC_SITELIST,MFCGridCtrl,1342242816
Control2=IDC_LIST_SAVE,button,1342242816
Control3=IDC_LIST_PRINT,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_DLG_TITLE,static,1342308353

[DLG:IDD_RUN_PROTOCOL]
Type=1
Class=CDlgRunProtocol
ControlCount=16
Control1=IDC_RUN_ASSEMBLY,edit,1350631552
Control2=IDC_RUN_NAME,combobox,1344340226
Control3=IDC_SITELIST,MFCGridCtrl,1342242816
Control4=IDC_EDIT,button,1342377988
Control5=IDC_LIST_SEND,button,1342373888
Control6=IDC_LIST_SAVE,button,1342242816
Control7=IDC_LIST_PRINT,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_DLG_TITLE,static,1342308353
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SITE_COUNT,edit,1350641794
Control13=IDC_STATIC,static,1342308352
Control14=IDC_NEEDNAMES,static,1342308352
Control15=IDC_RUN_SLOT,combobox,1344340227
Control16=IDC_STATIC,static,1342308352

[DLG:IDD_SITELIST]
Type=1
Class=CDlgSiteList
ControlCount=5
Control1=IDC_SITELIST,MFCGridCtrl,1342242816
Control2=IDC_LIST_SAVE,button,1342242816
Control3=IDC_LIST_PRINT,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_DLG_TITLE,static,1342308353

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_APPNAME,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_COPYRIGHT,static,1342308352
Control5=IDC_VERINFO,static,1342308480

[DLG:IDD_PP_APP]
Type=1
Class=CPPApp
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PP_DATAWIN]
Type=1
Class=CPPDataWin
ControlCount=5
Control1=IDC_AUTOWRAP,button,1342242819
Control2=IDC_NEWLINE,button,1342177283
Control3=IDC_LOCALECHO,button,1342177283
Control4=IDC_DISPLAYERRORS,button,1342177283
Control5=IDC_FONT,button,1342373888

[DLG:IDD_PP_SERIAL]
Type=1
Class=CPPSerial
ControlCount=14
Control1=IDC_STATIC,static,1342308354
Control2=IDC_PORTCB,combobox,1344340483
Control3=IDC_STATIC,static,1342177282
Control4=IDC_BAUDCB,combobox,1344340483
Control5=IDC_STATIC,static,1342177282
Control6=IDC_DATABITSCB,combobox,1344340483
Control7=IDC_STATIC,static,1342177282
Control8=IDC_PARITYCB,combobox,1344340483
Control9=IDC_STATIC,static,1342177282
Control10=IDC_STOPBITSCB,combobox,1344340483
Control11=IDC_DTRDSR,button,1342242819
Control12=IDC_RTSCTS,button,1342177283
Control13=IDC_XONXOFF,button,1342177283
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_DATAWIN]
Type=1
Class=CWndData
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TTYDATA,edit,1353781444
Control3=IDC_HEXMODE,button,1342242819

[DLG:IDD_ZYLUXZIP_DIALOG]
Type=1
Class=CZyluxZipDlg
ControlCount=2
Control1=IDC_APPNAME,static,1342177419
Control2=IDC_VERINFO,static,1342308480

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_SELECTALL
Command6=ID_EDIT_INS_ROW
Command7=ID_EDIT_DEL_ROW
Command8=IDM_SITELIST
Command9=IDM_RUN_NAMES
Command10=IDM_RUN_PROTOCOL_NEW
Command11=IDM_RUN_PROTOCOL_OPEN
Command12=IDM_RUN_PROTOCOL_DELETE
Command13=ID_FILE_MRU_FILE1
Command14=IDM_SETTINGS
Command15=IDM_CAPTURE
Command16=IDM_ABOUTBOX
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_DEL_ROW
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_INS_ROW
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[MNU:IDR_MENU_CONTEXT]
Type=1
Class=?
CommandCount=0

