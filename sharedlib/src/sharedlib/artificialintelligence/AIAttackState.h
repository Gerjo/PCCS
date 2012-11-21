#ifndef AIATTACKSTATE_H_
#define AIATTACKSTATE_H_

#include "AIState.h"
#include "CompileConfig.h"
#include "../gameobjects/GameObject.h"

class LIBEXPORT AIAttackState : public AIState {
public:
    void construct();
    void handle(const phantom::Time &time);
    void destruct();
};

#endif