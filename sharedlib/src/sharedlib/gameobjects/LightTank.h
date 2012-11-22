#ifndef LIGHTTANK_H_
#define LIGHTTANK_H_

#include "../artificialintelligence/AIState.h"
#include <sharedlib/gameobjects/GameObject.h>

class LIBEXPORT LightTank : public GameObject {
public:
    LightTank();
    virtual ~LightTank();

    bool isAttacking;

    virtual void attack(GameObject* victim);
    virtual void shootAt(UID::Type uid);
    virtual MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);

private:
    GameObject *_victim;
    AIState *idleState, *attackState;
};

#endif