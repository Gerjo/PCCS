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

        GameObject* gameObject = HeavyFactory::create(description("type"));
        gameObject->fromData(description);

        layer->addComponent(gameObject);
    }

    getGame<Game*>()->startPlaying();
}

void World::update(const float& elapsed) {
    GameState::update(elapsed);

    for(Composite* composite : layer->getComponents()) {
        GameObject* gob = (GameObject*) composite;

        gob->repaint();
    }
}