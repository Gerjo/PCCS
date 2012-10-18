#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"
#include <yaxl.h>

class Accepter;

class GtServer {
public:
    GtServer();
    virtual ~GtServer();

    void onNewConnection(yaxl::socket::Socket* client);

private:
    GtServer(const GtServer& orig);
    Accepter* _accepter;
};

#endif	/* GTSERVER_H */

