#ifndef LIGHTTANK_H_
#define LIGHTTANK_H_

#include "../artificialintelligence/AIState.h"
#include "LightWeapon.h"
#include "GameObject.h"
#include "EnemyMixin.h"

class LIBEXPORT LightTank : public GameObject, public EnemyMixin {
public:
    LightTank();
    virtual ~LightTank();

    virtual void update(const phantom::PhantomTime& time);

    LightWeapon *weapon;
    virtual void onGameObjectDestroyed(GameObject* gameobject);

    virtual MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);
    void toData(Data& data);
    Pathfinding::Route seekRoute(Vector3 location);
    virtual void move(const Vector3& location);

private:
    AIState *moveState, *attackState;
};

#endif