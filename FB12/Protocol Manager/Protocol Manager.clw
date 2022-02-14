; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPMDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "protocol manager.h"
LastPage=0

ClassCount=6
Class1=COptDlg
Class2=CPMActivationWatcher
Class3=CAboutDlg
Class4=CPMDlg
Class5=CPMApp
Class6=CWorkDirDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_PROTOCOLMANAGER_DIALOG
Resource3=IDR_MENU_COMMANDS
Resource4=IDD_TMPDIALOG
Resource5=IDD_OPTIONS

[CLS:COptDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptDlg.h
ImplementationFile=OptDlg.cpp

[CLS:CPMActivationWatcher]
Type=0
BaseClass=CWinThread
HeaderFile=PMActwatch.h
ImplementationFile=PMActwatch.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=PMDlg.cpp
ImplementationFile=PMDlg.cpp
LastObject=CAboutDlg

[CLS:CPMDlg]
Type=0
BaseClass=CDialog
HeaderFile=PMDlg.h
ImplementationFile=PMDlg.cpp
LastObject=CPMDlg

[CLS:CPMApp]
Type=0
BaseClass=CWinApp
HeaderFile=Protocol Manager.h
ImplementationFile=Protocol Manager.cpp

[CLS:CWorkDirDlg]
Type=0
BaseClass=CFileDialog
HeaderFile=WorkDirDlg.h
ImplementationFile=WorkDirDlg.cpp

[DLG:IDD_OPTIONS]
Type=1
Class=COptDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GROUP_SERIAL,button,1342177287
Control4=IDC_STATIC_PORT,static,1342308352
Control5=IDC_STATIC_BAUD,static,1342308352
Control6=IDC_COMBO_PORT,combobox,1344339970
Control7=IDC_COMBO_BAUD,combobox,1344339970
Control8=IDC_STATIC_WORKDIR,static,1342308352
Control9=IDC_EDIT_WORKDIR,edit,1350631552
Control10=IDC_BUTTON_WORKDIR,button,1342242816
Control11=IDC_CHECK_BEEP,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=13
Control1=IDC_STATIC_PROGICON,static,1342177539
Control2=IDC_STATIC_PROGSTR,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177294
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_VERSION,static,1342308480
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[DLG:IDD_PROTOCOLMANAGER_DIALOG]
Type=1
Class=CPMDlg
ControlCount=14
Control1=IDC_STATIC_TYPES,button,1342177287
Control2=IDC_CREATE,button,1342242816
Control3=IDC_LIST_PROTOCOLTYPES,listbox,1353777409
Control4=IDC_EDIT_TYPECOMMENT,edit,1352730692
Control5=IDC_STATIC_USER,button,1342177287
Control6=IDC_RUN,button,1342242817
Control7=IDC_EDIT,button,1342242816
Control8=IDC_DELETE,button,1342242816
Control9=IDC_LIST_PROTOCOLS,listbox,1353777409
Control10=IDC_EDIT_COMMENT,edit,1352730692
Control11=IDC_RETRIEVE,button,1342242816
Control12=IDC_OPTIONS,button,1342242816
Control13=ID_APP_ABOUT,button,1342242816
Control14=IDOK,button,1342242816

[MNU:IDR_MENU_COMMANDS]
Type=1
Class=?
Command1=IDC_VIEWFILE
Command2=IDC_PROTOCOLDONE
CommandCount=2

[DLG:IDD_TMPDIALOG]
Type=1
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_INJECTOR,button,1342242819
Control4=IDC_GROUP_INJECTOR,button,1342177287
Control5=IDC_STATIC_IPORT,static,1342308352
Control6=IDC_COMBO_IPORT,combobox,1344339970
Control7=IDC_STATIC_VOLUME,static,1342308352
Control8=IDC_COMBO_VOLUME,combobox,1344339970

