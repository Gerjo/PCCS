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
	${OBJECTDIR}/src/structures/Edge.o \
	${OBJECTDIR}/src/Procedural.o \
	${OBJECTDIR}/src/structures/Corner.o \
	${OBJECTDIR}/src/structures/fortune/voronoi.o \
	${OBJECTDIR}/src/VoronoiDiagram.o \
	${OBJECTDIR}/src/structures/Center.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Werror
CXXFLAGS=-Werror

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist -Wl,-rpath,. -lphantom -lyaxl -lsharedlib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/dedicated.run

../dist/dedicated.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -o ../dist/dedicated.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/structures/Edge.o: src/structures/Edge.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/structures
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/structures/Edge.o src/structures/Edge.cpp

${OBJECTDIR}/src/Procedural.o: src/Procedural.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Procedural.o src/Procedural.cpp

${OBJECTDIR}/src/structures/Corner.o: src/structures/Corner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/structures
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/structures/Corner.o src/structures/Corner.cpp

${OBJECTDIR}/src/structures/fortune/voronoi.o: src/structures/fortune/voronoi.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/structures/fortune
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/structures/fortune/voronoi.o src/structures/fortune/voronoi.cpp

${OBJECTDIR}/src/VoronoiDiagram.o: src/VoronoiDiagram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/VoronoiDiagram.o src/VoronoiDiagram.cpp

${OBJECTDIR}/src/structures/Center.o: src/structures/Center.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/structures
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/structures/Center.o src/structures/Center.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/dedicated.run

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
