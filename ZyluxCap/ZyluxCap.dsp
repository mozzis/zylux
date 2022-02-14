# Microsoft Developer Studio Project File - Name="ZyluxCap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZyluxCap - Win32 British Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZyluxCap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZyluxCap.mak" CFG="ZyluxCap - Win32 British Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZyluxCap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ZyluxCap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ZyluxCap - Win32 British Debug" (based on "Win32 (x86) Application")
!MESSAGE "ZyluxCap - Win32 British Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ZyluxCap/2.0","
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZyluxCap - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "..\obj\Release\ZCap"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZYLUX_NORMAL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_ZYLUX_NORMAL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "ZyluxCap - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "..\obj\Debug\ZCap"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZYLUX_NORMAL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_ZYLUX_NORMAL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ZyluxCap - Win32 British Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ZyluxCap___Win32_British_Debug"
# PROP BASE Intermediate_Dir "ZyluxCap___Win32_British_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\release"
# PROP Intermediate_Dir "..\obj\debug\zcap\brit"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZYLUX_BRITISH" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_ZYLUX_BRITISH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /pdb:"..\debug/ZyluxCapB.pdb" /debug /machine:I386 /out:"..\debug/ZyluxCap.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ZyluxCap - Win32 British Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ZyluxCap___Win32_British_Release"
# PROP BASE Intermediate_Dir "ZyluxCap___Win32_British_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release"
# PROP Intermediate_Dir "..\obj\release\zcap\brit"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZYLUX_BRITISH" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_ZYLUX_BRITISH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 version.lib /nologo /subsystem:windows /pdb:"..\release/Brit/ZyluxCap.pdb" /machine:I386 /out:"..\release/Brit/ZyluxCap.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /debug
# Begin Special Build Tool
TargetDir=\Code\Zylux\release\Brit
TargetPath=\Code\Zylux\release\Brit\ZyluxCap.exe
TargetName=ZyluxCap
SOURCE="$(InputPath)"
PostBuild_Desc=Making "B" copy...
PostBuild_Cmds=copy $(TargetPath) $(TargetDir)\$(TargetName)B.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ZyluxCap - Win32 Release"
# Name "ZyluxCap - Win32 Debug"
# Name "ZyluxCap - Win32 British Debug"
# Name "ZyluxCap - Win32 British Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\EdtCol.cpp
# End Source File
# Begin Source File

SOURCE=.\EdtData.cpp
# End Source File
# Begin Source File

SOURCE=.\EdtRow.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MMPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MMSlide.cpp
# End Source File
# Begin Source File

SOURCE=.\MMStatusBar.cpp
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

SOURCE=.\PPXfer.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\pushdata.cpp
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

SOURCE=.\ZyluxCap.cpp
# End Source File
# Begin Source File

SOURCE=.\ZyluxCap.odl
# ADD MTL /h "Zyluxtlb.h" /iid "Zyluxtlb.c"
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\ZyluxCap.rc
# End Source File
# Begin Source File

SOURCE=.\ZyluxForm.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgProxy.h
# End Source File
# Begin Source File

SOURCE=.\EdtCol.h
# End Source File
# Begin Source File

SOURCE=.\EdtData.h
# End Source File
# Begin Source File

SOURCE=.\EdtRow.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\messages.h
# End Source File
# Begin Source File

SOURCE=.\MMInfo.h
# End Source File
# Begin Source File

SOURCE=.\MMPropPage.h
# End Source File
# Begin Source File

SOURCE=.\MMSlide.h
# End Source File
# Begin Source File

SOURCE=.\MMStatusBar.h
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

SOURCE=.\PPXfer.h
# End Source File
# Begin Source File

SOURCE=.\PSSettings.h
# End Source File
# Begin Source File

SOURCE=.\pushdata.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
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

SOURCE=.\ZyluxCap.h
# End Source File
# Begin Source File

SOURCE=.\ZyluxForm.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\idd_data.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tty.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZyluxCap.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZyluxCap.rc2
# End Source File
# Begin Source File

SOURCE=.\ZyluxNotify.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ZyluxCap.reg
# End Source File
# Begin Source File

SOURCE=..\debug\ZyluxCap.tlb
# End Source File
# Begin Source File

SOURCE=..\release\zyluxcap.tlb
# End Source File
# End Target
# End Project
