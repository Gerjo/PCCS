#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include "Writer.h"
#include "Ping.h"
#include "../BandwidthTest.h"
#include "../gamestates/ClientWorld.h"


Network::Network(Game& game) : _game(game), authState(ROGUE) {
    _socket          = 0;
    _packetReader    = 0;
    _reader          = new Reader(*this);
    _writer          = new Writer(*this);

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
        authState = AUTH_STARTED;
        return new Packet(PacketType::IDENT_IAM, "insert name here");
    });

    registerPacketEvent(IDENT_ACCEPTED, [this] (Packet* packet) -> Packet* {
        Data data = Data::fromJson(packet->getPayload());

        PlayerModel model = PlayerModel::fromData(data);
        getGame<Game*>()->me = model;

        authState = AUTHENTICATED;
        return new Packet(PacketType::REQUEST_GAMEWORLD);
    });

    registerPacketEvent(REPLY_LARGE_PACKET, [this] (Packet* packet) -> Packet* {
        bandwidthTest->onPacketReceived(packet);
        return 0;
    });

    registerPacketEvent(REPLY_GAMEWORLD, [this] (Packet* packet) -> Packet* {
        getGame<Game*>()->world->load(packet->getPayload());
        return 0;
    });

    registerPacketEvent(PUSH_GAMEOBJECTS, [this] (Packet* packet) -> Packet* {
        getGame<Game*>()->world->push(packet->getPayload());
        return 0;
    });

    registerPacketEvent(DIRECT_PIPE, [this] (Packet* packet) -> Packet* {
        string payload = packet->getPayload();

        _commands.add([payload] () mutable -> void {
            Data data = Data::fromJson(payload);

            // Reconstruct the message:
            Message<Data>* message = new Message<Data>((string) data("type"), data("payload"));

            // Send it directly to a gameobject:
            GameObject* gameobject = NetworkRegistry::get(data("UID_network"));
            gameobject->handleMessage(message);

            delete message;
        });

        return 0;
    });
}


Network::~Network() {

    _writer->isAlive = false;
    _reader->isAlive = false;

    if(_socket != 0) {
        delete _socket;
    }

    if(_packetReader != 0) {
        delete _packetReader;
    }

    _writer->join();
    _reader->join();

    delete _writer;
    delete _reader;
}

void Network::sendNetworkMessage(GameObject* sender, Message<Data>* message) {
    Data data;
    data("UID_network") = sender->UID_network;
    data("payload")     = message->getData(); // move ctor?
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::DIRECT_PIPE, data.toJson());

    // TODO: threads!!
    sendPacket(packet);
}

void Network::addText(string text) {
    sendBufferedMessage(new Message<string>("loader-text", text));
}

void Network::init(void) {
    addText("Connecting to dedicated server " + Settings::SERVER_HOST + ":" + Settings::SERVER_PORT);

    try {
        _socket = new yaxl::socket::Socket(Settings::SERVER_HOST, Settings::SERVER_PORT);

        _packetReader = new PacketReader(_socket->getInputStream());

        _reader->start();
        _writer->start();

        // Magic packet, start the auth process.
        sendPacket(new Packet(PacketType::IDENT_LETSCONNECT, "Want to be friends?"));

        addText("... connected!");

        _socket->setTcpNoDelay(true);



    } catch(const yaxl::socket::SocketException& ex) {
        stringstream ss;
        ss << "Libyaxl SocketException: " << ex.what();
        ss << ". Errno: " << errno;
        addText(ss.str());
        cout << ss.str() << endl;
    }
}

yaxl::socket::OutputStream& Network::getOutputStream(void) {
    return _socket->getOutputStream();
}

PacketReader&  Network::getPacketReader(void) {
    return *_packetReader;
}

void Network::sendPacket(Packet* packet) {
    _writer->sendPacket(packet);
}

void Network::onPacketReceived(Packet* packet) {
    stringstream ss;
    ss << "> " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
    addText(ss.str());
    cout << ss.str() << endl; // *meh*
    emitPacketEvent(packet);
}

void Network::sendBufferedMessage(AbstractMessage* message) {
    _messageBuffer.push(message);
}

void Network::update(const Time& time) {
    Composite::update(time);

    AbstractMessage *message;
    while((message = _messageBuffer.tryPop()) != 0) {
        _game.handleMessage(message);
        delete message;
        message = 0;
    }

    _commands.run();
}