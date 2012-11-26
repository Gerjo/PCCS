#ifndef LIGHTHELICOPTER_H_
#define LIGHTHELICOPTER_H_

#include "../artificialintelligence/AIState.h"
#include "GameObject.h"

class LightHelicopter : public GameObject
{
public:
    LightHelicopter();
    ~LightHelicopter();

    LightWeapon *weapon;

    virtual void attack(GameObject *victim);
    virtual void stopShooting();
    virtual void fly(Vector3 location);
    MessageState handleMessage(AbstractMessage *message);

protected:
    GameObject *_victim;
private:
    AIState *_idleState, *_attackState;
    deque<Vector3> _path;
};

#endif