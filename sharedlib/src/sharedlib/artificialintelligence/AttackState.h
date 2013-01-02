#ifndef TANKATTACKSTATE_H_
#define TANKATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class GameObject;
class EnemyMixin;
class BSPTree;

class LIBEXPORT AttackState : public AIState {
public:
    AttackState(GameObject *enemyG, float attackRange);
    void update(const phantom::PhantomTime &time);

private:
    GameObject *enemyG;
    EnemyMixin *enemyM;
    BSPTree *tree;
    float attackRange;
};

#endif