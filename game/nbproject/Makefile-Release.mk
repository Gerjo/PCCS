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
	${OBJECTDIR}/src/sockets/SocketException.o \
	${OBJECTDIR}/src/sockets/Socket.o \
	${OBJECTDIR}/src/sockets/InputStream.o \
	${OBJECTDIR}/src/sockets/OutputStream.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Werror -lSDL
CXXFLAGS=-Werror -lSDL

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/game

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/game: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/game ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/sockets/SocketException.o: src/sockets/SocketException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/SocketException.o src/sockets/SocketException.cpp

${OBJECTDIR}/src/sockets/Socket.o: src/sockets/Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/Socket.o src/sockets/Socket.cpp

${OBJECTDIR}/src/sockets/InputStream.o: src/sockets/InputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/InputStream.o src/sockets/InputStream.cpp

${OBJECTDIR}/src/sockets/OutputStream.o: src/sockets/OutputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/OutputStream.o src/sockets/OutputStream.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/game

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
