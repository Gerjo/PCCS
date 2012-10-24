#ifndef BULLET_H
#define	BULLET_H

#include <phantom.h>
#include <sstream>

using namespace phantom;
#include "../../components/Console.h"
#include <sharedlib/gameobjects/GameObject.h>

class Bullet : public GameObject {
public:
    Bullet(Entity* owner);
    virtual ~Bullet();
    virtual void update(const float& elapsed);
    void setDirection(Vector3& direction);
    void onCollision(Composite* entity);

private:
    void draw();
    Vector3 _direction;
    Vector3 _velocity;
    double _creationTime;
    double _ttl;
};

#endif	/* BULLET_H */

