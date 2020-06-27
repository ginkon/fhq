# Microsoft Developer Studio Generated NMAKE File, Based on FireWall.dsp
!IF $(CFG)" == "
CFG=FireWall - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FireWall - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FireWall - Win32 Release" && "$(CFG)" != "FireWall - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FireWall.mak" CFG="FireWall - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FireWall - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FireWall - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FireWall - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\FireWall.exe"


CLEAN :
	-@erase "$(INTDIR)\FireWall.obj"
	-@erase "$(INTDIR)\FireWall.pch"
	-@erase "$(INTDIR)\FireWall.res"
	-@erase "$(INTDIR)\FireWallDoc.obj"
	-@erase "$(INTDIR)\FireWallView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RuleDlg.obj"
	-@erase "$(INTDIR)\SockUtil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TDriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FireWall.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FireWall.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\FireWall.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FireWall.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FireWall.pdb" /machine:I386 /out:"$(OUTDIR)\FireWall.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FireWall.obj" \
	"$(INTDIR)\FireWallDoc.obj" \
	"$(INTDIR)\FireWallView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RuleDlg.obj" \
	"$(INTDIR)\SockUtil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TDriver.obj" \
	"$(INTDIR)\FireWall.res"

"$(OUTDIR)\FireWall.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FireWall - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\FireWall.exe"


CLEAN :
	-@erase "$(INTDIR)\FireWall.obj"
	-@erase "$(INTDIR)\FireWall.pch"
	-@erase "$(INTDIR)\FireWall.res"
	-@erase "$(INTDIR)\FireWallDoc.obj"
	-@erase "$(INTDIR)\FireWallView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RuleDlg.obj"
	-@erase "$(INTDIR)\SockUtil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TDriver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FireWall.exe"
	-@erase "$(OUTDIR)\FireWall.ilk"
	-@erase "$(OUTDIR)\FireWall.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FireWall.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\FireWall.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FireWall.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FireWall.pdb" /debug /machine:I386 /out:"$(OUTDIR)\FireWall.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FireWall.obj" \
	"$(INTDIR)\FireWallDoc.obj" \
	"$(INTDIR)\FireWallView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RuleDlg.obj" \
	"$(INTDIR)\SockUtil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TDriver.obj" \
	"$(INTDIR)\FireWall.res"

"$(OUTDIR)\FireWall.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FireWall.dep")
!INCLUDE "FireWall.dep"
!ELSE 
!MESSAGE Warning: cannot find "FireWall.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FireWall - Win32 Release" || "$(CFG)" == "FireWall - Win32 Debug"
SOURCE=.\FireWall.cpp

"$(INTDIR)\FireWall.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\FireWall.rc

"$(INTDIR)\FireWall.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FireWallDoc.cpp

"$(INTDIR)\FireWallDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\FireWallView.cpp

"$(INTDIR)\FireWallView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\RuleDlg.cpp

"$(INTDIR)\RuleDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\SockUtil.cpp

"$(INTDIR)\SockUtil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FireWall - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FireWall.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FireWall.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FireWall - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FireWall.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FireWall.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TDriver.cpp

"$(INTDIR)\TDriver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FireWall.pch"



!ENDIF 

