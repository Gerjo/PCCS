#include "Reader.h"

Reader::Reader(Network& network) : _network(network), isAlive(true) {

}

Reader::~Reader() {

}

void Reader::run(void) {
    _network.addText("Started reading worker thread.");

    PacketReader& reader = _network.getPacketReader();
    do {
        Packet* packet = reader.readNext();

        if(packet != 0) {
            _network.onPacketReceived(packet);
        }
    } while(isAlive);
}