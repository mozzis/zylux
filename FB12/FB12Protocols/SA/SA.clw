; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSAEditDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sa.h"
LastPage=0

ClassCount=10
Class1=CMainFrame
Class2=CSAApp
Class3=CAboutDlg
Class4=CSAAdvancedDlg
Class5=CSADoc
Class6=CSAEditDlg
Class7=CSAGridWnd
Class8=CSAKineticsView
Class9=CSampGridWnd
Class10=CSAView

ResourceCount=14
Resource1=IDD_SAADVANCED
Resource2=IDR_FB12
Resource3=IDR_VIEWFRAME
Resource4=IDD_ABOUTBOX
Resource5=IDR_SATYPE
Resource6=IDD_EXCELOPTIONS
Resource7=IDR_SAKINETICSTYPE
Resource8=IDD_SAEDIT
Resource9=IDR_MEASURE
Resource10=IDR_CONTEXT
Resource11=IDR_MAINFRAME
Resource12=IDR_SAVIEWTYPE
Resource13=IDD_PPSDIALOG
Resource14=IDD_SAVIEW

[CLS:CMainFrame]
Type=0
BaseClass=CProtocolFrame
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CSAApp]
Type=0
BaseClass=CProtocolApp
HeaderFile=SA.h
ImplementationFile=SA.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SA.cpp
ImplementationFile=SA.cpp
LastObject=CAboutDlg

[CLS:CSAAdvancedDlg]
Type=0
BaseClass=CProtocolDlg
HeaderFile=SAAdvancedDlg.h
ImplementationFile=SAAdvancedDlg.cpp

[CLS:CSADoc]
Type=0
BaseClass=CProtocolDoc
HeaderFile=SADoc.h
ImplementationFile=SADoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CSADoc

[CLS:CSAEditDlg]
Type=0
BaseClass=CProtocolDlg
HeaderFile=SAEditDlg.h
ImplementationFile=SAEditDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_ADVANCED

[CLS:CSAGridWnd]
Type=0
BaseClass=CProtocolGridWnd
HeaderFile=SAGridWnd.h
ImplementationFile=SAGridWnd.cpp

[CLS:CSAKineticsView]
Type=0
BaseClass=CKineticsView
HeaderFile=SAKineticsView.h
ImplementationFile=SAKineticsView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CSAKineticsView

[CLS:CSampGridWnd]
Type=0
BaseClass=CGXGridWnd
HeaderFile=SampGridWnd.h
ImplementationFile=SampGridWnd.cpp

[CLS:CSAView]
Type=0
BaseClass=CFormView
HeaderFile=SAView.h
ImplementationFile=SAView.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC_PROGICON,static,1342177539
Control2=IDC_STATIC_PROGSTR,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC_VERSION,static,1342308480

[DLG:IDD_SAADVANCED]
Type=1
Class=CSAAdvancedDlg
ControlCount=14
Control1=IDC_GB_OPTIONS,button,1342177287
Control2=IDC_CB_FLEXREPS,button,1342242819
Control3=IDC_CB_FLEXSAMPS,button,1342242819
Control4=IDC_GB_ENTRYORDER,button,1342308359
Control5=IDC_RB_ROWORDER,button,1342242825
Control6=IDC_RB_COLORDER,button,1342242825
Control7=IDC_GB_SAMPTITLES,button,1342177287
Control8=IDC_DELETE,button,1342242816
Control9=IDC_CLEAR,button,1342242816
Control10=IDC_IMPORT,button,1342242816
Control11=IDC_EDGRID,GXWND,1353777152
Control12=IDC_STATIC,static,1342308352
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816

[DLG:IDD_SAEDIT]
Type=1
Class=CSAEditDlg
ControlCount=26
Control1=IDC_GB_TIMES,button,1342177287
Control2=IDC_STATIC_DELAY,static,1342308352
Control3=IDC_EDIT_DELAY,edit,1350633600
Control4=IDC_SPIN_DELAY,msctls_updown32,1342177328
Control5=IDC_STATIC_MEAS,static,1342308352
Control6=IDC_EDIT_MEAS,edit,1350633600
Control7=IDC_SPIN_MEAS,msctls_updown32,1342177328
Control8=IDC_GB_STARTOPTION,button,1342308359
Control9=IDC_RB_STARTBUTTON,button,1342242825
Control10=IDC_STATIC,static,1342177280
Control11=IDC_RB_DOORCLOSE,button,1342242825
Control12=IDC_GB_REPSAMPS,button,1342177287
Control13=IDC_STATIC_REPS,static,1342308352
Control14=IDC_EDIT_REPS,edit,1350631552
Control15=IDC_SPIN_REPS,msctls_updown32,1342177330
Control16=IDC_STATIC_SAMPS,static,1342308352
Control17=IDC_EDIT_SAMPS,edit,1350631552
Control18=IDC_SPIN_SAMPS,msctls_updown32,1342177330
Control19=IDC_CB_BACKGROUND,button,1342242819
Control20=IDC_STATIC_COMMENTS,static,1342308352
Control21=IDC_EDIT_COMMENTS,edit,1350631492
Control22=IDC_ADVANCED,button,1342242816
Control23=IDC_SAVE,button,1342242817
Control24=IDC_SAVEAS,button,1342242816
Control25=IDCANCEL,button,1342242816
Control26=IDC_EXCEL,button,1342242816

[DLG:IDD_SAVIEW]
Type=1
Class=CSAView
ControlCount=18
Control1=IDC_SAGRID,GXWND,1353777152
Control2=IDC_STATIC_NUMREPS,static,1342308352
Control3=IDC_EDIT_NUMREPS,edit,1350633600
Control4=IDC_ADDREP,button,1342242816
Control5=IDC_STATIC_NUMSAMPS,static,1342308352
Control6=IDC_EDIT_NUMSAMPS,edit,1350633600
Control7=IDC_ADDSAMP,button,1342242816
Control8=IDC_STATIC_BACKGROUND,static,1342308353
Control9=IDC_EDIT_BACKGROUND,edit,1350631552
Control10=IDC_STATIC_RLUs,static,1342308352
Control11=IDC_STATIC_DATE,static,1342308352
Control12=IDC_EDIT_DATE,edit,1350633600
Control13=IDC_STATIC_DELAYTIME,static,1342308352
Control14=IDC_EDIT_DELAYTIME,edit,1350633600
Control15=IDC_STATIC_TIME,static,1342308352
Control16=IDC_EDIT_TIME,edit,1350633600
Control17=IDC_STATIC_MEASTIME,static,1342308352
Control18=IDC_EDIT_MEASTIME,edit,1350633600

[TB:IDR_FB12]
Type=1
Class=?
Command1=ID_FB12_DOOR
CommandCount=1

[TB:IDR_MEASURE]
Type=1
Class=?
Command1=ID_MEASURE_START
Command2=ID_MEASURE_STOP
Command3=ID_MEASURE_DELETE
CommandCount=3

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_COPY
Command4=ID_EXCEL
Command5=ID_FILE_PRINT
Command6=ID_APP_ABOUT
Command7=ID_MEASURE_GRID
Command8=ID_MEASURE_KINETICS
Command9=ID_KINETICS_ZOOMOUT
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_TILE_VERT
CommandCount=11

[TB:IDR_VIEWFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EXCEL
Command3=ID_FILE_PRINT
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EXCEL
Command3=ID_MEASURE_KINETICS
Command4=ID_FILE_NEW
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_MEASURE_GRID
Command8=ID_KINETICS_ZOOMOUT
Command9=ID_MEASURE_STOP
Command10=ID_EDIT_COPY
CommandCount=10

[DLG:IDD_PPSDIALOG]
Type=1
Class=?
ControlCount=6
Control1=PPS_IDC_STATIC_PROTOCOL,static,1342308352
Control2=PPS_IDC_EDIT_PROTOCOL,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=PPS_IDC_STATIC_PROTOCOLS,static,1342308352
Control6=PPS_IDC_LIST_PROTOCOLS,listbox,1352728833

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_SAVIEWTYPE]
Type=1
Class=?
Command1=ID_FILE_CLOSE
Command2=ID_FILE_SAVE_AS_TEXT
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_APP_EXIT
Command7=ID_EDIT_COPY
Command8=ID_EXCEL
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_SATYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_SAVE_AS_TEXT
Command6=ID_FILE_SAVE_KINETICS_AS_TEXT
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_APP_EXIT
Command11=ID_EDIT_COPY
Command12=ID_EXCEL
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_VIEW_RUNBAR
Command16=ID_MEASURE_START
Command17=ID_MEASURE_STOP
Command18=ID_MEASURE_DELETE
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_TILE_VERT
Command22=ID_WINDOW_ARRANGE
Command23=ID_MEASURE_GRID
Command24=ID_MEASURE_KINETICS
Command25=ID_APP_ABOUT
CommandCount=25

[MNU:IDR_CONTEXT]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_CONTEXT_BACKGROUND
CommandCount=2

[MNU:IDR_SAKINETICSTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_SAVE_KINETICS_AS_TEXT
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_APP_EXIT
Command10=ID_EDIT_COPY
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_VIEW_RUNBAR
Command14=ID_MEASURE_START
Command15=ID_MEASURE_STOP
Command16=ID_MEASURE_DELETE
Command17=ID_WINDOW_CASCADE
Command18=ID_WINDOW_TILE_HORZ
Command19=ID_WINDOW_TILE_VERT
Command20=ID_WINDOW_ARRANGE
Command21=ID_MEASURE_GRID
Command22=ID_MEASURE_KINETICS
Command23=ID_KINETICS_ZOOMOUT
Command24=ID_APP_ABOUT
CommandCount=24

[DLG:IDD_EXCELOPTIONS]
Type=1
Class=?
ControlCount=14
Control1=IDC_CHECK_AUTOSEND,button,1342242819
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_WORKBOOK,edit,1350631552
Control4=IDC_BROWSE,button,1342242817
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_WORKSHEET,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_MACRO,edit,1350631552
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816
Control12=IDC_COMBO_COL,combobox,1344339970
Control13=IDC_EDIT_ROW,edit,1350631552
Control14=IDC_STATIC,static,1342308352
