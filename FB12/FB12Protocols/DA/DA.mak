# Microsoft Developer Studio Generated NMAKE File, Based on DA.DSP
!IF "$(CFG)" == ""
CFG=DA - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to DA - Win32 Debug Simulate.
!ENDIF 

!IF "$(CFG)" != "DA - Win32 Release" && "$(CFG)" != "DA - Win32 Debug" &&\
 "$(CFG)" != "DA - Win32 Debug Simulate" && "$(CFG)" !=\
 "DA - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DA.MAK" CFG="DA - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DA - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "DA - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DA - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DA.exe"

!ELSE 

ALL : "$(OUTDIR)\DA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DA.obj"
	-@erase "$(INTDIR)\DA.pch"
	-@erase "$(INTDIR)\DA.res"
	-@erase "$(INTDIR)\DADoc.obj"
	-@erase "$(INTDIR)\DAEditDlg.obj"
	-@erase "$(INTDIR)\DAGridWnd.obj"
	-@erase "$(INTDIR)\DAPPS.obj"
	-@erase "$(INTDIR)\DAView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\DA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolR.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\DA.pdb" /machine:I386 /out:"$(OUTDIR)\DA.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\DA.obj" \
	"$(INTDIR)\DA.res" \
	"$(INTDIR)\DADoc.obj" \
	"$(INTDIR)\DAEditDlg.obj" \
	"$(INTDIR)\DAGridWnd.obj" \
	"$(INTDIR)\DAPPS.obj" \
	"$(INTDIR)\DAView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DA.exe"

!ELSE 

ALL : "$(OUTDIR)\DA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DA.obj"
	-@erase "$(INTDIR)\DA.pch"
	-@erase "$(INTDIR)\DA.res"
	-@erase "$(INTDIR)\DADoc.obj"
	-@erase "$(INTDIR)\DAEditDlg.obj"
	-@erase "$(INTDIR)\DAGridWnd.obj"
	-@erase "$(INTDIR)\DAPPS.obj"
	-@erase "$(INTDIR)\DAView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\DA.exe"
	-@erase "$(OUTDIR)\DA.ilk"
	-@erase "$(OUTDIR)\DA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolD.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\DA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\DA.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\DA.obj" \
	"$(INTDIR)\DA.res" \
	"$(INTDIR)\DADoc.obj" \
	"$(INTDIR)\DAEditDlg.obj" \
	"$(INTDIR)\DAGridWnd.obj" \
	"$(INTDIR)\DAPPS.obj" \
	"$(INTDIR)\DAView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=.\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DA.exe"

!ELSE 

ALL : "$(OUTDIR)\DA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DA.obj"
	-@erase "$(INTDIR)\DA.pch"
	-@erase "$(INTDIR)\DA.res"
	-@erase "$(INTDIR)\DADoc.obj"
	-@erase "$(INTDIR)\DAEditDlg.obj"
	-@erase "$(INTDIR)\DAGridWnd.obj"
	-@erase "$(INTDIR)\DAPPS.obj"
	-@erase "$(INTDIR)\DAView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\DA.exe"
	-@erase "$(OUTDIR)\DA.ilk"
	-@erase "$(OUTDIR)\DA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\DA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolDS.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\DA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\DA.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\DA.obj" \
	"$(INTDIR)\DA.res" \
	"$(INTDIR)\DADoc.obj" \
	"$(INTDIR)\DAEditDlg.obj" \
	"$(INTDIR)\DAGridWnd.obj" \
	"$(INTDIR)\DAPPS.obj" \
	"$(INTDIR)\DAView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=.\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DA.exe"

!ELSE 

ALL : "$(OUTDIR)\DA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DA.obj"
	-@erase "$(INTDIR)\DA.pch"
	-@erase "$(INTDIR)\DA.res"
	-@erase "$(INTDIR)\DADoc.obj"
	-@erase "$(INTDIR)\DAEditDlg.obj"
	-@erase "$(INTDIR)\DAGridWnd.obj"
	-@erase "$(INTDIR)\DAPPS.obj"
	-@erase "$(INTDIR)\DAView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\DA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\DA.pch"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib ProtocolRS.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\DA.pdb" /machine:I386 /out:"$(OUTDIR)\DA.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\DA.obj" \
	"$(INTDIR)\DA.res" \
	"$(INTDIR)\DADoc.obj" \
	"$(INTDIR)\DAEditDlg.obj" \
	"$(INTDIR)\DAGridWnd.obj" \
	"$(INTDIR)\DAPPS.obj" \
	"$(INTDIR)\DAView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "DA - Win32 Release" || "$(CFG)" == "DA - Win32 Debug" ||\
 "$(CFG)" == "DA - Win32 Debug Simulate" || "$(CFG)" ==\
 "DA - Win32 Release Simulate"
SOURCE=.\DA.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_DA_CP=\
	"..\protocol\childfrm.h"\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAEditDlg.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DA.obj" : $(SOURCE) $(DEP_CPP_DA_CP) "$(INTDIR)" "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_DA_CP=\
	"..\protocol\childfrm.h"\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAEditDlg.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DA.obj" : $(SOURCE) $(DEP_CPP_DA_CP) "$(INTDIR)" "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_DA_CP=\
	"..\protocol\childfrm.h"\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAEditDlg.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DA.obj" : $(SOURCE) $(DEP_CPP_DA_CP) "$(INTDIR)" "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_DA_CP=\
	"..\protocol\childfrm.h"\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAEditDlg.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DA.obj" : $(SOURCE) $(DEP_CPP_DA_CP) "$(INTDIR)" "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\DA.rc
DEP_RSC_DA_RC=\
	".\res\bmp00001.bmp"\
	".\res\DA.ico"\
	".\res\DA.rc2"\
	".\res\DADoc.ico"\
	".\res\idr_DAty.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	

"$(INTDIR)\DA.res" : $(SOURCE) $(DEP_RSC_DA_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DADoc.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_DADOC=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DADoc.obj" : $(SOURCE) $(DEP_CPP_DADOC) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_DADOC=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DADoc.obj" : $(SOURCE) $(DEP_CPP_DADOC) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_DADOC=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DADoc.obj" : $(SOURCE) $(DEP_CPP_DADOC) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_DADOC=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DADoc.obj" : $(SOURCE) $(DEP_CPP_DADOC) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\DAEditDlg.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_DAEDI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\DA.h"\
	".\DAEditDlg.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAEditDlg.obj" : $(SOURCE) $(DEP_CPP_DAEDI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_DAEDI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\DA.h"\
	".\DAEditDlg.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAEditDlg.obj" : $(SOURCE) $(DEP_CPP_DAEDI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_DAEDI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\DA.h"\
	".\DAEditDlg.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAEditDlg.obj" : $(SOURCE) $(DEP_CPP_DAEDI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_DAEDI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldlg.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	".\DA.h"\
	".\DAEditDlg.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAEditDlg.obj" : $(SOURCE) $(DEP_CPP_DAEDI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\DAGridWnd.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_DAGRI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	".\DA.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAGridWnd.obj" : $(SOURCE) $(DEP_CPP_DAGRI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_DAGRI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	".\DA.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAGridWnd.obj" : $(SOURCE) $(DEP_CPP_DAGRI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_DAGRI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\DAGridWnd.obj" : $(SOURCE) $(DEP_CPP_DAGRI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_DAGRI=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	".\DA.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\DAGridWnd.obj" : $(SOURCE) $(DEP_CPP_DAGRI) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\DAPPS.cpp
DEP_CPP_DAPPS=\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	".\DAPPS.h"\
	

"$(INTDIR)\DAPPS.obj" : $(SOURCE) $(DEP_CPP_DAPPS) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


SOURCE=.\DAView.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_DAVIE=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DAView.obj" : $(SOURCE) $(DEP_CPP_DAVIE) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_DAVIE=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DAView.obj" : $(SOURCE) $(DEP_CPP_DAVIE) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_DAVIE=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\DA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DAView.obj" : $(SOURCE) $(DEP_CPP_DAVIE) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_DAVIE=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\protocolgridwnd.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAGridWnd.h"\
	".\DAPPS.h"\
	".\DAView.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\DA.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DAView.obj" : $(SOURCE) $(DEP_CPP_DAVIE) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_MAINF=\
	"..\protocol\fb12device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_MAINF=\
	"..\protocol\fb12device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_MAINF=\
	"..\protocol\fb12device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_MAINF=\
	"..\protocol\fb12device.h"\
	"..\protocol\gpps.h"\
	"..\protocol\kinetics.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DADoc.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\Sample.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_SAMPL=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_SAMPL=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_SAMPL=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_SAMPL=\
	"..\protocol\fb12device.h"\
	"..\protocol\general.h"\
	"..\protocol\gpps.h"\
	"..\protocol\pps.h"\
	"..\protocol\protocol.h"\
	"..\protocol\protocoldoc.h"\
	"..\protocol\protocolframe.h"\
	"..\protocol\replicate.h"\
	".\DA.h"\
	".\DAPPS.h"\
	".\MainFrm.h"\
	".\Sample.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\DA.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DA - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\DA.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Debug Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\DA.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DA - Win32 Release Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\DA.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

