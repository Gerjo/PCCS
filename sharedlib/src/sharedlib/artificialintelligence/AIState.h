#ifndef AISTATE_H_
#define AISTATE_H_

#include <messaging/AbstractMessage.h>
#include "CompileConfig.h"

class LIBEXPORT AIState {
public:
    virtual void construct() = 0;
    virtual void handle(const phantom::Time& time) = 0;
    virtual void destruct() = 0;
};

#endif