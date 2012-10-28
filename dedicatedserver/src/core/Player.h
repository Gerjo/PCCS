#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <phantom.h>
#include <sharedlib/networking/networking.h>
#include <functional>
#include <sharedlib/models/PlayerModel.h>

class GameHub;

class Player : public yaxl::concurrency::Thread, private PacketEventMixin {
public:
    Player(GameHub* gamehub, yaxl::socket::Socket* socket);
    ~Player();
    void run(void);
    virtual void sendPacket(Packet* packet);
    void takeInitiative();

    PlayerModel model;
    AuthState authState;

private:
    GameHub* _gamehub;
    PacketReader* _packetReader;
    yaxl::socket::Socket* _socket;
    yaxl::concurrency::Stack<Packet*> _sendBuffer;

    void handlePacket(Packet* packet);
    void readPackets(void);
    void writePackets(void);
};

#endif	/* PLAYER_H */
