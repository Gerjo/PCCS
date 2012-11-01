#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/pathfinding/Pathfinding.h>
#include "HeavyFactory.h"

HeavySoldier::HeavySoldier() : _isSelected(false) {
    repaint();
}

HeavySoldier::~HeavySoldier() {

}


void HeavySoldier::onBulletFired(LightBullet* bullet) {
    getGame<Game*>()->network->introduceGameObject(bullet);
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
    getGraphics().clear().beginPath();

    if(_isSelected) {
        getGraphics().setFillStyle(Colors::RED);
    } else {
        getGraphics().setFillStyle(Colors::WHITE);
    }

    getGraphics().rect(0, 0, _boundingBox.size.x, _boundingBox.size.y).fill();
    //getGraphics().image("images/unit exports/shadows/soldier 1 53x53.png", -20, -20, 59, 58).fill();

    if(isMe()) {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            //rect(-8, -8, _boundingBox.size.x + 16, _boundingBox.size.x + 16, false)
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

void HeavySoldier::update(const Time& time) {
    LightSoldier::update(time);
}

MessageState HeavySoldier::handleMessage(AbstractMessage* message) {
    return  LightSoldier::handleMessage(message);;
}

void HeavySoldier::walk(Vector3 location) {
    LightSoldier::walk(location);

    Data data;
    data("to-x") = location.x;
    data("to-y") = location.y;
    data("x")    = _position.x;
    data("y")    = _position.y;

    Message<Data>* msg = new Message<Data>("Soldier-walk-to", data);

    // TODO: hide logic?
    getGame<Game*>()->network->sendNetworkMessage(this, msg);
}

void HeavySoldier::fromData(Data& data) {
    LightSoldier::fromData(data);

    repaint();
}

void HeavySoldier::toData(Data& data) {
    LightSoldier::toData(data);
}
