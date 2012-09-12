@ECHO OFF
cd vs2012\FolderToProject
FolderToProject.exe "..\..\phantom\src" "..\CpPhantom\CpPhantom.vcxproj"
FolderToProject.exe "..\..\src" "..\GuerrillaTactics\GuerrillaTactics.vcxproj"