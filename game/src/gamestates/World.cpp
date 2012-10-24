#include "World.h"
#include "src/Game.h"


World::World() : layer(new Layer()) {
    addComponent(layer);
}

World::~World() {

}

void World::init(void) {

}

void World::load(string json) {

    Data data;
    data.parseJson(json);

    Layer* gobLayer = layer;

    for(Data::KeyValue pair : data("static")) {
        Data& description = pair.second;

        _commands.add([&gobLayer, description] (void) {
            Data readable(description);

            GameObject* gameObject = HeavyFactory::create(readable("type"));
            gameObject->fromData(readable);

            gobLayer->addComponent(gameObject);
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