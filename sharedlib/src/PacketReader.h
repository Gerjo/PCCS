#ifndef PACKETREADER_H_Gerjo
#define	PACKETREADER_H_Gerjo

#include <yaxl.h>
#include "Packet.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class PacketReader {
public:
    PacketReader(yaxl::socket::InputStream& inputStream) : _inputStream(inputStream) {

    }

    Packet* readNext(void) {

        int available = _inputStream.available();

        if(available >= Packet::headerPrefixLength) {
            string bytes   = _inputStream.read(Packet::headerPrefixLength);
            Packet* packet = Packet::createHeader(bytes.c_str());

            string payload;
            int bytesLeft = packet->getPayloadLength() + Packet::headerPostfixLength;
            do {
                int available = _inputStream.available();

                if(available > 0) {
                    int readSize = min(bytesLeft, available);
                    payload     += _inputStream.read(readSize);
                    bytesLeft   -= readSize;
                }

            } while(bytesLeft > 0);

            if(payload.at(payload.length() - 1) == Packet::EOT) {
                payload.resize(payload.length() - 1);

                packet->setPayload(payload);

                return packet;

            } else {
                cout << "WARNING! Packet declined. EOT mismatch." << endl;
                delete packet;

                return 0;
            }
        }

        return 0;
    }

private:
    yaxl::socket::InputStream& _inputStream;
};

#endif	/* PACKETREADER_H_Gerjo */

