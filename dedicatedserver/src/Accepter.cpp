#include "Accepter.h"

Accepter::Accepter(GtServer* server) :
    _socket(5555)
{
    _server = server;
}

Accepter::~Accepter() {

}

void Accepter::run(void) {
    do {
        cout << "Thread started. Waiting for new clients:" << endl;

        yaxl::socket::Socket* client = _socket.accept();

        _server->onNewConnection(client);
    } while(true);
}
