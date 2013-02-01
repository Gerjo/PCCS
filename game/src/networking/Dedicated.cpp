#include "Dedicated.h"
#include "../gamestates/Loader.h"
#include "Ping.h"
#include "../BandwidthTest.h"
#include "../gamestates/ClientWorld.h"


Dedicated::Dedicated(Game& game) : _game(game), authState(ROGUE) {

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
        return new Packet(PacketType::IDENT_IAM, Services::settings()->nickname);
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
        getGame<Game*>()->launchGame();
        
        return 0;
    });

    registerPacketEvent(PROCEDURAL, [this] (Packet *packet) -> Packet* {
        printf("%s", packet->getPayload());

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


Dedicated::~Dedicated() {
    cout << "Network.cpp: Clearing any messages from the queue" << endl;
    AbstractMessage *message;
    while((message = _messageBuffer.tryPop()) != 0) {
        _game.handleMessage(message);
        delete message;
        message = nullptr;
    }

    cout << "Network.cpp: and it's gone." << endl;
}

void Dedicated::onConnectionSuccess(void) {
    sendPacket(new Packet(PacketType::IDENT_LETSCONNECT, "Want to be friends?"));
}

void Dedicated::onConnectionFail(const yaxl::socket::SocketException& ex) {
    cout << ex.what() << endl;
}

void Dedicated::onDisconnect(void) {
    cout << "!! WARNING: Lost connecting with the dedicated server. Proceeding with unexpected results, and expected crashes." << endl;
}

void Dedicated::introduceGameObject(GameObject* gameobject) {
    Data data;
    gameobject->toData(data);

    Packet* packet = new Packet(PacketType::REQUEST_INTRODUCE, data.toJson());
    sendPacket(packet);

    //getGame<Game*>()->localRegistry.add(gameobject);
}

void Dedicated::broadcast(GameObject* recipient, Message<Data>* message) {
    Data data;
    data("UID_network") = recipient->UID_network;
    data("payload")     = message->getData(); // move ctor?
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::DIRECT_PIPE, data.toJson());

    sendPacket(packet);
}

// Bit of copy pasting that needs to be merged into one method?
void Dedicated::sendServerMessage(GameObject* recipient, Message<Data>* message) {
    Data data;
    data("UID_network") = recipient->UID_network;
    data("payload")     = message->getData(); // move ctor?
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::SERVER_PIPE, data.toJson());

    sendPacket(packet);
}

void Dedicated::addText(string text) {
    sendBufferedMessage(new Message<string>("loader-text", text));
}

void Dedicated::init(DedicatedModel model) {
    stringstream ss;

    ss << "Connecting to dedicated server " << model.ipv4 << ":" << model.port;

    addText(ss.str());
    Console::log(ss.str());

    connect(model.ipv4, model.port);
}

void Dedicated::sendBufferedMessage(AbstractMessage* message) {
    _messageBuffer.push(message);
}

void Dedicated::update(const PhantomTime& time) {
    Composite::update(time);

    AbstractMessage *message;
    while((message = _messageBuffer.tryPop()) != 0) {
        _game.handleMessage(message);
        delete message;
        message = 0;
    }

    _commands.run();
}
