#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"

class GtServer {
public:
    GtServer();
    virtual ~GtServer();

private:
    GtServer(const GtServer& orig);
    
};

#endif	/* GTSERVER_H */

