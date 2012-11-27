#include "HeavyHelicopter.h"
#include "../helper/ImageDirections.h"
#include "../Game.h"
#include <utils/Maths.h>

HeavyHelicopter::HeavyHelicopter() {
    _rotorblade = 1;

    paint();
}

HeavyHelicopter::~HeavyHelicopter() {
}

void HeavyHelicopter::attack(GameObject *victim) {

}

void HeavyHelicopter::update(const phantom::PhantomTime &time) {
    LightHelicopter::update(time);

    paint();

    Vector3 mouse = getDriver()->getActiveCameras()->front()->getWorldCoordinates(
            getDriver()->getInput()->getMouseState()->getPosition()
    );

    // Demo demonstrating line of sight:
    BSPTree* bsptree = static_cast<BSPTree*>(_layer);
    if(bsptree->inlineOfSight(this, mouse)) {
        getGraphics().beginPath().setFillStyle(Colors::WHITE).rect(0, 0, _boundingBox.size.x, _boundingBox.size.y, false).stroke();
    }
}

void HeavyHelicopter::paint() {
    stringstream s;
    s << _rotorblade;

    stringstream t;
    ImageDirections::to8Directions(t, phantom::maths::directionToRotation(&_direction));

    getGraphics().clear().beginPath().setFillStyle(Colors::WHITE).
        image("images/unit exports/shadows/blanco hellcopter/hellcopter_" + t.str() + "_225x230_shadow.png", 0, 0, 225, 230).fill().
        setFillStyle(Colors::RED).
        image("images/unit exports/shadows/blanco hellcopter/hellcopter_" + t.str() + "_225x230.png", 0, 0, 225, 230).fill().
        setFillStyle(Colors::WHITE).
        image("images/unit exports/shadows/blanco hellcopter/hellcoptertur_" + s.str() + "_225x230_shadow.png", 0, 0, 225, 230).fill().
        image("images/unit exports/shadows/blanco hellcopter/hellcoptertur_" + s.str() + "_225x230.png", 0, 0, 225, 230).fill();

    _rotorblade = (_rotorblade == 1) ? 2 : 1;
}

void HeavyHelicopter::fly(Vector3 location) {
    LightHelicopter::fly(location);
}

void HeavyHelicopter::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    getGame<Game*>()->cursor->currentCursor = Cursor::CURATTACK;
    getGame<Game*>()->cursor->redraw();
}