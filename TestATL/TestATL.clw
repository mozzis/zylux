; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestATLDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestATL.h"
ODLFile=TestATL.odl

ClassCount=4
Class1=CTestATLApp
Class2=CTestATLDlg
Class3=CAboutDlg
Class4=CTestATLDlgAutoProxy

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTATL_DIALOG

[CLS:CTestATLApp]
Type=0
HeaderFile=TestATL.h
ImplementationFile=TestATL.cpp
Filter=N

[CLS:CTestATLDlg]
Type=0
HeaderFile=TestATLDlg.h
ImplementationFile=TestATLDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TestATLDlg.h
ImplementationFile=TestATLDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CTestATLDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_TESTATL_DIALOG]
Type=1
Class=CTestATLDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816

