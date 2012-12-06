#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>

class ArtificialIntelligence;

class LIBEXPORT AIState {
public:
    ArtificialIntelligence *ai;
    bool isEnabled;

    AIState() : isEnabled(false) { }

    virtual void construct() { isEnabled = true; }
    virtual void handle(const phantom::PhantomTime& time) = 0;
    virtual void destruct() { isEnabled = false; }
};

#endif