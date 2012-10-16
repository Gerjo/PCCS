@ECHO OFF
cd foldertoproject
FolderToProject.exe "..\phantom\src" "..\phantom\phantom.vcxproj"
FolderToProject.exe "..\game\src" "..\game\guerrillatactics.vcxproj"
FolderToProject.exe "..\dedicatedserver\src" "..\dedicatedserver\dedicatedserver.vcxproj"
FolderToProject.exe "..\sharedlib\src" "..\sharedlib\sharedlib.vcxproj"
cd ..