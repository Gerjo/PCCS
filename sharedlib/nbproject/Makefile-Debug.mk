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
	${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/AssaultRifle.o \
	${OBJECTDIR}/src/sharedlib/serialization/Data.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/Crate.o \
	${OBJECTDIR}/src/sharedlib/pathfinding/Pathfinding.o \
	${OBJECTDIR}/src/sharedlib/networking/PacketReader.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightBullet.o \
	${OBJECTDIR}/src/sharedlib/pathfinding/Space.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightWeapon.o \
	${OBJECTDIR}/src/sharedlib/ClickableEntity.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightFactory.o \
	${OBJECTDIR}/src/sharedlib/networking/Packet.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightTank.o \
	${OBJECTDIR}/src/sharedlib/SharedSettings.o \
	${OBJECTDIR}/src/sharedlib/networking/NetworkRegistry.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o \
	${OBJECTDIR}/src/sharedlib/networking/UID.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightSoldier.o \
	${OBJECTDIR}/src/sharedlib/CommandQueue.o \
	${OBJECTDIR}/src/sharedlib/pathfinding/BSPTree.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/StandardBullet.o \
	${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o \
	${OBJECTDIR}/src/sharedlib/networking/PacketEventMixin.o


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

${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/AssaultRifle.o: src/sharedlib/gameobjects/behaviours/AssaultRifle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects/behaviours
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/AssaultRifle.o src/sharedlib/gameobjects/behaviours/AssaultRifle.cpp

${OBJECTDIR}/src/sharedlib/serialization/Data.o: src/sharedlib/serialization/Data.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/serialization
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/serialization/Data.o src/sharedlib/serialization/Data.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/Crate.o: src/sharedlib/gameobjects/Crate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/Crate.o src/sharedlib/gameobjects/Crate.cpp

${OBJECTDIR}/src/sharedlib/pathfinding/Pathfinding.o: src/sharedlib/pathfinding/Pathfinding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/pathfinding/Pathfinding.o src/sharedlib/pathfinding/Pathfinding.cpp

${OBJECTDIR}/src/sharedlib/networking/PacketReader.o: src/sharedlib/networking/PacketReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/networking/PacketReader.o src/sharedlib/networking/PacketReader.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightBullet.o: src/sharedlib/gameobjects/LightBullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightBullet.o src/sharedlib/gameobjects/LightBullet.cpp

${OBJECTDIR}/src/sharedlib/pathfinding/Space.o: src/sharedlib/pathfinding/Space.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/pathfinding/Space.o src/sharedlib/pathfinding/Space.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightWeapon.o: src/sharedlib/gameobjects/LightWeapon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightWeapon.o src/sharedlib/gameobjects/LightWeapon.cpp

${OBJECTDIR}/src/sharedlib/ClickableEntity.o: src/sharedlib/ClickableEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/ClickableEntity.o src/sharedlib/ClickableEntity.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightFactory.o: src/sharedlib/gameobjects/LightFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightFactory.o src/sharedlib/gameobjects/LightFactory.cpp

${OBJECTDIR}/src/sharedlib/networking/Packet.o: src/sharedlib/networking/Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/networking/Packet.o src/sharedlib/networking/Packet.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightTank.o: src/sharedlib/gameobjects/LightTank.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightTank.o src/sharedlib/gameobjects/LightTank.cpp

${OBJECTDIR}/src/sharedlib/SharedSettings.o: src/sharedlib/SharedSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/SharedSettings.o src/sharedlib/SharedSettings.cpp

${OBJECTDIR}/src/sharedlib/networking/NetworkRegistry.o: src/sharedlib/networking/NetworkRegistry.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/networking/NetworkRegistry.o src/sharedlib/networking/NetworkRegistry.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o: src/sharedlib/gameobjects/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/GameObject.o src/sharedlib/gameobjects/GameObject.cpp

${OBJECTDIR}/src/sharedlib/networking/UID.o: src/sharedlib/networking/UID.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/networking/UID.o src/sharedlib/networking/UID.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightSoldier.o: src/sharedlib/gameobjects/LightSoldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightSoldier.o src/sharedlib/gameobjects/LightSoldier.cpp

${OBJECTDIR}/src/sharedlib/CommandQueue.o: src/sharedlib/CommandQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/CommandQueue.o src/sharedlib/CommandQueue.cpp

${OBJECTDIR}/src/sharedlib/pathfinding/BSPTree.o: src/sharedlib/pathfinding/BSPTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/pathfinding
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/pathfinding/BSPTree.o src/sharedlib/pathfinding/BSPTree.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/StandardBullet.o: src/sharedlib/gameobjects/behaviours/StandardBullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects/behaviours
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/behaviours/StandardBullet.o src/sharedlib/gameobjects/behaviours/StandardBullet.cpp

${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o: src/sharedlib/gameobjects/LightTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/gameobjects/LightTree.o src/sharedlib/gameobjects/LightTree.cpp

${OBJECTDIR}/src/sharedlib/networking/PacketEventMixin.o: src/sharedlib/networking/PacketEventMixin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sharedlib/networking
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I../libyaxl/libyaxl -I../phantom/src -std=c++11 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sharedlib/networking/PacketEventMixin.o src/sharedlib/networking/PacketEventMixin.cpp

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
