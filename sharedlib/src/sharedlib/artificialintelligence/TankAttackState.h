#ifndef TANKATTACKSTATE_H_
#define TANKATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class LightTank;

class LIBEXPORT TankAttackState : public AIState {
public:
    LightTank *tank;

    TankAttackState(LightTank *tank);
    void construct();
    void handle(const phantom::Time &time);
    void destruct();
};

#endif