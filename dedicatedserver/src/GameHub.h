#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"
#include <yaxl.h>

class Accepter;
class Player;

class GameHub {
public:
    GameHub();
    virtual ~GameHub();

    void onNewConnection(yaxl::socket::Socket* client);


private:
    GameHub(const GameHub& orig);
    Accepter* _accepter;
};

#endif	/* GTSERVER_H */

