#ifndef WALKSTATE_H
#define	WALKSTATE_H

#include "../AIState.h"

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class WalkState : public AIState {
public:
    WalkState() {

    }

    void setTarget(const Vector3 target) {
        _target = target;
    }

    virtual void construct() {
        AIState::construct();

        cout << "construct IdleState" << endl;
    }

    virtual void handle(const phantom::PhantomTime& time) {
        cout << "meh" << endl;
    }

    virtual void destruct() {
        AIState::destruct();

    }

private:
    Vector3 _target;
};

#endif	/* WALKSTATE_H */

