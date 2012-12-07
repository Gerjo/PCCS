#ifndef TANKATTACKSTATE_H_
#define TANKATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class GameObject;
class EnemyMixin;
class BSPTree;

class LIBEXPORT AttackState : public AIState {
public:
    GameObject *enemyG;
    EnemyMixin *enemyM;
    BSPTree *tree;
    float attackRange;

    AttackState(GameObject *enemyG, float attackRange);
    void handle(const phantom::PhantomTime &time);
};

#endif