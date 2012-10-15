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
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/gameobjects/Soldier.o \
	${OBJECTDIR}/src/tiles/Tile.o \
	${OBJECTDIR}/src/pathfinding/BSPTree.o \
	${OBJECTDIR}/src/components/Selector.o \
	${OBJECTDIR}/src/FixedLayer.o \
	${OBJECTDIR}/src/pathfinding/Space.o \
	${OBJECTDIR}/src/ObjectFactory.o \
	${OBJECTDIR}/src/gameobjects/Enemy.o \
	${OBJECTDIR}/src/tiles/TiledObjectLayer.o \
	${OBJECTDIR}/src/gameobjects/GameObject.o \
	${OBJECTDIR}/src/pathfinding/Pathfinding.o \
	${OBJECTDIR}/src/components/RtsCamera.o \
	${OBJECTDIR}/src/components/Cursor.o \
	${OBJECTDIR}/src/gameobjects/Tree.o \
	${OBJECTDIR}/src/gameobjects/Crate.o


# C Compiler Flags
CFLAGS=-Werror

# CC Compiler Flags
CCFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15
CXXFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15

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
	${LINK.cc} -Werror -lphantom -lglut -o ../dist/guarrilla_tactics.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/gameobjects/Soldier.o: src/gameobjects/Soldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Soldier.o src/gameobjects/Soldier.cpp

${OBJECTDIR}/src/tiles/Tile.o: src/tiles/Tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/Tile.o src/tiles/Tile.cpp

${OBJECTDIR}/src/pathfinding/BSPTree.o: src/pathfinding/BSPTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pathfinding/BSPTree.o src/pathfinding/BSPTree.cpp

${OBJECTDIR}/src/components/Selector.o: src/components/Selector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Selector.o src/components/Selector.cpp

${OBJECTDIR}/src/FixedLayer.o: src/FixedLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FixedLayer.o src/FixedLayer.cpp

${OBJECTDIR}/src/pathfinding/Space.o: src/pathfinding/Space.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pathfinding/Space.o src/pathfinding/Space.cpp

${OBJECTDIR}/src/ObjectFactory.o: src/ObjectFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ObjectFactory.o src/ObjectFactory.cpp

${OBJECTDIR}/src/gameobjects/Enemy.o: src/gameobjects/Enemy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Enemy.o src/gameobjects/Enemy.cpp

${OBJECTDIR}/src/tiles/TiledObjectLayer.o: src/tiles/TiledObjectLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/TiledObjectLayer.o src/tiles/TiledObjectLayer.cpp

${OBJECTDIR}/src/gameobjects/GameObject.o: src/gameobjects/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/GameObject.o src/gameobjects/GameObject.cpp

${OBJECTDIR}/src/pathfinding/Pathfinding.o: src/pathfinding/Pathfinding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pathfinding/Pathfinding.o src/pathfinding/Pathfinding.cpp

${OBJECTDIR}/src/components/RtsCamera.o: src/components/RtsCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/RtsCamera.o src/components/RtsCamera.cpp

${OBJECTDIR}/src/components/Cursor.o: src/components/Cursor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Cursor.o src/components/Cursor.cpp

${OBJECTDIR}/src/gameobjects/Tree.o: src/gameobjects/Tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Tree.o src/gameobjects/Tree.cpp

${OBJECTDIR}/src/gameobjects/Crate.o: src/gameobjects/Crate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Crate.o src/gameobjects/Crate.cpp

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
