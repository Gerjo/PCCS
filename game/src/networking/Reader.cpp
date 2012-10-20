#include "Reader.h"

Reader::Reader(Network& network) : _network(network) {

}

Reader::~Reader() {

}

void Reader::run(void) {
    _network.addText("Started reading worker thread.");

    yaxl::socket::InputStream& in = _network.getInputStream();


    do {
        int available = in.available();

        if(available >= Packet::headerPrefixLength) {
            string bytes   = in.read(Packet::headerPrefixLength);
            Packet* packet = Packet::createHeader(bytes.c_str());

            string payload;
            int bytesLeft = packet->getPayloadLength() + Packet::headerPostfixLength;
            do {
                int available = in.available();

                if(available > 0) {
                    int readSize = min(bytesLeft, available);
                    payload     += in.read(readSize);
                    bytesLeft   -= readSize;
                }

            } while(bytesLeft > 0);

            if(payload.at(payload.length() - 1) == Packet::EOT) {
                payload.resize(payload.length() - 1);

                packet->setPayload(payload);

                _network.onPacketReceived(packet);

            } else {
                cout << "WARNING! Packet declined. EOT mismatch." << endl;
                delete packet;
            }
        }

        phantom::Util::sleep(300);
    } while(1);

}