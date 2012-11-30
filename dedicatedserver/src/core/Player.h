#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <phantom.h>
#include <sharedlib/networking/networking.h>
#include <functional>
#include <sharedlib/models/PlayerModel.h>
#include <deque>
#include <sharedlib/services/Services.h>
#include <sharedlib/gameobjects/LightFactory.h>

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
    vector<LightSoldier*> _soldiers;
    bool _isThreadRunning;
    yaxl::concurrency::CachedCondition _sleepCondition;

    void handleDeadlines();
    void handlePacket(Packet* packet);
    void readPackets(void);
    void writePackets(void);
    void loadSoldiers(void);
};

#endif	/* PLAYER_H */
