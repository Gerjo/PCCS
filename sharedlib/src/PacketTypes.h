#ifndef PACKETTYPES_H
#define	PACKETTYPES_H

enum PacketTypes {
    DEFAULT     = 0,

    // Identification:
    IDENT_WHOAREYOU   = 1,
    IDENT_IAM         = 2,
    IDENT_ACCEPTED    = 3,

    // Is alive:
    PING              = 10,
    PONG              = 11,

    // Errors:
    WARNING           = 20,

    REQUEST_LARGE_PACKET = 30,
    REPLY_LARGE_PACKET   = 31,

    LASTITEM
};

#endif	/* PACKETTYPES_H */

