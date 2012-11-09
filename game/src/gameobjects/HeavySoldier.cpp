#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/pathfinding/Pathfinding.h>
#include <utils/Maths.h>
#include <phantom.h>
#include "HeavyFactory.h"
#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"

HeavySoldier::HeavySoldier() : _isSelected(false) {
    repaint();
    addComponent(new HealthBar());
}

HeavySoldier::~HeavySoldier() {

}


void HeavySoldier::onBulletFired(LightBullet* bullet) {
    // this bullet can deal damage, it's not some dumb animation
    // only instance.
    if(isMe()) {
        bullet->setAuthority(true);
    }

    //getGame<Game*>()->network->introduceGameObject(bullet);
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

    stringstream imageName;
    imageName << "images/unit exports/shadows/blanco soldier/soldier blanko ";
    float rotation = phantom::maths::directionToRotation(&_direction);
    ImageDirections::to8Directions(imageName, rotation);
    imageName << " 70x70.png";

    stringstream imageName2;
    imageName2 << "images/unit exports/shadows/blanco soldier/soldier blanko ";
    ImageDirections::to8Directions(imageName2, rotation);
    imageName2 << "-1 70x70.png";

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image(imageName.str(), 0, 0, 70, 70).fill();

    if(isMe()) {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::RED)
            .image(imageName2.str(), 0, 0, 70, 70).fill();
    }
    else {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLUE)
            .image(imageName2.str(), 0, 0, 70, 70).fill();
    }
    getGraphics()
        .beginPath()
            .setFillStyle(Color(128, 128, 128, 20))
        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y, false)
        .fill();
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
    handleAi();
}

MessageState HeavySoldier::handleMessage(AbstractMessage* message) {
    return LightSoldier::handleMessage(message);;
}

void HeavySoldier::attack(GameObject* victim) {
    LightSoldier::attack(victim);

    Data data;
    data("victim") = victim->UID_network;

    Message<Data>* msg = new Message<Data>("Soldier-shoot-start", data);
    getGame<Game*>()->network->sendNetworkMessage(this, msg);

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

    paint();

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

void HeavySoldier::handleAi() {
    if(_victim != nullptr) {
        float distanceSq = distanceToSq(_victim);

        if(distanceSq < weapon->getRangeSq()) {
            if(!mover->isStopped()) {
                mover->stop();
                //cout << "*In range, Commence shooting!*";
            }

            if(weapon->isCooldownExpired()) {
                //cout << "Bullet spawned in layer: " << _layer->getType() << endl;
                Vector3 direction   = directionTo(_victim);
                LightBullet* bullet = weapon->createBullet();
                bullet->setDirection(direction);
                bullet->setPosition(this->getBoundingBox().getCenter());
                bullet->owner = this;

                onBulletFired(bullet);
                _layer->addComponent(bullet);
            }
        }
    }
}