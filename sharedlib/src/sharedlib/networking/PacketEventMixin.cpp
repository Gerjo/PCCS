#include "PacketEventMixin.h"

void PacketEventMixin::registerEvent(PacketType type, PacketEvent event) {
    _packetEvents.insert(std::pair<PacketType, PacketEvent>(
        type, event
    ));
}

void PacketEventMixin::emitEvent(Packet* packet) {
    const PacketType type = (PacketType) packet->getType();

    cout << "> " << PacketTypeHelper::toString(type) << " (" << packet->getPayloadLength() << " bytes)" << endl;

    if(_packetEvents.find(type) != _packetEvents.end()) {
        PacketEvent& handler = _packetEvents[type];

        Packet* reply = handler(packet);

        if(reply != 0) {
            sendPacket(reply);
        }
    }

    delete packet;
}