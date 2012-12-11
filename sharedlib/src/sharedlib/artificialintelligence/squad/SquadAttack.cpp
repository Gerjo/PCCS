#include "SquadAttack.h"
#include "../../gameobjects/LightWeapon.h"
#include "../ArtificialIntelligence.h"
#include "SquadFlock.h"
#include "SquadLeaderMove.h"
#include "SquadFlock.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../pathfinding/BSPTree.h"

SquadAttack::SquadAttack() : _victim(nullptr), _updateInterval(0.1) {

}

SquadAttack::~SquadAttack() {
    resetVictim();
}

void SquadAttack::resetVictim(void) {
    if(_victim != nullptr) {
        _victim->unregisterDestoryEvent(this);
        _victim = nullptr;
    }
}

void SquadAttack::setVictim(GameObject* gameobject) {
    resetVictim();
    _victim = gameobject;
    _victim->registerDestoryEvent(this);
}

void SquadAttack::construct() {
    AIState::construct();
}

void SquadAttack::handle(const phantom::PhantomTime& time) {
    if(_updateInterval.hasExpired(time)) {
        _updateInterval.restart();

        if(_victim != nullptr) {
            LightSoldier* attacker = ai->getOwner<LightSoldier*>();
            LightWeapon* weapon    = attacker->weapon;
            const bool inRange     = attacker->distanceToSq(_victim) < weapon->getRangeSq();
            WalkState* flockstate  = ai->getState<WalkState>();
            BSPTree* tree          = static_cast<BSPTree*>(ai->getLayer());
            bool inSight           = tree->inlineOfSight(attacker, _victim);

            if(inRange && inSight) {

                // Stop any movement
                if(flockstate->isEnabled) {
                    ai->setNonActive<WalkState>();
                    cout << "In range, stopped walking. Start shooting." << endl;
                }

                // The server shall not shoot bullets.
                if(attacker->residence == GameObject::CLIENT) {
                    // Fire bullets!
                    if(weapon->isCooldownExpired()) {
                        Vector3 direction   = attacker->directionTo(_victim);
                        LightBullet* bullet = weapon->createBullet();
                        bullet->owner = attacker;
                        bullet->setDirection(direction);
                        bullet->setPosition(attacker->getBoundingBox().getCenter());
                        bullet->killList(attacker->getKillList());

                        ai->getLayer()->addComponent(bullet);

                        // Perhaps the owner wants to do something with the bullet
                        // EG: sync it over network, or set the authority flag.
                        Message<LightBullet*> message("bullet-fired", bullet);
                        ai->getParent()->handleMessage(&message);
                    }
                }
            } else {
                if(!flockstate->isEnabled) {
                    // TODO: enable that walking state.
                }
            }
        }
    }
}

MessageState SquadAttack::handleMessage(AbstractMessage* message) {
    if(message->isType("gameobject-destroyed")) {
        GameObject* victim = message->getPayload<GameObject*>();
        if(_victim == victim) {
            if(!isEnabled) {
                cout << "SquadAttack::handleMessage(): Good effort! Victim died without me attacking!" << endl;
            } else {
                cout << "SquadAttack::handleMessage(): Target down." << endl;
            }

            resetVictim();

            return HANDLED;
        }
    }

    return AIState::handleMessage(message);
}

void SquadAttack::destruct() {
    AIState::destruct();
    resetVictim();
}