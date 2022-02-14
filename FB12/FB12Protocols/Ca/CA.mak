# Microsoft Developer Studio Generated NMAKE File, Based on CA.DSP
!IF "$(CFG)" == ""
CFG=CA - Win32 Debug Simulate
!MESSAGE No configuration specified. Defaulting to CA - Win32 Debug Simulate.
!ENDIF 

!IF "$(CFG)" != "CA - Win32 Release" && "$(CFG)" != "CA - Win32 Debug" &&\
 "$(CFG)" != "CA - Win32 Debug Simulate" && "$(CFG)" !=\
 "CA - Win32 Release Simulate"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CA.MAK" CFG="CA - Win32 Debug Simulate"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CA - Win32 Debug Simulate" (based on "Win32 (x86) Application")
!MESSAGE "CA - Win32 Release Simulate" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CA - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CA.exe"

!ELSE 

ALL : "$(OUTDIR)\CA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\CA.obj"
	-@erase "$(INTDIR)\CA.pch"
	-@erase "$(INTDIR)\CA.res"
	-@erase "$(INTDIR)\CAAdvancedDlg.obj"
	-@erase "$(INTDIR)\CADoc.obj"
	-@erase "$(INTDIR)\CAEditDlg.obj"
	-@erase "$(INTDIR)\CAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\CAPPS.obj"
	-@erase "$(INTDIR)\CAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\CA.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolR.lib Winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\CA.pdb" /machine:I386 /out:"$(OUTDIR)\CA.exe"\
 /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\CA.obj" \
	"$(INTDIR)\CA.res" \
	"$(INTDIR)\CAAdvancedDlg.obj" \
	"$(INTDIR)\CADoc.obj" \
	"$(INTDIR)\CAEditDlg.obj" \
	"$(INTDIR)\CAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\CAPPS.obj" \
	"$(INTDIR)\CAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CA.exe"

!ELSE 

ALL : "$(OUTDIR)\CA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\CA.obj"
	-@erase "$(INTDIR)\CA.pch"
	-@erase "$(INTDIR)\CA.res"
	-@erase "$(INTDIR)\CAAdvancedDlg.obj"
	-@erase "$(INTDIR)\CADoc.obj"
	-@erase "$(INTDIR)\CAEditDlg.obj"
	-@erase "$(INTDIR)\CAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\CAPPS.obj"
	-@erase "$(INTDIR)\CAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CA.exe"
	-@erase "$(OUTDIR)\CA.ilk"
	-@erase "$(OUTDIR)\CA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I\
 "..\Excel\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL"\
 /Fp"$(INTDIR)\CA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolD.lib Winmm.lib Excel.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\CA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\CA.exe" /pdbtype:sept /libpath:"..\Protocol\lib"\
 /libpath:"..\Excel\Debug" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\CA.obj" \
	"$(INTDIR)\CA.res" \
	"$(INTDIR)\CAAdvancedDlg.obj" \
	"$(INTDIR)\CADoc.obj" \
	"$(INTDIR)\CAEditDlg.obj" \
	"$(INTDIR)\CAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\CAPPS.obj" \
	"$(INTDIR)\CAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

OUTDIR=.\DebugS
INTDIR=.\DebugS
# Begin Custom Macros
OutDir=.\DebugS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CA.exe"

!ELSE 

ALL : "$(OUTDIR)\CA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\CA.obj"
	-@erase "$(INTDIR)\CA.pch"
	-@erase "$(INTDIR)\CA.res"
	-@erase "$(INTDIR)\CAAdvancedDlg.obj"
	-@erase "$(INTDIR)\CADoc.obj"
	-@erase "$(INTDIR)\CAEditDlg.obj"
	-@erase "$(INTDIR)\CAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\CAPPS.obj"
	-@erase "$(INTDIR)\CAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CA.exe"
	-@erase "$(OUTDIR)\CA.ilk"
	-@erase "$(OUTDIR)\CA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\CA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CA.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolDS.lib Winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\CA.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\CA.exe" /pdbtype:sept /libpath:"..\Protocol\lib" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\CA.obj" \
	"$(INTDIR)\CA.res" \
	"$(INTDIR)\CAAdvancedDlg.obj" \
	"$(INTDIR)\CADoc.obj" \
	"$(INTDIR)\CAEditDlg.obj" \
	"$(INTDIR)\CAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\CAPPS.obj" \
	"$(INTDIR)\CAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

OUTDIR=.\ReleaseS
INTDIR=.\ReleaseS
# Begin Custom Macros
OutDir=.\ReleaseS
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CA.exe"

!ELSE 

ALL : "$(OUTDIR)\CA.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RunBar.obj"
	-@erase "$(INTDIR)\CA.obj"
	-@erase "$(INTDIR)\CA.pch"
	-@erase "$(INTDIR)\CA.res"
	-@erase "$(INTDIR)\CAAdvancedDlg.obj"
	-@erase "$(INTDIR)\CADoc.obj"
	-@erase "$(INTDIR)\CAEditDlg.obj"
	-@erase "$(INTDIR)\CAGridWnd.obj"
	-@erase "$(INTDIR)\SampGridWnd.obj"
	-@erase "$(INTDIR)\Sample.obj"
	-@erase "$(INTDIR)\CAPPS.obj"
	-@erase "$(INTDIR)\CAView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CA.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Protocol\include" /I "..\Excel\Release"\
 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D\
 "FB12_SIMULATE" /Fp"$(INTDIR)\CA.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CA.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ProtocolRS.lib Winmm.lib Excel.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\CA.pdb" /machine:I386 /out:"$(OUTDIR)\CA.exe"\
 /libpath:"..\Protocol\lib" /libpath:"..\Excel\Release" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RunBar.obj" \
	"$(INTDIR)\CA.obj" \
	"$(INTDIR)\CA.res" \
	"$(INTDIR)\CAAdvancedDlg.obj" \
	"$(INTDIR)\CADoc.obj" \
	"$(INTDIR)\CAEditDlg.obj" \
	"$(INTDIR)\CAGridWnd.obj" \
	"$(INTDIR)\SampGridWnd.obj" \
	"$(INTDIR)\Sample.obj" \
	"$(INTDIR)\CAPPS.obj" \
	"$(INTDIR)\CAView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CA.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "CA - Win32 Release" || "$(CFG)" == "CA - Win32 Debug" ||\
 "$(CFG)" == "CA - Win32 Debug Simulate" || "$(CFG)" ==\
 "CA - Win32 Release Simulate"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

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
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MAINF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\RunBar.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

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
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RUNBA=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\RunBar.obj" : $(SOURCE) $(DEP_CPP_RUNBA) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_RUNBA=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CA.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CA_CP=\
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
	".\CA.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CA_CP=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CA.obj" : $(SOURCE) $(DEP_CPP_CA_CP) "$(INTDIR)" "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CA_CP=\
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
	

"$(INTDIR)\CA.obj" : $(SOURCE) $(DEP_CPP_CA_CP) "$(INTDIR)" "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	
NODEP_CPP_CA_CP=\
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
	

"$(INTDIR)\CA.obj" : $(SOURCE) $(DEP_CPP_CA_CP) "$(INTDIR)" "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CA_CP=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CA_CP=\
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
	

"$(INTDIR)\CA.obj" : $(SOURCE) $(DEP_CPP_CA_CP) "$(INTDIR)" "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CA.rc
DEP_RSC_CA_RC=\
	".\res\bmp00001.bmp"\
	".\res\idr_saty.ico"\
	".\res\CA.ico"\
	".\res\CA.rc2"\
	".\res\CADoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	

"$(INTDIR)\CA.res" : $(SOURCE) $(DEP_RSC_CA_RC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CAAdvancedDlg.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CAADV=\
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
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAADV=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_CAADV) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAADV=\
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
	

"$(INTDIR)\CAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_CAADV) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
NODEP_CPP_CAADV=\
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
	

"$(INTDIR)\CAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_CAADV) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CAADV=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAADV=\
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
	

"$(INTDIR)\CAAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_CAADV) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CADoc.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CADOC=\
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
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CADOC=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CADoc.obj" : $(SOURCE) $(DEP_CPP_CADOC) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CADOC=\
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
	

"$(INTDIR)\CADoc.obj" : $(SOURCE) $(DEP_CPP_CADOC) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
NODEP_CPP_CADOC=\
	"..\protocol\include\fb12device.h"\
	"..\protocol\include\general.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\CADoc.obj" : $(SOURCE) $(DEP_CPP_CADOC) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CADOC=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CADOC=\
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
	

"$(INTDIR)\CADoc.obj" : $(SOURCE) $(DEP_CPP_CADOC) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CAEditDlg.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CAEDI=\
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
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAEDI=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAEditDlg.obj" : $(SOURCE) $(DEP_CPP_CAEDI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAEDI=\
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
	

"$(INTDIR)\CAEditDlg.obj" : $(SOURCE) $(DEP_CPP_CAEDI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
NODEP_CPP_CAEDI=\
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
	

"$(INTDIR)\CAEditDlg.obj" : $(SOURCE) $(DEP_CPP_CAEDI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CAEDI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CAAdvancedDlg.h"\
	".\CADoc.h"\
	".\CAEditDlg.h"\
	".\CAGridWnd.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAEDI=\
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
	

"$(INTDIR)\CAEditDlg.obj" : $(SOURCE) $(DEP_CPP_CAEDI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CAGridWnd.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CAGRI=\
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
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAGRI=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAGridWnd.obj" : $(SOURCE) $(DEP_CPP_CAGRI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAGRI=\
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
	

"$(INTDIR)\CAGridWnd.obj" : $(SOURCE) $(DEP_CPP_CAGRI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
NODEP_CPP_CAGRI=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\protocolgridwnd.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\CAGridWnd.obj" : $(SOURCE) $(DEP_CPP_CAGRI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CAGRI=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAGRI=\
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
	

"$(INTDIR)\CAGridWnd.obj" : $(SOURCE) $(DEP_CPP_CAGRI) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\SampGridWnd.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

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
	".\CA.h"\
	".\CADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPG=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\SampGridWnd.obj" : $(SOURCE) $(DEP_CPP_SAMPG) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_SAMPG=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\SampGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\Sample.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

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
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SAMPL=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\Sample.obj" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
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
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_SAMPL=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
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
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CAPPS.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CAPPS=\
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
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAPPS=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAPPS.obj" : $(SOURCE) $(DEP_CPP_CAPPS) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAPPS=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAPPS.obj" : $(SOURCE) $(DEP_CPP_CAPPS) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	
NODEP_CPP_CAPPS=\
	"..\protocol\include\fb12device.h"\
	"..\Protocol\include\GPPS.h"\
	"..\protocol\include\kinetics.h"\
	"..\Protocol\include\PPS.h"\
	"..\protocol\include\protocol.h"\
	"..\protocol\include\protocoldoc.h"\
	"..\protocol\include\protocolframe.h"\
	"..\protocol\include\replicate.h"\
	

"$(INTDIR)\CAPPS.obj" : $(SOURCE) $(DEP_CPP_CAPPS) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CAPPS=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAPPS=\
	".\excel8.tlh"\
	".\FB12Device.h"\
	".\Kinetics.h"\
	".\mso97.tlh"\
	".\Protocol.h"\
	".\ProtocolDoc.h"\
	".\ProtocolFrame.h"\
	".\Replicate.h"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAPPS.obj" : $(SOURCE) $(DEP_CPP_CAPPS) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\CAView.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_CAVIE=\
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
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAVIE=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	

"$(INTDIR)\CAView.obj" : $(SOURCE) $(DEP_CPP_CAVIE) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_CAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAVIE=\
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
	

"$(INTDIR)\CAView.obj" : $(SOURCE) $(DEP_CPP_CAVIE) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_CAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	
NODEP_CPP_CAVIE=\
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
	

"$(INTDIR)\CAView.obj" : $(SOURCE) $(DEP_CPP_CAVIE) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_CAVIE=\
	".\MainFrm.h"\
	".\RunBar.h"\
	".\CA.h"\
	".\CADoc.h"\
	".\CAGridWnd.h"\
	".\Sample.h"\
	".\CAPPS.h"\
	".\CAView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CAVIE=\
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
	

"$(INTDIR)\CAView.obj" : $(SOURCE) $(DEP_CPP_CAVIE) "$(INTDIR)"\
 "$(INTDIR)\CA.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CA - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /Fp"$(INTDIR)\CA.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CA - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol\include" /I\
 "..\Excel\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL"\
 /Fp"$(INTDIR)\CA.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CA - Win32 Debug Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\og50\include\gxbrowse.inl"\
	"d:\og50\include\gxcrtf.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Protocol" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_GXDLL" /D "FB12_SIMULATE"\
 /Fp"$(INTDIR)\CA.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CA - Win32 Release Simulate"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\excel8.tlh"\
	".\mso97.tlh"\
	".\vbeext1.tlh"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Protocol\include" /I\
 "..\Excel\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D\
 "_GXDLL" /D "FB12_SIMULATE" /Fp"$(INTDIR)\CA.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CA.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

