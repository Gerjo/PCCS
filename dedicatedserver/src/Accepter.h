#ifndef ACCEPTER_H
#define	ACCEPTER_H

#include "Accepter.h"
#include "GtServer.h"

#include "yaxl.h"

class Accepter : public yaxl::concurrency::Thread {
public:
    Accepter(GtServer* server);
    virtual ~Accepter();
    virtual void run(void);

private:
    GtServer* _server;
};

#endif	/* ACCEPTER_H */

