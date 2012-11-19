#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
#include "AIState.h"
#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

class LIBEXPORT ArtificialIntelligence : public phantom::Entity
{
public:
    enum STATE{
        STATEIDLE,
        STATEATTACKING,
        STATEDEFENDING,
        STATEFLEEING
    };

    STATE currentState;
    GameObject *parent;

    vector<AIState*> states;

    ArtificialIntelligence(AIState *idle = nullptr, AIState *attack = nullptr, AIState *defending = nullptr, AIState *fleeing = nullptr) : currentState(STATEIDLE), states(4) {
        parent = dynamic_cast<GameObject*>(getParent());

        if(parent == nullptr) {
            Console::log("Cannot add an AI behaviour to a non-gameobject.");
            return;
        }

        setStates(idle, attack, defending, fleeing);
    }

    void clearStates() {
        for(AIState *state : states) {
            delete state;
        }
        states.clear();
    }

    void setStates(AIState *idle, AIState *attack, AIState *defending, AIState *fleeing) {
        clearStates();
        states.push_back(idle);
        states.push_back(attack);
        states.push_back(defending);
        states.push_back(fleeing);
    }

    void setActive(STATE state) {
        currentState = state;
        states[state]->handling();
    }

    void update(const phantom::Time& time) {
        Composite::update(time);

        // Do some awesome in range detection and add statehandling for it.
    }

    MessageState handleMessage(AbstractMessage* message) {
        return Entity::handleMessage(message);
    }
};

#endif

