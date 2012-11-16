#include "Master.h"
#include "Dedicated.h"

Master::Master(Game& game) : _game(game) {
    registerPacketEvent(PacketType::REPLY_AVAILABLE_SERVERS, [this] (Packet* packet) -> Packet* {

        Data data = Data::fromPacket(packet);

        cout << "Available servers:" << endl;

        vector<DedicatedModel> servers;

        for(Data::KeyValue pair : data("servers")) {
            servers.push_back(DedicatedModel::fromData(pair.second));
        }

        // Iterating again, as a test to show the models are working:
        for(DedicatedModel server :servers) {
            cout << "Server UID: #(" << server.uid << "), Server Name: (" << server.name << ")" << endl;
        }

        // TODO: Amazing code to handle the servers and add them to the GUI.

        return 0;
    });
}

Master::~Master(void) {

}

void Master::init(void) {
    connect("localhost", 8071);
}

void Master::onConnectionSuccess(void) {
    _game.launchMenu();
    cout << "Master: Connected to master." << endl;
}

void Master::onConnectionFail(const yaxl::socket::SocketException& ex) {
    // Still load the menu. The game can run without a master server, too.
    _game.launchMenu();
    cout << "Master: " << ex.what() << endl;
}

void Master::requestAvailableDedicated() {
    sendPacket(new Packet(PacketType::REQUEST_LIST_SERVERS));
}

