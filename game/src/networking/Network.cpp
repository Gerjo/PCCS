#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include "Ping.h"
#include "src/BandwidthTest.h"


Network::Network(Game& game) : _game(game) {
    _socket          = 0;
    _packetReader    = 0;
    _isAuthenticated = false;
    _reader          = new Reader(*this);

    addComponent(ping = new Ping());
    addComponent(bandwidthTest = new BandwidthTest());
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
    sendBufferedMessage(new Message<string>("loader-text", text));
}

void Network::init(void) {
    addText("Connecting to dedicated server localhost:8075");

    try {
        _socket = new yaxl::socket::Socket("localhost", "8075");
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
    stringstream ss;
    ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
    addText(ss.str());

    const char* bytes = packet->getBytes();

    getOutputStream().write(bytes, packet->length());

    delete packet;
    delete[] bytes;
}

void Network::onPacketReceived(Packet* packet) {
    stringstream ss;
    ss << "> " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
    addText(ss.str());

    switch(packet->getType()) {
        case PacketType::IDENT_WHOAREYOU: {
            Packet* reply = new Packet(PacketType::IDENT_IAM);
            sendPacket(reply);
        } break;

        case PacketType::IDENT_ACCEPTED: {
            _isAuthenticated = true;
            sendPacket(new Packet(PacketType::REQUEST_GAMEWORLD));
        } break;

        case PacketType::PONG:
        case PacketType::PING: {
            ping->onPacketReceived(packet);
        } break;

        case PacketType::REPLY_LARGE_PACKET:
        case PacketType::REQUEST_LARGE_PACKET: {
            bandwidthTest->onPacketReceived(packet);
        } break;

    }

    delete packet;
}

void Network::sendBufferedMessage(AbstractMessage* message) {
    _messages.push_back(message);
}

void Network::update(const float& elapsed) {
    Composite::update(elapsed);

    for(AbstractMessage* message : _messages) {
        _game.handleMessage(message);

        delete message;
    }

    _messages.clear();
}