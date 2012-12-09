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

class FlockState : public AIState {
public:
    FlockState();

    virtual void setLeader(GameObject* leader);
    virtual void construct();
    virtual void handle(const phantom::PhantomTime& time);
    virtual void destruct();

private:
    GameObject* _leader;
    Timer _updateInterval;
};


#endif	/* FOLLOWSTATE_H */

