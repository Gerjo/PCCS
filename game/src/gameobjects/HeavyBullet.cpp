#include "HeavyBullet.h"
#include <utils/maths.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const Time& time) {
    LightBullet::update(time);

    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/projectiles/bullet.png", 0, 0, 4, 14)
        .rotate(phantom::maths::directionToRotation(&_direction) - 90.0f)
        .stroke()
        ;
}