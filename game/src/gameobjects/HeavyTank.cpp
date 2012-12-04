#include "HeavyTank.h"
#include "HeavyBullet.h"
#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"
#include <sharedlib/services/Services.h>

#include <utils/Maths.h>

HeavyTank::HeavyTank() {
    repaint();
    _canHover = true;
    addComponent(new HealthBar());
}

HeavyTank::~HeavyTank() {
}

void HeavyTank::update(const phantom::PhantomTime &time) {
    GameObject::update(time);
    if(_victim != nullptr && weapon->isCooldownExpired()) {
        Vector3 direction   = directionTo(_victim);
        LightBullet* bullet = weapon->createBullet();
        bullet->setDirection(direction);
        bullet->setPosition(this->getBoundingBox().getCenter());
        bullet->owner = this;
        dynamic_cast<HeavyBullet*>(bullet)->killList(_killList);

        _layer->addComponent(bullet);
    }
}

void HeavyTank::paint() {
    std::stringstream tankBodyShadow;
    tankBodyShadow << "images/unit exports/shadows/Tank Bot 120x120 ";
    ImageDirections::to8Directions(tankBodyShadow, phantom::maths::directionToRotation(&_directionTur));
    tankBodyShadow << " shadow.png";

    std::stringstream tankBody;
    tankBody << "images/unit exports/shadows/Tank Bot 120x120 ";
    ImageDirections::to8Directions(tankBody, phantom::maths::directionToRotation(&_directionTur));
    tankBody << ".png";

    std::stringstream tankTurretShadow;
    tankTurretShadow << "images/unit exports/shadows/Tank Tur 100x100 ";
    ImageDirections::to8Directions(tankTurretShadow, phantom::maths::directionToRotation(&_direction));
    tankTurretShadow << " shadow.png";

    std::stringstream tankTurret;
    tankTurret << "images/unit exports/shadows/Tank Tur 100x100 ";
    ImageDirections::to8Directions(tankTurret, phantom::maths::directionToRotation(&_direction));
    tankTurret << ".png";

    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image(tankBodyShadow.str(), 0, 0, 120, 120)
        .fill()
        .stroke();

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::CORNFLOWER)
        .image(tankBody.str(), 0, 0, 120, 120)
        .fill()
        .stroke();

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image(tankTurretShadow.str(), 10, 10, 100, 100)
        .fill()
        .stroke();

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::CORNFLOWER)
        .image(tankTurret.str(), 10, 10, 100, 100)
        .fill()
        .stroke();

    //getGraphics()
    //        .beginPath()
    //        .setFillStyle(Colors::CORNFLOWER)
    //        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
    //        .fill()
    //        .stroke();
}

void HeavyTank::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    getGame<Game*>()->cursor->currentCursor = Cursor::CURATTACK;
    getGame<Game*>()->cursor->redraw();
}

void HeavyTank::attack(GameObject *victim) {
    LightTank::attack(victim);
}

void HeavyTank::drive(Vector3 location) {
    LightTank::drive(location);

    paint();
}

void HeavyTank::fromData(Data& data) {
    LightTank::fromData(data);

    repaint();
}

void HeavyTank::toData(Data& data) {
}