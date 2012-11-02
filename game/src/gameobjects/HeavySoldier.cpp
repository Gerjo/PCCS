#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/pathfinding/Pathfinding.h>
#include <utils/Maths.h>
#include <phantom.h>
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

// TODO: refactor to something more global instead of a sneaky C-style function.
void to8Directions(stringstream &str, float rotation) {
    if(rotation > 337.5f || rotation < 22.5f)
        str << "2";
    else if(rotation > 22.5f && rotation < 67.5f)
        str << "1";
    else if(rotation > 67.5f && rotation < 112.5f)
        str << "8";
    else if(rotation > 112.5f && rotation < 157.5f)
        str << "7";
    else if(rotation > 157.5f && rotation < 202.5f)
        str << "6";
    else if(rotation > 202.5f && rotation < 247.5f)
        str << "5";
    else if(rotation > 247.5f && rotation < 292.5f)
        str << "4";
    else if(rotation > 157.5f && rotation < 337.5f)
        str << "3";
    else
        str << "1";
}

void HeavySoldier::paint() {
    getGraphics().clear().beginPath();

    if(_isSelected) {
        getGraphics().setFillStyle(Colors::RED);
    } else {
        getGraphics().setFillStyle(Colors::WHITE);
    }

    stringstream imageName;
    imageName << "images/unit exports/shadows/blanco soldier/soldier blanko ";
    float rotation = phantom::maths::directionToRotation(&_direction);
    to8Directions(imageName, rotation);
    imageName << " 70x70.png";

    stringstream imageName2;
    imageName2 << "images/unit exports/shadows/blanco soldier/soldier blanko ";
    to8Directions(imageName2, rotation);
    imageName2 << "-1 70x70.png";

    getGraphics().image(imageName.str(), -20, -20, 59, 58).fill();

    if(isMe()) {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::RED)
            .image(imageName2.str(), -20, -20, 59, 58).fill();
    }
    else {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLUE)
            .image(imageName2.str(), -20, -20, 59, 58).fill();
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

    _direction = location - _position;
    _direction.normalize();

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
