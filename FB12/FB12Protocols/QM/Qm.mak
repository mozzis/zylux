# Microsoft Developer Studio Generated NMAKE File, Based on QM.DSP
!IF "$(CFG)" == ""
CFG=QM - Win32 Debug
!MESSAGE No configuration specified. Defaulting to QM - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "QM - Win32 Release" && "$(CFG)" != "QM - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "QM.MAK" CFG="QM - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "QM - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QM - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF

!IF  "$(CFG)" == "QM - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\QM.exe"

!ELSE

ALL : "$(OUTDIR)\QM.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\FB12Events.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\QM.obj"
	-@erase "$(INTDIR)\QM.res"
	-@erase "$(INTDIR)\QM.pch"
	-@erase "$(INTDIR)\QMCommandLineInfo.obj"
	-@erase "$(INTDIR)\QMGridWnd.obj"
	-@erase "$(INTDIR)\QMView.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\QM.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\QM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QM.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QM.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\QM.pdb"\
 /machine:I386 /out:"$(OUTDIR)\QM.exe"
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\FB12Events.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\QM.obj" \
	"$(INTDIR)\QM.res" \
	"$(INTDIR)\QMCommandLineInfo.obj" \
	"$(INTDIR)\QMGridWnd.obj" \
	"$(INTDIR)\QMView.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\QM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "QM - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\QM.exe"

!ELSE

ALL : "$(OUTDIR)\QM.exe"

!ENDIF

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\FB12Events.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\QM.obj"
	-@erase "$(INTDIR)\QM.res"
	-@erase "$(INTDIR)\QM.pch"
	-@erase "$(INTDIR)\QMCommandLineInfo.obj"
	-@erase "$(INTDIR)\QMGridWnd.obj"
	-@erase "$(INTDIR)\QMView.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\QM.exe"
	-@erase "$(OUTDIR)\QM.ilk"
	-@erase "$(OUTDIR)\QM.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\QM.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QM.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QM.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\QM.pdb" /debug /machine:I386 /out:"$(OUTDIR)\QM.exe"\
 /pdbtype:sept
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\FB12Events.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\QM.obj" \
	"$(INTDIR)\QM.res" \
	"$(INTDIR)\QMCommandLineInfo.obj" \
	"$(INTDIR)\QMGridWnd.obj" \
	"$(INTDIR)\QMView.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\QM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF


!IF "$(CFG)" == "QM - Win32 Release" || "$(CFG)" == "QM - Win32 Debug"
SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	"..\..\FB12\FB12.h"\
	".\ChildFrm.h"\
	".\StdAfx.h"\

NODEP_CPP_CHILD=\
	".\QM.h"\


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\FB12Events.cpp
DEP_CPP_FB12E=\
	"..\..\FB12\FB12.h"\
	".\FB12Events.h"\
	".\StdAfx.h"\

NODEP_CPP_FB12E=\
	".\QM.h"\


"$(INTDIR)\FB12Events.obj" : $(SOURCE) $(DEP_CPP_FB12E) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\..\FB12\FB12.h"\
	".\FB12Events.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\StdAfx.h"\

NODEP_CPP_MAINF=\
	".\QM.h"\


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\QM.cpp
DEP_CPP_QM_CP=\
	"..\..\FB12\FB12.h"\
	".\ChildFrm.h"\
	".\FB12Events.h"\
	".\MainFrm.h"\
	".\QM.h"\
	".\QMCommandLineInfo.h"\
	".\QMDoc.h"\
	".\QMGridWnd.h"\
	".\QMView.h"\
	".\RunBar.h"\
	".\StdAfx.h"\

NODEP_CPP_QM_CP=\
	".\QMDoc.h"\


"$(INTDIR)\QM.obj" : $(SOURCE) $(DEP_CPP_QM_CP) "$(INTDIR)" "$(INTDIR)\QM.pch"


SOURCE=.\QM.rc
DEP_RSC_QM_RC=\
	".\res\bitmap1.bmp"\
	".\res\QM.ico"\
	".\res\QM.rc2"\
	".\res\QMDoc.ico"\
	".\res\Toolbar.bmp"\


"$(INTDIR)\QM.res" : $(SOURCE) $(DEP_RSC_QM_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\QMCommandLineInfo.cpp
DEP_CPP_QMCOM=\
	"..\..\FB12\FB12.h"\
	".\QMCommandLineInfo.h"\
	".\StdAfx.h"\

NODEP_CPP_QMCOM=\
	".\QM.h"\


"$(INTDIR)\QMCommandLineInfo.obj" : $(SOURCE) $(DEP_CPP_QMCOM) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\QMGridWnd.cpp
DEP_CPP_QMGRI=\
	"..\..\FB12\FB12.h"\
	".\QMGridWnd.h"\
	".\StdAfx.h"\

NODEP_CPP_QMGRI=\
	".\QM.h"\


"$(INTDIR)\QMGridWnd.obj" : $(SOURCE) $(DEP_CPP_QMGRI) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\QMView.cpp
DEP_CPP_QMVIE=\
	"..\..\FB12\FB12.h"\
	".\QMGridWnd.h"\
	".\QMView.h"\
	".\StdAfx.h"\

NODEP_CPP_QMVIE=\
	".\QM.h"\
	".\QMDoc.h"\


"$(INTDIR)\QMView.obj" : $(SOURCE) $(DEP_CPP_QMVIE) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\RunBar.cpp
DEP_CPP_RUNBA=\
	"..\..\FB12\FB12.h"\
	"..\..\FB12\FB12_i.c"\
	".\FB12Events.h"\
	".\RunBar.h"\
	".\StdAfx.h"\

NODEP_CPP_RUNBA=\
	".\QM.h"\


"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\QM.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\..\FB12\FB12.h"\
	".\StdAfx.h"\


!IF  "$(CFG)" == "QM - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\QM.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QM.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "QM - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\QM.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QM.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF


!ENDIF

