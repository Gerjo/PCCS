#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"
#include "PlayerPool.h"
#include <null/NullDriver.h>
#include "Master.h"

GameHub::GameHub() : phantom::PhantomGame(""), world(nullptr), _accepter(nullptr), pool(nullptr) {
    setDriver(new NullDriver(this));
    Settings::load();

    master = new Master(*this);

    // Info about us: (TODO: IP and port number).
    master->dedicatedModel.uid  = 0; // Default, the server will give us one.
    master->dedicatedModel.name = "Gerjo's awesome server";

    // Connects to the master, spawns two threads, and signals the "meh" condition.
    master->init();

    // The main thread will wait here.
    meh.wait();

    // Load the game :D
    onMasterConnected();
}

GameHub::~GameHub() {
    delete master;
    delete _accepter;
    delete pool;
}

void GameHub::onMasterConnected(void) {

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

    pushGameState(world);

    start(0, 0);

    // Blocking stuff (should be in destructor?)
    _accepter->join();
    pool->join();
}

void GameHub::onNewConnection(yaxl::socket::Socket* client) {
    // NB: Keep the code in this method as short as possible. While this method
    // is executed, no new clients can be accepted. This is OK until our backlog
    // is overrun, then new clients will be blocked by the kernel.

    Player* player = new Player(this, client);

    // The PlayerPool class shall now be responsible for deletion of players.
    pool->addPlayer(player);
}
