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

    for(Data::KeyValue pair : data("static")) {
        Data& description = pair.second;

        _commands.add([this, description] () mutable -> void {
            GameObject* gameObject = HeavyFactory::create(description("type"));
            gameObject->fromData(description);

            layer->addComponent(gameObject);
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

