#ifndef LIGHTTANK_H_
#define LIGHTTANK_H_

#include "../artificialintelligence/AIState.h"
#include "LightWeapon.h"
#include <sharedlib/gameobjects/GameObject.h>

class LIBEXPORT LightTank : public GameObject {
public:
    LightTank();
    virtual ~LightTank();

    bool isAttacking;
    LightWeapon *weapon;

    virtual void attack(GameObject* victim);
    virtual void shootAt(UID::Type uid);
    virtual MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);
    void toData(Data& data);
protected:
    GameObject *_victim;
private:
    AIState *idleState, *attackState;
};

#endif