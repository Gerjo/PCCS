#include "GameHub.h"
#include "Accepter.h"
#include "Player.h"

GameHub::GameHub() {
    _accepter = new Accepter(this);

    // Spawns a thread:
    _accepter->start();
}

GameHub::GameHub(const GameHub& orig) {
    throw new ServerException(
            "You are not allowed to copy GtServer. "
            "Use pointers or references instead.");
}

GameHub::~GameHub() {
    // Wait for the sub-thread to die:
    _accepter->join();

    delete _accepter;
}

void GameHub::onNewConnection(yaxl::socket::Socket* client) {
    // NB: Keep the code in this method as short as possible. While this method
    // is executed, no new clients can be accepted. This is OK until our backlog
    // is overrun, then new clients will be blocked by the kernel.

    Player* player = new Player(client);

    //cout << "New connection!" << endl;
    //client->getOutputStream().write("You will be disconnected now.\n");
    delete client;
}
