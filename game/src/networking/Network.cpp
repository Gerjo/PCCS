#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include <Packet.h>

Network::Network(Game& game) : _game(game) {
    _socket          = 0;
    _packetReader    = 0;
    _isAuthenticated = false;
    _reader          = new Reader(*this);
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
    addText("Connecting to dedicated server localhost:5555");

    try {
        _socket = new yaxl::socket::Socket("localhost", "5555");
        addText("... connected!");

        _packetReader = new PacketReader(_socket->getInputStream());

        _reader->start();

    } catch(const yaxl::socket::SocketException& ex) {
        stringstream ss;
        ss << "Libyaxl SocketException: " << ex.what();

        addText(ss.str());
    }
}

yaxl::socket::OutputStream& Network::getOutputStream(void) {
    return _socket->getOutputStream();
}

PacketReader&  Network::getPacketReader(void) {
    return *_packetReader;
}

void Network::writePacket(Packet* packet) {
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
            writePacket(reply);
            delete packet;
        } break;

        case IDENT_ACCEPTED: {
            _isAuthenticated = true;
        } break;
    }
}

void Network::update(const float& elapsed) {
    cout << "le updated" << endl;
}