#ifndef READER_H
#define	READER_H

#include <yaxl.h>
#include <phantom.h>
#include "Network.h"
#include <sharedlib/Packet.h>
#include <sstream>
#include <sharedlib/PacketReader.h>

using namespace phantom;
using namespace std;

class Reader : public yaxl::concurrency::Thread {
public:
    Reader(Network& network);
    virtual ~Reader();
    virtual void run(void);

private:
    Network& _network;
};

#endif	/* READER_H */

