# Microsoft Developer Studio Project File - Name="guidoar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=guidoar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "guidoar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "guidoar.mak" CFG="guidoar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "guidoar - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "guidoar - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "guidoar - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUIDOAR_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../src/guido" /I "../../src/guido/abstract" /I "../../src/visitors" /I "../../src/lib" /I "../../src/parser" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUIDOAR_EXPORTS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /dll /machine:I386 /out:"../guidoar.dll" /implib:"guidoar.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "guidoar - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUIDOAR_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../../src/guido" /I "../../src/guido/abstract" /I "../../src/visitors" /I "../../src/lib" /I "../../src/parser" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUIDOAR_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /dll /debug /machine:I386 /out:"../guidoar.dll" /implib:"guidoar.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "guidoar - Win32 Release"
# Name "guidoar - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\lib\rational.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lib\streambeautifuller.cpp
# End Source File
# End Group
# Begin Group "operations"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\operations\durationOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\eheadOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\etailOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\headOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\interleaveOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\parOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\seqOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\tailOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\transposeOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\vheadOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operations\vtailOperation.cpp
# End Source File
# End Group
# Begin Group "parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\parser\guido.l

!IF  "$(CFG)" == "guidoar - Win32 Release"

!ELSEIF  "$(CFG)" == "guidoar - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\parser\guido.y

!IF  "$(CFG)" == "guidoar - Win32 Release"

!ELSEIF  "$(CFG)" == "guidoar - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\parser\guidoparser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\parser.cpp
# End Source File
# End Group
# Begin Group "visitors"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\visitors\clonevisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\counteventsvisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\durationvisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\event2timevisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\gmnvisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\midicontextvisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\visitors\unrolled_guido_browser.cpp
# End Source File
# End Group
# Begin Group "guido"

# PROP Default_Filter ""
# Begin Group "abstract"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\guido\abstract\ARChord.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\guido\abstract\ARFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\guido\abstract\ARNote.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\guido\abstract\AROthers.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\guido\abstract\ARTag.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\guido\guidoelement.cpp
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
