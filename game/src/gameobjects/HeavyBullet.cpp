#include "HeavyBullet.h"
#include <utils/Maths.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const Time& time) {
    LightBullet::update(time);

    _bulletBehaviour->render(&getGraphics());
}