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
	${OBJECTDIR}/src/main.o


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
LDLIBSOPTIONS=-L../dist -Wl,-rpath,. -lphantom -lglut -lyaxl -lsharedlib -lpng15 -lpthread -lopenal -lvorbis -lprocedural

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/proceduraltest.run

../dist/proceduraltest.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -Werror -o ../dist/proceduraltest.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -I../procedural/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug
	cd ../procedural && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/proceduraltest.run

# Subprojects
.clean-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../procedural && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
