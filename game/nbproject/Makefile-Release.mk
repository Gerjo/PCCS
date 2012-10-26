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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/gamestates/ClientWorld.o \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/components/PreloaderText.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/gamestates/Loader.o \
	${OBJECTDIR}/src/components/PreloaderLogo.o \
	${OBJECTDIR}/src/components/Selector.o \
	${OBJECTDIR}/src/FixedLayer.o \
	${OBJECTDIR}/src/gameobjects/HeavyTree.o \
	${OBJECTDIR}/src/networking/Reader.o \
	${OBJECTDIR}/src/components/Console.o \
	${OBJECTDIR}/src/networking/Ping.o \
	${OBJECTDIR}/src/gameobjects/HeavyFactory.o \
	${OBJECTDIR}/src/components/RtsCamera.o \
	${OBJECTDIR}/src/networking/Network.o \
	${OBJECTDIR}/src/goodies/weapons/Weapon.o \
	${OBJECTDIR}/src/components/Cursor.o \
	${OBJECTDIR}/src/gameobjects/HeavySoldier.o \
	${OBJECTDIR}/src/goodies/bullets/Bullet.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15 -lyaxl -lsharedlib
CXXFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15 -lyaxl -lsharedlib

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist -Wl,-rpath,.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/guarrilla_tactics.run

../dist/guarrilla_tactics.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -Werror -lphantom -lglut -lyaxl -lsharedlib -o ../dist/guarrilla_tactics.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/gamestates/ClientWorld.o: src/gamestates/ClientWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gamestates
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gamestates/ClientWorld.o src/gamestates/ClientWorld.cpp

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/components/PreloaderText.o: src/components/PreloaderText.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/PreloaderText.o src/components/PreloaderText.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/gamestates/Loader.o: src/gamestates/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gamestates
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gamestates/Loader.o src/gamestates/Loader.cpp

${OBJECTDIR}/src/components/PreloaderLogo.o: src/components/PreloaderLogo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/PreloaderLogo.o src/components/PreloaderLogo.cpp

${OBJECTDIR}/src/components/Selector.o: src/components/Selector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Selector.o src/components/Selector.cpp

${OBJECTDIR}/src/FixedLayer.o: src/FixedLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FixedLayer.o src/FixedLayer.cpp

${OBJECTDIR}/src/gameobjects/HeavyTree.o: src/gameobjects/HeavyTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyTree.o src/gameobjects/HeavyTree.cpp

${OBJECTDIR}/src/networking/Reader.o: src/networking/Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Reader.o src/networking/Reader.cpp

${OBJECTDIR}/src/components/Console.o: src/components/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Console.o src/components/Console.cpp

${OBJECTDIR}/src/networking/Ping.o: src/networking/Ping.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Ping.o src/networking/Ping.cpp

${OBJECTDIR}/src/gameobjects/HeavyFactory.o: src/gameobjects/HeavyFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavyFactory.o src/gameobjects/HeavyFactory.cpp

${OBJECTDIR}/src/components/RtsCamera.o: src/components/RtsCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/RtsCamera.o src/components/RtsCamera.cpp

${OBJECTDIR}/src/networking/Network.o: src/networking/Network.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/networking
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/networking/Network.o src/networking/Network.cpp

${OBJECTDIR}/src/goodies/weapons/Weapon.o: src/goodies/weapons/Weapon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goodies/weapons
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/goodies/weapons/Weapon.o src/goodies/weapons/Weapon.cpp

${OBJECTDIR}/src/components/Cursor.o: src/components/Cursor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Cursor.o src/components/Cursor.cpp

${OBJECTDIR}/src/gameobjects/HeavySoldier.o: src/gameobjects/HeavySoldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/HeavySoldier.o src/gameobjects/HeavySoldier.cpp

${OBJECTDIR}/src/goodies/bullets/Bullet.o: src/goodies/bullets/Bullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goodies/bullets
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/goodies/bullets/Bullet.o src/goodies/bullets/Bullet.cpp

# Subprojects
.build-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/guarrilla_tactics.run

# Subprojects
.clean-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
