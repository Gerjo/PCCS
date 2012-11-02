#ifndef PACKETTYPE_H_SHAREDLIB
#define	PACKETTYPE_H_SHAREDLIB

#include <sstream>
#include "../CompileConfig.h"

// NB: These are serialized to a short-int byte array.
enum LIBEXPORT PacketType {
    DEFAULT = 0,

    // Identification:
    IDENT_WHOAREYOU   = 1,
    IDENT_IAM         = 2,
    IDENT_ACCEPTED    = 3,
    IDENT_LETSCONNECT = 4,

    // Is alive:
    PING              = 10,
    PONG              = 11,
    YOU_TIMED_OUT     = 12,

    // Errors:
    WARNING           = 20,

    // Testing stuff:
    REQUEST_LARGE_PACKET = 30,
    REPLY_LARGE_PACKET   = 31,


    // World sync stuff:
    REQUEST_GAMEWORLD    = 50,
    REPLY_GAMEWORLD      = 51,


    // Soldier sync:
    SOLDIER_COMMAND      = 100,


    // Other dynamic object sync:
    PUSH_GAMEOBJECTS     = 120,
    DIRECT_PIPE          = 121,
    SYNC_POSITION        = 122,
    REQUEST_INTRODUCE    = 123,
    ACCEPTED_INTRODUCE   = 124,
    REJECTED_INTRODUCE   = 125
};

// One reason C# of Java are enjoyable, they have build-in reverse lookups. C++
// however, does not.
struct LIBEXPORT PacketTypeHelper {
    static std::string toString(const short& type) {
        return PacketTypeHelper::toString((PacketType) type);
    }

    static std::string toString(const PacketType type) {
        switch(type) {
            case DEFAULT:              return "DEFAULT-ENUM-ITEM";
            case IDENT_WHOAREYOU:      return "IDENT_WHOAREYOU";
            case IDENT_IAM:            return "IDENT_IAM";
            case IDENT_ACCEPTED:       return "IDENT_ACCEPTED";
            case IDENT_LETSCONNECT:    return "IDENT_LETSCONNECT";
            case PING:                 return "PING";
            case PONG:                 return "PONG";
            case YOU_TIMED_OUT:        return "YOU_TIMED_OUT";
            case WARNING:              return "WARNING";
            case REQUEST_LARGE_PACKET: return "REQUEST_LARGE_PACKET";
            case REPLY_LARGE_PACKET:   return "REPLY_LARGE_PACKET";
            case REQUEST_GAMEWORLD:    return "REQUEST_GAMEWORLD";
            case REPLY_GAMEWORLD:      return "REPLY_GAMEWORLD";
            case PUSH_GAMEOBJECTS:     return "PUSH_GAMEOBJECTS";
            case SOLDIER_COMMAND:      return "SOLDIER_COMMAND";
            case SYNC_POSITION:        return "SYNC_POSITION";
            case DIRECT_PIPE:          return "DIRECT_PIPE";
            case REQUEST_INTRODUCE:    return "REQUEST_INTRODUCE";
            case ACCEPTED_INTRODUCE:   return "ACCEPTED_INTRODUCE";
            case REJECTED_INTRODUCE:   return "REJECTED_INTRODUCE";

            default: {
                std::stringstream ss;
                ss << "!! WARNING: No reverse lookup available in PacketType.h for enum #" << type;
                return ss.str();
            }

        }
    }
};




#endif	/* PACKETTYPES_H_SHAREDLIB */

