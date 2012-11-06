#ifndef LIGHTBULLET_H
#define	LIGHTBULLET_H

#include <phantom.h>
#include "GameObject.h"
#include "LightSoldier.h"
#include "behaviours/BulletBehaviour.h"
#include "../CompileConfig.h"

using namespace phantom;

class LightSoldier;

class LIBEXPORT LightBullet : public GameObject {
public:
    LightBullet();
    virtual ~LightBullet();
    void setBehaviour(BulletBehaviour* newBehaviour);

    virtual void onCollision(Composite* entity);
    virtual void update(const Time& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    void setDirection(Vector3& direction);

    LightSoldier* owner;
protected:
    BulletBehaviour* _bulletBehaviour;
    Vector3 _direction;
    Vector3 _velocity;
    double _creationTime;
    double _ttl;
    float _damage;
};

#endif	/* LIGHTBULLET_H */
