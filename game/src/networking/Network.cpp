#include "Network.h"
#include "../gamestates/Loader.h"
#include "Reader.h"
#include "Writer.h"
#include "Ping.h"
#include "../BandwidthTest.h"
#include "../gamestates/ClientWorld.h"


Network::Network(Game& game) : _game(game), authState(ROGUE), _socket(nullptr), _packetReader(nullptr) {
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
        return new Packet(PacketType::IDENT_IAM, Settings::NICKNAME);
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

    registerPacketEvent(ACCEPTED_INTRODUCE, [this] (Packet* packet) -> Packet* {
        /*Data data  = Data::fromJson(packet->getPayload());
        string UID_network = data("UID_network").toString();
        string UID_local   = data("UID_local").toString();

        GameObject* gameobject = getGame<Game*>()->localRegistry.get(UID_local);

        if(gameobject != nullptr) {
            gameobject->UID_network = UID_network;
            cout << "accepted " << UID_network << endl;

            NetworkRegistry::add(gameobject);
        } else {
            cout << "died? " << data.toJson() << endl;
        }*/

        return 0;
    });

    registerPacketEvent(REJECTED_INTRODUCE, [this] (Packet* packet) -> Packet* {
        cout << "!! INTRODUCTION REJECTED." << endl;
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

            if(gameobject != nullptr) {
                gameobject->handleMessage(message);
            }

            delete message;
        });

        return 0;
    });
}


Network::~Network() {

    _reader->isAlive = false;
    _writer->forceQuit();

    try {
        cout << "Network.cpp: stopping _writer." << endl;
        _writer->join();

    } catch(yaxl::concurrency::ConcurrencyException& e) {
        cout << "Network.cpp: writer: " << e.what() << endl;
    }

    try {
        cout << "Network.cpp: stopping InputStream." << endl;
        _socket->getInputStream().forceQuit();

    } catch(yaxl::socket::SocketException& e) {
        cout << "Network.cpp: InputStream: " << e.what() << endl;

    } catch(...) {
        cout << "Network.cpp: InputStream: Unknown exception." << endl;
    }

    try {
        cout << "Network.cpp: stopping _reader." << endl;
        _reader->join();

    } catch(yaxl::concurrency::ConcurrencyException& e) {
        cout << "Network.cpp: _reader, ConcurrencyException: " << e.what() << endl;

    } catch(yaxl::socket::SocketException& e) {
        cout << "Network.cpp: _reader, SocketException: " << e.what() << endl;

    } catch(...) {
        cout << "Network.cpp: _reader: Unknown exception." << endl;
    }

    cout << "Network.cpp: Deleting everything network related" << endl;

    delete _socket;       _socket       = nullptr;
    delete _packetReader; _packetReader = nullptr;
    delete _writer;       _writer       = nullptr;
    delete _reader;       _reader       = nullptr;

    cout << "Network.cpp: Clearing any messages from the queues" << endl;
    AbstractMessage *message;
    while((message = _messageBuffer.tryPop()) != 0) {
        _game.handleMessage(message);
        delete message;
        message = 0;
    }

    cout << "Network.cpp: and it's gone." << endl;
}

void Network::introduceGameObject(GameObject* gameobject) {
    Data data;
    gameobject->toData(data);

    Packet* packet = new Packet(PacketType::REQUEST_INTRODUCE, data.toJson());
    sendPacket(packet);

    //getGame<Game*>()->localRegistry.add(gameobject);
}

void Network::broadcast(GameObject* recipient, Message<Data>* message) {
    Data data;
    data("UID_network") = recipient->UID_network;
    data("payload")     = message->getData(); // move ctor?
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::DIRECT_PIPE, data.toJson());

    sendPacket(packet);
}

// Bit of copy pasting that needs to be merged into one method?
void Network::sendServerMessage(GameObject* recipient, Message<Data>* message) {
    Data data;
    data("UID_network") = recipient->UID_network;
    data("payload")     = message->getData(); // move ctor?
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::SERVER_PIPE, data.toJson());

    sendPacket(packet);
}

void Network::addText(string text) {
    sendBufferedMessage(new Message<string>("loader-text", text));
}

void Network::init(void) {
    addText("Connecting to dedicated server " + Settings::SERVER_HOST + ":" + Settings::SERVER_PORT);
    Console::log("Connecting to dedicated server " + Settings::SERVER_HOST + ":" + Settings::SERVER_PORT);

    try {
        _socket = new yaxl::socket::Socket(Settings::SERVER_HOST, Settings::SERVER_PORT);

        _packetReader = new PacketReader(_socket->getInputStream());

        _reader->start();
        _writer->start();

        // Magic packet, start the auth process.
        sendPacket(new Packet(PacketType::IDENT_LETSCONNECT, "Want to be friends?"));

        addText("... connected!");

        Console::log("Connection established.");

        _socket->setTcpNoDelay(true);

    } catch(const yaxl::socket::SocketException& ex) {
        stringstream ss;
        ss << "Libyaxl SocketException: " << ex.what();
        ss << ". Errno: " << errno;
        addText(ss.str());
        Console::log("Connection failed: " + string(ex.what()));
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
    ss << "> " << PacketTypeHelper::toString(packet->getType())
    << " (" << packet->getPayloadLength() << " bytes, "
    << packet->estimatedLatency() << "ms) ";

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
