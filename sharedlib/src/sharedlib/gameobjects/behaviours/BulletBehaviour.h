#ifndef BULLETBEHAVIOUR_H
#define BULLETBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>
#include "AbstractBehaviour.h"

using namespace phantom;

class LIBEXPORT BulletBehaviour: public AbstractBehaviour {
public:
    virtual void onCollision(Composite* entity, CollisionData& collisionData) {}
    virtual void update(const PhantomTime& time){

    }

    virtual Vector3 setDirection(Vector3& direction){
        _direction = direction;
        return _direction;
    }
    virtual void render(Graphics* g) = 0;

protected:
    Vector3 _position;
    Vector3 _direction;
    Vector3 _velocity;
    double _creationTime;
    double _ttl;

    virtual void setType(){}
};


#endif /* BULLETBEHAVIOUR_H */