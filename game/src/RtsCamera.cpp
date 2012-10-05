#include "RtsCamera.h"

RtsCamera::RtsCamera() {
    _phantomCamera = getDriver()->createCamera();

    addComponent(_phantomCamera);
}

void RtsCamera::update(const float& elapsed) {

}
