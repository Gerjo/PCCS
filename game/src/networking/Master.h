#ifndef MASTER_H
#define	MASTER_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>
#include <sharedlib/networking/networking.h>
#include <sharedlib/CommandQueue.h>
#include "../Game.h"
#include <sharedlib/serialization/Data.h>
#include <sharedlib/models/DedicatedModel.h>
#include <vector>

using namespace phantom;

using std::cout;
using std::endl;
using std::vector;

class Master : public AbstractNetwork, public Composite {
public:
    Master(Game& game);
    virtual ~Master(void);
    void init(void);

    virtual void onConnectionSuccess(void);
    virtual void onConnectionFail(const yaxl::socket::SocketException& ex);
    virtual void onDisconnect(void);
    
    virtual void requestAvailableDedicated();

private:
    Game& _game;

};

#endif	/* MASTER_H */

