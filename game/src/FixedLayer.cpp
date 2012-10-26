#include "FixedLayer.h"

#include "Game.h"

#include "components/Console.h"

FixedLayer::FixedLayer() : _camera(0) {

}

void FixedLayer::setCamera(Camera* camera) {
    _camera = camera;
}

void FixedLayer::update(const Time& time) {
    if(_camera != 0) {
        setPosition(_camera->getPosition());
    }
    
    // Updating here makes the camera so much more responsive!
    Layer::update(time);
}