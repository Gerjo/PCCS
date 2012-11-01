#ifndef BULLETBEHAVIOUR_H
#define BULLETBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>

using namespace phantom;

class LIBEXPORT BulletBehaviour{
public:
    virtual void onCollision(Composite* entity) = 0;
    virtual void update(const Time& time){
        
    }

    virtual Vector3 setDirection(Vector3& direction){
        _direction = direction;
        return _direction;
    }

protected:
    Vector3 _position;
    Vector3 _direction;
    Vector3 _velocity;
    double _creationTime;
    double _ttl;
};


#endif /* BULLETBEHAVIOUR_H */