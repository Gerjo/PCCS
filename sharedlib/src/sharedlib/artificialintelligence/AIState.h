#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>
#include <phantom.h>

class ArtificialIntelligence;

using namespace phantom;

class LIBEXPORT AIState {
public:
    ArtificialIntelligence *ai;
    bool isEnabled;

    AIState() : isEnabled(false) { }

    virtual void construct() { isEnabled = true; }
    virtual void handle(const phantom::PhantomTime& time) = 0;
    virtual void destruct() { isEnabled = false; }
    virtual MessageState handleMessage(AbstractMessage* message) { return IGNORED; }
};

#endif