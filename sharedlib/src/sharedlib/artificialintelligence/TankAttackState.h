#ifndef TANKATTACKSTATE_H_
#define TANKATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class LightTank;
class BSPTree;

class LIBEXPORT TankAttackState : public AIState {
public:
    LightTank *tank;
    BSPTree *tree;

    TankAttackState(LightTank *tank);
    void handle(const phantom::PhantomTime &time);
};

#endif