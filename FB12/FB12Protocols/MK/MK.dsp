# Microsoft Developer Studio Project File - Name="MK" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MK - Win32 Debug Simulate
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MK.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MK.MAK" CFG="MK - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MK - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MK - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MK - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "MK - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MK - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "T:\tmp\FB12\MK\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib ProtocolR.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\Protocol\lib"

!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "T:\tmp\FB12\MK\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib ProtocolD.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\Protocol\lib"

!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MK___Win"
# PROP BASE Intermediate_Dir "MK___Win"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugS"
# PROP Intermediate_Dir "T:\tmp\FB12\MK\DebugS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I "..\Excel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Winmm.lib Protocol.lib Excel.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\Protocol\Debug" /libpath:"..\Excel\Debug"
# ADD LINK32 Winmm.lib ProtocolDS.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\Protocol\lib"
# SUBTRACT LINK32 /verbose

!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MK___Wi0"
# PROP BASE Intermediate_Dir "MK___Wi0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseS"
# PROP Intermediate_Dir "T:\tmp\FB12\MK\ReleaseS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\Protocol\include" /I "..\Excel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Winmm.lib Protocol.lib Excel.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\Protocol\Release" /libpath:"..\Excel\Release"
# ADD LINK32 Winmm.lib ProtocolRS.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\Protocol\lib"

!ENDIF 

# Begin Target

# Name "MK - Win32 Release"
# Name "MK - Win32 Debug"
# Name "MK - Win32 Debug Simulate"
# Name "MK - Win32 Release Simulate"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChartOptView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartView.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcelOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MK.cpp
# End Source File
# Begin Source File

SOURCE=.\MK.rc
# End Source File
# Begin Source File

SOURCE=.\MKDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MKEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MKGraphFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MKGridWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MKHint.cpp
# End Source File
# Begin Source File

SOURCE=.\MKPPS.cpp
# End Source File
# Begin Source File

SOURCE=.\MKView.cpp
# End Source File
# Begin Source File

SOURCE=.\RepInfoList.cpp
# End Source File
# Begin Source File

SOURCE=.\Sample.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChartOptView.h
# End Source File
# Begin Source File

SOURCE=.\ChartView.h
# End Source File
# Begin Source File

SOURCE=.\ExcelOptions.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\FB12Device.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\General.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\Kinetics.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MK.h
# End Source File
# Begin Source File

SOURCE=.\MKDoc.h
# End Source File
# Begin Source File

SOURCE=.\MKEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\MKGraphFrame.h
# End Source File
# Begin Source File

SOURCE=.\MKGridWnd.h
# End Source File
# Begin Source File

SOURCE=.\MKHint.h
# End Source File
# Begin Source File

SOURCE=.\MKPPS.h
# End Source File
# Begin Source File

SOURCE=.\MKView.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\include\PPS.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\include\ProtocolDlg.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\ProtocolDoc.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\include\ProtocolFrame.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolGridWnd.h
# End Source File
# Begin Source File

SOURCE=.\RepInfoList.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\Replicate.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Sample.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_MKty.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MK.ico
# End Source File
# Begin Source File

SOURCE=.\res\MK.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MKDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
