#include "Client.h"
#include "Master.h"

Client::Client(yaxl::socket::Socket* socket, Master* master) :
        BlockingReader(socket),
        _master(master),
        _socket(socket) {

}

Client::~Client() {
    
}

void Client::onPacket(Packet* packet){
    _master->handlePacket(packet, this);
}
