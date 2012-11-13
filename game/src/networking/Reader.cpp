#include "Reader.h"

Reader::Reader(Network& network) : _network(network), isAlive(true) {

}

Reader::~Reader() {

}

void Reader::run(void) {
    _network.addText("Started reading worker thread.");

    PacketReader& reader = _network.getPacketReader();
    reader.setBlocking(true);
    do {
        Packet* packet = reader.readNext();

        if(packet != 0) {
            _network.onPacketReceived(packet);
        } else {
            cout << "Reader.cpp Error: false read. You are probably exiting the application." << endl;
        }

        //sleep(113);
    } while(isAlive);

    cout << "Reader.cpp Thread broke free" << endl;
}