@ECHO OFF
cd game
cd vs2012
cd FolderToProject
FolderToProject.exe "..\..\..\phantom\src" "..\CpPhantom\CpPhantom.vcxproj"
FolderToProject.exe "..\..\src" "..\GuerrillaTactics\GuerrillaTactics.vcxproj"