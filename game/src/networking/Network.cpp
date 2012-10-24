#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include "Ping.h"
#include "src/BandwidthTest.h"
#include "src/gamestates/ClientWorld.h"


Network::Network(Game& game) : _game(game) {
    _socket          = 0;
    _packetReader    = 0;
    _isAuthenticated = false;
    _reader          = new Reader(*this);

    addComponent(ping = new Ping());
    addComponent(bandwidthTest = new BandwidthTest());


    registerPacketEvent(PING, [this] (Packet* packet) -> Packet* {
        return new Packet(PacketType::PONG, "PONG");
    });

    registerPacketEvent(PONG, [this] (Packet* packet) -> Packet* {
        ping->onPacketReceived(packet);
        return 0;
    });

    registerPacketEvent(IDENT_WHOAREYOU, [this] (Packet* packet) -> Packet* {
        return new Packet(PacketType::IDENT_IAM, "insert name here");
    });

    registerPacketEvent(IDENT_ACCEPTED, [this] (Packet* packet) -> Packet* {
        _isAuthenticated = true;
        return new Packet(PacketType::REQUEST_GAMEWORLD, "insert name here");
    });

    registerPacketEvent(REPLY_LARGE_PACKET, [this] (Packet* packet) -> Packet* {
        bandwidthTest->onPacketReceived(packet);
        return 0;
    });

    registerPacketEvent(REPLY_GAMEWORLD, [this] (Packet* packet) -> Packet* {
        getGame<Game*>()->world->load(packet->getPayload());
        return 0;
    });
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

    emitPacketEvent(packet);
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