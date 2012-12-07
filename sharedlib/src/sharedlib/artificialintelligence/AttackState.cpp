#include "AttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/EnemyMixin.h"
#include "../gameobjects/GameObject.h"
#include "../pathfinding/BSPTree.h"

AttackState::AttackState(GameObject *enemy, float attackRange) {
    this->enemyG        = enemy;
    this->enemyM        = dynamic_cast<EnemyMixin*>(enemy);
    this->tree          = nullptr;
    this->attackRange   = attackRange;
}

void AttackState::handle(const phantom::PhantomTime &time) {
    if(tree == nullptr) {
        tree = dynamic_cast<BSPTree*>(enemyG->getLayer());
    }

    const vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    
    for(GameObject *soldier : soldiers) {
        float length = (enemyG->getPosition() - soldier->getPosition()).getLengthSq();
        GameObject *victim = enemyM->getVictim();
        
        if(length < attackRange && tree->inlineOfSight(enemyG, soldier)) {
            if(victim == soldier || victim == nullptr) {     
                if(!enemyM->isAttacking()) {
                    enemyM->attack(soldier);
                }
            }
        }
        else {
            if(victim == soldier && enemyM->isAttacking() || victim == soldier && length > attackRange) {
                enemyM->stopShooting();
            }
        }
    }
}