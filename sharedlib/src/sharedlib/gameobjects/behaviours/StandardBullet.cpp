#include "StandardBullet.h"

StandardBullet::StandardBullet(){
    _position = Vector3(0,0);
    _direction = Vector3(0,0);
    _velocity = Vector3(0,0);
    _creationTime = 0;
    _ttl = 4000000000000;
}

void StandardBullet::onCollision(Composite* entity){

}