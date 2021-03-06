#ifndef PING_H
#define	PING_H

#include <sharedlib/networking/Packet.h>
#include <sharedlib/networking/PacketType.h>
#include <iostream>
#include <phantom.h>

using namespace phantom;

class Game;

class Ping : public Composite {
public:
    Ping();
    ~Ping();
    void update(const PhantomTime& time);
    void onPacketReceived(Packet* packet);
    void sendPing(void);
    void onPong(void);
    double getPing(void);

private:
    double _currentPing;
    bool _isPingSent;
    double _pingStartTime;
    double _lastPong;
    Game* _game;

    Timer _timer;
};

#endif	/* PING_H */

