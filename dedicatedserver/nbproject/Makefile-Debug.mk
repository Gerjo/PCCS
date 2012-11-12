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
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/game/ServerWorld.o \
	${OBJECTDIR}/src/core/Player.o \
	${OBJECTDIR}/src/Settings.o \
	${OBJECTDIR}/src/core/GameHub.o \
	${OBJECTDIR}/src/core/Accepter.o \
	${OBJECTDIR}/src/NetworkFactory.o \
	${OBJECTDIR}/src/core/PlayerPool.o


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
LDLIBSOPTIONS=-L../dist -Wl,-rpath,.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/dedicated.run

../dist/dedicated.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -o ../dist/dedicated.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/game/ServerWorld.o: src/game/ServerWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/game/ServerWorld.o src/game/ServerWorld.cpp

${OBJECTDIR}/src/core/Player.o: src/core/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/core
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core/Player.o src/core/Player.cpp

${OBJECTDIR}/src/Settings.o: src/Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Settings.o src/Settings.cpp

${OBJECTDIR}/src/core/GameHub.o: src/core/GameHub.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/core
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core/GameHub.o src/core/GameHub.cpp

${OBJECTDIR}/src/core/Accepter.o: src/core/Accepter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/core
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core/Accepter.o src/core/Accepter.cpp

${OBJECTDIR}/src/NetworkFactory.o: src/NetworkFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/NetworkFactory.o src/NetworkFactory.cpp

${OBJECTDIR}/src/core/PlayerPool.o: src/core/PlayerPool.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/core
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core/PlayerPool.o src/core/PlayerPool.cpp

# Subprojects
.build-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/dedicated.run

# Subprojects
.clean-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libyaxl && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../sharedlib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
