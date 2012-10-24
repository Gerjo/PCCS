#include "World.h"
#include "../Game.h"
#include "../components/RtsCamera.h"
#include "src/FixedLayer.h"

World::World() :
    gameobjects(new Layer()),
    fixedlayer(new FixedLayer())
{
    addComponent(gameobjects);
    addComponent(fixedlayer);


    fixedlayer->addComponent(rtsCamera = new RtsCamera());
    fixedlayer->setCamera(camera = rtsCamera->getPhantomCamera());
}

World::~World() {

}

void World::init(void) {

}

void World::load(string json) {
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

void World::update(const float& elapsed) {
    GameState::update(elapsed);

    _commands.run();
}

