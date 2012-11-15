#ifndef MASTER_H
#define	MASTER_H

#include <sharedlib/networking/networking.h>
#include <sharedlib/SharedSettings.h>
#include <sharedlib/models/DedicatedModel.h>
#include "GameHub.h"
#include <iostream>

using std::cout;
using std::endl;

class Master : public AbstractNetwork {
public:
    Master(GameHub& gamehub) : _gamehub(gamehub) {
        loadLambdas();
    }

    void loadLambdas() {
        registerPacketEvent(PacketType::MASTER_IDENT_ACCEPTED, [&] (Packet* packet) -> Packet* {
            Data data = Data::fromPacket(packet);

            int uid = data("uid");

            cout << "+ Received UID " << uid << " from master." << endl;

            dedicatedModel.uid = uid;

            _gamehub.meh.signal();

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
        sendPacket(new Packet(PacketType::MASTER_LETSCONNECT, dedicatedModel.toData()));

        // Wakup the game.
        //_gamehub.meh.signal();
    }

    virtual void onConnectionFail(const yaxl::socket::SocketException& ex) {
        cout << "Unable to connect to master. Attempting to continue without a masterserver." << endl;

        // Wakup the game.
        _gamehub.meh.signal();
    }

    DedicatedModel dedicatedModel;
private:
    GameHub& _gamehub;
};

#endif	/* MASTER_H */

