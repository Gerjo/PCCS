#include "GtServer.h"
#include "Accepter.h"

GtServer::GtServer() {
    _accepter = new Accepter(this);

    // Spawns a thread:
    _accepter->start();
}

GtServer::GtServer(const GtServer& orig) {
    throw new ServerException(
            "You are not allowed to copy GtServer. "
            "Use pointers or references instead.");
}

GtServer::~GtServer() {
    // Wait for the sub-thread to die:
    _accepter->join();

    delete _accepter;
}

void GtServer::onNewConnection(yaxl::socket::Socket* client) {
    cout << "New connection!" << endl;
    client->getOutputStream().write("You will be disconnected now.\n");
    delete client;
}