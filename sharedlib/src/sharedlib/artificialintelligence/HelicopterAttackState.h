#ifndef HELICOPTERATTACKSTATE_H_
#define HELICOPTERATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class LightHelicopter;
class BSPTree;

class LIBEXPORT HelicopterAttackState : public AIState {
public:
    LightHelicopter *helicopter;
    BSPTree *tree;
    static float maxdist;
    static float startflying;

    HelicopterAttackState(LightHelicopter *tank);
    void handle(const phantom::PhantomTime &time);
};

#endif