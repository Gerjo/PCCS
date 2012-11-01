#include "HeavyBullet.h"

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
        .rect(0.0f, 0.0f, _boundingBox.size.x, _boundingBox.size.y)
        //.image("images/projectiles/bullet.png", 0, 0, 4, 14)
        .stroke()
        ;
}