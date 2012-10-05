#include "FixedLayer.h"

#include "Game.h"

FixedLayer::FixedLayer() //:
   // _rtsCamera(static_cast<Game*>(getGame())->getRtsCamera())
{

}

void FixedLayer::update(const float& elapsed) {
    Layer::update(elapsed);
    cout << "teehee 1"  << endl;

Game* game  = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    // translate this layer, too.
    setPosition(cam.getPosition());

    cout << "teehee 2"  << endl;
}