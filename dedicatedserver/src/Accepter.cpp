#include "Accepter.h"

Accepter::Accepter(GameHub* server) :
    _socket(5555)
{
    _server = server;
}

Accepter::~Accepter() {

}

void Accepter::run(void) {
    do {
        cout << "Ready to accept a new client." << endl;

        yaxl::socket::Socket* client = _socket.accept();

        _server->onNewConnection(client);
    } while(true);
}
