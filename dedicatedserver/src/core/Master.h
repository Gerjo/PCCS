#ifndef MASTER_H
#define	MASTER_H

#include <sharedlib/networking/networking.h>
#include <sharedlib/SharedSettings.h>
#include <sharedlib/models/DedicatedModel.h>
#include "GameHub.h"
#include <iostream>
#include <phantom.h>

using std::cout;
using std::endl;
using namespace phantom;

class Master : public AbstractNetwork, public Composite {
public:
    Master(GameHub& gamehub) : _gamehub(gamehub), _isPingSent(false), _pingTimer(SharedSettings::PING_INTERVALMASTER()) {
        loadLambdas();
    }

    void loadLambdas() {
        registerPacketEvent(PacketType::MASTER_IDENT_ACCEPTED, [this] (Packet* packet) -> Packet* {
            Data data = Data::fromPacket(packet);

            dedicatedModel.uid = data("uid");

            cout << "+ Received UID " << dedicatedModel.uid << " from master." << endl;

            _gamehub.meh.signal();

            return 0;
        });

        registerPacketEvent(PacketType::MASTER_PONG, [this] (Packet* packet) -> Packet* {
            _isPingSent = false;
            _pingTimer.restart();
            return 0;
        });

    }

    void init(void) {
        cout << "Connecting to masterserver at " << SharedSettings::MASTER_HOST() << ":" << SharedSettings::MASTER_PORT() << endl;

        connect(SharedSettings::MASTER_HOST(), SharedSettings::MASTER_PORT());
    }

    virtual void onConnectionSuccess(void) {
        cout << "Connected to master server." << endl;

        // Start auth routine.
        sendPacket(new Packet(PacketType::MASTER_LETSCONNECT, dedicatedModel.toData().toJson()));

        // Wakup the game.
        //_gamehub.meh.signal();
    }

    virtual void onConnectionFail(const yaxl::socket::SocketException& ex) {
        cout << "Unable to connect to master. Attempting to continue without a masterserver." << endl;

        // Wakup the game.
        _gamehub.meh.signal();
    }

    virtual void onDisconnect(void) {
        // TODO: reconnect code.
        cout << "!! WARNING: lost connecting to master. Proceeding without a master." << endl;
    }

    virtual void update(const Time& time) {
        if(!_isPingSent && isConnected() && _pingTimer.hasExpired(time)) {
            sendPacket(new Packet(PacketType::MASTER_PING, dedicatedModel.toData().toJson()));
            _isPingSent = true;
        }
    }

    DedicatedModel dedicatedModel;

private:
    GameHub& _gamehub;
    Timer _pingTimer;
    bool _isPingSent;

};

#endif	/* MASTER_H */

