#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>

class ArtificialIntelligence;

class LIBEXPORT AIState {
public:
    ArtificialIntelligence *ai;

    virtual void construct() { }
    virtual void handle(const phantom::PhantomTime& time) = 0;
    virtual void destruct() { }
};

#endif