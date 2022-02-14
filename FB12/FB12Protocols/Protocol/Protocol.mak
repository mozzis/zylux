# Microsoft Developer Studio Generated NMAKE File, Based on Protocol.dsp
!IF "$(CFG)" == ""
CFG=Protocol - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to Protocol - Win32 Debug\
 Simulate.
!ENDIF 

!IF "$(CFG)" != "Protocol - Win32 Release" && "$(CFG)" !=\
 "Protocol - Win32 Debug" && "$(CFG)" != "Protocol - Win32 Debug Simulate" &&\
 "$(CFG)" != "Protocol - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Protocol.mak" CFG="Protocol - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Protocol - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Debug Simulate" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "Protocol - Win32 Release Simulate" (based on\
 "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Protocol - Win32 Release"

OUTDIR=.\lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ProtocolR.lib"

!ELSE 

ALL : "$(OUTDIR)\ProtocolR.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Actwatch.obj"
	-@erase "$(INTDIR)\Excel95.obj"
	-@erase "$(INTDIR)\Excel97.obj"
	-@erase "$(INTDIR)\FB12Device.obj"
	-@erase "$(INTDIR)\General.obj"
	-@erase "$(INTDIR)\GPPS.obj"
	-@erase "$(INTDIR)\GraphFrm.obj"
	-@erase "$(INTDIR)\GridFrm.obj"
	-@erase "$(INTDIR)\GridView.obj"
	-@erase "$(INTDIR)\Kinetics.obj"
	-@erase "$(INTDIR)\KineticsView.obj"
	-@erase "$(INTDIR)\PPS.obj"
	-@erase "$(INTDIR)\ProtCmdLineInfo.obj"
	-@erase "$(INTDIR)\Protocol.obj"
	-@erase "$(INTDIR)\ProtocolDlg.obj"
	-@erase "$(INTDIR)\ProtocolDoc.obj"
	-@erase "$(INTDIR)\ProtocolFrame.obj"
	-@erase "$(INTDIR)\ProtocolGridWnd.obj"
	-@erase "$(INTDIR)\Replicate.obj"
	-@erase "$(INTDIR)\SaveAsDlg.obj"
	-@erase "$(INTDIR)\SCSerialNumber.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ProtocolR.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /I "resources" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\Protocol.pch" /YX\
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

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Protocol.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtocolR.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Actwatch.obj" \
	"$(INTDIR)\Excel95.obj" \
	"$(INTDIR)\Excel97.obj" \
	"$(INTDIR)\FB12Device.obj" \
	"$(INTDIR)\General.obj" \
	"$(INTDIR)\GPPS.obj" \
	"$(INTDIR)\GraphFrm.obj" \
	"$(INTDIR)\GridFrm.obj" \
	"$(INTDIR)\GridView.obj" \
	"$(INTDIR)\Kinetics.obj" \
	"$(INTDIR)\KineticsView.obj" \
	"$(INTDIR)\PPS.obj" \
	"$(INTDIR)\ProtCmdLineInfo.obj" \
	"$(INTDIR)\Protocol.obj" \
	"$(INTDIR)\ProtocolDlg.obj" \
	"$(INTDIR)\ProtocolDoc.obj" \
	"$(INTDIR)\ProtocolFrame.obj" \
	"$(INTDIR)\ProtocolGridWnd.obj" \
	"$(INTDIR)\Replicate.obj" \
	"$(INTDIR)\SaveAsDlg.obj" \
	"$(INTDIR)\SCSerialNumber.obj"

"$(OUTDIR)\ProtocolR.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

OUTDIR=.\lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ProtocolD.lib"

!ELSE 

ALL : "$(OUTDIR)\ProtocolD.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Actwatch.obj"
	-@erase "$(INTDIR)\Excel95.obj"
	-@erase "$(INTDIR)\Excel97.obj"
	-@erase "$(INTDIR)\FB12Device.obj"
	-@erase "$(INTDIR)\General.obj"
	-@erase "$(INTDIR)\GPPS.obj"
	-@erase "$(INTDIR)\GraphFrm.obj"
	-@erase "$(INTDIR)\GridFrm.obj"
	-@erase "$(INTDIR)\GridView.obj"
	-@erase "$(INTDIR)\Kinetics.obj"
	-@erase "$(INTDIR)\KineticsView.obj"
	-@erase "$(INTDIR)\PPS.obj"
	-@erase "$(INTDIR)\ProtCmdLineInfo.obj"
	-@erase "$(INTDIR)\Protocol.obj"
	-@erase "$(INTDIR)\ProtocolDlg.obj"
	-@erase "$(INTDIR)\ProtocolDoc.obj"
	-@erase "$(INTDIR)\ProtocolFrame.obj"
	-@erase "$(INTDIR)\ProtocolGridWnd.obj"
	-@erase "$(INTDIR)\Replicate.obj"
	-@erase "$(INTDIR)\SaveAsDlg.obj"
	-@erase "$(INTDIR)\SCSerialNumber.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ProtocolD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "include" /I "resources" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\Protocol.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Protocol.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtocolD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Actwatch.obj" \
	"$(INTDIR)\Excel95.obj" \
	"$(INTDIR)\Excel97.obj" \
	"$(INTDIR)\FB12Device.obj" \
	"$(INTDIR)\General.obj" \
	"$(INTDIR)\GPPS.obj" \
	"$(INTDIR)\GraphFrm.obj" \
	"$(INTDIR)\GridFrm.obj" \
	"$(INTDIR)\GridView.obj" \
	"$(INTDIR)\Kinetics.obj" \
	"$(INTDIR)\KineticsView.obj" \
	"$(INTDIR)\PPS.obj" \
	"$(INTDIR)\ProtCmdLineInfo.obj" \
	"$(INTDIR)\Protocol.obj" \
	"$(INTDIR)\ProtocolDlg.obj" \
	"$(INTDIR)\ProtocolDoc.obj" \
	"$(INTDIR)\ProtocolFrame.obj" \
	"$(INTDIR)\ProtocolGridWnd.obj" \
	"$(INTDIR)\Replicate.obj" \
	"$(INTDIR)\SaveAsDlg.obj" \
	"$(INTDIR)\SCSerialNumber.obj"

"$(OUTDIR)\ProtocolD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

OUTDIR=.\lib
INTDIR=.\DebugS
# Begin Custom Macros
OutDir=.\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ProtocolDS.lib"

!ELSE 

ALL : "$(OUTDIR)\ProtocolDS.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Actwatch.obj"
	-@erase "$(INTDIR)\Excel95.obj"
	-@erase "$(INTDIR)\Excel97.obj"
	-@erase "$(INTDIR)\FB12Device.obj"
	-@erase "$(INTDIR)\General.obj"
	-@erase "$(INTDIR)\GPPS.obj"
	-@erase "$(INTDIR)\GraphFrm.obj"
	-@erase "$(INTDIR)\GridFrm.obj"
	-@erase "$(INTDIR)\GridView.obj"
	-@erase "$(INTDIR)\Kinetics.obj"
	-@erase "$(INTDIR)\KineticsView.obj"
	-@erase "$(INTDIR)\PPS.obj"
	-@erase "$(INTDIR)\ProtCmdLineInfo.obj"
	-@erase "$(INTDIR)\Protocol.obj"
	-@erase "$(INTDIR)\ProtocolDlg.obj"
	-@erase "$(INTDIR)\ProtocolDoc.obj"
	-@erase "$(INTDIR)\ProtocolFrame.obj"
	-@erase "$(INTDIR)\ProtocolGridWnd.obj"
	-@erase "$(INTDIR)\Replicate.obj"
	-@erase "$(INTDIR)\SaveAsDlg.obj"
	-@erase "$(INTDIR)\SCSerialNumber.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ProtocolDS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "resources" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\Protocol.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Protocol.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtocolDS.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Actwatch.obj" \
	"$(INTDIR)\Excel95.obj" \
	"$(INTDIR)\Excel97.obj" \
	"$(INTDIR)\FB12Device.obj" \
	"$(INTDIR)\General.obj" \
	"$(INTDIR)\GPPS.obj" \
	"$(INTDIR)\GraphFrm.obj" \
	"$(INTDIR)\GridFrm.obj" \
	"$(INTDIR)\GridView.obj" \
	"$(INTDIR)\Kinetics.obj" \
	"$(INTDIR)\KineticsView.obj" \
	"$(INTDIR)\PPS.obj" \
	"$(INTDIR)\ProtCmdLineInfo.obj" \
	"$(INTDIR)\Protocol.obj" \
	"$(INTDIR)\ProtocolDlg.obj" \
	"$(INTDIR)\ProtocolDoc.obj" \
	"$(INTDIR)\ProtocolFrame.obj" \
	"$(INTDIR)\ProtocolGridWnd.obj" \
	"$(INTDIR)\Replicate.obj" \
	"$(INTDIR)\SaveAsDlg.obj" \
	"$(INTDIR)\SCSerialNumber.obj"

"$(OUTDIR)\ProtocolDS.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

OUTDIR=.\lib
INTDIR=.\ReleaseS
# Begin Custom Macros
OutDir=.\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ProtocolRS.lib"

!ELSE 

ALL : "$(OUTDIR)\ProtocolRS.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Actwatch.obj"
	-@erase "$(INTDIR)\Excel95.obj"
	-@erase "$(INTDIR)\Excel97.obj"
	-@erase "$(INTDIR)\FB12Device.obj"
	-@erase "$(INTDIR)\General.obj"
	-@erase "$(INTDIR)\GPPS.obj"
	-@erase "$(INTDIR)\GraphFrm.obj"
	-@erase "$(INTDIR)\GridFrm.obj"
	-@erase "$(INTDIR)\GridView.obj"
	-@erase "$(INTDIR)\Kinetics.obj"
	-@erase "$(INTDIR)\KineticsView.obj"
	-@erase "$(INTDIR)\PPS.obj"
	-@erase "$(INTDIR)\ProtCmdLineInfo.obj"
	-@erase "$(INTDIR)\Protocol.obj"
	-@erase "$(INTDIR)\ProtocolDlg.obj"
	-@erase "$(INTDIR)\ProtocolDoc.obj"
	-@erase "$(INTDIR)\ProtocolFrame.obj"
	-@erase "$(INTDIR)\ProtocolGridWnd.obj"
	-@erase "$(INTDIR)\Replicate.obj"
	-@erase "$(INTDIR)\SaveAsDlg.obj"
	-@erase "$(INTDIR)\SCSerialNumber.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ProtocolRS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /I "resources" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\Protocol.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Protocol.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtocolRS.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Actwatch.obj" \
	"$(INTDIR)\Excel95.obj" \
	"$(INTDIR)\Excel97.obj" \
	"$(INTDIR)\FB12Device.obj" \
	"$(INTDIR)\General.obj" \
	"$(INTDIR)\GPPS.obj" \
	"$(INTDIR)\GraphFrm.obj" \
	"$(INTDIR)\GridFrm.obj" \
	"$(INTDIR)\GridView.obj" \
	"$(INTDIR)\Kinetics.obj" \
	"$(INTDIR)\KineticsView.obj" \
	"$(INTDIR)\PPS.obj" \
	"$(INTDIR)\ProtCmdLineInfo.obj" \
	"$(INTDIR)\Protocol.obj" \
	"$(INTDIR)\ProtocolDlg.obj" \
	"$(INTDIR)\ProtocolDoc.obj" \
	"$(INTDIR)\ProtocolFrame.obj" \
	"$(INTDIR)\ProtocolGridWnd.obj" \
	"$(INTDIR)\Replicate.obj" \
	"$(INTDIR)\SaveAsDlg.obj" \
	"$(INTDIR)\SCSerialNumber.obj"

"$(OUTDIR)\ProtocolRS.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Protocol - Win32 Release" || "$(CFG)" ==\
 "Protocol - Win32 Debug" || "$(CFG)" == "Protocol - Win32 Debug Simulate" ||\
 "$(CFG)" == "Protocol - Win32 Release Simulate"
SOURCE=.\Actwatch.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_ACTWA=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Actwatch.obj" : $(SOURCE) $(DEP_CPP_ACTWA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_ACTWA=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Actwatch.obj" : $(SOURCE) $(DEP_CPP_ACTWA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_ACTWA=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Actwatch.obj" : $(SOURCE) $(DEP_CPP_ACTWA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_ACTWA=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Actwatch.obj" : $(SOURCE) $(DEP_CPP_ACTWA) "$(INTDIR)"


!ENDIF 

SOURCE=.\Excel95.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_EXCEL=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\xl5en32.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel95.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_EXCEL=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\xl5en32.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel95.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_EXCEL=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\xl5en32.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel95.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_EXCEL=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\xl5en32.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel95.obj" : $(SOURCE) $(DEP_CPP_EXCEL) "$(INTDIR)"


!ENDIF 

SOURCE=.\Excel97.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_EXCEL9=\
	".\excel8.olb"\
	".\General.h"\
	".\mso97.dll"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\vbeext1.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel97.obj" : $(SOURCE) $(DEP_CPP_EXCEL9) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_EXCEL9=\
	".\excel8.olb"\
	".\General.h"\
	".\mso97.dll"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\vbeext1.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel97.obj" : $(SOURCE) $(DEP_CPP_EXCEL9) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_EXCEL9=\
	".\excel8.olb"\
	".\General.h"\
	".\mso97.dll"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\vbeext1.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel97.obj" : $(SOURCE) $(DEP_CPP_EXCEL9) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_EXCEL9=\
	".\excel8.olb"\
	".\General.h"\
	".\mso97.dll"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	".\vbeext1.olb"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Excel97.obj" : $(SOURCE) $(DEP_CPP_EXCEL9) "$(INTDIR)"


!ENDIF 

SOURCE=.\FB12Device.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_FB12D=\
	".\FB12Device.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\FB12Device.obj" : $(SOURCE) $(DEP_CPP_FB12D) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_FB12D=\
	".\FB12Device.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\FB12Device.obj" : $(SOURCE) $(DEP_CPP_FB12D) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_FB12D=\
	".\FB12Device.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\FB12Device.obj" : $(SOURCE) $(DEP_CPP_FB12D) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_FB12D=\
	".\FB12Device.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\FB12Device.obj" : $(SOURCE) $(DEP_CPP_FB12D) "$(INTDIR)"


!ENDIF 

SOURCE=.\General.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_GENER=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\General.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_GENER=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\General.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_GENER=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\General.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_GENER=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\General.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"


!ENDIF 

SOURCE=.\GPPS.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_GPPS_=\
	".\GPPS.h"\
	".\PPS.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GPPS.obj" : $(SOURCE) $(DEP_CPP_GPPS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_GPPS_=\
	".\GPPS.h"\
	".\PPS.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GPPS.obj" : $(SOURCE) $(DEP_CPP_GPPS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_GPPS_=\
	".\GPPS.h"\
	".\PPS.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GPPS.obj" : $(SOURCE) $(DEP_CPP_GPPS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_GPPS_=\
	".\GPPS.h"\
	".\PPS.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GPPS.obj" : $(SOURCE) $(DEP_CPP_GPPS_) "$(INTDIR)"


!ENDIF 

SOURCE=.\GraphFrm.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_GRAPH=\
	".\FB12Device.h"\
	".\GraphFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GraphFrm.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_GRAPH=\
	".\FB12Device.h"\
	".\GraphFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GraphFrm.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_GRAPH=\
	".\FB12Device.h"\
	".\GraphFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GraphFrm.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_GRAPH=\
	".\FB12Device.h"\
	".\GraphFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GraphFrm.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"


!ENDIF 

SOURCE=.\GridFrm.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_GRIDF=\
	".\FB12Device.h"\
	".\GridFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridFrm.obj" : $(SOURCE) $(DEP_CPP_GRIDF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_GRIDF=\
	".\FB12Device.h"\
	".\GridFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridFrm.obj" : $(SOURCE) $(DEP_CPP_GRIDF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_GRIDF=\
	".\FB12Device.h"\
	".\GridFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridFrm.obj" : $(SOURCE) $(DEP_CPP_GRIDF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_GRIDF=\
	".\FB12Device.h"\
	".\GridFrm.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridFrm.obj" : $(SOURCE) $(DEP_CPP_GRIDF) "$(INTDIR)"


!ENDIF 

SOURCE=.\GridView.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_GRIDV=\
	".\FB12Device.h"\
	".\GridView.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridView.obj" : $(SOURCE) $(DEP_CPP_GRIDV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_GRIDV=\
	".\FB12Device.h"\
	".\GridView.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridView.obj" : $(SOURCE) $(DEP_CPP_GRIDV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_GRIDV=\
	".\FB12Device.h"\
	".\GridView.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridView.obj" : $(SOURCE) $(DEP_CPP_GRIDV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_GRIDV=\
	".\FB12Device.h"\
	".\GridView.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\GridView.obj" : $(SOURCE) $(DEP_CPP_GRIDV) "$(INTDIR)"


!ENDIF 

SOURCE=.\Kinetics.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_KINET=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Kinetics.obj" : $(SOURCE) $(DEP_CPP_KINET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_KINET=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Kinetics.obj" : $(SOURCE) $(DEP_CPP_KINET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_KINET=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Kinetics.obj" : $(SOURCE) $(DEP_CPP_KINET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_KINET=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Kinetics.obj" : $(SOURCE) $(DEP_CPP_KINET) "$(INTDIR)"


!ENDIF 

SOURCE=.\KineticsView.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_KINETI=\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\KineticsView.obj" : $(SOURCE) $(DEP_CPP_KINETI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_KINETI=\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\KineticsView.obj" : $(SOURCE) $(DEP_CPP_KINETI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_KINETI=\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\KineticsView.obj" : $(SOURCE) $(DEP_CPP_KINETI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_KINETI=\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\KineticsView.obj" : $(SOURCE) $(DEP_CPP_KINETI) "$(INTDIR)"


!ENDIF 

SOURCE=.\PPS.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PPS_C=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\PPS.obj" : $(SOURCE) $(DEP_CPP_PPS_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PPS_C=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\PPS.obj" : $(SOURCE) $(DEP_CPP_PPS_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PPS_C=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\PPS.obj" : $(SOURCE) $(DEP_CPP_PPS_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PPS_C=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\PPS.obj" : $(SOURCE) $(DEP_CPP_PPS_C) "$(INTDIR)"


!ENDIF 

SOURCE=.\ProtCmdLineInfo.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTC=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtCmdLineInfo.obj" : $(SOURCE) $(DEP_CPP_PROTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTC=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtCmdLineInfo.obj" : $(SOURCE) $(DEP_CPP_PROTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTC=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtCmdLineInfo.obj" : $(SOURCE) $(DEP_CPP_PROTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTC=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtCmdLineInfo.obj" : $(SOURCE) $(DEP_CPP_PROTC) "$(INTDIR)"


!ENDIF 

SOURCE=.\Protocol.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTO=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTO=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTO=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTO=\
	".\Actwatch.h"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ENDIF 

SOURCE=.\ProtocolDlg.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTOC=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDlg.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDlg.obj" : $(SOURCE) $(DEP_CPP_PROTOC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTOC=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDlg.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDlg.obj" : $(SOURCE) $(DEP_CPP_PROTOC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTOC=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDlg.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDlg.obj" : $(SOURCE) $(DEP_CPP_PROTOC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTOC=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDlg.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDlg.obj" : $(SOURCE) $(DEP_CPP_PROTOC) "$(INTDIR)"


!ENDIF 

SOURCE=.\ProtocolDoc.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTOCO=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDoc.obj" : $(SOURCE) $(DEP_CPP_PROTOCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTOCO=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDoc.obj" : $(SOURCE) $(DEP_CPP_PROTOCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTOCO=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDoc.obj" : $(SOURCE) $(DEP_CPP_PROTOCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTOCO=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolDoc.obj" : $(SOURCE) $(DEP_CPP_PROTOCO) "$(INTDIR)"


!ENDIF 

SOURCE=.\ProtocolFrame.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTOCOL=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolFrame.obj" : $(SOURCE) $(DEP_CPP_PROTOCOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTOCOL=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolFrame.obj" : $(SOURCE) $(DEP_CPP_PROTOCOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTOCOL=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolFrame.obj" : $(SOURCE) $(DEP_CPP_PROTOCOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTOCOL=\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolFrame.obj" : $(SOURCE) $(DEP_CPP_PROTOCOL) "$(INTDIR)"


!ENDIF 

SOURCE=.\ProtocolGridWnd.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_PROTOCOLG=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolGridWnd.obj" : $(SOURCE) $(DEP_CPP_PROTOCOLG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_PROTOCOLG=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolGridWnd.obj" : $(SOURCE) $(DEP_CPP_PROTOCOLG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_PROTOCOLG=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolGridWnd.obj" : $(SOURCE) $(DEP_CPP_PROTOCOLG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_PROTOCOLG=\
	".\General.h"\
	".\ProtocolGridWnd.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\ProtocolGridWnd.obj" : $(SOURCE) $(DEP_CPP_PROTOCOLG) "$(INTDIR)"


!ENDIF 

SOURCE=.\Replicate.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_REPLI=\
	".\Replicate.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Replicate.obj" : $(SOURCE) $(DEP_CPP_REPLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_REPLI=\
	".\Replicate.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Replicate.obj" : $(SOURCE) $(DEP_CPP_REPLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_REPLI=\
	".\Replicate.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Replicate.obj" : $(SOURCE) $(DEP_CPP_REPLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_REPLI=\
	".\Replicate.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\Replicate.obj" : $(SOURCE) $(DEP_CPP_REPLI) "$(INTDIR)"


!ENDIF 

SOURCE=.\SaveAsDlg.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_SAVEA=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SaveAsDlg.obj" : $(SOURCE) $(DEP_CPP_SAVEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_SAVEA=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SaveAsDlg.obj" : $(SOURCE) $(DEP_CPP_SAVEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_SAVEA=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SaveAsDlg.obj" : $(SOURCE) $(DEP_CPP_SAVEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_SAVEA=\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\KineticsView.h"\
	".\PPS.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\SaveAsDlg.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SaveAsDlg.obj" : $(SOURCE) $(DEP_CPP_SAVEA) "$(INTDIR)"


!ENDIF 

SOURCE=.\SCSerialNumber.cpp

!IF  "$(CFG)" == "Protocol - Win32 Release"

DEP_CPP_SCSER=\
	".\General.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SCSerialNumber.obj" : $(SOURCE) $(DEP_CPP_SCSER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug"

DEP_CPP_SCSER=\
	".\General.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SCSerialNumber.obj" : $(SOURCE) $(DEP_CPP_SCSER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Debug Simulate"

DEP_CPP_SCSER=\
	".\General.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SCSerialNumber.obj" : $(SOURCE) $(DEP_CPP_SCSER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Protocol - Win32 Release Simulate"

DEP_CPP_SCSER=\
	".\General.h"\
	".\SCSerialNumber.h"\
	".\StdAfx.h"\
	"d:\objective chart 1.1\include\comdoc.h"\
	"d:\objective chart 1.1\include\docmngr.h"\
	"d:\objective chart 1.1\include\dscale.h"\
	"d:\objective chart 1.1\include\graphdoc.h"\
	"d:\objective chart 1.1\include\graphvw.h"\
	"d:\objective chart 1.1\include\grphtip.h"\
	"d:\objective chart 1.1\include\ochart.h"\
	"d:\objective chart 1.1\include\srgaxismanager.h"\
	"d:\objective chart 1.1\include\srgcomp.h"\
	"d:\objective chart 1.1\include\srgcompoundcomponent.h"\
	"d:\objective chart 1.1\include\srgcompounddisplay.h"\
	"d:\objective chart 1.1\include\srgcply.h"\
	"d:\objective chart 1.1\include\srgdat.h"\
	"d:\objective chart 1.1\include\srgdatawatcher.h"\
	"d:\objective chart 1.1\include\srgexc.h"\
	"d:\objective chart 1.1\include\srgfbck.h"\
	"d:\objective chart 1.1\include\srggridlines.h"\
	"d:\objective chart 1.1\include\srgposn.h"\
	"d:\objective chart 1.1\include\srgraph.h"\
	"d:\objective chart 1.1\include\srgscrollview.h"\
	"d:\objective chart 1.1\include\srgtextpanel.h"\
	"d:\objective chart 1.1\include\srgtickmarks.h"\
	"d:\objective grid 5.01\include\gxbrowse.inl"\
	"d:\objective grid 5.01\include\gxcrtf.h"\
	

"$(INTDIR)\SCSerialNumber.obj" : $(SOURCE) $(DEP_CPP_SCSER) "$(INTDIR)"


!ENDIF 


!ENDIF 

