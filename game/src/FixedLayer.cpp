#include "FixedLayer.h"

#include "Game.h"

#include "components/Console.h"

FixedLayer::FixedLayer() {

}

void FixedLayer::update(const float& elapsed) {
    Layer::update(elapsed);

    Game* game  = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    // translate this layer, too.
    setPosition(cam.getPosition());
}