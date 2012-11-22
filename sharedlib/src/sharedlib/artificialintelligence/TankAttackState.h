#ifndef AIATTACKSTATE_H_
#define AIATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"
#include "../gameobjects/LightTank.h"

class LIBEXPORT TankAttackState : public AIState {
public:
    LightTank *tank;

    TankAttackState(LightTank *tank);

    void construct();
    void handle(const phantom::Time &time);
    void destruct();
};

#endif