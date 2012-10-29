#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/pathfinding/Pathfinding.h>

HeavySoldier::HeavySoldier() : _isSelected(false), _victim(0) {
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
    getGraphics().clear().beginPath();

    if(_isSelected) {
        getGraphics().setFillStyle(Colors::RED);
    } else {
        getGraphics().setFillStyle(Colors::WHITE);
    }

    getGraphics().image("images/unit exports/shadows/soldier 1.png", -10, -16, 20, 32).fill();

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

void HeavySoldier::attack(GameObject* victim) {
    cout << "attacking" << endl;
}

void HeavySoldier::walk(Vector3 location) {
    _victim = 0; // stop shooting. (can change this later on?)
    seekRoute(location);

    stringstream ss;

    if(_path.empty()) {
        ss << "Cannot find route to destination.";
    } else {
        ss << "Walking to location (" << _path.size() << " waypoints).";
    }

    cout << ss.str() << endl;

    Data data;
    data("to-x") = location.x;
    data("to-y") = location.y;
    data("x")    = _position.x;
    data("y")    = _position.y;

    Message<Data>* msg = new Message<Data>("Soldier-walk-to", data);

    // TODO: hide logic!
    getGame<Game*>()->network->sendNetworkMessage(this, msg);
}

void HeavySoldier::handleAi(void) {

}

void HeavySoldier::update(const Time& time) {
    LightSoldier::update(time);
   // cout << this->toString() << endl;

    mover->update(time);
}

bool HeavySoldier::seekRoute(Vector3 location) {
    Vector3 soldierPos       = getPosition();
    Pathfinding* pathfinding = static_cast<BSPTree*>(_layer)->pathfinding;

    _path.clear();
    deque<Space*> spaces = pathfinding->getPath(soldierPos, location);

    if(spaces.empty()) {
        return false;
    }

    _path.push_back(Vector3(location));

    // We pop the last element, walking to the mouse coords is more
    // sensible than walking to the waypoint. NB: '2' is intentional.
    const int endOffset = 2;

    for(int i = spaces.size() - endOffset; i >= 0; --i) {
        _path.push_back(Vector3(spaces[i]->getCenter()));
    }

    mover->moveTo(&_path);
    //setShowPath(true);

    return true;
}

MessageState HeavySoldier::handleMessage(AbstractMessage* message) {

    if(message->isType("Soldier-walk-to")) {
        Data data = message->getPayload<Data>();

        // Our amazing position integration:
        _position.x = data("x");
        _position.y = data("y");

        seekRoute(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;
    }

    return  LightSoldier::handleMessage(message);;
}

void HeavySoldier::fromData(Data& data) {
    LightSoldier::fromData(data);

    repaint();
}

void HeavySoldier::toData(Data& data) {
    LightSoldier::toData(data);
}
