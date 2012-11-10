#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"
#include "PlayerPool.h"
#include <null/NullDriver.h>

GameHub::GameHub() : phantom::PhantomGame("") {
    setDriver(new NullDriver(this));
    Settings::load();

    world     = new ServerWorld(this);
    pool      = new PlayerPool(this);
    _accepter = new Accepter(this);

    // Attach the service implementation:
    Services::setBroadcast(pool);

    cout << "Summoning trees, ninja turtles, magic fairies and pink ponies." << endl;
    world->generate();
    cout << "All critters have reported ready." << endl;

    // Spawns a thread:
    _accepter->start();
    pool->start();
    //world->start();

    pushGameState(world);

    start(0, 0);

    // Blocking stuff (should be in destructor?)
    _accepter->join();
    pool->join();
}

GameHub::~GameHub() {
    // TODO: are we killing all threads in an OK manner?
    delete _accepter;
    delete pool;
    //delete world;
}

void GameHub::onNewConnection(yaxl::socket::Socket* client) {
    // NB: Keep the code in this method as short as possible. While this method
    // is executed, no new clients can be accepted. This is OK until our backlog
    // is overrun, then new clients will be blocked by the kernel.

    Player* player = new Player(this, client);

    // The PlayerPool class shall now be responsible for deletion of players.
    pool->addPlayer(player);
}
