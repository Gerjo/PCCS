#ifndef NETWORK_H
#define	NETWORK_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>

#include "../Game.h"

using namespace phantom;
using namespace std;

class Reader;
class Packet;

class Network : public Composite {
public:
    Network(Game& game);
    virtual ~Network();

    void init(void);
    void addText(string text);

    void onPacketReceived(Packet* packet);

    friend class Reader;
private:
    yaxl::socket::OutputStream& getOutputStream(void);
    yaxl::socket::InputStream& getInputStream(void);

    Game& _game;
    yaxl::socket::Socket* _socket;
    Reader* _reader;
};

#endif	/* NETWORK_H */

