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
INTDIR=T:\tmp\SK\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK.exe"

!ELSE 

ALL : "$(OUTDIR)\SK.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
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
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SK.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Fp"$(INTDIR)\SK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=T:\tmp\SK\Release/
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
 /pdb:"$(OUTDIR)\SK.pdb" /machine:I386 /out:"$(OUTDIR)\SK.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
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
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

OUTDIR=.\Debug
INTDIR=T:\tmp\SK\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK.exe"

!ELSE 

ALL : "$(OUTDIR)\SK.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
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
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SK.exe"
	-@erase "$(OUTDIR)\SK.ilk"
	-@erase "$(OUTDIR)\SK.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL"\
 /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=T:\tmp\SK\Debug/
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
 /incremental:yes /pdb:"$(OUTDIR)\SK.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SK.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
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
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=T:\tmp\SK\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK.exe"

!ELSE 

ALL : "$(OUTDIR)\SK.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
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
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SK.exe"
	-@erase "$(OUTDIR)\SK.ilk"
	-@erase "$(OUTDIR)\SK.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D\
 "FB12_SIMULATE" /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=T:\tmp\SK\DebugS/
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
 /incremental:yes /pdb:"$(OUTDIR)\SK.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SK.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
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
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SK - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=T:\tmp\SK\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SK.exe"

!ELSE 

ALL : "$(OUTDIR)\SK.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChartOptView.obj"
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\ExcelOptions.obj"
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
	-@erase "$(INTDIR)\SKPPS.obj"
	-@erase "$(INTDIR)\SKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SK.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=T:\tmp\SK\ReleaseS/
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
 /incremental:no /pdb:"$(OUTDIR)\SK.pdb" /machine:I386 /out:"$(OUTDIR)\SK.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ChartOptView.obj" \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\ExcelOptions.obj" \
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
	"$(INTDIR)\SKPPS.obj" \
	"$(INTDIR)\SKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SK - Win32 Release" || "$(CFG)" == "SK - Win32 Debug" ||\
 "$(CFG)" == "SK - Win32 Debug Simulate" || "$(CFG)" ==\
 "SK - Win32 Release Simulate"
SOURCE=.\ChartOptView.cpp
DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\ChartOptView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\ChartView.cpp
DEP_CPP_CHARTV=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\ChartView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKHint.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHARTV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\ExcelOptions.cpp
DEP_CPP_EXCEL=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	".\ExcelOptions.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\ExcelOptions.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\RepInfoList.cpp
DEP_CPP_REPIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\SK.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\RepInfoList.obj" : $(SOURCE) $(DEP_CPP_REPIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\Sample.cpp
DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SK.cpp
DEP_CPP_SK_CP=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\GraphFrm.h"\
	"..\Protocol\GridFrm.h"\
	"..\Protocol\GridView.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\ChartView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKEditDlg.h"\
	".\SKGraphFrame.h"\
	".\SKGridWnd.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SK.obj" : $(SOURCE) $(DEP_CPP_SK_CP) "$(INTDIR)" "$(INTDIR)\SK.pch"


SOURCE=.\SK.rc
DEP_RSC_SK_RC=\
	".\res\bmp00001.bmp"\
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
DEP_CPP_SKADV=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKAdvanced.obj" : $(SOURCE) $(DEP_CPP_SKADV) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKDoc.cpp
DEP_CPP_SKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\GridView.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKDoc.obj" : $(SOURCE) $(DEP_CPP_SKDOC) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKEditDlg.cpp
DEP_CPP_SKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	".\ExcelOptions.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKAdvanced.h"\
	".\SKEditDlg.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKEditDlg.obj" : $(SOURCE) $(DEP_CPP_SKEDI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKGraphFrame.cpp
DEP_CPP_SKGRA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\GraphFrm.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\ChartOptView.h"\
	".\ChartView.h"\
	".\MainFrm.h"\
	".\RepInfoList.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGraphFrame.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKGraphFrame.obj" : $(SOURCE) $(DEP_CPP_SKGRA) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKGridWnd.cpp
DEP_CPP_SKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKGridWnd.obj" : $(SOURCE) $(DEP_CPP_SKGRI) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKHint.cpp
DEP_CPP_SKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	".\MainFrm.h"\
	".\SK.h"\
	".\SKHint.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKHint.obj" : $(SOURCE) $(DEP_CPP_SKHIN) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKPPS.cpp
DEP_CPP_SKPPS=\
	"..\Protocol\GPPS.h"\
	"..\Protocol\PPS.h"\
	".\SKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKPPS.obj" : $(SOURCE) $(DEP_CPP_SKPPS) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\SKView.cpp
DEP_CPP_SKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\GridView.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\KineticsView.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\SK.h"\
	".\SKDoc.h"\
	".\SKGridWnd.h"\
	".\SKHint.h"\
	".\SKPPS.h"\
	".\SKView.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

"$(INTDIR)\SKView.obj" : $(SOURCE) $(DEP_CPP_SKVIE) "$(INTDIR)"\
 "$(INTDIR)\SK.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"DScale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"obstack.h"\
	{$(INCLUDE)}"ochart.h"\
	{$(INCLUDE)}"SREGraphView.h"\
	{$(INCLUDE)}"SRGAxisManager.h"\
	{$(INCLUDE)}"SRGBareView.h"\
	{$(INCLUDE)}"SRGComboBox.h"\
	{$(INCLUDE)}"SRGComp.h"\
	{$(INCLUDE)}"SRGCompoundComponent.h"\
	{$(INCLUDE)}"SRGCompoundDisplay.h"\
	{$(INCLUDE)}"SRGCPly.h"\
	{$(INCLUDE)}"SRGDat.h"\
	{$(INCLUDE)}"SRGDataWatcher.h"\
	{$(INCLUDE)}"SRGDisplayBase.h"\
	{$(INCLUDE)}"SRGExc.h"\
	{$(INCLUDE)}"SRGFbck.h"\
	{$(INCLUDE)}"SRGGridLines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"SRGraph.h"\
	{$(INCLUDE)}"SRGraph2.h"\
	{$(INCLUDE)}"SRGraphBackground.h"\
	{$(INCLUDE)}"SRGraphDisplay.h"\
	{$(INCLUDE)}"SRGraphLabel.h"\
	{$(INCLUDE)}"SRGraphLabelBlock.h"\
	{$(INCLUDE)}"SRGraphLegend.h"\
	{$(INCLUDE)}"SRGraphRect.h"\
	{$(INCLUDE)}"SRGraphTitle.h"\
	{$(INCLUDE)}"SRGScrollView.h"\
	{$(INCLUDE)}"SRGStructureData.h"\
	{$(INCLUDE)}"SRGTextPanel.h"\
	{$(INCLUDE)}"SRGTickMarks.h"\
	{$(INCLUDE)}"SRGWzDisplay.h"\
	{$(INCLUDE)}"SRGZoom.h"\
	{$(INCLUDE)}"swtchbtn.h"\
	{$(INCLUDE)}"WizSheet.h"\
	

!IF  "$(CFG)" == "SK - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /Fp"$(INTDIR)\SK.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SK - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL"\
 /Fp"$(INTDIR)\SK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SK - Win32 Debug Simulate"

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

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "_OBJCHART_DLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

