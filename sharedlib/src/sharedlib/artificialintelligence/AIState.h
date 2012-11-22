#ifndef AISTATE_H_
#define AISTATE_H_

#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

class ArtificialIntelligence;

class LIBEXPORT AIState {
public:
    ArtificialIntelligence *ai;

    virtual void construct() = 0;
    virtual void handle(const phantom::Time& time) = 0;
    virtual void destruct() = 0;
};

#endif