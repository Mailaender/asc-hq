# Microsoft Developer Studio Project File - Name="asc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=asc - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "asc.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "asc.mak" CFG="asc - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "asc - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "asc - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "asc - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /vmg /vmm /GX /O2 /I "." /I "D:\LANDI\PROJECTS\sourceforge\SDL-1.1.3\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "HEXAGON" /D "_NOASM_" /D "sgmain" /D "FREEMAPZOOM" /D "NEWKEYB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib /nologo /subsystem:console /machine:I386 /libpath:"D:\LANDI\PROJECTS\sourceforge\SDL-1.1.3\VisualC\SDL\release"

!ELSEIF  "$(CFG)" == "asc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /Gi /vmg /vmm /vd0 /GX /ZI /Od /I "." /I "../source/libs/jpeg" /I "D:\LANDI\PROJECTS\sourceforge\SDL-1.1.3\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "HEXAGON" /D "_NOASM_" /D "sgmain" /D "FREEMAPZOOM" /D "NEWKEYB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"D:\LANDI\PROJECTS\sourceforge\SDL-1.1.3\VisualC\SDL\debug"

!ENDIF 

# Begin Target

# Name "asc - Win32 Release"
# Name "asc - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\artint.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\asc_IMG_jpg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\attack.cpp
# End Source File
# Begin Source File

SOURCE=..\source\basegfx.cpp
# End Source File
# Begin Source File

SOURCE=..\source\basestrm.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\blocksort.c
# End Source File
# Begin Source File

SOURCE=..\source\building.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\bzip2.c
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\bzlib.c
# End Source File
# Begin Source File

SOURCE=..\source\CLoadable.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\compress.c
# End Source File
# Begin Source File

SOURCE=..\source\libs\triangul\construc.c
# End Source File
# Begin Source File

SOURCE=..\source\controls.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\crctable.c
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\decompress.c
# End Source File
# Begin Source File

SOURCE=..\source\dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dlg_box.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\events.cpp
# End Source File
# Begin Source File

SOURCE=..\source\gamedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\gameoptions.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\graphics.cpp
# End Source File
# Begin Source File

SOURCE=..\source\gui.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\huffman.c
# End Source File
# Begin Source File

SOURCE=..\source\loadbi3.cpp
# End Source File
# Begin Source File

SOURCE=..\source\loaders.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\loadimage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\loadjpg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\loadpcxc.cpp
# End Source File
# Begin Source File

SOURCE=..\source\misc.cpp
# End Source File
# Begin Source File

SOURCE=..\source\missions.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\triangul\monotone.c
# End Source File
# Begin Source File

SOURCE=..\source\mousecontrol.cpp
# End Source File
# Begin Source File

SOURCE=..\source\Named.cpp
# End Source File
# Begin Source File

SOURCE=.\ndir.c
# End Source File
# Begin Source File

SOURCE=..\source\network.cpp
# End Source File
# Begin Source File

SOURCE=..\source\newfont.cpp
# End Source File
# Begin Source File

SOURCE=..\source\palette.cpp
# End Source File
# Begin Source File

SOURCE=..\source\pd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\Property.cpp
# End Source File
# Begin Source File

SOURCE=..\source\PropertyGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\bzlib\randtable.c
# End Source File
# Begin Source File

SOURCE=..\source\sdl\SDLStretch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sgstream.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\sound.cpp
# End Source File
# Begin Source File

SOURCE=..\source\soundList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\spfst.cpp
# End Source File
# Begin Source File

SOURCE=..\source\stack.cpp
# End Source File
# Begin Source File

SOURCE=..\source\strtmesg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sdl\timer.cpp
# End Source File
# Begin Source File

SOURCE=..\source\libs\triangul\tri.c
# End Source File
# Begin Source File

SOURCE=..\source\libs\triangul\trimisc.c
# End Source File
# Begin Source File

SOURCE=..\source\typen.cpp
# End Source File
# Begin Source File

SOURCE=..\source\unitctrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\weather.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\source\attack.h
# End Source File
# Begin Source File

SOURCE=..\source\basegfx.h
# End Source File
# Begin Source File

SOURCE=..\source\basestrm.h
# End Source File
# Begin Source File

SOURCE=..\source\building.h
# End Source File
# Begin Source File

SOURCE=..\source\CLoadable.h
# End Source File
# Begin Source File

SOURCE=..\source\gui.h
# End Source File
# Begin Source File

SOURCE=..\source\sgstream.h
# End Source File
# Begin Source File

SOURCE=..\source\spfst.h
# End Source File
# Begin Source File

SOURCE=..\source\typen.h
# End Source File
# Begin Source File

SOURCE=..\source\weather.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
