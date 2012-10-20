#ifndef PLAYER_H
#define	PLAYER_H

#include <yaxl.h>
#include <Packet.h>

class Player {
public:
    enum States { NEWPLAYER };

    Player(yaxl::socket::Socket* socket);
    virtual ~Player();

private:
    yaxl::socket::Socket* _socket;
    void identify(void);

};

#endif	/* PLAYER_H */

