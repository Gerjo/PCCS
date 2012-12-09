#ifndef FOLLOWSTATE_H
#define	FOLLOWSTATE_H

#include "../AIState.h"

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class FlockState : public AIState {
public:
    FlockState() {

    }

    virtual void setLeader(GameObject* leader) {
        _leader = leader;

        cout << "flocking.." << endl;
    }

    virtual void construct() {
        AIState::construct();
    }

    virtual void handle(const phantom::PhantomTime& time) {

    }

    virtual void destruct() {
        AIState::destruct();

    }

private:
    GameObject* _leader;
};


#endif	/* FOLLOWSTATE_H */

