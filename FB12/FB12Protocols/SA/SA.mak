# Microsoft Developer Studio Generated NMAKE File, Based on SA.DSP
!IF "$(CFG)" == ""
CFG=SA - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to SA - Win32 Debug Simulate.
!ENDIF 

!IF "$(CFG)" != "SA - Win32 Release" && "$(CFG)" != "SA - Win32 Debug" &&\
 "$(CFG)" != "SA - Win32 Debug Simulate" && "$(CFG)" !=\
 "SA - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SA.MAK" CFG="SA - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SA - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "SA - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SA - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SA.exe"

!ELSE 

ALL : "$(OUTDIR)\SA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\SA.obj"
	-@erase "$(INTDIR)\SA.pch"
	-@erase "$(INTDIR)\SA.res"
	-@erase "$(INTDIR)\SAAdvancedDlg.obj"
	-@erase "$(INTDIR)\SADoc.obj"
	-@erase "$(INTDIR)\SAEditDlg.obj"
	-@erase "$(INTDIR)\SAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SAPPS.obj"
	-@erase "$(INTDIR)\SAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\SA.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolR.lib Winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\SA.pdb" /machine:I386 /out:"$(OUTDIR)\SA.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\SA.obj" \
	"$(INTDIR)\SA.res" \
	"$(INTDIR)\SAAdvancedDlg.obj" \
	"$(INTDIR)\SADoc.obj" \
	"$(INTDIR)\SAEditDlg.obj" \
	"$(INTDIR)\SAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SAPPS.obj" \
	"$(INTDIR)\SAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SA.exe"

!ELSE 

ALL : "$(OUTDIR)\SA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\SA.obj"
	-@erase "$(INTDIR)\SA.pch"
	-@erase "$(INTDIR)\SA.res"
	-@erase "$(INTDIR)\SAAdvancedDlg.obj"
	-@erase "$(INTDIR)\SADoc.obj"
	-@erase "$(INTDIR)\SAEditDlg.obj"
	-@erase "$(INTDIR)\SAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SAPPS.obj"
	-@erase "$(INTDIR)\SAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SA.exe"
	-@erase "$(OUTDIR)\SA.ilk"
	-@erase "$(OUTDIR)\SA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I\
 "..\Excel\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL"\
 /Fp"$(INTDIR)\SA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolD.lib Winmm.lib Excel.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\SA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SA.exe" /pdbtype:sept /libpath:"..\Protocol\lib"\
 /libpath:"..\Excel\Debug" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\SA.obj" \
	"$(INTDIR)\SA.res" \
	"$(INTDIR)\SAAdvancedDlg.obj" \
	"$(INTDIR)\SADoc.obj" \
	"$(INTDIR)\SAEditDlg.obj" \
	"$(INTDIR)\SAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SAPPS.obj" \
	"$(INTDIR)\SAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=.\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SA.exe"

!ELSE 

ALL : "$(OUTDIR)\SA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\SA.obj"
	-@erase "$(INTDIR)\SA.pch"
	-@erase "$(INTDIR)\SA.res"
	-@erase "$(INTDIR)\SAAdvancedDlg.obj"
	-@erase "$(INTDIR)\SADoc.obj"
	-@erase "$(INTDIR)\SAEditDlg.obj"
	-@erase "$(INTDIR)\SAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SAPPS.obj"
	-@erase "$(INTDIR)\SAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SA.exe"
	-@erase "$(OUTDIR)\SA.ilk"
	-@erase "$(OUTDIR)\SA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolDS.lib Winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\SA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SA.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\SA.obj" \
	"$(INTDIR)\SA.res" \
	"$(INTDIR)\SAAdvancedDlg.obj" \
	"$(INTDIR)\SADoc.obj" \
	"$(INTDIR)\SAEditDlg.obj" \
	"$(INTDIR)\SAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SAPPS.obj" \
	"$(INTDIR)\SAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=.\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SA.exe"

!ELSE 

ALL : "$(OUTDIR)\SA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\SA.obj"
	-@erase "$(INTDIR)\SA.pch"
	-@erase "$(INTDIR)\SA.res"
	-@erase "$(INTDIR)\SAAdvancedDlg.obj"
	-@erase "$(INTDIR)\SADoc.obj"
	-@erase "$(INTDIR)\SAEditDlg.obj"
	-@erase "$(INTDIR)\SAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\SAPPS.obj"
	-@erase "$(INTDIR)\SAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol\include" /I "..\Excel\Release"\
 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D\
 "FB12_SIMULATE" /Fp"$(INTDIR)\SA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolRS.lib Winmm.lib Excel.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\SA.pdb" /machine:I386 /out:"$(OUTDIR)\SA.exe"\
 /libpath:"..\Protocol\lib" /libpath:"..\Excel\Release" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\SA.obj" \
	"$(INTDIR)\SA.res" \
	"$(INTDIR)\SAAdvancedDlg.obj" \
	"$(INTDIR)\SADoc.obj" \
	"$(INTDIR)\SAEditDlg.obj" \
	"$(INTDIR)\SAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\SAPPS.obj" \
	"$(INTDIR)\SAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SA - Win32 Release" || "$(CFG)" == "SA - Win32 Debug" ||\
 "$(CFG)" == "SA - Win32 Debug Simulate" || "$(CFG)" ==\
 "SA - Win32 Release Simulate"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_MAINF=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MAINF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MAINF=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_MAINF=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MAINF=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\RunBar.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_RUNBA=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RUNBA=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RUNBA=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_RUNBA=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RUNBA=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SA.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SA_CP=\
	"..\Protocol\ChildFrm.h"\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\ProtCmdLineInfo.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SA_CP=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SA.obj" : $(SOURCE) $(DEP_CPP_SA_CP) "$(INTDIR)" "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SA_CP=\
	".\ChildFrm.h"\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SA.obj" : $(SOURCE) $(DEP_CPP_SA_CP) "$(INTDIR)" "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	
NODEP_CPP_SA_CP=\
	"..\protocol\include\childfrm.h"\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protcmdlineinfo.h"\
	"..\protocol\include\protocol.h"\
	"..\Protocol\include\ProtocolDlg.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SA.obj" : $(SOURCE) $(DEP_CPP_SA_CP) "$(INTDIR)" "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SA_CP=\
	".\ChildFrm.h"\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\ProtCmdLineInfo.h"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SA.obj" : $(SOURCE) $(DEP_CPP_SA_CP) "$(INTDIR)" "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SA.rc
DEP_RSC_SA_RC=\
	".\res\bmp00001.bmp"\
	".\res\idr_saty.ico"\
	".\res\SA.ico"\
	".\res\SA.rc2"\
	".\res\SADoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	

"$(INTDIR)\SA.res" : $(SOURCE) $(DEP_RSC_SA_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SAAdvancedDlg.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAADV=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAADV=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_SAADV) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAADV=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_SAADV) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAADV=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\Protocol\include\ProtocolDlg.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_SAADV) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAADV=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_SAADV) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SADoc.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SADOC=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SADOC=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SADoc.obj" : $(SOURCE) $(DEP_CPP_SADOC) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SADOC=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SADoc.obj" : $(SOURCE) $(DEP_CPP_SADOC) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SADOC=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SADoc.obj" : $(SOURCE) $(DEP_CPP_SADOC) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SADOC=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SADoc.obj" : $(SOURCE) $(DEP_CPP_SADOC) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SAEditDlg.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAEDI=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDlg.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAEDI=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAEditDlg.obj" : $(SOURCE) $(DEP_CPP_SAEDI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAEDI=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAEditDlg.obj" : $(SOURCE) $(DEP_CPP_SAEDI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAEDI=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\Protocol\include\ProtocolDlg.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SAEditDlg.obj" : $(SOURCE) $(DEP_CPP_SAEDI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SAAdvancedDlg.h"\
	".\SADoc.h"\
	".\SAEditDlg.h"\
	".\SAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAEDI=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAEditDlg.obj" : $(SOURCE) $(DEP_CPP_SAEDI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SAGridWnd.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAGRI=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAGRI=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAGRI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAGRI=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAGRI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAGRI=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SAGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAGRI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAGRI=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAGRI) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SampGridWnd.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAMPG=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPG=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SampGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAMPG) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPG=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SampGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAMPG) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAMPG=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SampGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAMPG) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPG=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SampGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAMPG) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\Sample.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAMPL=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPL=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPL=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAMPL=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPL=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SAPPS.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAPPS=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAPPS=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAPPS.obj" : $(SOURCE) $(DEP_CPP_SAPPS) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAPPS=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAPPS.obj" : $(SOURCE) $(DEP_CPP_SAPPS) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	
NODEP_CPP_SAPPS=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SAPPS.obj" : $(SOURCE) $(DEP_CPP_SAPPS) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAPPS=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAPPS.obj" : $(SOURCE) $(DEP_CPP_SAPPS) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\SAView.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_SAVIE=\
	"..\Protocol\FB12Device.h"\
	"..\Protocol\General.h"\
	"..\Protocol\GPPS.h"\
	"..\Protocol\Kinetics.h"\
	"..\Protocol\PPS.h"\
	"..\Protocol\Protocol.h"\
	"..\Protocol\ProtocolDoc.h"\
	"..\Protocol\ProtocolFrame.h"\
	"..\Protocol\ProtocolGridWnd.h"\
	"..\Protocol\Replicate.h"\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAVIE=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAView.obj" : $(SOURCE) $(DEP_CPP_SAVIE) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_SAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAVIE=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAView.obj" : $(SOURCE) $(DEP_CPP_SAVIE) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_SAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	
NODEP_CPP_SAVIE=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\SAView.obj" : $(SOURCE) $(DEP_CPP_SAVIE) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_SAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\SA.h"\
	".\SADoc.h"\
	".\SAGridWnd.h"\
	".\Sample.h"\
	".\SAPPS.h"\
	".\SAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAVIE=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\General.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\ProtocolGridWnd.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SAView.obj" : $(SOURCE) $(DEP_CPP_SAVIE) "$(INTDIR)"\
 "$(INTDIR)\SA.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SA - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\SA.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SA - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I\
 "..\Excel\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL"\
 /Fp"$(INTDIR)\SA.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SA - Win32 Debug Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\SA.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SA - Win32 Release Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol\include" /I\
 "..\Excel\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D\
 "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\SA.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

