#include "Writer.h"

Writer::Writer(Network& network) : _network(network), isAlive(true) {

}

Writer::~Writer() {

}

void Writer::sendPacket(Packet* packet) {
    _buffer.push(packet);
}

void Writer::run(void) {
    do {
        Packet* packet;
        while((packet = _buffer.tryPop()) != 0) {
            stringstream ss;
            ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
            _network.addText(ss.str());

            const char* bytes = packet->getBytes();
            _network.getOutputStream().write(bytes, packet->length());

            delete packet;
            delete[] bytes;
        }

        sleep(200);
    } while(isAlive);
}

// 11:00