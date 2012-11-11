#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <phantom.h>
#include <sharedlib/networking/networking.h>
#include <functional>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/Timer.h>
#include "../Settings.h"
#include <deque>

using std::deque;

class GameHub;

class Player : public yaxl::concurrency::Thread, private PacketEventMixin {
public:
    Player(GameHub* gamehub, yaxl::socket::Socket* socket);
    virtual ~Player();
    void run(void);
    virtual void sendPacket(Packet* packet);
    void takeInitiative();

    PlayerModel model;
    AuthState authState;

    void disconnect();
    bool shouldDelete();

    string toString();

private:
    GameHub* _gamehub;
    PacketReader* _packetReader;
    yaxl::socket::Socket* _socket;
    deque<Packet*> _sendBuffer;
    Timer _authDeadline;
    Timer _pingDeadline;

    bool _isThreadRunning;

    void handleDeadlines();
    void handlePacket(Packet* packet);
    void readPackets(void);
    void writePackets(void);
};

#endif	/* PLAYER_H */
