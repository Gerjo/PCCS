#include "HeavySoldier.h"

HeavySoldier::HeavySoldier() {
    repaint();
}

HeavySoldier::~HeavySoldier() {

}

void HeavySoldier::paint() {
    const string filename("images/gunner20x32.png");

    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
        .image(filename, -10, -16, 20, 32)
        .fill()
    ;
}

void HeavySoldier::fromData(Data& data) {
    LightSoldier::fromData(data);

    // Inform the selector that this soldier is controlled by this player.
    //if(data("isPlayer") == 1) {
    //    _layer->handleMessage(new Message<HeavySoldier*>("selector-register", this));
    //}
}

void HeavySoldier::toData(Data& data) {
    LightSoldier::toData(data);

}