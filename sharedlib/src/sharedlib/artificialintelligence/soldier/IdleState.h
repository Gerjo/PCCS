#ifndef IDLE_H
#define	IDLE_H
#include "../AIState.h"

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class IdleState : public AIState {
public:
    IdleState() {

    }

    virtual void construct() {
        AIState::construct();
    }

    virtual void handle(const phantom::PhantomTime& time) {

    }

    virtual void destruct() {
        AIState::destruct();

    }
};

#endif	/* IDLE_H */

