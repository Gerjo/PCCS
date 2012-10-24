#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"

HeavySoldier::HeavySoldier() : _isSelected(false) {
    repaint();
}

HeavySoldier::~HeavySoldier() {

}

bool HeavySoldier::isSelected(void) {
    return _isSelected;
}

void HeavySoldier::onLayerChanged(Layer* layer) {
    LightSoldier::onLayerChanged(layer);
    if(_layer != 0) {
        // Ownership state may have changed. NB: The selector will automatically
        // ignore this soldier if it's already part of the selector.
        if(isMe()) {
            getGame<Game*>()->world->handleMessage(new Message<HeavySoldier*>("selector-register", this));
        }
    }
}

bool HeavySoldier::isMe(void) {
    const PlayerModel& model = getGame<Game*>()->me;
    return model.id == playerId;
}

void HeavySoldier::paint() {
    const string filename("images/gunner20x32.png");

    getGraphics().clear().beginPath();


    if(_isSelected) {
        getGraphics().setFillStyle(Colors::GREEN);
    } else {
        getGraphics().setFillStyle(Colors::WHITE);
    }

    getGraphics().rect(0, 0, _boundingBox.size.x, _boundingBox.size.y).fill();

    if(isMe()) {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            .rect(-8, -8, _boundingBox.size.x + 16, _boundingBox.size.x + 16, false)
            .stroke()
        ;
    }
}

void HeavySoldier::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {

}

void HeavySoldier::onSelect(void) {
    _isSelected = true;
    repaint();
}

void HeavySoldier::onDeselect(void) {
    _isSelected = false;
    repaint();
}

void HeavySoldier::attack(GameObject* victim) {
    cout << "attacking" << endl;
}
void HeavySoldier::walk(Vector3 location) {
    cout << "walking" << endl;
}

void HeavySoldier::fromData(Data& data) {
    LightSoldier::fromData(data);

    repaint();
}

void HeavySoldier::toData(Data& data) {
    LightSoldier::toData(data);
}
