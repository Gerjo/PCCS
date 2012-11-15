#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"
#include <yaxl.h>
#include <phantom.h>
#include "../game/ServerWorld.h"
#include <sharedlib/services/Services.h>
#include <sharedlib/models/MasterCookie.h>
#include <sharedlib/networking/networking.h>
class Accepter;
class Player;
class PlayerPool;

class GameHub : public phantom::PhantomGame {
public:
    GameHub();
    virtual ~GameHub();
    void onNewConnection(yaxl::socket::Socket* client);

    ServerWorld* world;
    PlayerPool* pool;
    MasterCookie serverModel;
    MasterFacade master;
private:
    GameHub(const GameHub& orig);
    Accepter* _accepter;
};

#endif	/* GTSERVER_H */

