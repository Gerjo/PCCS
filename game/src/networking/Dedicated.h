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

class Packet;
class Ping;
class BandwidthTest;

class Dedicated : public Composite, public AbstractNetwork, public IBroadcast {
public:
    Dedicated(Game& game);
    virtual ~Dedicated();

    void init(void);
    void addText(string text);
    void update(const Time& time);

    Ping* ping;
    BandwidthTest* bandwidthTest;
    AuthState authState;


    // Internal use only. NB: solve with a messaging proxy.
    void sendBufferedMessage(AbstractMessage* message);
    virtual void broadcast(GameObject* recipient, Message<Data>* message);
    void introduceGameObject(GameObject* gameobject);
    void sendServerMessage(GameObject* recipient, Message<Data>* message);

    virtual void onConnectionSuccess(void);
    virtual void onConnectionFail(const yaxl::socket::SocketException& ex);

private:
    Game& _game;
    CommandQueue _commands;

    // TODO: deques
    yaxl::concurrency::Queue<Packet> _packetBuffer;
    yaxl::concurrency::Queue<AbstractMessage> _messageBuffer;
};

#endif	/* NETWORK_H */

