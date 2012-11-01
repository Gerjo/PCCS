#include "ClientWorld.h"
#include "../Game.h"
#include "../components/ScrollBehaviour.h"
#include "../components/Selector.h"
#include "../FixedLayer.h"
#include "../components/Cursor.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/SharedSettings.h>

ClientWorld::ClientWorld() {
    setType("ClientWorld");


    fixedlayer  = new FixedLayer();
    gameobjects = new BSPTree(SharedSettings::BSP_WIDTH(), SharedSettings::BSP_HEIGHT(), SharedSettings::BSP_SMALLESTSIZE(), SharedSettings::BSP_MAXCOLLISIONSPERSPACE());
    
    cursor      = new Cursor();
    selector    = new Selector();

    camera      = getDriver()->createCamera();
    camera->addComponent(new ScrollBehaviour());
    getDriver()->setActiveCamera(camera);

    addComponent(gameobjects);
    addComponent(fixedlayer);
    addComponent(selector);

    // Dependency injection :(
    selector->setTrackingLayer(gameobjects);
    selector->setCamera(camera); // For "screen to world" coordinates.
    fixedlayer->addComponent(camera);
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

            NetworkRegistry::add(gameObject);
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

            NetworkRegistry::add(gameObject);
        });
    }

    _commands.add([this] (void) {
        getGame<Game*>()->startPlaying();
    });
}

void ClientWorld::update(const Time& time) {
    GameState::update(time);

    _commands.run();
}


