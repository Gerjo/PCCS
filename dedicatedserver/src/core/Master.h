#ifndef MASTER_H
#define	MASTER_H

#include <sharedlib/networking/networking.h>
#include <sharedlib/models/DedicatedModel.h>
#include "GameHub.h"
#include <iostream>
#include <phantom.h>

using std::cout;
using std::endl;
using namespace phantom;

class Master : public AbstractNetwork, public Composite {
public:
    Master(GameHub& gamehub) : _gamehub(gamehub), _isPingSent(false), _pingTimer(Services::settings()->ping_interval_master) {
        loadLambdas();
    }

    void loadLambdas() {
        registerPacketEvent(PacketType::MASTER_IDENT_ACCEPTED, [this] (Packet* packet) -> Packet* {
            Data data = Data::fromPacket(packet);

            // The master is kind enough to give us these details:
            dedicatedModel.uid  = data("uid");
            dedicatedModel.ipv4 = data("ipv4").toString();

            cout << "+ Received UID " << dedicatedModel.uid << " from master. Public ip is " << dedicatedModel.ipv4 << endl;

            _gamehub.meh.signal();

            return 0;
        });

        registerPacketEvent(PacketType::MASTER_PONG, [this] (Packet* packet) -> Packet* {
            _pingTimer.restart();
            _isPingSent = false;
            return 0;
        });

    }

    void init(void) {
        cout << "Connecting to masterserver at " << Services::settings()->master_host << ":" << Services::settings()->master_port << endl;

        connect(Services::settings()->master_host, Services::settings()->master_port);
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

    virtual void update(const PhantomTime& time) {
        if( _pingTimer.hasExpired(time) && isConnected()) {
            if(!_isPingSent) {
                _isPingSent = true;

                //cout << " is connected? " << (int) isConnected() << endl;

                sendPacket(new Packet(PacketType::MASTER_PING, dedicatedModel.toData().toJson()));

            } else {
                //cout << "Timer expired, but not sending, no pong received." << endl;
            }
        }
    }

    DedicatedModel dedicatedModel;

private:
    GameHub& _gamehub;
    Timer _pingTimer;
    bool _isPingSent;

};

#endif	/* MASTER_H */

