#ifndef PACKETEVENTMIXIN_H
#define	PACKETEVENTMIXIN_H

#include <map>
#include <functional>
#include "networking.h"

class PacketEventMixin {
public:
    typedef std::function<Packet*(Packet*)> PacketEvent;

    void registerEvent(PacketType type, PacketEvent event);
    void emitEvent(Packet* packet);

    virtual void sendPacket(Packet* packet) = 0;
private:
    std::map<const PacketType, PacketEvent> _packetEvents;
};

#endif	/* PACKETEVENTMIXIN_H */

