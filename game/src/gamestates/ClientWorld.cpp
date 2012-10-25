#include "ClientWorld.h"
#include "../Game.h"
#include "../components/RtsCamera.h"
#include "../components/Selector.h"
#include "../FixedLayer.h"
#include "../components/Cursor.h"
#include <sharedlib/pathfinding/BSPTree.h>


ClientWorld::ClientWorld() {
    setType("ClientWorld");


    fixedlayer  = new FixedLayer();
    gameobjects = new BSPTree(2000, 2000, 20, 50);
    cursor      = new Cursor();
    rtsCamera   = new RtsCamera();
    camera      = rtsCamera->getPhantomCamera();
    selector    = new Selector();


    addComponent(gameobjects);
    addComponent(fixedlayer);
    addComponent(selector);

    // Dependency injection :(
    selector->setTrackingLayer(gameobjects);
    selector->setCamera(camera); // For "screen to world" coordinates.
    fixedlayer->addComponent(rtsCamera);
    fixedlayer->setCamera(camera);
    fixedlayer->addComponent(cursor);
}

ClientWorld::~ClientWorld() {

}

void ClientWorld::init(void) {

}

// Kind of copy pasted from the method below. Will refactor once the full
// requirements are know for this routine. -- Gerjo
void ClientWorld::push(string json) {
    Data data = Data::fromJson(json);

    for(Data::KeyValue pair : data("dynamic")) {
        Data& description = pair.second;

        _commands.add([this, description] () mutable -> void {
            GameObject* gameObject = HeavyFactory::create(description("type"));
            gameObject->fromData(description);

            gameobjects->addComponent(gameObject);
        });
    }
}

// Only Called the first time:
void ClientWorld::load(string json) {
    Data data = Data::fromJson(json);

    for(Data::KeyValue pair : data("static")) {
        Data& description = pair.second;

        _commands.add([this, description] () mutable -> void {
            GameObject* gameObject = HeavyFactory::create(description("type"));
            gameObject->fromData(description);

            gameobjects->addComponent(gameObject);
        });
    }

    _commands.add([this] (void) {
        getGame<Game*>()->startPlaying();
    });
}

void ClientWorld::update(const float& elapsed) {
    GameState::update(elapsed);

    _commands.run();
}


