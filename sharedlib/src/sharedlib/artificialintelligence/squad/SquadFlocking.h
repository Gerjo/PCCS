#ifndef FOLLOWSTATE_H
#define	FOLLOWSTATE_H

#include "../AIState.h"
#include <phantom.h>

using namespace phantom;

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class GameObject;

class SquadFlocking : public AIState {
public:
    SquadFlocking();

    virtual void setLeader(GameObject* leader);
    virtual void construct();
    virtual void update(const phantom::PhantomTime& time);
    virtual void destruct();
    virtual MessageState handleMessage(AbstractMessage* message);
private:
    GameObject* _leader;
    Timer _updateInterval;
};


#endif	/* FOLLOWSTATE_H */

