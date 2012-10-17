#ifndef BULLET_H
#define	BULLET_H

#include <phantom.h>

using namespace phantom;

class Bullet : public Entity {
public:
    Bullet(Entity* owner);
    virtual ~Bullet();
    virtual void update(const float& elapsed);
    void setDirection(Vector3& direction);
private:
    void draw();
    Vector3 _direction;
    Vector3 _velocity;
};

#endif	/* BULLET_H */

