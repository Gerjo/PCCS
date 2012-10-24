#include "ClientWorld.h"
#include "../Game.h"
#include "../components/RtsCamera.h"
#include "src/FixedLayer.h"

ClientWorld::ClientWorld() :
    gameobjects(new Layer()),
    fixedlayer(new FixedLayer())
{
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
    Data data;
    data.parseJson(json);

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

