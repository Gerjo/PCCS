#include "Accepter.h"

Accepter::Accepter(GtServer* server) {
    _server = server;
}

Accepter::~Accepter() {

}

void Accepter::run(void) {
    cout << "Thread started." << endl;
}
