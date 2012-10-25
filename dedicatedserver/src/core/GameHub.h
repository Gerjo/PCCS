#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"
#include <yaxl.h>
#include "../game/ServerWorld.h"

class Accepter;
class Player;
class PlayerPool;

class GameHub {
public:
    GameHub();
    virtual ~GameHub();
    void onNewConnection(yaxl::socket::Socket* client);

    ServerWorld* world;
    PlayerPool* pool;

private:
    GameHub(const GameHub& orig);
    Accepter* _accepter;
};

#endif	/* GTSERVER_H */

