# Microsoft Developer Studio Generated NMAKE File, Based on SK.DSP
!IF "$(CFG)" == ""
CFG=SK - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to SK - Win32 Debug Simulate.
!ENDIF 

!IF "$(CFG)" != "SK - Win32 Release" && "$(CFG)" != "SK - Win32 Debug" &&\
 "$(CFG)" != "SK - Win32 Debug Simulate" && "$(CFG)" !=\
 "SK - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SK.MAK" CFG="SK - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SK - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SK - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SK - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "SK - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SK - Win32 Release"

OUTDIR=.\Release
INTDIR=T:\tmp\Fb12\SK Injector\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK Injector.exe"

!ELSE 

ALL : "$(OUTDIR)\SK Injector.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
	-@erase "$(INTDIR)\InjectorOptions.obj"
	-@erase "$(INTDIR)\InjectorParams.obj"
	-@erase "$(INTDIR)\InjectorToolBar.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RepInfoList.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SK.obj"
	-@erase "$(INTDIR)\SK.pch"
	-@erase "$(INTDIR)\SK.res"
	-@erase "$(INTDIR)\SKAdvanced.obj"
	-@erase "$(INTDIR)\SKDoc.obj"
	-@erase "$(INTDIR)\SKEditDlg.obj"
	-@erase "$(INTDIR)\SKGraphFrame.obj"
	-@erase "$(INTDIR)\SKGridWnd.obj"
	-@erase "$(INTDIR)\SKHint.obj"
	-@erase "$(INTDIR)\SKOptions.obj"
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\XP3KControl.obj"
	-@erase "$(INTDIR)\XP3KDev.obj"
	-@erase "$(INTDIR)\XP3KTarget.obj"
	-@erase "$(OUTDIR)\SK Injector.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Fp"$(INTDIR)\SK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS="T:\tmp\Fb12\SK Injector\Release/"
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SK.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SK.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolR.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\SK Injector.pdb" /machine:I386 /out:"$(OUTDIR)\SK Injector.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
	"$(INTDIR)\InjectorOptions.obj" \
	"$(INTDIR)\InjectorParams.obj" \
	"$(INTDIR)\InjectorToolBar.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RepInfoList.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SK.obj" \
	"$(INTDIR)\SK.res" \
	"$(INTDIR)\SKAdvanced.obj" \
	"$(INTDIR)\SKDoc.obj" \
	"$(INTDIR)\SKEditDlg.obj" \
	"$(INTDIR)\SKGraphFrame.obj" \
	"$(INTDIR)\SKGridWnd.obj" \
	"$(INTDIR)\SKHint.obj" \
	"$(INTDIR)\SKOptions.obj" \
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\XP3KControl.obj" \
	"$(INTDIR)\XP3KDev.obj" \
	"$(INTDIR)\XP3KTarget.obj"

"$(OUTDIR)\SK Injector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

OUTDIR=.\Debug
INTDIR=T:\tmp\Fb12\SK Injector\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK Injector.exe"

!ELSE 

ALL : "$(OUTDIR)\SK Injector.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
	-@erase "$(INTDIR)\InjectorOptions.obj"
	-@erase "$(INTDIR)\InjectorParams.obj"
	-@erase "$(INTDIR)\InjectorToolBar.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RepInfoList.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SK.obj"
	-@erase "$(INTDIR)\SK.pch"
	-@erase "$(INTDIR)\SK.res"
	-@erase "$(INTDIR)\SKAdvanced.obj"
	-@erase "$(INTDIR)\SKDoc.obj"
	-@erase "$(INTDIR)\SKEditDlg.obj"
	-@erase "$(INTDIR)\SKGraphFrame.obj"
	-@erase "$(INTDIR)\SKGridWnd.obj"
	-@erase "$(INTDIR)\SKHint.obj"
	-@erase "$(INTDIR)\SKOptions.obj"
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\XP3KControl.obj"
	-@erase "$(INTDIR)\XP3KDev.obj"
	-@erase "$(INTDIR)\XP3KTarget.obj"
	-@erase "$(OUTDIR)\SK Injector.exe"
	-@erase "$(OUTDIR)\SK Injector.ilk"
	-@erase "$(OUTDIR)\SK Injector.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL"\
 /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS="T:\tmp\Fb12\SK Injector\Debug/"
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SK.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SK.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolD.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\SK Injector.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SK Injector.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
	"$(INTDIR)\InjectorOptions.obj" \
	"$(INTDIR)\InjectorParams.obj" \
	"$(INTDIR)\InjectorToolBar.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RepInfoList.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SK.obj" \
	"$(INTDIR)\SK.res" \
	"$(INTDIR)\SKAdvanced.obj" \
	"$(INTDIR)\SKDoc.obj" \
	"$(INTDIR)\SKEditDlg.obj" \
	"$(INTDIR)\SKGraphFrame.obj" \
	"$(INTDIR)\SKGridWnd.obj" \
	"$(INTDIR)\SKHint.obj" \
	"$(INTDIR)\SKOptions.obj" \
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\XP3KControl.obj" \
	"$(INTDIR)\XP3KDev.obj" \
	"$(INTDIR)\XP3KTarget.obj"

"$(OUTDIR)\SK Injector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=T:\tmp\Fb12\SK Injector\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK Injector.exe"

!ELSE 

ALL : "$(OUTDIR)\SK Injector.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
	-@erase "$(INTDIR)\InjectorOptions.obj"
	-@erase "$(INTDIR)\InjectorParams.obj"
	-@erase "$(INTDIR)\InjectorToolBar.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RepInfoList.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SK.obj"
	-@erase "$(INTDIR)\SK.pch"
	-@erase "$(INTDIR)\SK.res"
	-@erase "$(INTDIR)\SKAdvanced.obj"
	-@erase "$(INTDIR)\SKDoc.obj"
	-@erase "$(INTDIR)\SKEditDlg.obj"
	-@erase "$(INTDIR)\SKGraphFrame.obj"
	-@erase "$(INTDIR)\SKGridWnd.obj"
	-@erase "$(INTDIR)\SKHint.obj"
	-@erase "$(INTDIR)\SKOptions.obj"
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\XP3KControl.obj"
	-@erase "$(INTDIR)\XP3KDev.obj"
	-@erase "$(INTDIR)\XP3KTarget.obj"
	-@erase "$(OUTDIR)\SK Injector.exe"
	-@erase "$(OUTDIR)\SK Injector.ilk"
	-@erase "$(OUTDIR)\SK Injector.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D\
 "FB12_SIMULATE" /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS="T:\tmp\Fb12\SK Injector\DebugS/"
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SK.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SK.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolDS.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\SK Injector.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SK Injector.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
	"$(INTDIR)\InjectorOptions.obj" \
	"$(INTDIR)\InjectorParams.obj" \
	"$(INTDIR)\InjectorToolBar.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RepInfoList.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SK.obj" \
	"$(INTDIR)\SK.res" \
	"$(INTDIR)\SKAdvanced.obj" \
	"$(INTDIR)\SKDoc.obj" \
	"$(INTDIR)\SKEditDlg.obj" \
	"$(INTDIR)\SKGraphFrame.obj" \
	"$(INTDIR)\SKGridWnd.obj" \
	"$(INTDIR)\SKHint.obj" \
	"$(INTDIR)\SKOptions.obj" \
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\XP3KControl.obj" \
	"$(INTDIR)\XP3KDev.obj" \
	"$(INTDIR)\XP3KTarget.obj"

"$(OUTDIR)\SK Injector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=T:\tmp\Fb12\SK Injector\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK Injector.exe"

!ELSE 

ALL : "$(OUTDIR)\SK Injector.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
	-@erase "$(INTDIR)\InjectorOptions.obj"
	-@erase "$(INTDIR)\InjectorParams.obj"
	-@erase "$(INTDIR)\InjectorToolBar.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RepInfoList.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SK.obj"
	-@erase "$(INTDIR)\SK.pch"
	-@erase "$(INTDIR)\SK.res"
	-@erase "$(INTDIR)\SKAdvanced.obj"
	-@erase "$(INTDIR)\SKDoc.obj"
	-@erase "$(INTDIR)\SKEditDlg.obj"
	-@erase "$(INTDIR)\SKGraphFrame.obj"
	-@erase "$(INTDIR)\SKGridWnd.obj"
	-@erase "$(INTDIR)\SKHint.obj"
	-@erase "$(INTDIR)\SKOptions.obj"
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\XP3KControl.obj"
	-@erase "$(INTDIR)\XP3KDev.obj"
	-@erase "$(INTDIR)\XP3KTarget.obj"
	-@erase "$(OUTDIR)\SK Injector.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS="T:\tmp\Fb12\SK Injector\ReleaseS/"
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SK.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SK.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolRS.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\SK Injector.pdb" /machine:I386\
 /out:"$(OUTDIR)\SK Injector.exe" /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
	"$(INTDIR)\InjectorOptions.obj" \
	"$(INTDIR)\InjectorParams.obj" \
	"$(INTDIR)\InjectorToolBar.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RepInfoList.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SK.obj" \
	"$(INTDIR)\SK.res" \
	"$(INTDIR)\SKAdvanced.obj" \
	"$(INTDIR)\SKDoc.obj" \
	"$(INTDIR)\SKEditDlg.obj" \
	"$(INTDIR)\SKGraphFrame.obj" \
	"$(INTDIR)\SKGridWnd.obj" \
	"$(INTDIR)\SKHint.obj" \
	"$(INTDIR)\SKOptions.obj" \
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\XP3KControl.obj" \
	"$(INTDIR)\XP3KDev.obj" \
	"$(INTDIR)\XP3KTarget.obj"

"$(OUTDIR)\SK Injector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SK - Win32 Release" || "$(CFG)" == "SK - Win32 Debug" ||\
 "$(CFG)" == "SK - Win32 Debug Simulate" || "$(CFG)" ==\
 "SK - Win32 Release Simulate"
SOURCE=.\ChartOptView.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartOptView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartOptView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartOptView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartOptView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\ChartView.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_CHARTV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHARTV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_CHARTV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHARTV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_CHARTV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHARTV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_CHARTV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHARTV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\ExcelOptions.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_EXCEL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\ExcelOptions.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_EXCEL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\ExcelOptions.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_EXCEL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\ExcelOptions.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_EXCEL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\ExcelOptions.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\InjectorOptions.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_INJEC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorOptions.obj" : $(SOURCE) $(DEP_CPP_INJEC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_INJEC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorOptions.obj" : $(SOURCE) $(DEP_CPP_INJEC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_INJEC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorOptions.obj" : $(SOURCE) $(DEP_CPP_INJEC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_INJEC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorOptions.obj" : $(SOURCE) $(DEP_CPP_INJEC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\InjectorParams.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_INJECT=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorParams.obj" : $(SOURCE) $(DEP_CPP_INJECT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_INJECT=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorParams.obj" : $(SOURCE) $(DEP_CPP_INJECT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_INJECT=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorParams.obj" : $(SOURCE) $(DEP_CPP_INJECT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_INJECT=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\InjectorParams.obj" : $(SOURCE) $(DEP_CPP_INJECT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\InjectorToolBar.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_INJECTO=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\InjectorToolBar.obj" : $(SOURCE) $(DEP_CPP_INJECTO) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_INJECTO=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\InjectorToolBar.obj" : $(SOURCE) $(DEP_CPP_INJECTO) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_INJECTO=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\InjectorToolBar.obj" : $(SOURCE) $(DEP_CPP_INJECTO) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_INJECTO=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\InjectorToolBar.obj" : $(SOURCE) $(DEP_CPP_INJECTO) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\RepInfoList.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_REPIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\RepInfoList.obj" : $(SOURCE) $(DEP_CPP_REPIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_REPIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\RepInfoList.obj" : $(SOURCE) $(DEP_CPP_REPIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_REPIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\RepInfoList.obj" : $(SOURCE) $(DEP_CPP_REPIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_REPIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\RepInfoList.obj" : $(SOURCE) $(DEP_CPP_REPIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\Sample.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SK.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SK_CP=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\gridfrm.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKEditDlg.h"\
	".\SKGraphFrame.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SK.obj" : $(SOURCE) $(DEP_CPP_SK_CP) "$(INTDIR)" "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SK_CP=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\gridfrm.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKEditDlg.h"\
	".\SKGraphFrame.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SK.obj" : $(SOURCE) $(DEP_CPP_SK_CP) "$(INTDIR)" "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SK_CP=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\gridfrm.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKEditDlg.h"\
	".\SKGraphFrame.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SK.obj" : $(SOURCE) $(DEP_CPP_SK_CP) "$(INTDIR)" "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SK_CP=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\gridfrm.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKEditDlg.h"\
	".\SKGraphFrame.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SK.obj" : $(SOURCE) $(DEP_CPP_SK_CP) "$(INTDIR)" "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SK.rc
DEP_RSC_SK_RC=\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\idr_main.ico"\
	".\res\idr_SKty.ico"\
	".\res\mainfram.bmp"\
	".\res\SK.ico"\
	".\res\SK.rc2"\
	".\res\SKDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	

"$(INTDIR)\SK.res" : $(SOURCE) $(DEP_RSC_SK_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SKAdvanced.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKADV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKAdvanced.obj" : $(SOURCE) $(DEP_CPP_SKADV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKADV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKAdvanced.obj" : $(SOURCE) $(DEP_CPP_SKADV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKADV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKAdvanced.obj" : $(SOURCE) $(DEP_CPP_SKADV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKADV=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKAdvanced.obj" : $(SOURCE) $(DEP_CPP_SKADV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKDoc.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKDoc.obj" : $(SOURCE) $(DEP_CPP_SKDOC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKDoc.obj" : $(SOURCE) $(DEP_CPP_SKDOC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKDoc.obj" : $(SOURCE) $(DEP_CPP_SKDOC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKDoc.obj" : $(SOURCE) $(DEP_CPP_SKDOC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKEditDlg.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKEditDlg.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKEditDlg.obj" : $(SOURCE) $(DEP_CPP_SKEDI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKEditDlg.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKEditDlg.obj" : $(SOURCE) $(DEP_CPP_SKEDI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKEditDlg.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKEditDlg.obj" : $(SOURCE) $(DEP_CPP_SKEDI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\ExcelOptions.h"\
	".\InjectorOptions.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKEditDlg.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKEditDlg.obj" : $(SOURCE) $(DEP_CPP_SKEDI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKGraphFrame.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKGRA=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGraphFrame.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGraphFrame.obj" : $(SOURCE) $(DEP_CPP_SKGRA) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKGRA=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGraphFrame.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGraphFrame.obj" : $(SOURCE) $(DEP_CPP_SKGRA) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKGRA=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGraphFrame.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGraphFrame.obj" : $(SOURCE) $(DEP_CPP_SKGRA) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKGRA=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\graphfrm.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGraphFrame.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGraphFrame.obj" : $(SOURCE) $(DEP_CPP_SKGRA) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKGridWnd.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGridWnd.obj" : $(SOURCE) $(DEP_CPP_SKGRI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGridWnd.obj" : $(SOURCE) $(DEP_CPP_SKGRI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGridWnd.obj" : $(SOURCE) $(DEP_CPP_SKGRI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKGridWnd.obj" : $(SOURCE) $(DEP_CPP_SKGRI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKHint.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKHint.obj" : $(SOURCE) $(DEP_CPP_SKHIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKHint.obj" : $(SOURCE) $(DEP_CPP_SKHIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKHint.obj" : $(SOURCE) $(DEP_CPP_SKHIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKHint.obj" : $(SOURCE) $(DEP_CPP_SKHIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKOptions.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKOPT=\
	"..\protocol\general.h"\
	".\SKOptions.h"\
	

"$(INTDIR)\SKOptions.obj" : $(SOURCE) $(DEP_CPP_SKOPT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKOPT=\
	"..\protocol\general.h"\
	".\SKOptions.h"\
	

"$(INTDIR)\SKOptions.obj" : $(SOURCE) $(DEP_CPP_SKOPT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKOPT=\
	"..\protocol\general.h"\
	".\SKOptions.h"\
	

"$(INTDIR)\SKOptions.obj" : $(SOURCE) $(DEP_CPP_SKOPT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKOPT=\
	"..\protocol\general.h"\
	".\SKOptions.h"\
	

"$(INTDIR)\SKOptions.obj" : $(SOURCE) $(DEP_CPP_SKOPT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKPPS.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKPPS=\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	".\InjectorParams.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKPPS.obj" : $(SOURCE) $(DEP_CPP_SKPPS) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKPPS=\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	".\InjectorParams.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKPPS.obj" : $(SOURCE) $(DEP_CPP_SKPPS) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKPPS=\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	".\InjectorParams.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKPPS.obj" : $(SOURCE) $(DEP_CPP_SKPPS) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKPPS=\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	".\InjectorParams.h"\
	".\SKPPS.h"\
	

"$(INTDIR)\SKPPS.obj" : $(SOURCE) $(DEP_CPP_SKPPS) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\SKView.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_SKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKView.obj" : $(SOURCE) $(DEP_CPP_SKVIE) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_SKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKView.obj" : $(SOURCE) $(DEP_CPP_SKVIE) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_SKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKView.obj" : $(SOURCE) $(DEP_CPP_SKVIE) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_SKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\gridview.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\options.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\InjectorParams.h"\
	".\InjectorToolBar.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKOptions.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\SKView.obj" : $(SOURCE) $(DEP_CPP_SKVIE) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\oc12\include\comdoc.h"\
	"d:\oc12\include\docmngr.h"\
	"d:\oc12\include\dscale.h"\
	"d:\oc12\include\graphdoc.h"\
	"d:\oc12\include\graphvw.h"\
	"d:\oc12\include\grphtip.h"\
	"d:\oc12\include\obstack.h"\
	"d:\oc12\include\ochart.h"\
	"d:\oc12\include\sregraphview.h"\
	"d:\oc12\include\srgaxismanager.h"\
	"d:\oc12\include\srgbareview.h"\
	"d:\oc12\include\srgcombobox.h"\
	"d:\oc12\include\srgcomp.h"\
	"d:\oc12\include\srgcompoundcomponent.h"\
	"d:\oc12\include\srgcompounddisplay.h"\
	"d:\oc12\include\srgcply.h"\
	"d:\oc12\include\srgdat.h"\
	"d:\oc12\include\srgdatawatcher.h"\
	"d:\oc12\include\srgdisplaybase.h"\
	"d:\oc12\include\srgexc.h"\
	"d:\oc12\include\srgfbck.h"\
	"d:\oc12\include\srggridlines.h"\
	"d:\oc12\include\srgposn.h"\
	"d:\oc12\include\srgraph.h"\
	"d:\oc12\include\srgraph2.h"\
	"d:\oc12\include\srgraphbackground.h"\
	"d:\oc12\include\srgraphdisplay.h"\
	"d:\oc12\include\srgraphlabel.h"\
	"d:\oc12\include\srgraphlabelblock.h"\
	"d:\oc12\include\srgraphlegend.h"\
	"d:\oc12\include\srgraphrect.h"\
	"d:\oc12\include\srgraphtitle.h"\
	"d:\oc12\include\srgscrollview.h"\
	"d:\oc12\include\srgstructuredata.h"\
	"d:\oc12\include\srgtextpanel.h"\
	"d:\oc12\include\srgtickmarks.h"\
	"d:\oc12\include\srgwzdisplay.h"\
	"d:\oc12\include\srgzoom.h"\
	"d:\oc12\include\swtchbtn.h"\
	"d:\oc12\include\wizsheet.h"\
	
NODEP_CPP_STDAF=\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Fp"$(INTDIR)\SK.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\oc12\include\comdoc.h"\
	"d:\oc12\include\docmngr.h"\
	"d:\oc12\include\dscale.h"\
	"d:\oc12\include\graphdoc.h"\
	"d:\oc12\include\graphvw.h"\
	"d:\oc12\include\grphtip.h"\
	"d:\oc12\include\obstack.h"\
	"d:\oc12\include\ochart.h"\
	"d:\oc12\include\sregraphview.h"\
	"d:\oc12\include\srgaxismanager.h"\
	"d:\oc12\include\srgbareview.h"\
	"d:\oc12\include\srgcombobox.h"\
	"d:\oc12\include\srgcomp.h"\
	"d:\oc12\include\srgcompoundcomponent.h"\
	"d:\oc12\include\srgcompounddisplay.h"\
	"d:\oc12\include\srgcply.h"\
	"d:\oc12\include\srgdat.h"\
	"d:\oc12\include\srgdatawatcher.h"\
	"d:\oc12\include\srgdisplaybase.h"\
	"d:\oc12\include\srgexc.h"\
	"d:\oc12\include\srgfbck.h"\
	"d:\oc12\include\srggridlines.h"\
	"d:\oc12\include\srgposn.h"\
	"d:\oc12\include\srgraph.h"\
	"d:\oc12\include\srgraph2.h"\
	"d:\oc12\include\srgraphbackground.h"\
	"d:\oc12\include\srgraphdisplay.h"\
	"d:\oc12\include\srgraphlabel.h"\
	"d:\oc12\include\srgraphlabelblock.h"\
	"d:\oc12\include\srgraphlegend.h"\
	"d:\oc12\include\srgraphrect.h"\
	"d:\oc12\include\srgraphtitle.h"\
	"d:\oc12\include\srgscrollview.h"\
	"d:\oc12\include\srgstructuredata.h"\
	"d:\oc12\include\srgtextpanel.h"\
	"d:\oc12\include\srgtickmarks.h"\
	"d:\oc12\include\srgwzdisplay.h"\
	"d:\oc12\include\srgzoom.h"\
	"d:\oc12\include\swtchbtn.h"\
	"d:\oc12\include\wizsheet.h"\
	
NODEP_CPP_STDAF=\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL"\
 /Fp"$(INTDIR)\SK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\oc12\include\comdoc.h"\
	"d:\oc12\include\docmngr.h"\
	"d:\oc12\include\dscale.h"\
	"d:\oc12\include\graphdoc.h"\
	"d:\oc12\include\graphvw.h"\
	"d:\oc12\include\grphtip.h"\
	"d:\oc12\include\obstack.h"\
	"d:\oc12\include\ochart.h"\
	"d:\oc12\include\sregraphview.h"\
	"d:\oc12\include\srgaxismanager.h"\
	"d:\oc12\include\srgbareview.h"\
	"d:\oc12\include\srgcombobox.h"\
	"d:\oc12\include\srgcomp.h"\
	"d:\oc12\include\srgcompoundcomponent.h"\
	"d:\oc12\include\srgcompounddisplay.h"\
	"d:\oc12\include\srgcply.h"\
	"d:\oc12\include\srgdat.h"\
	"d:\oc12\include\srgdatawatcher.h"\
	"d:\oc12\include\srgdisplaybase.h"\
	"d:\oc12\include\srgexc.h"\
	"d:\oc12\include\srgfbck.h"\
	"d:\oc12\include\srggridlines.h"\
	"d:\oc12\include\srgposn.h"\
	"d:\oc12\include\srgraph.h"\
	"d:\oc12\include\srgraph2.h"\
	"d:\oc12\include\srgraphbackground.h"\
	"d:\oc12\include\srgraphdisplay.h"\
	"d:\oc12\include\srgraphlabel.h"\
	"d:\oc12\include\srgraphlabelblock.h"\
	"d:\oc12\include\srgraphlegend.h"\
	"d:\oc12\include\srgraphrect.h"\
	"d:\oc12\include\srgraphtitle.h"\
	"d:\oc12\include\srgscrollview.h"\
	"d:\oc12\include\srgstructuredata.h"\
	"d:\oc12\include\srgtextpanel.h"\
	"d:\oc12\include\srgtickmarks.h"\
	"d:\oc12\include\srgwzdisplay.h"\
	"d:\oc12\include\srgzoom.h"\
	"d:\oc12\include\swtchbtn.h"\
	"d:\oc12\include\wizsheet.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D\
 "FB12_SIMULATE" /Fp"$(INTDIR)\SK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\oc12\include\comdoc.h"\
	"d:\oc12\include\docmngr.h"\
	"d:\oc12\include\dscale.h"\
	"d:\oc12\include\graphdoc.h"\
	"d:\oc12\include\graphvw.h"\
	"d:\oc12\include\grphtip.h"\
	"d:\oc12\include\obstack.h"\
	"d:\oc12\include\ochart.h"\
	"d:\oc12\include\sregraphview.h"\
	"d:\oc12\include\srgaxismanager.h"\
	"d:\oc12\include\srgbareview.h"\
	"d:\oc12\include\srgcombobox.h"\
	"d:\oc12\include\srgcomp.h"\
	"d:\oc12\include\srgcompoundcomponent.h"\
	"d:\oc12\include\srgcompounddisplay.h"\
	"d:\oc12\include\srgcply.h"\
	"d:\oc12\include\srgdat.h"\
	"d:\oc12\include\srgdatawatcher.h"\
	"d:\oc12\include\srgdisplaybase.h"\
	"d:\oc12\include\srgexc.h"\
	"d:\oc12\include\srgfbck.h"\
	"d:\oc12\include\srggridlines.h"\
	"d:\oc12\include\srgposn.h"\
	"d:\oc12\include\srgraph.h"\
	"d:\oc12\include\srgraph2.h"\
	"d:\oc12\include\srgraphbackground.h"\
	"d:\oc12\include\srgraphdisplay.h"\
	"d:\oc12\include\srgraphlabel.h"\
	"d:\oc12\include\srgraphlabelblock.h"\
	"d:\oc12\include\srgraphlegend.h"\
	"d:\oc12\include\srgraphrect.h"\
	"d:\oc12\include\srgraphtitle.h"\
	"d:\oc12\include\srgscrollview.h"\
	"d:\oc12\include\srgstructuredata.h"\
	"d:\oc12\include\srgtextpanel.h"\
	"d:\oc12\include\srgtickmarks.h"\
	"d:\oc12\include\srgwzdisplay.h"\
	"d:\oc12\include\srgzoom.h"\
	"d:\oc12\include\swtchbtn.h"\
	"d:\oc12\include\wizsheet.h"\
	
NODEP_CPP_STDAF=\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\XP3KControl.cpp

!IF  "$(CFG)" == "SK - Win32 Release"

DEP_CPP_XP3KC=\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\XP3KControl.obj" : $(SOURCE) $(DEP_CPP_XP3KC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

DEP_CPP_XP3KC=\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\XP3KControl.obj" : $(SOURCE) $(DEP_CPP_XP3KC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

DEP_CPP_XP3KC=\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\XP3KControl.obj" : $(SOURCE) $(DEP_CPP_XP3KC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

DEP_CPP_XP3KC=\
	".\XP3KControl.h"\
	".\XP3KDev.h"\
	".\XP3KTarget.h"\
	

"$(INTDIR)\XP3KControl.obj" : $(SOURCE) $(DEP_CPP_XP3KC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


!ENDIF 

SOURCE=.\XP3KDev.cpp
DEP_CPP_XP3KD=\
	".\XP3KDev.h"\
	

"$(INTDIR)\XP3KDev.obj" : $(SOURCE) $(DEP_CPP_XP3KD) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\XP3KTarget.cpp
DEP_CPP_XP3KT=\
	".\XP3KTarget.h"\
	

"$(INTDIR)\XP3KTarget.obj" : $(SOURCE) $(DEP_CPP_XP3KT) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"



!ENDIF 

