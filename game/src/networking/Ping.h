#ifndef PING_H
#define	PING_H

#include <Packet.h>
#include <PacketTypes.h>
#include <iostream>
#include <phantom.h>

using namespace phantom;

class Game;

class Ping : public Composite {
public:
    Ping();
    ~Ping();
    void update(const float& elapsed);
    void onPacketReceived(Packet* packet);
    void sendPing(void);
    void onPong(void);

private:
    bool _isPingSent;
    double _pingStartTime;
    Game* _game;
};

#endif	/* PING_H */

