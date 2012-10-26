#ifndef NETWORK_H
#define	NETWORK_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>
#include <sharedlib/networking/networking.h>
#include <sharedlib/CommandQueue.h>
#include "../Game.h"
#include <map>
#include <sharedlib/serialization/Data.h>

using namespace phantom;
using namespace std;

class Reader;
class Packet;
class Ping;
class BandwidthTest;

class Network : public Composite, private PacketEventMixin {
public:
    Network(Game& game);
    virtual ~Network();

    void init(void);
    void addText(string text);

    void onPacketReceived(Packet* packet);
    void sendPacket(Packet* packet);

    void update(const Time& time);

    Ping* ping;
    BandwidthTest* bandwidthTest;

    // Internal use only. NB: solve with a messaging proxy.
    void sendBufferedMessage(AbstractMessage* message);
    void sendNetworkMessage(GameObject* sender, Message<Data>* message);

    friend class Reader;

private:
    yaxl::socket::OutputStream& getOutputStream(void);
    PacketReader& getPacketReader(void);

    PacketReader* _packetReader;
    Game& _game;
    yaxl::socket::Socket* _socket;
    Reader* _reader;

    bool _isAuthenticated;

    deque<AbstractMessage*> _messages;
    CommandQueue _commands;
};

#endif	/* NETWORK_H */

