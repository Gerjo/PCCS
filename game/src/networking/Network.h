#ifndef NETWORK_H
#define	NETWORK_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>
#include <sharedlib/networking/networking.h>
#include <sharedlib/CommandQueue.h>
#include "../Game.h"
#include <map>
#include <deque>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/services/Services.h>

using namespace phantom;
using namespace std;

class Writer;
class Reader;
class Packet;
class Ping;
class BandwidthTest;

class Network : public Composite, private PacketEventMixin, public IBroadcast {
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
    AuthState authState;

    // Internal use only. NB: solve with a messaging proxy.
    void sendBufferedMessage(AbstractMessage* message);
    virtual void broadcast(GameObject* recipient, Message<Data>* message);
    void introduceGameObject(GameObject* gameobject);
    void sendServerMessage(GameObject* recipient, Message<Data>* message);
    friend class Reader;
    friend class Writer;

private:
    yaxl::socket::OutputStream& getOutputStream(void);
    PacketReader& getPacketReader(void);

    PacketReader* _packetReader;
    Game& _game;
    yaxl::socket::Socket* _socket;
    Reader* _reader;
    Writer* _writer;

    CommandQueue _commands;

    yaxl::concurrency::Queue<Packet> _packetBuffer;
    yaxl::concurrency::Queue<AbstractMessage> _messageBuffer;
};

#endif	/* NETWORK_H */

