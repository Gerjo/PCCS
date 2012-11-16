#include "Master.h"
#include "Client.h"
#include "storage/StubStorage.h"

Master::Master() :_server(nullptr), _isAlive(true), UID_counter(10) {

    // At somepoint we could load a MySQL storage interface.
    _dataInterface = new StubStorage();

    cout << "+ Creating ServerSocket..." << endl;
    _server = new yaxl::socket::ServerSocket(SharedSettings::MASTER_PORT());

    // Seperate method, easier for "code collapse".
    loadLambdas();

    cout << "+ Listening for new connections on port " << SharedSettings::MASTER_PORT() << endl;
    run();
}

Master::~Master() {
    _isAlive = false;

    delete _server;
    _server  = nullptr;

    delete _dataInterface;
    _dataInterface = nullptr;
}

void Master::onDisconnect(Client* client) {
    yaxl::concurrency::ScopedLock lock(_clientMutex);

    for(auto it = _clients.begin(); it != _clients.end(); ++it) {
        if(*it == client) {
            _clients.erase(it);
            break;
        }
    }
    client->detach();
    delete client;
}

void Master::loadLambdas() {
    registerPacketEvent(MASTER_LETSCONNECT, [this] (Packet* packet, Client* client) {
	Data data            = Data::fromJson(packet->getPayload());
	DedicatedModel model = DedicatedModel::fromData(data);
	model.uid            = ++UID_counter;
        data("uid")          = model.uid;

        client->write(new Packet(PacketType::MASTER_IDENT_ACCEPTED, data.toJson()));

	_dataInterface->registerServer(model);
    });

    registerPacketEvent(MASTER_PING, [this] (Packet* packet, Client* client) -> Packet* {
        Data data = Data::fromJson(packet->getPayload());

        DedicatedModel model = DedicatedModel::fromData(data);

        cout << "+ Updating heartbeat of server UID #" << model.uid << endl;

        client->write(new Packet(PacketType::MASTER_PONG));

        _dataInterface->updatePing(model.uid);
    });

    registerPacketEvent(REQUEST_LIST_SERVERS, [this] (Packet* packet, Client* client) -> Packet* {
        Data data = _dataInterface->listServers();

        client->write(new Packet(PacketType::MASTER_PONG, data.toJson()));
    });


}

void Master::registerPacketEvent(PacketType type, LambdaEvent event) {
    std::pair<PacketType, LambdaEvent> eventpair(type, event);

    _handlers.insert(eventpair);
}

void Master::onConnect(Client* client) {
    yaxl::concurrency::ScopedLock lock(_clientMutex);

    cout << "Accepted a new client." << endl;
    _clients.push_back(client);

    client->start();
}

void Master::run(void) {
    do {
        onConnect(new Client(_server->accept(), this));
    } while(_isAlive);
}

void Master::handlePacket(Packet* packet, Client* client) {
    packet->retain();

    PacketType type = static_cast<PacketType>(packet->getType());

    if(_handlers.find(type) != _handlers.end()){
        _handlers.at(type)(packet, client);
    } else {
        cout << "Packet of type" << PacketTypeHelper::toString(type) << " was left unhandled. " << endl;
    }

    packet->release();
}
