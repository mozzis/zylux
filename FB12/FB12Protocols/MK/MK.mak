# Microsoft Developer Studio Generated NMAKE File, Based on MK.DSP
!IF "$(CFG)" == ""
CFG=MK - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to MK - Win32 Debug Simulate.
!ENDIF

!IF "$(CFG)" != "MK - Win32 Release" && "$(CFG)" != "MK - Win32 Debug" &&\
 "$(CFG)" != "MK - Win32 Debug Simulate" && "$(CFG)" !=\
 "MK - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF

!IF  "$(CFG)" == "MK - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\MK.exe"

!ELSE

ALL : "$(OUTDIR)\MK.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\GraphControl.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\MK.obj"
	-@erase "$(INTDIR)\MK.pch"
	-@erase "$(INTDIR)\MK.res"
	-@erase "$(INTDIR)\MKChartView.obj"
	-@erase "$(INTDIR)\MKDoc.obj"
	-@erase "$(INTDIR)\MKEditDlg.obj"
	-@erase "$(INTDIR)\MKGridWnd.obj"
	-@erase "$(INTDIR)\MKHint.obj"
	-@erase "$(INTDIR)\MKPPS.obj"
	-@erase "$(INTDIR)\MKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MK.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\Release/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MK.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MK.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolR.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\MK.pdb" /machine:I386 /out:"$(OUTDIR)\MK.exe"\
 /libpath:"..\Protocol\lib"
LINK32_OBJS= \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\GraphControl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\MK.obj" \
	"$(INTDIR)\MK.res" \
	"$(INTDIR)\MKChartView.obj" \
	"$(INTDIR)\MKDoc.obj" \
	"$(INTDIR)\MKEditDlg.obj" \
	"$(INTDIR)\MKGridWnd.obj" \
	"$(INTDIR)\MKHint.obj" \
	"$(INTDIR)\MKPPS.obj" \
	"$(INTDIR)\MKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\MK.exe"

!ELSE

ALL : "$(OUTDIR)\MK.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\GraphControl.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\MK.obj"
	-@erase "$(INTDIR)\MK.pch"
	-@erase "$(INTDIR)\MK.res"
	-@erase "$(INTDIR)\MKChartView.obj"
	-@erase "$(INTDIR)\MKDoc.obj"
	-@erase "$(INTDIR)\MKEditDlg.obj"
	-@erase "$(INTDIR)\MKGridWnd.obj"
	-@erase "$(INTDIR)\MKHint.obj"
	-@erase "$(INTDIR)\MKPPS.obj"
	-@erase "$(INTDIR)\MKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MK.exe"
	-@erase "$(OUTDIR)\MK.ilk"
	-@erase "$(OUTDIR)\MK.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\Debug/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MK.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MK.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolD.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\MK.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\MK.exe" /pdbtype:sept /libpath:"..\Protocol\lib"
LINK32_OBJS= \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\GraphControl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\MK.obj" \
	"$(INTDIR)\MK.res" \
	"$(INTDIR)\MKChartView.obj" \
	"$(INTDIR)\MKDoc.obj" \
	"$(INTDIR)\MKEditDlg.obj" \
	"$(INTDIR)\MKGridWnd.obj" \
	"$(INTDIR)\MKHint.obj" \
	"$(INTDIR)\MKPPS.obj" \
	"$(INTDIR)\MKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=.\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\MK.exe"

!ELSE

ALL : "$(OUTDIR)\MK.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\GraphControl.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\MK.obj"
	-@erase "$(INTDIR)\MK.pch"
	-@erase "$(INTDIR)\MK.res"
	-@erase "$(INTDIR)\MKChartView.obj"
	-@erase "$(INTDIR)\MKDoc.obj"
	-@erase "$(INTDIR)\MKEditDlg.obj"
	-@erase "$(INTDIR)\MKGridWnd.obj"
	-@erase "$(INTDIR)\MKHint.obj"
	-@erase "$(INTDIR)\MKPPS.obj"
	-@erase "$(INTDIR)\MKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MK.exe"
	-@erase "$(OUTDIR)\MK.ilk"
	-@erase "$(OUTDIR)\MK.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\MK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\DebugS/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MK.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MK.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolDS.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\MK.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\MK.exe" /pdbtype:sept /libpath:"..\Protocol\lib"
LINK32_OBJS= \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\GraphControl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\MK.obj" \
	"$(INTDIR)\MK.res" \
	"$(INTDIR)\MKChartView.obj" \
	"$(INTDIR)\MKDoc.obj" \
	"$(INTDIR)\MKEditDlg.obj" \
	"$(INTDIR)\MKGridWnd.obj" \
	"$(INTDIR)\MKHint.obj" \
	"$(INTDIR)\MKPPS.obj" \
	"$(INTDIR)\MKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=.\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\MK.exe"

!ELSE

ALL : "$(OUTDIR)\MK.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChartView.obj"
	-@erase "$(INTDIR)\GraphControl.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\MK.obj"
	-@erase "$(INTDIR)\MK.pch"
	-@erase "$(INTDIR)\MK.res"
	-@erase "$(INTDIR)\MKChartView.obj"
	-@erase "$(INTDIR)\MKDoc.obj"
	-@erase "$(INTDIR)\MKEditDlg.obj"
	-@erase "$(INTDIR)\MKGridWnd.obj"
	-@erase "$(INTDIR)\MKHint.obj"
	-@erase "$(INTDIR)\MKPPS.obj"
	-@erase "$(INTDIR)\MKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MK.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\MK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\ReleaseS/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MK.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MK.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolRS.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\MK.pdb" /machine:I386 /out:"$(OUTDIR)\MK.exe"\
 /libpath:"..\Protocol\lib"
LINK32_OBJS= \
	"$(INTDIR)\ChartView.obj" \
	"$(INTDIR)\GraphControl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\MK.obj" \
	"$(INTDIR)\MK.res" \
	"$(INTDIR)\MKChartView.obj" \
	"$(INTDIR)\MKDoc.obj" \
	"$(INTDIR)\MKEditDlg.obj" \
	"$(INTDIR)\MKGridWnd.obj" \
	"$(INTDIR)\MKHint.obj" \
	"$(INTDIR)\MKPPS.obj" \
	"$(INTDIR)\MKView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF


!IF "$(CFG)" == "MK - Win32 Release" || "$(CFG)" == "MK - Win32 Debug" ||\
 "$(CFG)" == "MK - Win32 Debug Simulate" || "$(CFG)" ==\
 "MK - Win32 Release Simulate"
SOURCE=.\ChartView.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_CHART=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\ChartView.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\GraphControl.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_GRAPH=\
	".\GraphControl.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\GraphControl.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_GRAPH=\
	".\GraphControl.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\GraphControl.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_GRAPH=\
	".\GraphControl.h"\


"$(INTDIR)\GraphControl.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_GRAPH=\
	".\GraphControl.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\GraphControl.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKPPS.h"\


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKPPS.h"\


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKPPS.h"\


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKPPS.h"\


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\Sample.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKPPS.h"\


"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKPPS.h"\


"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKPPS.h"\


"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKPPS.h"\


"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MK.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MK_CP=\
	"..\protocol\childfrm.h"\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKEditDlg.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\
	".\MKView.h"\


"$(INTDIR)\MK.obj" : $(SOURCE) $(DEP_CPP_MK_CP) "$(INTDIR)" "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MK_CP=\
	"..\protocol\childfrm.h"\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKEditDlg.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\
	".\MKView.h"\


"$(INTDIR)\MK.obj" : $(SOURCE) $(DEP_CPP_MK_CP) "$(INTDIR)" "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MK_CP=\
	"..\protocol\childfrm.h"\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKChartView.h"\
	".\MKDoc.h"\
	".\MKEditDlg.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\
	".\MKView.h"\


"$(INTDIR)\MK.obj" : $(SOURCE) $(DEP_CPP_MK_CP) "$(INTDIR)" "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MK_CP=\
	"..\protocol\childfrm.h"\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKEditDlg.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\
	".\MKView.h"\


"$(INTDIR)\MK.obj" : $(SOURCE) $(DEP_CPP_MK_CP) "$(INTDIR)" "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MK.rc
DEP_RSC_MK_RC=\
	".\res\bmp00001.bmp"\
	".\res\idr_main.ico"\
	".\res\idr_MKty.ico"\
	".\res\mainfram.bmp"\
	".\res\MK.ico"\
	".\res\MK.rc2"\
	".\res\MKDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\


"$(INTDIR)\MK.res" : $(SOURCE) $(DEP_RSC_MK_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MKChartView.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKCHA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKChartView.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\MKChartView.obj" : $(SOURCE) $(DEP_CPP_MKCHA) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKCHA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKChartView.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\MKChartView.obj" : $(SOURCE) $(DEP_CPP_MKCHA) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKCHA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKChartView.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKChartView.obj" : $(SOURCE) $(DEP_CPP_MKCHA) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKCHA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\ChartView.h"\
	".\GraphControl.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKChartView.h"\
	".\MKPPS.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\


"$(INTDIR)\MKChartView.obj" : $(SOURCE) $(DEP_CPP_MKCHA) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKDoc.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKDoc.obj" : $(SOURCE) $(DEP_CPP_MKDOC) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKDoc.obj" : $(SOURCE) $(DEP_CPP_MKDOC) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKDoc.obj" : $(SOURCE) $(DEP_CPP_MKDOC) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKDOC=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKDoc.obj" : $(SOURCE) $(DEP_CPP_MKDOC) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKEditDlg.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKEditDlg.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKEditDlg.obj" : $(SOURCE) $(DEP_CPP_MKEDI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKEditDlg.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKEditDlg.obj" : $(SOURCE) $(DEP_CPP_MKEDI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKEditDlg.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKEditDlg.obj" : $(SOURCE) $(DEP_CPP_MKEDI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKEDI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKEditDlg.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKEditDlg.obj" : $(SOURCE) $(DEP_CPP_MKEDI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKGridWnd.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKGridWnd.obj" : $(SOURCE) $(DEP_CPP_MKGRI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKGridWnd.obj" : $(SOURCE) $(DEP_CPP_MKGRI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKGridWnd.obj" : $(SOURCE) $(DEP_CPP_MKGRI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKGRI=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKGridWnd.obj" : $(SOURCE) $(DEP_CPP_MKGRI) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKHint.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKHint.obj" : $(SOURCE) $(DEP_CPP_MKHIN) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKHint.obj" : $(SOURCE) $(DEP_CPP_MKHIN) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKHint.obj" : $(SOURCE) $(DEP_CPP_MKHIN) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKHIN=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\MainFrm.h"\
	".\MK.h"\
	".\MKHint.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKHint.obj" : $(SOURCE) $(DEP_CPP_MKHIN) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKPPS.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKPPS=\
	"..\Protocol\GPPS.h"\
	"..\protocol\pps.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKPPS.obj" : $(SOURCE) $(DEP_CPP_MKPPS) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKPPS=\
	"..\Protocol\GPPS.h"\
	"..\protocol\pps.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKPPS.obj" : $(SOURCE) $(DEP_CPP_MKPPS) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKPPS=\
	"..\Protocol\GPPS.h"\
	"..\protocol\pps.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKPPS.obj" : $(SOURCE) $(DEP_CPP_MKPPS) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKPPS=\
	"..\Protocol\GPPS.h"\
	"..\protocol\pps.h"\
	".\MKPPS.h"\


"$(INTDIR)\MKPPS.obj" : $(SOURCE) $(DEP_CPP_MKPPS) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"


!ENDIF

SOURCE=.\MKView.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_MKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\MKView.h"\

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\MKView.obj" : $(SOURCE) $(DEP_CPP_MKVIE) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_MKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\MKView.h"\

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\MKView.obj" : $(SOURCE) $(DEP_CPP_MKVIE) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_MKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\MKView.h"\

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\MK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\MKView.obj" : $(SOURCE) $(DEP_CPP_MKVIE) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_MKVIE=\
	"..\Protocol\FB12Device.h"\
	"..\protocol\general.h"\
	"..\Protocol\GPPS.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\kineticsview.h"\
	"..\protocol\pps.h"\
	"..\Protocol\Protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	".\MK.h"\
	".\MKDoc.h"\
	".\MKGridWnd.h"\
	".\MKHint.h"\
	".\MKPPS.h"\
	".\MKView.h"\

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\MK.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\MKView.obj" : $(SOURCE) $(DEP_CPP_MKVIE) "$(INTDIR)"\
 "$(INTDIR)\MK.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MK - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\MK.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Debug Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	{$(INCLUDE)}"comdoc.h"\
	{$(INCLUDE)}"docmngr.h"\
	{$(INCLUDE)}"dscale.h"\
	{$(INCLUDE)}"graphdoc.h"\
	{$(INCLUDE)}"graphvw.h"\
	{$(INCLUDE)}"grphtip.h"\
	{$(INCLUDE)}"Ochart.h"\
	{$(INCLUDE)}"srgaxismanager.h"\
	{$(INCLUDE)}"srgcomp.h"\
	{$(INCLUDE)}"srgcompoundcomponent.h"\
	{$(INCLUDE)}"srgcompounddisplay.h"\
	{$(INCLUDE)}"srgcply.h"\
	{$(INCLUDE)}"srgdat.h"\
	{$(INCLUDE)}"srgdatawatcher.h"\
	{$(INCLUDE)}"srgexc.h"\
	{$(INCLUDE)}"srgfbck.h"\
	{$(INCLUDE)}"srggridlines.h"\
	{$(INCLUDE)}"srgposn.h"\
	{$(INCLUDE)}"srgraph.h"\
	{$(INCLUDE)}"srgscrollview.h"\
	{$(INCLUDE)}"srgtextpanel.h"\
	{$(INCLUDE)}"srgtickmarks.h"\

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\MK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MK - Win32 Release Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\MK.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MK.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF


!ENDIF

