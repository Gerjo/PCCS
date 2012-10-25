#ifndef PACKETTYPE_H_SHAREDLIB
#define	PACKETTYPE_H_SHAREDLIB

#include "../CompileConfig.h"

enum LIBEXPORT PacketType {
    DEFAULT = 0,

    // Identification:
    IDENT_WHOAREYOU   = 1,
    IDENT_IAM         = 2,
    IDENT_ACCEPTED    = 3,

    // Is alive:
    PING              = 10,
    PONG              = 11,

    // Errors:
    WARNING           = 20,

    // Testing stuff:
    REQUEST_LARGE_PACKET = 30,
    REPLY_LARGE_PACKET   = 31,


    // World sync stuff:
    REQUEST_GAMEWORLD    = 50,
    REPLY_GAMEWORLD      = 51

};

// One reason C# of Java are enjoyable, they have build-in reverse lookups. C++
// however, does not.
struct LIBEXPORT PacketTypeHelper {
    static std::string toString(const short& type) {
        return PacketTypeHelper::toString((PacketType) type);
    }
    static std::string toString(const PacketType type) {
        switch(type) {
            case DEFAULT:                 return "DEFAULT";
            case IDENT_WHOAREYOU:         return "IDENT_WHOAREYOU";
            case IDENT_IAM:               return "IDENT_IAM";
            case IDENT_ACCEPTED:          return "IDENT_ACCEPTED";
            case PING:                    return "PING";
            case PONG:                    return "PONG";
            case WARNING:                 return "WARNING";
            case REQUEST_LARGE_PACKET:    return "REQUEST_LARGE_PACKET";
            case REPLY_LARGE_PACKET:      return "REPLY_LARGE_PACKET";
            case REQUEST_GAMEWORLD:       return "REQUEST_GAMEWORLD";
            case REPLY_GAMEWORLD:         return "REPLY_GAMEWORLD";

            default:
                return "No reverse lookup available in PacketType.h";
        }
    }
};




#endif	/* PACKETTYPES_H_SHAREDLIB */

