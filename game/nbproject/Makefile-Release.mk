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
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/gameobjects/Soldier.o \
	${OBJECTDIR}/src/tiles/Tile.o \
	${OBJECTDIR}/src/components/Selector.o \
	${OBJECTDIR}/src/FixedLayer.o \
	${OBJECTDIR}/src/ObjectFactory.o \
	${OBJECTDIR}/src/gameobjects/Tank.o \
	${OBJECTDIR}/src/tiles/TiledObjectLayer.o \
	${OBJECTDIR}/src/gameobjects/GameObject.o \
	${OBJECTDIR}/src/gameobjects/Water.o \
	${OBJECTDIR}/src/gameobjects/Ground.o \
	${OBJECTDIR}/src/components/Pathfinding.o \
	${OBJECTDIR}/src/components/RtsCamera.o \
	${OBJECTDIR}/src/gameobjects/Tree.o


# C Compiler Flags
CFLAGS=

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
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/json/elements.inl.gch: src/json/elements.inl 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o $@ src/json/elements.inl

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/gameobjects/Soldier.o: src/gameobjects/Soldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Soldier.o src/gameobjects/Soldier.cpp

${OBJECTDIR}/src/tiles/Tile.o: src/tiles/Tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/Tile.o src/tiles/Tile.cpp

${OBJECTDIR}/src/components/Selector.o: src/components/Selector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Selector.o src/components/Selector.cpp

${OBJECTDIR}/src/FixedLayer.o: src/FixedLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FixedLayer.o src/FixedLayer.cpp

${OBJECTDIR}/src/ObjectFactory.o: src/ObjectFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ObjectFactory.o src/ObjectFactory.cpp

${OBJECTDIR}/src/gameobjects/Tank.o: src/gameobjects/Tank.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Tank.o src/gameobjects/Tank.cpp

${OBJECTDIR}/src/tiles/TiledObjectLayer.o: src/tiles/TiledObjectLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/TiledObjectLayer.o src/tiles/TiledObjectLayer.cpp

${OBJECTDIR}/src/gameobjects/GameObject.o: src/gameobjects/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/GameObject.o src/gameobjects/GameObject.cpp

${OBJECTDIR}/src/gameobjects/Water.o: src/gameobjects/Water.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Water.o src/gameobjects/Water.cpp

${OBJECTDIR}/src/gameobjects/Ground.o: src/gameobjects/Ground.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Ground.o src/gameobjects/Ground.cpp

${OBJECTDIR}/src/components/Pathfinding.o: src/components/Pathfinding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/Pathfinding.o src/components/Pathfinding.cpp

${OBJECTDIR}/src/components/RtsCamera.o: src/components/RtsCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/components
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/components/RtsCamera.o src/components/RtsCamera.cpp

${OBJECTDIR}/src/json/reader.inl.gch: src/json/reader.inl 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o $@ src/json/reader.inl

${OBJECTDIR}/src/gameobjects/Tree.o: src/gameobjects/Tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Tree.o src/gameobjects/Tree.cpp

${OBJECTDIR}/src/json/writer.inl.gch: src/json/writer.inl 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o $@ src/json/writer.inl

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
