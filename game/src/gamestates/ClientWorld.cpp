#include "ClientWorld.h"
#include "../Game.h"
#include "../components/RtsCamera.h"
#include "src/FixedLayer.h"
#include <sharedlib/pathfinding/BSPTree.h>

ClientWorld::ClientWorld() :
    fixedlayer(new FixedLayer()),
    gameobjects(new BSPTree(2000, 2000, 20, 50))
{
    setType("ClientWorld");

    addComponent(gameobjects);
    addComponent(fixedlayer);

    fixedlayer->addComponent(rtsCamera = new RtsCamera());
    fixedlayer->setCamera(camera = rtsCamera->getPhantomCamera());
}

ClientWorld::~ClientWorld() {

}

void ClientWorld::init(void) {

}

void ClientWorld::load(string json) {
    //cout << json << endl;
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


