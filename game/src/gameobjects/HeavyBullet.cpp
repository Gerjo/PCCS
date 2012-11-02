#include "HeavyBullet.h"
#include <utils/maths.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const Time& time) {
    LightBullet::update(time);

    _bulletBehaviour->render(&getGraphics());
}