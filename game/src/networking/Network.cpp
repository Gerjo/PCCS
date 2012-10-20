#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include <Packet.h>

Network::Network(Game& game) : _game(game) {
    _socket = 0;
    _reader = new Reader(*this);
}

Network::~Network() {
    if(_socket != 0) {
        delete _socket;
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

yaxl::socket::InputStream& Network::getInputStream(void) {
    return _socket->getInputStream();
}

void Network::onPacketReceived(Packet* packet) {
    cout << "Do something with: '" << packet->getPayload() << "'" << endl;

    addText("in: " + packet->getPayload());

    delete packet;
}