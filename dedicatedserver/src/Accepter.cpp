#include "Accepter.h"

Accepter::Accepter(GameHub* server) :
    _socket(8075),
    _server(server)
{
    _socket.setKeepAlive(true);
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
