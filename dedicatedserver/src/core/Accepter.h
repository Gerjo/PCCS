#ifndef ACCEPTER_H
#define	ACCEPTER_H

#include "Accepter.h"
#include "GameHub.h"
#include <sharedlib/services/Services.h>
#include "yaxl.h"

class Accepter : public yaxl::concurrency::Thread {
public:
    Accepter(GameHub* server);
    virtual ~Accepter();
    virtual void run(void);

private:
    GameHub* _server;
    yaxl::socket::ServerSocket _socket;

};

#endif	/* ACCEPTER_H */

