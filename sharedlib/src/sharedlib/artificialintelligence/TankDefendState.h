#ifndef TANKDEFENDSTATE_H_
#define TANKDEFENDSTATE_H_

#include "AIState.h"
#include "../CompileConfig.h"

class LightTank;
class BSPTree;

class LIBEXPORT TankDefendState : public AIState {
public:
    LightTank *tank;
    BSPTree *tree;

    TankDefendState(LightTank *tank);
    void handle(const phantom::PhantomTime& time);
};

#endif