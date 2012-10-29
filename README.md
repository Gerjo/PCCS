PCCS
====

See the wiki for the full game design document.

Automatic builds
====
Are probably found here: http://cis.gerardmeier.com:8080/ login with your Abydoss unix account.  
  
Windows build server can be found using TeamViewer at: 947 969 915  
Login using the windows account Teal'C

Or internally you can use an RDP to 145.92.17.86

Compile & toolchain instructions
====
Linux: Just type "make" in the project root folder.  
  
Windows: In GIT Extensions go to the tab scripts. Add an AfterPull action with the batch file located in vs2012 named "Create Project.bat".
This will create a project based on the files that have been pulled, so no need to do manual work in the filters.


![logo](https://github.com/Gerjo/PCCS/blob/master/game/artwork/exports/one_page_game_design.png?raw=true)