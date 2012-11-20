#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/gameobjects/HeavyTank.o \
	${OBJECTDIR}/src/gamestates/ClientWorld.o \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/components/PreloaderText.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/gamestates/Loader.o \
	${OBJECTDIR}/src/guicomponents/menu/MainMenu.o \
	${OBJECTDIR}/src/gamestates/MenuState.o \
	${OBJECTDIR}/src/components/PreloaderLogo.o \
	${OBJECTDIR}/src/gameobjects/HeavyBullet.o \
	${OBJECTDIR}/src/components/Selector.o \
	${OBJECTDIR}/src/gameobjects/HeavyTree.o \
	${OBJECTDIR}/src/networking/Dedicated.o \
	${OBJECTDIR}/src/components/Clicktor.o \
	${OBJECTDIR}/src/Settings.o \
	${OBJECTDIR}/src/guicomponents/menu/SettingsMenu.o \
	${OBJECTDIR}/src/gameobjects/HeavyCrate.o \
	${OBJECTDIR}/src/networking/Ping.o \
	${OBJECTDIR}/src/guicomponents/HUD.o \
	${OBJECTDIR}/src/guicomponents/menu/MenuLabel.o \
	${OBJECTDIR}/src/gameobjects/HeavyFactory.o \
	${OBJECTDIR}/src/guicomponents/InputField.o \
	${OBJECTDIR}/src/guicomponents/menu/MenuButton.o \
	${OBJECTDIR}/src/networking/Master.o \
	${OBJECTDIR}/src/components/ScrollBehaviour.o \
	${OBJECTDIR}/src/guicomponents/menu/ServerBrowser.o \
	${OBJECTDIR}/src/guicomponents/menu/CreditsMenu.o \
	${OBJECTDIR}/src/components/Cursor.o \
	${OBJECTDIR}/src/gameobjects/HeavySoldier.o \
	${OBJECTDIR}/src/gameobjects/HeavyWeapon.o \
	${OBJECTDIR}/src/guicomponents/menu/MenuInputField.o \
	${OBJECTDIR}/src/networking/LocalRegistry.o


# C Compiler Flags
CFLAGS=-Werror

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist -Wl,-rpath,. -lphantom -lglut -lyaxl -lsharedlib -lpng15

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/guarrilla_tactics.run

../dist/guarrilla_tactics.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -Werror -o ../dist/guarrilla_tactics.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/gameobjects/HeavyTank.o: src/gameobjects/HeavyTank.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyTank.o src/gameobjects/HeavyTank.cpp

${OBJECTDIR}/src/gamestates/ClientWorld.o: src/gamestates/ClientWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gamestates
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gamestates/ClientWorld.o src/gamestates/ClientWorld.cpp

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/components/PreloaderText.o: src/components/PreloaderText.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/PreloaderText.o src/components/PreloaderText.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/gamestates/Loader.o: src/gamestates/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gamestates
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gamestates/Loader.o src/gamestates/Loader.cpp

${OBJECTDIR}/src/guicomponents/menu/MainMenu.o: src/guicomponents/menu/MainMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/MainMenu.o src/guicomponents/menu/MainMenu.cpp

${OBJECTDIR}/src/gamestates/MenuState.o: src/gamestates/MenuState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gamestates
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gamestates/MenuState.o src/gamestates/MenuState.cpp

${OBJECTDIR}/src/components/PreloaderLogo.o: src/components/PreloaderLogo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/PreloaderLogo.o src/components/PreloaderLogo.cpp

${OBJECTDIR}/src/gameobjects/HeavyBullet.o: src/gameobjects/HeavyBullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyBullet.o src/gameobjects/HeavyBullet.cpp

${OBJECTDIR}/src/components/Selector.o: src/components/Selector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Selector.o src/components/Selector.cpp

${OBJECTDIR}/src/gameobjects/HeavyTree.o: src/gameobjects/HeavyTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyTree.o src/gameobjects/HeavyTree.cpp

${OBJECTDIR}/src/networking/Dedicated.o: src/networking/Dedicated.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Dedicated.o src/networking/Dedicated.cpp

${OBJECTDIR}/src/components/Clicktor.o: src/components/Clicktor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Clicktor.o src/components/Clicktor.cpp

${OBJECTDIR}/src/Settings.o: src/Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Settings.o src/Settings.cpp

${OBJECTDIR}/src/guicomponents/menu/SettingsMenu.o: src/guicomponents/menu/SettingsMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/SettingsMenu.o src/guicomponents/menu/SettingsMenu.cpp

${OBJECTDIR}/src/gameobjects/HeavyCrate.o: src/gameobjects/HeavyCrate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyCrate.o src/gameobjects/HeavyCrate.cpp

${OBJECTDIR}/src/networking/Ping.o: src/networking/Ping.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Ping.o src/networking/Ping.cpp

${OBJECTDIR}/src/guicomponents/HUD.o: src/guicomponents/HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/HUD.o src/guicomponents/HUD.cpp

${OBJECTDIR}/src/guicomponents/menu/MenuLabel.o: src/guicomponents/menu/MenuLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/MenuLabel.o src/guicomponents/menu/MenuLabel.cpp

${OBJECTDIR}/src/gameobjects/HeavyFactory.o: src/gameobjects/HeavyFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyFactory.o src/gameobjects/HeavyFactory.cpp

${OBJECTDIR}/src/guicomponents/InputField.o: src/guicomponents/InputField.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/InputField.o src/guicomponents/InputField.cpp

${OBJECTDIR}/src/guicomponents/menu/MenuButton.o: src/guicomponents/menu/MenuButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/MenuButton.o src/guicomponents/menu/MenuButton.cpp

${OBJECTDIR}/src/networking/Master.o: src/networking/Master.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Master.o src/networking/Master.cpp

${OBJECTDIR}/src/components/ScrollBehaviour.o: src/components/ScrollBehaviour.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/ScrollBehaviour.o src/components/ScrollBehaviour.cpp

${OBJECTDIR}/src/guicomponents/menu/ServerBrowser.o: src/guicomponents/menu/ServerBrowser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/ServerBrowser.o src/guicomponents/menu/ServerBrowser.cpp

${OBJECTDIR}/src/guicomponents/menu/CreditsMenu.o: src/guicomponents/menu/CreditsMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/CreditsMenu.o src/guicomponents/menu/CreditsMenu.cpp

${OBJECTDIR}/src/components/Cursor.o: src/components/Cursor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Cursor.o src/components/Cursor.cpp

${OBJECTDIR}/src/gameobjects/HeavySoldier.o: src/gameobjects/HeavySoldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavySoldier.o src/gameobjects/HeavySoldier.cpp

${OBJECTDIR}/src/gameobjects/HeavyWeapon.o: src/gameobjects/HeavyWeapon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyWeapon.o src/gameobjects/HeavyWeapon.cpp

${OBJECTDIR}/src/guicomponents/menu/MenuInputField.o: src/guicomponents/menu/MenuInputField.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/guicomponents/menu
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/guicomponents/menu/MenuInputField.o src/guicomponents/menu/MenuInputField.cpp

${OBJECTDIR}/src/networking/LocalRegistry.o: src/networking/LocalRegistry.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/LocalRegistry.o src/networking/LocalRegistry.cpp

# Subprojects
.build-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/guarrilla_tactics.run

# Subprojects
.clean-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
