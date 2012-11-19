#ifndef AISTATE_H_
#define AISTATE_H_

#include <messaging/AbstractMessage.h>
#include "CompileConfig.h"

class LIBEXPORT AIState {
public:
    virtual void handling() = 0;
};

#endif