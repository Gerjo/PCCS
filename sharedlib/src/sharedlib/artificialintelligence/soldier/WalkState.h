#ifndef WALKSTATE_H
#define	WALKSTATE_H

#include "../AIState.h"
#include <phantom.h>

using namespace phantom;


// tmp:
#include <iostream>
using std::cout;
using std::endl;

class WalkState : public AIState {
public:
    WalkState();

    void setTarget(const Vector3& target);
    virtual void construct();
    virtual void handle(const phantom::PhantomTime& time);
    virtual void destruct();

private:
    Vector3 _target;
};

#endif	/* WALKSTATE_H */

