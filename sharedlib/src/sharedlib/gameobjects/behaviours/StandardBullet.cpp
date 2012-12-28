#include "StandardBullet.h"
#include <utils/Maths.h>
StandardBullet::StandardBullet(){
    _position = Vector3(0,0);
    _velocity = Vector3(0,0);
    _creationTime = 0;
    _ttl = 1;
    _typeName = "StandardBullet";
}

void StandardBullet::onCollision(Composite* entity){

}
void StandardBullet::render(Graphics* graphics){
    (*graphics)
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/projectiles/bullet.png", 0, 0, 4, 14)
        .rotate(_direction.getAngleXOY() - 90.0f)
        .stroke()
        ;
}