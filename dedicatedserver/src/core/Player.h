#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <phantom.h>
#include <sharedlib/networking/networking.h>
#include <functional>
#include <map>

class GameHub;

class Player : public yaxl::concurrency::Thread {
public:
    typedef std::function<Packet*(Packet*)> PacketEvent;

    enum States {
        NEWPLAYER,
        IDENT_REQUESTED,
        IDENT_ACCEPTED
    };

    Player(GameHub* gamehub, yaxl::socket::Socket* socket);
    ~Player();
    void run(void);
    void sendPacket(Packet* packet);
    void takeInitiative();
    void registerEvent(PacketType type, PacketEvent event);

private:
    GameHub* _gamehub;
    PacketReader* _packetReader;
    yaxl::socket::Socket* _socket;
    States _state;
    yaxl::concurrency::Stack<Packet*> _sendBuffer;

    void handlePacket(Packet* packet);

    void readPackets(void);
    void writePackets(void);

    std::map<const PacketType, PacketEvent> _packetEvents;
};

#endif	/* PLAYER_H */
