#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"
#include "PlayerPool.h"
#include <null/NullDriver.h>
#include "Master.h"

GameHub::GameHub() : phantom::PhantomGame(""), world(nullptr), _accepter(nullptr), pool(nullptr) {
    setDriver(new NullDriver(this));

    Services::settings()->loadFromFile("conf/settings.json");

    // Added as component, just incase it wants to sync with the game.
    addComponent(master = new Master(*this));

    // Info about us: (TODO: IP and port number).
    master->dedicatedModel.uid  = 0; // Default, the server will give us one.
    master->dedicatedModel.name = Services::settings()->dedicated_name;
    master->dedicatedModel.port = Services::settings()->dedicated_port;
    master->dedicatedModel.ipv4 = "0.0.0.0"; // The master will inform us about our real IP.

    // Connects to the master, spawns two threads, and signals the "meh" condition.
    master->init();

    // The main thread will wait here. Once we are connected to the master, the
    // semaphore will be signalled.
    masterSemaphore.wait();

    // Load the game :D
    onMasterConnected();
}

GameHub::~GameHub() {
    delete master;    master = nullptr; // Deleted via phantomgame due to composite?
    delete _accepter; _accepter = nullptr;
    delete pool;      pool = nullptr;
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
