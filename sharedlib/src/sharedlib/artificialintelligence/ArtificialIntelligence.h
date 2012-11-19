#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
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

    ArtificialIntelligence() : currentState(STATEIDLE) {
        parent = dynamic_cast<GameObject*>(getParent());

        if(parent == nullptr) {
            Console::log("Cannot add an AI behaviour to a non-gameobject.");
            return;
        }
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

