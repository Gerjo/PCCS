#ifndef MASTERFACADE_H
#define	MASTERFACADE_H

#include "../networking.h"
#include "yaxl.h"

class LIBEXPORT MasterFacade : public PacketEventMixin, public yaxl::concurrency::Thread {
public:
    MasterFacade();
    virtual ~MasterFacade();
    virtual void sendPacket(Packet* packet);
    virtual void run(void);

private:
    bool _isAlive;
    yaxl::socket::Socket* _socket;
};

#endif	/* MASTERFACADE_H */

