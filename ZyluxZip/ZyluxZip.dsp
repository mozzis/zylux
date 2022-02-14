# Microsoft Developer Studio Project File - Name="ZyluxZip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZyluxZip - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZyluxZip.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZyluxZip.mak" CFG="ZyluxZip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZyluxZip - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ZyluxZip - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ZyluxZip", PRCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZyluxZip - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "..\obj\Release\ZZip"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 VERSION.LIB /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"SHELL32.LIB COMDLG32.LIB" /pdbtype:sept /opt:noref
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ZyluxZip - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "..\obj\Debug\ZZip"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 VERSION.LIB /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"SHELL32.LIB COMDLG32.LIB" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ZyluxZip - Win32 Release"
# Name "ZyluxZip - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgNameList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRunProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSiteList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZipList.cpp
# End Source File
# Begin Source File

SOURCE=.\EdtData.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\GridZip.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid\InPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\izyluxcap.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MMPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MMStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\mystrtok.cpp
# End Source File
# Begin Source File

SOURCE=.\PPApp.cpp
# End Source File
# Begin Source File

SOURCE=.\PPDataWin.cpp
# End Source File
# Begin Source File

SOURCE=.\PPSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\RunNameList.cpp
# End Source File
# Begin Source File

SOURCE=.\RunProtList.cpp
# End Source File
# Begin Source File

SOURCE=.\SiteList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tty.cpp
# End Source File
# Begin Source File

SOURCE=.\WinPlace.cpp
# End Source File
# Begin Source File

SOURCE=.\WndData.cpp
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.cpp
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.odl
# ADD MTL /h "ZyluxZip_i.h" /iid "ZyluxZip_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.rc
# End Source File
# Begin Source File

SOURCE=.\ZyluxZipDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Grid\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\DlgNameList.h
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.h
# End Source File
# Begin Source File

SOURCE=.\DlgRunProtocol.h
# End Source File
# Begin Source File

SOURCE=.\DlgSiteList.h
# End Source File
# Begin Source File

SOURCE=.\DlgZipList.h
# End Source File
# Begin Source File

SOURCE=.\EdtData.h
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCombo.h
# End Source File
# Begin Source File

SOURCE=.\Grid\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Grid\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\GridZip.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceCheck.h
# End Source File
# Begin Source File

SOURCE=.\Grid\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\Grid\InPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\izyluxcap.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\Grid\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\messages.h
# End Source File
# Begin Source File

SOURCE=.\MMPropPage.h
# End Source File
# Begin Source File

SOURCE=.\MMStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\mystrtok.h
# End Source File
# Begin Source File

SOURCE=.\PPApp.h
# End Source File
# Begin Source File

SOURCE=.\PPDataWin.h
# End Source File
# Begin Source File

SOURCE=.\PPSerial.h
# End Source File
# Begin Source File

SOURCE=.\PSSettings.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RunNameList.h
# End Source File
# Begin Source File

SOURCE=.\RunProtList.h
# End Source File
# Begin Source File

SOURCE=.\SiteList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tty.h
# End Source File
# Begin Source File

SOURCE=.\WinPlace.h
# End Source File
# Begin Source File

SOURCE=.\WndData.h
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.h
# End Source File
# Begin Source File

SOURCE=.\ZyluxZipDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ZyluxZip.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZyluxZip.rc2
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ZyluxZip.reg
# End Source File
# End Target
# End Project
