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
	${OBJECTDIR}/src/sharedlib/serialization/Subset.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/HeavyTree.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist/ -Wl,-rpath,.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/libsharedlib.${CND_DLIB_EXT}

../dist/libsharedlib.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -lyaxl -shared -o ../dist/libsharedlib.${CND_DLIB_EXT} -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/sharedlib/serialization/Subset.o: src/sharedlib/serialization/Subset.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/serialization
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/serialization/Subset.o src/sharedlib/serialization/Subset.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o: src/sharedlib/gameobjects/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o src/sharedlib/gameobjects/GameObject.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/HeavyTree.o: src/sharedlib/gameobjects/HeavyTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/HeavyTree.o src/sharedlib/gameobjects/HeavyTree.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o: src/sharedlib/gameobjects/LightTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o src/sharedlib/gameobjects/LightTree.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/libsharedlib.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
