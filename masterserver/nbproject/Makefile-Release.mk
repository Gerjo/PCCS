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
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/Client.o \
	${OBJECTDIR}/src/Master.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Werror -lphantom -lyaxl -lsharedlib
CXXFLAGS=-Werror -lphantom -lyaxl -lsharedlib

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist -Wl,-rpath,../dist -Wl,-rpath,.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/masterserver.run

../dist/masterserver.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -o ../dist/masterserver.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I../libyaxl/libyaxl -I../sharedlib/src -I../phantom/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/Client.o: src/Client.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I../libyaxl/libyaxl -I../sharedlib/src -I../phantom/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Client.o src/Client.cpp

${OBJECTDIR}/src/Master.o: src/Master.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I../libyaxl/libyaxl -I../sharedlib/src -I../phantom/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Master.o src/Master.cpp

# Subprojects
.build-subprojects:
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/masterserver.run

# Subprojects
.clean-subprojects:
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
