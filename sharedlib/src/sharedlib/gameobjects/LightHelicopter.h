#ifndef LIGHTHELICOPTER_H_
#define LIGHTHELICOPTER_H_

#include "../artificialintelligence/AIState.h"
#include "LightWeapon.h"
#include "GameObject.h"

class LIBEXPORT LightHelicopter : public GameObject, public EnemyMixin
{
public:
    LightHelicopter();
    ~LightHelicopter();

    LightWeapon *weapon;

    virtual void fly(Vector3 location);
    MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);
    void toData(Data& data);

protected:
    GameObject *_victim;
private:
    AIState *_idleState, *_attackState;
    deque<Vector3> _path;
};

#endif