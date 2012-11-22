#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
#include "AIState.h"
#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

class LIBEXPORT ArtificialIntelligence : public phantom::Composite
{
public:
    enum STATE{
        STATEIDLE,
        STATEATTACKING,
        STATEDEFENDING,
        STATEFLEEING,
        STATECOUNT
    };

    STATE currentState;
    GameObject *parent;

    static vector<GameObject*> soldiers;
    AIState *states[4];

    ArtificialIntelligence(GameObject *parent, AIState *idle = nullptr, AIState *attack = nullptr, AIState *defending = nullptr, AIState *fleeing = nullptr);
    void setStates(AIState *idle, AIState *attack, AIState *defending, AIState *fleeing);
    void update(const phantom::Time& time);
    MessageState handleMessage(AbstractMessage* message);

private:
    void setActive(STATE state);
    void clearStates();
};

#endif