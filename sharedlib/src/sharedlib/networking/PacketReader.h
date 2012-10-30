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
    PacketReader(yaxl::socket::InputStream& inputStream);
    Packet* readNext(void);

private:
    void readHeader();
    Packet* readPayload();
    void reset();
    bool isValid();

    yaxl::socket::InputStream& _inputStream;
    string _payload;
    bool _hasHeader;
    Packet* _packet;
};

#endif	/* PACKETREADER_H_Gerjo */

