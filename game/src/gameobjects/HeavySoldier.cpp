#include "HeavySoldier.h"

#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "../networking/Dedicated.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/pathfinding/Pathfinding.h>
#include <phantom.h>
#include "HeavyFactory.h"
#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"
#include "../guicomponents/HUD.h"

HeavySoldier::HeavySoldier() : _isSelected(false) {
    addComponent(new HealthBar());
    addComponent(new InertiaMover());

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
            Message<HeavySoldier*> mail("selector-register", this);
            getGame<Game*>()->world->handleMessage(&mail);
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
    ImageDirections::to8Directions(imageName, _direction.getAngleXOY());
    imageName << " 70x70.png";

    stringstream imageName2;
    imageName2 << "images/unit exports/shadows/blanco soldier/soldier blanko ";
    ImageDirections::to8Directions(imageName2, _direction.getAngleXOY());
    imageName2 << "-1 70x70.png";

    getGraphics()
        .beginPath()
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

    findAnsestor<ClientWorld>()->hud->displayActionBar(true);

    repaint();
}

void HeavySoldier::onDeselect(void) {
    _isSelected = false;

    findAnsestor<ClientWorld>()->hud->displayActionBar(false);

    repaint();
}

void HeavySoldier::update(const PhantomTime& time) {
    const Vector3& tmp = inertia->getDominantDirection();
    if(tmp != _direction) {
        _direction = tmp;
        repaint();
    }

    LightSoldier::update(time);
}

MessageState HeavySoldier::handleMessage(AbstractMessage* message) {

    if(message->isType("bullet-fired")) {
        LightBullet* bullet = message->getPayload<LightBullet*>();

        if(isMe()) {
            bullet->setAuthority(true);
        }

        return CONSUMED;
    }

    if(message->isType("victim-reset")) {
        //GameObject* oldVictim = message->getPayload<GameObject*>();

        if(isMe()) {
            Data data;
            auto networkMessage = new Message<Data>("victim-reset-sync", data);
            Services::broadcast(this, networkMessage);
        }

        return CONSUMED;
    }

    if(message->isType("victim-change")) {
        if(isMe()) {
            GameObject* newVictim = message->getPayload<GameObject*>();
            Data data;
            data("victim-uid")  = newVictim->UID_network;
            auto networkMessage = new Message<Data>("victim-change-sync", data);
            Services::broadcast(this, networkMessage);
        }

        return CONSUMED;
    }

    return LightSoldier::handleMessage(message);;
}

void HeavySoldier::fromData(Data& data) {
    LightSoldier::fromData(data);

    repaint();
}

void HeavySoldier::toData(Data& data) {
    LightSoldier::toData(data);
}

void HeavySoldier::setDirection(Vector3 direction) {
    repaint();

    _direction = direction;
}
