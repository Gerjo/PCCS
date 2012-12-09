#include "MoveState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/GameObject.h"
#include "../gameobjects/EnemyMixin.h"
#include "../pathfinding/BSPTree.h"

MoveState::MoveState(GameObject *enemy, float detectionRange, float startDrivingDistance, bool hasLineOfSight) {
    this->enemyG                = enemy;
    this->enemyM                = dynamic_cast<EnemyMixin*>(enemy);
    this->detectionRange        = detectionRange;
    this->startDrivingDistance  = startDrivingDistance;
    this->hasLineOfSight        = hasLineOfSight;
    this->tree                  = nullptr;
}

void MoveState::handle(const phantom::PhantomTime &time) {
    if(tree == nullptr) {
        tree = dynamic_cast<BSPTree*>(enemyG->getLayer());
    }

    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : soldiers) {
        float distance = (enemyG->getPosition() - soldier->getPosition()).getLengthSq();
        if(distance < detectionRange && distance > startDrivingDistance)
            if(hasLineOfSight && tree->inlineOfSight(enemyG, soldier))
                enemyM->move(soldier->getPosition());
            else
                enemyM->move(soldier->getPosition());
    }
}