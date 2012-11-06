#include "HeavyTank.h"
#include "../helper/ImageDirections.h"

#include <utils/Maths.h>

HeavyTank::HeavyTank() {
    repaint();
}

HeavyTank::~HeavyTank() {
}

void HeavyTank::paint() {
    std::stringstream imageName;
    imageName << "images/unit exports/shadows/Tank Bot 120x120 ";
    ImageDirections::to8Directions(imageName, phantom::maths::directionToRotation(&_directionTur));
    imageName << ".png";

    std::stringstream imageName2;
    imageName2 << "images/unit exports/shadows/Tank Tur 100x100 ";
    ImageDirections::to8Directions(imageName2, phantom::maths::directionToRotation(&_direction));
    imageName2 << ".png";

    getGraphics().clear().beginPath().setFillStyle(Colors::WHITE).image(imageName.str(), 0, 0, 120, 120).image(imageName2.str(), 10, 10, 100, 100).
        rect(0, 0, _boundingBox.size.x * (_health / _totalHealth), 5).
        fill().stroke();
}