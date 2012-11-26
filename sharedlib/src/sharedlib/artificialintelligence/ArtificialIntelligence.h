#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
#include "AIState.h"
#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

#include "TankAttackState.h"
#include "TankIdleState.h"

class LIBEXPORT ArtificialIntelligence : public phantom::Composite
{
public:
    AIState *currentState;
    GameObject *parent;

    static vector<GameObject*> soldiers;
    vector<AIState*> states;

    ArtificialIntelligence(GameObject *parent);
    void insertState(AIState *state);
    void update(const phantom::PhantomTime& time);
    MessageState handleMessage(AbstractMessage* message);

    template<class T> bool setActive() {
        T *state = nullptr;
        for(AIState *it : states) {
            state = dynamic_cast<T*>(it);
            if(state != nullptr)
                break;
        }
        if(state == nullptr)
            return false;

        if(currentState != nullptr)
            currentState->destruct();
        currentState = state;
        currentState->construct();

        return true;
    }
};

#endif