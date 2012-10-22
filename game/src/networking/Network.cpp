#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include "Ping.h"
#include <Packet.h>

Network::Network(Game& game) : _game(game) {
    _socket          = 0;
    _packetReader    = 0;
    _isAuthenticated = false;
    _reader          = new Reader(*this);

    addComponent(ping = new Ping());
}

Network::~Network() {
    if(_socket != 0) {
        delete _socket;
    }

    if(_packetReader != 0) {
        delete _packetReader;
    }
}

void Network::addText(string text) {
    _game.preloader->addText(text);
}

void Network::init(void) {
    addText("Connecting to dedicated server cis.gerardmeier.com:8075");

    try {
        _socket = new yaxl::socket::Socket("cis.gerardmeier.com", 8075);
        addText("... connected!");

        _socket->setTcpNoDelay(true);

        _packetReader = new PacketReader(_socket->getInputStream());

        _reader->start();

    } catch(const yaxl::socket::SocketException& ex) {
        stringstream ss;
        ss << "Libyaxl SocketException: " << ex.what();
        ss << ". Errno: " << errno;
        addText(ss.str());
    }
}

yaxl::socket::OutputStream& Network::getOutputStream(void) {
    return _socket->getOutputStream();
}

PacketReader&  Network::getPacketReader(void) {
    return *_packetReader;
}

void Network::sendPacket(Packet* packet) {
    addText("Out: " + packet->getPayload());

    const char* bytes = packet->getBytes();

    getOutputStream().write(bytes, packet->length());

    delete packet;
    delete[] bytes;
}

void Network::onPacketReceived(Packet* packet) {
    addText("in: " + packet->getPayload());

    switch(packet->getType()) {
        case IDENT_WHOAREYOU: {
            Packet* reply = new Packet(PacketTypes::IDENT_IAM, "I am Gerjo");
            sendPacket(reply);
        } break;

        case IDENT_ACCEPTED: {
            _isAuthenticated = true;
        } break;

        case PONG:
        case PING: {
            ping->onPacketReceived(packet);
        } break;
    }

    delete packet;
}

void Network::update(const float& elapsed) {
    Composite::update(elapsed);
}