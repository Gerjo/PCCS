#ifndef MASTER_H
#define	MASTER_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>
#include <sharedlib/networking/networking.h>
#include <sharedlib/CommandQueue.h>
#include "../Game.h"
#include <sharedlib/serialization/Data.h>


class Master : public AbstractNetwork {
public:
    Master(Game& game);
    virtual ~Master(void);
    void init(void);

    virtual void onConnectionSuccess(void);
    virtual void onConnectionFail(const yaxl::socket::SocketException& ex);

private:
    Game& _game;

};

#endif	/* MASTER_H */

