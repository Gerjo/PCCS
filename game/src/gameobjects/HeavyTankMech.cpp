#include "HeavyTankMech.h"
#include "HeavyBullet.h"
#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"
#include <sharedlib/services/Services.h>

#include <utils/Maths.h>

HeavyTankMech::HeavyTankMech() {
    repaint();
    _canHover = true;
    addComponent(new HealthBar());
}

HeavyTankMech::~HeavyTankMech() {
}

void HeavyTankMech::update(const phantom::PhantomTime &time) {
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

void HeavyTankMech::paint() {
    std::stringstream tankBody;
    tankBody << "images/unit exports/shadows/blanco mech tank/mech_tank_150x150_";
    ImageDirections::to8Directions(tankBody, phantom::maths::directionToRotation(&_directionTur));
    tankBody << ".png";

    std::stringstream tankTurretShadow;
    tankTurretShadow << "images/unit exports/shadows/blanco mech tank/mech_tank_tur_150x150_";
    ImageDirections::to8Directions(tankTurretShadow, phantom::maths::directionToRotation(&_direction));
    tankTurretShadow << "_shadow.png";

    std::stringstream tankTurret;
    tankTurret << "images/unit exports/shadows/blanco mech tank/mech_tank_tur_150x150_";
    ImageDirections::to8Directions(tankTurret, phantom::maths::directionToRotation(&_direction));
    tankTurret << ".png";

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
}

void HeavyTankMech::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    getGame<Game*>()->cursor->currentCursor = Cursor::CURATTACK;
    getGame<Game*>()->cursor->redraw();
}

void HeavyTankMech::attack(GameObject *victim) {
    LightTankMech::attack(victim);
}

void HeavyTankMech::move(const Vector3& location) {
    LightTankMech::move(location);
    paint();
}

void HeavyTankMech::fromData(Data& data) {
    LightTankMech::fromData(data);

    repaint();
}

void HeavyTankMech::toData(Data& data) {
}