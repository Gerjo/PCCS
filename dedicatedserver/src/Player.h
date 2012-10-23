#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <phantom.h>
#include <Packet.h>
#include <PacketTypes.h>
#include <PacketReader.h>

class Player : public yaxl::concurrency::Thread {
public:
    enum States {
        NEWPLAYER,
        IDENT_REQUESTED,
        IDENT_ACCEPTED
    };

    Player(yaxl::socket::Socket* socket);
    ~Player();
    void run(void);
    void sendPacket(Packet* packet);

private:
    PacketReader* _packetReader;
    yaxl::socket::Socket* _socket;
    States _state;
    yaxl::concurrency::Stack<Packet*> _sendBuffer;

    void handlePacket(Packet* packet);
};

#endif	/* PLAYER_H */

