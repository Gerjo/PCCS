#include "Client.h"
#include "Master.h"

Client::Client(yaxl::socket::Socket* socket, Master* master) :
        ThreadedReader(socket),
        _master(master),
        _socket(socket) {

}

Client::~Client() {

}

void Client::onPacket(Packet* packet){
    stringstream ss;
    ss << "> " << PacketTypeHelper::toString(packet->getType())
    << " (" << packet->getPayloadLength() << " bytes, "
    << packet->estimatedLatency() << "ms) ";
    cout << ss.str() << endl;

    _master->handlePacket(packet, this);
}

void Client::write(Packet* packet) {

    stringstream ss;
    ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
    cout << ss.str() << endl;

    const char* bytes = packet->getBytes();

    _socket->getOutputStream().write(bytes, packet->length());

    // Leak, if exception is thrown.
    delete packet;
    delete[] bytes;
}