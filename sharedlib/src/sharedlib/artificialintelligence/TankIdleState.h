#ifndef TANKIDLESTATE_H_
#define TANKIDLESTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class LightTank;

class LIBEXPORT TankIdleState : public AIState {
public:
    LightTank *tank;

    TankIdleState(LightTank *tank);
    void construct();
    void handle(const phantom::Time& time);
    void destruct();
};

#endif