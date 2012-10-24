#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"
#include "PlayerPool.h"

GameHub::GameHub() {
    pool  = new PlayerPool(this);
    _accepter = new Accepter(this);

    cout << "Summoning trees, ninja turtles, magic fairies and pink ponies." << endl;
    world.generate();
    cout << "All critters have reported ready. Here is de Data of this world:" << endl;
    cout << "-----" << endl;
    cout << world.getSerializedData().toJson() << endl;;
    cout << "-----" << endl;

    // Spawns a thread:
    _accepter->start();

    // Blocking stuff.
    _accepter->join();
}

GameHub::GameHub(const GameHub& orig) {
    throw new ServerException(
            "You are not allowed to copy GtServer. "
            "Use pointers or references instead.");
}

GameHub::~GameHub() {
    delete _accepter;
    delete pool;
}

void GameHub::onNewConnection(yaxl::socket::Socket* client) {
    // NB: Keep the code in this method as short as possible. While this method
    // is executed, no new clients can be accepted. This is OK until our backlog
    // is overrun, then new clients will be blocked by the kernel.

    Player* player = new Player(this, client);

    // The PlayerPool class shall now be responsible for deletion of players.
    pool->addPlayer(player);
}
