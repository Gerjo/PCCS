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
        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
        .stroke()
        ;
}