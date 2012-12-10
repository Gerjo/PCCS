#include "HeavyObstacle.h"
#include "../guicomponents/HealthBar.h"
#include "../helper/ImageDirections.h"

HeavyObstacle::HeavyObstacle(float rotation) {
    if(rotation > 135) {
        rotation = rotation - 135;
    }
    stringstream id;
    ImageDirections::to8Directions(id, rotation);
    this->imageChar = id.str();

    repaint();
}

HeavyObstacle::~HeavyObstacle() {

}

void HeavyObstacle::paint(void) {
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/unit exports/shadows/blanco obstacle/obst_" + this->imageChar + "_100x102.png", -10, -10, 106, 100)
        .fill()
        .stroke()
        ;
}