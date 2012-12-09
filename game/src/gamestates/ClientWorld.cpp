#include "ClientWorld.h"
#include "../Game.h"
#include "../components/ScrollBehaviour.h"
#include "../components/Selector.h"
#include "../components/Cursor.h"
#include "../guicomponents/HUD.h"
#include "../networking/Dedicated.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include <input/KeyboardListener.h>
#include <sharedlib/missions/ObjDestroy.h>
#include <sharedlib/services/Services.h>
#include "../components/UsageGraph.h"

ClientWorld::ClientWorld(){
    setType("ClientWorld");
    phantom::Console::log("Initializing ClientWorld...");

    fixedlayer  = new Layer();
    gameobjects = new BSPTree(Services::settings()->bsp_width, Services::settings()->bsp_height, Services::settings()->bsp_smallestsize, Services::settings()->bsp_maxcollisionperspace);
    selector    = new Selector();
    hud         = new HUD();

    vector<Camera*> cams = *getDriver()->getActiveCameras();
    for(Camera *camera : cams) {
        getDriver()->disableCamera(camera);
    }
    mission = new Mission("first");
    obj = new ObjDestroy("kill tank!");
    gameobjects->addComponent(mission);
    camera = getDriver()->createCamera();
    getDriver()->enableCamera(camera);
    camera->addComponent(hud);
    addComponent(gameobjects);
    addComponent(fixedlayer);
    addComponent(selector);

    // Dependency injection :(
    selector->setTrackingLayer(gameobjects);
    selector->setCamera(camera); // For "screen to world" coordinates.
    fixedlayer->addComponent(camera);

    phantom::Console::log("Initialization complete.");
    //gameobjects->enableDebug();

    camera->addComponent(new UsageGraph());
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
            if(this->obj->getComposites()->size() <= 0){
                if(gameObject->getType() == "Tank"){
                    this->obj->addObject(gameObject);
                }
            }

            gameobjects->addComponent(gameObject);

            NetworkRegistry::add(gameObject);
        });
    }
    _commands.add([this] (){
        this->mission->addObjective(this->obj);
    });

    _commands.add([this] (void) {
        getGame<Game*>()->startPlaying();
    });
}

void ClientWorld::update(const PhantomTime& time) {
    GameState::update(time);

    _commands.run();
}


