#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"
#include "PlayerPool.h"

GameHub::GameHub() {
    _players  = new PlayerPool(this);
    _accepter = new Accepter(this);

    // Spawns a thread:
    _accepter->start();

    // Blocking.
    _accepter->join();
}

GameHub::GameHub(const GameHub& orig) {
    throw new ServerException(
            "You are not allowed to copy GtServer. "
            "Use pointers or references instead.");
}

GameHub::~GameHub() {
    delete _accepter;
}

void GameHub::onNewConnection(yaxl::socket::Socket* client) {
    // NB: Keep the code in this method as short as possible. While this method
    // is executed, no new clients can be accepted. This is OK until our backlog
    // is overrun, then new clients will be blocked by the kernel.

    Player* player = new Player(client);

    // The PlayerPool class shall now be responsible for deletion of players.
    _players->addPlayer(player);
}
