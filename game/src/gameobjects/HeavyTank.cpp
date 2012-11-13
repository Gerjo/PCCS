#include "HeavyTank.h"
#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"

#include <utils/Maths.h>

HeavyTank::HeavyTank() {
    repaint();
    addComponent(new HealthBar());
}

HeavyTank::~HeavyTank() {
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