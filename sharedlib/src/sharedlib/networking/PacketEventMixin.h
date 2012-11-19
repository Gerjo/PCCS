#ifndef PACKETEVENTMIXIN_H
#define	PACKETEVENTMIXIN_H

#include <map>
#include <functional>
#include "Packet.h"
#include "PacketType.h"

class LIBEXPORT PacketEventMixin {
public:
    typedef std::function<Packet*(Packet*)> PacketEvent;

    void registerPacketEvent(PacketType type, PacketEvent event);
    void emitPacketEvent(Packet* packet);
    void clearPacketEvents();

    virtual void sendPacket(Packet* packet) = 0;

private:
    std::map<const PacketType, PacketEvent> _packetEvents;
    
};

#endif	/* PACKETEVENTMIXIN_H */

