# Microsoft Developer Studio Project File - Name="QM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=QM - Win32 Debug Simulate
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QM.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QM.MAK" CFG="QM - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QM - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QM - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "QM - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "QM - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QM - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "T:\tmp\FB12\QM\Release"
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

!ELSEIF  "$(CFG)" == "QM - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "T:\tmp\FB12\QM\Debug"
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

!ELSEIF  "$(CFG)" == "QM - Win32 Debug Simulate"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "QM___Win"
# PROP BASE Intermediate_Dir "QM___Win"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugS"
# PROP Intermediate_Dir "T:\tmp\FB12\QM\DebugS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I "..\Excel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "QM - Win32 Release Simulate"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "QM___Wi0"
# PROP BASE Intermediate_Dir "QM___Wi0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseS"
# PROP Intermediate_Dir "T:\tmp\FB12\QM\ReleaseS"
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

# Name "QM - Win32 Release"
# Name "QM - Win32 Debug"
# Name "QM - Win32 Debug Simulate"
# Name "QM - Win32 Release Simulate"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\QM.cpp
# End Source File
# Begin Source File

SOURCE=.\QM.rc
# End Source File
# Begin Source File

SOURCE=.\QMDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\QMEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QMGridWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\QMPPS.cpp
# End Source File
# Begin Source File

SOURCE=.\QMView.cpp

!IF  "$(CFG)" == "QM - Win32 Release"

!ELSEIF  "$(CFG)" == "QM - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "QM - Win32 Debug Simulate"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "QM - Win32 Release Simulate"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\include\PPS.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\PPS.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\Protocol.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\include\ProtocolDlg.h
# End Source File
# Begin Source File

SOURCE=..\Protocol\ProtocolFrame.h
# End Source File
# Begin Source File

SOURCE=.\QM.h
# End Source File
# Begin Source File

SOURCE=.\QMDoc.h
# End Source File
# Begin Source File

SOURCE=.\QMEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\QMGridWnd.h
# End Source File
# Begin Source File

SOURCE=.\QMPPS.h
# End Source File
# Begin Source File

SOURCE=.\QMView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\idr_qmty.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\QM.ico
# End Source File
# Begin Source File

SOURCE=.\res\QM.rc2
# End Source File
# Begin Source File

SOURCE=.\res\QMDoc.ico
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
