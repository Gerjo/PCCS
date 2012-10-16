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
	${OBJECTDIR}/_ext/1147955449/md5.o \
	${OBJECTDIR}/_ext/900185589/Socket.o \
	${OBJECTDIR}/_ext/1147955449/AbstractFile.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/_ext/900185589/ServerSocket.o \
	${OBJECTDIR}/_ext/1682609240/Thread.o \
	${OBJECTDIR}/_ext/900185589/InputStream.o \
	${OBJECTDIR}/_ext/1446051756/examples.o \
	${OBJECTDIR}/_ext/1147955449/WinFileImpl.o \
	${OBJECTDIR}/_ext/1147955449/PosixFileImpl.o \
	${OBJECTDIR}/_ext/900185589/OutputStream.o


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

${OBJECTDIR}/_ext/1147955449/md5.o: ../libyaxl/libyaxl/file/md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1147955449
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1147955449/md5.o ../libyaxl/libyaxl/file/md5.cpp

${OBJECTDIR}/_ext/900185589/Socket.o: ../libyaxl/libyaxl/sockets/Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/900185589
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/900185589/Socket.o ../libyaxl/libyaxl/sockets/Socket.cpp

${OBJECTDIR}/_ext/1147955449/AbstractFile.o: ../libyaxl/libyaxl/file/AbstractFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1147955449
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1147955449/AbstractFile.o ../libyaxl/libyaxl/file/AbstractFile.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/_ext/900185589/ServerSocket.o: ../libyaxl/libyaxl/sockets/ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/900185589
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/900185589/ServerSocket.o ../libyaxl/libyaxl/sockets/ServerSocket.cpp

${OBJECTDIR}/_ext/1682609240/Thread.o: ../libyaxl/libyaxl/concurrency/Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1682609240
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1682609240/Thread.o ../libyaxl/libyaxl/concurrency/Thread.cpp

${OBJECTDIR}/_ext/900185589/InputStream.o: ../libyaxl/libyaxl/sockets/InputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/900185589
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/900185589/InputStream.o ../libyaxl/libyaxl/sockets/InputStream.cpp

${OBJECTDIR}/_ext/1446051756/examples.o: ../libyaxl/libyaxl/examples/examples.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1446051756
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1446051756/examples.o ../libyaxl/libyaxl/examples/examples.cpp

${OBJECTDIR}/_ext/1147955449/WinFileImpl.o: ../libyaxl/libyaxl/file/WinFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1147955449
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1147955449/WinFileImpl.o ../libyaxl/libyaxl/file/WinFileImpl.cpp

${OBJECTDIR}/_ext/1147955449/PosixFileImpl.o: ../libyaxl/libyaxl/file/PosixFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1147955449
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1147955449/PosixFileImpl.o ../libyaxl/libyaxl/file/PosixFileImpl.cpp

${OBJECTDIR}/_ext/900185589/OutputStream.o: ../libyaxl/libyaxl/sockets/OutputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/900185589
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -I. -I../libyaxl/libyaxl -I../sharedlib/src -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/900185589/OutputStream.o ../libyaxl/libyaxl/sockets/OutputStream.cpp

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
