@ECHO OFF
cd game
cd vs2012
cd FolderToProject
FolderToProject.exe "..\..\..\phantom\src" "..\CpPhantom\CpPhantom.vcxproj"
FolderToProject.exe "..\..\src" "..\GuerrillaTactics\GuerrillaTactics.vcxproj"
FolderToProject.exe "..\..\..\dedicatedserver\src" "..\Dedicated Server\Dedicated Server.vcxproj"
FolderToProject.exe "..\..\..\sharedlib\src" "..\Shared\Shared.vcxproj"