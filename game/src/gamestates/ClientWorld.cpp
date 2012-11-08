#include "ClientWorld.h"
#include "../Game.h"
#include "../components/ScrollBehaviour.h"
#include "../components/Selector.h"
#include "../components/Cursor.h"
#include "../guicomponents/HUD.h"
#include "../networking/Network.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/SharedSettings.h>

ClientWorld::ClientWorld(){
    setType("ClientWorld");

    fixedlayer  = new Layer();
    gameobjects = new BSPTree(SharedSettings::BSP_WIDTH(), SharedSettings::BSP_HEIGHT(), SharedSettings::BSP_SMALLESTSIZE(), SharedSettings::BSP_MAXCOLLISIONSPERSPACE());
    cursor      = new Cursor();
    selector    = new Selector();
    console     = new Console();
    hud         = new HUD();
    vector<Camera*> cams = *getDriver()->getActiveCameras();
    for(Camera *camera : cams) {
        getDriver()->disableCamera(camera);
    }

    camera = getDriver()->createCamera();
    getDriver()->enableCamera(camera);
    camera->addComponent(console);
    camera->addComponent(hud);
    addComponent(gameobjects);
    addComponent(fixedlayer);
    addComponent(selector);

    // Dependency injection :(
    selector->setTrackingLayer(gameobjects);
    selector->setCamera(camera); // For "screen to world" coordinates.
    fixedlayer->addComponent(camera);
    camera->addComponent(cursor);
}

ClientWorld::~ClientWorld() {

}

void ClientWorld::start(void) {
    ScrollBehaviour *scrollbehaviour = new ScrollBehaviour();
    scrollbehaviour->setScrollableObject(camera);
    camera->addComponent(scrollbehaviour);
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


