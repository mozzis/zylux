# Microsoft Developer Studio Project File - Name="Protocol" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Protocol - Win32 Debug Simulate
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Protocol.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Protocol.mak" CFG="Protocol - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Protocol - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Debug Simulate" (based on "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Release Simulate" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Protocol - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\obj\Release\PCOLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "resources" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ProtocolR.lib"

!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\obj\Debug\PCOLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "include" /I "resources" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ProtocolD.lib"

!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Protocol"
# PROP BASE Intermediate_Dir "Protocol"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\obj\DebugS\PCOL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "resources" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ProtocolDS.lib"

!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Protoco0"
# PROP BASE Intermediate_Dir "Protoco0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\obj\ReleaseS\PCOLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "resources" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ProtocolRS.lib"

!ENDIF 

# Begin Target

# Name "Protocol - Win32 Release"
# Name "Protocol - Win32 Debug"
# Name "Protocol - Win32 Debug Simulate"
# Name "Protocol - Win32 Release Simulate"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Actwatch.cpp
# End Source File
# Begin Source File

SOURCE=.\Excel95.cpp
# End Source File
# Begin Source File

SOURCE=.\Excel97.cpp
# End Source File
# Begin Source File

SOURCE=.\FB12Device.cpp
# End Source File
# Begin Source File

SOURCE=.\General.cpp
# End Source File
# Begin Source File

SOURCE=.\GPPS.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GridFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GridView.cpp
# End Source File
# Begin Source File

SOURCE=.\Kinetics.cpp
# End Source File
# Begin Source File

SOURCE=.\KineticsView.cpp
# End Source File
# Begin Source File

SOURCE=.\PPS.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtCmdLineInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolGridWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Replicate.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveAsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCSerialNumber.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Actwatch.h
# End Source File
# Begin Source File

SOURCE=.\FB12Device.h
# End Source File
# Begin Source File

SOURCE=.\General.h
# End Source File
# Begin Source File

SOURCE=.\GPPS.h
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.h
# End Source File
# Begin Source File

SOURCE=.\GridFrm.h
# End Source File
# Begin Source File

SOURCE=.\GridView.h
# End Source File
# Begin Source File

SOURCE=.\Kinetics.h
# End Source File
# Begin Source File

SOURCE=.\KineticsView.h
# End Source File
# Begin Source File

SOURCE=.\PPS.h
# End Source File
# Begin Source File

SOURCE=.\ProtCmdLineInfo.h
# End Source File
# Begin Source File

SOURCE=.\Protocol.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolDoc.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolFrame.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolGridWnd.h
# End Source File
# Begin Source File

SOURCE=.\Replicate.h
# End Source File
# Begin Source File

SOURCE=.\SaveAsDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCSerialNumber.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# End Target
# End Project
