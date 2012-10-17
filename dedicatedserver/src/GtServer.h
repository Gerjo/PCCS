#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"

class Accepter;

class GtServer {
public:
    GtServer();
    virtual ~GtServer();

private:
    GtServer(const GtServer& orig);
    Accepter* _accepter;
};

#endif	/* GTSERVER_H */

