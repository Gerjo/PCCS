#include "Master.h"
#include "Client.h"

Master::Master() :_server(nullptr), _isAlive(true), UID_counter(10) {
    cout << "Creating ServerSocket..." << endl;
    _server = new yaxl::socket::ServerSocket(8071);
    cout << "success" << endl;

    loadLambdas();

    cout << "Listening for new connections." << endl;
    run();

}

Master::~Master() {
    _isAlive = false;

    delete _server;
    _server  = nullptr;
}

void Master::loadLambdas() {
    registerPacketEvent(MASTER_LETSCONNECT, [this] (Packet* packet, Client* client) {

        Data data;
        data("uid") = UID_counter++;

        client->write(new Packet(PacketType::MASTER_IDENT_ACCEPTED, data.toJson()));
    });
}

void Master::registerPacketEvent(PacketType type, LambdaEvent event) {
    std::pair<PacketType, LambdaEvent> eventpair(type, event);

    _handlers.insert(eventpair);
}

void Master::onConnect(Client* client) {
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