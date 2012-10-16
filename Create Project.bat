@ECHO OFF
cd foldertoproject
FolderToProject.exe "..\dedicatedserver\src" "..\dedicatedserver\dedicatedserver.vcxproj"
FolderToProject.exe "..\game\src" "..\game\guerrillatactics.vcxproj"
FolderToProject.exe "..\libyaxl\libyaxl" ..\libyaxl\yaxl.vcxproj"
FolderToProject.exe "..\phantom\src" "..\phantom\phantom.vcxproj"
FolderToProject.exe "..\sharedlib\src" "..\sharedlib\sharedlib.vcxproj"
cd ..