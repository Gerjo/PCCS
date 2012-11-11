#ifndef WRITER_H
#define	WRITER_H

#include <yaxl.h>

#include "Network.h"
#include <iostream>
#include <deque>

using std::cout;
using std::endl;
using std::deque;

class Writer : public yaxl::concurrency::Thread {
public:
    Writer(Network& network);
    virtual ~Writer();
    virtual void run(void);
    void sendPacket(Packet* packet);

    bool isAlive;
private:
    Network& _network;
    deque<Packet*> _buffer;
    yaxl::concurrency::Semaphore _semaphore;
};

#endif	/* WRITER_H */

