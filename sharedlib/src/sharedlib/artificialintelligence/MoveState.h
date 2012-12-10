#ifndef MOVESTATE_H_
#define MOVESTATE_H_

#include "AIState.h"
#include "CompileConfig.h"

class GameObject;
class EnemyMixin;
class BSPTree;

class MoveState : public AIState {
public:
    MoveState(GameObject* enemyG, float detectionRange, float startDrivingDistance, bool hasLineOfSight);
    void handle(const phantom::PhantomTime &time);

private:
    GameObject *enemyG;
    EnemyMixin *enemyM;
    BSPTree *tree;
    float detectionRange;
    float startDrivingDistance;
    bool hasLineOfSight;
};

#endif