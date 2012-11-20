#include "Master.h"
#include "Dedicated.h"
#include "../gamestates/MenuState.h"
#include "../guicomponents/menu/ServerBrowser.h"

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
            cout << "Server UID: #(" << server.uid << "), Server Name: (" << server.name << ")";
            cout << "Server port: #(" << server.port << "), Server IPv4: (" << server.ipv4 << ")" << endl;
        }
        
        _commands.add([this, servers] () -> void {
            getGame<Game*>()->menu->serverBrowser->servers(servers);
        });

        return 0;
    });
}

Master::~Master(void) {

}

void Master::init(void) {
    cout << "Connecting to masterserver at " << Services::settings().master_host << ":" << Services::settings().master_port << endl;
    connect(Services::settings().master_host, Services::settings().master_port);
}

void Master::onConnectionSuccess(void) {
    _game.launchMenu();
}

void Master::onConnectionFail(const yaxl::socket::SocketException& ex) {
    // Still load the menu. The game can run without a master server, too.
    _game.launchMenu();
}

void Master::onDisconnect(void) {
    // TODO: reconnect code.
     cout << "!! WARNING: Lost connecting with master. You are probably still connected to the dedicated, and can carry on playing." << endl;
}

void Master::requestAvailableDedicated() {
    sendPacket(new Packet(PacketType::REQUEST_LIST_SERVERS));
}

void Master::update(const Time& time) {
    _commands.run();
}

