#include "MasterFacade.h"

MasterFacade::MasterFacade() : _socket(nullptr), _isAlive(true) {

}

MasterFacade::~MasterFacade() {
    _isAlive = false;
    delete _socket;
}

void MasterFacade::run(void) {
    do {

    } while(_isAlive);
}

void MasterFacade::sendPacket(Packet* packet) {
    // send!
}