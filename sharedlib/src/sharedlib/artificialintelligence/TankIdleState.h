#ifndef AIIDLESTATE_H_
#define AIIDLESTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class LIBEXPORT TankIdleState : public AIState {
    void construct() { };
    void handle(const phantom::Time& time) { };
    void destruct() { };
};

#endif