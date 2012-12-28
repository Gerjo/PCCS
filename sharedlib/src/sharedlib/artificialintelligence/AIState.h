#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>
#include <phantom.h>

class ArtificialIntelligence;

using namespace phantom;

class LIBEXPORT AIState : public IHandleMessage {
public:
    ArtificialIntelligence* ai;
    bool isEnabled;

    AIState() : ai(nullptr), isEnabled(false) {

    }

    virtual void construct() {
        isEnabled = true;
    }


    virtual void destruct() {
        isEnabled = false;
    }

    virtual MessageState handleMessage(AbstractMessage* message) {
        return IGNORED;
    }

    virtual void handle(const phantom::PhantomTime& time) = 0;

private:
    GameObject* getOwner() {
        return ai->getOwner();
    }
};

#endif