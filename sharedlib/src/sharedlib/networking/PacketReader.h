#ifndef PACKETREADER_H_Gerjo
#define	PACKETREADER_H_Gerjo

#include <yaxl.h>
#include "Packet.h"
#include <sstream>
#include <string>
#include <iostream>
#include "../CompileConfig.h"

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

            if(payload.length() < 1 || payload.at(payload.length() - 1) != Packet::EOT) {
                cout << "WARNING! Packet declined, payload is less than 1 or EOT mismatch." << endl;
                cout << "Type: " << packet->getType() << endl;
                cout << "Prio: " << packet->getPriority() << endl;
                cout << "Version: " << packet->getVersion() << endl;
                cout << "Payload Size: " << packet->getPayloadLength() << endl;

                cout << "Dumping the first 6 bytes: " << endl;
                for(unsigned int i = 0; i < bytes.length(); ++i) {
                    cout << i << ": " << Packet::formatByte(bytes.at(i)) << endl;
                }

            } else {
                payload.resize(payload.length() - 1);

                packet->setPayload(payload);

                return packet;

            }
        }

        return 0;
    }

private:
    yaxl::socket::InputStream& _inputStream;
};

#endif	/* PACKETREADER_H_Gerjo */

